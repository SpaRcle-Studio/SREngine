//
// Created by Monika on 18.07.2026.
//

#include <ImmediateGUI/GUI/NodeEditor.h>
#include <ImmediateGUI/Impl/ImGUI.h>

#if defined(SR_USE_IMGUI_NODE_FLOW) && defined(SR_USE_IMGUI)

namespace SR_IMMEDIATE_GUI_NS::NodeFlowImpl {
    constexpr float_t SOCKET_RADIUS = 4.f * 1.567f;
    constexpr float_t SOCKET_HOVERED_RADIUS = 4.67f * 1.567f;
    constexpr float_t SOCKET_CONNECTED_RADIUS = 3.7f * 1.567f;

    std::shared_ptr<ImFlow::PinStyle> GetPinStyle(IconType type) {
        static std::map<IconType, std::shared_ptr<ImFlow::PinStyle>> g_pinStyles = {
            { IconType::Flow, std::make_shared<ImFlow::PinStyle>(ImFlow::PinStyle(IM_COL32(255, 255, 255, 255), 1, SOCKET_RADIUS, SOCKET_HOVERED_RADIUS, SOCKET_CONNECTED_RADIUS, 1.f)) },
            { IconType::Circle, std::make_shared<ImFlow::PinStyle>(ImFlow::PinStyle(IM_COL32(87, 155, 185, 255), 0, SOCKET_RADIUS, SOCKET_HOVERED_RADIUS, SOCKET_CONNECTED_RADIUS, 1.f)) },
            { IconType::Square, std::make_shared<ImFlow::PinStyle>(ImFlow::PinStyle(IM_COL32(87, 155, 185, 255), 0, SOCKET_RADIUS, SOCKET_HOVERED_RADIUS, SOCKET_CONNECTED_RADIUS, 1.f)) },
            { IconType::Grid, std::make_shared<ImFlow::PinStyle>(ImFlow::PinStyle(IM_COL32(87, 155, 185, 255), 0, SOCKET_RADIUS, SOCKET_HOVERED_RADIUS, SOCKET_CONNECTED_RADIUS, 1.f)) },
            { IconType::RoundSquare, std::make_shared<ImFlow::PinStyle>(ImFlow::PinStyle(IM_COL32(87, 155, 185, 255), 0, SOCKET_RADIUS, SOCKET_HOVERED_RADIUS, SOCKET_CONNECTED_RADIUS, 1.f)) },
            { IconType::Diamond, std::make_shared<ImFlow::PinStyle>(ImFlow::PinStyle(IM_COL32(87, 155, 185, 255), 0, SOCKET_RADIUS, SOCKET_HOVERED_RADIUS, SOCKET_CONNECTED_RADIUS, 1.f)) }
        };

        auto it = g_pinStyles.find(type);
        if (it != g_pinStyles.end()) {
            return it->second;
        }

        return nullptr;
    }

    class InputPinInstanceNFImpl : public InputPinInstance {
    public:
        void Draw() override { }

        void SetPin(std::shared_ptr<ImFlow::InPin<PinData*>> pPin) {
            m_pPin = std::move(pPin);
        }
        SR_NODISCARD std::shared_ptr<ImFlow::InPin<PinData*>>& GetPin() { return m_pPin; }

    private:
        std::shared_ptr<ImFlow::InPin<PinData*>> m_pPin;

    };

    class OutputPinInstanceNFImpl : public OutputPinInstance {
    public:
        void Draw() override { }

        void SetPin(std::shared_ptr<ImFlow::OutPin<PinData*>> pPin) {
            m_pPin = std::move(pPin);
        }
        SR_NODISCARD std::shared_ptr<ImFlow::OutPin<PinData*>>& GetPin() { return m_pPin; }

    private:
        std::shared_ptr<ImFlow::OutPin<PinData*>> m_pPin;

    };

    class LinkInstanceNFImpl : public ImFlow::Link {
    public:
        LinkInstanceNFImpl(ImFlow::Pin* left, ImFlow::Pin* right, ImFlow::ImNodeFlow* inf)
            : ImFlow::Link(left, right, inf)
        { }

        void SetPins(ImFlow::Pin* pLeft, ImFlow::Pin* pRight) {
            m_left = pLeft;
            m_right = pRight;
        }
    };

    class NodeInstanceNFImpl : public NodeInstance, public ImFlow::BaseNode {
    public:
        explicit NodeInstanceNFImpl(NodeEditorInstance* pEditor)
            : NodeInstance(pEditor)
        { }

