//
// Created by Monika on 29.11.2021.
//

#include <Types/Geometry/DebugWireframeMesh.h>
#include <Engine.h>
#include "World/VisualRegion.h"

void Framework::Core::World::VisualRegion::OnEnter() {
    Region::OnEnter();
}

void Framework::Core::World::VisualRegion::OnExit() {
    Region::OnExit();
}

void Framework::Core::World::VisualRegion::SetVisible(bool value) {
    using namespace Graphics::Types;
    using namespace Graphics;

    if (value && !m_mesh && m_position.y == 1) {
        if (auto&& meshes = Mesh::Load("engine/planeWireframe.obj", MeshType::Wireframe); !meshes.empty()) {
            m_mesh = dynamic_cast<DebugWireframeMesh *>(meshes.at(0));
        }
        else
            return;

        auto render = Engine::Instance().GetRender();

        const auto size = SR_MATH_NS::FVector2(m_width) * m_chunkSize.x;

        UpdateFacesPos();

        m_mesh->SetMaterial(Material::Load("Engine/Colors/red"));
        render->RegisterMesh(m_mesh);

        m_mesh->OnScaled(SR_MATH_NS::FVector3(size.x / 2, 1, size.y / 2));
    }

    if (!value && m_mesh) {
        Engine::Instance().GetRender()->RemoveMesh(m_mesh);
        m_mesh->Destroy();
        m_mesh = nullptr;
    }
}

bool Framework::Core::World::VisualRegion::Unload(bool force) {
    SetVisible(false);
    return Region::Unload(force);
}

bool Framework::Core::World::VisualRegion::Load() {
    SetVisible(true);
    return Region::Load();
}

void Framework::Core::World::VisualRegion::UpdateFacesPos() {
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

void Framework::Core::World::VisualRegion::ApplyOffset() {
    UpdateFacesPos();
    Region::ApplyOffset();
}
