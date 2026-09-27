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

    void ITerrainChunk::Activate(SR_UTILS_NS::SceneObject& pool, const SR_UTILS_NS::SceneObject& proto, SR_MATH_NS::FVector3 position) {
        SR_TRACY_ZONE;
        if (!m_object) {
            m_object = proto.CloneSceneObject();
            pool.AddChild(m_object);
        }

        if (auto&& pGameObject = m_object.DynamicCast<SR_UTILS_NS::GameObject>()) {
            pGameObject->GetTransform()->SetTranslation(position);
        }

        m_object->SetEnabled(true);
    }

    void ITerrainChunk::Deactivate() {
        SR_TRACY_ZONE;
        if (m_grass) {
            m_grass->OnChunkDeactivated(*this);
        }
        if (m_data) {
            m_data->Deactivate();
        }
        if (m_object) {
            m_object->SetEnabled(false);
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
        }

        return data;
    }
}