        void Draw() override {
            SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.f, 40.f));
        }

        void draw() override {
            Draw();
        }

        void SetTitle(SR_UTILS_NS::StringView title) override {
            static std::string gBufferTmp;
            gBufferTmp = title;
            setTitle(gBufferTmp);
        }

        void SetPosition(const SR_MATH_NS::FVector2& position) override {
            setPos(ImVec2(position.x, position.y));
        }

        SR_NODISCARD SR_MATH_NS::FVector2 GetPosition() const override {
            SR_TRACY_ZONE;
            auto&& pos = const_cast<NodeInstanceNFImpl*>(this)->getPos();
            return SR_MATH_NS::FVector2(pos.x, pos.y);
        }

        InputPinInstance* AddInputPin(SR_UTILS_NS::StringView name, IconType type) override {
            SR_TRACY_ZONE;
            static std::string gBufferTmp;
            gBufferTmp = name;

            InputPinInstanceNFImpl* pPin = nullptr;
            for (auto&& pInputPin : m_inputPins) {
                if (!pInputPin->IsUsed()) {
                    pPin = static_cast<InputPinInstanceNFImpl*>(pInputPin.Get());
                    break;
                }
            }
            if (!pPin) {
                pPin = new InputPinInstanceNFImpl();
                ImFlow::PinUID h = std::hash<void*>{ }(pPin);
                m_pHandler = getHandler();
                auto pRawPin = std::make_shared<ImFlow::InPin<PinData*>>(h, gBufferTmp, nullptr, ImFlow::ConnectionFilter::SameType(), nullptr, this, &m_pHandler);
                pPin->SetPin(pRawPin);
                m_inputPins.emplace_back(static_cast<InputPinInstance*>(pPin));
            }

            pPin->SetUsed(true);
            pPin->GetPin()->getStyle() = GetPinStyle(type);
            const_cast<std::vector<std::shared_ptr<ImFlow::Pin>>&>(getIns()).emplace_back(pPin->GetPin());
            const_cast<std::string&>(pPin->GetPin()->getName()) = gBufferTmp;
            return pPin;
        }

        OutputPinInstance* AddOutputPin(SR_UTILS_NS::StringView name, IconType type) override {
            SR_TRACY_ZONE;
            static std::string gBufferTmp;
            gBufferTmp = name;

            OutputPinInstanceNFImpl* pPin = nullptr;
            for (auto&& pOutputPin : m_outputPins) {
                if (!pOutputPin->IsUsed()) {
                    pPin = static_cast<OutputPinInstanceNFImpl*>(pOutputPin.Get());
                    break;
                }
            }
            if (!pPin) {
                pPin = new OutputPinInstanceNFImpl();
                ImFlow::PinUID h = std::hash<void*>{ }(pPin);
                m_pHandler = getHandler();
                auto pRawPin = std::make_shared<ImFlow::OutPin<PinData*>>(h, gBufferTmp, nullptr, this, &m_pHandler);
                pPin->SetPin(pRawPin);
                m_outputPins.emplace_back(static_cast<OutputPinInstance*>(pPin));
            }

            pPin->SetUsed(true);
            pPin->GetPin()->getStyle() = GetPinStyle(type);
            const_cast<std::vector<std::shared_ptr<ImFlow::Pin>>&>(getOuts()).emplace_back(pPin->GetPin());
            const_cast<std::string&>(pPin->GetPin()->getName()) = gBufferTmp;
            return pPin;
        }

        void RemovePins() override {
            SR_TRACY_ZONE;
            for (auto&& pin : getIns()) {
                pin->deleteLink();
            }
            for (auto&& pin : getOuts()) {
                pin->deleteLink();
            }
            const_cast<std::vector<std::shared_ptr<ImFlow::Pin>>&>(getIns()).clear();
            const_cast<std::vector<std::shared_ptr<ImFlow::Pin>>&>(getOuts()).clear();
            for (auto&& pPin : m_inputPins) {
                pPin->SetUsed(false);
            }
            for (auto&& pPin : m_outputPins) {
                pPin->SetUsed(false);
            }
        }

        void LinkTo(NodeInstance* pTargetNode, uint32_t sourcePin, uint32_t targetPin) override;

    private:
        ImFlow::ImNodeFlow* m_pHandler = nullptr;

    };

    class NodeEditorInstanceNodeFlowImpl : public NodeEditorInstance {
    public:
        void Draw() override {
            m_nodeFlow.update();
        }

        void SetSize(const SR_MATH_NS::FVector2& size) override {
            m_nodeFlow.setSize(ImVec2(size.x, size.y));
        }

        void Zoom() override { }

        void RemoveAllNodes() override {
            SR_TRACY_ZONE;
            for (auto&& pNode : m_nodes) {
                pNode->SetPosition(SR_MATH_NS::FVector2(SR_FLOAT_MAX));
                pNode->RemovePins();
            }
            for (auto&& pLink : m_links) {
                static_cast<LinkInstanceNFImpl*>(pLink.get())->SetPins(nullptr, nullptr);
            }
            const_cast<std::vector<std::weak_ptr<ImFlow::Link>>&>(GetNodeFlow().getLinks()).clear();
            m_freeNodes = m_nodes;
            m_freeLinks = m_links;
        }

        NodeInstance* CreateNode(uintptr_t nodeId) override {
            SR_TRACY_ZONE;

            NodeInstanceNFImpl* pNode = nullptr;
            if (m_freeNodes.empty()) {
                auto&& pNewNode = std::make_shared<NodeInstanceNFImpl>(this);
                pNewNode->setHandler(&m_nodeFlow);
                pNewNode->setStyle(ImFlow::NodeStyle::cyan());
                m_nodeFlow.getNodes()[nodeId] = pNewNode;
                m_nodes.emplace_back(pNewNode);
                pNode = pNewNode.get();
            }
            else {
                pNode = m_freeNodes.back().get();
                m_freeNodes.pop_back();
            }

            pNode->setUID(nodeId);
            return pNode;
        }

        SR_NODISCARD ImFlow::ImNodeFlow& GetNodeFlow() { return m_nodeFlow; }

        SR_NODISCARD std::shared_ptr<ImFlow::Link> CreateLink(ImFlow::Pin* pSource, ImFlow::Pin* pTarget) {
            SR_TRACY_ZONE;
            if (m_freeLinks.empty()) {
                std::shared_ptr<ImFlow::Link> pLink = std::make_shared<LinkInstanceNFImpl>(pSource, pTarget, &m_nodeFlow);
                GetNodeFlow().addLink(pLink);
                m_links.emplace_back(pLink);
                return pLink;
            }
            auto&& pLink = m_freeLinks.back();
            GetNodeFlow().addLink(pLink);
            m_freeLinks.pop_back();
            static_cast<LinkInstanceNFImpl*>(pLink.get())->SetPins(pSource, pTarget);
            return pLink;
        }

    private:
        ImFlow::ImNodeFlow m_nodeFlow;

        SR_UTILS_NS::Vector<std::shared_ptr<NodeInstanceNFImpl>> m_nodes;
        SR_UTILS_NS::Vector<std::shared_ptr<NodeInstanceNFImpl>> m_freeNodes;

        SR_UTILS_NS::Vector<std::shared_ptr<ImFlow::Link>> m_links;
        SR_UTILS_NS::Vector<std::shared_ptr<ImFlow::Link>> m_freeLinks;

    };
}

