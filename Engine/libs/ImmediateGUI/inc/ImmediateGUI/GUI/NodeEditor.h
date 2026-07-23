//
// Created by Monika on 11.07.2026.
//

#ifndef SR_ENGINE_IMMEDIATE_GUI_NODE_EDITOR_H
#define SR_ENGINE_IMMEDIATE_GUI_NODE_EDITOR_H

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Utils/Reflection/Value.h>
#include <Utils/Reflection/ReflectedType.h>

namespace SR_GRAPH_GUI_NS::Immediate {
    class NodeInstance;
    class PinInstance;
    class InputPinInstance;
    class OutputPinInstance;

    struct PinData {
        SR_UTILS_NS::Reflection::Value value;
    };

    struct PinTypeInfo {
        SR_UTILS_NS::Reflection::TypeInfo type;
        bool isFlow = false;
        bool operator ==(const PinTypeInfo& other) const {
            return type == other.type && isFlow == other.isFlow;
        }
        bool operator !=(const PinTypeInfo& other) const { return !(*this == other); }
    };

    class LinkInstance {
    public:
        LinkInstance() = default;

        SR_NODISCARD InputPinInstance* GetInputPin() const { return m_pInputPin; }
        SR_NODISCARD OutputPinInstance* GetOutputPin() const { return m_pOutputPin; }

        void Link(InputPinInstance* pInputPin, OutputPinInstance* pOutputPin) {
            m_pInputPin = pInputPin;
            m_pOutputPin = pOutputPin;
        }

        virtual void Draw() = 0;

    private:
        InputPinInstance* m_pInputPin = nullptr;
        OutputPinInstance* m_pOutputPin = nullptr;

    };

    enum class NodeEditorStyleType : uint8_t {
        Graph,
        StateMachine
    };

    class NodeEditorInstance {
        using OnNodeDeletedCallback = SR_HTYPES_NS::Function<void(NodeInstance&)>;
        using OnLinkDeletedCallback = SR_HTYPES_NS::Function<void(LinkInstance&)>;
        using OnLinkCreatedCallback = SR_HTYPES_NS::Function<void(LinkInstance&)>;
        using OnSomethingChangedCallback = SR_HTYPES_NS::Function<void()>;
        using OnBackgroundPopupCallback = SR_HTYPES_NS::Function<void(SR_MATH_NS::FVector2)>;
        using OnNodeDoubleClickedCallback = SR_HTYPES_NS::Function<void(NodeInstance&)>;
        using OnNodePopupCallback = SR_HTYPES_NS::Function<void(NodeInstance&, SR_MATH_NS::FVector2)>;
    public:
        static NodeEditorInstance* Create();

    public:
        virtual ~NodeEditorInstance();
        virtual void Draw() = 0;
        virtual void Zoom() { }
        virtual NodeInstance* CreateNode() = 0;
        virtual void CreateLink(InputPinInstance* pInputPin, OutputPinInstance* pOutputPin) = 0;
        virtual void SetSize(const SR_MATH_NS::FVector2& size) = 0;
        virtual void SetBackgroundText(SR_UTILS_NS::StringView text) { m_backgroundText = text; }
        virtual void ResetEditor() = 0;
        virtual void ClearSelection() = 0;

