

# File ImmediateGUI.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**ImmediateGUI.h**](ImmediateGUI_8h.md)

[Go to the documentation of this file](ImmediateGUI_8h.md)


```C++
//
// Created by Monika on 10.05.2025.
//

#ifndef SR_ENGINE_RENDERER_IMMEDIATE_GUI_H
#define SR_ENGINE_RENDERER_IMMEDIATE_GUI_H

#include <Graphics/Pipeline/PipelineType.h>
#include <Utils/Math/Rect.h>

#include <Enum/TreeNodeFlags.hpp>

namespace SR_GRAPH_NS {
    class Pipeline;
}

namespace SR_GRAPH_GUI_NS {
    SR_ENUM_NS_STRUCT_T(WindowFlags, uint32_t,
        None                      = 0,
        NoTitleBar                = 1 << 0,
        NoResize                  = 1 << 1,
        NoMove                    = 1 << 2,
        NoScrollbar               = 1 << 3,
        NoScrollWithMouse         = 1 << 4,
        NoCollapse                = 1 << 5,
        AlwaysAutoResize          = 1 << 6,
        NoBackground              = 1 << 7,
        NoSavedSettings           = 1 << 8,
        NoMouseInputs             = 1 << 9,
        MenuBar                   = 1 << 10,
        HorizontalScrollbar       = 1 << 11,
        NoFocusOnAppearing        = 1 << 12,
        NoBringToFrontOnFocus     = 1 << 13,
        AlwaysVerticalScrollbar   = 1 << 14,
        AlwaysHorizontalScrollbar = 1 << 15,
        AlwaysUseWindowPadding    = 1 << 16,
        NoNavInputs               = 1 << 18,
        NoNavFocus                = 1 << 19,
        UnsavedDocument           = 1 << 20,
        NoDocking                 = 1 << 21,

        NoNav                     = NoNavInputs | NoNavFocus,
        NoDecoration              = NoTitleBar | NoResize | NoScrollbar | NoCollapse,
        NoInputs                  = NoMouseInputs | NoNavInputs | NoNavFocus,

        NavFlattened              = 1 << 23,
        ChildWindow               = 1 << 24,
        Tooltip                   = 1 << 25,
        Popup                     = 1 << 26,
        Modal                     = 1 << 27,
        ChildMenu                 = 1 << 28,
        DockNodeHost              = 1 << 29
    )

    namespace Immediate {
        enum class SR_RENDERER_DLL_API ImmediateDataType : uint8_t {
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

        enum class SR_RENDERER_DLL_API StyleColor {
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
            TitleBg,
            TitleBgActive,
            TitleBgCollapsed,
            MenuBarBg,
            ScrollbarBg,
            ScrollbarGrab,
            ScrollbarGrabHovered,
            ScrollbarGrabActive,
            CheckMark,
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
            Tab,                   // TabItem in a TabBar
            TabHovered,
            TabActive,
            TabUnfocused,
            TabUnfocusedActive,
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
            TextSelectedBg,
            DragDropTarget,        // Rectangle highlighting a drop target
            NavHighlight,          // Gamepad/keyboard: current highlighted item
            NavWindowingHighlight, // Highlight window when using CTRL+TAB
            NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
            ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
            COUNT
        };

        enum class SR_RENDERER_DLL_API Direction {
            None    = -1,
            Left    = 0,
            Right   = 1,
            Up      = 2,
            Down    = 3,
            COUNT
        };

        enum class StyleVar {
            Alpha,               // float     Alpha
            DisabledAlpha,       // float     DisabledAlpha
            WindowPadding,       // FVector2  WindowPadding
            WindowRounding,      // float     WindowRounding
            WindowBorderSize,    // float     WindowBorderSize
            WindowMinSize,       // FVector2  WindowMinSize
            WindowTitleAlign,    // FVector2  WindowTitleAlign
            ChildRounding,       // float     ChildRounding
            ChildBorderSize,     // float     ChildBorderSize
            PopupRounding,       // float     PopupRounding
            PopupBorderSize,     // float     PopupBorderSize
            FramePadding,        // FVector2  FramePadding
            FrameRounding,       // float     FrameRounding
            FrameBorderSize,     // float     FrameBorderSize
            ItemSpacing,         // FVector2  ItemSpacing
            ItemInnerSpacing,    // FVector2  ItemInnerSpacing
            IndentSpacing,       // float     IndentSpacing
            CellPadding,         // FVector2  CellPadding
            ScrollbarSize,       // float     ScrollbarSize
            ScrollbarRounding,   // float     ScrollbarRounding
            GrabMinSize,         // float     GrabMinSize
            GrabRounding,        // float     GrabRounding
            TabRounding,         // float     TabRounding
            ButtonTextAlign,     // FVector2  ButtonTextAlign
            SelectableTextAlign, // FVector2  SelectableTextAlign
            LayoutAlign,         // float     LayoutAlign
            COUNT
        };

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
            SourceNoPreviewTooltip       = 1 << 0,   // By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disable this behavior.
            SourceNoDisableHover         = 1 << 1,   // By default, when dragging we clear data so that IsItemHovered() will return false, to avoid subsequent user code submitting tooltips. This flag disable this behavior so you can still call IsItemHovered() on the source item.
            SourceNoHoldToOpenOthers     = 1 << 2,   // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
            SourceAllowNullID            = 1 << 3,   // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is extremely unusual within the dear imgui ecosystem and so we made it explicit.
            SourceExtern                 = 1 << 4,   // External source (from outside of dear imgui), won't attempt to read current item/window info. Will always return true. Only one Extern source can be active simultaneously.
            SourceAutoExpirePayload      = 1 << 5,   // Automatically expire the payload if the source cease to be submitted (otherwise payloads are persisting while being dragged)
            // AcceptDragDropPayload() flags
            AcceptBeforeDelivery         = 1 << 10,  // AcceptDragDropPayload() will returns true even before the mouse button is released. You can then call IsDelivery() to test if the payload needs to be delivered.
            AcceptNoDrawDefaultRect      = 1 << 11,  // Do not draw the default highlight rectangle when hovering over target.
            AcceptNoPreviewTooltip       = 1 << 12,  // Request hiding the BeginDragDropSource tooltip from the BeginDragDropTarget site.
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

        const auto SR_NODE_FLAGS_WITH_CHILD = SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnArrow | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnDoubleClick;
        const auto SR_NODE_FLAGS_WITHOUT_CHILD = SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::NoTreePushOnOpen | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::Leaf;

        SR_ENUM_NS_STRUCT_T(Condition, uint32_t,
            None          = 0,        // No condition (always set the variable), same as _Always
            Always        = 1 << 0,   // No condition (always set the variable)
            Once          = 1 << 1,   // Set the variable once per runtime session (only the first call will succeed)
            FirstUseEver  = 1 << 2,   // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
            Appearing     = 1 << 3    // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
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

        enum class SR_RENDERER_DLL_API MouseButton
        {
            Left = 0,
            Right = 1,
            Middle = 2,
            COUNT = 5
        };

        union SR_RENDERER_DLL_API ImmediateDataTypeUnion {
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

        SR_RENDERER_DLL_API extern void SetDragDropPayload(const char* type, const void* data, size_t size, Condition cond = Condition::None);
        SR_RENDERER_DLL_API extern void Separator();
        SR_RENDERER_DLL_API extern void Text(const char* text, ...);
        SR_RENDERER_DLL_API extern void TextWrapped(const char* text, ...);
        SR_RENDERER_DLL_API extern void LabelText(const char* label, const char* text, ...);
        SR_RENDERER_DLL_API extern void TextColored(const SR_MATH_NS::FColor& color, const char* text, ...);
        SR_RENDERER_DLL_API extern void PushID(const char* strId);
        SR_RENDERER_DLL_API extern void PushID(const void* ptrId);
        SR_RENDERER_DLL_API extern void PushID(int intId);
        SR_RENDERER_DLL_API extern void PopID();
        SR_RENDERER_DLL_API extern bool IsAnyItemHovered();
        SR_RENDERER_DLL_API extern bool IsWindowHovered(HoveredFlags flags = HoveredFlags::None);
        SR_RENDERER_DLL_API extern void WindowTreeNodeSetOpen(bool open, uint64_t id);
        SR_RENDERER_DLL_API extern void PushStyleVar(StyleVar idx, float val);
        SR_RENDERER_DLL_API extern void PushStyleVar(StyleVar idx, const SR_MATH_NS::FVector2& val);
        SR_RENDERER_DLL_API extern void PopStyleVar(uint32_t count = 1);
        SR_RENDERER_DLL_API extern bool BeginPopup(const char* name);
        SR_RENDERER_DLL_API extern void EndPopup();
        SR_RENDERER_DLL_API extern void SameLine();
        SR_RENDERER_DLL_API extern bool Button(const char* label, const SR_MATH_NS::FVector2& size = { 0.f, 0.f });
        SR_RENDERER_DLL_API extern bool Checkbox(const char* label, bool* v);
        SR_RENDERER_DLL_API extern bool IsCurrentlyDisabled();
        SR_RENDERER_DLL_API extern bool IsItemHovered();
        SR_RENDERER_DLL_API extern bool IsItemFocused();
        SR_RENDERER_DLL_API extern bool DragScalar(const char* label, ImmediateDataType type, void* pData, float_t vSpeed, const void* pMin = nullptr, const void* pMax = nullptr, const char* format = nullptr);
        SR_RENDERER_DLL_API extern void PushItemWidth(float_t itemWidth);
        SR_RENDERER_DLL_API extern void PopItemWidth();
        SR_RENDERER_DLL_API extern void PushStyleColor(StyleColor idx, const SR_MATH_NS::FColor& color);
        SR_RENDERER_DLL_API extern void PopStyleColor(uint32_t count = 1);
        SR_RENDERER_DLL_API extern void BeginGroup();
        SR_RENDERER_DLL_API extern void EndGroup();
        SR_RENDERER_DLL_API extern void TreePop();
        SR_RENDERER_DLL_API extern bool BeginDragDropSource(DragDropFlags flags = DragDropFlags::None);
        SR_RENDERER_DLL_API extern float_t GetFrameHeight();
        SR_RENDERER_DLL_API extern void Dummy(const SR_MATH_NS::FVector2& size);
        SR_RENDERER_DLL_API extern bool BeginCombo(const char* label, const char* previewValue, ComboFlags flags = ComboFlags::None);
        SR_RENDERER_DLL_API extern void EndCombo();
        SR_RENDERER_DLL_API extern bool Selectable(const char* label, bool selected = false);
        SR_RENDERER_DLL_API extern void SetItemDefaultFocus();
        SR_RENDERER_DLL_API extern uint32_t BeginForceEnabled();
        SR_RENDERER_DLL_API extern void EndForceEnabled(uint32_t stackSize);
        SR_RENDERER_DLL_API extern void BeginDisabled();
        SR_RENDERER_DLL_API extern void EndDisabled();
        SR_RENDERER_DLL_API extern void EndDragDropSource();
        SR_RENDERER_DLL_API extern void* GetCurrentWindow();
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 GetWindowCursorPos(void* pWindow = nullptr);
        SR_RENDERER_DLL_API extern void* GetWindowDrawList(void* pWindow = nullptr);
        SR_RENDERER_DLL_API extern uint32_t GetColorU32(StyleColor idx, float alpha_mul = 1.0f);
        SR_RENDERER_DLL_API extern void RenderArrow(void* pDrawList, const SR_MATH_NS::FVector2& pos, uint32_t color, Direction dir, float_t scale = 1.0f);
        SR_RENDERER_DLL_API extern bool InputFloat(const char* label, float_t* v, float_t step = 0.0f, float_t stepFast = 0.0f, const char* format = "%.3f", InputTextFlags flags = InputTextFlags::None);
        SR_RENDERER_DLL_API extern bool InputInt(const char* label, int* v, int step = 1, int step_fast = 100, InputTextFlags flags = InputTextFlags::None);
        SR_RENDERER_DLL_API extern bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros);
        SR_RENDERER_DLL_API extern bool Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

        SR_RENDERER_DLL_API extern bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size = -1.0f);
        SR_RENDERER_DLL_API extern bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding);
        SR_RENDERER_DLL_API extern bool ImageButtonDouble(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding);
        SR_RENDERER_DLL_API extern bool ImageButton(void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding);
        SR_RENDERER_DLL_API extern bool ImageButton(void* pDescriptor, const SR_MATH_NS::FVector2& size);
        SR_RENDERER_DLL_API extern bool BeginDragDropTargetWindow(const std::string& payloadType);
        SR_RENDERER_DLL_API extern bool ImageButtonInternal(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2 &size, float_t framePadding, ButtonFlags flags);
        SR_RENDERER_DLL_API extern bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding, ButtonFlags flags);
        SR_RENDERER_DLL_API extern bool CollapsingHeader(const std::string& label, TreeNodeFlags flags = TreeNodeFlags::CollapsingHeader);
        SR_RENDERER_DLL_API extern void DrawMultiLineTextOnCenter(const std::string& text);
        SR_RENDERER_DLL_API extern void DrawMultiLineTextOnCenter(const std::string& text, const SR_MATH_NS::FColor& color);
        SR_RENDERER_DLL_API extern void DrawTextOnCenter(const std::string& text, const SR_MATH_NS::FColor& color = SR_MATH_NS::FColor(1.f, 1.f, 1.f, 1.f));
        SR_RENDERER_DLL_API extern int ImTextCharToUtf8(char* buf, int32_t bufSize, uint32_t c);
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 DrawTexture(const void* pDescriptor, const SR_MATH_NS::FVector2& size, SR_GRAPH_NS::PipelineType pipelineType, bool imposition);
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 DrawTexture(const SR_GRAPH_NS::Pipeline* pPipeline, uint32_t textureId, const SR_MATH_NS::FVector2& size, bool imposition);
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 DrawImage(void* user_texture_id, const SR_MATH_NS::FVector2& size, const SR_MATH_NS::FVector2& uv0, const SR_MATH_NS::FVector2& uv1, const SR_MATH_NS::FColor& tint_col, const SR_MATH_NS::FColor& border_col, bool imposition);
        SR_RENDERER_DLL_API extern bool BeginTabItem(const char* str_id);
        SR_RENDERER_DLL_API extern void EndTabItem();
        SR_RENDERER_DLL_API extern bool BeginTabBar(const char* str_id);
        SR_RENDERER_DLL_API extern void EndTabBar();
        SR_RENDERER_DLL_API extern void PushFont(void* pFont);
        SR_RENDERER_DLL_API extern void PopFont();
        SR_RENDERER_DLL_API extern bool BeginChild(const char* str_id, const SR_MATH_NS::FVector2& size = SR_MATH_NS::FVector2(), bool border = false);
        SR_RENDERER_DLL_API extern void EndChild();
        SR_RENDERER_DLL_API extern const void* GetDragDropPayload();
        SR_RENDERER_DLL_API extern float_t GetScrollMaxY();
        SR_RENDERER_DLL_API extern bool BeginDragDropTarget();
        SR_RENDERER_DLL_API extern const void* AcceptDragDropPayload(const char* type);
        SR_RENDERER_DLL_API extern void EndDragDropTarget();
        SR_RENDERER_DLL_API extern void* GetDataFromDragDropPayload(const void* pPayload);
        SR_RENDERER_DLL_API extern const char* GetPayloadType(const void* pPayload);
        SR_RENDERER_DLL_API extern float_t GetFontSize();
        SR_RENDERER_DLL_API extern float_t GetScrollbarSize();
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 GetMousePos();
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 GetContentRegionAvail();
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 GetFramePadding();
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 GetItemRectSize();
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 GetItemRectMin();
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 CalcTextSize(const char* text);
        SR_RENDERER_DLL_API extern void SetKeyboardFocusHere();
        SR_RENDERER_DLL_API extern void OpenPopup(const char* str_id);
        SR_RENDERER_DLL_API extern void AddText(void* pDrawList, const SR_MATH_NS::FVector2& pos, uint32_t color, const char* text);
        SR_RENDERER_DLL_API extern void CloseCurrentPopup();
        SR_RENDERER_DLL_API extern bool InputText(const char* label, std::string* str, InputTextFlags flags = InputTextFlags::None);
        SR_RENDERER_DLL_API extern bool InputText(const char* label, char* str, size_t strSize, InputTextFlags flags = InputTextFlags::None);
        SR_RENDERER_DLL_API extern bool InputTextMultiline(const char* label, std::string* str, const SR_MATH_NS::FVector2& size, InputTextFlags flags = InputTextFlags::None);
        SR_RENDERER_DLL_API extern bool BeginMenu(const char* label);
        SR_RENDERER_DLL_API extern bool MenuItem(const char* label);
        SR_RENDERER_DLL_API extern void EndMenu();
        SR_RENDERER_DLL_API extern void BeginDocking();
        SR_RENDERER_DLL_API extern void EndDocking();
        SR_RENDERER_DLL_API extern bool BeginMainMenuBar();
        SR_RENDERER_DLL_API extern bool IsItemToggledOpen();
        SR_RENDERER_DLL_API extern bool IsItemDeactivatedAfterEdit();
        SR_RENDERER_DLL_API extern void TableNextRow();
        SR_RENDERER_DLL_API extern void EndMenuBar();
        SR_RENDERER_DLL_API extern void End();
        SR_RENDERER_DLL_API extern bool BeginListBox(const char* label, const SR_MATH_NS::FVector2& size = { 0.f, 0.f });
        SR_RENDERER_DLL_API extern void EndListBox();
        SR_RENDERER_DLL_API extern bool BeginTable(const char* str_id, int columns);
        SR_RENDERER_DLL_API extern void EndTable();
        SR_RENDERER_DLL_API extern void TableSetColumnIndex(int column_n);
        SR_RENDERER_DLL_API extern bool IsMouseDragging(MouseButton button);
        SR_RENDERER_DLL_API extern bool IsMouseDown(MouseButton button);
        SR_RENDERER_DLL_API extern bool IsMouseReleased(MouseButton button);
        SR_RENDERER_DLL_API extern bool IsItemClicked(MouseButton button = MouseButton::Left);
        SR_RENDERER_DLL_API extern bool IsMouseDoubleClicked(MouseButton button);
        SR_RENDERER_DLL_API extern bool BeginPopupContextWindow(const char* str_id = nullptr);
        SR_RENDERER_DLL_API extern bool BeginPopupContextItem(const char* str_id = nullptr);
        SR_RENDERER_DLL_API extern bool TreeNodeEx(const void* ptr_id, TreeNodeFlags flags, const char* fmt, ...);
        SR_RENDERER_DLL_API extern void* FindWindowByName(const char* name);
        SR_RENDERER_DLL_API extern void SetCursorPosX(float_t x);
        SR_RENDERER_DLL_API extern void SetCursorPosY(float_t y);
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 GetWindowSize();
        SR_RENDERER_DLL_API extern SR_MATH_NS::FVector2 GetCursorPos();
        SR_RENDERER_DLL_API extern SR_MATH_NS::FRect GetWindowRect(void* pWindow = nullptr);
        SR_RENDERER_DLL_API extern bool SmallButton(const char* label);
        SR_RENDERER_DLL_API extern void FocusTopMostWindowUnderOne();
        SR_RENDERER_DLL_API extern void SetCursorPos(const SR_MATH_NS::FVector2& pos);
        SR_RENDERER_DLL_API extern void LoadIniSettingsFromDisk();
        SR_RENDERER_DLL_API extern bool DragFloat(const char* label, float_t* v, float_t vSpeed, float_t min = 0.f, float_t max = 0.f, const char* format = "%.3f");
        SR_RENDERER_DLL_API extern bool SliderFloat(const char* label, float_t* v, float_t min, float_t max, const char* format = "%.3f");
        SR_RENDERER_DLL_API extern float_t GetFramerate();
        SR_RENDERER_DLL_API extern float_t GetFrameHeightWithSpacing();

        SR_RENDERER_DLL_API extern ImmediateDataType GetDataType(std::string_view type);
        SR_RENDERER_DLL_API extern ImmediateDataType GetDataType(uint64_t size, bool isSigned, bool isIntegral);
        SR_RENDERER_DLL_API extern ImmediateDataTypeUnion ReadDataType(void* pData, ImmediateDataType type);
        SR_RENDERER_DLL_API extern void WriteDataType(void* pData, ImmediateDataType type, ImmediateDataTypeUnion value);
    }
}

#endif //SRENGINE_IMMEDIATEGUI_H
```


