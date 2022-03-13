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
        mesh->OnMove(GetWorldPosition(Math::AXIS_XYZ));
    }
}
void Framework::Core::World::VisualChunk::UpdateLoadPos() {
    if (auto&& mesh = m_meshes[1]) {
        mesh->OnMove(GetWorldPosition(Math::AXIS_XZ));
    }
}

void Framework::Core::World::VisualChunk::SetFacesVisible(bool value) {
    auto&& mesh = m_meshes[0];
    if (value && !mesh) {
        mesh = dynamic_cast<DebugWireframeMesh *>(Mesh::Load("engine/cubeWireframe.obj", MeshType::Wireframe)[0]);

        auto render = Engine::Instance().GetRender();

        UpdateFacesPos();

        mesh->SetShader(render->FindShader(static_cast<uint32_t>(Shader::StandardID::DebugWireframe)));
        mesh->SetMaterial(Material::Load("Engine/Colors/green"));
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
        mesh->SetMaterial(Material::Load("Engine/Colors/yellow"));
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

bool Framework::Core::World::VisualChunk::Load(const MarshalDecodeNode& node) {
    SetLoadVisible(true);
    return Chunk::Load(node);
}

bool Framework::Core::World::VisualChunk::ApplyOffset() {
    UpdateLoadPos();
    UpdateFacesPos();
    return Chunk::ApplyOffset();
}

void Framework::Core::World::VisualChunk::Reload() {


    Chunk::Reload();
}




