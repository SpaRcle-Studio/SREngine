//
// Created by Monika on 17.11.2021.
//

#include <World/VisualChunk.h>
#include <Render/Render.h>
#include <Engine.h>
#include <Types/Geometry/DebugWireframeMesh.h>
#include <World/Region.h>

using namespace Framework::Graphics::Types;
using namespace Framework::Graphics;

void Framework::Core::World::VisualChunk::Update(float_t dt) {
    Chunk::Update(dt);
}

void Framework::Core::World::VisualChunk::UpdateFacesPos() {
    if (auto&& mesh = m_meshes[0]) {
        auto fPos = Math::FVector3::XZ(m_region->GetWorldPosition());
        const Helper::World::Offset offset = m_observer->m_offset;

        fPos = Helper::World::AddOffset(fPos + (m_position - Math::FVector3(1, 0, 1)),
                                        offset.m_chunk.Cast<Math::Unit>());

        fPos = Math::FVector3(
                fPos.x * m_size.x + (Math::Unit) m_size.x / 2,
                fPos.y * m_size.y + (Math::Unit) m_size.y / 2,
                fPos.z * m_size.x + (Math::Unit) m_size.x / 2);

        fPos = fPos.DeSingular(Math::FVector3(m_size.x, m_size.y, m_size.x));

        mesh->OnMove(fPos);
    }
}
void Framework::Core::World::VisualChunk::UpdateLoadPos() {
    if (auto&& mesh = m_meshes[1]) {
        auto fPos = Math::FVector3::XZ(m_region->GetWorldPosition());
        const Helper::World::Offset offset = m_observer->m_offset;

        fPos = Helper::World::AddOffset(fPos + (m_position - Math::FVector3(1, 0, 1)),
                                        offset.m_chunk.Cast<Math::Unit>());

        fPos = Math::FVector3(
                fPos.x * m_size.x + (Math::Unit) m_size.x / 2,
                fPos.y * m_size.y,
                fPos.z * m_size.x + (Math::Unit) m_size.x / 2);

        fPos = fPos.DeSingular(Math::FVector3(m_size.x, m_size.y, m_size.x));
        mesh->OnMove(fPos);
    }
}

void Framework::Core::World::VisualChunk::SetFacesVisible(bool value) {
    auto&& mesh = m_meshes[0];
    if (value && !mesh) {
        mesh = dynamic_cast<DebugWireframeMesh *>(Mesh::Load("engine/cubeWireframe.obj", MeshType::Wireframe)[0]);

        auto render = Engine::Instance().GetRender();

        UpdateFacesPos();

        mesh->SetShader(render->FindShader(static_cast<uint32_t>(Shader::StandardID::DebugWireframe)));
        mesh->GetMaterial()->SetColor(0.0, 1.0, 0.0);
        render->RegisterMesh(mesh);
        mesh->OnScaled(Math::FVector3(m_size.x, m_size.y, m_size.x) / 2);
    }

    if (!value && mesh) {
        Engine::Instance().GetRender()->RemoveMesh(mesh);
        mesh->Destroy();
        mesh = nullptr;
    }
}
void Framework::Core::World::VisualChunk::SetLoadVisible(bool value) {
    auto&& mesh = m_meshes[1];
    if (value && !mesh && m_position.y == 1) {
        mesh = dynamic_cast<DebugWireframeMesh *>(Mesh::Load("engine/planeWireframe.obj", MeshType::Wireframe)[0]);

        auto render = Engine::Instance().GetRender();

        UpdateLoadPos();

        mesh->SetShader(render->FindShader(static_cast<uint32_t>(Shader::StandardID::DebugWireframe)));
        mesh->GetMaterial()->SetColor(1.0, 1.0, 0.0);
        render->RegisterMesh(mesh);
        mesh->OnScaled(Math::FVector3(m_size.x, m_size.y, m_size.x) / 2);
    }

    if (!value && mesh) {
        Engine::Instance().GetRender()->RemoveMesh(mesh);
        mesh->Destroy();
        mesh = nullptr;
    }
}

void Framework::Core::World::VisualChunk::OnExit() {
    SetFacesVisible(false);
    Chunk::OnExit();
}

void Framework::Core::World::VisualChunk::OnEnter() {
    SetFacesVisible(true);
    Chunk::OnEnter();
}

Framework::Core::World::VisualChunk::VisualChunk(SRChunkAllocArgs)
    : Helper::World::Chunk(SRChunkAllocVArgs) { }

bool Framework::Core::World::VisualChunk::Unload() {
    SetFacesVisible(false);
    SetLoadVisible(false);
    return Chunk::Unload();
}

bool Framework::Core::World::VisualChunk::Load() {
    SetLoadVisible(true);
    return Chunk::Load();
}

bool Framework::Core::World::VisualChunk::ApplyOffset() {
    UpdateLoadPos();
    UpdateFacesPos();
    return Chunk::ApplyOffset();
}




