//
// Created by Monika on 10.05.2025.
//

#ifndef SR_ENGINE_RENDERER_IMMEDIATE_GUI_H
#define SR_ENGINE_RENDERER_IMMEDIATE_GUI_H

#include "ImmediateGUI/macros.h"
#include <ImmediateGUI/stdInclude.h>

#include <Utils/Math/Rect.h>
#include <Utils/Math/Vector4.h>
#include <Utils/FileSystem/Path.h>

#define SR_COL32_R_SHIFT    0
#define SR_COL32_G_SHIFT    8
#define SR_COL32_B_SHIFT    16
#define SR_COL32_A_SHIFT    24
#define SR_COL32_A_MASK     0xFF000000

#define SR_COL32(R,G,B,A)    (((uint32_t)(A)<<SR_COL32_A_SHIFT) | ((uint32_t)(B)<<SR_COL32_B_SHIFT) | ((uint32_t)(G)<<SR_COL32_G_SHIFT) | ((uint32_t)(R)<<SR_COL32_R_SHIFT))

#ifdef Always
    #undef Always
#endif

namespace SR_GRAPH_GUI_NS {
    SR_ENUM_NS_CLASS(IconType,
        Flow,
        Circle,
        Square,
        Grid,
        RoundSquare,
        Diamond
    );

    struct PayloadArrayData {
        void* data = nullptr;
        uint64_t size = 0;
    };

    SR_ENUM_NS_STRUCT_T(ChildWindowFlags, uint32_t,
        None                    = 0,
        Borders                 = 1 << 0,   // Show an outer border and enable WindowPadding. (IMPORTANT: this is always == 1 == true for legacy reason)
        AlwaysUseWindowPadding  = 1 << 1,   // Pad with style.WindowPadding even if no border are drawn (no padding by default for non-bordered child windows because it makes more sense)
        ResizeX                 = 1 << 2,   // Allow resize from right border (layout direction). Enable .ini saving (unless ImGuiWindowFlags_NoSavedSettings passed to window flags)
        ResizeY                 = 1 << 3,   // Allow resize from bottom border (layout direction). "
        AutoResizeX             = 1 << 4,   // Enable auto-resizing width. Read "IMPORTANT: Size measurement" details above.
        AutoResizeY             = 1 << 5,   // Enable auto-resizing height. Read "IMPORTANT: Size measurement" details above.
        AlwaysAutoResize        = 1 << 6,   // Combined with AutoResizeX/AutoResizeY. Always measure size even when child is hidden, always return true, always disable clipping optimization! NOT RECOMMENDED.
        FrameStyle              = 1 << 7,   // Style the child window like a framed item: use FrameBg, FrameRounding, FrameBorderSize, FramePadding instead of ChildBg, ChildRounding, ChildBorderSize, WindowPadding.
        NavFlattened            = 1 << 8   // [BETA] Share focus scope, allow keyboard/gamepad navigation to cross over parent border to this child or between sibling child windows.
    )

    SR_ENUM_NS_STRUCT_T(WindowFlags, uint32_t,
        None                   = 0,
        NoTitleBar             = 1 << 0,   // Disable title-bar
        NoResize               = 1 << 1,   // Disable user resizing with the lower-right grip
        NoMove                 = 1 << 2,   // Disable user moving the window
        NoScrollbar            = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
        NoScrollWithMouse      = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
        NoCollapse             = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
        AlwaysAutoResize       = 1 << 6,   // Resize every window to its content every frame
        NoBackground           = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
        NoSavedSettings        = 1 << 8,   // Never load/save settings in .ini file
        NoMouseInputs          = 1 << 9,   // Disable catching mouse, hovering test with pass through.
        MenuBar                = 1 << 10,  // Has a menu-bar
        HorizontalScrollbar    = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
        NoFocusOnAppearing     = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
        NoBringToFrontOnFocus  = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
        AlwaysVerticalScrollbar= 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
        AlwaysHorizontalScrollbar=1<< 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
        NoNavInputs            = 1 << 16,  // No keyboard/gamepad navigation within the window
        NoNavFocus             = 1 << 17,  // No focusing toward this window with keyboard/gamepad navigation (e.g. skipped by Ctrl+Tab)
        UnsavedDocument        = 1 << 18,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
        NoDocking              = 1 << 19,  // Disable docking of this window
        NoNav                  = NoNavInputs   | NoNavFocus,
        NoDecoration           = NoTitleBar    | NoResize    | NoScrollbar | NoCollapse,
        NoInputs               = NoMouseInputs | NoNavInputs | NoNavFocus,

        // [Internal]
        DockNodeHost           = 1 << 23,  // Don't use! For internal use by Begin()/NewFrame()
        ChildWindow            = 1 << 24,  // Don't use! For internal use by BeginChild()
        Tooltip                = 1 << 25,  // Don't use! For internal use by BeginTooltip()
        Popup                  = 1 << 26,  // Don't use! For internal use by BeginPopup()
        Modal                  = 1 << 27,  // Don't use! For internal use by BeginPopupModal()
        ChildMenu              = 1 << 28  // Don't use! For internal use by BeginMenu()
    )

    namespace Immediate {
        using WindowFlags = SR_GRAPH_GUI_NS::WindowFlags;
        using ChildWindowFlags = SR_GRAPH_GUI_NS::ChildWindowFlags;

        inline constexpr float_t DEFAULT_FONT_SIZE = 14.0f;

        SR_IMMEDIATE_GUI_DLL_API extern void NewFrame();
        SR_IMMEDIATE_GUI_DLL_API extern void Render();
        SR_IMMEDIATE_GUI_DLL_API extern void UpdatePlatformWindows();
        SR_IMMEDIATE_GUI_DLL_API extern void RenderPlatformWindowsDefault();

        enum class ImmediateDataType : uint8_t {
            Int8,
            UInt8,
            Int16,
            UInt16,
            Int32,
            UInt32,
            Int64,
            UInt64,
            Float,
            Double,
            COUNT
        };

