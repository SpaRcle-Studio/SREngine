//
// Created by Monika on 12.08.2023.
//

#include <Core/GUI/RenderTechniqueEditor.h>
#include <Graphics/GUI/NodeCreation.h>

namespace SR_CORE_GUI_NS {
    RenderTechniqueEditor::RenderTechniqueEditor()
        : Super("Render Technique Editor")
    { }

    void RenderTechniqueEditor::OnOpen() {
        ax::NodeEditor::Config config;

        static const SR_UTILS_NS::Path settings = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/RenderTechniqueEditor.json");
        config.SettingsFile = settings.c_str();

        config.UserPointer = this;

        config.LoadNodeSettings = [](ax::NodeEditor::NodeId nodeId, char* data, void* userPointer) -> size_t {
            return 0;
        };

        config.SaveNodeSettings = [](ax::NodeEditor::NodeId nodeId, const char* data, size_t size, ax::NodeEditor::SaveReasonFlags reason, void* userPointer) -> bool {
            return true;
        };

        m_editor = ax::NodeEditor::CreateEditor(&config);

        Super::OnOpen();
    }

    void RenderTechniqueEditor::InitCreationPopup() {
        auto&& passesNodesMenu = m_creationPopup->AddMenu("Passes");

        passesNodesMenu.AddMenu("Cascaded Shadow Map Pass").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(SR_GRAPH_GUI_NS::CreateNode(context.popupPos, SR_SRLM_NS::NODE_CASCADED_SHADOW_MAP_PASS));
        });

        passesNodesMenu.AddMenu("Start Pass").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(SR_GRAPH_GUI_NS::CreateNode(context.popupPos, SR_SRLM_NS::NODE_START_PASS));
        });

        passesNodesMenu.AddMenu("End Pass").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(SR_GRAPH_GUI_NS::CreateNode(context.popupPos, SR_SRLM_NS::NODE_END_PASS));
        });

        Super::InitCreationPopup();
    }
}