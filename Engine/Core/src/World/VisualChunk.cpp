//
// Created by Monika on 17.11.2021.
//

#include <World/VisualChunk.h>
#include <Render/Render.h>
#include <Engine.h>
#include <Types/Geometry/DebugWireframeMesh.h>
#include <Types/Mesh.h>
#include <Render/Shader.h>
#include <Math/Vector2.h>
#include <World/Region.h>
#include <World/Observer.h>

void Framework::Core::World::VisualChunk::Update(float_t dt) {
    Chunk::Update(dt);
}

void Framework::Core::World::VisualChunk::SetVisible(bool value) {
    using namespace Graphics::Types;
    using namespace Graphics;

    if (value && !m_mesh) {
        m_mesh = dynamic_cast<DebugWireframeMesh *>(Mesh::Load("engine/cubeWireframe.obj", MeshType::Wireframe)[0]);

        auto render = Engine::Instance().GetRender();

        auto fPos = Math::FVector3::XZ(m_region->GetWorldPosition()) + m_position.Cast<Math::Unit>();

        fPos = Helper::World::AddOffset(fPos, m_offset.m_chunk.Cast<Math::Unit>());

        fPos = Math::FVector3(
                fPos.x * m_size.x + (Math::Unit)m_size.x / 2,
                fPos.y * m_size.y + (Math::Unit)m_size.y / 2,
                fPos.z * m_size.x + (Math::Unit)m_size.x / 2);

        fPos = fPos.DeSingular(Math::FVector3(m_size.x, m_size.y, m_size.x));

        m_mesh->SetShader(render->FindShader(static_cast<uint32_t>(Shader::StandardID::DebugWireframe)));
        m_mesh->GetMaterial()->SetColor(0.0, 1.0, 0.0);
        render->RegisterMesh(m_mesh);
        m_mesh->OnMove(fPos);
        m_mesh->OnScaled(Math::FVector3(m_size.x, m_size.y, m_size.x) / 2);
    }

    if (!value && m_mesh) {
        Engine::Instance().GetRender()->RemoveMesh(m_mesh);
        m_mesh->Destroy();
        m_mesh = nullptr;
    }
}

void Framework::Core::World::VisualChunk::OnExit() {
    SetVisible(false);
    Chunk::OnExit();
}

void Framework::Core::World::VisualChunk::OnEnter() {
    SetVisible(true);
    Chunk::OnEnter();
}

Framework::Core::World::VisualChunk::VisualChunk(SRChunkAllocArgs)
    : Helper::World::Chunk(SRChunkAllocVArgs) { }

bool Framework::Core::World::VisualChunk::Unload() {
    SetVisible(false);
    return Chunk::Unload();
}