namespace SR_IMMEDIATE_GUI_NS::NodeFlowImpl {
    void NodeInstanceNFImpl::LinkTo(NodeInstance* pTargetNode, uint32_t sourcePin, uint32_t targetPin) {
        SR_TRACY_ZONE;

        if (!pTargetNode) {
            return;
        }

        auto&& pSourcePin = m_outputPins[sourcePin].Get();
        auto&& pTargetPin = pTargetNode->GetInputs()[targetPin].Get();
        if (!pSourcePin || !pTargetPin) {
            return;
        }

        auto&& pEditor = static_cast<NodeEditorInstanceNodeFlowImpl*>(GetEditor());
        if (auto&& pSourceRawPin = static_cast<OutputPinInstanceNFImpl*>(pSourcePin)->GetPin()) {
            if (auto&& pTargetRawPin = static_cast<InputPinInstanceNFImpl*>(pTargetPin)->GetPin()) {
                //auto&& pLink = pEditor->CreateLink(pSourceRawPin.get(), pTargetRawPin.get());
                //pSourceRawPin->setLink(pLink);
                //pTargetRawPin->setLink(pLink);

                pTargetRawPin->createLink(pSourceRawPin.get());

                //pSourceRawPin->setLink(pLink);

                //m_link = std::make_shared<Link>(other, this, (*m_inf));
                //other->setLink(m_link);
                //(*m_inf)->addLink(m_link);
            }
        }
    }
}

#endif

#if defined(SR_USE_IMGUI_NODE_EDITOR) && defined(SR_USE_IMGUI)

namespace SR_IMMEDIATE_GUI_NS::NodeEditorImpl {
    class PushNodeEditorContext {
    public:
        explicit PushNodeEditorContext(ax::NodeEditor::EditorContext* pContext) {
            m_pPreviousContext = ax::NodeEditor::GetCurrentEditor();
            ax::NodeEditor::SetCurrentEditor(pContext);
        }
        ~PushNodeEditorContext() {
            ax::NodeEditor::SetCurrentEditor(m_pPreviousContext);
        }
    private:
        ax::NodeEditor::EditorContext* m_pPreviousContext = nullptr;
    };