        SR_ENUM_NS_CLASS_T(StyleColor, uint32_t,
            Text,
            TextDisabled,
            WindowBg,              // Background of normal windows
            ChildBg,               // Background of child windows
            PopupBg,               // Background of popups, menus, tooltips windows
            Border,
            BorderShadow,
            FrameBg,               // Background of checkbox, radio button, plot, slider, text input
            FrameBgHovered,
            FrameBgActive,
            TitleBg,               // Title bar
            TitleBgActive,         // Title bar when focused
            TitleBgCollapsed,      // Title bar when collapsed
            MenuBarBg,
            ScrollbarBg,
            ScrollbarGrab,
            ScrollbarGrabHovered,
            ScrollbarGrabActive,
            CheckMark,             // Checkbox tick and RadioButton circle
            CheckboxSelectedBg,    // Checkbox background when Selected, otherwise use FrameBg
            SliderGrab,
            SliderGrabActive,
            Button,
            ButtonHovered,
            ButtonActive,
            Header,                // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
            HeaderHovered,
            HeaderActive,
            Separator,
            SeparatorHovered,
            SeparatorActive,
            ResizeGrip,            // Resize grip in lower-right and lower-left corners of windows.
            ResizeGripHovered,
            ResizeGripActive,
            InputTextCursor,       // InputText cursor/caret
            TabHovered,            // Tab background, when hovered
            Tab,                   // Tab background, when tab-bar is focused & tab is unselected
            TabSelected,           // Tab background, when tab-bar is focused & tab is selected
            TabSelectedOverline,   // Tab horizontal overline, when tab-bar is focused & tab is selected
            TabDimmed,             // Tab background, when tab-bar is unfocused & tab is unselected
            TabDimmedSelected,     // Tab background, when tab-bar is unfocused & tab is selected
            TabDimmedSelectedOverline,//..horizontal overline, when tab-bar is unfocused & tab is selected
            DockingPreview,        // Preview overlay color when about to docking something
            DockingEmptyBg,        // Background color for empty node (e.g. CentralNode with no window docked into it)
            PlotLines,
            PlotLinesHovered,
            PlotHistogram,
            PlotHistogramHovered,
            TableHeaderBg,         // Table header background
            TableBorderStrong,     // Table outer and header borders (prefer using Alpha=1.0 here)
            TableBorderLight,      // Table inner borders (prefer using Alpha=1.0 here)
            TableRowBg,            // Table row background (even rows)
            TableRowBgAlt,         // Table row background (odd rows)
            TextLink,              // Hyperlink color
            TextSelectedBg,        // Selected text inside an InputText
            TreeLines,             // Tree node hierarchy outlines when using ImGuiTreeNodeFlags_DrawLines
            DragDropTarget,        // Rectangle border highlighting a drop target
            DragDropTargetBg,      // Rectangle background highlighting a drop target
            UnsavedMarker,         // Unsaved Document marker (in window title and tabs)
            NavCursor,             // Color of keyboard/gamepad navigation cursor/rectangle, when visible
            NavWindowingHighlight, // Highlight window when using Ctrl+Tab
            NavWindowingDimBg,     // Darken/colorize entire screen behind the Ctrl+Tab window list, when active
            ModalWindowDimBg       // Darken/colorize entire screen behind a modal window, when one is active
        )

        enum class Direction {
            None    = -1,
            Left    = 0,
            Right   = 1,
            Up      = 2,
            Down    = 3,
            COUNT
        };

        SR_ENUM_NS_CLASS_T(StyleVar, uint32_t,
            Alpha,                      // float     Alpha
            DisabledAlpha,              // float     DisabledAlpha
            WindowPadding,              // ImVec2    WindowPadding
            WindowRounding,             // float     WindowRounding
            WindowBorderSize,           // float     WindowBorderSize
            WindowMinSize,              // ImVec2    WindowMinSize
            WindowTitleAlign,           // ImVec2    WindowTitleAlign
            ChildRounding,              // float     ChildRounding
            ChildBorderSize,            // float     ChildBorderSize
            PopupRounding,              // float     PopupRounding
            PopupBorderSize,            // float     PopupBorderSize
            FramePadding,               // ImVec2    FramePadding
            FrameRounding,              // float     FrameRounding
            FrameBorderSize,            // float     FrameBorderSize
            ItemSpacing,                // ImVec2    ItemSpacing
            ItemInnerSpacing,           // ImVec2    ItemInnerSpacing
            IndentSpacing,              // float     IndentSpacing
            CellPadding,                // ImVec2    CellPadding
            ScrollbarSize,              // float     ScrollbarSize
            ScrollbarRounding,          // float     ScrollbarRounding
            ScrollbarPadding,           // float     ScrollbarPadding
            GrabMinSize,                // float     GrabMinSize
            GrabRounding,               // float     GrabRounding
            ImageRounding,              // float     ImageRounding
            ImageBorderSize,            // float     ImageBorderSize
            TabRounding,                // float     TabRounding
            TabBorderSize,              // float     TabBorderSize
            TabMinWidthBase,            // float     TabMinWidthBase
            TabMinWidthShrink,          // float     TabMinWidthShrink
            TabBarBorderSize,           // float     TabBarBorderSize
            TabBarOverlineSize,         // float     TabBarOverlineSize
            TableAngledHeadersAngle,    // float     TableAngledHeadersAngle
            TableAngledHeadersTextAlign,// ImVec2  TableAngledHeadersTextAlign
            TreeLinesSize,              // float     TreeLinesSize
            TreeLinesRounding,          // float     TreeLinesRounding
            MenuItemRounding,           // float     MenuItemRounding
            SelectableRounding,         // float     SelectableRounding
            DragDropTargetRounding,     // float     DragDropTargetRounding
            ButtonTextAlign,            // ImVec2    ButtonTextAlign
            SelectableTextAlign,        // ImVec2    SelectableTextAlign
            SeparatorSize,              // float     SeparatorSize
            SeparatorTextBorderSize,    // float     SeparatorTextBorderSize
            SeparatorTextAlign,         // ImVec2    SeparatorTextAlign
            SeparatorTextPadding,       // ImVec2    SeparatorTextPadding
            DockingSeparatorSize        // float     DockingSeparatorSize
        )

        SR_ENUM_NS_STRUCT_T(InputTextFlags, uint32_t,
            None                = 0,
            CharsDecimal        = 1 << 0,   // Allow 0123456789.+-*/
            CharsHexadecimal    = 1 << 1,   // Allow 0123456789ABCDEFabcdef
            CharsUppercase      = 1 << 2,   // Turn a..z into A..Z
            CharsNoBlank        = 1 << 3,   // Filter out spaces, tabs
            AutoSelectAll       = 1 << 4,   // Select entire text when first taking mouse focus
            EnterReturnsTrue    = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
            CallbackCompletion  = 1 << 6,   // Callback on pressing TAB (for completion handling)
            CallbackHistory     = 1 << 7,   // Callback on pressing Up/Down arrows (for history handling)
            CallbackAlways      = 1 << 8,   // Callback on each iteration. User code may query cursor position, modify text buffer.
            CallbackCharFilter  = 1 << 9,   // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
            AllowTabInput       = 1 << 10,  // Pressing TAB input a '\t' character into the text field
            CtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
            NoHorizontalScroll  = 1 << 12,  // Disable following the cursor horizontally
            AlwaysOverwrite     = 1 << 13,  // Overwrite mode
            ReadOnly            = 1 << 14,  // Read-only mode
            Password            = 1 << 15,  // Password mode, display all characters as '*'
            NoUndoRedo          = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
            CharsScientific     = 1 << 17,  // Allow 0123456789.+-*/eE (Scientific notation input)
            CallbackResize      = 1 << 18,  // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
            CallbackEdit        = 1 << 19   // Callback on any edit (note that InputText() already returns true on edit, the callback is useful mainly to manipulate the underlying buffer while focus is active)
        )