        SR_NODISCARD virtual InputPinInstance* CreateInputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) = 0;
        SR_NODISCARD virtual OutputPinInstance* CreateOutputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) = 0;
        SR_NODISCARD virtual const SR_UTILS_NS::Vector<NodeInstance*>& GetSelectedNodes() const = 0;

        virtual void OnInputPinRemoved(PinInstance* pPin);
        virtual void OnOutputPinRemoved(PinInstance* pPin);

        void SetNodeDeletedCallback(OnNodeDeletedCallback callback) { m_onNodeDeletedCallback = std::move(callback); }
        void SetLinkDeletedCallback(OnLinkDeletedCallback callback) { m_onLinkDeletedCallback = std::move(callback); }
        void SetSomethingChangedCallback(OnSomethingChangedCallback callback) { m_onSomethingChangedCallback = std::move(callback); }
        void SetLinkCreatedCallback(OnLinkCreatedCallback callback) { m_onLinkCreatedCallback = std::move(callback); }
        void SetBackgroundPopupCallback(OnBackgroundPopupCallback callback) { m_onBackgroundPopupCallback = std::move(callback); }
        void SetNodeDoubleClickedCallback(OnNodeDoubleClickedCallback callback) { m_onNodeDoubleClickedCallback = std::move(callback); }
        void SetNodePopupCallback(OnNodePopupCallback callback) { m_onNodePopupCallback = std::move(callback); }
        void SetStyleType(NodeEditorStyleType styleType) { m_styleType = styleType; }

        SR_NODISCARD const OnSomethingChangedCallback& GetSomethingChangedCallback() const { return m_onSomethingChangedCallback; }
        SR_NODISCARD NodeEditorStyleType GetStyleType() const { return m_styleType; }

    protected:
        OnNodePopupCallback m_onNodePopupCallback;
        OnNodeDoubleClickedCallback m_onNodeDoubleClickedCallback;
        OnSomethingChangedCallback m_onSomethingChangedCallback;
        OnNodeDeletedCallback m_onNodeDeletedCallback;
        OnLinkDeletedCallback m_onLinkDeletedCallback;
        OnLinkCreatedCallback m_onLinkCreatedCallback;
        OnBackgroundPopupCallback m_onBackgroundPopupCallback;
        SR_UTILS_NS::Vector<LinkInstance*> m_links;
        SR_UTILS_NS::Vector<LinkInstance*> m_freeLinks;
        SR_UTILS_NS::Vector<NodeInstance*> m_nodes;
        SR_UTILS_NS::Vector<NodeInstance*> m_freeNodes;
        SR_UTILS_NS::Vector<PinInstance*> m_freeInputPins;
        SR_UTILS_NS::Vector<PinInstance*> m_freeOutputPins;
        SR_MATH_NS::FVector2 m_popupMousePos;
        SR_UTILS_NS::String m_backgroundText;
        NodeEditorStyleType m_styleType = NodeEditorStyleType::Graph;
        NodeInstance* m_pPopupNode = nullptr;

    };

    class NodeInstance {
        using InputPin = PinInstance*;
        using OutputPin = PinInstance*;
    public:
        explicit NodeInstance(NodeEditorInstance* pEditor)
            : m_pEditor(pEditor)
        { }

        virtual ~NodeInstance();

        virtual void Draw() = 0;
        virtual InputPinInstance* AddInputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) { return nullptr; }
        virtual OutputPinInstance* AddOutputPin(SR_UTILS_NS::StringView name, PinTypeInfo type) { return nullptr; }
        virtual void SetPosition(const SR_MATH_NS::FVector2& position) { }
        virtual void SetTitle(SR_UTILS_NS::StringView title) { }
        virtual void RemovePins() { }
        virtual void LinkTo(NodeInstance* pTargetNode, uint32_t sourcePin, uint32_t targetPin) { }
        virtual void SetUserData(void* pUserData) { m_pUserData = pUserData; }

        void SetProgress(std::optional<float_t> progress) { m_progress = progress; }

        SR_NODISCARD uint32_t GetPinIndex(PinInstance* pPin) const;
        SR_NODISCARD virtual SR_MATH_NS::FVector2 GetPosition() const { return SR_MATH_NS::FVector2(); }
        SR_NODISCARD NodeEditorInstance* GetEditor() const { return m_pEditor; }
        SR_NODISCARD void* GetUserData() const { return m_pUserData; }
        SR_NODISCARD const SR_MATH_NS::FRect& GetNodeRect() const { return m_nodeRect; }
        SR_NODISCARD LinkInstance* GetInputLink(NodeInstance* pNode) const;
        SR_NODISCARD LinkInstance* GetOutputLink(NodeInstance* pNode) const;

        SR_NODISCARD const SR_UTILS_NS::Vector<InputPin>& GetInputs() const { return m_inputPins; }
        SR_NODISCARD const SR_UTILS_NS::Vector<OutputPin>& GetOutputs() const { return m_outputPins; }

    protected:
        void* m_pUserData = nullptr;
        std::optional<float_t> m_progress;
        NodeEditorInstance* m_pEditor = nullptr;
        SR_UTILS_NS::Vector<InputPin> m_inputPins;
        SR_UTILS_NS::Vector<OutputPin> m_outputPins;
        SR_MATH_NS::FRect m_nodeRect;

    };

    class PinInstance {
    public:
        virtual void Draw() = 0;
        virtual ~PinInstance() = default;

        SR_NODISCARD PinTypeInfo GetType() const { return m_type; }
        void SetType(PinTypeInfo type) { m_type = type; }

        SR_NODISCARD SR_UTILS_NS::StringView GetName() const { return m_name; }
        void SetName(SR_UTILS_NS::StringView name);

        SR_NODISCARD NodeInstance* GetNode() const { return m_pNode; }
        void SetNode(NodeInstance* pNode) { m_pNode = pNode; }

        SR_NODISCARD bool IsLinked() const { return !m_links.empty(); }
        SR_NODISCARD virtual bool IsInput() const = 0;
        SR_NODISCARD bool IsConnectedTo(PinInstance* pPin, std::optional<bool> isInput = std::nullopt) const;
        SR_NODISCARD LinkInstance* FindLink(PinInstance* pPin, std::optional<bool> isInput = std::nullopt) const;
        SR_NODISCARD const SR_UTILS_NS::Vector<LinkInstance*>& GetLinks() const { return m_links; }

        void ClearLinks() { m_links.clear(); }
        void AddLink(LinkInstance* pLink) { m_links.emplace_back(pLink); }
        void RemoveLink(LinkInstance* pLink) {
            m_links.erase(std::remove(m_links.begin(), m_links.end(), pLink), m_links.end());
        }

    private:
        NodeInstance* m_pNode = nullptr;
        SR_UTILS_NS::Vector<LinkInstance*> m_links;
        PinTypeInfo m_type;
        SR_UTILS_NS::String m_name;

    };

    class InputPinInstance : public PinInstance {
    public:
        bool IsInput() const override { return true; }
    };
    class OutputPinInstance : public PinInstance {
    public:
        bool IsInput() const override { return false; }
    };
}