    class LinkInstanceNEImpl : public LinkInstance {
    public:
        void Draw() override {
            auto&& pInputPin = GetInputPin();
            auto&& pOutputPin = GetOutputPin();

            auto&& pEditor = pInputPin->GetNode()->GetEditor();
            if (pEditor->GetStyleType() == NodeEditorStyleType::StateMachine) {
                auto&& pSrcNode = pOutputPin->GetNode();
                auto&& pDstNode = pInputPin->GetNode();

                const bool isDoubleWay = pSrcNode->GetInputLink(pDstNode) && pDstNode->GetInputLink(pSrcNode);
                const bool isNeedOffset = isDoubleWay && pSrcNode->GetInputLink(pDstNode) > pDstNode->GetInputLink(pSrcNode);

                auto&& pDrawList = ImGui::GetWindowDrawList();

                auto&& srcRect = pSrcNode->GetNodeRect();
                auto&& dstRect = pDstNode->GetNodeRect();

                const SR_MATH_NS::FVector2 srcOffset = isDoubleWay ? (isNeedOffset ? SR_MATH_NS::FVector2(0.0f, 30.0f) : SR_MATH_NS::FVector2(0.0f, -30.f)) : SR_MATH_NS::FVector2();
                const SR_MATH_NS::FVector2 dstOffset = isDoubleWay ? (isNeedOffset ? SR_MATH_NS::FVector2(0.0f, -30.0f) : SR_MATH_NS::FVector2(0.0f, 30.f)) : SR_MATH_NS::FVector2();

                const SR_MATH_NS::FVector2 srcPoint = SR_MATH_NS::ClipToRectEdge(srcRect, srcRect.Center(), dstRect.Center() + srcOffset);
                const SR_MATH_NS::FVector2 dstPoint = SR_MATH_NS::ClipToRectEdge(dstRect, dstRect.Center() + dstOffset, srcRect.Center());

                const auto defaultColor = SR_COL32(200, 200, 200, 220); /// white
                const auto activeColor = SR_COL32(60, 220, 110, 255); /// green
                const auto selectedColor = SR_COL32(255, 165, 0, 255); /// orange

                const bool isActive = false;
                const bool isSelected = false;
                const uint32_t col = isSelected ? selectedColor : (isActive ? activeColor : defaultColor);
                const float thickness = isSelected || isActive ? 3.0f : 2.0f;

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

                SR_MATH_NS::FVector2 lineDstArrowOffset = nd * arrowLen;
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(pDrawList, srcPoint, dstPoint - lineDstArrowOffset, col, thickness);
            }
            else {
                const ax::NodeEditor::LinkId linkId((uintptr_t)(this));
                ax::NodeEditor::Link(linkId, ax::NodeEditor::PinId((uintptr_t)(pInputPin)), ax::NodeEditor::PinId((uintptr_t)(pOutputPin)));
            }
        }
    };

    class InputPinInstanceNEImpl : public InputPinInstance {
    public:
        void Draw() override {
            const ax::NodeEditor::PinId pinId((uintptr_t)(static_cast<PinInstance*>(this)));
            ax::NodeEditor::BeginPin(pinId, ax::NodeEditor::PinKind::Input);
            SR_GRAPH_GUI_NS::Immediate::DrawPinIcon(
                SR_MATH_NS::FVector2(24.0f, 24.0f),
                IconType::Flow,
                IsLinked(),
                SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 1.0f),
                SR_MATH_NS::FColor(0.125f, 0.125f, 0.125f, 1.0f)
            );
            ax::NodeEditor::EndPin();
            ImGui::SameLine();
            if (auto&& name = GetName(); !name.empty()) {
                ImGui::Text("%s", name.c_str());
            }
        }
    };

    class OutputPinInstanceNEImpl : public OutputPinInstance {
    public:
        void Draw() override {
            const ax::NodeEditor::PinId pinId((uintptr_t)(static_cast<PinInstance*>(this)));
            if (auto&& name = GetName(); !name.empty()) {
                ImGui::Text("%s", name.c_str());
            }
            ImGui::SameLine();
            ax::NodeEditor::BeginPin(pinId, ax::NodeEditor::PinKind::Output);
            SR_GRAPH_GUI_NS::Immediate::DrawPinIcon(
                SR_MATH_NS::FVector2(24.0f, 24.0f),
                IconType::Flow,
                IsLinked(),
                SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 1.0f),
                SR_MATH_NS::FColor(0.125f, 0.125f, 0.125f, 1.0f)
            );
            ax::NodeEditor::EndPin();
        }
    };

    class NodeInstanceNEImpl : public NodeInstance {
        static constexpr float Height = 34.f;
        static constexpr float Padding = 8.f;
        static constexpr float PinIconWidth = 24.f;
        static constexpr float HeaderRounding = 11.f;
        static constexpr float MinWidth = 200.f;
        static constexpr float MinContentHeight = 50.f;
    public:
        explicit NodeInstanceNEImpl(NodeEditorInstance* pEditor)
            : NodeInstance(pEditor)
        { }

        float_t DrawHeader();
        float_t CalculatePinMaxWidth(bool input);

        void LinkTo(NodeInstance* pTargetNode, uint32_t sourcePin, uint32_t targetPin) override;

        void Draw() override;

        void SetTitle(SR_UTILS_NS::StringView title) override { m_title = title; }
        void SetPosition(const SR_MATH_NS::FVector2& position) override { m_position = position; }
        SR_NODISCARD SR_MATH_NS::FVector2 GetPosition() const override { return m_position; }

        void FetchPosition() {
            auto&& newPosition = ImV2ToF2(ax::NodeEditor::GetNodePosition(ax::NodeEditor::NodeId(this)));
            if (m_position != newPosition) {
                m_position = newPosition;
                if (auto&& callback = GetEditor()->GetSomethingChangedCallback()) {
                    callback();
                }
            }
        }

        InputPinInstance* AddInputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) override {
            auto&& pPin = (InputPinInstance*)m_inputPins.emplace_back(GetEditor()->CreateInputPin(name, type));
            pPin->SetNode(this);
            return pPin;
        }

        OutputPinInstance* AddOutputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) override {
            auto&& pPin = (OutputPinInstance*)m_outputPins.emplace_back(GetEditor()->CreateOutputPin(name, type));
            pPin->SetNode(this);
            return pPin;
        }

        void RemovePins() override;

    private:
        SR_UTILS_NS::String m_title;
        SR_MATH_NS::FVector2 m_position;

    };

    class NodeEditorInstanceNEImpl : public NodeEditorInstance {
    public:
        NodeEditorInstanceNEImpl() {
            m_editorContext = ax::NodeEditor::CreateEditor();
        }

        ~NodeEditorInstanceNEImpl() override {
            ax::NodeEditor::DestroyEditor(m_editorContext);
        }

        void SetSize(const SR_MATH_NS::FVector2& size) override;
        void ResetEditor() override;
        void Zoom() override;
        void Draw() override;
        void ClearSelection() override;

        SR_NODISCARD ax::NodeEditor::EditorContext* GetEditorContext() const { return m_editorContext; }

        const SR_UTILS_NS::Vector<NodeInstance*>& GetSelectedNodes() const override;
        NodeInstance* CreateNode() override;
        void CreateLink(InputPinInstance* pInputPin, OutputPinInstance* pOutputPin) override;
        SR_NODISCARD InputPinInstance* CreateInputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) override;
        SR_NODISCARD OutputPinInstance* CreateOutputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) override;

    private:
        mutable SR_UTILS_NS::Vector<NodeInstance*> m_selectedNodes;
        mutable SR_UTILS_NS::Vector<ax::NodeEditor::NodeId> m_selectedNodeIds;
        ax::NodeEditor::EditorContext* m_editorContext = nullptr;

    };
}