        SR_ENUM_NS_STRUCT_T(DragDropFlags, uint32_t,
            None                         = 0,
            // BeginDragDropSource() flags
            SourceNoPreviewTooltip       = 1 << 0,   // Disable preview tooltip. By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disables this behavior.
            SourceNoDisableHover         = 1 << 1,   // By default, when dragging we clear data so that IsItemHovered() will return false, to avoid subsequent user code submitting tooltips. This flag disables this behavior so you can still call IsItemHovered() on the source item.
            SourceNoHoldToOpenOthers     = 1 << 2,   // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
            SourceAllowNullID            = 1 << 3,   // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is extremely unusual within the dear imgui ecosystem and so we made it explicit.
            SourceExtern                 = 1 << 4,   // External source (from outside of dear imgui), won't attempt to read current item/window info. Will always return true. Only one Extern source can be active simultaneously.
            PayloadAutoExpire            = 1 << 5,   // Automatically expire the payload if the source cease to be submitted (otherwise payloads are persisting while being dragged)
            PayloadNoCrossContext        = 1 << 6,   // Hint to specify that the payload may not be copied outside current dear imgui context.
            PayloadNoCrossProcess        = 1 << 7,   // Hint to specify that the payload may not be copied outside current process.
            // AcceptDragDropPayload() flags
            AcceptBeforeDelivery         = 1 << 10,  // AcceptDragDropPayload() will returns true even before the mouse button is released. You can then call IsDelivery() to test if the payload needs to be delivered.
            AcceptNoDrawDefaultRect      = 1 << 11,  // Do not draw the default highlight rectangle when hovering over target.
            AcceptNoPreviewTooltip       = 1 << 12,  // Request hiding the BeginDragDropSource tooltip from the BeginDragDropTarget site.
            AcceptDrawAsHovered          = 1 << 13,  // Accepting item will render as if hovered. Useful for e.g. a Button() used as a drop target.
            AcceptPeekOnly               = AcceptBeforeDelivery | AcceptNoDrawDefaultRect // For peeking ahead and inspecting the payload before delivery.
        )

        SR_ENUM_NS_STRUCT_T(ButtonFlags, uint32_t,
            None                   = 0,
            Repeat                 = 1 << 0,   // hold to repeat
            PressedOnClickRelease  = 1 << 1,   // return true on click + release on same item [DEFAULT if no PressedOn* flag is set]
            PressedOnClick         = 1 << 2,   // return true on click (default requires click+release)
            PressedOnRelease       = 1 << 3,   // return true on release (default requires click+release)
            PressedOnDoubleClick   = 1 << 4,   // return true on double-click (default requires click+release)
            FlattenChildren        = 1 << 5,   // allow interactions even if a child window is overlapping
            AllowItemOverlap       = 1 << 6,   // require previous frame HoveredId to either match id or be null before being usable, use along with SetItemAllowOverlap()
            DontClosePopups        = 1 << 7,   // disable automatically closing parent popup on press // [UNUSED]
            Disabled               = 1 << 8,   // disable interactions
            AlignTextBaseLine      = 1 << 9,   // vertically align button to match text baseline - ButtonEx() only // FIXME: Should be removed and handled by SmallButton(), not possible currently because of DC.CursorPosPrevLine
            NoKeyModifiers         = 1 << 10,  // disable interaction if a key modifier is held
            NoHoldingActiveID      = 1 << 11,  // don't set ActiveId while holding the mouse (ImGuiButtonFlags_PressedOnClick only)
            PressedOnDragDropHold  = 1 << 12,  // press when held into while we are drag and dropping another item (used by e.g. tree nodes, collapsing headers)
            NoNavFocus             = 1 << 13   // don't override navigation focus when activated
        )

        SR_ENUM_NS_STRUCT_T(ComboFlags, uint32_t,
            None                    = 0,
            PopupAlignLeft          = 1 << 0,   // Align the popup toward the left by default
            HeightSmall             = 1 << 1,   // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
            HeightRegular           = 1 << 2,   // Max ~8 items visible (default)
            HeightLarge             = 1 << 3,   // Max ~20 items visible
            HeightLargest           = 1 << 4,   // As many fitting items as possible
            NoArrowButton           = 1 << 5,   // Display on the preview box without the square arrow button
            NoPreview               = 1 << 6,   // Display only a square arrow button
            HeightMask              = HeightSmall | HeightRegular | HeightLarge | HeightLargest
        )

        SR_ENUM_NS_STRUCT_T(TreeNodeFlags, uint32_t,
            None                 = 0,
            Selected             = 1 << 0,   // Draw as selected
            Framed               = 1 << 1,   // Draw frame with background (e.g. for CollapsingHeader)
            AllowItemOverlap     = 1 << 2,   // Hit testing to allow subsequent widgets to overlap this one
            NoTreePushOnOpen     = 1 << 3,   // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
            NoAutoOpenOnLog      = 1 << 4,   // Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
            DefaultOpen          = 1 << 5,   // Default node to be open
            OpenOnDoubleClick    = 1 << 6,   // Need double-click to open node
            OpenOnArrow          = 1 << 7,   // Only open when clicking on the arrow part. If ImGuiTreeNodeFlags_OpenOnDoubleClick is also set, single-click arrow or double-click all box to open.
            Leaf                 = 1 << 8,   // No collapsing, no arrow (use as a convenience for leaf nodes).
            Bullet               = 1 << 9,   // Display a bullet instead of arrow
            FramePadding         = 1 << 10,  // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding().
            SpanAvailWidth       = 1 << 11,  // Extend hit box to the right-most edge, even if not framed. This is not the default in order to allow adding other items on the same line. In the future we may refactor the hit system to be front-to-back, allowing natural overlaps and then this can become the default.
            SpanFullWidth        = 1 << 12,  // Extend hit box to the left-most and right-most edges (bypass the indented area).
            NavLeftJumpsBackHere = 1 << 13,  // (WIP) Nav: left direction may move to this TreeNode() from any of its child (items submitted between TreeNode and TreePop)
            CollapsingHeader     = Framed | NoTreePushOnOpen | NoAutoOpenOnLog
        )

