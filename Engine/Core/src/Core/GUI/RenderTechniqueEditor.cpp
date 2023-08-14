//
// Created by Monika on 12.08.2023.
//

#include <Core/GUI/RenderTechniqueEditor.h>

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
        auto&& commonNodesMenu = m_creationPopup->AddMenu("Common");

        commonNodesMenu.AddMenu("Condition").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(new SR_GRAPH_GUI_NS::Node("Condition", SR_GRAPH_GUI_NS::NodeType::Simple))
                .AddInput("", SR_GRAPH_GUI_NS::PinType::Flow)
                .AddInput("", SR_GRAPH_GUI_NS::PinType::Bool)
                .AddOutput("True", SR_GRAPH_GUI_NS::PinType::Flow)
                .AddOutput("False", SR_GRAPH_GUI_NS::PinType::Flow)
                .SetPosition(context.popupPos)
            ;
        });

        commonNodesMenu.AddMenu("And").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(new SR_GRAPH_GUI_NS::Node("And", SR_GRAPH_GUI_NS::NodeType::Simple))
                .AddInput("", SR_GRAPH_GUI_NS::PinType::Bool)
                .AddInput("", SR_GRAPH_GUI_NS::PinType::Bool)
                .AddOutput("", SR_GRAPH_GUI_NS::PinType::Bool)
                .SetPosition(context.popupPos)
            ;
        });

        commonNodesMenu.AddMenu("Or").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(new SR_GRAPH_GUI_NS::Node("Or", SR_GRAPH_GUI_NS::NodeType::Simple))
                .AddInput("", SR_GRAPH_GUI_NS::PinType::Bool)
                .AddInput("", SR_GRAPH_GUI_NS::PinType::Bool)
                .AddOutput("", SR_GRAPH_GUI_NS::PinType::Bool)
                .SetPosition(context.popupPos)
            ;
        });

        commonNodesMenu.AddMenu("Not").SetAction([](const SR_GRAPH_GUI_NS::DrawPopupContext& context) {
            context.pWidget->AddNode(new SR_GRAPH_GUI_NS::Node("Not", SR_GRAPH_GUI_NS::NodeType::Simple))
                .AddInput("", SR_GRAPH_GUI_NS::PinType::Bool)
                .AddOutput("", SR_GRAPH_GUI_NS::PinType::Bool)
                .SetPosition(context.popupPos)
            ;
        });

        auto&& passesNodesMenu = m_creationPopup->AddMenu("Passes");

        Super::InitCreationPopup();
    }
}