namespace SR_GRAPH_GUI_NS::Immediate::NodeEditor {
    // NodeEditor wrappers
    enum class NodeEditorStyleColor : uint8_t {
        Bg, Grid, NodeBg, NodeBorder, HovNodeBorder, SelNodeBorder,
        NodeSelRect, NodeSelRectBorder, HovLinkBorder, SelLinkBorder,
        HighlightLinkBorder, LinkSelRect, LinkSelRectBorder,
        PinRect, PinRectBorder, Flow, FlowMarker, GroupBg, GroupBorder
    };

    enum NodeEditorStyleVar : uint8_t
    {
        NodePadding,
        NodeRounding,
        NodeBorderWidth,
        HoveredNodeBorderWidth,
        SelectedNodeBorderWidth,
        PinRounding,
        PinBorderWidth,
        LinkStrength,
        SourceDirection,
        TargetDirection,
        ScrollDuration,
        FlowMarkerDistance,
        FlowSpeed,
        FlowDuration,
        PivotAlignment,
        PivotSize,
        PivotScale,
        PinCorners,
        PinRadius,
        PinArrowSize,
        PinArrowWidth,
        GroupRounding,
        GroupBorderWidth,
        HighlightConnectedLinks,
        SnapLinkToPinDir,
        Count
    };