        SR_ENUM_NS_STRUCT_T(ColorEditFlags, uint32_t, // TODO: rename to ColorPickerFlags?
            None            = 0,
            NoAlpha         = 1 << 1,   //              // ColorEdit, ColorPicker, ColorButton: ignore Alpha component (will only read 3 components from the input pointer).
            NoPicker        = 1 << 2,   //              // ColorEdit: disable picker when clicking on color square.
            NoOptions       = 1 << 3,   //              // ColorEdit: disable toggling options menu when right-clicking on inputs/small preview.
            NoSmallPreview  = 1 << 4,   //              // ColorEdit, ColorPicker: disable color square preview next to the inputs. (e.g. to show only the inputs)
            NoInputs        = 1 << 5,   //              // ColorEdit, ColorPicker: disable inputs sliders/text widgets (e.g. to show only the small preview color square).
            NoTooltip       = 1 << 6,   //              // ColorEdit, ColorPicker, ColorButton: disable tooltip when hovering the preview.
            NoLabel         = 1 << 7,   //              // ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).
            NoSidePreview   = 1 << 8,   //              // ColorPicker: disable bigger color preview on right side of the picker, use small color square preview instead.
            NoDragDrop      = 1 << 9,   //              // ColorEdit: disable drag and drop target/source. ColorButton: disable drag and drop source.
            NoBorder        = 1 << 10,  //              // ColorButton: disable border (which is enforced by default)
            NoColorMarkers  = 1 << 11,  //              // ColorEdit: disable rendering R/G/B/A color marker. May also be disabled globally by setting style.ColorMarkerSize = 0.

            // Alpha preview
            // - Prior to 1.91.8 (2025/01/21): alpha was made opaque in the preview by default using old name ImGuiColorEditFlags_AlphaPreview.
            // - We now display the preview as transparent by default. You can use ImGuiColorEditFlags_AlphaOpaque to use old behavior.
            // - The new flags may be combined better and allow finer controls.
            AlphaOpaque     = 1 << 12,  //              // ColorEdit, ColorPicker, ColorButton: disable alpha in the preview,. Contrary to _NoAlpha it may still be edited when calling ColorEdit4()/ColorPicker4(). For ColorButton() this does the same as _NoAlpha.
            AlphaNoBg       = 1 << 13,  //              // ColorEdit, ColorPicker, ColorButton: disable rendering a checkerboard background behind transparent color.
            AlphaPreviewHalf= 1 << 14,  //              // ColorEdit, ColorPicker, ColorButton: display half opaque / half transparent preview.

            // User Options (right-click on widget to change some of them)
            // Current settings are stored in style.ColorEditFlags.
            AlphaBar        = 1 << 18,  //              // ColorEdit, ColorPicker: show vertical alpha bar/gradient in picker.
            HDR             = 1 << 19,  //              // (WIP) ColorEdit: Currently only disable 0.0f..1.0f limits in RGBA edition (note: you probably want to use ImGuiColorEditFlags_Float flag as well).
            DisplayRGB      = 1 << 20,  // [Display]    // ColorEdit: override _display_ type among RGB/HSV/Hex. ColorPicker: select any combination using one or more of RGB/HSV/Hex.
            DisplayHSV      = 1 << 21,  // [Display]    // "
            DisplayHex      = 1 << 22,  // [Display]    // "
            Uint8           = 1 << 23,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0..255.
            Float           = 1 << 24,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers. No round-trip of value via integers.
            PickerHueBar    = 1 << 25,  // [Picker]     // ColorPicker: bar for Hue, rectangle for Sat/Value.
            PickerHueWheel  = 1 << 26,  // [Picker]     // ColorPicker: wheel for Hue, triangle for Sat/Value.
            PickerNoRotate  = 1 << 27,  // [Picker]     // ColorPicker: disable rotating Sat/Value triangle. Best set in io.ConfigColorEditFlags once.
            InputRGB        = 1 << 28,  // [Input]      // ColorEdit, ColorPicker: input and output data in RGB format.
            InputHSV        = 1 << 29,  // [Input]      // ColorEdit, ColorPicker: input and output data in HSV format.

            // Defaults Options copied to io.ConfigColorEditFlags during initialization.
            // The intent is that you probably don't want to override them in most of your calls.
            // Let the user choose via the option menu and/or modify io.ConfigColorEditFlags directly during startup if you want.
            DefaultOptions = Uint8 | DisplayRGB | InputRGB | PickerHueBar,

            // [Internal] Masks
            AlphaMask      = NoAlpha | AlphaOpaque | AlphaNoBg | AlphaPreviewHalf,
            DisplayMask    = DisplayRGB | DisplayHSV | DisplayHex,
            DataTypeMask   = Uint8 | Float,
            PickerMask     = PickerHueWheel | PickerHueBar,
            InputMask      = InputRGB | InputHSV
        )

        SR_IMMEDIATE_GUI_DLL_API extern SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags GetNodeFlagsWithChild();
        SR_IMMEDIATE_GUI_DLL_API extern SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags GetNodeFlagsWithoutChild();

        SR_ENUM_NS_STRUCT_T(Condition, uint32_t,
            None          = 0,        // No condition (always set the variable), same as _Always
            Always        = 1 << 0,   // No condition (always set the variable)
            Once          = 1 << 1,   // Set the variable once per runtime session (only the first call will succeed)
            FirstUseEver  = 1 << 2,   // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
            Appearing     = 1 << 3    // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
        )

        SR_ENUM_NS_STRUCT_T(DrawFlags, int64_t,
            None                        = 0,

            // Rounding for AddRect(), AddRectFilled(), PathRect()
            // - When not specified, we defaults to ImDrawFlags_RoundCornersAll! So you only need to use those flags if you want another configuration.
            RoundCornersTopLeft         = 1 << 4, // Round top-left corner only (when rounding > 0.0f, we default to all corners).
            RoundCornersTopRight        = 1 << 5, // Round top-right corner only (when rounding > 0.0f, we default to all corners).
            RoundCornersBottomLeft      = 1 << 6, // Round bottom-left corner only (when rounding > 0.0f, we default to all corners).
            RoundCornersBottomRight     = 1 << 7, // Round bottom-right corner only (when rounding > 0.0f, we default to all corners).
            RoundCornersNone            = 1 << 8, // Disable rounding even if `float rounding > 0.0f`. This is NOT zero, NOT an implicit flag!
            RoundCornersAll             = RoundCornersTopLeft     | RoundCornersTopRight | RoundCornersBottomLeft | RoundCornersBottomRight, // (Default!!)
            RoundCornersDefault_        = RoundCornersAll, // Default to ALL corners if none of the _RoundCornersXX flags are specified!
            RoundCornersTop             = RoundCornersTopLeft     | RoundCornersTopRight,
            RoundCornersBottom          = RoundCornersBottomLeft  | RoundCornersBottomRight,
            RoundCornersLeft            = RoundCornersBottomLeft  | RoundCornersTopLeft,
            RoundCornersRight           = RoundCornersBottomRight | RoundCornersTopRight,
            RoundCornersMask_           = RoundCornersAll         | RoundCornersNone,

            // Stroke options
            Closed                      = 1 << 9, // PathStroke(), AddPolyline(): specify that shape should be closed.
            //ImDrawFlags_Closed        = 1 << 0, // Prior to 1.92.8 (May 2026), ImDrawFlags_Closed was guaranteed to be == 1<<0 == 1 for legacy compatibility reason. Hardcoded use of 1 or true should be replaced.

            InvalidMask_                = ~0x7FFFFFF0 // == 0x8000000F,
        )

