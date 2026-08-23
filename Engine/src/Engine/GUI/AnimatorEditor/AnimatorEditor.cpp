//
// Created by Monika on 14.01.2023.
//

#include <Engine/GUI/AnimatorEditor/AnimatorEditor.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawer.h>
#include <Engine/EngineCommands.h>

#include <Graphics/Animations/Animator.h>
#include <Graphics/Animations/AnimationGraphNode.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>
#include <ImmediateGUI/GUI/NodeEditor.h>

#include <Utils/Resources/ResourceManager.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/Events/Broadcaster.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/Reflection/Value.h>

#include <Codegen/AnimatorEditor.generated.hpp>

namespace SR_CORE_GUI_NS {
    AnimatorEditor::AnimatorEditor()
        : Super("Animator")
    { }

    void AnimatorEditor::Init() {
        Super::Init();

        if (!m_propertyDrawer) {
            m_propertyDrawer = SRNew<SR_CORE_GUI_NS::ObjectPropertyDrawer>();
        }

        m_onCommandRedoSubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_ON_COMMAND_REDO_ID, [this](const SR_UTILS_NS::SubscriptionMessage& msg) {
            m_skipInspect = true;
        });
        m_onCommandUndoSubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_ON_COMMAND_UNDO_ID, [this](const SR_UTILS_NS::SubscriptionMessage& msg) {
            m_skipInspect = true;
        });
        m_doInspectEntitySubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_DO_INSPECT_ENTITY_ID, [this](const SR_UTILS_NS::SubscriptionMessage& msg) {
            if (msg.GetStringAtom("ClassName") != SR_ANIMATIONS_NS::Animator::GetClassStaticName()) {
                return;
            }
            const auto entityId = msg.GetInt("EntityId");
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& pEntity = pEngine->GetScene()->GetEntityController()->FindById(entityId);
            if (!pEntity) {
                SR_ERROR("AnimatorEditor::Init() : failed to find entity with id: {}", entityId);
                return;
            }
            if (auto&& pAnimator = pEntity.DynamicCast<SR_ANIMATIONS_NS::Animator>()) {
                m_animator = pAnimator;
                m_live = true;
                if (auto&& pGraph = pAnimator->GetGraph()) {
                    m_keepLiveContext = true;
                    Inspect(pAnimator->GetGraphPath());
                    m_keepLiveContext = false;
                    m_animator = pAnimator;
                    m_live = true;
                }
                else {
                    Inspect(pAnimator->GetGraphPath());
                }
            }
        });
    }

    void AnimatorEditor::Inspect(const SR_UTILS_NS::Path& path) {
        if (!m_keepLiveContext) {
            m_animator.Reset();
            m_live = false;
        }

        m_pActiveGraph.Reset();
        m_currentFile = path;

        if (path.IsEmpty()) {
            return;
        }

        m_tab = Tab::Graph;

        Open();
        Focus();

        if (m_live && m_animator) {
            m_pActiveGraph = m_animator->GetGraph();
            return;
        }

        auto&& loadPath = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
        if (auto&& pAsset = SR_UTILS_NS::Asset::Load<SR_GRAPH_NS::Animations::AnimationGraphAsset>(loadPath)) {
            m_pActiveGraph = new SR_GRAPH_NS::Animations::AnimationGraph();
            pAsset->GetData().CloneTo(*m_pActiveGraph);
            m_pActiveGraph->SetAsset(pAsset.Get());
        }
        else {
            SR_ERROR("AnimatorEditor::SetGraphPath() : failed to load animation graph asset: {}", loadPath);
        }
    }

    void AnimatorEditor::DrawNodeEditor() {
        const float_t lineHeight = SR_GRAPH_GUI_NS::Immediate::GetFrameHeightWithSpacing();

        const bool isGraph = m_tab == Tab::Graph;
        const bool isStateMachine = m_tab == Tab::StateMachine;

        if (SR_GRAPH_GUI_NS::Immediate::ButtonColoredText("Graph", isGraph ? SR_MATH_NS::FColor(0.25f, 0.7f, 1.0f, 1.0f) : SR_MATH_NS::FColor(0.35f, 0.35f, 0.35f, 1.0f), SR_MATH_NS::FVector2(lineHeight * 4.f, 0.f))) {
            m_tab = Tab::Graph;
            m_nodeGraphEditor->ClearSelection();
            m_nodeGraphEditor->ResetEditor();
        }
        SR_GRAPH_GUI_NS::Immediate::SameLine();
        if (SR_GRAPH_GUI_NS::Immediate::ButtonColoredText("State Machine", isStateMachine ? SR_MATH_NS::FColor(0.25f, 0.7f, 1.0f, 1.0f) : SR_MATH_NS::FColor(0.35f, 0.35f, 0.35f, 1.0f), SR_MATH_NS::FVector2(lineHeight * 7.f, 0.f))) {
            m_tab = Tab::StateMachine;
            m_nodeGraphEditor->ClearSelection();
            m_nodeGraphEditor->ResetEditor();
        }

        if (m_pActiveGraph && m_live) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            if (SR_GRAPH_GUI_NS::Immediate::ButtonColoredText("Disable live mode", SR_MATH_NS::FColor(1.0f, 0.25f, 0.25f, 1.0f), SR_MATH_NS::FVector2(lineHeight * 7.f, 0.f))) {
                m_live = false;
                m_animator.Reset();
                Inspect(m_pActiveGraph->GetPath());
            }
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (!m_nodeGraphEditor) {
            return;
        }

        const auto size = SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail();
        if (SR_IMMEDIATE_GUI_NS::BeginChild("Node Editor")) {
            m_backgroundText.clear();
            if (auto&& pAsset = m_pActiveGraph ? m_pActiveGraph->GetAsset() : nullptr) {
                m_backgroundText = "Animator: ";
                m_backgroundText += pAsset->GetResourcePath().View();
            }
            if (!IsStateMachineActive() && m_tab == Tab::StateMachine) {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.0f, 0.25f, 0.25f, 1.0f), "State machine is not active!");
            }
            else {
                SyncLogicToVisual();
                m_nodeGraphEditor->SetStyleType(m_tab == Tab::Graph ?
                    SR_IMMEDIATE_GUI_NS::NodeEditorStyleType::Graph :
                    SR_IMMEDIATE_GUI_NS::NodeEditorStyleType::StateMachine
                );
                m_nodeGraphEditor->SetBackgroundText(m_backgroundText);
                m_nodeGraphEditor->SetSize(size);
                m_nodeGraphEditor->Draw();
                SyncVisualToLogic();
            }
            SR_IMMEDIATE_GUI_NS::EndChild();
        }

        if (m_serializer && !SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseLeft)) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& cmd = new SR_CORE_NS::Commands::SerializableChange(pEngine, SR_UTILS_NS::SharedPtrBaseHolder(&m_pActiveGraph), std::move(m_serializer));
            pEngine->GetCmdManager()->Store(cmd);
        }
    }

    void AnimatorEditor::OnNodeTypeSelected(SR_UTILS_NS::StringAtom type, SR_MATH_NS::FVector2 pos) {
        if (IsStateMachineActive()) {
            auto&& pSM = m_pActiveStateMachine.Lock();
            if (auto&& pState = SR_UTILS_NS::Factory::Instance().Create<SR_ANIMATIONS_NS::AnimationState>(type)) {
                pSM->GetMachine()->AddState(pState.Get());
                pState->SetEditorPosition(SR_IMMEDIATE_GUI_NS::NodeEditor::ScreenToCanvas(pos));
            }
        }
        else {
            if (auto&& pNode = SR_UTILS_NS::Factory::Instance().Create<SR_ANIMATIONS_NS::AnimationGraphNode>(type)) {
                auto&& pGraphNode = m_pActiveGraph->AddNode(pNode.Get());
                pGraphNode->SetEditorPosition(SR_IMMEDIATE_GUI_NS::NodeEditor::ScreenToCanvas(pos));
            }
        }
    }

    void AnimatorEditor::SyncLogicToVisual() {
        SR_TRACY_ZONE;

        m_nodeGraphEditor->ResetEditor();

        if (!m_pActiveGraph) {
            return;
        }

        m_nodeGraphEditor->SetNodePopupCallback([this](SR_IMMEDIATE_GUI_NS::NodeInstance& node, const SR_MATH_NS::FVector2& pos) {
            if (IsStateMachineActive()) {
                if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Fast forward")) {
                    if (auto&& pState = static_cast<SR_ANIMATIONS_NS::AnimationState*>(node.GetUserData())) {
                        m_pActiveStateMachine.Lock()->GetMachine()->FastForwardState(pState);
                    }
                }
                if (SR_GRAPH_GUI_NS::Immediate::MenuItem("New transition")) {

                }
            }
        });

        m_nodeGraphEditor->SetSomethingChangedCallback([this]() {
            if (!m_serializer) {
                m_serializer = SR_CORE_NS::Commands::CreateSerializer();
                SR_UTILS_NS::Serialization::Save(*m_serializer, *m_pActiveGraph, SR_UTILS_NS::COMMAND_DATA_ID);
            }
        });

        m_nodeGraphEditor->SetNodeDoubleClickedCallback([this](SR_IMMEDIATE_GUI_NS::NodeInstance& node) {
            if (!IsStateMachineActive()) {
                auto&& pGraphNode = static_cast<SR_ANIMATIONS_NS::AnimationGraphNode*>(node.GetUserData());
                if (auto&& pSMNode = dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode)) {
                    m_tab = Tab::StateMachine;
                    m_skipSync = true;
                    m_pActiveStateMachine = pSMNode;
                    m_nodeGraphEditor->ResetEditor();
                    m_nodeGraphEditor->ClearSelection();
                }
            }
        });

        m_nodeGraphEditor->SetNodeDeletedCallback([this](SR_IMMEDIATE_GUI_NS::NodeInstance& node) {
            if (IsStateMachineActive()) {
                if (auto&& pState = static_cast<SR_ANIMATIONS_NS::AnimationState*>(node.GetUserData())) {
                    m_pActiveStateMachine.Lock()->GetMachine()->RemoveState(pState);
                }
            }
            else {
                if (auto&& pNodeData = (SR_ANIMATIONS_NS::AnimationGraphNode*)node.GetUserData()) {
                    m_pActiveGraph->RemoveNode(pNodeData->GetIndex());
                }
            }
        });

        m_nodeGraphEditor->SetLinkDeletedCallback([this](SR_IMMEDIATE_GUI_NS::LinkInstance& link) {
            if (IsStateMachineActive()) {
                if (auto&& pTransition = static_cast<SR_ANIMATIONS_NS::AnimationStateTransition*>(link.GetUserData())) {
                    if (auto&& pState = static_cast<SR_ANIMATIONS_NS::AnimationState*>(link.GetOutputPin()->GetNode()->GetUserData())) {
                        pState->RemoveTransition(pTransition);
                    }
                }
            }
            else {
                auto&& pInputPin = link.GetInputPin();
                auto&& pInputNode = pInputPin->GetNode();
                const uint32_t inputIndex = pInputNode->GetPinIndex(pInputPin);
                static_cast<SR_ANIMATIONS_NS::AnimationGraphNode*>(pInputNode->GetUserData())->BreakLink(inputIndex);
            }
        });

        m_nodeGraphEditor->SetLinkCreatedCallback([](SR_IMMEDIATE_GUI_NS::LinkInstance& link) {
            auto&& pInputPin = link.GetInputPin();
            auto&& pOutputPin = link.GetOutputPin();
            auto&& pInputNode = pInputPin->GetNode();
            auto&& pOutputNode = pOutputPin->GetNode();
            const uint32_t inputIndex = pInputNode->GetPinIndex(pInputPin);
            const uint32_t outputIndex = pOutputNode->GetPinIndex(pOutputPin);
            static_cast<SR_ANIMATIONS_NS::AnimationGraphNode*>(pOutputNode->GetUserData())->ConnectTo(
                static_cast<SR_ANIMATIONS_NS::AnimationGraphNode*>(pInputNode->GetUserData()), outputIndex, inputIndex
            );
        });

        m_nodeGraphEditor->SetBackgroundPopupCallback([this](const SR_MATH_NS::FVector2& pos) {
            if (m_pActiveGraph) {
                if (m_nodeSearchTabCached != m_tab) {
                    m_nodeSearchTabCached = m_tab;
                    m_createNodeSearch.clear();
                    m_availableNodeTypes.clear();
                }

                BuildNodeMenu(m_categories, m_tab == Tab::Graph ?
                    SR_ANIMATIONS_NS::AnimationGraphNode::GetClassStaticName() :
                    SR_ANIMATIONS_NS::AnimationState::GetClassStaticName()
                );
                SR_GRAPH_GUI_NS::Immediate::InputText("##NodeSearch", &m_createNodeSearch);
                SR_GRAPH_GUI_NS::Immediate::Separator();
                DrawNodeMenuRecursive(m_categories, "", pos);
            }
        });

        if (IsStateMachineActive()) {
            m_pActiveStateMachine.Lock()->GetMachine()->ForEachState([this](SR_ANIMATIONS_NS::AnimationState& state) {
                if (auto&& pNode = m_nodeGraphEditor->CreateNode()) {
                    state.SetUserData(pNode);
                    pNode->SetUserData(&state);
                    pNode->SetPosition(state.GetEditorPosition());
                    pNode->SetTitle(state.GetStateName());
                    pNode->SetProgress(state.GetProgress());
                    pNode->AddInputPin("In", SR_IMMEDIATE_GUI_NS::PinTypeInfo(nullptr, true));
                    pNode->AddOutputPin("Out", SR_IMMEDIATE_GUI_NS::PinTypeInfo(nullptr, true));
                }
            });
            m_pActiveStateMachine.Lock()->GetMachine()->ForEachState([this](SR_ANIMATIONS_NS::AnimationState& state) {
                if (auto&& pNode = state.GetUserData<SR_IMMEDIATE_GUI_NS::NodeInstance>()) {
                    for (auto&& pTransition : state.GetTransitions()) {
                        auto&& pTargetState = m_pActiveStateMachine.Lock()->GetMachine()->GetState(pTransition->GetTargetIndex());
                        if (auto&& pTargetNodeInstance = pTargetState->GetUserData<SR_IMMEDIATE_GUI_NS::NodeInstance>()) {
                            auto&& pLink = pNode->LinkTo(pTargetNodeInstance, 0, 0);
                            pLink->SetUserData(pTransition.Get());
                        }
                    }
                }
            });
        }
        else {
            m_pActiveGraph->ForEachNode([this](SR_ANIMATIONS_NS::AnimationGraphNode& node) {
                if (auto&& pNode = m_nodeGraphEditor->CreateNode()) {
                    node.SetUserData(pNode);
                    pNode->SetUserData(&node);
                    pNode->SetPosition(node->GetEditorPosition());
                    pNode->SetTitle(node.GetMeta()->GetDisplayName());
                    for (auto&& inputLink : node->GetInputLinks()) {
                        pNode->AddInputPin(inputLink.name, SR_IMMEDIATE_GUI_NS::PinTypeInfo(nullptr, true));
                    }
                    for (auto&& outputLink : node->GetOutputLinks()) {
                        pNode->AddOutputPin(outputLink.name, SR_IMMEDIATE_GUI_NS::PinTypeInfo(nullptr, true));
                    }
                }
            });

            m_pActiveGraph->ForEachNode([this](SR_ANIMATIONS_NS::AnimationGraphNode& node) {
                if (auto&& pNode = node->GetUserData<SR_IMMEDIATE_GUI_NS::NodeInstance>()) {
                    uint32_t inputIndex = 0;
                    for (auto&& inputLink : node->GetInputLinks()) {
                        inputIndex++;
                        if (inputLink.IsConnected()) {
                            auto&& pTargetNode = m_pActiveGraph->GetNode(inputLink.GetTargetNodeIndex());
                            if (auto&& pTargetNodeInstance = pTargetNode->GetUserData<SR_IMMEDIATE_GUI_NS::NodeInstance>()) {
                                pTargetNodeInstance->LinkTo(pNode, inputLink.GetTargetPinIndex(), inputIndex - 1);
                            }
                        }
                    }
                }
            });
        }
    }

    void AnimatorEditor::SyncVisualToLogic() {
        SR_TRACY_ZONE;

        if (m_skipSync) {
            m_skipSync = false;
            return;
        }

        if (!m_pActiveGraph) {
            return;
        }

        if (IsStateMachineActive()) {
            m_pActiveStateMachine.Lock()->GetMachine()->ForEachState([](SR_ANIMATIONS_NS::AnimationState& state) {
                if (auto&& pNode = state->GetUserData<SR_IMMEDIATE_GUI_NS::NodeInstance>()) {
                    state->SetEditorPosition(pNode->GetPosition());
                }
            });
        }
        else {
            m_pActiveGraph->ForEachNode([](SR_ANIMATIONS_NS::AnimationGraphNode& node) {
                if (auto&& pNode = node->GetUserData<SR_IMMEDIATE_GUI_NS::NodeInstance>()) {
                    node->SetEditorPosition(pNode->GetPosition());
                }
            });
        }
    }

    void AnimatorEditor::DrawInspectPanel() {
        if (!m_pActiveGraph) {
            return;
        }

        if (m_skipInspect) {
            m_skipInspect = false;
            return;
        }

        if (!m_propertyDrawer) {
            m_propertyDrawer = SRNew<SR_CORE_GUI_NS::ObjectPropertyDrawer>();
        }

        SR_GRAPH_GUI_NS::Immediate::Text("Properties");
        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_UTILS_NS::SRClass* pSelectedObject = nullptr;

        auto&& selectedNodes = m_nodeGraphEditor->GetSelectedNodes();
        auto&& selectedLinks = m_nodeGraphEditor->GetSelectedLinks();
        if (selectedNodes.size() == 1) {
            if (IsStateMachineActive()) {
                pSelectedObject = static_cast<SR_ANIMATIONS_NS::AnimationState*>(selectedNodes.front()->GetUserData());
            }
            else {
                pSelectedObject = static_cast<SR_ANIMATIONS_NS::AnimationGraphNode*>(selectedNodes.front()->GetUserData());
            }
        }
        else if (selectedLinks.size() == 1) {
            if (IsStateMachineActive()) {
                auto&& pUserData = selectedLinks.front()->GetUserData();
                pSelectedObject = pUserData ? static_cast<SR_ANIMATIONS_NS::AnimationStateTransition*>(pUserData) : nullptr;
            }
        }

        if (!pSelectedObject) {
            if (m_tab == Tab::Graph) {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.7f, 0.7f, 0.7f, 1.0f), "Select a graph node or transition to edit its properties.");
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.7f, 0.7f, 0.7f, 1.0f), "Select a state node to edit its properties (including transitions/conditions).");
            }
            return;
        }

        SR_UTILS_NS::Reflection::Value value = SR_UTILS_NS::Reflection::Value::CreateRef(*pSelectedObject);

        PropertyDrawerContext context(&value);
        context.pEditor = dynamic_cast<EditorGUI*>(GetManager());

        const float_t lineHeight = SR_GRAPH_GUI_NS::Immediate::GetFontSize() + SR_GRAPH_GUI_NS::Immediate::GetFramePadding().y * 2.0f;
        float_t windowWidth = SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x;
        context.lineHeight = lineHeight;
        context.fieldHeight = lineHeight;
        context.axisButtonWidth = context.lineHeight;
        context.spaceWidth = windowWidth;
        context.fieldTitleWidth = windowWidth * 0.33f;
        context.fieldWidth = windowWidth * 0.67f;
        context.noHeader = true;
        context.openedByDefault = true;
        context.pOwner = pSelectedObject;
        context.pUID = pSelectedObject;
        context.onBeforeChangeCallback = [this](bool drag) {
            if (!m_serializer) {
                m_serializer = SR_CORE_NS::Commands::CreateSerializer();
                SR_UTILS_NS::Serialization::Save(*m_serializer, *m_pActiveGraph, SR_UTILS_NS::COMMAND_DATA_ID);
            }
        };
        m_propertyDrawer->Draw(context);
    }

    void AnimatorEditor::TopPanelSave() {
        if (!m_pActiveGraph) {
            return;
        }

        if (auto&& pAsset = m_pActiveGraph->GetAsset()) {
            m_pActiveGraph->CloneTo(pAsset->GetDataMutable());
            if (!pAsset->SaveAsset()) {
                SR_ERROR("AnimatorEditor::TopPanelSave() : failed to save asset \"{}\"!", pAsset->GetResourcePath());
            }
        }
    }

    void AnimatorEditor::TopPanelOpen() {
        auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(
            SR_UTILS_NS::ResourceManager::Instance().GetResPath(), 
            { { "Animator", "animator" } }
        );
        
        if (path.empty()) {
            return;
        }

        Inspect(path);
    }
}

