//
// Created by Monika on 28.11.2026.
//

#include <Engine/World/TerrainScatterRenderer.h>

#include <Graphics/Pipeline/Pipeline.h>
#include <Graphics/Pipeline/ShaderUtils.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Memory/DescriptorManager.h>
#include <Graphics/Types/Shader.h>

#include <Utils/ECS/Transform.h>
#include <Utils/Types/RawMesh.h>

#include <Codegen/TerrainScatterRenderer.generated.hpp>

namespace SR_CORE_NS {
    /// Слот 0 - инстансы (строки матрицы 3x4), слот 1 - геометрия меша.
    /// VertexLayoutDescription выравнивает атрибуты по 16 байт: три vec4 подряд дают шаг 48, как TerrainScatterInstanceGPU
    static const auto TerrainScatterInstanceLayout = SR_UTILS_NS::VertexLayoutDescription()
        .AddAttribute(SR_UTILS_NS::VertexAttribute::Custom0, SR_UTILS_NS::VertexAttributeFormat::Float32, 4)
        .AddAttribute(SR_UTILS_NS::VertexAttribute::Custom1, SR_UTILS_NS::VertexAttributeFormat::Float32, 4)
        .AddAttribute(SR_UTILS_NS::VertexAttribute::Custom2, SR_UTILS_NS::VertexAttributeFormat::Float32, 4)
        .SetInstanced(true);

