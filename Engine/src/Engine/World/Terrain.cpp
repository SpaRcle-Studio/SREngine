//
// Created by Monika on 27.08.2026.
//

#include <Engine/World/Terrain.h>

#include <Utils/World/Scene.h>
#include <Utils/ECS/GameObject.h>

#include <Codegen/Terrain.generated.hpp>

namespace SR_CORE_NS {
    ITerrainChunkData::ITerrainChunkData()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    ITerrainChunk::ITerrainChunk()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    bool ITerrainChunk::IsGrassReady() const {
        return !m_grass || m_grass->IsChunkReady(*this);
    }

    void ITerrainChunk::Deactivate() {
        SR_TRACY_ZONE;
        if (m_grass) {
            m_grass->OnChunkDeactivated(*this);
        }
        if (m_data) {
            m_data->Deactivate();
        }
    }

    SR_UTILS_NS::SceneObject::Ptr ITerrainChunkGenerator::AcquireChunkObject(ITerrainChunk& chunk) {
        SR_TRACY_ZONE;

        if (auto&& pObject = chunk.GetObject()) {
            return pObject;
        }

        SR_UTILS_NS::SceneObject::Ptr pObject;
        if (!m_freeObjects.empty()) {
            pObject = m_freeObjects.back();
            m_freeObjects.pop_back();
        }
        else {
            auto&& pProto = m_chunkObjectProto.Get();
            auto&& pPool = m_poolObject.Get();
            if (!pProto || !pPool) {
                SR_ERROR("ITerrainChunkGenerator::AcquireChunkObject() : chunk object proto or pool object is null!");
                return nullptr;
            }
            pObject = pProto->CloneSceneObject();
            pPool->AddChild(pObject);
        }

        chunk.SetObject(pObject);
        SetupChunkObject(chunk, *pObject);
        pObject->SetEnabled(true);

        return pObject;
    }

    void ITerrainChunkGenerator::ReleaseChunkObject(ITerrainChunk& chunk) {
        SR_TRACY_ZONE;

        chunk.Deactivate();

        SR_UTILS_NS::SceneObject::Ptr pObject = chunk.GetObject();
        if (!pObject) {
            return;
        }

        /// Трава рисуется относительно текущей позиции объекта. Если объект уйдёт в пул с инстансами,
        /// следующий чанк нарисует их на своём месте поверх своей травы. Чистим независимо от того,
        /// успел ли чанк получить траву (SetGrass вызывается только после генерации травы).
        if (auto&& pGrassRenderer = pObject->GetComponent<TerrainGrassRenderer>()) {
            pGrassRenderer->ClearInstances();
        }

        chunk.SetObject(nullptr);
        chunk.SetGrass(nullptr);

        if (m_freeObjects.size() < m_maxFreeObjects) {
            pObject->SetEnabled(false);
            m_freeObjects.emplace_back(pObject);
        }
        else {
            pObject->Destroy();
        }
    }

    ITerrainChunkGenerator::ITerrainChunkGenerator()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    ITerrainChunkDataGenerator::ITerrainChunkDataGenerator()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    void Terrain::Update(float_t dt) {
        Super::Update(dt);

        if (m_chunkGenerator) {
            auto&& observer = GetObserver();
            m_chunkGenerator->LoadNextChunk([this, &observer](ITerrainChunk& chunk) {
                if (m_chunkDataGenerator) {
                    m_chunkDataGenerator->GenerateChunkData(*this, chunk, observer, 0.f);
                }
                chunk.SetStatus(ITerrainChunk::Status::Loaded);
            });
            m_chunkGenerator->Update(*this, observer, dt);
        }

        if (m_grass) {
            m_grass->Update(*this, dt);
        }
    }

    void Terrain::OnDestroy() {
        if (m_grass) {
            m_grass->Shutdown();
        }
        Super::OnDestroy();
    }

    TerrainGrass* Terrain::GetGrass() const noexcept {
        if (m_grass && m_grass->IsEnabled()) {
            return const_cast<TerrainGrass*>(m_grass.Get());
        }
        return nullptr;
    }

    ITerrainChunkGenerator* Terrain::GetChunkGenerator() const noexcept {
        return const_cast<ITerrainChunkGenerator*>(m_chunkGenerator.Get());
    }

