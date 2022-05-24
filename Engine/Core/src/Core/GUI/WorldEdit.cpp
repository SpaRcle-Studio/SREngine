//
// Created by Monika on 14.02.2022.
//

#include <Core/GUI/WorldEdit.h>

namespace Framework::Core::GUI {
    WorldEdit::WorldEdit()
        : Graphics::GUI::Widget("World edit")
    { }

    void WorldEdit::SetScene(const SR_WORLD_NS::Scene::Ptr &scene) {
        m_scene.Replace(scene);
    }

    void WorldEdit::Draw() {
        if (m_scene.TryLockIfValid()) {
            const auto&& observer = m_scene->GetObserver();
            const auto offset = observer->m_offset;

            ImGui::Separator();
            TextCenter("Current");

            ImGui::InputFloat3("Chunk", &observer->m_chunk.ToGLM()[0], "%.3f", ImGuiInputTextFlags_ReadOnly);
            ImGui::InputFloat3("Region", &observer->m_region.ToGLM()[0], "%.2f", ImGuiInputTextFlags_ReadOnly);

            ImGui::Separator();
            TextCenter("Offset");

            auto chunkOffset = offset.m_chunk.ToGLM();
            if (ImGui::InputFloat3("Chunk offset", &chunkOffset[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
                m_scene->SetWorldOffset(SR_WORLD_NS::Offset(offset.m_region, chunkOffset));

            auto regionOffset = offset.m_region.ToGLM();
            if (ImGui::InputFloat3("Region offset", &regionOffset[0], "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
                m_scene->SetWorldOffset(SR_WORLD_NS::Offset(regionOffset, offset.m_chunk));

            auto scope = observer->GetScope();
            if (ImGui::InputInt("Scope", &scope))
                observer->SetScope(SR_CLAMP(scope, 32, 0));

            if (ImGui::Button("Reload chunks")) {
                m_scene->ReloadChunks();
            }

            if (auto&& chunk = m_scene->GetCurrentChunk()) {
                ImGui::Separator();
                int32_t size = -1;// static_cast<int32_t>(chunk->GetContainerSize());
                ImGui::InputInt("Container size", &size, 0, 0, ImGuiInputTextFlags_ReadOnly);
            }

            m_scene.Unlock();
        }
    }
}