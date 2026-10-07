//
// Created by Monika on 27.09.2026.
//

#include <Engine/World/TerrainGrassRenderer.h>

#include <Graphics/Pipeline/Pipeline.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Memory/DescriptorManager.h>
#include <Graphics/Types/Shader.h>

#include <Utils/ECS/Transform.h>

#include <Codegen/TerrainGrassRenderer.generated.hpp>

namespace SR_CORE_NS {
    /// Раскладка инстанс-буфера должна совпадать с TerrainGrassInstance байт в байт.
    /// VertexLayoutDescription выравнивает каждый атрибут по 16 байт, поэтому инстанс упакован в два vec4:
    /// CUSTOM0 = (position.xyz, rank), CUSTOM1 = (normal.xyz, random) - смещения 0 и 16, шаг 32.
    static const auto TerrainGrassInstanceLayout = SR_UTILS_NS::VertexLayoutDescription()
        .AddAttribute(SR_UTILS_NS::VertexAttribute::Custom0, SR_UTILS_NS::VertexAttributeFormat::Float32, 4)
        .AddAttribute(SR_UTILS_NS::VertexAttribute::Custom1, SR_UTILS_NS::VertexAttributeFormat::Float32, 4)
        .SetInstanced(true);

    static const SR_UTILS_NS::StringAtom SHADER_GRASS_ORIGIN = "grassOrigin";
    static const SR_UTILS_NS::StringAtom SHADER_GRASS_FULL_DENSITY_DISTANCE = "grassFullDensityDistance";
    static const SR_UTILS_NS::StringAtom SHADER_GRASS_MAX_DISTANCE = "grassMaxDistance";
    static const SR_UTILS_NS::StringAtom SHADER_GRASS_FALLOFF = "grassFalloff";
    static const SR_UTILS_NS::StringAtom SHADER_GRASS_MIN_KEEP = "grassMinKeep";
    static const SR_UTILS_NS::StringAtom SHADER_GRASS_SEGMENTS_LOD_DISTANCE = "grassSegmentsLodDistance";
    static const SR_UTILS_NS::StringAtom SHADER_GRASS_SEGMENTS = "grassSegments";
    static const SR_UTILS_NS::StringAtom SHADER_GRASS_LOW_SEGMENTS = "grassLowSegments";
    static const SR_UTILS_NS::StringAtom SHADER_GRASS_BENDERS_COUNT = "grassBendersCount";
    static const SR_UTILS_NS::StringAtom SHADER_GRASS_BENDERS_SSBO = "grassBenders";

    float_t TerrainGrassLodParams::GetKeepFraction(float_t distance) const noexcept {
        if (distance <= fullDensityDistance) {
            return 1.f;
        }
        if (distance >= maxDistance || maxDistance <= fullDensityDistance) {
            return 0.f;
        }
        const float_t x = 1.f - (distance - fullDensityDistance) / (maxDistance - fullDensityDistance);
        return std::max(minKeep, std::pow(x, falloff));
    }

    void TerrainGrassRenderer::SetInstances(SR_UTILS_NS::Vector<TerrainGrassInstance>&& instances, SR_UTILS_NS::Vector<TerrainGrassCell>&& cells) {
        SR_TRACY_ZONE;
        {
            std::lock_guard lock(m_mutex);
            m_instancesCount = static_cast<uint32_t>(instances.size());
            m_pendingInstances = std::move(instances);
            m_cells = std::move(cells);
            m_cellLevels.assign(m_cells.size(), 0);
            m_ranges.clear();
            m_drawnCount = 0;
            m_isDataDirty = true;
        }
        MarkRenderDirty();
    }