    TerrainObserverData Terrain::GetObserver() const {
        SR_TRACY_ZONE;

        TerrainObserverData data;

        SR_GTYPES_NS::Camera* pCamera = nullptr;
        if (auto&& pCameraRef = m_camera.Get()) {
            pCamera = pCameraRef.Get();
        }
        else if (auto&& pMainCamera = GetScene()->GetMainCamera()) {
            pCamera = pMainCamera->GetComponent<SR_GTYPES_NS::Camera>().Get();
        }

        if (pCamera) {
            data.position = pCamera->GetPosition();
            /// Направление берётся из тех же матриц, с которыми рисуется кадр: строка w матрицы PROJECTION * VIEW -
            /// это градиент глубины, т.е. направление "вперёд" независимо от соглашений осей камеры.
            const SR_MATH_NS::Matrix4x4 viewProjection = pCamera->GetProjection() * pCamera->GetViewTranslate();
            const SR_MATH_NS::FVector3 forward(viewProjection[0][3], viewProjection[1][3], viewProjection[2][3]);
            data.direction = forward.Length() > 1e-6f ? forward.Normalized() : pCamera->GetViewDirection();
            data.fovY = SR_RAD(pCamera->GetFOV());
            data.aspect = pCamera->GetAspect();
            data.farPlane = pCamera->GetFar();
        }

        return data;
    }

    SR_MATH_NS::AABB TerrainDeformation::GetBounds() const noexcept {
        const SR_MATH_NS::FVector3 extents = size.Abs();
        return SR_MATH_NS::AABB(position - extents, position + extents);
    }

    void Terrain::AddDeformation(const TerrainDeformation& deformation) {
        if (deformation.strength <= 0.f) {
            return;
        }
        m_pendingDeformations.emplace_back(deformation);
    }

    void Terrain::LateUpdate() {
        Super::LateUpdate();

        if (m_pendingDeformations.empty()) {
            return;
        }

        SR_TRACY_ZONE;

        /// Область всех деформаций кадра: чанки перегенерируются один раз, а не на каждую деформацию
        SR_MATH_NS::AABB region = m_pendingDeformations[0].GetBounds();
        for (auto&& deformation : m_pendingDeformations) {
            ApplyDeformation(deformation);

            const SR_MATH_NS::AABB bounds = deformation.GetBounds();
            region.min = SR_MATH_NS::FVector3(std::min(region.min.x, bounds.min.x), std::min(region.min.y, bounds.min.y), std::min(region.min.z, bounds.min.z));
            region.max = SR_MATH_NS::FVector3(std::max(region.max.x, bounds.max.x), std::max(region.max.y, bounds.max.y), std::max(region.max.z, bounds.max.z));
        }

        m_pendingDeformations.clear();

        if (m_chunkGenerator) {
            m_chunkGenerator->InvalidateRegion(region);
        }
    }

