//
// Created by Monika on 29.11.2021.
//

#include <Core/Engine.h>
#include <Core/World/VisualRegion.h>

#include <Graphics/Types/Geometry/DebugWireframeMesh.h>
#include <Graphics/Render/RenderScene.h>

namespace SR_CORE_NS {
    void VisualRegion::OnEnter() {
        Region::OnEnter();
    }

    void VisualRegion::OnExit() {
        Region::OnExit();
    }

    void VisualRegion::SetVisible(bool value) {
        using namespace Graphics::Types;
        using namespace Graphics;

        auto&& renderScene = GetScene().Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) -> RenderScenePtr {
            return ptr->GetDataStorage().GetValue<RenderScenePtr>();
        }, RenderScenePtr());

        if (value && !m_mesh && m_position.y == 1) {
            if (auto&& pMesh = SR_GTYPES_NS::Mesh::Load("Engine/Models/planeWireframe.obj", SR_GTYPES_NS::MeshType::Wireframe, 0)) {
                m_mesh = dynamic_cast<SR_GTYPES_NS::DebugWireframeMesh *>(pMesh);
            }
            else
                return;

            UpdateFacesPos();

            m_mesh->AddUsePoint();
            m_mesh->SetMaterial(Material::Load("Engine/Materials/Colors/red_wireframe.mat"));

            //renderScene.Do([this](SR_GRAPH_NS::RenderScene* ptr) {
            //    ptr->Register(m_mesh);
            //});
        }

        if (!value && m_mesh) {
            m_mesh->RemoveUsePoint();
            m_mesh = nullptr;
        }
    }

    bool VisualRegion::Unload(bool force) {
        SetVisible(false);
        return Region::Unload(force);
    }

    bool VisualRegion::Load() {
        SetVisible(true);
        return Region::Load();
    }

    void VisualRegion::UpdateFacesPos() {
        if (m_mesh) {
            const auto size = SR_MATH_NS::FVector3(m_width) * m_chunkSize.x;
            const SR_WORLD_NS::Offset offset = m_observer->m_offset;

            auto fPos = SR_WORLD_NS::AddOffset(m_position.Cast<SR_MATH_NS::Unit>(), offset.m_region);
            fPos = fPos * size + (size / 2);
            fPos = fPos.DeSingular(size);

            fPos += offset.m_chunk * m_chunkSize.x;

            auto&& matrix = SR_MATH_NS::Matrix4x4(
                    SR_MATH_NS::FVector3(fPos.x, static_cast<SR_MATH_NS::Unit>(0.01), fPos.z),
                    SR_MATH_NS::Quaternion::Identity(),
                    SR_MATH_NS::FVector3(size.x / 2.f, 1.f, size.y / 2.f)
            );

            m_mesh->SetMatrix(matrix);
        }
    }

    void VisualRegion::ApplyOffset() {
        UpdateFacesPos();
        Region::ApplyOffset();
    }
}