    void TerrainGrassRenderer::ClearInstances() {
        SR_TRACY_ZONE;
        {
            std::lock_guard lock(m_mutex);
            if (m_instancesCount == 0 && m_cells.empty()) {
                return;
            }
            m_instancesCount = 0;
            m_drawnCount = 0;
            SR_UTILS_NS::Vector<TerrainGrassInstance>().swap(m_pendingInstances);
            SR_UTILS_NS::Vector<TerrainGrassCell>().swap(m_cells);
            m_cellLevels.clear();
            m_ranges.clear();
            m_isDataDirty = true;
            /// Пустой рендерер больше не рисуется, и Draw() не вызовется - буфер уходит в retired здесь,
            /// а освобождается в UpdateLod(), когда все кадры свапчейна пересоберутся
            Calculate();
        }
        MarkRenderDirty();
    }

    bool TerrainGrassCullCone::IsVisible(const SR_MATH_NS::AABB& bounds) const noexcept {
        const SR_MATH_NS::FVector3 center = bounds.GetCenter();
        const float_t radius = bounds.GetExtends().Length();

        const SR_MATH_NS::FVector3 toCenter = center - position;
        const float_t distance = toCenter.Length();

        if (distance <= radius) {
            return true; /// камера внутри (или вплотную к) ячейке
        }

        const float_t cosTheta = std::clamp(toCenter.Dot(direction) / distance, -1.f, 1.f);
        const float_t theta = std::acos(cosTheta);
        const float_t sphereAngle = std::asin(std::clamp(radius / distance, 0.f, 1.f));

        return theta <= halfAngle + sphereAngle;
    }

    bool TerrainGrassRenderer::UpdateLod(const SR_MATH_NS::FVector3& observer, const TerrainGrassLodParams& params, const TerrainGrassCullCone* pCone) {
        SR_TRACY_ZONE;

        bool changed = false;
        bool uniformsChanged = false;

        {
            std::lock_guard lock(m_mutex);

            /// Draw() не вызывается у пустых и выключенных рендереров, поэтому старые буферы досвобождаются и здесь.
            /// Каждый кадр свапчейна после SetDirty() пересобирает командный буфер, так что смена индекса кадра безопасна.
            if (!m_retiredVBOs.empty() && (m_ranges.empty() || !IsActive())) {
                FreeRetiredVBOs(TryGetPipeline());
            }

            if (!(m_lodParams == params)) {
                m_lodParams = params;
                uniformsChanged = true;
                changed = true;
            }

            for (size_t i = 0; i < m_cells.size(); ++i) {
                const auto& bounds = m_cells[i].bounds;

                const SR_MATH_NS::FVector3 closest(
                    std::clamp(observer.x, bounds.min.x, bounds.max.x),
                    std::clamp(observer.y, bounds.min.y, bounds.max.y),
                    std::clamp(observer.z, bounds.min.z, bounds.max.z)
                );
                const float_t distance = (observer - closest).Length();

                uint32_t buckets = 0;
                const float_t keep = params.GetKeepFraction(distance);
                if (keep > 0.f) {
                    buckets = static_cast<uint32_t>(std::ceil(keep * static_cast<float_t>(SR_TERRAIN_GRASS_RANK_BUCKETS)));
                    buckets = ((buckets + SR_TERRAIN_GRASS_LOD_STEP - 1) / SR_TERRAIN_GRASS_LOD_STEP) * SR_TERRAIN_GRASS_LOD_STEP;
                    buckets = std::min(buckets, SR_TERRAIN_GRASS_RANK_BUCKETS);
                }

                /// Гистерезис: на один шаг вниз не опускаемся, иначе на границе шагов командные буферы
                /// пересобирались бы каждый кадр. Лишние травинки всё равно гасятся в шейдере.
                const uint32_t oldBuckets = m_cellLevels[i] & 0x3Fu;
                if (buckets != 0 && buckets < oldBuckets && oldBuckets - buckets <= SR_TERRAIN_GRASS_LOD_STEP) {
                    buckets = oldBuckets;
                }

                if (buckets != 0 && pCone && !pCone->IsVisible(bounds)) {
                    buckets = 0;
                }

                uint8_t level = 0;
                if (buckets != 0) {
                    level = static_cast<uint8_t>(buckets);
                    if (distance < params.segmentsLodDistance) {
                        level |= 0x80u;
                    }
                }

                if (m_cellLevels[i] != level) {
                    m_cellLevels[i] = level;
                    changed = true;
                }
            }

            if (changed) {
                RebuildRanges();
            }
        }

        if (uniformsChanged) {
            MarkUniformsDirty();
        }

        if (changed) {
            MarkRenderDirty();
        }

        return changed;
    }

