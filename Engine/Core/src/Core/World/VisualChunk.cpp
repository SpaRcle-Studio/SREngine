//
// Created by Monika on 17.11.2021.
//

#include <Core/World/VisualChunk.h>
#include <Core/Engine.h>

#include <Render/Render.h>
#include <Types/Geometry/DebugWireframeMesh.h>
#include <Utils/World/Region.h>

using namespace Framework::Graphics::Types;
using namespace Framework::Graphics;

Framework::Core::World::VisualChunk::VisualChunk(SRChunkAllocArgs)
    : Helper::World::Chunk(SRChunkAllocVArgs)
{ }

Framework::Core::World::VisualChunk::~VisualChunk() {
    SRAssert(!m_meshes[0]);
    SRAssert(!m_meshes[1]);
}

void Framework::Core::World::VisualChunk::Update(float_t dt) {
    Chunk::Update(dt);
}

void Framework::Core::World::VisualChunk::UpdateFacesPos() {
    if (auto&& mesh = m_meshes[0]) {
        mesh->OnMove(GetWorldPosition(SR_MATH_NS::AXIS_XYZ));
    }
}
void Framework::Core::World::VisualChunk::UpdateLoadPos() {
    if (auto&& mesh = m_meshes[1]) {
        mesh->OnMove(GetWorldPosition(SR_MATH_NS::AXIS_XZ));
    }
}

void Framework::Core::World::VisualChunk::SetFacesVisible(bool value) {
    auto&& mesh = m_meshes[0];
    if (value && !mesh) {
        if (auto&& meshes = Mesh::Load("engine/cubeWireframe.obj", MeshType::Wireframe); !meshes.empty()) {
            mesh = dynamic_cast<DebugWireframeMesh *>(meshes.at(0));
        }
        else
            return;

        auto render = Engine::Instance().GetRender();

        UpdateFacesPos();

        mesh->SetMaterial(Material::Load("Engine/Colors/green.mat"));
        render->RegisterMesh(mesh);
        mesh->OnScaled(SR_MATH_NS::FVector3(m_size.x, m_size.y, m_size.x) / 2);
    }

    if (!value && mesh) {
        Engine::Instance().GetRender()->RemoveMesh(mesh);
        mesh->Destroy();
        mesh = nullptr;
    }
}
void Framework::Core::World::VisualChunk::SetLoadVisible(bool value) {
    auto&& mesh = m_meshes[1];
    if (value && !mesh && m_position.y == 1 && m_regionPosition.y == 1) {
        if (auto&& meshes = Mesh::Load("engine/planeWireframe.obj", MeshType::Wireframe); !meshes.empty()) {
            mesh = dynamic_cast<DebugWireframeMesh *>(meshes.at(0));
        }
        else
            return;

        auto render = Engine::Instance().GetRender();

        UpdateLoadPos();

        mesh->SetMaterial(Material::Load("Engine/Colors/yellow.mat"));
        render->RegisterMesh(mesh);
        mesh->OnScaled(SR_MATH_NS::FVector3(m_size.x, m_size.y, m_size.x) / 2);
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

bool Framework::Core::World::VisualChunk::Unload() {
    SetFacesVisible(false);
    SetLoadVisible(false);
    return Chunk::Unload();
}

bool Framework::Core::World::VisualChunk::Load(SR_HTYPES_NS::Marshal&& marshal) {
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



