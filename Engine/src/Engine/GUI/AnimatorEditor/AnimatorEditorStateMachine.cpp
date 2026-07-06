//
// Created by Monika on 06.07.2026.
//

#include <Engine/GUI/AnimatorEditor/AnimatorEditorStateMachine.h>
#include <Engine/GUI/PropertyDrawer.h>

#include <Graphics/Animations/AnimationState.h>
#include <Graphics/Animations/AnimationStateMachine.h>
#include <Graphics/Animations/AnimationStateCondition.h>
#include <Graphics/GUI/Node.h>
#include <Graphics/GUI/Link.h>
#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/NodeBuilder.h>
#include <Graphics/GUI/ImmediateGUI.h>

#include <Utils/TypeTraits/Factory.h>

namespace SR_CORE_GUI_NS {
    void AnimatorEditorStateMachine::ClearStateMachineVisual() {
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

    void AnimatorEditorStateMachine::SyncStateMachineToVisual() {
        ClearStateMachineVisual();

        if (!m_context.pGraph || m_context.openedStateMachineNodeIndex == SR_ID_INVALID) {
            return;
        }

        auto&& pGraphNode = m_context.pGraph->GetNode(m_context.openedStateMachineNodeIndex);
        auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
        if (!pSMNode) {
            return;
        }

        auto&& pMachine = pSMNode->GetMachine();
        if (!pMachine) {
            return;
        }

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_context.pStateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_context.pStateMachineEditor);
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
            if (m_context.pStateMachineEditor) {
                SR_GRAPH_GUI_NS::Immediate::SetNodePosition(pNode->GetId(), pState->GetEditorPosition());
            }
        #endif
        }