    void TerrainGrassRenderer::RebuildRanges() {
        SR_TRACY_ZONE;
        m_ranges.clear();

        const uint32_t segments = std::clamp<uint32_t>(m_lodParams.segments, 1, 7);
        const uint32_t lowSegments = std::clamp<uint32_t>(m_lodParams.lowSegments, 1, segments);
        /// две половины травинки (по обе стороны от жилки) по 2 * segments + 1 вершин + 2 вырожденные для склейки
        const uint32_t fullVertexCount = (segments * 2 + 1) * 2 + 2;
        const uint32_t lowVertexCount = (lowSegments * 2 + 1) * 2 + 2;

        uint32_t drawn = 0;

        for (size_t i = 0; i < m_cells.size(); ++i) {
            const uint8_t level = m_cellLevels[i];
            const uint32_t buckets = level & 0x3Fu;
            if (buckets == 0) {
                continue;
            }

            const auto& cell = m_cells[i];
            const uint32_t count = cell.cumulative[buckets - 1];
            if (count == 0) {
                continue;
            }

            const uint32_t vertexCount = (level & 0x80u) ? fullVertexCount : lowVertexCount;

            /// Соседние ячейки лежат в буфере подряд, поэтому полностью нарисованные ячейки склеиваются в один draw call.
            if (!m_ranges.empty()) {
                auto& last = m_ranges.back();
                if (last.start + last.count == cell.start && last.vertexCount == vertexCount) {
                    last.count += count;
                    drawn += count;
                    continue;
                }
            }

            m_ranges.emplace_back(DrawRange { .start = cell.start, .count = count, .vertexCount = vertexCount });
            drawn += count;
        }

        m_drawnCount = drawn;
    }

    void TerrainGrassRenderer::MarkRenderDirty() {
        if (auto&& pRenderScene = TryGetRenderScene()) {
            pRenderScene->SetDirty();
        }
    }

    void TerrainGrassRenderer::Calculate() {
        if (!m_isDataDirty) {
            return;
        }

        SR_TRACY_ZONE;

        m_isDataDirty = false;

        /// Старый буфер нельзя ни перезаписывать, ни удалять сразу: на него ссылаются закешированные командные
        /// буферы других кадров свапчейна. Он освобождается в FreeRetiredVBOs(), когда все кадры перезаписаны.
        if (m_VBO != SR_ID_INVALID) {
            m_retiredVBOs.emplace_back(RetiredVBO { .VBO = m_VBO });
            m_VBO = SR_ID_INVALID;
        }

        if (m_pendingInstances.empty()) {
            m_uploadedCount = 0;
            return;
        }

        auto&& pPipeline = GetPipeline();
        if (!pPipeline) SR_UNLIKELY_ATTRIBUTE {
            m_isDataDirty = true;
            return;
        }

        SRAssert(TerrainGrassInstanceLayout.GetStride() == sizeof(TerrainGrassInstance));
        const uint64_t size = m_pendingInstances.size() * sizeof(TerrainGrassInstance);
        m_VBO = pPipeline->AllocateVBO(SR_ID_INVALID, size, m_pendingInstances.data());

        if (m_VBO == SR_ID_INVALID) SR_UNLIKELY_ATTRIBUTE {
            SR_ERROR("TerrainGrassRenderer::Calculate() : failed to allocate grass instance buffer! Instances: {}", m_pendingInstances.size());
            m_uploadedCount = 0;
            return;
        }

        m_uploadedCount = static_cast<uint32_t>(m_pendingInstances.size());

        /// Данные уже на GPU, копия на CPU больше не нужна.
        SR_UTILS_NS::Vector<TerrainGrassInstance>().swap(m_pendingInstances);
    }

