//
// Created by Monika on 14.02.2022.
//

#include <Engine/GUI/WorldEdit.h>
#include <Utils/World/Scene.h>
#include <Utils/World/SceneCubeChunkLogic.h>

namespace SR_CORE_GUI_NS {
    WorldEdit::WorldEdit()
        : Super("World edit")
    { }

    void WorldEdit::SetScene(const SR_WORLD_NS::Scene::Ptr& pScene) {
        m_scene = pScene;
    }

    void WorldEdit::Draw() {
        /*if (m_scene.TryRecursiveLockIfValid()) {
            auto&& pLogic = m_scene->GetLogicBase().DynamicCast<SR_WORLD_NS::SceneCubeChunkLogic>();

            if (!pLogic) {
                m_scene.Unlock();
                return;
            }

            SR_GRAPH_GUI_NS::Immediate::Separator();
            TextCenter("Settings");

            auto&& dataStorage = m_scene->GetDataStorage();

            auto&& renderTechniquePath = dataStorage.GetValueDef<SR_UTILS_NS::Path>("RenderTechnique", "");
            if (SR_GRAPH_GUI_NS::Immediate::InputText("Render Technique", renderTechniquePath.ToStringPtr())) {
                dataStorage.SetValue("RenderTechnique", renderTechniquePath);
            }

            auto&& editorRenderTechniquePath = dataStorage.GetValueDef<SR_UTILS_NS::Path>("EditorRenderTechnique", "");
            if (SR_GRAPH_GUI_NS::Immediate::InputText("Editor Render Technique", editorRenderTechniquePath.ToStringPtr())) {
                dataStorage.SetValue("EditorRenderTechnique", editorRenderTechniquePath);
            }*/

            /*if (const auto&& observer = pLogic->GetObserver()) {
                const auto offset = observer->m_offset;

                SR_GRAPH_GUI_NS::Immediate::Separator();
                TextCenter("Current");

                SR_GRAPH_GUI_NS::Immediate::InputInt3("Chunk", &observer->m_chunk[0], ImGuiInputTextFlags_ReadOnly);
                SR_GRAPH_GUI_NS::Immediate::InputInt3("Region", &observer->m_region[0], ImGuiInputTextFlags_ReadOnly);

                SR_GRAPH_GUI_NS::Immediate::Separator();
                TextCenter("Offset");

                auto chunkOffset = offset.m_chunk;
                if (SR_GRAPH_GUI_NS::Immediate::InputInt3("Chunk offset", &chunkOffset[0], ImGuiInputTextFlags_EnterReturnsTrue)) {
                    pLogic->SetWorldOffset(SR_WORLD_NS::Offset(offset.m_region, chunkOffset));
                }

                auto regionOffset = offset.m_region;
                if (SR_GRAPH_GUI_NS::Immediate::InputInt3("Region offset", &regionOffset[0], ImGuiInputTextFlags_EnterReturnsTrue)) {
                    pLogic->SetWorldOffset(SR_WORLD_NS::Offset(regionOffset, offset.m_chunk));
                }

                auto scope = observer->GetScope();
                if (SR_GRAPH_GUI_NS::Immediate::InputInt("Scope", &scope)) {
                    observer->SetScope(SR_CLAMP(scope, 0, 32));
                }

                if (SR_GRAPH_GUI_NS::Immediate::Button("Reload chunks")) {
                    pLogic->ReloadChunks();
                }
            }*/

        //    m_scene.Unlock();
        //}
    }
}