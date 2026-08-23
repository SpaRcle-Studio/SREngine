//
// Created by Monika on 11.07.2026.
//

#include <ImmediateGUI/GUI/NodeEditor.h>
#include <ImmediateGUI/Impl/ImGUI.h>

namespace SR_GRAPH_GUI_NS::Immediate::NodeEditor {
#if defined(SR_USE_IMGUI_NODE_EDITOR) && defined(SR_USE_IMGUI)
    void* CreateEditor(const char* settingsFile) {
        ax::NodeEditor::Config config;
        if (settingsFile) {
            config.SettingsFile = settingsFile;
        }
        return ax::NodeEditor::CreateEditor(&config);
    }

    void DestroyEditor(void* editor) {
        if (editor) {
            ax::NodeEditor::DestroyEditor(reinterpret_cast<ax::NodeEditor::EditorContext*>(editor));
        }
    }

    void SetCurrentEditor(void* editor) {
        ax::NodeEditor::SetCurrentEditor(reinterpret_cast<ax::NodeEditor::EditorContext*>(editor));
    }

    void NavigateToContent() {
        ax::NodeEditor::NavigateToContent();
    }

    bool BeginNodeEditor(const char* id, const SR_MATH_NS::FVector2& size) {
        ax::NodeEditor::Begin(id, F2ToImV2(size));
        return true;
    }

    void EndNodeEditor() {
        ax::NodeEditor::End();
    }

    void ResumeNodeEditor() {
        ax::NodeEditor::Resume();
    }

    void SuspendNodeEditor() {
        ax::NodeEditor::Suspend();
    }

    void BeginNode(uintptr_t nodeId) {
        ax::NodeEditor::BeginNode(ax::NodeEditor::NodeId(nodeId));
    }

    void EndNode() {
        ax::NodeEditor::EndNode();
    }

    void BeginPin(uintptr_t pinId, bool isInput) {
        ax::NodeEditor::BeginPin(
            ax::NodeEditor::PinId(pinId),
            isInput ? ax::NodeEditor::PinKind::Input : ax::NodeEditor::PinKind::Output
        );
    }

    void PinPivotAlignment(const SR_MATH_NS::FVector2& alignment) {
        ax::NodeEditor::PinPivotAlignment(F2ToImV2(alignment));
    }

    void PinPivotSize(const SR_MATH_NS::FVector2& size) {
        ax::NodeEditor::PinPivotSize(F2ToImV2(size));
    }

    void EndPin() {
        ax::NodeEditor::EndPin();
    }

    void Link(uintptr_t linkId, uintptr_t startPinId, uintptr_t endPinId) {
        ax::NodeEditor::Link(
            ax::NodeEditor::LinkId(linkId),
            ax::NodeEditor::PinId(startPinId),
            ax::NodeEditor::PinId(endPinId)
        );
    }

    bool BeginCreate() {
        return ax::NodeEditor::BeginCreate();
    }

    bool QueryNewLink(uintptr_t* startPinId, uintptr_t* endPinId) {
        ax::NodeEditor::PinId startId, endId;
        if (ax::NodeEditor::QueryNewLink(&startId, &endId)) {
            if (startPinId) *startPinId = startId.Get();
            if (endPinId) *endPinId = endId.Get();
            return true;
        }
        return false;
    }

    bool AcceptNewItem() {
        return ax::NodeEditor::AcceptNewItem();
    }

    void EndCreate() {
        ax::NodeEditor::EndCreate();
    }

    bool BeginDelete() {
        return ax::NodeEditor::BeginDelete();
    }

    bool QueryDeletedLink(uintptr_t* linkId, uintptr_t* startPinId, uintptr_t* endPinId) {
        ax::NodeEditor::LinkId linkIdObj;
        ax::NodeEditor::PinId startId, endId;
        if (ax::NodeEditor::QueryDeletedLink(&linkIdObj, startPinId ? &startId : nullptr, endPinId ? &endId : nullptr)) {
            if (linkId) *linkId = linkIdObj.Get();
            if (startPinId && startId) *startPinId = startId.Get();
            if (endPinId && endId) *endPinId = endId.Get();
            return true;
        }
        return false;
    }

