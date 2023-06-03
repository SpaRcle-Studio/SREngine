//
// Created by Monika on 17.11.2021.
//

#include <Utils/World/Region.h>

#include <Graphics/Types/Geometry/DebugWireframeMesh.h>
#include <Graphics/Render/RenderScene.h>

#include <Core/World/VisualChunk.h>
#include <Core/Engine.h>

namespace SR_CORE_NS {
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
            auto&& matrix = SR_MATH_NS::Matrix4x4(
                    GetWorldPosition(SR_MATH_NS::AXIS_XYZ),
                    SR_MATH_NS::Quaternion::Identity(),
                    SR_MATH_NS::FVector3(m_size.x, m_size.y, m_size.x) / 2
            );

            m_stayMesh->SetMatrix(matrix);
        }
    }

    void VisualChunk::UpdateLoadPos() {
        if (m_loadMesh) {
            auto&& matrix = SR_MATH_NS::Matrix4x4(
                    GetWorldPosition(SR_MATH_NS::AXIS_XZ),
                    SR_MATH_NS::Quaternion::Identity(),
                    SR_MATH_NS::FVector3(m_size.x, m_size.y, m_size.x) / 2
            );

            m_loadMesh->SetMatrix(matrix);
        }
    }

    void VisualChunk::SetFacesVisible(bool value) {
        auto&& renderScene = GetScene().Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) -> RenderScenePtr {
            return ptr->GetDataStorage().GetValue<RenderScenePtr>();
        }, RenderScenePtr());

        if (value && !m_stayMesh) {
            //if (auto&& pMesh = SR_GTYPES_NS::Mesh::Load("Engine/Models/cubeWireframe.obj", SR_GTYPES_NS::MeshType::Wireframe, 0)) {
            //    m_stayMesh = dynamic_cast<SR_GTYPES_NS::DebugWireframeMesh *>(pMesh);
            //}
            //else
            //    return;

            //UpdateFacesPos();

           //m_stayMesh->AddUsePoint();
           //m_stayMesh->SetMaterial(SR_GTYPES_NS::Material::Load("Engine/Materials/Colors/green_wireframe.mat"));

           //renderScene.Do([this](SR_GRAPH_NS::RenderScene* ptr) {
           //    ptr->Register(m_stayMesh);
           //});
        }

        //if (!value && m_stayMesh) {
        //    m_stayMesh->RemoveUsePoint();
        //    m_stayMesh = nullptr;
        //}
    }

    void VisualChunk::SetLoadVisible(bool value) {
        auto&& renderScene = GetScene().Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) -> RenderScenePtr {
            return ptr->GetDataStorage().GetValue<RenderScenePtr>();
        }, RenderScenePtr());

        if (value && !m_loadMesh && m_position.y == 1 && m_regionPosition.y == 1) {
            //if (auto&& pMesh = SR_GTYPES_NS::Mesh::Load("Engine/Models/planeWireframe.obj", SR_GTYPES_NS::MeshType::Wireframe, 0)) {
            //    m_loadMesh = dynamic_cast<SR_GTYPES_NS::DebugWireframeMesh *>(pMesh);
            //}
            //else
            //    return;

            //UpdateLoadPos();
//
            //m_loadMesh->AddUsePoint();
            //m_loadMesh->SetMaterial(SR_GTYPES_NS::Material::Load("Engine/Materials/Colors/yellow_wireframe.mat"));

            //renderScene.Do([this](SR_GRAPH_NS::RenderScene* ptr) {
            //    ptr->Register(m_loadMesh);
            //});
        }

        //if (!value && m_loadMesh) {
        //    m_loadMesh->RemoveUsePoint();
        //    m_loadMesh = nullptr;
        //}
    }

    void VisualChunk::OnExit() {
        SetFacesVisible(false);
        Chunk::OnExit();
    }

    void VisualChunk::OnEnter() {
        SetFacesVisible(true);
        Chunk::OnEnter();
    }

    bool VisualChunk::Unload() {
        SetFacesVisible(false);
        SetLoadVisible(false);
        return Chunk::Unload();
    }

    bool VisualChunk::ApplyOffset() {
        UpdateLoadPos();
        UpdateFacesPos();
        return Chunk::ApplyOffset();
    }

    void VisualChunk::Reload() {
        Chunk::Reload();
    }
}