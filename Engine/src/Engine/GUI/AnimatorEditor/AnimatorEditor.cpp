//
// Created by Monika on 14.01.2023.
//

#include <Engine/GUI/AnimatorEditor/AnimatorEditor.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>
#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawer.h>

#include <Graphics/Animations/Animator.h>
#include <Graphics/Animations/AnimationGraphNode.h>
#include <Graphics/GUI/Node.h>
#include <Graphics/GUI/Link.h>
#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/NodeBuilder.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

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
        , m_editorStateMachine(m_context)
    { }

    void AnimatorEditor::Init() {
        Super::Init();
        InitNodeTypes();
        m_editorStateMachine.InitStateTypes();

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
                m_context.isLive = true;

                if (auto&& pGraph = pAnimator->GetGraph()) {
                    m_context.pRuntimeGraph = pGraph;
                    m_keepLiveContext = true;
                    Inspect(pAnimator->GetGraphPath());
                    m_keepLiveContext = false;
                    m_animator = pAnimator;
                    m_context.isLive = true;
                }
                else {
                    Inspect(pAnimator->GetGraphPath());
                }
            }
        });
    }

    void AnimatorEditor::OnClose() {
        if (m_editor) {
            SR_GRAPH_GUI_NS::Immediate::DestroyEditor(m_editor);
            m_editor = nullptr;
        }
        if (m_context.pStateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::DestroyEditor(m_context.pStateMachineEditor);
            m_context.pStateMachineEditor = nullptr;
        }
        m_editorStateMachine.ClearStateMachineVisual();

        Super::OnClose();
    }

    void AnimatorEditor::Inspect(const SR_UTILS_NS::Path& path) {
        if (!m_keepLiveContext) {
            m_animator.Reset();
            m_context.isLive = false;
            m_context.pRuntimeGraph = nullptr;
        }

        m_graphPath = path;
        m_context.pGraph.Reset();
        m_asset.Reset();
        m_graphAsset.Reset();
        m_currentFile = path;

        if (m_graphPath.IsEmpty()) {
            return;
        }

        m_tab = Tab::Graph;

        Open();
        Focus();

        auto&& loadPath = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
        if (auto&& pAsset = SR_UTILS_NS::Asset::Load<SR_GRAPH_NS::Animations::AnimationGraphAsset>(loadPath)) {
            m_asset = pAsset.StaticCast<SR_UTILS_NS::Asset>();
            m_graphAsset = pAsset;
            m_context.pGraph = new SR_GRAPH_NS::Animations::AnimationGraph();
            pAsset->GetData().CloneTo(*m_context.pGraph);
            m_context.pGraph->SetAsset(pAsset.Get());
            
            // Синхронизируем визуальные ноды с данными графа
            SyncGraphToVisualNodes();
        }
        else {
            SR_ERROR("AnimatorEditor::SetGraphPath() : failed to load animation graph asset: {}", loadPath);
        }
    }

    void AnimatorEditor::Draw() {
        DrawTopPanel();

        if (m_context.isLive) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::Checkbox("Read-only (Live)", &m_context.liveReadOnly);
        }
        
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

        SR_GRAPH_GUI_NS::Immediate::Separator();

        if (m_tab == Tab::Graph) {
            DrawGraphEditor();
        }
        else {
            m_editorStateMachine.DrawStateMachineEditor();
        }
    }

    void AnimatorEditor::DrawGraphEditor() {
        bool needsSync = false;

        if (!m_editor) {
            return;
        }

        const bool editable = !(m_context.isLive && m_context.liveReadOnly);

        SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_editor);
        if (!SR_GRAPH_GUI_NS::Immediate::BeginNodeEditor("Animation Graph Editor", SR_MATH_NS::FVector2())) {
            return;
        }

        // Создаем NodeBuilder (без текстуры для заголовка пока)
        SR_GRAPH_GUI_NS::NodeBuilder builder(nullptr);

        // link style: более “ровные” направления и без странных изгибов
        SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::SourceDirection, SR_MATH_NS::FVector2(1.0f, 0.0f));
        SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::TargetDirection, SR_MATH_NS::FVector2(-1.0f, 0.0f));
        SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::SnapLinkToPinDir, 1.0f);

        if (!m_graphPath.IsEmpty()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.6f, 0.6f, 0.6f, 1.0f), "Live: %s", m_graphPath.CStr());
        }

        // ---------------------------------------------------------------------------------
        // Live overlay: вычисляем активные ноды/линки (по текущим данным графа)
        m_activeGraphNodes.clear();
        m_activeGraphLinks.clear();

        auto* pTraceGraph = (m_context.isLive && m_context.pRuntimeGraph) ? m_context.pRuntimeGraph : (m_context.pGraph ? m_context.pGraph.Get() : nullptr);

        if (pTraceGraph) {
            std::function<void(uint64_t)> visit;
            visit = [this, &visit, pTraceGraph](uint64_t nodeIndex) {
                if (nodeIndex == SR_ID_INVALID) {
                    return;
                }
                if (m_activeGraphNodes.count(nodeIndex) == 1) {
                    return;
                }
                m_activeGraphNodes.insert(nodeIndex);

                auto&& pNode = pTraceGraph->GetNode(nodeIndex);
                if (!pNode) {
                    return;
                }

                auto&& inputs = pNode->GetInputLinks();
                for (uint32_t inputIndex = 0; inputIndex < inputs.size(); ++inputIndex) {
                    auto&& link = inputs[inputIndex];
                    if (!link.IsConnected()) {
                        continue;
                    }
                    visit(static_cast<uint64_t>(link.m_targetNodeIndex));
                }
            };

            if (auto&& pFinal = pTraceGraph->GetFinal()) {
                visit(pFinal->GetIndex());
            }

            for (auto&& [id, pLink] : m_links) {
                if (!pLink || !pLink->IsLinked()) {
                    continue;
                }

                auto* pStartPin = pLink->GetStart();
                auto* pEndPin = pLink->GetEnd();
                if (!pStartPin || !pEndPin) {
                    continue;
                }

                // нормализуем направление output -> input
                if (pStartPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Input && pEndPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Output) {
                    std::swap(pStartPin, pEndPin);
                }

                if (pStartPin->GetKind() != SR_GRAPH_GUI_NS::PinKind::Output || pEndPin->GetKind() != SR_GRAPH_GUI_NS::PinKind::Input) {
                    continue;
                }

                auto* pStartNode = pStartPin->GetNode();
                auto* pEndNode = pEndPin->GetNode();
                if (!pStartNode || !pEndNode) {
                    continue;
                }

                const uint64_t startIndex = pStartNode->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>()->GetIndex();
                const uint64_t endIndex = pEndNode->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>()->GetIndex();

                if (m_activeGraphNodes.count(startIndex) == 0 || m_activeGraphNodes.count(endIndex) == 0) {
                    continue;
                }

                const int32_t startPinIndex = pStartNode->GetPinIndex(pStartPin);
                const int32_t endPinIndex = pEndNode->GetPinIndex(pEndPin);
                if (startPinIndex == SR_ID_INVALID || endPinIndex == SR_ID_INVALID) {
                    continue;
                }

                auto&& pEndGraphNode = pTraceGraph->GetNode(endIndex);
                if (!pEndGraphNode) {
                    continue;
                }

                auto&& endInputs = pEndGraphNode->GetInputLinks();
                if (static_cast<size_t>(endPinIndex) >= endInputs.size()) {
                    continue;
                }

                auto&& dataLink = endInputs[static_cast<size_t>(endPinIndex)];
                if (!dataLink.IsConnected()) {
                    continue;
                }

                if (static_cast<uint64_t>(dataLink.m_targetNodeIndex) == startIndex &&
                    static_cast<int32_t>(dataLink.m_targetPinIndex) == startPinIndex) {
                    m_activeGraphLinks.insert(pLink->GetId());
                }
            }
        }
        // ---------------------------------------------------------------------------------

        // Отрисовываем все ноды
        for (auto&& [id, pNode] : m_nodes) {
            if (!pNode) {
                continue;
            }

            auto&& pGraphNode = pNode->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>();

            const bool activeNode = m_context.isLive && m_activeGraphNodes.count(pGraphNode->GetIndex()) == 1;

            // Получаем цвет заголовка на основе типа ноды
            SR_MATH_NS::FColor headerColor = SR_MATH_NS::FColor(0.2f, 0.6f, 0.84f, 1.0f); // Синий по умолчанию

            if (auto&& pMeta = pGraphNode->GetMeta()) {
                auto&& category = pMeta->GetCategory();
                // Определяем цвет на основе категории
                if (!category.empty()) {
                    // Хешируем первую категорию для получения цвета
                    uint32_t hash = 0;
                    for (char c : category[0].ToStringRef()) {
                        hash = hash * 31 + c;
                    }
                    headerColor = SR_MATH_NS::FColor(
                        std::max(0.3f, std::min(0.9f, ((hash & 0xFF) / 255.0f))),
                        std::max(0.3f, std::min(0.9f, (((hash >> 8) & 0xFF) / 255.0f))),
                        std::max(0.3f, std::min(0.9f, (((hash >> 16) & 0xFF) / 255.0f))),
                        1.0f
                    );
                }
                // Active nodes will be highlighted by border (below), not by header tint.
            }

            builder.Begin(pNode);
            
            // Заголовок ноды
            builder.Header(headerColor);
            SR_GRAPH_GUI_NS::Immediate::Spring(0);
            if (activeNode) {
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, SR_MATH_NS::FColor(0.05f, 0.05f, 0.05f, 1.0f));
            }
            SR_GRAPH_GUI_NS::Immediate::Text("%s", pNode->GetName().c_str());
            if (activeNode) {
                SR_GRAPH_GUI_NS::Immediate::PopStyleColor(1);
            }
            SR_GRAPH_GUI_NS::Immediate::Spring(1);
            builder.EndHeader();
            
            // Отрисовываем входные пины
            for (auto&& pPin : pNode->GetInputs()) {
                builder.Input(pPin);
                
                // Получаем цвет и тип иконки пина
                auto&& pinType = pPin->GetType();
                auto&& iconType = SR_GRAPH_NS::GUI::Pin::GetIconType(pinType);
                auto&& pinColor = GetPinColor(pinType);
                auto&& isLinked = pPin->IsLinked();
                
                // Рисуем иконку пина
                SR_GRAPH_GUI_NS::Immediate::DrawPinIcon(
                    SR_MATH_NS::FVector2(24.0f, 24.0f),
                    iconType,
                    isLinked,
                    pinColor,
                    SR_MATH_NS::FColor(0.125f, 0.125f, 0.125f, 1.0f)
                );
                SR_GRAPH_GUI_NS::Immediate::Spring(0);
                
                if (!pPin->GetName().empty()) {
                    SR_GRAPH_GUI_NS::Immediate::Text("%s", pPin->GetName().c_str());
                    SR_GRAPH_GUI_NS::Immediate::Spring(0);
                }
                
                builder.EndInput();
            }
            
            // Отрисовываем выходные пины
            for (auto&& pPin : pNode->GetOutputs()) {
                builder.Output(pPin);
                
                SR_GRAPH_GUI_NS::Immediate::Spring(0);
                
                if (!pPin->GetName().empty()) {
                    SR_GRAPH_GUI_NS::Immediate::Text("%s", pPin->GetName().c_str());
                    SR_GRAPH_GUI_NS::Immediate::Spring(0);
                }
                
                // Получаем цвет и тип иконки пина
                auto&& pinType = pPin->GetType();
                auto&& iconType = SR_GRAPH_NS::GUI::Pin::GetIconType(pinType);
                auto&& pinColor = GetPinColor(pinType);
                auto&& isLinked = pPin->IsLinked();
                
                // Рисуем иконку пина
                SR_GRAPH_GUI_NS::Immediate::DrawPinIcon(
                    SR_MATH_NS::FVector2(24.0f, 24.0f),
                    iconType,
                    isLinked,
                    pinColor,
                    SR_MATH_NS::FColor(0.125f, 0.125f, 0.125f, 1.0f)
                );
                
                builder.EndOutput();
            }
            
            builder.End();

            // Active highlight: рисуем рамку вручную (node-editor стиль глобальный и не работает per-node)
            //if (activeNode) {
            //    if (void* dl = SR_GRAPH_GUI_NS::Immediate::GetNodeBackgroundDrawList(pNode->GetId())) {
            //        const auto min = SR_GRAPH_GUI_NS::Immediate::GetItemRectMin();
            //        const auto max = SR_GRAPH_GUI_NS::Immediate::GetItemRectMax();
            //        SR_GRAPH_GUI_NS::Immediate::DrawListAddRect(
            //            dl,
            //            min - SR_MATH_NS::FVector2(2.f, 2.f),
            //            max + SR_MATH_NS::FVector2(2.f, 2.f),
            //            SR_COL32(255, 170, 50, 255),
            //            6.0f,
            //            3.0f
            //        );
            //    }
            //}
        }

        // Отрисовываем все связи
        for (auto&& [id, pLink] : m_links) {
            if (pLink && pLink->IsLinked()) {
                if (m_activeGraphLinks.count(pLink->GetId()) == 1) {
                    SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleColor(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleColor::HighlightLinkBorder, SR_MATH_NS::FColor(0.25f, 1.0f, 0.35f, 1.0f));
                    SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleColor(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleColor::SelLinkBorder, SR_MATH_NS::FColor(0.25f, 1.0f, 0.35f, 1.0f));
                    SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::LinkStrength, 3.0f);
                    pLink->DrawBezier();
                    SR_GRAPH_GUI_NS::Immediate::PopNodeEditorStyleVar(1);
                    SR_GRAPH_GUI_NS::Immediate::PopNodeEditorStyleColor(2);
                }
                else {
                    pLink->DrawBezier();
                }
            }
        }

        if (editable) {
            // Обработка создания новых связей
            if (SR_GRAPH_GUI_NS::Immediate::BeginCreate()) {
                uintptr_t startPinId = 0, endPinId = 0;
                if (SR_GRAPH_GUI_NS::Immediate::QueryNewLink(&startPinId, &endPinId)) {
                    if (startPinId && endPinId) {
                        // Находим пины по ID
                        SR_GRAPH_GUI_NS::Pin* pStartPin = nullptr;
                        SR_GRAPH_GUI_NS::Pin* pEndPin = nullptr;

                        for (auto&& [nodeId, pNode] : m_nodes) {
                            for (auto&& pPin : pNode->GetInputs()) {
                                if (pPin->GetId() == startPinId || pPin->GetId() == endPinId) {
                                    if (pPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Input) {
                                        pEndPin = pPin;
                                    }
                                }
                            }
                            for (auto&& pPin : pNode->GetOutputs()) {
                                if (pPin->GetId() == startPinId || pPin->GetId() == endPinId) {
                                    if (pPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Output) {
                                        pStartPin = pPin;
                                    }
                                }
                            }
                        }

                        // Проверяем, что startPin - выходной, а endPin - входной
                        if (pStartPin && pEndPin &&
                            pStartPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Output &&
                            pEndPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Input &&
                            SR_GRAPH_GUI_NS::Immediate::AcceptNewItem()) {
                            auto&& pLink = new SR_GRAPH_GUI_NS::Link(pStartPin, pEndPin);
                            AddLink(pLink);
                            needsSync = true;
                        }
                    }
                }
            }
            SR_GRAPH_GUI_NS::Immediate::EndCreate();

            // Обработка удаления
            if (SR_GRAPH_GUI_NS::Immediate::BeginDelete()) {
                uintptr_t linkId = 0;
                while (SR_GRAPH_GUI_NS::Immediate::QueryDeletedLink(&linkId, nullptr, nullptr)) {
                    if (linkId) {
                        for (auto&& [id, pLink] : m_links) {
                            if (pLink->GetId() == linkId) {
                                RemoveLink(pLink);
                                needsSync = true;
                                break;
                            }
                        }
                    }
                }

                uintptr_t nodeId = 0;
                while (SR_GRAPH_GUI_NS::Immediate::QueryDeletedNode(&nodeId)) {
                    if (nodeId) {
                        for (auto&& [id, pNode] : m_nodes) {
                            if (pNode->GetId() == nodeId) {
                                if (m_context.pGraph) {
                                    auto&& pGraphNode = pNode->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>();
                                    m_context.pGraph->RemoveNode(pGraphNode);
                                }
                                RemoveNode(pNode);
                                needsSync = true;
                                break;
                            }
                        }
                    }
                }
            }
            SR_GRAPH_GUI_NS::Immediate::EndDelete();
        }

        // Даблклик по ноде стейт-машины открывает вкладку State Machine
        if (SR_GRAPH_GUI_NS::Immediate::IsMouseDoubleClicked(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left)) {
            const int selected = SR_GRAPH_GUI_NS::Immediate::GetSelectedNodes(nullptr, 0);
            if (selected > 0) {
                std::vector<uintptr_t> nodeIds(selected);
                SR_GRAPH_GUI_NS::Immediate::GetSelectedNodes(nodeIds.data(), selected);

                if (!nodeIds.empty()) {
                    if (auto&& it = m_nodes.find(nodeIds[0]); it != m_nodes.end()) {
                        auto&& pGraphNode = it->second->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>();
                        if (auto&& pSMNode = dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode)) {
                            m_context.openedStateMachineNodeIndex = pSMNode->GetIndex();
                            m_tab = Tab::StateMachine;
                            m_context.openStateMachineRequested = true; // синхронизацию делаем уже в DrawStateMachineEditor()
                        }
                    }
                }
            }
        }

        // Контекстное меню (dock-safe)
        if (editable) {
            SR_GRAPH_GUI_NS::Immediate::SuspendNodeEditor();
            if (SR_GRAPH_GUI_NS::Immediate::ShowBackgroundContextMenu()) {
                SR_GRAPH_GUI_NS::Immediate::OpenPopup("AnimatorEditor_Graph_Context");
                m_popupMousePos = SR_GRAPH_GUI_NS::Immediate::GetMousePos();
            }
            if (SR_GRAPH_GUI_NS::Immediate::BeginPopup("AnimatorEditor_Graph_Context")) {
                std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>> categories;
                BuildNodeMenu(categories);
                SR_GRAPH_GUI_NS::Immediate::InputText("##NodeSearch", &m_createNodeSearch);
                SR_GRAPH_GUI_NS::Immediate::Separator();
                DrawNodeMenuRecursive(categories, "");
                SR_GRAPH_GUI_NS::Immediate::EndPopup();
            }
            SR_GRAPH_GUI_NS::Immediate::ResumeNodeEditor();
        }

        SR_GRAPH_GUI_NS::Immediate::EndNodeEditor();
        SR_GRAPH_GUI_NS::Immediate::PopNodeEditorStyleVar(3);
        SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        if (needsSync) {
            SyncVisualNodesToGraph();
        }
    }

    void AnimatorEditor::DrawLeftPanel() {
        if (!m_context.pGraph) {
            return;
        }

        if (!m_propertyDrawer) {
            m_propertyDrawer = SRNew<SR_CORE_GUI_NS::ObjectPropertyDrawer>();
        }

        SR_GRAPH_GUI_NS::Immediate::Text("Properties");
        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_UTILS_NS::SRClass* pSelectedObject = nullptr;

        void* pEditor = (m_tab == Tab::Graph) ? m_editor : m_context.pStateMachineEditor;
        if (pEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(pEditor);

            const int selectedNodes = SR_GRAPH_GUI_NS::Immediate::GetSelectedNodes(nullptr, 0);

            if (selectedNodes > 0) {
                m_editorStateMachine.ResetSelectedLink();
                std::vector<uintptr_t> nodeIds(selectedNodes);
                SR_GRAPH_GUI_NS::Immediate::GetSelectedNodes(nodeIds.data(), selectedNodes);
                if (nodeIds.size() == 1) {
                    const uintptr_t nodeId = nodeIds[0];
                    if (m_tab == Tab::Graph) {
                        if (auto&& it = m_nodes.find(nodeId); it != m_nodes.end()) {
                            pSelectedObject = it->second->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>();
                        }
                    }
                    else {
                        pSelectedObject = m_editorStateMachine.GetSelectedNode(nodeId);
                    }
                }
            }
            else if (m_tab == Tab::StateMachine) {
                pSelectedObject = m_editorStateMachine.GetSelectedLink();
            }

            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
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

        if (m_context.isLive && m_context.liveReadOnly) {
            SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
            m_propertyDrawer->Draw(context);
            SR_GRAPH_GUI_NS::Immediate::EndDisabled();
        }
        else {
            m_propertyDrawer->Draw(context);
        }
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
    
    void AnimatorEditor::DrawNodeMenuRecursive(const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix) {
        // Группируем ноды по следующему уровню категорий
        std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>> subCategories;
        std::vector<SR_UTILS_NS::StringAtom> directNodes;

        for (auto&& [categoryPath, nodeTypes] : categories) {
            if (categoryPath == prefix) {
                // Ноды напрямую в этой категории
                directNodes.insert(directNodes.end(), nodeTypes.begin(), nodeTypes.end());
            }
            else if (prefix.empty() || (categoryPath.size() >= prefix.size() + 1 && categoryPath.substr(0, prefix.size() + 1) == prefix + "/")) {
                // Определяем следующий уровень
                std::string remaining = prefix.empty() ? categoryPath : categoryPath.substr(prefix.size() + 1);
                auto&& nextSlash = remaining.find('/');
                
                if (nextSlash == std::string::npos) {
                    // Это конечный уровень для этой категории
                    directNodes.insert(directNodes.end(), nodeTypes.begin(), nodeTypes.end());
                }
                else {
                    // Есть подкатегория
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
                if (m_context.pGraph) {
                    // Создаем ноду через Factory
                    if (auto&& pNode = SR_UTILS_NS::Factory::Instance().Create<SR_ANIMATIONS_NS::AnimationGraphNode>(nodeTypeName)) {
                        auto&& pGraphNode = m_context.pGraph->AddNode(pNode.Get());
                        auto&& pVisualNode = CreateVisualNode(pGraphNode);

                        auto&& pos = SR_GRAPH_GUI_NS::Immediate::ScreenToCanvas(m_popupMousePos);
                        SR_GRAPH_GUI_NS::Immediate::SetNodePosition(pVisualNode->GetId(), pos);
                    }
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
                DrawNodeMenuRecursive(categories, nextLevel);
                SR_GRAPH_GUI_NS::Immediate::EndMenu();
            }
        }
    }

    void AnimatorEditor::DrawPopupMenu() {

    }

    void AnimatorEditor::SyncGraphToVisualNodes() {
        if (!m_context.pGraph) {
            return;
        }

        // Очищаем существующие визуальные ноды
        Clear();

        // Создаем визуальные ноды для каждой граф-ноды
        for (auto&& pGraphNode : m_context.pGraph->GetNodes()) {
            if (pGraphNode) {
                auto&& pVisualNode = CreateVisualNode(pGraphNode.Get());
                if (m_editor) {
                    SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_editor);
                    SR_GRAPH_GUI_NS::Immediate::SetNodePosition(pVisualNode->GetId(), pGraphNode->GetEditorPosition());
                    SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
                }
            }
        }

        // Создаем связи
        for (auto&& pGraphNode : m_context.pGraph->GetNodes()) {
            if (!pGraphNode) {
                continue;
            }

            auto&& destIndex = pGraphNode->GetIndex();
            auto&& pDestVisual = m_context.pGraph->GetNode(destIndex)->GetUserData<SR_GRAPH_GUI_NS::Node>();

            auto&& inputs = pGraphNode->GetInputLinks();
            for (uint32_t inputIndex = 0; inputIndex < inputs.size(); ++inputIndex) {
                auto&& link = inputs[inputIndex];
                if (!link.IsConnected()) {
                    continue;
                }

                auto&& srcIndex = static_cast<uint64_t>(link.m_targetNodeIndex);
                auto&& pSrcVisual = m_context.pGraph->GetNode(srcIndex)->GetUserData<SR_GRAPH_GUI_NS::Node>();

                if (link.m_targetPinIndex >= pSrcVisual->GetOutputs().size()) {
                    continue;
                }
                if (inputIndex >= pDestVisual->GetInputs().size()) {
                    continue;
                }

                auto&& pStartPin = pSrcVisual->GetOutputs().at(link.m_targetPinIndex);
                auto&& pEndPin = pDestVisual->GetInputs().at(inputIndex);

                auto&& pVisualLink = new SR_GRAPH_GUI_NS::Link(pStartPin, pEndPin);
                AddLink(pVisualLink);
            }
        }
    }

    void AnimatorEditor::SyncVisualNodesToGraph() {
        if (!m_context.pGraph) {
            return;
        }

        if (m_editor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_editor);
        }

        // Сохраняем позиции визуальных нод в данные графа
        for (auto&& [nodeId, pVisualNode] : m_nodes) {
            if (m_editor) {
                auto&& pGraphNode = pVisualNode->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>();
                pGraphNode->SetEditorPosition(SR_GRAPH_GUI_NS::Immediate::GetNodePosition(pVisualNode->GetId()));
            }
        }

        // Сбрасываем старые подключения (полный ребилд по визуальным links)
        for (auto&& pGraphNode : m_context.pGraph->GetNodes()) {
            if (!pGraphNode) {
                continue;
            }

            const uint32_t inputCount = pGraphNode->GetInputCount();
            const uint32_t outputCount = pGraphNode->GetOutputCount();

            pGraphNode->ClearInputPins();
            pGraphNode->ClearOutputPins();

            for (uint32_t i = 0; i < inputCount; ++i) {
                pGraphNode->AddInputPin(SR_ANIMATIONS_NS::AnimationLink());
            }
            for (uint32_t i = 0; i < outputCount; ++i) {
                pGraphNode->AddOutputPin(SR_ANIMATIONS_NS::AnimationLink());
            }
        }

        // Обновляем связи в графе на основе визуальных связей
        for (auto&& [linkId, pLink] : m_links) {
            if (!pLink || !pLink->IsLinked()) {
                continue;
            }

            auto&& pStartPin = pLink->GetStart();
            auto&& pEndPin = pLink->GetEnd();
            
            if (!pStartPin || !pEndPin) {
                continue;
            }

            auto&& pStartNode = pStartPin->GetNode();
            auto&& pEndNode = pEndPin->GetNode();

            auto&& pStartGraphNode = pStartNode->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>();
            auto&& pEndGraphNode = pEndNode->GetUserData<SR_ANIMATIONS_NS::AnimationGraphNode>();

            if (!pStartGraphNode || !pEndGraphNode) {
                continue;
            }

            auto&& startPinIndex = pStartNode->GetPinIndex(pStartPin);
            auto&& endPinIndex = pEndNode->GetPinIndex(pEndPin);

            // Проверяем валидность индексов
            if (startPinIndex == SR_ID_INVALID || endPinIndex == SR_ID_INVALID) {
                continue;
            }

            // Нормализуем направление (output -> input)
            if (pStartPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Input && pEndPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Output) {
                std::swap(pStartPin, pEndPin);
                std::swap(pStartNode, pEndNode);
                std::swap(pStartGraphNode, pEndGraphNode);
                std::swap(startPinIndex, endPinIndex);
            }

            if (pStartPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Output &&
                pEndPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Input) {
                pStartGraphNode->ConnectTo(pEndGraphNode, static_cast<uint16_t>(startPinIndex), static_cast<uint16_t>(endPinIndex));
            }
        }

        if (m_editor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        }
    }

    SR_GRAPH_GUI_NS::Node* AnimatorEditor::CreateVisualNode(SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode) {
        if (!pGraphNode) {
            return nullptr;
        }

        // Получаем имя ноды из метаинформации
        std::string nodeName = "Node";
        if (auto&& pMeta = pGraphNode->GetMeta()) {
            auto&& displayName = pMeta->GetDisplayName();
            if (!displayName.empty()) {
                nodeName = displayName;
            }
            else {
                auto&& factoryName = SR_UTILS_NS::Factory::Instance().GetName(pMeta, false);
                if (!factoryName.empty()) {
                    nodeName = factoryName.ToStringRef();
                }
            }
        }

        auto&& pNode = new SR_GRAPH_GUI_NS::Node();
        pNode->SetName(nodeName);
        pNode->SetUserData(pGraphNode);

        pGraphNode->SetUserData(pNode);

        // Создаем входные пины
        for (uint32_t i = 0; i < pGraphNode->GetInputCount(); ++i) {
            auto&& pPin = new SR_GRAPH_GUI_NS::Pin("Input " + std::to_string(i), SR_GRAPH_GUI_NS::PinKind::Input);
            pNode->AddInput(pPin);
        }

        // Создаем выходные пины
        for (uint32_t i = 0; i < pGraphNode->GetOutputCount(); ++i) {
            auto&& pPin = new SR_GRAPH_GUI_NS::Pin("Output " + std::to_string(i), SR_GRAPH_GUI_NS::PinKind::Output);
            pNode->AddOutput(pPin);
        }

        AddNode(pNode);
        return pNode;
    }

    void AnimatorEditor::TopPanelSave() {
        if (!m_context.pGraph) {
            return;
        }

        if (m_graphPath.IsEmpty()) {
            TopPanelSaveAt();
            return;
        }

        m_currentFile = m_graphPath;

        // Синхронизируем визуальные изменения с графом
        SyncVisualNodesToGraph();
        m_editorStateMachine.SyncVisualToStateMachine();

        if (m_context.isLive && m_context.liveReadOnly) {
            return;
        }

        // Кладём изменения обратно в ассет (мы редактируем клон)
        if (m_graphAsset) {
            m_context.pGraph->CloneTo(m_graphAsset->GetDataMutable());
        }

        // Сохраняем ассет
        if (auto&& pAsset = m_graphAsset ? m_graphAsset.Get() : (m_asset ? m_asset.Get() : m_context.pGraph->GetAsset())) {
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
        if (!m_editor) {
            static auto&& settingsPath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/AnimatorEditor.json");
            m_editor = SR_GRAPH_GUI_NS::Immediate::CreateEditor(settingsPath.CStr());
        }
        if (!m_context.pStateMachineEditor) {
            static auto&& smSettingsPath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/AnimatorStateMachineEditor.json");
            m_context.pStateMachineEditor = SR_GRAPH_GUI_NS::Immediate::CreateEditor(smSettingsPath.CStr());
        }
        if (m_context.pGraph) {
            SyncGraphToVisualNodes();
        }
        Super::OnOpen();
    }

    void AnimatorEditor::Zoom() {
        if (m_tab == Tab::StateMachine) {
            if (m_context.pStateMachineEditor) {
                SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_context.pStateMachineEditor);
                SR_GRAPH_GUI_NS::Immediate::NavigateToContent();
                SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
            }
        }
        else {
            if (m_editor) {
                SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_editor);
                SR_GRAPH_GUI_NS::Immediate::NavigateToContent();
                SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
            }
        }
        Super::Zoom();
    }
}