    SR_IMMEDIATE_GUI_DLL_API extern void* CreateEditor(const char* settingsFile);
    SR_IMMEDIATE_GUI_DLL_API extern void DestroyEditor(void* editor);
    SR_IMMEDIATE_GUI_DLL_API extern void SetCurrentEditor(void* editor);
    SR_IMMEDIATE_GUI_DLL_API extern void NavigateToContent();
    SR_IMMEDIATE_GUI_DLL_API extern bool BeginNodeEditor(const char* id, const SR_MATH_NS::FVector2& size = SR_MATH_NS::FVector2());
    SR_IMMEDIATE_GUI_DLL_API extern void EndNodeEditor();
    SR_IMMEDIATE_GUI_DLL_API extern void ResumeNodeEditor();
    SR_IMMEDIATE_GUI_DLL_API extern void SuspendNodeEditor();
    SR_IMMEDIATE_GUI_DLL_API extern void BeginNode(uintptr_t nodeId);
    SR_IMMEDIATE_GUI_DLL_API extern void EndNode();
    SR_IMMEDIATE_GUI_DLL_API extern void BeginPin(uintptr_t pinId, bool isInput);
    SR_IMMEDIATE_GUI_DLL_API extern void PinPivotAlignment(const SR_MATH_NS::FVector2& alignment);
    SR_IMMEDIATE_GUI_DLL_API extern void PinPivotSize(const SR_MATH_NS::FVector2& size);
    SR_IMMEDIATE_GUI_DLL_API extern void EndPin();
    SR_IMMEDIATE_GUI_DLL_API extern void Link(uintptr_t linkId, uintptr_t startPinId, uintptr_t endPinId);
    SR_IMMEDIATE_GUI_DLL_API extern bool BeginCreate();
    SR_IMMEDIATE_GUI_DLL_API extern bool QueryNewLink(uintptr_t* startPinId, uintptr_t* endPinId);
    SR_IMMEDIATE_GUI_DLL_API extern bool AcceptNewItem();
    SR_IMMEDIATE_GUI_DLL_API extern void EndCreate();
    SR_IMMEDIATE_GUI_DLL_API extern bool BeginDelete();
    SR_IMMEDIATE_GUI_DLL_API extern bool QueryDeletedLink(uintptr_t* linkId, uintptr_t* startPinId, uintptr_t* endPinId);
    SR_IMMEDIATE_GUI_DLL_API extern bool QueryDeletedNode(uintptr_t* nodeId);
    SR_IMMEDIATE_GUI_DLL_API extern void EndDelete();
    SR_IMMEDIATE_GUI_DLL_API extern bool ShowBackgroundContextMenu();
    SR_IMMEDIATE_GUI_DLL_API extern bool ShowNodeContextMenu(uintptr_t* nodeId);
    SR_IMMEDIATE_GUI_DLL_API extern int GetSelectedNodes(uintptr_t* nodeIds, int maxCount);
    SR_IMMEDIATE_GUI_DLL_API extern int GetSelectedLinks(uintptr_t* linkIds, int maxCount);
    SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 ScreenToCanvas(const SR_MATH_NS::FVector2& screenPos);
    SR_IMMEDIATE_GUI_DLL_API extern void SetNodePosition(uintptr_t nodeId, const SR_MATH_NS::FVector2& position);
    SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetNodePosition(uintptr_t nodeId);
    SR_IMMEDIATE_GUI_DLL_API extern void PushNodeEditorStyleColor(NodeEditorStyleColor colorIndex, const SR_MATH_NS::FColor& color);
    SR_IMMEDIATE_GUI_DLL_API extern void PopNodeEditorStyleColor(int count = 1);
    SR_IMMEDIATE_GUI_DLL_API extern void PushNodeEditorStyleVar(NodeEditorStyleVar varIndex, float value);
    SR_IMMEDIATE_GUI_DLL_API extern void PushNodeEditorStyleVar(NodeEditorStyleVar varIndex, const SR_MATH_NS::FVector2& value);
    SR_IMMEDIATE_GUI_DLL_API extern void PushNodeEditorStyleVar(NodeEditorStyleVar varIndex, const SR_MATH_NS::FVector4& value);
    SR_IMMEDIATE_GUI_DLL_API extern void PopNodeEditorStyleVar(int count = 1);
    SR_IMMEDIATE_GUI_DLL_API extern void* GetNodeBackgroundDrawList(uintptr_t nodeId);
}

#endif //SR_ENGINE_IMMEDIATE_GUI_NODE_EDITOR_H