    bool TerrainGrassRenderer::Bind() {
        /// Все рендереры травы имеют одинаковый (пустой) GetVBO(), поэтому RenderQueue вызывает Bind()
        /// только у первого из них. Реальная привязка инстанс-буфера происходит в Draw().
        return true;
    }

    void TerrainGrassRenderer::Draw() {
        SR_TRACY_ZONE;

        if (m_hasErrors) SR_UNLIKELY_ATTRIBUTE {
            return;
        }

        auto&& pPipeline = GetPipeline();

        static SR_THREAD_LOCAL SR_UTILS_NS::Vector<DrawRange> ranges;
        uint32_t uploadedCount = 0;
        int32_t VBO = SR_ID_INVALID;
        {
            std::lock_guard lock(m_mutex);
            Calculate();
            /// Текущий кадр перезаписывается и больше не будет ссылаться на старые буферы
            FreeRetiredVBOs(pPipeline);

            if (auto&& pShader = pPipeline->GetCurrentShader()) {
                auto&& macros = pShader->GetMacros();
                if (macros.IsDefined("SR_DEFINE_CASCADED_SHADOW_MAP_PASS")) {
                    /// При инстансинге каскадов gl_InstanceIndex занят под индекс каскада, совместить с травой нельзя.
                    if (!m_castShadows || macros.IsDefined("CASCADES_INSTANCING")) {
                        return;
                    }
                }
            }

            if (m_VBO == SR_ID_INVALID || m_uploadedCount == 0 || m_ranges.empty()) {
                return;
            }
            ranges = m_ranges;
            uploadedCount = m_uploadedCount;
            VBO = m_VBO;
        }

        pPipeline->BindVBO(VBO, 0, SR_GRAPH_NS::VertexInputRate::Instance);

        bool isFirst = true;

        for (auto&& range : ranges) {
            if (range.start >= uploadedCount) SR_UNLIKELY_ATTRIBUTE {
                continue;
            }

            const uint32_t count = std::min(range.count, uploadedCount - range.start);
            pPipeline->SetDrawInstancesCount(count, range.start);

            if (isFirst) {
                /// Первый вызов привязывает UBO/дескрипторы, остальные диапазоны рисуются с тем же состоянием.
                SR_GRAPH_NS::DrawRenderObject(this, range.vertexCount, m_virtualUBO, m_virtualDescriptor, m_dirtyMaterial, m_hasErrors);
                isFirst = false;
                if (m_hasErrors) SR_UNLIKELY_ATTRIBUTE {
                    break;
                }
            }
            else {
                pPipeline->Draw(range.vertexCount);
            }
        }

        pPipeline->ResetDrawInstancesCount();
    }

    void TerrainGrassRenderer::UseMaterial(SR_GTYPES_NS::Shader& shader) {
        Super::UseMaterial(shader);
        UseModelMatrix(shader);
    }

