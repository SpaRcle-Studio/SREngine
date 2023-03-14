//
// Created by Monika on 14.02.2022.
//

#include <Core/GUI/WorldEdit.h>
#include <Utils/World/Scene.h>
#include <Utils/World/SceneCubeChunkLogic.h>

namespace Framework::Core::GUI {
    WorldEdit::WorldEdit()
        : Graphics::GUI::Widget("World edit")
    { }

    void WorldEdit::SetScene(const SR_WORLD_NS::Scene::Ptr &scene) {
        m_scene.Replace(scene);
    }

    void WorldEdit::Draw() {
        if (m_scene.TryRecursiveLockIfValid()) {
            auto&& pLogic = m_scene->GetLogicBase().DynamicCast<SR_WORLD_NS::SceneCubeChunkLogic*>();

            if (!pLogic) {
                m_scene.Unlock();
                return;
            }

            const auto&& observer = pLogic->GetObserver();
            const auto offset = observer->m_offset;

            ImGui::Separator();
            TextCenter("Current");

            ImGui::InputInt3("Chunk", &observer->m_chunk[0], ImGuiInputTextFlags_ReadOnly);
            ImGui::InputInt3("Region", &observer->m_region[0], ImGuiInputTextFlags_ReadOnly);

            ImGui::Separator();
            TextCenter("Offset");

            auto chunkOffset = offset.m_chunk;
            if (ImGui::InputInt3("Chunk offset", &chunkOffset[0], ImGuiInputTextFlags_EnterReturnsTrue))
                pLogic->SetWorldOffset(SR_WORLD_NS::Offset(offset.m_region, chunkOffset));

            auto regionOffset = offset.m_region;
            if (ImGui::InputInt3("Region offset", &regionOffset[0], ImGuiInputTextFlags_EnterReturnsTrue))
                pLogic->SetWorldOffset(SR_WORLD_NS::Offset(regionOffset, offset.m_chunk));

            auto scope = observer->GetScope();
            if (ImGui::InputInt("Scope", &scope))
                observer->SetScope(SR_CLAMP(scope, 32, 0));

            if (ImGui::Button("Reload chunks")) {
                pLogic->ReloadChunks();
            }

            if (auto&& chunk = pLogic->GetCurrentChunk()) {
                ImGui::Separator();
                int32_t size = -1;// static_cast<int32_t>(chunk->GetContainerSize());
                ImGui::InputInt("Container size", &size, 0, 0, ImGuiInputTextFlags_ReadOnly);
            }

            m_scene.Unlock();
        }
    }
}