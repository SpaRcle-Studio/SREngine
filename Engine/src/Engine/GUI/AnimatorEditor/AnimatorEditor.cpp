//
// Created by Monika on 14.01.2023.
//

#include <Engine/GUI/AnimatorEditor/AnimatorEditor.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>
#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawer.h>
#include <Engine/EngineCommands.h>

#include <Graphics/Animations/Animator.h>
#include <Graphics/Animations/AnimationGraphNode.h>
#include <Graphics/GUI/Node.h>
#include <Graphics/GUI/Link.h>
#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/NodeBuilder.h>

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
        , m_nodeGraphEditor(SR_IMMEDIATE_GUI_NS::NodeEditorInstance::Create())
    { }

    void AnimatorEditor::Init() {
        Super::Init();
        InitNodeTypes();

        if (!m_propertyDrawer) {
            m_propertyDrawer = SRNew<SR_CORE_GUI_NS::ObjectPropertyDrawer>();
        }

        m_doInspectEntitySubscription.Reset();
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

    void AnimatorEditor::OnClose() {
        Super::OnClose();
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

    void AnimatorEditor::Draw() {
        DrawTopPanel();

        SR_GRAPH_GUI_NS::Immediate::Separator();
        
        // Разделяем окно на левую панель и редактор
        auto&& availableSize = SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail();
        
        // Левая панель для свойств
        SR_GRAPH_GUI_NS::Immediate::BeginChild("LeftPanel", SR_MATH_NS::FVector2(m_leftPaneWidth, availableSize.y));
        DrawLeftPanel();
        SR_GRAPH_GUI_NS::Immediate::EndChild();
        
        SR_GRAPH_GUI_NS::Immediate::SameLine();
        
        // Редактор графа
        SR_GRAPH_GUI_NS::Immediate::BeginChild("NodeEditor", SR_MATH_NS::FVector2(availableSize.x - m_leftPaneWidth - 10, availableSize.y));
        DrawNodeEditor();
        SR_GRAPH_GUI_NS::Immediate::EndChild();
    }

    void AnimatorEditor::DrawNodeEditor() {
        const float_t lineHeight = SR_GRAPH_GUI_NS::Immediate::GetFrameHeightWithSpacing();

        const bool isGraph = m_tab == Tab::Graph;
        const bool isStateMachine = m_tab == Tab::StateMachine;

        if (SR_GRAPH_GUI_NS::Immediate::ButtonColoredText("Graph", isGraph ? SR_MATH_NS::FColor(0.25f, 0.7f, 1.0f, 1.0f) : SR_MATH_NS::FColor(0.35f, 0.35f, 0.35f, 1.0f), SR_MATH_NS::FVector2(lineHeight * 4.f, 0.f))) {
            m_tab = Tab::Graph;
        }
        SR_GRAPH_GUI_NS::Immediate::SameLine();
        if (SR_GRAPH_GUI_NS::Immediate::ButtonColoredText("State Machine", isStateMachine ? SR_MATH_NS::FColor(0.25f, 0.7f, 1.0f, 1.0f) : SR_MATH_NS::FColor(0.35f, 0.35f, 0.35f, 1.0f), SR_MATH_NS::FVector2(lineHeight * 7.f, 0.f))) {
            m_tab = Tab::StateMachine;
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
            SyncLogicToVisual();
            m_nodeGraphEditor->SetBackgroundText(m_backgroundText);
            m_nodeGraphEditor->SetSize(size);
            m_nodeGraphEditor->Draw();
            SyncVisualToLogic();
            SR_IMMEDIATE_GUI_NS::EndChild();
        }

        if (m_serializer && !SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::MouseLeft)) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& cmd = new SR_CORE_NS::Commands::SerializableChange(pEngine, SR_UTILS_NS::SharedPtrBaseHolder(&m_pActiveGraph), std::move(m_serializer));
            pEngine->GetCmdManager()->Store(cmd);
        }
    }

    void AnimatorEditor::SyncLogicToVisual() {
        SR_TRACY_ZONE;

        m_nodeGraphEditor->ResetEditor();

        if (!m_pActiveGraph) {
            return;
        }

        m_nodeGraphEditor->SetSomethingChangedCallback([this]() {
            if (!m_serializer) {
                m_serializer = SR_CORE_NS::Commands::CreateSerializer();
                SR_UTILS_NS::Serialization::Save(*m_serializer, *m_pActiveGraph, SR_UTILS_NS::COMMAND_DATA_ID);
            }
        });

        m_nodeGraphEditor->SetNodeDeletedCallback([this](SR_IMMEDIATE_GUI_NS::NodeInstance& node) {
            if (auto&& pNodeData = (SR_ANIMATIONS_NS::AnimationGraphNode*)node.GetUserData()) {
                m_pActiveGraph->RemoveNode(pNodeData->GetIndex());
            }
        });

        m_nodeGraphEditor->SetLinkDeletedCallback([](SR_IMMEDIATE_GUI_NS::LinkInstance& link) {
            auto&& pInputPin = link.GetInputPin();
            auto&& pInputNode = pInputPin->GetNode();
            const uint32_t inputIndex = pInputNode->GetPinIndex(pInputPin);
            static_cast<SR_ANIMATIONS_NS::AnimationGraphNode*>(pInputNode->GetUserData())->BreakLink(inputIndex);
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
                BuildNodeMenu(m_categories);
                SR_GRAPH_GUI_NS::Immediate::InputText("##NodeSearch", &m_createNodeSearch);
                SR_GRAPH_GUI_NS::Immediate::Separator();
                DrawNodeMenuRecursive(m_categories, "", pos);
            }
        });

        m_pActiveGraph->ForEachNode([this](SR_ANIMATIONS_NS::AnimationGraphNode& node) {
            if (auto&& pNode = m_nodeGraphEditor->CreateNode()) {
                node.SetUserData(pNode);
                pNode->SetUserData(&node);
                pNode->SetPosition(node->GetEditorPosition());
                pNode->SetTitle(node.GetMeta()->GetDisplayName());
                for (auto&& inputLink : node->GetInputLinks()) {
                    pNode->AddInputPin(inputLink.name, SR_IMMEDIATE_GUI_NS::PinTypeInfo{SR_UTILS_NS::Reflection::TypeInfo(), true});
                }
                for (auto&& outputLink : node->GetOutputLinks()) {
                    pNode->AddOutputPin(outputLink.name, SR_IMMEDIATE_GUI_NS::PinTypeInfo{SR_UTILS_NS::Reflection::TypeInfo(), true});
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

    void AnimatorEditor::SyncVisualToLogic() {
        SR_TRACY_ZONE;

        if (!m_pActiveGraph) {
            return;
        }

        m_pActiveGraph->ForEachNode([](SR_ANIMATIONS_NS::AnimationGraphNode& node) {
            if (auto&& pNode = node->GetUserData<SR_IMMEDIATE_GUI_NS::NodeInstance>()) {
                node->SetEditorPosition(pNode->GetPosition());
            }
        });
    }

    void AnimatorEditor::DrawGraphEditor() {
        //// Даблклик по ноде стейт-машины открывает вкладку State Machine
        //if (SR_GRAPH_GUI_NS::Immediate::IsMouseDoubleClicked(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left)) {
        //    const int selected = SR_IMMEDIATE_GUI_NS::NodeEditor::GetSelectedNodes(nullptr, 0);
        //    if (selected > 0) {
        //        std::vector<uintptr_t> nodeIds(selected);
        //        SR_IMMEDIATE_GUI_NS::NodeEditor::GetSelectedNodes(nodeIds.data(), selected);
//
        //        if (!nodeIds.empty()) {
        //            if (auto&& it = m_nodes.find(nodeIds[0]); it != m_nodes.end()) {
        //                auto&& pGraphNode = it->second->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>();
        //                if (auto&& pSMNode = dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode)) {
        //                    m_context.openedStateMachineNodeIndex = pSMNode->GetIndex();
        //                    m_tab = Tab::StateMachine;
        //                    m_context.openStateMachineRequested = true; // синхронизацию делаем уже в DrawStateMachineEditor()
        //                }
        //            }
        //        }
        //    }
        //}
    }

    void AnimatorEditor::DrawLeftPanel() {
        if (!m_pActiveGraph) {
            return;
        }

        if (!m_propertyDrawer) {
            m_propertyDrawer = SRNew<SR_CORE_GUI_NS::ObjectPropertyDrawer>();
        }

        SR_GRAPH_GUI_NS::Immediate::Text("Properties");
        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_UTILS_NS::SRClass* pSelectedObject = nullptr;

        //void* pEditor = (m_tab == Tab::Graph) ? m_editor : m_context.pStateMachineEditor;
        //if (pEditor) {
        //    SR_IMMEDIATE_GUI_NS::NodeEditor::SetCurrentEditor(pEditor);

        //    const int selectedNodes = SR_IMMEDIATE_GUI_NS::NodeEditor::GetSelectedNodes(nullptr, 0);

        //    if (selectedNodes > 0) {
        //        m_editorStateMachine.ResetSelectedLink();
        //        std::vector<uintptr_t> nodeIds(selectedNodes);
        //        SR_IMMEDIATE_GUI_NS::NodeEditor::GetSelectedNodes(nodeIds.data(), selectedNodes);
        //        if (nodeIds.size() == 1) {
        //            const uintptr_t nodeId = nodeIds[0];
        //            if (m_tab == Tab::Graph) {
        //                if (auto&& it = m_nodes.find(nodeId); it != m_nodes.end()) {
        //                    pSelectedObject = it->second->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>();
        //                }
        //            }
        //            else {
        //                pSelectedObject = m_editorStateMachine.GetSelectedNode(nodeId);
        //            }
        //        }
        //    }
        //    else if (m_tab == Tab::StateMachine) {
        //        pSelectedObject = m_editorStateMachine.GetSelectedLink();
        //    }

        //    SR_IMMEDIATE_GUI_NS::NodeEditor::SetCurrentEditor(nullptr);
        //}

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
        m_propertyDrawer->Draw(context);
    }

    void AnimatorEditor::InitNodeTypes() {
        // Получаем все классы, наследующиеся от AnimationGraphNode
        m_availableNodeTypes = SR_UTILS_NS::Factory::Instance().GetInheritances(
            SR_ANIMATIONS_NS::AnimationGraphNode::GetClassStaticName()
        );

        // Фильтруем абстрактные и скрытые классы
        std::erase_if(m_availableNodeTypes, [](auto&& name) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(name);
            if (!pMeta) {
                return true;
            }
            return pMeta->IsAbstract() || pMeta->IsHidden();
        });
    }

    void AnimatorEditor::BuildNodeMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories) {
        categories.clear();

        for (auto&& nodeTypeName : m_availableNodeTypes) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(nodeTypeName);
            if (!pMeta) {
                continue;
            }

            auto&& category = pMeta->GetCategory();
            std::string categoryPath = "Nodes";
            if (!category.empty()) {
                categoryPath.clear();
                for (size_t i = 0; i < category.size(); ++i) {
                    if (i > 0) {
                        categoryPath += "/";
                    }
                    categoryPath += category[i].ToStringRef();
                }
            }

            categories[categoryPath].emplace_back(nodeTypeName);
        }
    }
    
    void AnimatorEditor::DrawNodeMenuRecursive(const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix, SR_MATH_NS::FVector2 popupPos) {
        /// Группируем ноды по следующему уровню категорий
        std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>> subCategories;
        std::vector<SR_UTILS_NS::StringAtom> directNodes;

        for (auto&& [categoryPath, nodeTypes] : categories) {
            if (categoryPath == prefix) {
                /// Ноды напрямую в этой категории
                directNodes.insert(directNodes.end(), nodeTypes.begin(), nodeTypes.end());
            }
            else if (prefix.empty() || (categoryPath.size() >= prefix.size() + 1 && categoryPath.substr(0, prefix.size() + 1) == prefix + "/")) {
                /// Определяем следующий уровень
                std::string remaining = prefix.empty() ? categoryPath : categoryPath.substr(prefix.size() + 1);
                auto&& nextSlash = remaining.find('/');

                if (nextSlash == std::string::npos) {
                    /// Это конечный уровень для этой категории
                    directNodes.insert(directNodes.end(), nodeTypes.begin(), nodeTypes.end());
                }
                else {
                    /// Есть подкатегория
                    std::string nextLevel = prefix.empty() ? remaining.substr(0, nextSlash) : prefix + "/" + remaining.substr(0, nextSlash);
                    subCategories[nextLevel].insert(subCategories[nextLevel].end(), nodeTypes.begin(), nodeTypes.end());
                }
            }
        }

        // Рисуем прямые элементы
        for (auto&& nodeTypeName : directNodes) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(nodeTypeName);
            if (!pMeta) {
                continue;
            }

            auto&& displayName = pMeta->GetDisplayName();
            SR_UTILS_NS::StringAtom menuName = displayName.empty() ? nodeTypeName : displayName;

            if (!m_createNodeSearch.empty() && !SR_CORE_GUI_NS::PropertyDrawerBase::CheckSearchMatch(m_createNodeSearch, menuName.ToStringView())) {
                continue;
            }

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem(menuName.c_str())) {
                if (auto&& pNode = SR_UTILS_NS::Factory::Instance().Create<SR_ANIMATIONS_NS::AnimationGraphNode>(nodeTypeName)) {
                    auto&& pGraphNode = m_pActiveGraph->AddNode(pNode.Get());
                    pGraphNode->SetEditorPosition(SR_IMMEDIATE_GUI_NS::NodeEditor::ScreenToCanvas(popupPos));
                }
            }
        }

        // Рисуем подменю
        for (auto&& [nextLevel, nodeTypes] : subCategories) {
            // Извлекаем имя следующего уровня
            std::string levelName = nextLevel;
            if (!prefix.empty()) {
                levelName = nextLevel.substr(prefix.size() + 1);
            }
            auto&& nextSlash = levelName.find('/');
            if (nextSlash != std::string::npos) {
                levelName = levelName.substr(0, nextSlash);
            }

            if (SR_GRAPH_GUI_NS::Immediate::BeginMenu(levelName.c_str())) {
                DrawNodeMenuRecursive(categories, nextLevel, popupPos);
                SR_GRAPH_GUI_NS::Immediate::EndMenu();
            }
        }
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

    SR_MATH_NS::FColor AnimatorEditor::GetPinColor(SR_SRLM_NS::DataTypeClass pinType) {
        // Цвета пинов на основе типа (аналогично примеру)
        switch (pinType) {
            case SR_SRLM_NS::DataTypeClass::Flow:
                return SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 1.0f); // Белый
            case SR_SRLM_NS::DataTypeClass::Bool:
                return SR_MATH_NS::FColor(0.86f, 0.19f, 0.19f, 1.0f); // Красный
            case SR_SRLM_NS::DataTypeClass::Int8:
            case SR_SRLM_NS::DataTypeClass::Int16:
            case SR_SRLM_NS::DataTypeClass::Int32:
            case SR_SRLM_NS::DataTypeClass::Int64:
            case SR_SRLM_NS::DataTypeClass::UInt8:
            case SR_SRLM_NS::DataTypeClass::UInt16:
            case SR_SRLM_NS::DataTypeClass::UInt32:
            case SR_SRLM_NS::DataTypeClass::UInt64:
                return SR_MATH_NS::FColor(0.27f, 0.79f, 0.61f, 1.0f); // Зеленый
            case SR_SRLM_NS::DataTypeClass::Float:
                return SR_MATH_NS::FColor(0.58f, 0.89f, 0.29f, 1.0f); // Светло-зеленый
            case SR_SRLM_NS::DataTypeClass::String:
                return SR_MATH_NS::FColor(0.49f, 0.08f, 0.60f, 1.0f); // Фиолетовый
            case SR_SRLM_NS::DataTypeClass::Struct:
                return SR_MATH_NS::FColor(0.20f, 0.59f, 0.84f, 1.0f); // Синий
            case SR_SRLM_NS::DataTypeClass::Enum:
                return SR_MATH_NS::FColor(1.0f, 0.19f, 0.19f, 1.0f); // Красный
            case SR_SRLM_NS::DataTypeClass::Array:
                return SR_MATH_NS::FColor(0.85f, 0.0f, 0.72f, 1.0f); // Розовый
            default:
                return SR_MATH_NS::FColor(0.4f, 0.7f, 1.0f, 1.0f); // Голубой по умолчанию
        }
    }

    void AnimatorEditor::OnOpen() {
        Super::OnOpen();
    }

    void AnimatorEditor::Zoom() {
        if (m_nodeGraphEditor) {
            m_nodeGraphEditor->Zoom();
        }
        Super::Zoom();
    }
}

