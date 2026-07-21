//
// Created by Monika on 11.07.2026.
//

#ifndef SR_ENGINE_IMMEDIATE_GUI_IM_GUI_THEME_H
#define SR_ENGINE_IMMEDIATE_GUI_IM_GUI_THEME_H

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Utils/Resources/Asset.h>

namespace SR_GRAPH_GUI_NS::Immediate {
    SR_ENUM_NS_CLASS_T(ImGUIThemeVec2Var, uint8_t,
        WindowPadding,
        WindowMinSize,
        WindowTitleAlign,
        FramePadding,
        ItemSpacing,
        ItemInnerSpacing,
        CellPadding,
        TouchExtraPadding,
        TableAngledHeadersTextAlign,
        ButtonTextAlign,
        SelectableTextAlign,
        SeparatorTextAlign,
        SeparatorTextPadding,
        DisplayWindowPadding,
        DisplaySafeAreaPadding
    )

    SR_ENUM_NS_CLASS_T(ImGUIThemeBoolVar, uint8_t,
        AntiAliasedLines,
        AntiAliasedLinesUseTex,
        AntiAliasedFill,
        DockingNodeHasCloseButton
    )

    SR_ENUM_NS_CLASS_T(ImGUIThemeFloatVar, uint16_t,
        FontSizeBase,
        FontScaleMain,
        FontScaleDpi,
        Alpha,
        DisabledAlpha,
        WindowRounding,
        WindowBorderSize,
        WindowBorderHoverPadding,
        ChildRounding,
        ChildBorderSize,
        PopupRounding,
        PopupBorderSize,
        FrameRounding,
        FrameBorderSize,
        IndentSpacing,
        ColumnsMinSpacing,
        ScrollbarSize,
        ScrollbarRounding,
        ScrollbarPadding,
        GrabMinSize,
        GrabRounding,
        LogSliderDeadzone,
        ImageRounding,
        ImageBorderSize,
        TabRounding,
        TabBorderSize,
        TabMinWidthBase,
        TabMinWidthShrink,
        TabCloseButtonMinWidthSelected,
        TabCloseButtonMinWidthUnselected,
        TabBarBorderSize,
        TabBarOverlineSize,
        TableAngledHeadersAngle,
        TreeLinesSize,
        TreeLinesRounding,
        MenuItemRounding,
        SelectableRounding,
        DragDropTargetRounding,
        DragDropTargetBorderSize,
        DragDropTargetPadding,
        ColorMarkerSize,
        InputTextCursorSize,
        SeparatorSize,
        SeparatorTextBorderSize,
        DockingSeparatorSize,
        MouseCursorScale,
        CurveTessellationTol,
        CircleTessellationMaxError,
        HoverStationaryDelay,
        HoverDelayShort,
        HoverDelayNormal
    )

    /// @extension(theme)
    class ImGUITheme : public SR_UTILS_NS::Asset {
        SR_CLASS()
        using Super = SR_UTILS_NS::Asset;
    public:
        /// @method @editorButton
        void Apply();
        /// @method @editorButton
        void StoreCurrentTheme();
        /// @method @editorButton
        void ImportHardcodedTheme();

    private:
        /// @property @onChanged(Apply)
        std::map<SR_GRAPH_GUI_NS::Immediate::ImGUIThemeBoolVar, bool> m_boolSettings;
        /// @property @onChanged(Apply)
        std::map<SR_GRAPH_GUI_NS::Immediate::ImGUIThemeFloatVar, float_t> m_floatSettings;
        /// @property @onChanged(Apply)
        std::map<SR_GRAPH_GUI_NS::Immediate::ImGUIThemeVec2Var, SR_MATH_NS::FVector2> m_vec2Settings;
        /// @property @onChanged(Apply)
        std::map<SR_GRAPH_GUI_NS::Immediate::StyleColor, SR_MATH_NS::FColor> m_colorSettings;

    };
}

#endif //SR_ENGINE_IMMEDIATE_GUI_IM_GUI_THEME_H