    void TerrainGrassRenderer::UseModelMatrix(SR_GTYPES_NS::Shader& shader) {
        Super::UseModelMatrix(shader);

        SR_MATH_NS::FVector3 origin;
        if (auto&& pTransform = GetTransform()) SR_LIKELY_ATTRIBUTE {
            origin = pTransform->GetMatrix().GetTranslate();
        }

        TerrainGrassLodParams params;
        {
            std::lock_guard lock(m_mutex);
            params = m_lodParams;
        }

        const uint32_t segments = std::clamp<uint32_t>(params.segments, 1, 7);
        const uint32_t lowSegments = std::clamp<uint32_t>(params.lowSegments, 1, segments);

        shader.SetVec3(SHADER_GRASS_ORIGIN, origin);
        shader.SetFloat(SHADER_GRASS_FULL_DENSITY_DISTANCE, params.fullDensityDistance);
        shader.SetFloat(SHADER_GRASS_MAX_DISTANCE, params.maxDistance);
        shader.SetFloat(SHADER_GRASS_FALLOFF, params.falloff);
        shader.SetFloat(SHADER_GRASS_MIN_KEEP, params.minKeep);
        shader.SetFloat(SHADER_GRASS_SEGMENTS_LOD_DISTANCE, params.segmentsLodDistance);
        shader.SetInt(SHADER_GRASS_SEGMENTS, static_cast<int32_t>(segments));
        shader.SetInt(SHADER_GRASS_LOW_SEGMENTS, static_cast<int32_t>(lowSegments));

        TerrainGrassBenders::Ptr pBenders;
        {
            std::lock_guard lock(m_mutex);
            pBenders = m_pBenders;
        }

        uint32_t bendersCount = 0;
        if (pBenders) {
            SR_MAYBE_UNUSED_VAR pBenders->PrepareFrame(GetPipeline(), bendersCount);
        }
        shader.SetInt(SHADER_GRASS_BENDERS_COUNT, static_cast<int32_t>(bendersCount));
    }

    void TerrainGrassRenderer::UseSSBO() {
        Super::UseSSBO();

        TerrainGrassBenders::Ptr pBenders;
        {
            std::lock_guard lock(m_mutex);
            pBenders = m_pBenders;
        }

        uint32_t count = 0;
        const int32_t ssbo = pBenders ? pBenders->PrepareFrame(GetPipeline(), count) : SR_ID_INVALID;
        if (ssbo != SR_ID_INVALID) {
            GetPipeline()->GetCurrentShader()->BindSSBO(SHADER_GRASS_BENDERS_SSBO, static_cast<uint32_t>(ssbo));
        }
    }

    void TerrainGrassRenderer::SetBenders(const TerrainGrassBenders::Ptr& pBenders) {
        {
            std::lock_guard lock(m_mutex);
            if (m_pBenders == pBenders) {
                return;
            }
            m_pBenders = pBenders;
        }
        MarkMaterialDirty();
        MarkRenderDirty();
    }

    TerrainGrassBenders::TerrainGrassBenders()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    void TerrainGrassBenders::SetBenders(const SR_UTILS_NS::Vector<TerrainGrassBenderGPU>& benders) {
        std::lock_guard lock(m_mutex);

        const uint32_t count = static_cast<uint32_t>(std::min<size_t>(benders.size(), SR_TERRAIN_GRASS_MAX_BENDERS));
        if (count == 0 && m_count == 0) {
            return;
        }

        if (count > 0) {
            std::memcpy(m_data.data(), benders.data(), count * sizeof(TerrainGrassBenderGPU));
        }
        m_count = count;
        ++m_version;
    }

    int32_t TerrainGrassBenders::PrepareFrame(SR_GRAPH_NS::Pipeline* pPipeline, uint32_t& count) {
        std::lock_guard lock(m_mutex);

        count = m_count;

        if (!pPipeline) SR_UNLIKELY_ATTRIBUTE {
            return SR_ID_INVALID;
        }

        const uint32_t framesCount = SR_MATH_NS::Clamp<uint32_t>(pPipeline->GetSwapchainImagesCount(), 1, SR_MAX_FRAMES_IN_FLIGHT);
        const uint32_t frame = std::min<uint32_t>(pPipeline->GetCurrentImageIndex(), framesCount - 1);

        auto&& pSSBO = m_SSBOs[frame];
        if (!pSSBO) {
            pSSBO = SR_GRAPH_NS::SSBOInstance::Create<TerrainGrassBenderGPU>(SR_TERRAIN_GRASS_MAX_BENDERS, SR_GRAPH_NS::SSBOUsage::CPUToGPU, "grassBenders");
            if (!pSSBO) SR_UNLIKELY_ATTRIBUTE {
                return SR_ID_INVALID;
            }
            m_uploadedVersions[frame] = SR_UINT64_MAX;
        }

        if (m_uploadedVersions[frame] != m_version) {
            pSSBO->UpdateSSBO(m_data.data(), m_data.size() * sizeof(TerrainGrassBenderGPU));
            m_uploadedVersions[frame] = m_version;
        }

        return pSSBO->GetSSBO();
    }