        // Note: windows with the ImGuiWindowFlags_NoInputs flag are ignored by IsWindowHovered() calls.
        SR_ENUM_NS_STRUCT_T(HoveredFlags, uint32_t,
            None                          = 0,        // Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
            ChildWindows                  = 1 << 0,   // IsWindowHovered() only: Return true if any children of the window is hovered
            RootWindow                    = 1 << 1,   // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
            AnyWindow                     = 1 << 2,   // IsWindowHovered() only: Return true if any window is hovered
            NoPopupHierarchy              = 1 << 3,   // IsWindowHovered() only: Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
            DockHierarchy                 = 1 << 4,   // IsWindowHovered() only: Consider docking hierarchy (treat dockspace host as parent of docked window) (when used with _ChildWindows or _RootWindow)
            AllowWhenBlockedByPopup       = 1 << 5,   // Return true even if a popup window is normally blocking access to this item/window
            s_AllowWhenBlockedByModal     = 1 << 6,   // Return true even if a modal popup window is normally blocking access to this item/window. FIXME-TODO: Unavailable yet.
            AllowWhenBlockedByActiveItem  = 1 << 7,   // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
            AllowWhenOverlapped           = 1 << 8,   // IsItemHovered() only: Return true even if the position is obstructed or overlapped by another window
            AllowWhenDisabled             = 1 << 9,   // IsItemHovered() only: Return true even if the item is disabled
            NoNavOverride                 = 1 << 10,  // Disable using gamepad/keyboard navigation state when active, always query mouse.
            RectOnly                      = AllowWhenBlockedByPopup | AllowWhenBlockedByActiveItem | AllowWhenOverlapped,
            RootAndChildWindows           = RootWindow | ChildWindows
        )


        enum PlotFlags {
            None          = 0,       // default
            NoTitle       = 1 << 0,  // the plot title will not be displayed (titles are also hidden if preceded by double hashes, e.g. "##MyPlot")
            NoLegend      = 1 << 1,  // the legend will not be displayed
            NoMouseText   = 1 << 2,  // the mouse position, in plot coordinates, will not be displayed inside of the plot
            NoInputs      = 1 << 3,  // the user will not be able to interact with the plot
            NoMenus       = 1 << 4,  // the user will not be able to open context menus
            NoBoxSelect   = 1 << 5,  // the user will not be able to box-select
            NoFrame       = 1 << 6,  // the ImGui frame will not be rendered
            Equal         = 1 << 7,  // x and y axes pairs will be constrained to have the same units/pixel
            Crosshairs    = 1 << 8,  // the default mouse cursor will be replaced with a crosshair when hovered
            CanvasOnly    = NoTitle | NoLegend | NoMenus | NoBoxSelect | NoMouseText
        };

        enum class MouseButton
        {
            Left = 0,
            Right = 1,
            Middle = 2,
            COUNT = 5
        };

        union ImmediateDataTypeUnion {
            int8_t   s8;
            uint8_t  u8;
            int16_t  s16;
            uint16_t u16;
            int32_t  s32;
            uint32_t u32;
            int64_t  s64;
            uint64_t u64;
            float    f32;
            double   f64;
        };

        struct SR_IMMEDIATE_GUI_DLL_API ImmediateGUICreateContext {
            bool viewportsEnabled = false;
            SR_UTILS_NS::Path iniPath;
        };

        struct SR_IMMEDIATE_GUI_DLL_API ImmediateGUIFontConfig {
            int32_t oversampleH = 1; /// Or 2 is the same
            int32_t oversampleV = 1;
            bool pixelSnapH = true;
            bool mergeMode = false;
            bool fontDataOwnedByAtlas = false;
            float_t glyphMinAdvanceX = 0.0f;
        };

        SR_IMMEDIATE_GUI_DLL_API extern bool WindowsWndProcHandler(void* hWnd, uint32_t message, uint64_t wParam, uint64_t lParam);