    void Terrain::ApplyDeformation(const TerrainDeformation& deformation) {
        SR_TRACY_ZONE;

        if (!m_chunkGenerator) {
            return;
        }

        /// Точка плотности d лежит в мире на (d - 0.5) * voxelSize (см. Density.srsl).
        /// Плотность измеряется в вокселях, поэтому strength (метры) делится на размер вокселя.
        const SR_MATH_NS::FVector3 voxelSize = m_chunkGenerator->GetVoxelSize();
        const SR_MATH_NS::FVector3 size = SR_MATH_NS::FVector3(
            std::max(std::abs(deformation.size.x), 0.001f),
            std::max(std::abs(deformation.size.y), 0.001f),
            std::max(std::abs(deformation.size.z), 0.001f)
        );
        const float_t strength = (deformation.isAdditive ? deformation.strength : -deformation.strength) / voxelSize.y;

        const SR_MATH_NS::AABB bounds = deformation.GetBounds();
        const SR_MATH_NS::IVector3 minPoint(
            static_cast<int32_t>(std::floor(bounds.min.x / voxelSize.x + 0.5f)),
            static_cast<int32_t>(std::floor(bounds.min.y / voxelSize.y + 0.5f)),
            static_cast<int32_t>(std::floor(bounds.min.z / voxelSize.z + 0.5f))
        );
        const SR_MATH_NS::IVector3 maxPoint(
            static_cast<int32_t>(std::ceil(bounds.max.x / voxelSize.x + 0.5f)),
            static_cast<int32_t>(std::ceil(bounds.max.y / voxelSize.y + 0.5f)),
            static_cast<int32_t>(std::ceil(bounds.max.z / voxelSize.z + 0.5f))
        );

        constexpr int32_t blockSize = SR_TERRAIN_EDIT_BLOCK_SIZE;

        for (int32_t z = minPoint.z; z <= maxPoint.z; ++z) {
            for (int32_t y = minPoint.y; y <= maxPoint.y; ++y) {
                for (int32_t x = minPoint.x; x <= maxPoint.x; ++x) {
                    const SR_MATH_NS::FVector3 worldPos(
                        (static_cast<float_t>(x) - 0.5f) * voxelSize.x,
                        (static_cast<float_t>(y) - 0.5f) * voxelSize.y,
                        (static_cast<float_t>(z) - 0.5f) * voxelSize.z
                    );
                    const SR_MATH_NS::FVector3 local = (worldPos - deformation.position) / size;

                    /// Нормированное расстояние до границы формы: 0 в центре, 1 на границе
                    float_t distance = 0.f;
                    if (deformation.shape == TerrainDeformationShape::Box) {
                        distance = std::max({ std::abs(local.x), std::abs(local.y), std::abs(local.z) });
                    }
                    else {
                        distance = local.Length();
                    }

                    if (distance >= 1.f) {
                        continue;
                    }

                    const SR_MATH_NS::IVector3 blockCoord(
                        static_cast<int32_t>(std::floor(static_cast<float_t>(x) / blockSize)),
                        static_cast<int32_t>(std::floor(static_cast<float_t>(y) / blockSize)),
                        static_cast<int32_t>(std::floor(static_cast<float_t>(z) / blockSize))
                    );

                    auto&& pBlock = m_editBlocks[blockCoord];
                    if (!pBlock) {
                        pBlock = SR_UTILS_NS::RawPointerHolder<DensityEditBlock>(new DensityEditBlock());
                    }

                    const int32_t lx = x - blockCoord.x * blockSize;
                    const int32_t ly = y - blockCoord.y * blockSize;
                    const int32_t lz = z - blockCoord.z * blockSize;
                    pBlock->values[(lz * blockSize + ly) * blockSize + lx] += strength * (1.f - distance);
                }
            }
        }
    }

    float_t Terrain::GetDensityOffset(const SR_MATH_NS::IVector3& point) const {
        constexpr int32_t blockSize = SR_TERRAIN_EDIT_BLOCK_SIZE;

        const SR_MATH_NS::IVector3 blockCoord(
            static_cast<int32_t>(std::floor(static_cast<float_t>(point.x) / blockSize)),
            static_cast<int32_t>(std::floor(static_cast<float_t>(point.y) / blockSize)),
            static_cast<int32_t>(std::floor(static_cast<float_t>(point.z) / blockSize))
        );

        auto&& pIt = m_editBlocks.find(blockCoord);
        if (pIt == m_editBlocks.end()) {
            return 0.f;
        }

        const int32_t lx = point.x - blockCoord.x * blockSize;
        const int32_t ly = point.y - blockCoord.y * blockSize;
        const int32_t lz = point.z - blockCoord.z * blockSize;
        return pIt->second->values[(lz * blockSize + ly) * blockSize + lx];
    }

    bool Terrain::HasDensityOffsets(const SR_MATH_NS::IVector3& min, const SR_MATH_NS::IVector3& max) const {
        if (m_editBlocks.empty()) {
            return false;
        }

        constexpr int32_t blockSize = SR_TERRAIN_EDIT_BLOCK_SIZE;

        const auto toBlock = [](int32_t v) {
            return static_cast<int32_t>(std::floor(static_cast<float_t>(v) / blockSize));
        };

        for (int32_t z = toBlock(min.z); z <= toBlock(max.z); ++z) {
            for (int32_t y = toBlock(min.y); y <= toBlock(max.y); ++y) {
                for (int32_t x = toBlock(min.x); x <= toBlock(max.x); ++x) {
                    if (m_editBlocks.find(SR_MATH_NS::IVector3(x, y, z)) != m_editBlocks.end()) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
}
