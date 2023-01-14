//
// Created by Monika on 14.01.2023.
//

#include <Core/GUI/AnimatorEditor.h>

namespace SR_CORE_NS::GUI {
    AnimatorEditor::AnimatorEditor()
        : Super("Animator")
    { }

    void AnimatorEditor::Draw() {
        UpdateTouch();

        ax::NodeEditor::SetCurrentEditor(m_editor);

        ax::NodeEditor::Begin("AnimatorEditor");

        for (auto&& [id, node] : m_nodes)
            node->Draw(m_nodeBuilder, nullptr);

        for (auto&& [id, link] : m_links)
            link->Draw();

        if (ax::NodeEditor::BeginCreate()) {
            ax::NodeEditor::PinId inputPinId, outputPinId;
            if (ax::NodeEditor::QueryNewLink(&inputPinId, &outputPinId) && (inputPinId && outputPinId)) {
                auto&& pInputPin = reinterpret_cast<SR_GRAPH_NS::GUI::Pin*>(inputPinId.AsPointer());
                auto&& pOutputPin = reinterpret_cast<SR_GRAPH_NS::GUI::Pin*>(outputPinId.AsPointer());

                if (pInputPin != pOutputPin) {
                    if (SR_GRAPH_NS::GUI::CanCreateLink(pInputPin, pOutputPin) && ax::NodeEditor::AcceptNewItem()) {
                        AddLink(new SR_GRAPH_NS::GUI::Link(pInputPin, pOutputPin));
                    }
                }
            }
        }
        ax::NodeEditor::EndCreate();

        ax::NodeEditor::End();
    }

    void AnimatorEditor::OnOpen() {
        ax::NodeEditor::Config config;

        static const SR_UTILS_NS::Path settings = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Animator.json");
        config.SettingsFile = settings.c_str();

        config.UserPointer = this;

        config.LoadNodeSettings = [](ax::NodeEditor::NodeId nodeId, char* data, void* userPointer) -> size_t {
            return 0;
        };

        config.SaveNodeSettings = [](ax::NodeEditor::NodeId nodeId, const char* data, size_t size, ax::NodeEditor::SaveReasonFlags reason, void* userPointer) -> bool {
            return true;
        };

        m_editor = ax::NodeEditor::CreateEditor(&config);

        AddNode(new SR_GRAPH_NS::GUI::Node("Node A", SR_GRAPH_NS::GUI::NodeType::Blueprint))
          .AddInput("Pin AAAA", SR_GRAPH_NS::GUI::PinType::Flow)
          .AddInput("Pin B", SR_GRAPH_NS::GUI::PinType::Bool)
          .AddInput("Pin C", SR_GRAPH_NS::GUI::PinType::Float)
          .AddInput("Pin D", SR_GRAPH_NS::GUI::PinType::Delegate)
          .AddInput("Pin E", SR_GRAPH_NS::GUI::PinType::String)
          .AddOutput("Pin A", SR_GRAPH_NS::GUI::PinType::Flow)
          .AddOutput("Pin B", SR_GRAPH_NS::GUI::PinType::Function);

        AddNode(new SR_GRAPH_NS::GUI::Node("Final Animation Pose", SR_GRAPH_NS::GUI::NodeType::Blueprint))
          .AddInput("Result", SR_GRAPH_NS::GUI::PinType::Flow);

        AddNode(new SR_GRAPH_NS::GUI::Node("Walking", SR_GRAPH_NS::GUI::NodeType::Simple))
          .AddOutput("", SR_GRAPH_NS::GUI::PinType::Flow);

        AddNode(new SR_GRAPH_NS::GUI::Node("Idle", SR_GRAPH_NS::GUI::NodeType::Simple))
          .AddOutput("", SR_GRAPH_NS::GUI::PinType::Flow);

        AddNode(new SR_GRAPH_NS::GUI::Node("Mix", SR_GRAPH_NS::GUI::NodeType::Simple))
          .AddInput("First", SR_GRAPH_NS::GUI::PinType::Flow)
          .AddInput("Second", SR_GRAPH_NS::GUI::PinType::Flow)
          .AddOutput("Output", SR_GRAPH_NS::GUI::PinType::Flow);

       Super::OnOpen();
    }

   void AnimatorEditor::OnClose() {
       if (m_editor) {
           ax::NodeEditor::DestroyEditor(m_editor);
           m_editor = nullptr;
       }

       Super::OnClose();
   }
}