    bool QueryDeletedNode(uintptr_t* nodeId) {
        ax::NodeEditor::NodeId nodeIdObj;
        if (ax::NodeEditor::QueryDeletedNode(&nodeIdObj)) {
            if (nodeId) *nodeId = nodeIdObj.Get();
            return true;
        }
        return false;
    }

    void EndDelete() {
        ax::NodeEditor::EndDelete();
    }

    bool ShowBackgroundContextMenu() {
        return ax::NodeEditor::ShowBackgroundContextMenu();
    }

    bool ShowNodeContextMenu(uintptr_t* nodeId) {
        ax::NodeEditor::NodeId nodeIdObj;
        if (ax::NodeEditor::ShowNodeContextMenu(&nodeIdObj)) {
            if (nodeId) *nodeId = nodeIdObj.Get();
            return true;
        }
        return false;
    }

    int GetSelectedNodes(uintptr_t* nodeIds, int maxCount) {
        if (!nodeIds || maxCount <= 0) {
            return ax::NodeEditor::GetSelectedNodes(nullptr, 0);
        }
        std::vector<ax::NodeEditor::NodeId> ids(maxCount);
        int count = ax::NodeEditor::GetSelectedNodes(ids.data(), maxCount);
        for (int i = 0; i < count; ++i) {
            nodeIds[i] = ids[i].Get();
        }
        return count;
    }

    int GetSelectedLinks(uintptr_t* linkIds, int maxCount) {
        if (!linkIds || maxCount <= 0) {
            return ax::NodeEditor::GetSelectedLinks(nullptr, 0);
        }
        std::vector<ax::NodeEditor::LinkId> ids(maxCount);
        int count = ax::NodeEditor::GetSelectedLinks(ids.data(), maxCount);
        for (int i = 0; i < count; ++i) {
            linkIds[i] = ids[i].Get();
        }
        return count;
    }

    SR_MATH_NS::FVector2 ScreenToCanvas(const SR_MATH_NS::FVector2& screenPos) {
        auto&& result = ax::NodeEditor::ScreenToCanvas(F2ToImV2(screenPos));
        return ImV2ToF2(result);
    }

    void SetNodePosition(uintptr_t nodeId, const SR_MATH_NS::FVector2& position) {
        ax::NodeEditor::SetNodePosition(ax::NodeEditor::NodeId(nodeId), F2ToImV2(position));
    }

    SR_MATH_NS::FVector2 GetNodePosition(uintptr_t nodeId) {
        auto&& result = ax::NodeEditor::GetNodePosition(ax::NodeEditor::NodeId(nodeId));
        return ImV2ToF2(result);
    }

    void PushNodeEditorStyleColor(NodeEditorStyleColor colorIndex, const SR_MATH_NS::FColor& color) {
        ax::NodeEditor::PushStyleColor(static_cast<ax::NodeEditor::StyleColor>(colorIndex), FCToImV4(color));
    }

    void PopNodeEditorStyleColor(int count) {
        ax::NodeEditor::PopStyleColor(count);
    }

    void PushNodeEditorStyleVar(NodeEditorStyleVar varIndex, float value) {
        ax::NodeEditor::PushStyleVar(static_cast<ax::NodeEditor::StyleVar>(varIndex), value);
    }

    void PushNodeEditorStyleVar(NodeEditorStyleVar varIndex, const SR_MATH_NS::FVector2& value) {
        ax::NodeEditor::PushStyleVar(static_cast<ax::NodeEditor::StyleVar>(varIndex), F2ToImV2(value));
    }

    void PushNodeEditorStyleVar(NodeEditorStyleVar varIndex, const SR_MATH_NS::FVector4& value) {
        ax::NodeEditor::PushStyleVar(static_cast<ax::NodeEditor::StyleVar>(varIndex), F4ToImV4(value));
    }

    void PopNodeEditorStyleVar(int count) {
        ax::NodeEditor::PopStyleVar(count);
    }

