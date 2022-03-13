//
// Created by Monika on 29.11.2021.
//

#include <Types/Geometry/DebugWireframeMesh.h>
#include <Engine.h>
#include "World/VisualRegion.h"

void Framework::Core::World::VisualRegion::OnEnter() {
    SetVisible(true);
    Region::OnEnter();
}

void Framework::Core::World::VisualRegion::OnExit() {
    SetVisible(false);
    Region::OnExit();
}

void Framework::Core::World::VisualRegion::SetVisible(bool value) {
    using namespace Graphics::Types;
    using namespace Graphics;

    if (value && !m_mesh) {
        m_mesh = dynamic_cast<DebugWireframeMesh *>(Mesh::Load("engine/planeWireframe.obj", MeshType::Wireframe)[0]);

        auto render = Engine::Instance().GetRender();

        const auto size = Math::FVector2(m_width) * m_chunkSize.x;

        UpdateFacesPos();

        m_mesh->SetShader(render->FindShader(static_cast<uint32_t>(Shader::StandardID::DebugWireframe)));
        m_mesh->SetMaterial(Material::Load("Engine/Colors/red"));
        render->RegisterMesh(m_mesh);

        m_mesh->OnScaled(Math::FVector3(size.x / 2, 1, size.y / 2));
    }

    if (!value && m_mesh) {
        Engine::Instance().GetRender()->RemoveMesh(m_mesh);
        m_mesh->Destroy();
        m_mesh = nullptr;
    }
}

bool Framework::Core::World::VisualRegion::Unload() {
    SetVisible(false);
    return Region::Unload();
}

void Framework::Core::World::VisualRegion::UpdateFacesPos() {
    if (m_mesh) {
        const auto size = Math::FVector2(m_width) * m_chunkSize.x;
        const Helper::World::Offset offset = m_observer->m_offset;

        auto fPos = Helper::World::AddOffset(m_position.Cast<Math::Unit>(), offset.m_region);
        fPos = fPos * size + (size / 2);
        fPos = fPos.DeSingular(size);

        fPos += offset.m_chunk.XZ() * m_chunkSize.x;

        m_mesh->OnMove(Math::FVector3(
                fPos.x,
                static_cast<Math::Unit>(0.01) + offset.m_chunk.y * m_chunkSize.y,
                fPos.y
        ));
    }
}

void Framework::Core::World::VisualRegion::ApplyOffset() {
    UpdateFacesPos();
    Region::ApplyOffset();
}