    void TerrainGrassBenders::FreeVideoMemory() {
        std::lock_guard lock(m_mutex);
        for (auto&& pSSBO : m_SSBOs) {
            pSSBO.reset();
        }
    }

    SR_UTILS_NS::VertexLayoutDescriptionsRef TerrainGrassRenderer::GetShaderVertexLayoutDescriptions() const noexcept {
        return SR_UTILS_NS::VertexLayoutDescriptionsRef(TerrainGrassInstanceLayout);
    }

    bool TerrainGrassRenderer::FreeRetired() {
        std::lock_guard lock(m_mutex);
        FreeRetiredVBOs(TryGetPipeline());
        return m_retiredVBOs.empty();
    }

    void TerrainGrassRenderer::FreeRetiredVBOs(SR_GRAPH_NS::Pipeline* pPipeline) {
        if (m_retiredVBOs.empty() || !pPipeline) {
            return;
        }

        const uint32_t framesCount = SR_MATH_NS::Clamp<uint32_t>(pPipeline->GetSwapchainImagesCount(), 1, SR_MAX_FRAMES_IN_FLIGHT);
        const uint32_t frame = std::min<uint32_t>(pPipeline->GetCurrentImageIndex(), framesCount - 1);

        for (auto pIt = m_retiredVBOs.begin(); pIt != m_retiredVBOs.end(); ) {
            pIt->rebuiltFrames.set(frame);

            bool isFree = true;
            for (uint32_t i = 0; i < framesCount; ++i) {
                if (!pIt->rebuiltFrames.test(i)) {
                    isFree = false;
                    break;
                }
            }

            if (isFree) {
                pPipeline->FreeVBO(&pIt->VBO);
                pIt = m_retiredVBOs.erase(pIt);
            }
            else {
                ++pIt;
            }
        }
    }

    void TerrainGrassRenderer::FreeVideoMemory() {
        Super::FreeVideoMemory();

        {
            std::lock_guard lock(m_mutex);

            if (m_VBO != SR_ID_INVALID) {
                GetPipeline()->FreeVBO(&m_VBO);
            }

            for (auto&& retired : m_retiredVBOs) {
                GetPipeline()->FreeVBO(&retired.VBO);
            }
            m_retiredVBOs.clear();

            m_uploadedCount = 0;
            /// Если данные ещё не были залиты, они останутся в m_pendingInstances. Иначе их нужно сгенерировать заново.
            m_isDataDirty = !m_pendingInstances.empty();
        }

        auto&& uboManager = SR_GRAPH_NS::Memory::UBOManager::Instance();
        auto&& descriptorManager = SR_GRAPH_NS::DescriptorManager::Instance();

        if (m_virtualUBO != SR_ID_INVALID && !uboManager.FreeUBO(&m_virtualUBO)) {
            SR_ERROR("TerrainGrassRenderer::FreeVideoMemory() : failed to free virtual uniform buffer object!");
        }

        if (m_virtualDescriptor != SR_ID_INVALID && !descriptorManager.FreeDescriptorSet(&m_virtualDescriptor)) {
            SR_ERROR("TerrainGrassRenderer::FreeVideoMemory() : failed to free virtual descriptor set!");
        }
    }
}
