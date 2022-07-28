//
// Created by Monika on 17.11.2021.
//

#include <Core/World/VisualChunk.h>
#include <Core/Engine.h>

#include <Render/Render.h>
#include <Types/Geometry/DebugWireframeMesh.h>
#include <Utils/World/Region.h>
#include <Render/RenderScene.h>

namespace Framework::Core::World {
    VisualChunk::VisualChunk(SRChunkAllocArgs)
        : Helper::World::Chunk(SRChunkAllocVArgs)
    { }

    VisualChunk::~VisualChunk() {
        SRAssert(!m_stayMesh);
        SRAssert(!m_loadMesh);
    }

    void VisualChunk::Update(float_t dt) {
        Chunk::Update(dt);
    }

    void VisualChunk::UpdateFacesPos() {
        if (m_stayMesh) {
            m_stayMesh->OnMove(GetWorldPosition(SR_MATH_NS::AXIS_XYZ));
        }
    }

    void VisualChunk::UpdateLoadPos() {
        if (m_loadMesh) {
            m_loadMesh->OnMove(GetWorldPosition(SR_MATH_NS::AXIS_XZ));
        }
    }

    void VisualChunk::SetFacesVisible(bool value) {
        auto&& renderScene = GetScene().Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) -> RenderScenePtr {
            return ptr->GetDataStorage().GetValue<RenderScenePtr>();
        }, RenderScenePtr());

        if (value && !m_stayMesh) {
            if (auto &&meshes = SR_GTYPES_NS::Mesh::Load("Engine/Models/cubeWireframe.obj", SR_GTYPES_NS::MeshType::Wireframe); !meshes.empty()) {
                m_stayMesh = dynamic_cast<SR_GTYPES_NS::DebugWireframeMesh *>(meshes.at(0));
            }
            else
                return;

            UpdateFacesPos();

            m_stayMesh->AddUsePoint();
            m_stayMesh->SetMaterial(SR_GTYPES_NS::Material::Load("Engine/Materials/Colors/green_wireframe.mat"));
            m_stayMesh->OnScaled(SR_MATH_NS::FVector3(m_size.x, m_size.y, m_size.x) / 2);

            renderScene.Do([this](SR_GRAPH_NS::RenderScene* ptr) {
                ptr->Register(m_stayMesh);
            });
        }

        if (!value && m_stayMesh) {
            m_stayMesh->RemoveUsePoint();
            m_stayMesh = nullptr;
        }
    }

    void VisualChunk::SetLoadVisible(bool value) {
        auto&& renderScene = GetScene().Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) -> RenderScenePtr {
            return ptr->GetDataStorage().GetValue<RenderScenePtr>();
        }, RenderScenePtr());

        if (value && !m_loadMesh && m_position.y == 1 && m_regionPosition.y == 1) {
            if (auto &&meshes = SR_GTYPES_NS::Mesh::Load("Engine/Models/planeWireframe.obj", SR_GTYPES_NS::MeshType::Wireframe); !meshes.empty()) {
                m_loadMesh = dynamic_cast<SR_GTYPES_NS::DebugWireframeMesh *>(meshes.at(0));
            }
            else
                return;

            UpdateLoadPos();

            m_loadMesh->AddUsePoint();
            m_loadMesh->SetMaterial(SR_GTYPES_NS::Material::Load("Engine/Materials/Colors/yellow_wireframe.mat"));
            m_loadMesh->OnScaled(SR_MATH_NS::FVector3(m_size.x, m_size.y, m_size.x) / 2);

            renderScene.Do([this](SR_GRAPH_NS::RenderScene* ptr) {
                ptr->Register(m_loadMesh);
            });
        }

        if (!value && m_loadMesh) {
            m_loadMesh->RemoveUsePoint();
            m_loadMesh = nullptr;
        }
    }

    void VisualChunk::OnExit() {
        SetFacesVisible(false);
        Chunk::OnExit();
    }

    void VisualChunk::OnEnter() {
        SetFacesVisible(true);
        Chunk::OnEnter();
    }

    bool Framework::Core::World::VisualChunk::Unload() {
        SetFacesVisible(false);
        SetLoadVisible(false);
        return Chunk::Unload();
    }

    bool Framework::Core::World::VisualChunk::Load(SR_HTYPES_NS::Marshal &&marshal) {
        SetLoadVisible(true);
        return Chunk::Load(std::move(marshal));
    }

    bool Framework::Core::World::VisualChunk::ApplyOffset() {
        UpdateLoadPos();
        UpdateFacesPos();
        return Chunk::ApplyOffset();
    }

    void Framework::Core::World::VisualChunk::Reload() {
        Chunk::Reload();
    }
}