    /// Позиция обязана быть первым атрибутом: упрощение meshoptimizer читает её по нулевому смещению вершины
    static const auto TerrainScatterGeometryLayout = SR_UTILS_NS::VertexLayoutDescription()
        .AddAttribute(SR_UTILS_NS::VertexAttribute::Position, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
        .AddAttribute(SR_UTILS_NS::VertexAttribute::UV0, SR_UTILS_NS::VertexAttributeFormat::Float32, 2)
        .AddAttribute(SR_UTILS_NS::VertexAttribute::Normal, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
        .AddAttribute(SR_UTILS_NS::VertexAttribute::Tangent, SR_UTILS_NS::VertexAttributeFormat::Float32, 4);

    static const std::array<SR_UTILS_NS::VertexLayoutDescription, 2> TerrainScatterLayouts = {
        TerrainScatterInstanceLayout,
        TerrainScatterGeometryLayout
    };

    void TerrainScatterRenderer::SetGeometry(const SR_UTILS_NS::Path& meshPath, int32_t meshId, float_t simplifyRatio) {
        SR_TRACY_ZONE;

        {
            std::lock_guard lock(m_mutex);
            m_simplifyRatio = std::clamp(simplifyRatio, 0.01f, 1.f);
            m_isGeometryDirty = true;
        }

        SetRawMesh(meshPath);
        SetMeshId(meshId);
    }

    void TerrainScatterRenderer::SetInstances(const SR_UTILS_NS::Vector<TerrainScatterInstanceGPU>& instances) {
        SR_TRACY_ZONE;
        {
            std::lock_guard lock(m_mutex);
            /// Набор не изменился - буфер не перезаливается и командные буферы не пересобираются
            if (instances.size() == m_instances.size() && (instances.empty() || std::memcmp(instances.data(), m_instances.data(), instances.size() * sizeof(TerrainScatterInstanceGPU)) == 0)) {
                return;
            }
            m_instances.assign(instances.begin(), instances.end());
            m_statInstances = static_cast<uint32_t>(instances.size());
            m_instancesCount = static_cast<uint32_t>(instances.size());
            m_isInstancesDirty = true;
        }
        MarkRenderDirty();
    }

    void TerrainScatterRenderer::ClearInstances() {
        SetInstances(SR_UTILS_NS::Vector<TerrainScatterInstanceGPU>());
    }

    void TerrainScatterRenderer::OnRawMeshChanged() {
        IRawMeshHolder::OnRawMeshChanged();
        {
            std::lock_guard lock(m_mutex);
            m_isGeometryDirty = true;
        }
        ReRegisterRenderObject();
        MarkMaterialDirty();
    }

    void TerrainScatterRenderer::MarkRenderDirty() {
        if (auto&& pRenderScene = TryGetRenderScene()) {
            pRenderScene->SetDirty();
        }
    }

    void TerrainScatterRenderer::Calculate() {
        auto&& pPipeline = TryGetPipeline();
        if (!pPipeline) SR_UNLIKELY_ATTRIBUTE {
            return;
        }

        CalculateGeometry(pPipeline);
        CalculateInstances(pPipeline);
    }

    void TerrainScatterRenderer::CalculateGeometry(SR_GRAPH_NS::Pipeline* pPipeline) {
        if (!m_isGeometryDirty) {
            return;
        }

        auto&& pRawMesh = GetRawMesh();
        if (!pRawMesh || !pRawMesh->CanBeUsed() || !IsValidMeshId()) {
            return; /// модель ещё грузится - попробуем в следующей отрисовке
        }

        SR_TRACY_ZONE;

        m_isGeometryDirty = false;

        if (m_geometryIBO != SR_ID_INVALID) {
            pPipeline->FreeIBO(&m_geometryIBO);
        }
        if (m_geometryVBO != SR_ID_INVALID) {
            pPipeline->FreeVBO(&m_geometryVBO);
        }
        m_indicesCount = 0;

        auto&& vertices = GetVertexBuffer(TerrainScatterGeometryLayout);
        auto&& indices = pRawMesh->GetIndices(GetMeshId());
        if (vertices.vertexCount == 0 || indices.empty()) {
            SR_WARN("TerrainScatterRenderer::CalculateGeometry() : mesh {} has no geometry! Path: {}", GetMeshId(), GetMeshStringPath());
            return;
        }

        const SR_HTYPES_NS::FastMemoryArray<uint32_t>* pIndices = &indices;

        SR_HTYPES_NS::FastMemoryArray<uint32_t> simplified;
        if (m_simplifyRatio < 0.999f) {
            const uint64_t targetCount = std::max<uint64_t>(3, static_cast<uint64_t>(static_cast<float_t>(indices.size()) * m_simplifyRatio) / 3 * 3);
            /// Ошибка не ограничивается: дальний LOD должен уложиться в заданную долю треугольников
            if (SR_UTILS_NS::Details::OptimizeVerticesImpl(vertices.GetRawData(), vertices.GetLayout().GetStride(), vertices.vertexCount, indices, targetCount, 1.f, simplified) && !simplified.empty()) {
                pIndices = &simplified;
            }
        }

        m_geometryVBO = pPipeline->AllocateVBO(SR_ID_INVALID, vertices.GetDataSize(), vertices.GetRawData());
        if (m_geometryVBO == SR_ID_INVALID) SR_UNLIKELY_ATTRIBUTE {
            SR_ERROR("TerrainScatterRenderer::CalculateGeometry() : failed to allocate vertex buffer!");
            m_hasErrors = true;
            return;
        }

        m_geometryIBO = pPipeline->AllocateIBO(pIndices->data(), sizeof(uint32_t), pIndices->size(), m_geometryVBO);
        if (m_geometryIBO == SR_ID_INVALID) SR_UNLIKELY_ATTRIBUTE {
            SR_ERROR("TerrainScatterRenderer::CalculateGeometry() : failed to allocate index buffer!");
            pPipeline->FreeVBO(&m_geometryVBO);
            m_hasErrors = true;
            return;
        }

        m_indicesCount = static_cast<uint32_t>(pIndices->size());
    }

    void TerrainScatterRenderer::CalculateInstances(SR_GRAPH_NS::Pipeline* pPipeline) {
        if (!m_isInstancesDirty) {
            return;
        }

        SR_TRACY_ZONE;

        m_isInstancesDirty = false;

        /// Старый буфер ещё читают закешированные командные буферы других кадров свапчейна
        if (m_instancesVBO != SR_ID_INVALID) {
            m_retiredVBOs.emplace_back(RetiredVBO { .VBO = m_instancesVBO });
            m_instancesVBO = SR_ID_INVALID;
        }

        m_uploadedCount = 0;

        if (m_instances.empty()) {
            return;
        }

        SRAssert(TerrainScatterInstanceLayout.GetStride() == sizeof(TerrainScatterInstanceGPU));
        const uint64_t size = m_instances.size() * sizeof(TerrainScatterInstanceGPU);
        m_instancesVBO = pPipeline->AllocateVBO(SR_ID_INVALID, size, m_instances.data());

        if (m_instancesVBO == SR_ID_INVALID) SR_UNLIKELY_ATTRIBUTE {
            SR_ERROR("TerrainScatterRenderer::CalculateInstances() : failed to allocate instance buffer! Instances: {}", m_instances.size());
            return;
        }

        m_uploadedCount = static_cast<uint32_t>(m_instances.size());
    }

    bool TerrainScatterRenderer::Bind() {
        /// GetVBO() у всех рендереров пустой, RenderQueue вызывает Bind() только у первого из них.
        /// Буферы привязываются в Draw()
        return true;
    }

    void TerrainScatterRenderer::Draw() {
        SR_TRACY_ZONE;

        if (m_hasErrors) SR_UNLIKELY_ATTRIBUTE {
            return;
        }

        auto&& pPipeline = GetPipeline();

        /// Проход каскадных теней с инстансингом рисует несколько каскадов одним вызовом через номер инстанса.
        /// Номер инстанса здесь занят, такие каскады пропускаются (тени остаются в каскадах, рисуемых по одному)
        const uint32_t passInstancesCount = pPipeline->GetDrawInstancesCount();
        const uint32_t passInstancesStart = pPipeline->GetDrawInstancesStart();
        if (passInstancesCount != 1) {
            return;
        }

        int32_t instancesVBO = SR_ID_INVALID;
        int32_t geometryVBO = SR_ID_INVALID;
        int32_t geometryIBO = SR_ID_INVALID;
        uint32_t instancesCount = 0;
        uint32_t indicesCount = 0;
        {
            std::lock_guard lock(m_mutex);
            Calculate();
            /// Текущий кадр перезаписывается и больше не ссылается на старые буферы
            FreeRetiredVBOs(pPipeline);

            instancesVBO = m_instancesVBO;
            geometryVBO = m_geometryVBO;
            geometryIBO = m_geometryIBO;
            instancesCount = m_uploadedCount;
            indicesCount = m_indicesCount;
        }

        if (instancesVBO == SR_ID_INVALID || geometryVBO == SR_ID_INVALID || geometryIBO == SR_ID_INVALID || instancesCount == 0 || indicesCount == 0) {
            return;
        }

        pPipeline->BindVBO(instancesVBO, 0, SR_GRAPH_NS::VertexInputRate::Instance);
        pPipeline->BindVBO(geometryVBO, 1, SR_GRAPH_NS::VertexInputRate::Vertex);
        pPipeline->BindIBO(geometryIBO);

        pPipeline->SetDrawInstancesCount(instancesCount);

        SR_GRAPH_NS::DrawRenderObject(this, indicesCount, m_virtualUBO, m_virtualDescriptor, m_dirtyMaterial, m_hasErrors);

        /// Состояние прохода восстанавливается: следующие объекты очереди рисуются с ним
        pPipeline->SetDrawInstancesCount(passInstancesCount, passInstancesStart);
        pPipeline->BindVBO(SR_ID_INVALID, 1, SR_GRAPH_NS::VertexInputRate::Vertex);
    }

    std::optional<int32_t> TerrainScatterRenderer::GetIBO() const {
        if (m_geometryIBO == SR_ID_INVALID) {
            return std::nullopt;
        }
        return m_geometryIBO;
    }

    void TerrainScatterRenderer::UseMaterial(SR_GTYPES_NS::Shader& shader) {
        Super::UseMaterial(shader);
        UseModelMatrix(shader);
    }

    void TerrainScatterRenderer::UseModelMatrix(SR_GTYPES_NS::Shader& shader) {
        Super::UseModelMatrix(shader);

        if (auto&& pTransform = GetTransform()) SR_LIKELY_ATTRIBUTE {
            shader.SetMat4(SR_GRAPH_NS::SHADER_MODEL_MATRIX, pTransform->GetMatrix());
        }
    }

    SR_UTILS_NS::VertexLayoutDescriptionsRef TerrainScatterRenderer::GetShaderVertexLayoutDescriptions() const noexcept {
        return SR_UTILS_NS::VertexLayoutDescriptionsRef(TerrainScatterLayouts);
    }

    void TerrainScatterRenderer::FreeRetired() {
        std::lock_guard lock(m_mutex);
        /// Пустой рендерер не рисуется и Draw() не вызывается, поэтому старые буферы досвобождаются отсюда
        if (m_uploadedCount == 0 || !IsActive()) {
            FreeRetiredVBOs(TryGetPipeline());
        }
    }

    void TerrainScatterRenderer::FreeRetiredVBOs(SR_GRAPH_NS::Pipeline* pPipeline) {
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

    void TerrainScatterRenderer::FreeVideoMemory() {
        SR_TRACY_ZONE;

        Super::FreeVideoMemory();

        {
            std::lock_guard lock(m_mutex);

            auto&& pPipeline = GetPipeline();

            if (m_instancesVBO != SR_ID_INVALID) {
                pPipeline->FreeVBO(&m_instancesVBO);
            }
            if (m_geometryIBO != SR_ID_INVALID) {
                pPipeline->FreeIBO(&m_geometryIBO);
            }
            if (m_geometryVBO != SR_ID_INVALID) {
                pPipeline->FreeVBO(&m_geometryVBO);
            }

            for (auto&& retired : m_retiredVBOs) {
                pPipeline->FreeVBO(&retired.VBO);
            }
            m_retiredVBOs.clear();

            m_uploadedCount = 0;
            m_indicesCount = 0;
            m_isGeometryDirty = true;
            /// Копия инстансов на CPU сохраняется - буфер перезальётся при следующей отрисовке
            m_isInstancesDirty = !m_instances.empty();
        }

        auto&& uboManager = SR_GRAPH_NS::Memory::UBOManager::Instance();
        auto&& descriptorManager = SR_GRAPH_NS::DescriptorManager::Instance();

        if (m_virtualUBO != SR_ID_INVALID && !uboManager.FreeUBO(&m_virtualUBO)) {
            SR_ERROR("TerrainScatterRenderer::FreeVideoMemory() : failed to free virtual uniform buffer object!");
        }

        if (m_virtualDescriptor != SR_ID_INVALID && !descriptorManager.FreeDescriptorSet(&m_virtualDescriptor)) {
            SR_ERROR("TerrainScatterRenderer::FreeVideoMemory() : failed to free virtual descriptor set!");
        }
    }
}