namespace SR_IMMEDIATE_GUI_NS::NodeEditorImpl {
    void NodeEditorInstanceNEImpl::Draw() {
        SR_TRACY_ZONE;

        PushNodeEditorContext pushContext(m_editorContext);
        ax::NodeEditor::Begin("Node Editor");

        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.6f, 0.6f, 0.6f, 1.0f), "%s", m_backgroundText.c_str());

        for (auto&& pNode : m_nodes) {
            ImGui::PushID(pNode);
            pNode->Draw();
            ImGui::PopID();
        }

        SR_IMMEDIATE_GUI_NS::NodeEditor::PushNodeEditorStyleColor(SR_IMMEDIATE_GUI_NS::NodeEditor::NodeEditorStyleColor::HighlightLinkBorder, SR_MATH_NS::FColor(0.25f, 1.0f, 0.35f, 1.0f));
        SR_IMMEDIATE_GUI_NS::NodeEditor::PushNodeEditorStyleColor(SR_IMMEDIATE_GUI_NS::NodeEditor::NodeEditorStyleColor::SelLinkBorder, SR_MATH_NS::FColor(0.25f, 1.0f, 0.35f, 1.0f));
        SR_IMMEDIATE_GUI_NS::NodeEditor::PushNodeEditorStyleVar(SR_IMMEDIATE_GUI_NS::NodeEditor::NodeEditorStyleVar::LinkStrength, 3.0f);

        for (auto&& pLink : m_links) {
            pLink->Draw();
        }

        SR_IMMEDIATE_GUI_NS::NodeEditor::PopNodeEditorStyleVar(1);
        SR_IMMEDIATE_GUI_NS::NodeEditor::PopNodeEditorStyleColor(2);

        if (SR_IMMEDIATE_GUI_NS::NodeEditor::BeginDelete()) {
            uintptr_t linkId = 0;
            while (SR_IMMEDIATE_GUI_NS::NodeEditor::QueryDeletedLink(&linkId, nullptr, nullptr)) {
                if (m_onSomethingChangedCallback) {
                    m_onSomethingChangedCallback();
                }
                if (m_onLinkDeletedCallback) {
                    m_onLinkDeletedCallback(*reinterpret_cast<LinkInstanceNEImpl*>(linkId));
                }
                ax::NodeEditor::ClearSelection();
            }

            uintptr_t nodeId = 0;
            while (SR_IMMEDIATE_GUI_NS::NodeEditor::QueryDeletedNode(&nodeId)) {
                if (m_onSomethingChangedCallback) {
                    m_onSomethingChangedCallback();
                }
                if (m_onNodeDeletedCallback) {
                    m_onNodeDeletedCallback(*reinterpret_cast<NodeInstanceNEImpl*>(nodeId));
                }
                ax::NodeEditor::ClearSelection();
            }
        }
        SR_IMMEDIATE_GUI_NS::NodeEditor::EndDelete();

        if (SR_IMMEDIATE_GUI_NS::NodeEditor::BeginCreate()) {
            uintptr_t startPinId = 0, endPinId = 0;
            if (SR_IMMEDIATE_GUI_NS::NodeEditor::QueryNewLink(&startPinId, &endPinId)) {
                auto&& pPinStart = reinterpret_cast<PinInstance*>(startPinId);
                auto&& pPinEnd = reinterpret_cast<PinInstance*>(endPinId);

                if (!pPinStart->IsInput() && pPinEnd->IsInput()) {
                    std::swap(pPinStart, pPinEnd);
                }

                const bool isNotAvailable =
                    (pPinEnd == pPinStart || pPinEnd->IsInput() == pPinStart->IsInput()) ||
                    (pPinEnd->GetNode() == pPinStart->GetNode()) ||
                    (pPinEnd->GetType() != pPinStart->GetType()) ||
                    (pPinStart->IsConnectedTo(pPinEnd));

                if (!isNotAvailable && SR_IMMEDIATE_GUI_NS::NodeEditor::AcceptNewItem()) {
                    static LinkInstanceNEImpl link;
                    link.Link((InputPinInstance*)pPinStart, (OutputPinInstance*)pPinEnd);
                    if (m_onSomethingChangedCallback) {
                        m_onSomethingChangedCallback();
                    }
                    if (m_onLinkCreatedCallback) {
                        m_onLinkCreatedCallback(link);
                    }
                }
            }
        }
        SR_IMMEDIATE_GUI_NS::NodeEditor::EndCreate();

        if (SR_GRAPH_GUI_NS::Immediate::IsMouseDoubleClicked(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left)) {
            if (auto&& selectedNodes = GetSelectedNodes(); selectedNodes.size() == 1) {
                if (m_onNodeDoubleClickedCallback) {
                    m_onNodeDoubleClickedCallback(*selectedNodes.front());
                }
            }
        }

        if (m_onBackgroundPopupCallback) {
            SR_IMMEDIATE_GUI_NS::NodeEditor::SuspendNodeEditor();
            if (SR_IMMEDIATE_GUI_NS::NodeEditor::ShowBackgroundContextMenu()) {
                SR_GRAPH_GUI_NS::Immediate::OpenPopup("NodeEditorGraphContext");
                m_popupMousePos = SR_GRAPH_GUI_NS::Immediate::GetMousePos();
            }
            if (SR_GRAPH_GUI_NS::Immediate::BeginPopup("NodeEditorGraphContext")) {
                m_onBackgroundPopupCallback(m_popupMousePos);
                SR_GRAPH_GUI_NS::Immediate::EndPopup();
            }
            SR_IMMEDIATE_GUI_NS::NodeEditor::ResumeNodeEditor();
        }

        if (m_onNodePopupCallback) {
            SR_IMMEDIATE_GUI_NS::NodeEditor::SuspendNodeEditor();
            uintptr_t nodeId = 0;
            if (SR_IMMEDIATE_GUI_NS::NodeEditor::ShowNodeContextMenu(&nodeId)) {
                SR_GRAPH_GUI_NS::Immediate::OpenPopup("AnimatorEditor_SM_NodeContext");
                m_popupMousePos = SR_GRAPH_GUI_NS::Immediate::GetMousePos();
                m_pPopupNode = reinterpret_cast<NodeInstance*>(nodeId);
            }
            if (SR_GRAPH_GUI_NS::Immediate::BeginPopup("AnimatorEditor_SM_NodeContext")) {
                m_onNodePopupCallback(*m_pPopupNode, m_popupMousePos);
                SR_GRAPH_GUI_NS::Immediate::EndPopup();
            }
            SR_IMMEDIATE_GUI_NS::NodeEditor::ResumeNodeEditor();
        }

        ax::NodeEditor::End();

        for (auto&& pNode : m_nodes) {
            static_cast<NodeInstanceNEImpl*>(pNode)->FetchPosition();
        }
    }

    void NodeEditorInstanceNEImpl::SetSize(const SR_MATH_NS::FVector2& size) {
        // Not needed for NodeEditor
    }

    void NodeEditorInstanceNEImpl::Zoom() {
        PushNodeEditorContext pushContext(m_editorContext);
        ax::NodeEditor::NavigateToContent();
    }

    NodeInstance* NodeEditorInstanceNEImpl::CreateNode() {
        NodeInstanceNEImpl* pNode = nullptr;
        if (m_freeNodes.empty()) {
            pNode = new NodeInstanceNEImpl(this);
            m_nodes.emplace_back(pNode);
        }
        else {
            pNode = static_cast<NodeInstanceNEImpl*>(m_freeNodes.back());
            m_freeNodes.pop_back();
            m_nodes.emplace_back(pNode);
        }
        return pNode;
    }

    void NodeEditorInstanceNEImpl::ClearSelection() {
        PushNodeEditorContext pushContext(m_editorContext);
        ax::NodeEditor::ClearSelection();
    }

    void NodeEditorInstanceNEImpl::ResetEditor() {
        SR_TRACY_ZONE;
        m_freeNodes = m_nodes;
        m_nodes.clear();
        for (auto&& pNode : m_freeNodes) {
            pNode->RemovePins();
        }
        m_freeLinks = m_links;
        m_links.clear();
        for (auto&& pLink : m_freeLinks) {
            pLink->Link(nullptr, nullptr);
        }
        std::ranges::stable_sort(m_freeLinks, [](const LinkInstance* a, const LinkInstance* b) {
            return a < b;
        });
        std::ranges::stable_sort(m_freeNodes, [](const NodeInstance* a, const NodeInstance* b) {
            return a < b;
        });
        std::ranges::stable_sort(m_freeInputPins, [](const PinInstance* a, const PinInstance* b) {
            return a < b;
        });
        std::ranges::stable_sort(m_freeOutputPins, [](const PinInstance* a, const PinInstance* b) {
            return a < b;
        });
    }

    InputPinInstance* NodeEditorInstanceNEImpl::CreateInputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) {
        InputPinInstance* pPin = nullptr;
        if (m_freeInputPins.empty()) {
            pPin = new InputPinInstanceNEImpl();
        }
        else {
            pPin = (InputPinInstance*)m_freeInputPins.back();
            m_freeInputPins.pop_back();
        }
        pPin->SetName(name);
        pPin->SetType(type);
        return pPin;
    }

    OutputPinInstance* NodeEditorInstanceNEImpl::CreateOutputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) {
        OutputPinInstance* pPin = nullptr;
        if (m_freeOutputPins.empty()) {
            pPin = new OutputPinInstanceNEImpl();
        }
        else {
            pPin = (OutputPinInstance*)m_freeOutputPins.back();
            m_freeOutputPins.pop_back();
        }
        pPin->SetName(name);
        pPin->SetType(type);
        return pPin;
    }

    void NodeEditorInstanceNEImpl::CreateLink(InputPinInstance* pInputPin, OutputPinInstance* pOutputPin) {
        SR_TRACY_ZONE;
        if (m_freeLinks.empty()) {
            auto&& pLink = new LinkInstanceNEImpl();
            pLink->Link(pInputPin, pOutputPin);
            m_links.emplace_back(pLink);
        }
        else {
            auto&& pLink = m_freeLinks.back();
            pLink->Link(pInputPin, pOutputPin);
            m_freeLinks.pop_back();
            m_links.emplace_back(pLink);
        }
        pInputPin->AddLink(m_links.back());
        pOutputPin->AddLink(m_links.back());
    }

    const SR_UTILS_NS::Vector<NodeInstance*>& NodeEditorInstanceNEImpl::GetSelectedNodes() const {
        SR_TRACY_ZONE;
        PushNodeEditorContext pushContext(m_editorContext);
        m_selectedNodes.clear();
        m_selectedNodeIds.clear();
        m_selectedNodeIds.resize(ax::NodeEditor::GetSelectedObjectCount());
        int nodeCount = ax::NodeEditor::GetSelectedNodes(m_selectedNodeIds.data(), static_cast<int>(m_selectedNodeIds.size()));
        m_selectedNodeIds.resize(nodeCount);
        for (auto&& nodeId : m_selectedNodeIds) {
            m_selectedNodes.emplace_back(reinterpret_cast<NodeInstance*>(nodeId.Get()));
        }
        return m_selectedNodes;
    }

    /// ================================================================================================================

    float_t NodeInstanceNEImpl::DrawHeader() {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        float fontSize = ImGui::GetFontSize();
        const float_t referenceFontSize = 12.f;
        const float_t scale = fontSize / referenceFontSize;
        ImFont* font = ImGui::GetFont();
        ImVec2 textSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, m_title.c_str());

        SR_MATH_NS::FColor color = SR_MATH_NS::FColor::PrettyRGBFromString(m_title);

        const float_t l = color.RelativeLuminance();
        const float_t whiteContrast = (1.05f) / (l + 0.05f);
        const float_t blackContrast = (l + 0.05f) / 0.05f;
        const bool useBlack = blackContrast > whiteContrast;
        constexpr float_t paddingY = 6.8f;

        ImColor imColor = ImColor(color.r, color.g, color.b, color.a);
        const float_t width = std::max(textSize.x + Padding * 2.f * scale, MinWidth);

        if (GetEditor()->GetStyleType() == NodeEditorStyleType::StateMachine) {
            auto&& pos = ImGui::GetCursorScreenPos() - ImVec2(0.f, paddingY);
            ImGui::Dummy(ImVec2(width, MinContentHeight)); /// резервируем место
            const float_t height = MinContentHeight + paddingY * 2.f;
            const float_t rectPadding = 12.f;
            drawList->AddRectFilled(
                pos + ImVec2(rectPadding, 0.f),
                ImVec2(pos.x + width - rectPadding, pos.y + height),
                ImGui::ColorConvertFloat4ToU32(imColor), 0.f, ImDrawFlags_RoundCornersAll
            );
            drawList->AddText(ImVec2(pos.x + (width - textSize.x) * 0.5f, pos.y + (Height - textSize.y) * 0.5f), useBlack ? IM_COL32_BLACK : IM_COL32_WHITE, m_title.c_str());

            /// progress bar
            const float_t progressBarHeight = 12.f;
            const ImVec2 progressBarPos = pos + ImVec2(rectPadding, 0.f) + ImVec2(0.f, height / 2.f - progressBarHeight / 2.f);
            const ImVec2 progressBarSize = ImVec2(pos.x + width - rectPadding, pos.y + height / 2.f + progressBarHeight / 2.f);
            const float_t progress = m_progress ? std::clamp(*m_progress, 0.f, 1.f) : 0.f;

            drawList->AddRectFilled(progressBarPos, progressBarSize,
                                    ImGui::ColorConvertFloat4ToU32(ImColor(0.1f, 0.1f, 0.1f, 0.4f)), 0.f, ImDrawFlags_RoundCornersAll
            );
            drawList->AddRectFilled(progressBarPos, progressBarSize - ImVec2((1.f - progress) * (progressBarSize.x - progressBarPos.x), 0.f),
                                    ImGui::ColorConvertFloat4ToU32(ImColor(0.3f, 0.8f, 0.3f, 0.8f)), 0.f, ImDrawFlags_RoundCornersAll
            );
        }
        else {
            ImVec2 padding = ImVec2(6.8, paddingY);
            ImVec2 pos = ImGui::GetCursorScreenPos() - padding;
            ImGui::Dummy(ImVec2(width, Height)); /// резервируем место
            drawList->AddRectFilled(pos, ImVec2(pos.x + width + padding.x * 2.f, pos.y + Height), ImGui::ColorConvertFloat4ToU32(imColor), HeaderRounding, ImDrawFlags_RoundCornersTop);
            drawList->AddText(ImVec2(pos.x + (width - textSize.x) * 0.5f, pos.y + (Height - textSize.y) * 0.5f), useBlack ? IM_COL32_BLACK : IM_COL32_WHITE, m_title.c_str());
        }
        return width;
    }

    float_t NodeInstanceNEImpl::CalculatePinMaxWidth(bool input) {
        SR_TRACY_ZONE;
        float_t maxWidth = 0.f;
        for (auto&& pPin : input ? m_inputPins : m_outputPins) {
            if (auto&& name = pPin->GetName(); !name.empty()) {
                auto&& textSize = ImGui::CalcTextSize(name.c_str());
                maxWidth = std::max(maxWidth, textSize.x);
            }
        }
        return maxWidth;
    }

    void NodeInstanceNEImpl::LinkTo(NodeInstance* pTargetNode, uint32_t sourcePin, uint32_t targetPin) {
        auto&& pPinTarget = static_cast<InputPinInstance*>(pTargetNode->GetInputs()[targetPin]);
        auto&& pPinSource = static_cast<OutputPinInstance*>(m_outputPins[sourcePin]);
        GetEditor()->CreateLink(pPinTarget, pPinSource);
    }

    void NodeInstanceNEImpl::Draw() {
        SR_TRACY_ZONE;

        if (GetEditor()->GetStyleType() == NodeEditorStyleType::StateMachine) {
            ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_NodeRounding, 2.f);
            ax::NodeEditor::BeginNode(ax::NodeEditor::NodeId(this));
            DrawHeader();
            ax::NodeEditor::EndNode();
            ax::NodeEditor::PopStyleVar();
        }
        else if (GetEditor()->GetStyleType() == NodeEditorStyleType::Graph) {
            ax::NodeEditor::BeginNode(ax::NodeEditor::NodeId(this));

            const float_t width = DrawHeader();
            const float_t outputPinMaxWidth = CalculatePinMaxWidth(false);
            const float_t maxPins = std::max(m_inputPins.size(), m_outputPins.size());
            const float_t height = std::max(MinContentHeight, maxPins * ImGui::GetFrameHeightWithSpacing() + Padding * 2.f);

            ImGui::Spacing();

            ImGui::BeginTable("pins", 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoSavedSettings, ImVec2(width, height));

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            for (auto&& pPin : m_inputPins) {
                pPin->Draw();
            }

            if (auto&& dummySize = ImVec2(width - PinIconWidth - outputPinMaxWidth - Padding * 2.f, 0); dummySize.x > 0.f) {
                ImGui::Dummy(dummySize);
            }

            ImGui::TableSetColumnIndex(1);

            if (!m_outputPins.empty()) {
                for (auto&& pPin : m_outputPins) {
                    pPin->Draw();
                }
            }

            ImGui::EndTable();
            ax::NodeEditor::EndNode();
        }

        ax::NodeEditor::SetNodePosition(ax::NodeEditor::NodeId(this), F2ToImV2(m_position));

        const auto nodeMin = SR_GRAPH_GUI_NS::Immediate::GetItemRectMin();
        const auto nodeMax = SR_GRAPH_GUI_NS::Immediate::GetItemRectMax();

        m_nodeRect = SR_MATH_NS::FRect(
            nodeMin.x,
            nodeMin.y,
            nodeMax.x - nodeMin.x,
            nodeMax.y - nodeMin.y
        );
    }

    void NodeInstanceNEImpl::RemovePins() {
        for (auto&& pPin : m_inputPins) {
            GetEditor()->OnInputPinRemoved(pPin);
            pPin->ClearLinks();
        }
        for (auto&& pPin : m_outputPins) {
            GetEditor()->OnOutputPinRemoved(pPin);
            pPin->ClearLinks();
        }
        m_inputPins.clear();
        m_outputPins.clear();
    }
}

#endif

namespace SR_GRAPH_GUI_NS::Immediate {
    NodeEditorInstance* NodeEditorInstance::Create() {
        SR_TRACY_ZONE;
    #if defined(SR_USE_IMGUI_NODE_FLOW) && defined(SR_USE_IMGUI)
        return new NodeFlowImpl::NodeEditorInstanceNodeFlowImpl();
    #elif defined(SR_USE_IMGUI_NODE_EDITOR) && defined(SR_USE_IMGUI)
        return new NodeEditorImpl::NodeEditorInstanceNEImpl();
    #else
        return nullptr;
    #endif
    }
}