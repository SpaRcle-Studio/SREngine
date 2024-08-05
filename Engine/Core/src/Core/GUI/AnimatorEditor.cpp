//
// Created by Monika on 14.01.2023.
//

#include <Core/GUI/AnimatorEditor.h>

#include <Graphics/Animations/Animator.h>

namespace SR_CORE_GUI_NS {
    AnimatorEditor::AnimatorEditor()
        : Super("Animator")
    { }

    void AnimatorEditor::SetAnimator(const AnimatorPtr& pAnimator) noexcept {
        m_pAnimator = pAnimator;
    }

    void AnimatorEditor::Draw() {
        if (auto&& pHierarchy = GetManager()->GetWidget<Hierarchy>()) {
            if (auto&& selected = pHierarchy->GetSelected(); !selected.empty()) {
                if (auto&& pAnimator = (*selected.begin())->GetComponent<SR_ANIMATIONS_NS::Animator>()) {
                    SetAnimator(pAnimator);
                }
            }
        }

        if (!m_pAnimator) {
            ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "No animator selected!");
            return;
        }

        auto&& pGraph = m_pAnimator->GetGraph();
        if (!pGraph) {
            ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Animator has no graph!");
            return;
        }

        for (auto&& pNode : pGraph->GetNodes()) {
            ImGui::Separator();
            ImGui::Text("Node: %s", SR_UTILS_NS::EnumReflector::ToStringAtom(pNode->GetType()).c_str());

            if (auto&& pStateMachineNode = dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pNode)) {
                auto&& pStateMachine = pStateMachineNode->GetMachine();
                if (!pStateMachine) {
                    ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "State machine is null!");
                    continue;
                }

                for (auto&& pState : pStateMachine->GetStates()) {
                    ImGui::Text("\tState: %s", pState->GetName().c_str());
                    ImGui::Text("\t\tProgress: %f", pState->GetProgress());

                    for (auto&& pTransition : pState->GetTransitions()) {
                        ImGui::Text("\t\tTransition from %s to %s", pTransition->GetSource()->GetName().c_str(), pTransition->GetDestination()->GetName().c_str());
                        ImGui::Text("\t\t\tProgress: %f", pTransition->GetProgress());
                    }
                }
            }
        }
    }

    //void AnimatorEditor::OnOpen() {
    //#ifdef SR_USE_IMGUI_NODE_EDITOR
    //    ax::NodeEditor::Config config;
//
    //    static const SR_UTILS_NS::Path settings = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Animator.json");
    //    config.SettingsFile = settings.c_str();
//
    //    config.UserPointer = this;
//
    //    config.LoadNodeSettings = [](ax::NodeEditor::NodeId nodeId, char* data, void* userPointer) -> size_t {
    //        return 0;
    //    };
//
    //    config.SaveNodeSettings = [](ax::NodeEditor::NodeId nodeId, const char* data, size_t size, ax::NodeEditor::SaveReasonFlags reason, void* userPointer) -> bool {
    //        return true;
    //    };
//
    //    m_editor = ax::NodeEditor::CreateEditor(&config);
    //#endif

        ///AddNode(new SR_GRAPH_NS::GUI::Node("Node A", SR_GRAPH_NS::GUI::NodeType::Blueprint))
        ///  .AddInput("Pin AAAA", SR_GRAPH_NS::GUI::PinType::Flow)
        ///  .AddInput("Pin B", SR_GRAPH_NS::GUI::PinType::Bool)
        ///  .AddInput("Pin C", SR_GRAPH_NS::GUI::PinType::Float)
        ///  .AddInput("Pin D", SR_GRAPH_NS::GUI::PinType::Delegate)
        ///  .AddInput("Pin E", SR_GRAPH_NS::GUI::PinType::String)
        ///  .AddOutput("Pin A", SR_GRAPH_NS::GUI::PinType::Flow)
        ///  .AddOutput("Pin B", SR_GRAPH_NS::GUI::PinType::Function);

        ///AddNode(new SR_GRAPH_NS::GUI::Node("Final Animation Pose", SR_GRAPH_NS::GUI::NodeType::Blueprint))
        ///  .AddInput("Result", SR_GRAPH_NS::GUI::PinType::Flow);

        ///AddNode(new SR_GRAPH_NS::GUI::Node("Walking", SR_GRAPH_NS::GUI::NodeType::Simple))
        ///  .AddOutput("", SR_GRAPH_NS::GUI::PinType::Flow);

        ///AddNode(new SR_GRAPH_NS::GUI::Node("Idle", SR_GRAPH_NS::GUI::NodeType::Simple))
        ///  .AddOutput("", SR_GRAPH_NS::GUI::PinType::Flow);

        ///AddNode(new SR_GRAPH_NS::GUI::Node("Mix", SR_GRAPH_NS::GUI::NodeType::Simple))
        ///  .AddInput("First", SR_GRAPH_NS::GUI::PinType::Flow)
        ///  .AddInput("Second", SR_GRAPH_NS::GUI::PinType::Flow)
        ///  .AddOutput("Output", SR_GRAPH_NS::GUI::PinType::Flow);

   //    Super::OnOpen();
   // }
//
   // void AnimatorEditor::DrawPopupMenu() {
   // #ifdef SR_USE_IMGUI_NODE_EDITOR
   //     auto&& openPopupPosition = ImGui::GetMousePos();
//
   //     ax::NodeEditor::Suspend();
//
   //     ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
//
   //     if (ax::NodeEditor::ShowBackgroundContextMenu()) {
   //         ImGui::OpenPopup("Create New Node");
   //     }

        //if (ImGui::BeginPopup("Create New Node")) {
        //    if (ImGui::MenuItem("Add animation")) {
        //        auto&& node = AddNode(new SR_GRAPH_NS::GUI::Node("Walking", SR_GRAPH_NS::GUI::NodeType::Simple))
        //            .AddOutput("", SR_GRAPH_NS::GUI::PinType::Flow);
        //        ax::NodeEditor::SetNodePosition(node.GetId(), openPopupPosition);
        //    }
        //    ImGui::EndPopup();
        //}

  //     ImGui::PopStyleVar();

  //     ax::NodeEditor::Resume();
  // #endif
  // }
}