    void* GetNodeBackgroundDrawList(uintptr_t nodeId) {
        return ax::NodeEditor::GetNodeBackgroundDrawList(ax::NodeEditor::NodeId(nodeId));
    }
#else
    void* CreateEditor(const char* settingsFile) { return nullptr; }
    void DestroyEditor(void* editor) { }
    void SetCurrentEditor(void* editor) { }
    bool BeginNodeEditor(const char* id, const SR_MATH_NS::FVector2& size) { return false; }
    void EndNodeEditor() { }
    void ResumeNodeEditor() { }
    void SuspendNodeEditor() { }
    void BeginNode(uintptr_t nodeId) { }
    void EndNode() { }
    void BeginPin(uintptr_t pinId, bool isInput) { }
    void PinPivotAlignment(const SR_MATH_NS::FVector2& alignment) { }
    void PinPivotSize(const SR_MATH_NS::FVector2& size) { }
    void EndPin() { }
    void Link(uintptr_t linkId, uintptr_t startPinId, uintptr_t endPinId) { }
    bool BeginCreate() { return false; }
    bool QueryNewLink(uintptr_t* startPinId, uintptr_t* endPinId) { return false; }
    bool AcceptNewItem() { return false; }
    void EndCreate() { }
    bool BeginDelete() { return false; }
    bool QueryDeletedLink(uintptr_t* linkId, uintptr_t* startPinId, uintptr_t* endPinId) { return false; }
    bool QueryDeletedNode(uintptr_t* nodeId) { return false; }
    void EndDelete() { }
    bool ShowBackgroundContextMenu() { return false; }
    bool ShowNodeContextMenu(uintptr_t* nodeId) { return false; }
    int GetSelectedNodes(uintptr_t* nodeIds, int maxCount) { return 0; }
    int GetSelectedLinks(uintptr_t* linkIds, int maxCount) { return 0; }
    SR_MATH_NS::FVector2 ScreenToCanvas(const SR_MATH_NS::FVector2& screenPos) { return screenPos; }
    void SetNodePosition(uintptr_t nodeId, const SR_MATH_NS::FVector2& position) { }
    SR_MATH_NS::FVector2 GetNodePosition(uintptr_t nodeId) { return SR_MATH_NS::FVector2(0.0f, 0.0f); }
    void PushNodeEditorStyleColor(NodeEditorStyleColor colorIndex, const SR_MATH_NS::FColor& color) { }
    void PopNodeEditorStyleColor(int count) { }
    void PushNodeEditorStyleVar(NodeEditorStyleVar varIndex, float value) { }
    void PushNodeEditorStyleVar(NodeEditorStyleVar varIndex, const SR_MATH_NS::FVector2& value) { }
    void PushNodeEditorStyleVar(NodeEditorStyleVar varIndex, const SR_MATH_NS::FVector4& value) { }
    void PopNodeEditorStyleVar(int count) { }
    void* GetNodeBackgroundDrawList(uintptr_t nodeId) { return nullptr; }
    void NavigateToContent() { }
#endif
}

namespace SR_IMMEDIATE_GUI_NS {
    NodeInstance::~NodeInstance() {
        m_inputPins.delete_contents();
        m_outputPins.delete_contents();
    }

    uint32_t NodeInstance::GetPinIndex(PinInstance *pPin) const {
        for (uint32_t i = 0; i < m_inputPins.size(); ++i) {
            if (m_inputPins[i] == pPin) {
                return i;
            }
        }
        for (uint32_t i = 0; i < m_outputPins.size(); ++i) {
            if (m_outputPins[i] == pPin) {
                return i;
            }
        }
        return SR_ID_INVALID;
    }

    LinkInstance* NodeInstance::GetInputLink(NodeInstance* pNode) const {
        for (auto&& pPin : m_inputPins) {
            for (auto&& pLink : pPin->GetLinks()) {
                if (pLink->GetOutputPin()->GetNode() == pNode) {
                    return pLink;
                }
            }
        }
        return nullptr;
    }

