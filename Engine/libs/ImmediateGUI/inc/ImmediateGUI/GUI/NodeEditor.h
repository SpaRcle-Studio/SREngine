//
// Created by Monika on 11.07.2026.
//

#ifndef SR_ENGINE_IMMEDIATE_GUI_NODE_EDITOR_H
#define SR_ENGINE_IMMEDIATE_GUI_NODE_EDITOR_H

#include <ImmediateGUI/GUI/ImmediateGUI.h>

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
