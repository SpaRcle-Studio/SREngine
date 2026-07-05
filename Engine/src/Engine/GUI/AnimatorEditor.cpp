//
// Created by Monika on 14.01.2023.
//

#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/AnimatorEditor.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>
#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawer.h>

#include <Graphics/Animations/Animator.h>
#include <Graphics/Animations/AnimationGraphNode.h>
#include <Graphics/Animations/AnimationState.h>
#include <Graphics/Animations/AnimationStateMachine.h>
#include <Graphics/Animations/AnimationStateCondition.h>
#include <Graphics/GUI/WidgetManager.h>
#include <Graphics/GUI/Node.h>
#include <Graphics/GUI/Link.h>
#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/NodeBuilder.h>
#include <Graphics/GUI/ImmediateGUI.h>

#include <Utils/Resources/ResourceManager.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/Events/Broadcaster.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/Reflection/Value.h>

#include <functional>
#include <cmath>
#include <algorithm>

#include <Codegen/AnimatorEditor.generated.hpp>

namespace SR_CORE_GUI_NS {
    AnimatorEditor::AnimatorEditor()
        : Super("Animator")
    { }

    void AnimatorEditor::Init() {
        Super::Init();
        InitNodeTypes();
        InitStateTypes();

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
                m_isLive = true;

                if (auto&& pGraph = pAnimator->GetGraph()) {
                    m_runtimeGraph = pGraph;
                    m_keepLiveContext = true;
                    Inspect(pAnimator->GetGraphPath());
                    m_keepLiveContext = false;
                    m_animator = pAnimator;
                    m_isLive = true;
                }
                else {
                    Inspect(pAnimator->GetGraphPath());
                }
            }
        });
    }

    void AnimatorEditor::OnClose() {
    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_editor) {
            SR_GRAPH_GUI_NS::Immediate::DestroyEditor(m_editor);
            m_editor = nullptr;
        }
        if (m_stateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::DestroyEditor(m_stateMachineEditor);
            m_stateMachineEditor = nullptr;
        }
    #endif
        ClearStateMachineVisual();

        Super::OnClose();
    }

    void AnimatorEditor::Inspect(const SR_UTILS_NS::Path& path) {
        if (!m_keepLiveContext) {
            m_animator.Reset();
            m_isLive = false;
            m_runtimeGraph = nullptr;
        }

        m_graphPath = path;
        m_graph.Reset();
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
            m_graph = new SR_GRAPH_NS::Animations::AnimationGraph();
            pAsset->GetData().CloneTo(*m_graph);
            m_graph->SetAsset(pAsset.Get());
            
            // Синхронизируем визуальные ноды с данными графа
            SyncGraphToVisualNodes();
        }
        else {
            SR_ERROR("AnimatorEditor::SetGraphPath() : failed to load animation graph asset: {}", loadPath);
        }
    }

    void AnimatorEditor::Draw() {
        if (!m_graph) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Red(), "No animator loaded!");
            return;
        }

        DrawTopPanel();

        if (m_isLive) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::Checkbox("Read-only (Live)", &m_liveReadOnly);
        }
        
        SR_GRAPH_GUI_NS::Immediate::Separator();
        
        // Разделяем окно на левую панель и редактор
        auto&& availableSize = SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail();
        
        // Левая панель для свойств
        SR_GRAPH_GUI_NS::Immediate::BeginChild("LeftPanel", SR_MATH_NS::FVector2(m_leftPaneWidth, availableSize.y), false);
        DrawLeftPanel();
        SR_GRAPH_GUI_NS::Immediate::EndChild();
        
        SR_GRAPH_GUI_NS::Immediate::SameLine();
        
        // Редактор графа
        SR_GRAPH_GUI_NS::Immediate::BeginChild("NodeEditor", SR_MATH_NS::FVector2(availableSize.x - m_leftPaneWidth - 10, availableSize.y), false);
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
            DrawStateMachineEditor();
        }
    }

    void AnimatorEditor::DrawGraphEditor() {
        bool needsSync = false;

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (!m_editor) {
            return;
        }

        const bool editable = !(m_isLive && m_liveReadOnly);

        SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_editor);
        SR_GRAPH_GUI_NS::Immediate::Begin("Animation Graph Editor", SR_MATH_NS::FVector2());

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

        auto* pTraceGraph = (m_isLive && m_runtimeGraph) ? m_runtimeGraph : (m_graph ? m_graph.Get() : nullptr);

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

                auto&& startIt = m_visualToGraphNode.find(pStartNode);
                auto&& endIt = m_visualToGraphNode.find(pEndNode);
                if (startIt == m_visualToGraphNode.end() || endIt == m_visualToGraphNode.end()) {
                    continue;
                }

                const uint64_t startIndex = startIt->second;
                const uint64_t endIndex = endIt->second;

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

            const bool activeNode =
                m_isLive &&
                (m_visualToGraphNode.count(pNode) == 1) &&
                (m_activeGraphNodes.count(m_visualToGraphNode.at(pNode)) == 1);

            // Получаем цвет заголовка на основе типа ноды
            SR_MATH_NS::FColor headerColor = SR_MATH_NS::FColor(0.2f, 0.6f, 0.84f, 1.0f); // Синий по умолчанию
            if (auto&& graphNodeIt = m_visualToGraphNode.find(pNode); graphNodeIt != m_visualToGraphNode.end()) {
                if (auto&& pGraphNode = m_graph->GetNode(graphNodeIt->second)) {
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
                    }

                    // Active nodes will be highlighted by border (below), not by header tint.
                }
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
            if (activeNode) {
                if (void* dl = SR_GRAPH_GUI_NS::Immediate::GetNodeBackgroundDrawList(pNode->GetId())) {
                    const auto min = SR_GRAPH_GUI_NS::Immediate::GetItemRectMin();
                    const auto max = SR_GRAPH_GUI_NS::Immediate::GetItemRectMax();
                    SR_GRAPH_GUI_NS::Immediate::DrawListAddRect(
                        dl,
                        min - SR_MATH_NS::FVector2(2.f, 2.f),
                        max + SR_MATH_NS::FVector2(2.f, 2.f),
                        SR_COL32(255, 170, 50, 255),
                        6.0f,
                        3.0f
                    );
                }
            }
        }

        // Отрисовываем все связи
        for (auto&& [id, pLink] : m_links) {
            if (pLink && pLink->IsLinked()) {
                if (m_activeGraphLinks.count(pLink->GetId()) == 1) {
                    SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleColor(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleColor::HighlightLinkBorder, SR_MATH_NS::FColor(0.25f, 1.0f, 0.35f, 1.0f));
                    SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleColor(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleColor::SelLinkBorder, SR_MATH_NS::FColor(0.25f, 1.0f, 0.35f, 1.0f));
                    SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::LinkStrength, 3.0f);
                    pLink->Draw();
                    SR_GRAPH_GUI_NS::Immediate::PopNodeEditorStyleVar(1);
                    SR_GRAPH_GUI_NS::Immediate::PopNodeEditorStyleColor(2);
                }
                else {
                    pLink->Draw();
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
                        if (auto&& graphNodeIt = m_visualToGraphNode.find(it->second); graphNodeIt != m_visualToGraphNode.end()) {
                            if (auto&& pGraphNode = m_graph->GetNode(graphNodeIt->second)) {
                                if (auto&& pSMNode = dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode)) {
                                    m_openedStateMachineNodeIndex = pSMNode->GetIndex();
                                    m_tab = Tab::StateMachine;
                                    m_openStateMachineRequested = true; // синхронизацию делаем уже в DrawStateMachineEditor()
                                }
                            }
                        }
                    }
                }
            }
        }

        // Контекстное меню (dock-safe)
        if (editable) {
            if (SR_GRAPH_GUI_NS::Immediate::ShowBackgroundContextMenu()) {
                SR_GRAPH_GUI_NS::Immediate::OpenPopup("AnimatorEditor_Graph_Context");
            }
            if (SR_GRAPH_GUI_NS::Immediate::BeginPopup("AnimatorEditor_Graph_Context")) {
                std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>> categories;
                BuildNodeMenu(categories);
                SR_GRAPH_GUI_NS::Immediate::InputText("##NodeSearch", &m_createNodeSearch);
                SR_GRAPH_GUI_NS::Immediate::Separator();
                DrawNodeMenuRecursive(categories, "");
                SR_GRAPH_GUI_NS::Immediate::EndPopup();
            }
        }

        SR_GRAPH_GUI_NS::Immediate::EndNodeEditor();
        SR_GRAPH_GUI_NS::Immediate::PopNodeEditorStyleVar(3);
        SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        if (needsSync) {
            SyncVisualNodesToGraph();
        }
    #endif
    }

    void AnimatorEditor::DrawLeftPanel() {
        if (!m_graph) {
            return;
        }

        if (!m_propertyDrawer) {
            m_propertyDrawer = SRNew<SR_CORE_GUI_NS::ObjectPropertyDrawer>();
        }

        SR_GRAPH_GUI_NS::Immediate::Text("Properties");
        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_UTILS_NS::SRClass* pSelectedObject = nullptr;

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        void* pEditor = (m_tab == Tab::Graph) ? m_editor : m_stateMachineEditor;
        if (pEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(pEditor);

            const int selectedNodes = SR_GRAPH_GUI_NS::Immediate::GetSelectedNodes(nullptr, 0);
            if (selectedNodes > 0) {
                std::vector<uintptr_t> nodeIds(selectedNodes);
                SR_GRAPH_GUI_NS::Immediate::GetSelectedNodes(nodeIds.data(), selectedNodes);

                if (!nodeIds.empty()) {
                    const uintptr_t nodeId = nodeIds[0];

                    if (m_tab == Tab::Graph) {
                        if (auto&& it = m_nodes.find(nodeId); it != m_nodes.end()) {
                            if (auto&& graphNodeIt = m_visualToGraphNode.find(it->second); graphNodeIt != m_visualToGraphNode.end()) {
                                pSelectedObject = m_graph->GetNode(graphNodeIt->second);
                            }
                        }
                    }
                    else {
                        if (auto&& it = m_smNodes.find(nodeId); it != m_smNodes.end()) {
                            if (auto&& idxIt = m_visualToStateIndex.find(it->second); idxIt != m_visualToStateIndex.end()) {
                                auto&& pGraphNode = m_graph->GetNode(m_openedStateMachineNodeIndex);
                                auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
                                if (pSMNode && pSMNode->GetMachine()) {
                                    pSelectedObject = pSMNode->GetMachine()->GetStateOrNull(idxIt->second);
                                }
                            }
                        }
                    }
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        }
    #endif

        if (!pSelectedObject) {
            if (m_tab == Tab::Graph) {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.7f, 0.7f, 0.7f, 1.0f), "Select a graph node to edit its properties.");
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

        if (m_isLive && m_liveReadOnly) {
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

    void AnimatorEditor::InitStateTypes() {
        m_availableStateTypes = SR_UTILS_NS::Factory::Instance().GetInheritances(
            SR_ANIMATIONS_NS::AnimationState::GetClassStaticName()
        );

        std::erase_if(m_availableStateTypes, [](auto&& name) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(name);
            if (!pMeta) {
                return true;
            }
            return pMeta->IsAbstract() || pMeta->IsHidden();
        });
    }

    void AnimatorEditor::BuildStateMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories) {
        categories.clear();

        for (auto&& stateTypeName : m_availableStateTypes) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(stateTypeName);
            if (!pMeta) {
                continue;
            }

            auto&& category = pMeta->GetCategory();
            std::string categoryPath = "States";
            if (!category.empty()) {
                categoryPath.clear();
                for (size_t i = 0; i < category.size(); ++i) {
                    if (i > 0) {
                        categoryPath += "/";
                    }
                    categoryPath += category[i].ToStringRef();
                }
            }

            categories[categoryPath].emplace_back(stateTypeName);
        }
    }

    void AnimatorEditor::DrawStateMenuRecursive(bool& needResync, const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix) {
        std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>> subCategories;
        std::vector<SR_UTILS_NS::StringAtom> directStates;

        for (auto&& [categoryPath, stateTypes] : categories) {
            if (categoryPath == prefix) {
                directStates.insert(directStates.end(), stateTypes.begin(), stateTypes.end());
            }
            else if (prefix.empty() || (categoryPath.size() >= prefix.size() + 1 && categoryPath.substr(0, prefix.size() + 1) == prefix + "/")) {
                std::string remaining = prefix.empty() ? categoryPath : categoryPath.substr(prefix.size() + 1);
                auto&& nextSlash = remaining.find('/');

                if (nextSlash == std::string::npos) {
                    directStates.insert(directStates.end(), stateTypes.begin(), stateTypes.end());
                }
                else {
                    std::string nextLevel = prefix.empty() ? remaining.substr(0, nextSlash) : prefix + "/" + remaining.substr(0, nextSlash);
                    subCategories[nextLevel].insert(subCategories[nextLevel].end(), stateTypes.begin(), stateTypes.end());
                }
            }
        }

        for (auto&& stateTypeName : directStates) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(stateTypeName);
            if (!pMeta) {
                continue;
            }

            auto&& displayName = pMeta->GetDisplayName();
            SR_UTILS_NS::StringAtom menuName = displayName.empty() ? stateTypeName : displayName;

            if (!m_createStateSearch.empty() && !SR_CORE_GUI_NS::PropertyDrawerBase::CheckSearchMatch(m_createStateSearch, menuName.ToStringView())) {
                continue;
            }

            if (SR_GRAPH_GUI_NS::Immediate::MenuItem(menuName.c_str())) {
                if (!m_graph || m_openedStateMachineNodeIndex == SR_ID_INVALID) {
                    continue;
                }

                auto&& pGraphNode = m_graph->GetNode(m_openedStateMachineNodeIndex);
                auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
                if (!pSMNode || !pSMNode->GetMachine()) {
                    continue;
                }

                auto&& pMachine = pSMNode->GetMachine();

                if (auto&& pState = SR_UTILS_NS::Factory::Instance().Create<SR_ANIMATIONS_NS::AnimationState>(stateTypeName)) {
                    auto&& mousePos = SR_GRAPH_GUI_NS::Immediate::GetMousePos();
                    auto&& pos = SR_GRAPH_GUI_NS::Immediate::ScreenToCanvas(mousePos);
                    pState->SetEditorPosition(pos);
                    pMachine->AddState(pState.Get());

                    m_graph->InvalidateCompile();
                    needResync = true;
                }
            }
        }

        for (auto&& [nextLevel, stateTypes] : subCategories) {
            std::string levelName = nextLevel;
            if (!prefix.empty()) {
                levelName = nextLevel.substr(prefix.size() + 1);
            }
            auto&& nextSlash = levelName.find('/');
            if (nextSlash != std::string::npos) {
                levelName = levelName.substr(0, nextSlash);
            }

            if (SR_GRAPH_GUI_NS::Immediate::BeginMenu(levelName.c_str())) {
                DrawStateMenuRecursive(needResync, categories, nextLevel);
                SR_GRAPH_GUI_NS::Immediate::EndMenu();
            }
        }
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
                if (m_graph) {
                    // Создаем ноду через Factory
                    if (auto&& pNode = SR_UTILS_NS::Factory::Instance().Create<SR_ANIMATIONS_NS::AnimationGraphNode>(nodeTypeName)) {
                        auto&& pGraphNode = m_graph->AddNode(pNode.Get());
                        auto&& pVisualNode = CreateVisualNode(pGraphNode);
                        AddNode(pVisualNode);
                        
                        auto&& mousePos = SR_GRAPH_GUI_NS::Immediate::GetMousePos();
                        auto&& pos = SR_GRAPH_GUI_NS::Immediate::ScreenToCanvas(mousePos);
                        SR_GRAPH_GUI_NS::Immediate::SetNodePosition(pVisualNode->GetId(), pos);
                        
                        // Обновляем маппинг
                        auto&& nodeIndex = pGraphNode->GetIndex();
                        m_graphNodeToVisual[nodeIndex] = pVisualNode;
                        m_visualToGraphNode[pVisualNode] = nodeIndex;
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
    #ifdef SR_USE_IMGUI_NODE_EDITOR
        // Deprecated: context menu is handled via BeginPopupContextWindow inside DrawGraphEditor/DrawStateMachineEditor.
    #endif
    }

    void AnimatorEditor::SyncGraphToVisualNodes() {
        if (!m_graph) {
            return;
        }

        // Очищаем существующие визуальные ноды
        Clear();
        m_graphNodeToVisual.clear();
        m_visualToGraphNode.clear();

        // Создаем визуальные ноды для каждой граф-ноды
        for (auto&& pGraphNode : m_graph->GetNodes()) {
            if (pGraphNode) {
                auto&& pVisualNode = CreateVisualNode(pGraphNode.Get());
                AddNode(pVisualNode);
                
                auto&& nodeIndex = pGraphNode->GetIndex();
                m_graphNodeToVisual[nodeIndex] = pVisualNode;
                m_visualToGraphNode[pVisualNode] = nodeIndex;

            #ifdef SR_USE_IMGUI_NODE_EDITOR
                if (m_editor) {
                    SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_editor);
                    SR_GRAPH_GUI_NS::Immediate::SetNodePosition(pVisualNode->GetId(), pGraphNode->GetEditorPosition());
                    SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
                }
            #endif
            }
        }

        // Создаем связи
        for (auto&& pGraphNode : m_graph->GetNodes()) {
            if (!pGraphNode) {
                continue;
            }

            auto&& destIndex = pGraphNode->GetIndex();
            auto&& destVisualIt = m_graphNodeToVisual.find(destIndex);
            if (destVisualIt == m_graphNodeToVisual.end()) {
                continue;
            }

            auto&& pDestVisual = destVisualIt->second;
            auto&& inputs = pGraphNode->GetInputLinks();
            for (uint32_t inputIndex = 0; inputIndex < inputs.size(); ++inputIndex) {
                auto&& link = inputs[inputIndex];
                if (!link.IsConnected()) {
                    continue;
                }

                auto&& srcIndex = static_cast<uint64_t>(link.m_targetNodeIndex);
                auto&& srcVisualIt = m_graphNodeToVisual.find(srcIndex);
                if (srcVisualIt == m_graphNodeToVisual.end()) {
                    continue;
                }

                auto&& pSrcVisual = srcVisualIt->second;

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
        if (!m_graph) {
            return;
        }

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_editor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_editor);
        }
    #endif

        // Сохраняем позиции визуальных нод в данные графа
        for (auto&& [graphIndex, pVisualNode] : m_graphNodeToVisual) {
            if (!pVisualNode) {
                continue;
            }
            if (auto&& pGraphNode = m_graph->GetNode(graphIndex)) {
            #ifdef SR_USE_IMGUI_NODE_EDITOR
                if (m_editor) {
                    pGraphNode->SetEditorPosition(SR_GRAPH_GUI_NS::Immediate::GetNodePosition(pVisualNode->GetId()));
                }
            #endif
            }
        }

        // Сбрасываем старые подключения (полный ребилд по визуальным links)
        for (auto&& pGraphNode : m_graph->GetNodes()) {
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

            auto&& startGraphIt = m_visualToGraphNode.find(pStartNode);
            auto&& endGraphIt = m_visualToGraphNode.find(pEndNode);

            if (startGraphIt == m_visualToGraphNode.end() || endGraphIt == m_visualToGraphNode.end()) {
                continue;
            }

            auto&& pStartGraphNode = m_graph->GetNode(startGraphIt->second);
            auto&& pEndGraphNode = m_graph->GetNode(endGraphIt->second);

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

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_editor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        }
    #endif
    }

    void AnimatorEditor::ClearStateMachineVisual() {
        for (auto&& [id, pLink] : m_smLinks) {
            delete pLink;
        }
        for (auto&& [id, pNode] : m_smNodes) {
            delete pNode;
        }
        m_smLinks.clear();
        m_smNodes.clear();
        m_stateIndexToVisual.clear();
        m_visualToStateIndex.clear();
        m_smLinkToTransition.clear();
        m_smNodeRects.clear();
    }

    void AnimatorEditor::SyncStateMachineToVisual() {
        ClearStateMachineVisual();

        if (!m_graph || m_openedStateMachineNodeIndex == SR_ID_INVALID) {
            return;
        }

        auto&& pGraphNode = m_graph->GetNode(m_openedStateMachineNodeIndex);
        auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
        if (!pSMNode) {
            return;
        }

        auto&& pMachine = pSMNode->GetMachine();
        if (!pMachine) {
            return;
        }

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_stateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_stateMachineEditor);
        }
    #endif

        // States -> visual nodes (без пинов)
        auto&& states = pMachine->GetStates();
        for (uint32_t stateIndex = 0; stateIndex < states.size(); ++stateIndex) {
            auto&& pState = states[stateIndex];
            if (!pState) {
                continue;
            }

            auto&& pNode = new SR_GRAPH_GUI_NS::Node();
            pNode->SetName(pState->GetStateName().c_str());

            m_smNodes[pNode->GetId()] = pNode;
            m_stateIndexToVisual[stateIndex] = pNode;
            m_visualToStateIndex[pNode] = stateIndex;

        #ifdef SR_USE_IMGUI_NODE_EDITOR
            if (m_stateMachineEditor) {
                SR_GRAPH_GUI_NS::Immediate::SetNodePosition(pNode->GetId(), pState->GetEditorPosition());
            }
        #endif
        }

        // Транзишены рисуем кастомно, без node-editor links

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_stateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        }
    #endif
    }

    void AnimatorEditor::SyncVisualToStateMachine() {
        if (!m_graph || m_openedStateMachineNodeIndex == SR_ID_INVALID) {
            return;
        }

        auto&& pGraphNode = m_graph->GetNode(m_openedStateMachineNodeIndex);
        auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
        if (!pSMNode || !pSMNode->GetMachine()) {
            return;
        }

        auto&& pMachine = pSMNode->GetMachine();

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_stateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_stateMachineEditor);
        }
    #endif

        for (auto&& [stateIndex, pVisualNode] : m_stateIndexToVisual) {
            if (!pVisualNode) {
                continue;
            }

            if (auto&& pState = pMachine->GetStateOrNull(stateIndex)) {
            #ifdef SR_USE_IMGUI_NODE_EDITOR
                if (m_stateMachineEditor) {
                    pState->SetEditorPosition(SR_GRAPH_GUI_NS::Immediate::GetNodePosition(pVisualNode->GetId()));
                }
            #endif
            }
        }

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_stateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        }
    #endif
    }

    void AnimatorEditor::DrawStateMachineEditor() {
    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (!m_stateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Red(), "State machine editor is not initialized!");
            return;
        }

        if (!m_graph || m_openedStateMachineNodeIndex == SR_ID_INVALID) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.7f, 0.7f, 0.7f, 1.0f), "No state machine selected. Double-click the state machine node in Graph.");
            return;
        }

        auto&& pGraphNode = m_graph->GetNode(m_openedStateMachineNodeIndex);
        auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
        if (!pSMNode || !pSMNode->GetMachine()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Red(), "Invalid state machine node!");
            return;
        }

        if (m_openStateMachineRequested) {
            SyncStateMachineToVisual();
            m_openStateMachineRequested = false;
        }

        // UI сверху (не в canvas), чтобы прогресс не “плавал”
        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.6f, 0.6f, 0.6f, 1.0f), "Graph > State Machine");

        // Live: progress bar for active animation state (привязан к текущему ImGui окну)
        if (m_isLive && m_runtimeGraph) {
            if (auto&& pRuntimeNode = m_runtimeGraph->GetNode(m_openedStateMachineNodeIndex)) {
                if (auto&& pRuntimeSM = dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pRuntimeNode)) {
                    if (auto&& pRuntimeMachine = pRuntimeSM->GetMachine()) {
                        float progress = -1.f;
                        for (uint32_t i = 0; i < pRuntimeMachine->GetStates().size(); ++i) {
                            if (auto&& pState = pRuntimeMachine->GetStateOrNull(i)) {
                                if (!pRuntimeMachine->IsStateActive(pState->GetStateName())) {
                                    continue;
                                }
                                progress = pState->GetProgress();
                                if (progress < 0.f || progress > 1.f) {
                                    const float dur = pState->GetDuration();
                                    const float t = pState->GetTime();
                                    progress = dur > 0.f ? (t / dur) : 0.f;
                                }
                                progress = std::clamp(progress, 0.f, 1.f);
                                break;
                            }
                        }

                        if (progress >= 0.f) {
                            const SR_MATH_NS::FVector2 pos = SR_GRAPH_GUI_NS::Immediate::GetCursorScreenPos();
                            const SR_MATH_NS::FVector2 avail = SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail();
                            const float h = 6.0f;

                            if (void* dl = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList()) {
                                SR_GRAPH_GUI_NS::Immediate::DrawListAddRectFilled(
                                    dl,
                                    pos,
                                    pos + SR_MATH_NS::FVector2(avail.x, h),
                                    SR_COL32(70, 70, 70, 200),
                                    2.0f
                                );
                                SR_GRAPH_GUI_NS::Immediate::DrawListAddRectFilled(
                                    dl,
                                    pos,
                                    pos + SR_MATH_NS::FVector2(avail.x * progress, h),
                                    SR_COL32(60, 220, 110, 240),
                                    2.0f
                                );
                            }

                            SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(avail.x, h + 6.0f));
                        }
                    }
                }
            }
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_stateMachineEditor);
        SR_GRAPH_GUI_NS::Immediate::Begin("Animation State Machine", SR_MATH_NS::FVector2());

        SR_GRAPH_GUI_NS::NodeBuilder builder(nullptr);

        SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::SourceDirection, SR_MATH_NS::FVector2(1.0f, 0.0f));
        SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::TargetDirection, SR_MATH_NS::FVector2(-1.0f, 0.0f));
        SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::SnapLinkToPinDir, 1.0f);

        auto&& pMachine = pSMNode->GetMachine();
        bool needResync = false;
        const bool editable = !(m_isLive && m_liveReadOnly);

        // draw states
        for (auto&& [id, pNode] : m_smNodes) {
            if (!pNode) {
                continue;
            }

            SR_MATH_NS::FColor headerColor = SR_MATH_NS::FColor(0.55f, 0.35f, 0.85f, 1.0f);
            if (auto&& it = m_visualToStateIndex.find(pNode); it != m_visualToStateIndex.end()) {
                const uint32_t stateIndex = it->second;
                if (auto&& pState = pMachine->GetStateOrNull(stateIndex)) {
                    if (pMachine->IsStateActive(pState->GetStateName())) {
                        headerColor = SR_MATH_NS::FColor(0.18f, 0.55f, 0.25f, 1.0f);
                    }
                }
            }

            builder.Begin(pNode);
            builder.Header(headerColor);
            SR_GRAPH_GUI_NS::Immediate::Spring(0);
            auto&& it = m_visualToStateIndex.find(pNode);
            const bool isActive = (it != m_visualToStateIndex.end())
                ? (pMachine->GetStateOrNull(it->second) ? pMachine->IsStateActive(pMachine->GetStateOrNull(it->second)->GetStateName()) : false)
                : false;
            if (isActive) {
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, SR_MATH_NS::FColor(0.05f, 0.05f, 0.05f, 1.0f));
            }
            SR_GRAPH_GUI_NS::Immediate::Text("%s", pNode->GetName().c_str());
            if (isActive) {
                SR_GRAPH_GUI_NS::Immediate::PopStyleColor(1);
            }

            // node context menu: create/delete transitions (no pins, Unity-like)
            if (editable && it != m_visualToStateIndex.end()) {
                const uint32_t srcIndex = it->second;
                SR_GRAPH_GUI_NS::Immediate::PushID(static_cast<int>(srcIndex));
                if (SR_GRAPH_GUI_NS::Immediate::BeginPopupContextItem("AnimatorEditor_SM_NodeContext")) {
                    if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Create transition (click target)")) {
                        m_smCreateTransitionFrom = static_cast<int32_t>(srcIndex);
                    }

                    if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Add transition")) {
                        auto&& states = pMachine->GetStates();
                        for (uint32_t dstIndex = 0; dstIndex < states.size(); ++dstIndex) {
                            if (dstIndex == srcIndex) {
                                continue;
                            }
                            auto&& pDstState = pMachine->GetStateOrNull(dstIndex);
                            if (!pDstState) {
                                continue;
                            }

                            const std::string label = pDstState->GetStateName().ToStringRef();
                            if (SR_GRAPH_GUI_NS::Immediate::MenuItem(label.c_str())) {
                                if (auto&& pSrcState = pMachine->GetStateOrNull(srcIndex)) {
                                    auto&& transitions = pSrcState->GetTransitions();
                                    bool exists = false;
                                    for (auto&& t : transitions) {
                                        if (t && t->GetTargetIndex() == static_cast<int32_t>(dstIndex)) {
                                            exists = true;
                                            break;
                                        }
                                    }
                                    if (!exists) {
                                        auto&& pTransition = SRNew<SR_ANIMATIONS_NS::AnimationStateTransition>();
                                        pTransition->ResetCondition();
                                        pTransition->SetTargetIndex(static_cast<int32_t>(dstIndex));
                                        transitions.emplace_back(pTransition);
                                        m_graph->InvalidateCompile();
                                        needResync = true;
                                    }
                                }
                            }
                        }
                        SR_GRAPH_GUI_NS::Immediate::EndMenu();
                    }

                    if (SR_GRAPH_GUI_NS::Immediate::BeginMenu("Delete transition")) {
                        if (auto&& pSrcState = pMachine->GetStateOrNull(srcIndex)) {
                            auto&& transitions = pSrcState->GetTransitions();
                            for (uint32_t i = 0; i < transitions.size(); ++i) {
                                auto&& t = transitions[i];
                                if (!t) {
                                    continue;
                                }
                                const int32_t dstIndexI = t->GetTargetIndex();
                                auto&& pDstState = (dstIndexI >= 0) ? pMachine->GetStateOrNull(static_cast<uint32_t>(dstIndexI)) : nullptr;
                                const std::string label = pDstState ? pDstState->GetStateName().ToStringRef() : std::string("Invalid");
                                if (SR_GRAPH_GUI_NS::Immediate::MenuItem(label.c_str())) {
                                    transitions.erase(transitions.begin() + static_cast<int32_t>(i));
                                    m_graph->InvalidateCompile();
                                    needResync = true;
                                    break;
                                }
                            }
                        }
                        SR_GRAPH_GUI_NS::Immediate::EndMenu();
                    }

                    if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Delete state")) {
                        if (pMachine->RemoveState(srcIndex)) {
                            m_graph->InvalidateCompile();
                            needResync = true;
                        }
                    }

                    SR_GRAPH_GUI_NS::Immediate::EndPopup();
                }
                SR_GRAPH_GUI_NS::Immediate::PopID();
            }
            SR_GRAPH_GUI_NS::Immediate::Spring(1);
            builder.EndHeader();

            builder.End();

            // кэшируем прямоугольник ноды (для рисования переходов от границы к границе)
            const auto nodeMin = SR_GRAPH_GUI_NS::Immediate::GetItemRectMin();
            const auto nodeMax = SR_GRAPH_GUI_NS::Immediate::GetItemRectMax();
            // Rect ctor = (x,y,w,h), не (min,max)
            m_smNodeRects[pNode->GetId()] = SR_MATH_NS::FRect(
                nodeMin.x,
                nodeMin.y,
                nodeMax.x - nodeMin.x,
                nodeMax.y - nodeMin.y
            );
        }

        auto clipToRectEdge = [](const SR_MATH_NS::FRect& rect, const SR_MATH_NS::FVector2& from, const SR_MATH_NS::FVector2& to) -> SR_MATH_NS::FVector2 {
                const SR_MATH_NS::FVector2 c = rect.Center();
                SR_MATH_NS::FVector2 dir = to - from;
                const float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                dir = len > 0.0001f ? (dir / len) : SR_MATH_NS::FVector2(1.f, 0.f);

                const float halfW = rect.Width() * 0.5f;
                const float halfH = rect.Height() * 0.5f;

                const float adx = std::abs(dir.x);
                const float ady = std::abs(dir.y);

                float s = 0.f;
                if (adx * halfH > ady * halfW) {
                    // hit left/right
                    s = halfW / (adx > 0.0001f ? adx : 1.f);
                }
                else {
                    // hit top/bottom
                    s = halfH / (ady > 0.0001f ? ady : 1.f);
                }

                return c + dir * s;
            };

        // transitions: straight lines from node border to node border (no pins)
        if (void* pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList()) {
            auto&& states = pMachine->GetStates();
            for (uint32_t srcIndex = 0; srcIndex < states.size(); ++srcIndex) {
                auto&& pState = states[srcIndex];
                if (!pState) {
                    continue;
                }

                auto&& srcVisualIt = m_stateIndexToVisual.find(srcIndex);
                if (srcVisualIt == m_stateIndexToVisual.end()) {
                    continue;
                }

                auto&& srcRectIt = m_smNodeRects.find(srcVisualIt->second->GetId());
                if (srcRectIt == m_smNodeRects.end()) {
                    continue;
                }

                const auto& srcRect = srcRectIt->second;
                const SR_MATH_NS::FVector2 srcCenter = srcRect.Center();

                auto&& transitions = pState->GetTransitions();
                for (uint32_t transitionIndex = 0; transitionIndex < transitions.size(); ++transitionIndex) {
                    auto&& pTransition = transitions[transitionIndex];
                    if (!pTransition) {
                        continue;
                    }

                    const int32_t dstIndexI = pTransition->GetTargetIndex();
                    if (dstIndexI < 0 || static_cast<uint32_t>(dstIndexI) >= states.size()) {
                        continue;
                    }
                    const uint32_t dstIndex = static_cast<uint32_t>(dstIndexI);

                    auto&& dstVisualIt = m_stateIndexToVisual.find(dstIndex);
                    if (dstVisualIt == m_stateIndexToVisual.end()) {
                        continue;
                    }

                    auto&& dstRectIt = m_smNodeRects.find(dstVisualIt->second->GetId());
                    if (dstRectIt == m_smNodeRects.end()) {
                        continue;
                    }

                    const auto& dstRect = dstRectIt->second;
                    const SR_MATH_NS::FVector2 dstCenter = dstRect.Center();

                    const SR_MATH_NS::FVector2 srcPoint = clipToRectEdge(srcRect, srcCenter, dstCenter);
                    const SR_MATH_NS::FVector2 dstPoint = clipToRectEdge(dstRect, dstCenter, srcCenter);

                    const bool isActive = (pState->GetActiveTransition() == pTransition.Get());
                    const uint32_t col = isActive ? SR_COL32(60, 220, 110, 255) : SR_COL32(200, 200, 200, 220);
                    const float thickness = isActive ? 3.0f : 2.0f;

                    SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(pDrawList, srcPoint, dstPoint, col, thickness);

                    // arrow head
                    const SR_MATH_NS::FVector2 dir = dstPoint - srcPoint;
                    const float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                    const SR_MATH_NS::FVector2 nd = len > 0.001f ? (dir / len) : SR_MATH_NS::FVector2(1.0f, 0.0f);
                    const SR_MATH_NS::FVector2 perp(-nd.y, nd.x);

                    const float arrowLen = 10.0f;
                    const float arrowWidth = 6.0f;
                    const SR_MATH_NS::FVector2 tip = dstPoint;
                    const SR_MATH_NS::FVector2 base = tip - nd * arrowLen;
                    const SR_MATH_NS::FVector2 left = base + perp * arrowWidth;
                    const SR_MATH_NS::FVector2 right = base - perp * arrowWidth;
                    SR_GRAPH_GUI_NS::Immediate::DrawListAddTriangleFilled(pDrawList, tip, left, right, col);
                }
            }
        }

        // transition creation mode: click source (context menu) -> click target
        if (editable && m_smCreateTransitionFrom >= 0) {
            // cancel on right click
            if (SR_GRAPH_GUI_NS::Immediate::IsMouseReleased(SR_GRAPH_GUI_NS::Immediate::MouseButton::Right)) {
                m_smCreateTransitionFrom = -1;
            }
            else if (void* pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList()) {
                const uint32_t srcIndex = static_cast<uint32_t>(m_smCreateTransitionFrom);
                auto&& srcVisualIt = m_stateIndexToVisual.find(srcIndex);
                if (srcVisualIt != m_stateIndexToVisual.end()) {
                    auto&& srcRectIt = m_smNodeRects.find(srcVisualIt->second->GetId());
                    if (srcRectIt != m_smNodeRects.end()) {
                        const auto& srcRect = srcRectIt->second;
                        const SR_MATH_NS::FVector2 mouse = SR_GRAPH_GUI_NS::Immediate::GetMousePos();
                        const SR_MATH_NS::FVector2 srcPoint = clipToRectEdge(srcRect, srcRect.Center(), mouse);

                        SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(pDrawList, srcPoint, mouse, SR_COL32(255, 255, 255, 180), 2.0f);

                        if (SR_GRAPH_GUI_NS::Immediate::IsMouseReleased(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left)) {
                            // find target node under mouse
                            uint32_t dstIndex = SR_ID_INVALID;
                            for (auto&& [nodeId, rect] : m_smNodeRects) {
                                if (!rect.Contains(mouse)) {
                                    continue;
                                }
                                auto&& nodeIt = m_smNodes.find(nodeId);
                                if (nodeIt == m_smNodes.end() || !nodeIt->second) {
                                    continue;
                                }
                                auto&& idxIt = m_visualToStateIndex.find(nodeIt->second);
                                if (idxIt == m_visualToStateIndex.end()) {
                                    continue;
                                }
                                if (idxIt->second != srcIndex) {
                                    dstIndex = idxIt->second;
                                    break;
                                }
                            }

                            if (dstIndex != SR_ID_INVALID) {
                                if (auto&& pSrcState = pMachine->GetStateOrNull(srcIndex)) {
                                    auto&& transitions = pSrcState->GetTransitions();
                                    bool exists = false;
                                    for (auto&& t : transitions) {
                                        if (t && t->GetTargetIndex() == static_cast<int32_t>(dstIndex)) {
                                            exists = true;
                                            break;
                                        }
                                    }
                                    if (!exists) {
                                        auto&& pTransition = SRNew<SR_ANIMATIONS_NS::AnimationStateTransition>();
                                        pTransition->ResetCondition();
                                        pTransition->SetTargetIndex(static_cast<int32_t>(dstIndex));
                                        transitions.emplace_back(pTransition);
                                        m_graph->InvalidateCompile();
                                        needResync = true;
                                    }
                                }
                                m_smCreateTransitionFrom = -1;
                            }
                        }
                    }
                }
            }
        }

        if (editable) {
            // create/delete transitions via drag is disabled (no pins)
            /*if (SR_GRAPH_GUI_NS::Immediate::BeginCreate()) {
                uintptr_t startPinId = 0, endPinId = 0;
                if (SR_GRAPH_GUI_NS::Immediate::QueryNewLink(&startPinId, &endPinId)) {
                    if (startPinId && endPinId) {
                        SR_GRAPH_GUI_NS::Pin* pStartPin = nullptr;
                        SR_GRAPH_GUI_NS::Pin* pEndPin = nullptr;

                        for (auto&& [nodeId, pNode] : m_smNodes) {
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

                        if (pStartPin && pEndPin &&
                            pStartPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Output &&
                            pEndPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Input &&
                            SR_GRAPH_GUI_NS::Immediate::AcceptNewItem()) {

                            auto&& pStartNode = pStartPin->GetNode();
                            auto&& pEndNode = pEndPin->GetNode();
                            if (pStartNode && pEndNode) {
                                auto&& srcIt = m_visualToStateIndex.find(pStartNode);
                                auto&& dstIt = m_visualToStateIndex.find(pEndNode);
                                if (srcIt != m_visualToStateIndex.end() && dstIt != m_visualToStateIndex.end()) {
                                    const uint32_t srcIndex = srcIt->second;
                                    const uint32_t dstIndex = dstIt->second;

                                    const int32_t outPinIndex = pStartNode->GetPinIndex(pStartPin);
                                    if (outPinIndex != SR_ID_INVALID) {
                                        if (auto&& pSrcState = pMachine->GetStateOrNull(srcIndex)) {
                                            auto&& transitions = pSrcState->GetTransitions();

                                            if (static_cast<size_t>(outPinIndex) >= transitions.size()) {
                                                auto&& pTransition = SRNew<SR_ANIMATIONS_NS::AnimationStateTransition>();
                                                pTransition->ResetCondition();
                                                pTransition->SetTargetIndex(static_cast<int32_t>(dstIndex));
                                                transitions.emplace_back(pTransition);
                                            }
                                            else {
                                                if (auto&& pTransition = transitions[static_cast<size_t>(outPinIndex)]) {
                                                    pTransition->SetTargetIndex(static_cast<int32_t>(dstIndex));
                                                    pTransition->ResetTransition();
                                                }
                                            }

                                            m_graph->InvalidateCompile();
                                            needResync = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            SR_GRAPH_GUI_NS::Immediate::EndCreate();
            */

            // delete transition/state
            if (SR_GRAPH_GUI_NS::Immediate::BeginDelete()) {
                // Link delete is disabled (no visual links)
                uintptr_t nodeId = 0;
                while (SR_GRAPH_GUI_NS::Immediate::QueryDeletedNode(&nodeId)) {
                    if (!nodeId) {
                        continue;
                    }

                    auto&& it = m_smNodes.find(nodeId);
                    if (it == m_smNodes.end() || !it->second) {
                        continue;
                    }

                    auto&& idxIt = m_visualToStateIndex.find(it->second);
                    if (idxIt == m_visualToStateIndex.end()) {
                        continue;
                    }

                    const uint32_t stateIndex = idxIt->second;
                    if (pMachine->RemoveState(stateIndex)) {
                        m_graph->InvalidateCompile();
                        needResync = true;
                        break;
                    }
                }
            }
            SR_GRAPH_GUI_NS::Immediate::EndDelete();

            // context menu: create state (dock-safe, anchored to node-editor background)
            if (SR_GRAPH_GUI_NS::Immediate::ShowBackgroundContextMenu()) {
                SR_GRAPH_GUI_NS::Immediate::OpenPopup("AnimatorEditor_SM_Context");
            }
            if (SR_GRAPH_GUI_NS::Immediate::BeginPopup("AnimatorEditor_SM_Context")) {
                std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>> categories;
                BuildStateMenu(categories);
                SR_GRAPH_GUI_NS::Immediate::InputText("##StateSearch", &m_createStateSearch);
                SR_GRAPH_GUI_NS::Immediate::Separator();
                DrawStateMenuRecursive(needResync, categories, "");
                SR_GRAPH_GUI_NS::Immediate::EndPopup();
            }
        }

        SR_GRAPH_GUI_NS::Immediate::EndNodeEditor();
        SR_GRAPH_GUI_NS::Immediate::PopNodeEditorStyleVar(3);
        SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);

        if (needResync) {
            SyncVisualToStateMachine();
            SyncStateMachineToVisual();
        }
    #else
        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Red(), "Node editor is disabled!");
    #endif
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

        return pNode;
    }

    void AnimatorEditor::UpdateVisualNode(SR_GRAPH_GUI_NS::Node* pVisualNode, SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode) {
        // Обновляем визуальную ноду на основе данных граф-ноды
        // Пока базовая реализация, можно расширить позже
    }

    void AnimatorEditor::TopPanelSave() {
        if (!m_graph) {
            return;
        }

        if (m_graphPath.IsEmpty()) {
            TopPanelSaveAt();
            return;
        }

        m_currentFile = m_graphPath;

        // Синхронизируем визуальные изменения с графом
        SyncVisualNodesToGraph();
        SyncVisualToStateMachine();

        if (m_isLive && m_liveReadOnly) {
            return;
        }

        // Кладём изменения обратно в ассет (мы редактируем клон)
        if (m_graphAsset) {
            m_graph->CloneTo(m_graphAsset->GetDataMutable());
        }

        // Сохраняем ассет
        if (auto&& pAsset = m_graphAsset ? m_graphAsset.Get() : (m_asset ? m_asset.Get() : m_graph->GetAsset())) {
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
#ifdef SR_USE_IMGUI_NODE_EDITOR
        if (!m_editor) {
            static auto&& settingsPath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/AnimatorEditor.json");
            m_editor = SR_GRAPH_GUI_NS::Immediate::CreateEditor(settingsPath.CStr());
        }
        if (!m_stateMachineEditor) {
            static auto&& smSettingsPath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/AnimatorStateMachineEditor.json");
            m_stateMachineEditor = SR_GRAPH_GUI_NS::Immediate::CreateEditor(smSettingsPath.CStr());
        }
#endif
        if (m_graph) {
            SyncGraphToVisualNodes();
        }
        Super::OnOpen();
    }

    void AnimatorEditor::Zoom() {
        if (m_tab == Tab::StateMachine) {
            if (m_stateMachineEditor) {
                SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_stateMachineEditor);
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