        // Транзишены рисуем кастомно, без node-editor links

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_context.pStateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        }
    #endif
    }

    void AnimatorEditorStateMachine::SyncVisualToStateMachine() {
        if (!m_context.pGraph || m_context.openedStateMachineNodeIndex == SR_ID_INVALID) {
            return;
        }

        auto&& pGraphNode = m_context.pGraph->GetNode(m_context.openedStateMachineNodeIndex);
        auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
        if (!pSMNode || !pSMNode->GetMachine()) {
            return;
        }

        auto&& pMachine = pSMNode->GetMachine();

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_context.pStateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_context.pStateMachineEditor);
        }
    #endif

        for (auto&& [stateIndex, pVisualNode] : m_stateIndexToVisual) {
            if (!pVisualNode) {
                continue;
            }

            if (auto&& pState = pMachine->GetStateOrNull(stateIndex)) {
            #ifdef SR_USE_IMGUI_NODE_EDITOR
                if (m_context.pStateMachineEditor) {
                    pState->SetEditorPosition(SR_GRAPH_GUI_NS::Immediate::GetNodePosition(pVisualNode->GetId()));
                }
            #endif
            }
        }

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_context.pStateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        }
    #endif
    }

    void AnimatorEditorStateMachine::DrawStateMachineEditor() {
    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (!m_context.pStateMachineEditor) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Red(), "State machine editor is not initialized!");
            return;
        }

        if (!m_context.pGraph || m_context.openedStateMachineNodeIndex == SR_ID_INVALID) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.7f, 0.7f, 0.7f, 1.0f), "No state machine selected. Double-click the state machine node in Graph.");
            return;
        }

        auto&& pGraphNode = m_context.pGraph->GetNode(m_context.openedStateMachineNodeIndex);
        auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
        if (!pSMNode || !pSMNode->GetMachine()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Red(), "Invalid state machine node!");
            return;
        }

        if (m_context.openStateMachineRequested) {
            SyncStateMachineToVisual();
            m_context.openStateMachineRequested = false;
        }

        // UI сверху (не в canvas), чтобы прогресс не “плавал”
        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.6f, 0.6f, 0.6f, 1.0f), "Graph > State Machine");

        // Live: progress bar for active animation state (привязан к текущему ImGui окну)
        if (m_context.isLive && m_context.pRuntimeGraph) {
            if (auto&& pRuntimeNode = m_context.pRuntimeGraph->GetNode(m_context.openedStateMachineNodeIndex)) {
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

        SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_context.pStateMachineEditor);
        SR_GRAPH_GUI_NS::Immediate::Begin("Animation State Machine", SR_MATH_NS::FVector2());

        SR_GRAPH_GUI_NS::NodeBuilder builder(nullptr);

        SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::SourceDirection, SR_MATH_NS::FVector2(1.0f, 0.0f));
        SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::TargetDirection, SR_MATH_NS::FVector2(-1.0f, 0.0f));
        SR_GRAPH_GUI_NS::Immediate::PushNodeEditorStyleVar(SR_GRAPH_GUI_NS::Immediate::NodeEditorStyleVar::SnapLinkToPinDir, 1.0f);

        auto&& pMachine = pSMNode->GetMachine();
        bool needResync = false;
        const bool editable = !(m_context.isLive && m_context.liveReadOnly);

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
                                        m_context.pGraph->InvalidateCompile();
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
                                    m_context.pGraph->InvalidateCompile();
                                    needResync = true;
                                    break;
                                }
                            }
                        }
                        SR_GRAPH_GUI_NS::Immediate::EndMenu();
                    }

                    if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Delete state")) {
                        if (pMachine->RemoveState(srcIndex)) {
                            m_context.pGraph->InvalidateCompile();
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
                                        m_context.pGraph->InvalidateCompile();
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

                                            m_context.pGraph->InvalidateCompile();
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
                        m_context.pGraph->InvalidateCompile();
                        needResync = true;
                        break;
                    }
                }
            }
            SR_GRAPH_GUI_NS::Immediate::EndDelete();

            SR_GRAPH_GUI_NS::Immediate::SuspendNodeEditor();
            // context menu: create state (dock-safe, anchored to node-editor background)
            if (SR_GRAPH_GUI_NS::Immediate::ShowBackgroundContextMenu()) {
                SR_GRAPH_GUI_NS::Immediate::OpenPopup("AnimatorEditor_SM_Context");
                m_popupMousePos = SR_GRAPH_GUI_NS::Immediate::GetMousePos();
            }
            if (SR_GRAPH_GUI_NS::Immediate::BeginPopup("AnimatorEditor_SM_Context")) {
                std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>> categories;
                BuildStateMenu(categories);
                SR_GRAPH_GUI_NS::Immediate::InputText("##StateSearch", &m_createStateSearch);
                SR_GRAPH_GUI_NS::Immediate::Separator();
                DrawStateMenuRecursive(needResync, categories, "");
                SR_GRAPH_GUI_NS::Immediate::EndPopup();
            }
            SR_GRAPH_GUI_NS::Immediate::ResumeNodeEditor();
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

    void AnimatorEditorStateMachine::InitStateTypes() {
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

    void AnimatorEditorStateMachine::BuildStateMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories) {
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

    void AnimatorEditorStateMachine::DrawStateMenuRecursive(bool& needResync, const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix) {
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
                if (!m_context.pGraph || m_context.openedStateMachineNodeIndex == SR_ID_INVALID) {
                    continue;
                }

                auto&& pGraphNode = m_context.pGraph->GetNode(m_context.openedStateMachineNodeIndex);
                auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
                if (!pSMNode || !pSMNode->GetMachine()) {
                    continue;
                }

                auto&& pMachine = pSMNode->GetMachine();

                if (auto&& pState = SR_UTILS_NS::Factory::Instance().Create<SR_ANIMATIONS_NS::AnimationState>(stateTypeName)) {
                    auto&& pos = SR_GRAPH_GUI_NS::Immediate::ScreenToCanvas(m_popupMousePos);
                    pState->SetEditorPosition(pos);
                    pMachine->AddState(pState.Get());

                    m_context.pGraph->InvalidateCompile();
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

    SR_UTILS_NS::SRClass* AnimatorEditorStateMachine::GetSelectedObject(uintptr_t nodeId) const {
        if (auto&& it = m_smNodes.find(nodeId); it != m_smNodes.end()) {
            if (auto&& idxIt = m_visualToStateIndex.find(it->second); idxIt != m_visualToStateIndex.end()) {
                auto&& pGraphNode = m_context.pGraph->GetNode(m_context.openedStateMachineNodeIndex);
                auto&& pSMNode = pGraphNode ? dynamic_cast<SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine*>(pGraphNode) : nullptr;
                if (pSMNode && pSMNode->GetMachine()) {
                    return pSMNode->GetMachine()->GetStateOrNull(idxIt->second);
                }
            }
        }
        return nullptr;
    }
}