    LinkInstance* NodeInstance::GetOutputLink(NodeInstance* pNode) const {
        for (auto&& pPin : m_outputPins) {
            for (auto&& pLink : pPin->GetLinks()) {
                if (pLink->GetInputPin()->GetNode() == pNode) {
                    return pLink;
                }
            }
        }
        return nullptr;
    }

    NodeEditorInstance::~NodeEditorInstance() {
        m_nodes.delete_contents();
        m_freeNodes.delete_contents();
        m_freeInputPins.delete_contents();
        m_freeOutputPins.delete_contents();
        m_links.delete_contents();
        m_freeLinks.delete_contents();
    }

    void NodeEditorInstance::OnInputPinRemoved(PinInstance* pPin) {
        m_freeInputPins.emplace_back(pPin);
    }

    void NodeEditorInstance::OnOutputPinRemoved(PinInstance* pPin) {
        m_freeOutputPins.emplace_back(pPin);
    }

    void PinInstance::SetName(SR_UTILS_NS::StringView name) {
        if (name.empty()) {
            m_name = "Pin";
        }
        else {
            m_name = name;
        }
    }

    bool PinInstance::IsConnectedTo(PinInstance* pPin, std::optional<bool> isInput) const {
        for (auto&& pLink : m_links) {
            if (isInput) {
                if (pLink->GetInputPin() == pPin && *isInput) {
                    return true;
                }
                if (pLink->GetOutputPin() == pPin && !*isInput) {
                    return true;
                }
            }
            if (pLink->GetInputPin() == pPin || pLink->GetOutputPin() == pPin) {
                return true;
            }
        }
        return false;
    }

    LinkInstance* PinInstance::FindLink(PinInstance* pPin, std::optional<bool> isInput) const {
        for (auto&& pLink : m_links) {
            if (isInput) {
                if (pLink->GetInputPin() == pPin && *isInput) {
                    return pLink;
                }
                if (pLink->GetOutputPin() == pPin && !*isInput) {
                    return pLink;
                }
            }
            if (pLink->GetInputPin() == pPin || pLink->GetOutputPin() == pPin) {
                return pLink;
            }
        }
        return nullptr;
    }

    IconType PinInstance::GetIconType() const {
        if (m_type.isFlow || !m_type.pType) {
            return IconType::Flow;
        }
        switch (m_type.pType->category) {
            case Utils::Reflection::ReflectedCategoryType::Value:
            case Utils::Reflection::ReflectedCategoryType::Object:
                return IconType::Diamond;
            case Utils::Reflection::ReflectedCategoryType::Arithmetic:
                if (m_type.pType->detailedType == "bool") {
                    return IconType::Square;
                }
            case Utils::Reflection::ReflectedCategoryType::String:
            case Utils::Reflection::ReflectedCategoryType::Enum:
                return IconType::Circle;
            case Utils::Reflection::ReflectedCategoryType::MathObject:
            case Utils::Reflection::ReflectedCategoryType::MathSize:
            case Utils::Reflection::ReflectedCategoryType::MathVector:
            case Utils::Reflection::ReflectedCategoryType::MathRect:
                return IconType::RoundSquare;
            case Utils::Reflection::ReflectedCategoryType::Container:
                return IconType::Grid;
            default:
                break;
        }
        return IconType::Flow;
    }

    bool PinTypeInfo::operator==(const PinTypeInfo& other) const {
        if (isFlow != other.isFlow) {
            return false;
        }
        if (bool(pType) != bool(other.pType)) {
            return false;
        }
        if (pType && other.pType) {
            return *pType == *other.pType;
        }
        return true;
    }

    PinTypeInfo::PinTypeInfo(const PinTypeInfo& other) {
        isFlow = other.isFlow;
        pType = other.pType;
    }

    PinTypeInfo& PinTypeInfo::operator=(const PinTypeInfo& other) {
        if (this != &other) {
            isFlow = other.isFlow;
            pType = other.pType;
        }
        return *this;
    }

    PinTypeInfo::~PinTypeInfo() = default;
}
