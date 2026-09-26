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

        m_object->SetEnabled(true);

        if (auto&& pGameObject = m_object.DynamicCast<SR_UTILS_NS::GameObject>()) {
            pGameObject->GetTransform()->SetTranslation(position);
        }
    }

    void ITerrainChunk::Deactivate() {
        SR_TRACY_ZONE;
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
            m_chunkGenerator->Update(*this, dt);
            m_chunkGenerator->LoadNextChunk([this](ITerrainChunk& chunk) {
                if (m_chunkDataGenerator) {
                    m_chunkDataGenerator->GenerateChunkData(*this, chunk);
                }
                chunk.SetStatus(ITerrainChunk::Status::Loaded);
            });
        }
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
        }

        return data;
    }
}
