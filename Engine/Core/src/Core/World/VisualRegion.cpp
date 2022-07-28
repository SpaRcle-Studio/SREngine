//
// Created by Monika on 29.11.2021.
//

#include <Core/Engine.h>
#include <Core/World/VisualRegion.h>
#include <Types/Geometry/DebugWireframeMesh.h>
#include <Render/RenderScene.h>

namespace Framework::Core::World {
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
            if (auto&& meshes = Mesh::Load("Engine/Models/planeWireframe.obj", MeshType::Wireframe); !meshes.empty()) {
                m_mesh = dynamic_cast<DebugWireframeMesh *>(meshes.at(0));
            }
            else
                return;

            const auto size = SR_MATH_NS::FVector2(m_width) * m_chunkSize.x;

            UpdateFacesPos();

            m_mesh->AddUsePoint();
            m_mesh->SetMaterial(Material::Load("Engine/Materials/Colors/red_wireframe.mat"));
            m_mesh->OnScaled(SR_MATH_NS::FVector3(size.x / 2, 1, size.y / 2));

            renderScene.Do([this](SR_GRAPH_NS::RenderScene* ptr) {
                ptr->Register(m_mesh);
            });
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
            const Helper::World::Offset offset = m_observer->m_offset;

            auto fPos = Helper::World::AddOffset(m_position.Cast<SR_MATH_NS::Unit>(), offset.m_region);
            fPos = fPos * size + (size / 2);
            fPos = fPos.DeSingular(size);

            fPos += offset.m_chunk * m_chunkSize.x;

            m_mesh->OnMove(SR_MATH_NS::FVector3(
                    fPos.x,
                    static_cast<SR_MATH_NS::Unit>(0.01),
                    fPos.z
            ));
        }
    }

    void VisualRegion::ApplyOffset() {
        UpdateFacesPos();
        Region::ApplyOffset();
    }
}