        SR_IMMEDIATE_GUI_DLL_API extern void SetTheme(const SR_UTILS_NS::Path& path);
        SR_IMMEDIATE_GUI_DLL_API extern uint32_t GetViewportCount(void* pContext);
        SR_IMMEDIATE_GUI_DLL_API extern void GetViewports(SR_UTILS_NS::Vector<void*>& viewports);
        SR_IMMEDIATE_GUI_DLL_API extern void ClearFonts();
        SR_IMMEDIATE_GUI_DLL_API extern bool BuildFonts(void* pDefaultFont);
        SR_IMMEDIATE_GUI_DLL_API extern void* AddFontFromMemoryTTF(const void* fontData, int fontDataSize, float size, const ImmediateGUIFontConfig& config, const uint32_t* glyphRanges = nullptr);
        SR_IMMEDIATE_GUI_DLL_API extern void* CreateContext(const ImmediateGUICreateContext& context);
        SR_IMMEDIATE_GUI_DLL_API extern void DestroyContext(void* pContext);
        SR_IMMEDIATE_GUI_DLL_API extern void* GetViewportPlatformHandle(void* pViewport);
        SR_IMMEDIATE_GUI_DLL_API extern void SetWindowSize(const SR_MATH_NS::FVector2& size, Condition cond = Condition::None);
        SR_IMMEDIATE_GUI_DLL_API extern void SetNextWindowSize(const SR_MATH_NS::FVector2& size, Condition cond = Condition::None);
        SR_IMMEDIATE_GUI_DLL_API extern void SetNextWindowPos(const SR_MATH_NS::FVector2& pos, Condition cond = Condition::None, const SR_MATH_NS::FVector2& pivot = { 0.f, 0.f });
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetDisplaySize();
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector4 GetStyleColorVec4(StyleColor idx);
        SR_IMMEDIATE_GUI_DLL_API extern void* GetWindowViewport();
        SR_IMMEDIATE_GUI_DLL_API extern bool RadioButton(const char* label, bool active, float_t radius);
        SR_IMMEDIATE_GUI_DLL_API extern void SetDragDropPayload(const char* type, const void* data, size_t size, Condition cond = Condition::None);
        SR_IMMEDIATE_GUI_DLL_API extern void Separator();
        SR_IMMEDIATE_GUI_DLL_API extern void Text(const char* text, ...);
        SR_IMMEDIATE_GUI_DLL_API extern void TextWrapped(const char* text, ...);
        SR_IMMEDIATE_GUI_DLL_API extern void LabelText(const char* label, const char* text, ...);
        SR_IMMEDIATE_GUI_DLL_API extern void TextColored(const SR_MATH_NS::FColor& color, const char* text, ...);
        SR_IMMEDIATE_GUI_DLL_API extern void TextVertical(const char* text, SR_MATH_NS::FVector2 pos, SR_MATH_NS::FColor color = SR_MATH_NS::FColor::White());
        SR_IMMEDIATE_GUI_DLL_API extern void PushID(const char* strId);
        SR_IMMEDIATE_GUI_DLL_API extern void PushID(const void* ptrId);
        SR_IMMEDIATE_GUI_DLL_API extern void PushID(int intId);
        SR_IMMEDIATE_GUI_DLL_API extern void PopID();
        SR_IMMEDIATE_GUI_DLL_API extern bool IsAnyItemHovered();
        SR_IMMEDIATE_GUI_DLL_API extern bool IsWindowHovered(HoveredFlags flags = HoveredFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern void WindowTreeNodeSetOpen(bool open, uint64_t id);
        SR_IMMEDIATE_GUI_DLL_API extern void PushStyleVar(StyleVar idx, float val);
        SR_IMMEDIATE_GUI_DLL_API extern void PushStyleVar(StyleVar idx, const SR_MATH_NS::FVector2& val);
        SR_IMMEDIATE_GUI_DLL_API extern void PopStyleVar(uint32_t count = 1);
        SR_IMMEDIATE_GUI_DLL_API extern float GetStyleVarFloat(StyleVar idx);
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetStyleVarVec2(StyleVar idx);
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginPopup(const char* name);
        SR_IMMEDIATE_GUI_DLL_API extern void EndPopup();
        SR_IMMEDIATE_GUI_DLL_API extern void SameLine(float_t offsetFromStartX = 0.0f, float_t spacing = -1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern bool Button(const char* label, const SR_MATH_NS::FVector2& size = { 0.f, 0.f });
        SR_IMMEDIATE_GUI_DLL_API extern bool ButtonColored(const char* label, const SR_MATH_NS::FColor& color, const SR_MATH_NS::FVector2& size = { 0.f, 0.f });
        SR_IMMEDIATE_GUI_DLL_API extern bool ButtonColoredText(const char* label, const SR_MATH_NS::FColor& color, const SR_MATH_NS::FVector2& size = { 0.f, 0.f });
        SR_IMMEDIATE_GUI_DLL_API extern bool Checkbox(const char* label, bool* v);
        SR_IMMEDIATE_GUI_DLL_API extern bool IsCurrentlyDisabled();
        SR_IMMEDIATE_GUI_DLL_API extern bool IsItemHovered();
        SR_IMMEDIATE_GUI_DLL_API extern bool IsItemFocused();
        SR_IMMEDIATE_GUI_DLL_API extern bool DragScalar(const char* label, ImmediateDataType type, void* pData, float_t vSpeed, const void* pMin = nullptr, const void* pMax = nullptr, const char* format = nullptr);
        SR_IMMEDIATE_GUI_DLL_API extern void PushItemWidth(float_t itemWidth);
        SR_IMMEDIATE_GUI_DLL_API extern void PopItemWidth();
        SR_IMMEDIATE_GUI_DLL_API extern void PushStyleColor(StyleColor idx, const SR_MATH_NS::FColor& color);
        SR_IMMEDIATE_GUI_DLL_API extern void PopStyleColor(uint32_t count = 1);
        SR_IMMEDIATE_GUI_DLL_API extern void BeginGroup();
        SR_IMMEDIATE_GUI_DLL_API extern void EndGroup();
        SR_IMMEDIATE_GUI_DLL_API extern void EndGroupIfCan();
        SR_IMMEDIATE_GUI_DLL_API extern void TreePop();
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginDragDropSource(DragDropFlags flags = DragDropFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern float_t GetFrameHeight();
        SR_IMMEDIATE_GUI_DLL_API extern void Dummy(const SR_MATH_NS::FVector2& size);
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginCombo(const char* label, const char* previewValue, ComboFlags flags = ComboFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern void EndCombo();
        SR_IMMEDIATE_GUI_DLL_API extern bool Selectable(const char* label, bool selected = false);
        SR_IMMEDIATE_GUI_DLL_API extern void SetItemDefaultFocus();
        SR_IMMEDIATE_GUI_DLL_API extern uint32_t BeginForceEnabled();
        SR_IMMEDIATE_GUI_DLL_API extern void EndForceEnabled(uint32_t stackSize);
        SR_IMMEDIATE_GUI_DLL_API extern void BeginDisabled(bool disabled = true);
        SR_IMMEDIATE_GUI_DLL_API extern void EndDisabled();
        SR_IMMEDIATE_GUI_DLL_API extern void EndDragDropSource();
        SR_IMMEDIATE_GUI_DLL_API extern void* GetCurrentWindow();
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetWindowCursorPos(void* pWindow = nullptr);
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetCursorScreenPos();
        SR_IMMEDIATE_GUI_DLL_API extern void* GetWindowDrawList(void* pWindow = nullptr);
        SR_IMMEDIATE_GUI_DLL_API extern uint32_t GetColorU32(StyleColor idx, float alpha_mul = 1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern void RenderArrow(void* pDrawList, const SR_MATH_NS::FVector2& pos, uint32_t color, Direction dir, float_t scale = 1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern void DrawListAddRect(void* pDrawList, const SR_MATH_NS::FVector2& min, const SR_MATH_NS::FVector2& max, uint32_t color, float rounding = 0.0f, float thickness = 1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern void DrawListAddRectFilled(void* pDrawList, const SR_MATH_NS::FVector2& min, const SR_MATH_NS::FVector2& max, uint32_t color, float rounding = 0.0f, DrawFlags flags = DrawFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern void DrawListAddLine(void* pDrawList, const SR_MATH_NS::FVector2& p1, const SR_MATH_NS::FVector2& p2, uint32_t color, float thickness = 1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern bool InputFloat(const char* label, float_t* v, float_t step = 0.0f, float_t stepFast = 0.0f, const char* format = "%.3f", InputTextFlags flags = InputTextFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern bool InputInt(const char* label, int* v, int step = 1, int step_fast = 100, InputTextFlags flags = InputTextFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros);

        SR_IMMEDIATE_GUI_DLL_API extern bool Begin(const char* name, bool* p_open = nullptr, WindowFlags flags = WindowFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size = -1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding);
        SR_IMMEDIATE_GUI_DLL_API extern bool ImageButtonDouble(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding);
        SR_IMMEDIATE_GUI_DLL_API extern bool ImageButton(void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding);
        SR_IMMEDIATE_GUI_DLL_API extern bool ImageButton(void* pDescriptor, const SR_MATH_NS::FVector2& size);
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginDragDropTargetWindow(const char* payloadType);
        SR_IMMEDIATE_GUI_DLL_API extern bool ImageButtonInternal(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2 &size, float_t framePadding, ButtonFlags flags);
        SR_IMMEDIATE_GUI_DLL_API extern bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding, ButtonFlags flags);
        SR_IMMEDIATE_GUI_DLL_API extern bool CollapsingHeader(const std::string& label, TreeNodeFlags flags = TreeNodeFlags::CollapsingHeader);
        SR_IMMEDIATE_GUI_DLL_API extern void DrawMultiLineTextOnCenter(const std::string& text);
        SR_IMMEDIATE_GUI_DLL_API extern void DrawMultiLineTextOnCenter(const std::string& text, const SR_MATH_NS::FColor& color);
        SR_IMMEDIATE_GUI_DLL_API extern void DrawTextOnCenter(const std::string& text, const SR_MATH_NS::FColor& color = SR_MATH_NS::FColor(1.f, 1.f, 1.f, 1.f));
        SR_IMMEDIATE_GUI_DLL_API extern int ImTextCharToUtf8(char* buf, int32_t bufSize, uint32_t c);
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 DrawTexture(const void* pDescriptor, const SR_MATH_NS::FVector2& size, bool imposition);
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 DrawImage(void* user_texture_id, const SR_MATH_NS::FVector2& size, const SR_MATH_NS::FVector2& uv0, const SR_MATH_NS::FVector2& uv1, const SR_MATH_NS::FColor& tint_col, const SR_MATH_NS::FColor& border_col, bool imposition);
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginTabItem(const char* str_id);
        SR_IMMEDIATE_GUI_DLL_API extern void EndTabItem();
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginTabBar(const char* str_id);
        SR_IMMEDIATE_GUI_DLL_API extern void EndTabBar();
        SR_IMMEDIATE_GUI_DLL_API extern void PushFont(void* pFont);
        SR_IMMEDIATE_GUI_DLL_API extern void PopFont();
        SR_IMMEDIATE_GUI_DLL_API extern void SetWindowFocus(const char* str_id);
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginChild(const char* name, const SR_MATH_NS::FVector2& size = SR_MATH_NS::FVector2(), ChildWindowFlags childFlags = ChildWindowFlags::None, WindowFlags flags = WindowFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern void EndChild();
        SR_IMMEDIATE_GUI_DLL_API extern const void* GetDragDropPayload();
        SR_IMMEDIATE_GUI_DLL_API extern float_t GetScrollMaxY();
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginDragDropTarget();
        SR_IMMEDIATE_GUI_DLL_API extern const void* AcceptDragDropPayload(const char* type);
        SR_IMMEDIATE_GUI_DLL_API extern void EndDragDropTarget();
        SR_IMMEDIATE_GUI_DLL_API extern void* GetDataFromDragDropPayload(const void* pPayload);
        SR_IMMEDIATE_GUI_DLL_API extern const char* GetPayloadType(const void* pPayload);
        SR_IMMEDIATE_GUI_DLL_API extern float_t GetFontSize();
        SR_IMMEDIATE_GUI_DLL_API extern float_t GetScrollbarSize();
        SR_IMMEDIATE_GUI_DLL_API extern bool* GetMouseDown();
        SR_IMMEDIATE_GUI_DLL_API extern void SetMousePos(const SR_MATH_NS::FVector2& pos);
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetMousePos();
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetContentRegionAvail();
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetFramePadding();
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetItemRectSize();
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetItemRectMin();
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 CalcTextSize(const char* text);
        SR_IMMEDIATE_GUI_DLL_API extern void SetKeyboardFocusHere();
        SR_IMMEDIATE_GUI_DLL_API extern void OpenPopup(const char* str_id);
        SR_IMMEDIATE_GUI_DLL_API extern void AddText(void* pDrawList, const SR_MATH_NS::FVector2& pos, uint32_t color, const char* text);
        SR_IMMEDIATE_GUI_DLL_API extern void CloseCurrentPopup();
        SR_IMMEDIATE_GUI_DLL_API extern bool InputText(const char* label, std::string* str, InputTextFlags flags = InputTextFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern bool InputText(const char* label, char* str, size_t strSize, InputTextFlags flags = InputTextFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern bool InputTextMultiline(const char* label, std::string* str, const SR_MATH_NS::FVector2& size, InputTextFlags flags = InputTextFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginMenu(const char* label);
        SR_IMMEDIATE_GUI_DLL_API extern bool MenuItem(const char* label);
        SR_IMMEDIATE_GUI_DLL_API extern void EndMenu();
        SR_IMMEDIATE_GUI_DLL_API extern void BeginDocking();
        SR_IMMEDIATE_GUI_DLL_API extern void EndDocking();
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginMainMenuBar();
        SR_IMMEDIATE_GUI_DLL_API extern bool IsItemToggledOpen();
        SR_IMMEDIATE_GUI_DLL_API extern bool IsItemDeactivatedAfterEdit();
        SR_IMMEDIATE_GUI_DLL_API extern bool IsWindowFocused();
        SR_IMMEDIATE_GUI_DLL_API extern void* GetCurrentContext();
        SR_IMMEDIATE_GUI_DLL_API extern void TableNextRow();
        SR_IMMEDIATE_GUI_DLL_API extern void EndMenuBar();
        SR_IMMEDIATE_GUI_DLL_API extern void End();
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginListBox(const char* label, const SR_MATH_NS::FVector2& size = { 0.f, 0.f });
        SR_IMMEDIATE_GUI_DLL_API extern void EndListBox();
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginTable(const char* str_id, int columns);
        SR_IMMEDIATE_GUI_DLL_API extern void EndTable();
        SR_IMMEDIATE_GUI_DLL_API extern void TableSetColumnIndex(int column_n);
        SR_IMMEDIATE_GUI_DLL_API extern bool IsMouseDragging(MouseButton button);
        SR_IMMEDIATE_GUI_DLL_API extern bool IsMouseDown(MouseButton button);
        SR_IMMEDIATE_GUI_DLL_API extern bool IsMouseReleased(MouseButton button);
        SR_IMMEDIATE_GUI_DLL_API extern bool IsItemClicked(MouseButton button = MouseButton::Left);
        SR_IMMEDIATE_GUI_DLL_API extern bool IsMouseDoubleClicked(MouseButton button);
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginPopupContextWindow(const char* str_id = nullptr);
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginPopupContextItem(const char* str_id = nullptr);
        SR_IMMEDIATE_GUI_DLL_API extern bool TreeNodeEx(const void* ptr_id, TreeNodeFlags flags, const char* fmt, ...);
        SR_IMMEDIATE_GUI_DLL_API extern void* FindWindowByName(const char* name);
        SR_IMMEDIATE_GUI_DLL_API extern void SetCursorPosX(float_t x);
        SR_IMMEDIATE_GUI_DLL_API extern void SetCursorPosY(float_t y);
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetWindowSize();
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetCursorPos();
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FRect GetWindowRect(void* pWindow = nullptr);
        SR_IMMEDIATE_GUI_DLL_API extern bool SmallButton(const char* label);
        SR_IMMEDIATE_GUI_DLL_API extern void FocusTopMostWindowUnderOne();
        SR_IMMEDIATE_GUI_DLL_API extern void SetCursorPos(const SR_MATH_NS::FVector2& pos);
        SR_IMMEDIATE_GUI_DLL_API extern void LoadIniSettingsFromDisk();
        SR_IMMEDIATE_GUI_DLL_API extern bool DragFloat(const char* label, float_t* v, float_t vSpeed, float_t min = 0.f, float_t max = 0.f, const char* format = "%.3f");
        SR_IMMEDIATE_GUI_DLL_API extern bool DragFloat2(const char* label, float_t v[2], float_t vSpeed, float_t min = 0.f, float_t max = 0.f, const char* format = "%.3f");
        SR_IMMEDIATE_GUI_DLL_API extern bool DragFloat3(const char* label, float_t v[3], float_t vSpeed, float_t min = 0.f, float_t max = 0.f, const char* format = "%.3f");
        SR_IMMEDIATE_GUI_DLL_API extern bool SliderFloat(const char* label, float_t* v, float_t min, float_t max, const char* format = "%.3f");
        SR_IMMEDIATE_GUI_DLL_API extern bool SliderInt(const char* label, int* v, int min, int max, const char* format = "%d");
        SR_IMMEDIATE_GUI_DLL_API extern float_t GetFramerate();
        SR_IMMEDIATE_GUI_DLL_API extern float_t GetFrameHeightWithSpacing();

        SR_IMMEDIATE_GUI_DLL_API extern ImmediateDataType GetDataType(std::string_view type);
        SR_IMMEDIATE_GUI_DLL_API extern ImmediateDataType GetDataType(uint64_t size, bool isSigned, bool isIntegral);
        SR_IMMEDIATE_GUI_DLL_API extern ImmediateDataTypeUnion ReadDataType(void* pData, ImmediateDataType type);
        SR_IMMEDIATE_GUI_DLL_API extern ImmediateDataTypeUnion FloatToDataType(float_t value, ImmediateDataType type);
        SR_IMMEDIATE_GUI_DLL_API extern void WriteDataType(void* pData, ImmediateDataType type, ImmediateDataTypeUnion value);
        SR_IMMEDIATE_GUI_DLL_API extern SR_MATH_NS::FVector2 GetItemRectMax();
        SR_IMMEDIATE_GUI_DLL_API extern void DrawListAddTriangleFilled(void* pDrawList, const SR_MATH_NS::FVector2& a, const SR_MATH_NS::FVector2& b, const SR_MATH_NS::FVector2& c, uint32_t color);
        SR_IMMEDIATE_GUI_DLL_API extern bool IsItemVisible();

        // Layout functions
        SR_IMMEDIATE_GUI_DLL_API extern void BeginVertical(const char* str_id, const SR_MATH_NS::FVector2& size = SR_MATH_NS::FVector2(), float align = -1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern void BeginVertical(const void* ptr_id, const SR_MATH_NS::FVector2& size = SR_MATH_NS::FVector2(), float align = -1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern void EndVertical();
        SR_IMMEDIATE_GUI_DLL_API extern void BeginHorizontal(const char* str_id, const SR_MATH_NS::FVector2& size = SR_MATH_NS::FVector2(), float align = -1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern void BeginHorizontal(const void* ptr_id, const SR_MATH_NS::FVector2& size = SR_MATH_NS::FVector2(), float align = -1.0f);
        SR_IMMEDIATE_GUI_DLL_API extern void EndHorizontal();
        SR_IMMEDIATE_GUI_DLL_API extern void Spring(float weight = 1.0f, float spacing = -1.0f);

        // Color Editor / Picker
        SR_IMMEDIATE_GUI_DLL_API extern bool ColorEdit(const char* label, SR_MATH_NS::FColor& color, ColorEditFlags flags = ColorEditFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern bool ColorEditAlpha(const char* label, SR_MATH_NS::FColor& color, ColorEditFlags flags = ColorEditFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern bool ColorPicker(const char* label, SR_MATH_NS::FColor& color, ColorEditFlags flags = ColorEditFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern bool ColorPickerAlpha(const char* label, SR_MATH_NS::FColor& color, ColorEditFlags flags = ColorEditFlags::None, const float* ref_col = NULL);
        SR_IMMEDIATE_GUI_DLL_API extern bool ColorButton(const char* desc_id, SR_MATH_NS::FColor& color, ColorEditFlags flags = ColorEditFlags::None, const SR_MATH_NS::FVector2& size = SR_MATH_NS::FVector2(0, 0)); // display a color square/button, hover for details, return true when pressed.

        // Debug
        SR_IMMEDIATE_GUI_DLL_API extern void ShowMetricsWindow(bool* pOpen = nullptr);

        // Icon drawing
        SR_IMMEDIATE_GUI_DLL_API extern void DrawPinIcon(const SR_MATH_NS::FVector2& size, SR_GRAPH_NS::GUI::IconType iconType, bool filled, const SR_MATH_NS::FColor& color, const SR_MATH_NS::FColor& innerColor = SR_MATH_NS::FColor(0, 0, 0, 0));


        // Plots
        SR_IMMEDIATE_GUI_DLL_API extern bool BeginPlot(const char* title_id, const SR_MATH_NS::FVector2& size = SR_MATH_NS::FVector2(-1,0), PlotFlags flags = PlotFlags::None);
        SR_IMMEDIATE_GUI_DLL_API extern void EndPlot();

        // ----- Line Plot
        SR_IMMEDIATE_GUI_DLL_API extern void PlotLine(const char* label_id, const void* values, int count, ImmediateDataType type, double xscale = 1, double xstart = 0);
        SR_IMMEDIATE_GUI_DLL_API extern void PlotLine(const char* label_id, const void* xs, const void* ys, int count, ImmediateDataType type);
    }
}

#endif //SRENGINE_IMMEDIATEGUI_H
