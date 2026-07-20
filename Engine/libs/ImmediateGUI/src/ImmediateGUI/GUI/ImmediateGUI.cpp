//
// Created by Monika on 10.05.2025.
//

#include <ImmediateGUI/GUI/ImmediateGUI.h>
#include <ImmediateGUI/GUI/ImGUITheme.h>
#include <ImmediateGUI/Impl/ImGUI.h>
#include <ImmediateGUI/Impl/ImGUIExperimental.h>
#include <ImmediateGUI/Impl/Theme.h>
#include <ImmediateGUI/Impl/WindowsImpl.h>

#include <Utils/Resources/ResourceRef.h>
#include <Utils/Common/StoreUtils.h>

#include <Enum/TreeNodeFlags.hpp>

namespace SR_GRAPH_GUI_NS::Immediate {
#ifdef SR_USE_IMGUI
    namespace {
        bool g_fontsRebuildPending = false;
        SR_UTILS_NS::Path g_themePath;
    }

    void NewFrame() {
        if (g_fontsRebuildPending) {
            ImGuiIO& io = ImGui::GetIO();

            // With new backends (1.92+) supporting RendererHasTextures: do NOT call Fonts->Build() manually.
            // Just request (re)upload of the atlas texture.
            if (io.Fonts && (io.BackendFlags & ImGuiBackendFlags_RendererHasTextures) != 0) {
                if (io.Fonts->TexData) {
                    io.Fonts->TexData->SetStatus(ImTextureStatus_WantCreate);
                }
            }
            // Fallback for older backends: build atlas on CPU here.
            else if (io.Fonts) {
                io.Fonts->Build();
            }

            g_fontsRebuildPending = false;
        }

        ImGui::NewFrame();
    }

    void Render() {
        SR_TRACY_ZONE;
        const float_t fontScale = SR_UTILS_NS::StoreUtils::User::GetFloat("EditorFontSize", SR_IMMEDIATE_GUI_NS::DEFAULT_FONT_SIZE);
        ImGui::GetStyle().FontScaleMain = (fontScale / SR_IMMEDIATE_GUI_NS::DEFAULT_FONT_SIZE) * 1.1f;
        ImGui::Render();
    }

    void UpdatePlatformWindows() {
        SR_TRACY_ZONE;
        ImGui::UpdatePlatformWindows();
    }

    void RenderPlatformWindowsDefault() {
        SR_TRACY_ZONE;
        ImGui::RenderPlatformWindowsDefault();
    }

    void Separator() {
        SR_TRACY_ZONE;
        ImGui::Separator();
    }

    void Text(const char* text, ...) {
        SR_TRACY_ZONE;
        va_list args;
        va_start(args, text);
        ImGui::TextV(text, args);
        va_end(args);
    }

    SR_MATH_NS::FVector4 GetStyleColorVec4(StyleColor idx) {
        return ImV4ToF4(ImGui::GetStyleColorVec4(static_cast<ImGuiCol>(idx)));
    }

    void TextColored(const SR_MATH_NS::FColor& color, const char* text, ...) {
        SR_TRACY_ZONE;
        va_list args;
        va_start(args, text);
        ImGui::TextColoredV(FCToImC(color), text, args);
        va_end(args);
    }

    void PushID(const char* strId) {
        ImGui::PushID(strId);
    }

    void PushID(const void* ptrId) {
        ImGui::PushID(ptrId);
    }

    void PushID(int intId) {
        ImGui::PushID(intId);
    }

    void PopID() {
        ImGui::PopID();
    }

    void PushStyleVar(StyleVar idx, float val) {
        ImGui::PushStyleVar(static_cast<ImGuiStyleVar>(idx), val);
    }

    void PushStyleVar(StyleVar idx, const SR_MATH_NS::FVector2& val) {
        ImGui::PushStyleVar(static_cast<ImGuiStyleVar>(idx), F2ToImV2(val));
    }

    SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags GetNodeFlagsWithChild() {
        return SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnArrow | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnDoubleClick;
    }

    SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags GetNodeFlagsWithoutChild() {
        return SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::NoTreePushOnOpen | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::Leaf;
    }

    void PopStyleVar(uint32_t count) {
        ImGui::PopStyleVar(static_cast<int>(count));
    }

    ImmediateDataType GetDataType(std::string_view type) {
        static const std::map<std::string_view, ImmediateDataType> table = {
                { "int", ImmediateDataType::Int32 },
                { "unsigned int", ImmediateDataType::UInt32 },
                { "float", ImmediateDataType::Float },
                { "double", ImmediateDataType::Double }
        };
        if (auto it = table.find(type); it != table.end()) {
            return it->second;
        }
        return ImmediateDataType::COUNT;
    }

    ImmediateDataType GetDataType(uint64_t size, bool isSigned, bool isIntegral) {
        static const std::map<uint64_t, ImmediateDataType> signedTable = {
                { 1, ImmediateDataType::Int8  },
                { 2, ImmediateDataType::Int16 },
                { 4, ImmediateDataType::Int32 },
                { 8, ImmediateDataType::Int64 }
        };

        static const std::map<uint64_t, ImmediateDataType> unsignedTable = {
                { 1, ImmediateDataType::UInt8  },
                { 2, ImmediateDataType::UInt16 },
                { 4, ImmediateDataType::UInt32 },
                { 8, ImmediateDataType::UInt64 }
        };

        if (!isIntegral) {
            if (size == 4) {
                return ImmediateDataType::Float;
            } else if (size == 8) {
                return ImmediateDataType::Double;
            }
            return ImmediateDataType::COUNT;
        }

        if (isSigned) {
            if (auto it = signedTable.find(size); it != signedTable.end()) {
                return it->second;
            }
        }
        else {
            if (auto it = unsignedTable.find(size); it != unsignedTable.end()) {
                return it->second;
            }
        }

        return ImmediateDataType::COUNT;
    }

    ImmediateDataTypeUnion ReadDataType(void* pData, ImmediateDataType type) {
        ImmediateDataTypeUnion result = {};
        switch (type) {
            case ImmediateDataType::Int8:  result.s8   = *(int8_t*)pData; break;
            case ImmediateDataType::UInt8:  result.u8   = *(uint8_t*)pData; break;
            case ImmediateDataType::Int16: result.s16  = *(int16_t*)pData; break;
            case ImmediateDataType::UInt16: result.u16  = *(uint16_t*)pData; break;
            case ImmediateDataType::Int32: result.s32  = *(int32_t*)pData; break;
            case ImmediateDataType::UInt32: result.u32  = *(uint32_t*)pData; break;
            case ImmediateDataType::Int64: result.s64  = *(int64_t*)pData; break;
            case ImmediateDataType::UInt64: result.u64  = *(uint64_t*)pData; break;
            case ImmediateDataType::Float: result.f32 = *(float*)pData; break;
            case ImmediateDataType::Double: result.f64 = *(double*)pData; break;
            default: SRHalt("Unknown ImGuiDataType!"); break;
        }
        return result;
    }

    ImmediateDataTypeUnion FloatToDataType(float_t value, ImmediateDataType type) {
        ImmediateDataTypeUnion result = {};
        switch (type) {
            case ImmediateDataType::Int8:  result.s8   = static_cast<int8_t>(value); break;
            case ImmediateDataType::UInt8:  result.u8   = static_cast<uint8_t>(value); break;
            case ImmediateDataType::Int16: result.s16  = static_cast<int16_t>(value); break;
            case ImmediateDataType::UInt16: result.u16  = static_cast<uint16_t>(value); break;
            case ImmediateDataType::Int32: result.s32  = static_cast<int32_t>(value); break;
            case ImmediateDataType::UInt32: result.u32  = static_cast<uint32_t>(value); break;
            case ImmediateDataType::Int64: result.s64  = static_cast<int64_t>(value); break;
            case ImmediateDataType::UInt64: result.u64  = static_cast<uint64_t>(value); break;
            case ImmediateDataType::Float: result.f32 = value; break;
            case ImmediateDataType::Double: result.f64 = value; break;
            default: SRHalt("Unknown ImGuiDataType!"); break;
        }
        return result;
    }

    void WriteDataType(void* pData, ImmediateDataType type, ImmediateDataTypeUnion value) {
        switch (type) {
            case ImmediateDataType::Int8:   *(int8_t*)pData   = value.s8; break;
            case ImmediateDataType::UInt8:  *(uint8_t*)pData  = value.u8; break;
            case ImmediateDataType::Int16:  *(int16_t*)pData  = value.s16; break;
            case ImmediateDataType::UInt16: *(uint16_t*)pData = value.u16; break;
            case ImmediateDataType::Int32:  *(int32_t*)pData  = value.s32; break;
            case ImmediateDataType::UInt32: *(uint32_t*)pData = value.u32; break;
            case ImmediateDataType::Int64:  *(int64_t*)pData  = value.s64; break;
            case ImmediateDataType::UInt64: *(uint64_t*)pData = value.u64; break;
            case ImmediateDataType::Float:  *(float*)pData    = value.f32; break;
            case ImmediateDataType::Double: *(double*)pData   = value.f64; break;
            default: SRHalt("Unknown ImmediateDataType!"); break;
        }
    }

    void SameLine(float_t offsetFromStartX, float_t spacing) {
        SR_TRACY_ZONE;
        ImGui::SameLine(offsetFromStartX, spacing);
    }

    bool IsCurrentlyDisabled() {
        ImGuiContext* ctx = ImGui::GetCurrentContext();
        return (ctx->CurrentItemFlags & ImGuiItemFlags_Disabled) != 0;
    }

    bool Button(const char* label, const SR_MATH_NS::FVector2& size) {
        SR_TRACY_ZONE;
        return ImGui::Button(label, F2ToImV2(size));
    }

    bool ButtonColored(const char* label, const SR_MATH_NS::FColor& color, const SR_MATH_NS::FVector2& size) {
        SR_TRACY_ZONE;
        PushStyleColor(StyleColor::Button, color);
        PushStyleColor(StyleColor::ButtonHovered, color + SR_MATH_NS::FColor(0.1f, 0.1f, 0.1f, 0.0f));
        PushStyleColor(StyleColor::ButtonActive, color + SR_MATH_NS::FColor(0.2f, 0.2f, 0.2f, 0.0f));

        const bool result = ImGui::Button(label, F2ToImV2(size));
        PopStyleColor(3);
        return result;
    }

    bool ButtonColoredText(const char* label, const SR_MATH_NS::FColor& color, const SR_MATH_NS::FVector2& size) {
        SR_TRACY_ZONE;
        PushStyleColor(StyleColor::Text, color);
        const bool result = ImGui::Button(label, F2ToImV2(size));
        PopStyleColor(1);
        return result;
    }

    void PushItemWidth(float_t itemWidth) {
        SR_TRACY_ZONE;
        ImGui::PushItemWidth(itemWidth);
    }

    bool BeginDragDropTarget() {
        SR_TRACY_ZONE;
        return ImGui::BeginDragDropTarget();
    }

    void PopItemWidth() {
        SR_TRACY_ZONE;
        ImGui::PopItemWidth();
    }

    bool Checkbox(const char *label, bool *v) {
        SR_TRACY_ZONE;
        return ImGui::Checkbox(label, v);
    }

    bool DragScalar(const char* label, ImmediateDataType type, void* pData, float_t vSpeed, const void* pMin, const void *pMax, const char* format) {
        SR_TRACY_ZONE;
        return ImGui::DragScalar(label, static_cast<ImGuiDataType_>(type), pData, vSpeed, pMin, pMax, format);
    }

    void PushStyleColor(StyleColor idx, const SR_MATH_NS::FColor& color) {
        SR_TRACY_ZONE;
        ImGui::PushStyleColor(static_cast<ImGuiCol>(idx), FCToImV4(color));
    }

    void PopStyleColor(uint32_t count) {
        SR_TRACY_ZONE;
        ImGui::PopStyleColor(count);
    }

    void BeginGroup() {
        SR_TRACY_ZONE;
        ImGui::BeginGroup();
    }

    void EndGroup() {
        SR_TRACY_ZONE;
        ImGui::EndGroup();
    }

    void EndGroupIfCan() {
        SR_TRACY_ZONE;

        if (GImGui->GroupStack.empty()) {
            return;
        }

        if (GImGui->GroupStack.back().WindowID != GImGui->CurrentWindow->ID) {
            return;
        }

        ImGui::EndGroup();
    }

    float_t GetFrameHeight() {
        return ImGui::GetFrameHeight();
    }

    void Dummy(const SR_MATH_NS::FVector2& size) {
        ImGui::Dummy(F2ToImV2(size));
    }

    bool BeginCombo(const char *label, const char *previewValue, ComboFlags flags) {
        return ImGui::BeginCombo(label, previewValue, static_cast<ImGuiComboFlags>(flags));
    }

    void EndCombo() {
        ImGui::EndCombo();
    }

    bool Selectable(const char* label, bool selected) {
        return ImGui::Selectable(label, selected);
    }

    void SetItemDefaultFocus() {
        ImGui::SetItemDefaultFocus();
    }

    uint32_t BeginForceEnabled() {
        const uint32_t stackSize = GImGui->DisabledStackSize;
        for (uint32_t i = 0; i < stackSize; ++i) {
            ImGui::EndDisabled();
        }
        return stackSize;
    }

    bool WindowsWndProcHandler(void* hWnd, uint32_t message, uint64_t wParam, uint64_t lParam) {
    #ifdef SR_WIN32
        return ImmediateGUI_WndProcHandler((HWND)hWnd, message, (WPARAM)wParam, (LPARAM)lParam);
    #else
        return false;
    #endif
    }

    void GetViewports(SR_UTILS_NS::Vector<void*>& viewports) {
        viewports.clear();
        viewports.reserve(ImGui::GetPlatformIO().Viewports.Size);
        for (auto&& pViewport : ImGui::GetPlatformIO().Viewports) {
            viewports.emplace_back(pViewport);
        }
    }

    void SetTheme(const SR_UTILS_NS::Path& path) {
        g_themePath = path;
    }

    uint32_t GetViewportCount(void* pContext) {
        return static_cast<ImGuiContext*>(pContext)->Viewports.Size;
    }

    void EndForceEnabled(uint32_t stackSize) {
        for (uint32_t i = 0; i < stackSize; ++i) {
            ImGui::BeginDisabled();
        }
    }

    void BeginDisabled(bool disabled) {
        ImGui::BeginDisabled();
    }

    void EndDisabled() {
        ImGui::EndDisabled();
    }

    void* GetCurrentWindow() {
        return ImGui::GetCurrentWindow();
    }

    SR_MATH_NS::FVector2 GetWindowCursorPos(void* pWindow) {
        if (auto&& pImGuiWindow = static_cast<ImGuiWindow*>(pWindow)) {
            return ImV2ToF2(pImGuiWindow->DC.CursorPos);
        }
        return ImV2ToF2(ImGui::GetCurrentWindow()->DC.CursorPos);
    }

    SR_MATH_NS::FVector2 GetCursorScreenPos() {
        return ImV2ToF2(ImGui::GetCursorScreenPos());
    }

    void* GetWindowDrawList(void *pWindow) {
        if (auto&& pImGuiWindow = static_cast<ImGuiWindow*>(pWindow)) {
            return pImGuiWindow->DrawList;
        }
        return ImGui::GetCurrentWindow()->DrawList;
    }

    uint32_t GetColorU32(StyleColor idx, float alpha_mul) {
        return ImGui::GetColorU32(static_cast<ImGuiCol>(idx), alpha_mul);
    }

    void RenderArrow(void* pDrawList, const SR_MATH_NS::FVector2& pos, uint32_t color, Direction dir, float_t scale) {
        if (auto&& pImGuiDrawList = static_cast<ImDrawList*>(pDrawList)) {
            ImGui::RenderArrow(pImGuiDrawList, F2ToImV2(pos), color, static_cast<ImGuiDir>(dir), scale);
        }
    }

    void DrawListAddRect(void* pDrawList, const SR_MATH_NS::FVector2& min, const SR_MATH_NS::FVector2& max, uint32_t color, float rounding, float thickness) {
        if (auto&& pImGuiDrawList = static_cast<ImDrawList*>(pDrawList)) {
            pImGuiDrawList->AddRect(F2ToImV2(min), F2ToImV2(max), color, rounding, 0, thickness);
        }
    }

    void DrawListAddRectFilled(void* pDrawList, const SR_MATH_NS::FVector2& min, const SR_MATH_NS::FVector2& max, uint32_t color, float rounding, DrawFlags flags) {
        if (auto&& pImGuiDrawList = static_cast<ImDrawList*>(pDrawList)) {
            pImGuiDrawList->AddRectFilled(F2ToImV2(min), F2ToImV2(max), color, rounding, static_cast<ImDrawFlags>(flags));
        }
    }

    void DrawListAddLine(void* pDrawList, const SR_MATH_NS::FVector2& p1, const SR_MATH_NS::FVector2& p2, uint32_t color, float thickness) {
        if (auto&& pImGuiDrawList = static_cast<ImDrawList*>(pDrawList)) {
            pImGuiDrawList->AddLine(F2ToImV2(p1), F2ToImV2(p2), color, thickness);
        }
    }

    bool InputFloat(const char* label, float_t* v, float_t step, float_t stepFast, const char* format, InputTextFlags flags) {
        SR_TRACY_ZONE;
        return ImGui::InputFloat(label, v, step, stepFast, format, static_cast<ImGuiInputTextFlags>(flags));
    }

    bool InputInt(const char* label, int* v, int step, int step_fast, InputTextFlags flags) {
        SR_TRACY_ZONE;
        return ImGui::InputInt(label, v, step, step_fast, static_cast<ImGuiInputTextFlags>(flags));
    }

    bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros) {
        SR_TRACY_ZONE;
        return ImGui::Combo(label, current_item, items_separated_by_zeros);
    }

    void DrawTextOnCenter(const std::string& text, ImVec4 color) {
        const auto fontSize = ImGui::GetFontSize() * static_cast<float_t>(text.size()) / 2.f;
        ImGui::SameLine(ImGui::GetWindowSize().x / 2 - fontSize + (fontSize / 2));
        ImGui::TextColored(color, "%s", text.c_str());
    }

    void DrawMultiLineTextOnCenter(const std::string& text) {
        const float_t winWidth = ImGui::GetWindowSize().x;
        const float_t textWidth = ImGui::CalcTextSize(text.c_str()).x;

        /// calculate the indentation that centers the text on one line, relative
        /// to window left, regardless of the `ImGuiStyleVar_WindowPadding` value
        float_t textIndentation = (winWidth - textWidth) * 0.5f;

        /// if text is too long to be drawn on one line, `text_indentation` can
        /// become too small or even negative, so we check a minimum indentation
        float_t minIndentation = 20.0f;
        if (textIndentation <= minIndentation) {
            textIndentation = minIndentation;
        }

        ImGui::SameLine(textIndentation);
        ImGui::PushTextWrapPos(winWidth - textIndentation);
        ImGui::TextWrapped("%s", text.c_str());
        ImGui::PopTextWrapPos();
    }

    void DrawMultiLineTextOnCenter(const std::string &text, ImVec4 color) {
        const float_t winWidth = ImGui::GetWindowSize().x;
        const float_t textWidth = ImGui::CalcTextSize(text.c_str()).x;

        /// calculate the indentation that centers the text on one line, relative
        /// to window left, regardless of the `ImGuiStyleVar_WindowPadding` value
        float_t textIndentation = (winWidth - textWidth) * 0.5f;

        /// if text is too long to be drawn on one line, `text_indentation` can
        /// become too small or even negative, so we check a minimum indentation
        float_t minIndentation = 20.0f;
        if (textIndentation <= minIndentation) {
            textIndentation = minIndentation;
        }

        ImGui::SameLine(textIndentation);

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::PushTextWrapPos(winWidth - textIndentation);

        ImGui::TextWrapped("%s", text.c_str());

        ImGui::PopTextWrapPos();
        ImGui::PopStyleColor();
    }

    bool CollapsingHeader(const std::string& label, TreeNodeFlags _flags) {
        ImGuiWindow* pWindow = ImGui::GetCurrentWindow();
        if (pWindow->SkipItems) {
            return false;
        }

        ImGuiTreeNodeFlags flags = static_cast<ImGuiTreeNodeFlags>(_flags);

        ImGuiID id = pWindow->GetID(label.c_str());
        flags |= ImGuiTreeNodeFlags_CollapsingHeader;
        flags |= ImGuiTreeNodeFlags_AllowOverlap | static_cast<ImGuiTreeNodeFlags>(ImGuiTreeNodeFlags_ClipLabelForTrailingButton);

        return ImGui::TreeNodeBehavior(id, flags, label.c_str());
    }

    bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding, ButtonFlags flags) {
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

        const bool result = ImageButtonInternal(imageId.data(), pDescriptor, size, framePadding, flags);

        ImGui::PopStyleColor();

        return result;
    }

    bool ImageButtonInternal(std::string_view &&imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding, ButtonFlags flags) {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        if (window->SkipItems)
            return false;

        ImVec4 bg_col = ImVec4(0,0,0,0);
        ImVec4 tint_col = ImVec4(1,1,1,1);
        ImVec2 uv0, uv1;

        /// if (m_pipeLine == Graphics::PipelineType::OpenGL) {
        uv0 = ImVec2(0, 0);
        uv1 = ImVec2(1, 1);
        /// }
        /// else {
        //uv0 = ImVec2(-1, 0);
        //uv1 = ImVec2(0, 1);
        ///}

        /// Default is to use texture ID as ID. User can still push string/integer prefixes.
        ImGui::PushID((void*)(intptr_t)pDescriptor);
        const ImGuiID id = window->GetID(imageId.data());
        ImGui::PopID();

        const ImVec2 padding = (framePadding >= 0) ? ImVec2((float)framePadding, (float)framePadding) : g.Style.FramePadding;

        const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(size.x, size.y) + padding * 2);
        ImGui::ItemSize(bb);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

        /// Render
        const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
        ImGui::RenderNavHighlight(bb, id);
        ImGui::RenderFrame(bb.Min, bb.Max, col, true, SR_CLAMP((float)SR_MIN(padding.x, padding.y), 0.0f, g.Style.FrameRounding));
        if (bg_col.w > 0.0f)
            window->DrawList->AddRectFilled(bb.Min + padding, bb.Max - padding, ImGui::GetColorU32(bg_col));
        if (pDescriptor) {
            window->DrawList->AddImage((ImTextureID) pDescriptor, bb.Min + padding, bb.Max - padding, uv0, uv1, ImGui::GetColorU32(tint_col));
        }

        return pressed;
    }

    SR_MATH_NS::FVector2 DrawTexture(const void* pDescriptor, const SR_MATH_NS::FVector2& size, bool imposition) {
        if (!pDescriptor) {
            return SR_MATH_NS::FVector2(); /// NOLINT
        }

        auto&& fSize = size.Cast<float_t>();
        return DrawImage(const_cast<void*>(pDescriptor), SR_MATH_NS::FVector2(fSize.x, fSize.y), SR_MATH_NS::FVector2(0, 0), SR_MATH_NS::FVector2(1, 1), { 1, 1, 1, 1 }, { 0, 0, 0, 0 }, imposition);
    }

    SR_MATH_NS::FVector2 DrawImage(void* user_texture_id, const SR_MATH_NS::FVector2& size, const SR_MATH_NS::FVector2& uv0, const SR_MATH_NS::FVector2& uv1, const SR_MATH_NS::FColor& tint_col, const SR_MATH_NS::FColor& border_col, bool imposition) {
        ImGuiWindow* pWindow = ImGui::GetCurrentWindow();
        if (pWindow->SkipItems) {
            return SR_MATH_NS::FVector2(); /// NOLINT
        }

        ImRect bb(pWindow->DC.CursorPos, pWindow->DC.CursorPos + F2ToImV2(size));
        if (border_col.w > 0.0f) {
            bb.Max = bb.Max + ImVec2(2, 2);
        }

        if (!imposition) {
            ImGui::ItemSize(bb);
            if (!ImGui::ItemAdd(bb, 0)) {
                return SR_MATH_NS::FVector2(); /// NOLINT
            }
        }

        if (border_col.w > 0.0f) {
            pWindow->DrawList->AddRect(bb.Min, bb.Max, ImGui::GetColorU32(FCToImV4(border_col)), 0.0f);
            pWindow->DrawList->AddImage(user_texture_id, bb.Min + ImVec2(1, 1), bb.Max - ImVec2(1, 1), F2ToImV2(uv0), F2ToImV2(uv1), ImGui::GetColorU32(FCToImV4(tint_col)));
        }
        else {
            pWindow->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, F2ToImV2(uv0), F2ToImV2(uv1), ImGui::GetColorU32(FCToImV4(tint_col)));
        }

        return ImV2ToF2(bb.GetTL());
    }

    bool BeginDragDropTargetWindow(const char* payloadType) {
        ImRect inner_rect = ImGui::GetCurrentWindow()->InnerRect;

        if (!ImGui::BeginDragDropTargetCustom(inner_rect, ImGui::GetID("##WindowBgArea"))) {
            return false;
        }

        if (payloadType) {
            if (const ImGuiPayload* payload = ImGui::GetDragDropPayload()) {
                if (strcmp(payload->DataType, payloadType) == 0) {
                    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
                    draw_list->AddRectFilled(inner_rect.Min, inner_rect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget, 0.05f));
                    draw_list->AddRect(inner_rect.Min, inner_rect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget), 0.0f, 0, 2.0f);
                }
            }
        }

        return true;
    }

    bool ImageButton(void* pDescriptor, const SR_MATH_NS::FVector2& size) {
        return ImageButton(pDescriptor, size, -1);
    }

    bool ImageButton(void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding) {
        return ImageButton("##image", pDescriptor, size, framePadding);
    }

    bool ImageButtonDouble(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding) {
        return ImageButton(imageId.data(), pDescriptor, size, framePadding, ButtonFlags::PressedOnDoubleClick);
    }

    bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding) {
        return ImageButton(imageId.data(), pDescriptor, size, framePadding, ButtonFlags::None);
    }

    int ImTextCharToUtf8(char* pBuffer, int32_t bufSize, uint32_t c) {
        if (c < 0x80)
        {
            pBuffer[0] = (char)c;
            return 1;
        }
        if (c < 0x800)
        {
            if (bufSize < 2) return 0;
            pBuffer[0] = (char)(0xc0 + (c >> 6));
            pBuffer[1] = (char)(0x80 + (c & 0x3f));
            return 2;
        }
        if (c < 0x10000)
        {
            if (bufSize < 3) return 0;
            pBuffer[0] = (char)(0xe0 + (c >> 12));
            pBuffer[1] = (char)(0x80 + ((c >> 6) & 0x3f));
            pBuffer[2] = (char)(0x80 + ((c ) & 0x3f));
            return 3;
        }
        if (c <= 0x10FFFF)
        {
            if (bufSize < 4) return 0;
            pBuffer[0] = (char)(0xf0 + (c >> 18));
            pBuffer[1] = (char)(0x80 + ((c >> 12) & 0x3f));
            pBuffer[2] = (char)(0x80 + ((c >> 6) & 0x3f));
            pBuffer[3] = (char)(0x80 + ((c ) & 0x3f));
            return 4;
        }
        /// Invalid code point, the max unicode is 0x10FFFF
        return 0;
    }

    bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size) {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        ImGuiID id = window->GetID("##Splitter");
        ImRect bb;
        bb.Min = window->DC.CursorPos + (split_vertically ? ImVec2(*size1, 0.0f) : ImVec2(0.0f, *size1));
        bb.Max = bb.Min + ImGui::CalcItemSize(split_vertically ? ImVec2(thickness, splitter_long_axis_size) : ImVec2(splitter_long_axis_size, thickness), 0.0f, 0.0f);
        return ImGui::SplitterBehavior(bb, id, split_vertically ? ImGuiAxis_X : ImGuiAxis_Y, size1, size2, min_size1, min_size2, 0.0f);
    }

    bool BeginTabBar(const char *str_id) {
        return ImGui::BeginTabBar(str_id);
    }

    void EndTabBar() {
        ImGui::EndTabBar();
    }

    void TextWrapped(const char* text, ...) {
        va_list args;
        va_start(args, text);
        ImGui::TextWrappedV(text, args);
        va_end(args);
    }

    void PushFont(void* pFont) {
        ImGui::PushFont(static_cast<ImFont*>(pFont));
    }

    void SetWindowFocus(const char* name) {
        ImGui::SetWindowFocus(name);
    }

    void PopFont() {
        ImGui::PopFont();
    }

    float_t GetFontSize() {
        return ImGui::GetFontSize();
    }

    SR_MATH_NS::FVector2 GetFramePadding() {
        return ImV2ToF2(GImGui->Style.FramePadding);
    }

    void SetKeyboardFocusHere() {
        ImGui::SetKeyboardFocusHere();
    }

    void CloseCurrentPopup() {
        ImGui::CloseCurrentPopup();
    }

    bool InputText(const char* label, std::string* str, InputTextFlags flags) {
        SR_TRACY_ZONE;
        return ImGui::InputText(label, str, static_cast<ImGuiInputTextFlags>(flags));
    }

    bool MenuItem(const char *label) {
        SR_TRACY_ZONE;
        return ImGui::MenuItem(label);
    }

    void EndMenu() {
        ImGui::EndMenu();
    }

    bool BeginListBox(const char* label, const SR_MATH_NS::FVector2& size) {
        return ImGui::BeginListBox(label, F2ToImV2(size));
    }

    void EndListBox() {
        ImGui::EndListBox();
    }

    bool BeginMenu(const char *label) {
        SR_TRACY_ZONE;
        return ImGui::BeginMenu(label);
    }

    void LabelText(const char* label, const char *text, ...) {
        SR_TRACY_ZONE;
        va_list args;
        va_start(args, text);
        ImGui::LabelTextV(label, text, args);
        va_end(args);
    }

    float_t GetFramerate() {
        return ImGui::GetIO().Framerate;
    }

    void LoadIniSettingsFromDisk() {
        ImGuiContext& g = *GImGui;
        if (g.IO.IniFilename)
            ImGui::LoadIniSettingsFromDisk(g.IO.IniFilename);
        g.SettingsLoaded = true;
    }

    void BeginDocking() {
        SR_TRACY_ZONE;

        ImGuiViewport* pViewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(pViewport->Pos);
        ImGui::SetNextWindowSize(pViewport->Size);
        ImGui::SetNextWindowViewport(pViewport->ID);

        static constexpr ImGuiWindowFlags windowFlags = 0
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
            | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("SpaRcle Engine", nullptr, windowFlags);
    }

    void EndDocking() {
        SR_TRACY_ZONE;
        ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        ImGui::End();
        ImGui::PopStyleVar(3);
    }

    void FocusTopMostWindowUnderOne() {
        SR_TRACY_ZONE;
        ImGuiContext& g = *GImGui;
        if (g.CurrentWindow == g.NavWindow && g.NavLayer == ImGuiNavLayer_Main && !g.NavAnyRequest) {
            ImGui::FocusTopMostWindowUnderOne(g.NavWindow, nullptr, nullptr, ImGuiFocusRequestFlags_None);
        }
    }

    bool BeginMainMenuBar() {
        SR_TRACY_ZONE;
        return ImGui::BeginMainMenuBar();
    }

    void EndMenuBar() {
        SR_TRACY_ZONE;
        ImGui::EndMenuBar();
    }

    void End() {
        SR_TRACY_ZONE;
        ImGui::End();
    }

    bool SmallButton(const char *label) {
        SR_TRACY_ZONE;
        return ImGui::SmallButton(label);
    }

    void SetCursorPosX(float_t x) {
        SR_TRACY_ZONE;
        ImGui::SetCursorPosX(x);
    }

    void SetCursorPosY(float_t y) {
        SR_TRACY_ZONE;
        ImGui::SetCursorPosY(y);
    }

    SR_MATH_NS::FVector2 GetCursorPos() {
        SR_TRACY_ZONE;
        return ImV2ToF2(ImGui::GetCursorPos());
    }

    SR_MATH_NS::FVector2 GetWindowSize() {
        SR_TRACY_ZONE;
        return ImV2ToF2(ImGui::GetWindowSize());
    }

    bool IsMouseDragging(MouseButton button) {
        SR_TRACY_ZONE;
        return ImGui::IsMouseDragging(static_cast<ImGuiMouseButton>(button));
    }

    bool IsMouseReleased(MouseButton button) {
        SR_TRACY_ZONE;
        return ImGui::IsMouseReleased(static_cast<ImGuiMouseButton>(button));
    }

    bool IsMouseDown(MouseButton button) {
        SR_TRACY_ZONE;
        return ImGui::IsMouseDown(static_cast<ImGuiMouseButton>(button));
    }

    void SetMousePos(const SR_MATH_NS::FVector2& pos) {
        ImGui::GetIO().MousePos = F2ToImV2(pos);
    }

    bool* GetMouseDown() {
        return ImGui::GetIO().MouseDown;
    }

    SR_MATH_NS::FVector2 GetMousePos() {
        return ImV2ToF2(ImGui::GetMousePos());
    }

    SR_MATH_NS::FRect GetWindowRect(void* pWindow) {
        if (auto&& pImGuiWindow = static_cast<ImGuiWindow*>(pWindow)) {
            return IRToFR(pImGuiWindow->Rect());
        }
        return IRToFR(ImGui::GetCurrentWindow()->Rect());
    }

    bool IsItemFocused() {
        return ImGui::IsItemFocused();
    }

    void ClearFonts() {
        ImGui::GetIO().Fonts->Clear();
        g_fontsRebuildPending = true;
    }

    bool BuildFonts(void* pDefaultFont) {
        auto&& io = ImGui::GetIO();
        io.FontDefault = static_cast<ImFont*>(pDefaultFont);
        // Defer actual build/upload until NewFrame(), after backends had a chance to set BackendFlags.
        g_fontsRebuildPending = true;
        return true;
    }

    void* AddFontFromMemoryTTF(const void* fontData, int fontDataSize, float size, const ImmediateGUIFontConfig& config, const uint32_t* glyphRanges) {
        ImFontConfig imConfig;
        imConfig.MergeMode = config.mergeMode;
        imConfig.PixelSnapH = config.pixelSnapH;
        imConfig.OversampleH = config.oversampleH;
        imConfig.OversampleV = config.oversampleV;
        imConfig.GlyphMinAdvanceX = config.glyphMinAdvanceX;
        imConfig.FontDataOwnedByAtlas = config.fontDataOwnedByAtlas;

        return ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)fontData, fontDataSize, size, &imConfig, glyphRanges);
    }

    static SR_UTILS_NS::Path INI_FILE_PATH;

    static void* ImGuiMallocWrapper(size_t size, void* user_data) { SR_TRACY_ZONE; IM_UNUSED(user_data); return SRMalloc(size); }
    static void  ImGuiFreeWrapper(void* ptr, void* user_data)     { SR_TRACY_ZONE; IM_UNUSED(user_data); SRFree(ptr); }

    void* CreateContext(const ImmediateGUICreateContext& context) {
        if (!ImGui::CreateContext()) {
            SRHalt("Failed to create ImGui context!");
        }

        if (!ImPlot::CreateContext()) {
            SRHalt("Failed to create ImPlot context!");
        }

        ImGui::SetAllocatorFunctions(ImGuiMallocWrapper, ImGuiFreeWrapper, nullptr);

        INI_FILE_PATH = context.iniPath;

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigDockingWithShift = true;
        io.ConfigWindowsResizeFromEdges = true;
        io.ConfigViewportsNoDecoration = true;
        io.ConfigWindowsMoveFromTitleBarOnly = true;
        io.IniFilename = INI_FILE_PATH.CStr();

        if (context.viewportsEnabled) {
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }

        //if (auto&& pTheme = SR_GRAPH_GUI_NS::Theme::Load("Engine/Configs/Themes/Dark.xml")) {
        //    pTheme->Apply();
        //    delete pTheme;
        //}
        //else {
        //    SR_ERROR("Immediate::CreateContext() : failed to load theme!");
        //}

        if (!g_themePath.empty()) {
            SR_UTILS_NS::ResourceRef<SR_GRAPH_GUI_NS::Immediate::ImGUITheme> theme(g_themePath);
            if (auto&& pTheme = theme.GetResource()) {
                pTheme->Apply();
            }
        }

        return ImGui::GetCurrentContext();
    }

    void DestroyContext(void* pContext) {
        ImPlot::DestroyContext();
        ImGui::DestroyContext(static_cast<ImGuiContext*>(pContext));
    }

    void* GetViewportPlatformHandle(void* pViewport) {
        return static_cast<ImGuiViewport*>(pViewport)->PlatformHandle;
    }

    void SetWindowSize(const SR_MATH_NS::FVector2& size, Condition cond) {
        ImGui::SetWindowSize(F2ToImV2(size), static_cast<ImGuiCond>(cond));
    }

    void SetNextWindowSize(const SR_MATH_NS::FVector2& size, Condition cond) {
        ImGui::SetNextWindowSize(F2ToImV2(size), static_cast<ImGuiCond>(cond));
    }

    void SetNextWindowPos(const SR_MATH_NS::FVector2& pos, Condition cond, const SR_MATH_NS::FVector2& pivot) {
        ImGui::SetNextWindowPos(F2ToImV2(pos), static_cast<ImGuiCond>(cond), F2ToImV2(pivot));
    }

    SR_MATH_NS::FVector2 GetDisplaySize() {
        return ImV2ToF2(ImGui::GetIO().DisplaySize);
    }

    void* GetWindowViewport() {
        return ImGui::GetWindowViewport();
    }

    bool RadioButton(const char* label, bool active, float_t radius) {
        SR_TRACY_ZONE;

        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        const float square_sz = ImGui::GetFrameHeight() * radius;
        const ImVec2 pos = window->DC.CursorPos;

        // Precalculate flags and dimensions
        const bool has_label = label_size.x > 0.0f;
        const float label_offset = has_label ? style.ItemInnerSpacing.x + label_size.x : 0.0f;
        const float padding_scaled = style.FramePadding.y / 1.75f;

        const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
        const ImRect total_bb(pos, pos + ImVec2(square_sz + label_offset,
                                                (label_size.y + style.FramePadding.y * 2.0f) / 1.75f));

        ImGui::ItemSize(total_bb, padding_scaled);
        if (!ImGui::ItemAdd(total_bb, id))
            return false;

        // Calculate center once
        const float half_square = square_sz * 0.5f;
        ImVec2 center = ImVec2(pos.x + half_square, pos.y + half_square);
        center.x = IM_ROUND(center.x);
        center.y = IM_ROUND(center.y);

        const float radiusInternal = (square_sz - 1.0f) * 0.5f;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);

        if (pressed)
            ImGui::MarkItemEdited(id);

        ImGui::RenderNavHighlight(total_bb, id);

        // Determine segment count based on size
        const int num_segments = 4;

        // Calculate background color once
        const ImGuiCol frame_col = (held && hovered) ? ImGuiCol_FrameBgActive
                                                     : hovered ? ImGuiCol_FrameBgHovered
                                                               : ImGuiCol_FrameBg;

        window->DrawList->AddCircleFilled(center, radiusInternal,
                                          ImGui::GetColorU32(frame_col), num_segments);

        if (active) {
            const float pad = ImMax(1.0f, ((float)(int)(square_sz / 6.0f)));
            window->DrawList->AddCircleFilled(center, radiusInternal - pad,
                                              ImGui::GetColorU32(ImGuiCol_CheckMark), num_segments);
        }

        if (style.FrameBorderSize > 0.0f) {
            window->DrawList->AddCircle(center + ImVec2(1, 1), radiusInternal,
                                        ImGui::GetColorU32(ImGuiCol_BorderShadow),
                                        num_segments, style.FrameBorderSize);
            window->DrawList->AddCircle(center, radiusInternal,
                                        ImGui::GetColorU32(ImGuiCol_Border),
                                        num_segments, style.FrameBorderSize);
        }

        // Only process label if needed
        if (has_label || g.LogEnabled) {
            ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x,
                                      check_bb.Min.y + style.FramePadding.y);
            if (g.LogEnabled)
                ImGui::LogRenderedText(&label_pos, active ? "(x)" : "( )");
            if (has_label)
                ImGui::RenderText(label_pos, label);
        }

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
        return pressed;
    }

    void EndPopup() {
        ImGui::EndPopup();
    }

    bool BeginPopup(const char *name) {
        return ImGui::BeginPopup(name);
    }

    void SetCursorPos(const SR_MATH_NS::FVector2& pos) {
        ImGui::SetCursorPos(F2ToImV2(pos));
    }

    float_t GetScrollbarSize() {
        return ImGui::GetStyle().ScrollbarSize;
    }

    bool IsItemDeactivatedAfterEdit() {
        return ImGui::IsItemDeactivatedAfterEdit();
    }

    void* GetCurrentContext() {
        return ImGui::GetCurrentContext();
    }

    bool IsWindowFocused() {
        return ImGui::IsWindowFocused();
    }

    bool BeginChild(const char* name, const SR_MATH_NS::FVector2& size, ChildWindowFlags childFlags, WindowFlags flags) {
        return ImGui::BeginChild(name, F2ToImV2(size), static_cast<ImGuiChildFlags>(childFlags), static_cast<ImGuiWindowFlags>(flags));
    }

    bool BeginTable(const char* str_id, int columns) {
        return ImGui::BeginTable(str_id, columns);
    }

    void TableSetColumnIndex(int column_n) {
        ImGui::TableSetColumnIndex(column_n);
    }

    void EndTable() {
        ImGui::EndTable();
    }

    void EndChild() {
        ImGui::EndChild();
    }

    void TableNextRow() {
        ImGui::TableNextRow();
    }

    const void* AcceptDragDropPayload(const char* type) {
        SR_TRACY_ZONE;
        return ImGui::AcceptDragDropPayload(type);
    }

    void EndDragDropTarget() {
        ImGui::EndDragDropTarget();
    }

    void* GetDataFromDragDropPayload(const void* pPayload) {
        SR_TRACY_ZONE;
        return static_cast<const ImGuiPayload*>(pPayload)->Data;
    }

    bool BeginTabItem(const char *str_id) {
        return ImGui::BeginTabItem(str_id);
    }

    void EndTabItem() {
        ImGui::EndTabItem();
    }

    float_t GetScrollMaxY() {
        return ImGui::GetScrollMaxY();
    }

    SR_MATH_NS::FVector2 GetContentRegionAvail() {
        return ImV2ToF2(ImGui::GetContentRegionAvail());
    }

    SR_MATH_NS::FVector2 CalcTextSize(const char *text) {
        return ImV2ToF2(ImGui::CalcTextSize(text));
    }

    SR_MATH_NS::FVector2 GetItemRectSize() {
        return ImV2ToF2(ImGui::GetItemRectSize());
    }

    SR_MATH_NS::FVector2 GetItemRectMin() {
        return ImV2ToF2(ImGui::GetItemRectMin());
    }

    void OpenPopup(const char *str_id) {
        ImGui::OpenPopup(str_id);
    }

    void AddText(void* pDrawList, const SR_MATH_NS::FVector2& pos, uint32_t color, const char* text) {
        if (auto&& pImGuiDrawList = static_cast<ImDrawList*>(pDrawList)) {
            pImGuiDrawList->AddText(F2ToImV2(pos), color, text);
        }
    }

    bool IsItemClicked(MouseButton button) {
        return ImGui::IsItemClicked(static_cast<ImGuiMouseButton>(button));
    }

    const void* GetDragDropPayload() {
        SR_TRACY_ZONE;
        return ImGui::GetDragDropPayload();
    }

    void EndDragDropSource() {
        ImGui::EndDragDropSource();
    }

    bool BeginDragDropSource(DragDropFlags flags) {
        return ImGui::BeginDragDropSource(static_cast<ImGuiDragDropFlags>(flags));
    }

    void SetDragDropPayload(const char *type, const void *data, size_t size, Condition cond) {
        ImGui::SetDragDropPayload(type, data, size, static_cast<ImGuiCond>(cond));
    }

    void WindowTreeNodeSetOpen(bool open, uint64_t id) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImGui::TreeNodeSetOpen(window->GetID((void*)(intptr_t)id), true);
    }

    bool IsAnyItemHovered() {
        return ImGui::IsAnyItemHovered();
    }

    bool IsWindowHovered(HoveredFlags flags) {
        SR_TRACY_ZONE;
        return ImGui::IsWindowHovered(static_cast<ImGuiHoveredFlags>(flags));
    }

    bool IsMouseDoubleClicked(MouseButton button) {
        return ImGui::IsMouseDoubleClicked(static_cast<ImGuiMouseButton>(button));
    }

    bool BeginPopupContextWindow(const char *str_id) {
        return ImGui::BeginPopupContextWindow(str_id);
    }

    bool BeginPopupContextItem(const char *str_id) {
        return ImGui::BeginPopupContextItem(str_id);
    }

    bool IsItemHovered() {
        return ImGui::IsItemHovered();
    }

    bool TreeNodeEx(const void *ptr_id, TreeNodeFlags flags, const char *fmt, ...) {
        SR_TRACY_ZONE;
        va_list args;
        va_start(args, fmt);
        const bool result = ImGui::TreeNodeExV(ptr_id, static_cast<ImGuiTreeNodeFlags>(flags), fmt, args);
        va_end(args);
        return result;
    }

    void TreePop() {
        SR_TRACY_ZONE;
        ImGui::TreePop();
    }

    const char* GetPayloadType(const void *pPayload) {
        return static_cast<const ImGuiPayload*>(pPayload)->DataType;
    }

    float_t GetFrameHeightWithSpacing() {
        return ImGui::GetFrameHeightWithSpacing();
    }

    bool IsItemToggledOpen() {
        return ImGui::IsItemToggledOpen();
    }

    bool DragFloat(const char *label, float_t *v, float_t vSpeed, const float_t min, const float_t max, const char *format) {
        return ImGui::DragFloat(label, v, vSpeed, min, max, format);
    }

    bool DragFloat2(const char *label, float_t v[2], float_t vSpeed, const float_t min, const float_t max, const char *format) {
        return ImGui::DragFloat2(label, v, vSpeed, min, max, format);
    }

    bool DragFloat3(const char *label, float_t v[3], float_t vSpeed, const float_t min, const float_t max, const char *format) {
        return ImGui::DragFloat3(label, v, vSpeed, min, max, format);
    }

    bool SliderFloat(const char *label, float_t *v, float_t min, float_t max, const char *format) {
        return ImGui::SliderFloat(label, v, min, max, format);
    }

    bool SliderInt(const char *label, int *v, int min, int max, const char *format) {
        return ImGui::SliderInt(label, v, min, max, format);
    }

    bool InputText(const char *label, char *str, size_t strSize, InputTextFlags flags) {
        return ImGui::InputText(label, str, strSize, static_cast<ImGuiInputTextFlags>(flags));
    }

    bool InputTextMultiline(const char *label, std::string *str, const SR_MATH_NS::FVector2 &size, InputTextFlags flags) {
        return ImGui::InputTextMultiline(label, str, F2ToImV2(size), static_cast<ImGuiInputTextFlags>(flags));
    }

    void* FindWindowByName(const char *name) {
        return ImGui::FindWindowByName(name);
    }

    void TextVertical(const char* text, SR_MATH_NS::FVector2 pos, SR_MATH_NS::FColor color) {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImFont* font = ImGui::GetFont();
        const float fontSize = GetFontSize();
        float yOffset = 0.0f;

        for (const char* c = text; *c; c++) {
            char buf[2] = { *c, '\0' };
            draw_list->AddText(
                font,
                fontSize,
                ImVec2(pos.x, pos.y + yOffset),
                ImGui::GetColorU32(FCToImV4(color)),
                buf
            );
            yOffset += fontSize; // шаг вниз
        }

        // Чтобы layout ImGui знал, что занято место
        ImGui::Dummy(ImVec2(0, yOffset));
    }

    bool Begin(const char* id, bool* pOpen, const WindowFlags flags) {
        return ImGui::Begin(id, pOpen, static_cast<ImGuiWindowFlags>(flags));
    }

    void BeginVertical(const char* str_id, const SR_MATH_NS::FVector2& size, float align) {
        Experimental::BeginVertical(str_id, F2ToImV2(size), align);
    }

    void BeginVertical(const void* ptr_id, const SR_MATH_NS::FVector2& size, float align) {
        Experimental::BeginVertical(ptr_id, F2ToImV2(size), align);
    }

    SR_MATH_NS::FVector2 GetItemRectMax() {
        return ImV2ToF2(ImGui::GetItemRectMax());
    }

    void DrawListAddTriangleFilled(void* pDrawList, const SR_MATH_NS::FVector2& a, const SR_MATH_NS::FVector2& b, const SR_MATH_NS::FVector2& c, uint32_t color) {
        if (auto&& pImGuiDrawList = static_cast<ImDrawList*>(pDrawList)) {
            pImGuiDrawList->AddTriangleFilled(F2ToImV2(a), F2ToImV2(b), F2ToImV2(c), color);
        }
    }

    bool IsItemVisible() {
        return ImGui::IsItemVisible();
    }

    float GetStyleVarFloat(StyleVar idx) {
        auto&& style = ImGui::GetStyle();
        switch (idx) {
            case StyleVar::Alpha: return style.Alpha;
            case StyleVar::DisabledAlpha: return style.DisabledAlpha;
            case StyleVar::WindowRounding: return style.WindowRounding;
            case StyleVar::ChildRounding: return style.ChildRounding;
            case StyleVar::PopupRounding: return style.PopupRounding;
            case StyleVar::FrameRounding: return style.FrameRounding;
            case StyleVar::GrabRounding: return style.GrabRounding;
            case StyleVar::TabRounding: return style.TabRounding;
            default:
                SRHalt("Unsupported StyleVar!");
                return 0.0f;
        }
    }

    SR_MATH_NS::FVector2 GetStyleVarVec2(StyleVar idx) {
        auto&& style = ImGui::GetStyle();
        switch (idx) {
            case StyleVar::WindowPadding: return ImV2ToF2(style.WindowPadding);
            case StyleVar::WindowMinSize: return ImV2ToF2(style.WindowMinSize);
            case StyleVar::WindowTitleAlign: return ImV2ToF2(style.WindowTitleAlign);
            case StyleVar::FramePadding: return ImV2ToF2(style.FramePadding);
            case StyleVar::ItemSpacing: return ImV2ToF2(style.ItemSpacing);
            case StyleVar::ItemInnerSpacing: return ImV2ToF2(style.ItemInnerSpacing);
            case StyleVar::ButtonTextAlign: return ImV2ToF2(style.ButtonTextAlign);
            case StyleVar::SelectableTextAlign: return ImV2ToF2(style.SelectableTextAlign);
            default:
                SRHalt("Unsupported StyleVar!");
                return SR_MATH_NS::FVector2(0.0f, 0.0f);
        }
    }

    void EndVertical() {
        Experimental::EndVertical();
    }

    void BeginHorizontal(const char* str_id, const SR_MATH_NS::FVector2& size, float align) {
        Experimental::BeginHorizontal(str_id, F2ToImV2(size), align);
    }

    void BeginHorizontal(const void* ptr_id, const SR_MATH_NS::FVector2& size, float align) {
        Experimental::BeginHorizontal(ptr_id, F2ToImV2(size), align);
    }

    void EndHorizontal() {
        Experimental::EndHorizontal();
    }

    void Spring(float weight, float spacing) {
        Experimental::Spring(weight, spacing);
    }

    void DrawPinIcon(const SR_MATH_NS::FVector2& size, SR_GRAPH_NS::GUI::IconType iconType, bool filled, const SR_MATH_NS::FColor& color, const SR_MATH_NS::FColor& innerColor) {
        if (ImGui::IsRectVisible(F2ToImV2(size))) {
            auto cursorPos = ImGui::GetCursorScreenPos();
            auto drawList = ImGui::GetWindowDrawList();
            
            auto rect = ImRect(cursorPos, cursorPos + F2ToImV2(size));
            auto rect_center = rect.GetCenter();
            auto rect_w = rect.Max.x - rect.Min.x;
            auto rect_h = rect.Max.y - rect.Min.y;
            
            ImU32 colorU32 = ImColor(FCToImV4(color));
            ImU32 innerColorU32 = ImColor(FCToImV4(innerColor));
            const auto outline_scale = rect_w / 24.0f;
            const auto extra_segments = static_cast<int>(2 * outline_scale);
            
            switch (iconType) {
                case SR_GRAPH_NS::GUI::IconType::Circle: {
                    const auto c = rect_center;
                    if (!filled) {
                        const auto r = 0.5f * rect_w / 2.0f - 0.5f;
                        if (innerColorU32 & 0xFF000000) {
                            drawList->AddCircleFilled(c, r, innerColorU32, 12 + extra_segments);
                        }
                        drawList->AddCircle(c, r, colorU32, 12 + extra_segments, 2.0f * outline_scale);
                    } else {
                        drawList->AddCircleFilled(c, 0.5f * rect_w / 2.0f, colorU32, 12 + extra_segments);
                    }
                    break;
                }
                case SR_GRAPH_NS::GUI::IconType::Square: {
                    if (filled) {
                        const auto r = 0.5f * rect_w / 2.0f;
                        const auto p0 = rect_center - ImVec2(r, r);
                        const auto p1 = rect_center + ImVec2(r, r);
                        drawList->AddRectFilled(p0, p1, colorU32, 0.0f);
                    } else {
                        const auto r = 0.5f * rect_w / 2.0f - 0.5f;
                        const auto p0 = rect_center - ImVec2(r, r);
                        const auto p1 = rect_center + ImVec2(r, r);
                        if (innerColorU32 & 0xFF000000) {
                            drawList->AddRectFilled(p0, p1, innerColorU32, 0.0f);
                        }
                        drawList->AddRect(p0, p1, colorU32, 0.0f, 0, 2.0f * outline_scale);
                    }
                    break;
                }
                case SR_GRAPH_NS::GUI::IconType::Flow: {
                    const auto origin_scale = rect_w / 24.0f;
                    const auto offset_x = 1.0f * origin_scale;
                    const auto offset_y = 0.0f * origin_scale;
                    const auto margin = 2.0f * origin_scale;
                    const auto rounding = 0.1f * origin_scale;
                    const auto tip_round = 0.7f;
                    const auto canvas = ImRect(
                        rect.Min.x + margin + offset_x,
                        rect.Min.y + margin + offset_y,
                        rect.Max.x - margin + offset_x,
                        rect.Max.y - margin + offset_y);
                    const auto canvas_x = canvas.Min.x;
                    const auto canvas_y = canvas.Min.y;
                    const auto canvas_w = canvas.Max.x - canvas.Min.x;
                    const auto canvas_h = canvas.Max.y - canvas.Min.y;
                    const auto left = canvas_x + canvas_w * 0.5f * 0.3f;
                    const auto right = canvas_x + canvas_w - canvas_w * 0.5f * 0.3f;
                    const auto top = canvas_y + canvas_h * 0.5f * 0.2f;
                    const auto bottom = canvas_y + canvas_h - canvas_h * 0.5f * 0.2f;
                    const auto center_y = (top + bottom) * 0.5f;
                    const auto tip_top = ImVec2(canvas_x + canvas_w * 0.5f, top);
                    const auto tip_right = ImVec2(right, center_y);
                    const auto tip_bottom = ImVec2(canvas_x + canvas_w * 0.5f, bottom);
                    
                    drawList->PathLineTo(ImVec2(left, top) + ImVec2(0, rounding));
                    drawList->PathBezierCubicCurveTo(ImVec2(left, top), ImVec2(left, top), ImVec2(left, top) + ImVec2(rounding, 0));
                    drawList->PathLineTo(tip_top);
                    drawList->PathLineTo(tip_top + (tip_right - tip_top) * tip_round);
                    drawList->PathBezierCubicCurveTo(tip_right, tip_right, tip_bottom + (tip_right - tip_bottom) * tip_round);
                    drawList->PathLineTo(tip_bottom);
                    drawList->PathLineTo(ImVec2(left, bottom) + ImVec2(rounding, 0));
                    drawList->PathBezierCubicCurveTo(ImVec2(left, bottom), ImVec2(left, bottom), ImVec2(left, bottom) - ImVec2(0, rounding));
                    
                    if (!filled) {
                        if (innerColorU32 & 0xFF000000) {
                            drawList->AddConvexPolyFilled(drawList->_Path.Data, drawList->_Path.Size, innerColorU32);
                        }
                        drawList->PathStroke(colorU32, ImDrawFlags_Closed, 2.0f * outline_scale);
                    } else {
                        drawList->PathFillConvex(colorU32);
                    }
                    break;
                }
                default:
                    // По умолчанию круг
                    {
                        const auto c = rect_center;
                        drawList->AddCircleFilled(c, 0.5f * rect_w / 2.0f, colorU32, 12 + extra_segments);
                    }
                    break;
            }
        }
        
        ImGui::Dummy(F2ToImV2(size));
    }

    void ShowMetricsWindow(bool* pOpen) {
        ImGui::ShowMetricsWindow(pOpen);
    }

    bool BeginPlot(const char* title_id, const SR_MATH_NS::FVector2& size, PlotFlags flags) {
        ImPlot::BeginPlot(title_id, F2ToImV2(SR_MATH_NS::FVector2(size)), static_cast<ImPlotFlags>(flags));
    }

    void EndPlot() {
        ImPlot::EndPlot();
    }
#endif

#ifndef SR_USE_IMGUI
    void Render() { }
    void NewFrame() { }
    void UpdatePlatformWindows() { }
    void RenderPlatformWindowsDefault() { }

    bool WindowsWndProcHandler(void* hWnd, uint32_t message, uint64_t wParam, uint64_t lParam) { return false; }
    uint32_t GetViewportCount(void* pContext) { return 0; }
    void GetViewports(SR_UTILS_NS::Vector<void*>& viewports) { viewports.clear(); }
    void ClearFonts() { }
    bool BuildFonts(void* pDefaultFont) { return false; }
    void* AddFontFromMemoryTTF(const void* fontData, int fontDataSize, float size, const ImmediateGUIFontConfig& config, const uint32_t* glyphRanges) { return nullptr; }
    void* CreateContext(const ImmediateGUICreateContext& context) { return nullptr; }
    void DestroyContext(void* pContext) { }
    void* GetViewportPlatformHandle(void* pViewport) { return nullptr; }
    void SetWindowSize(const SR_MATH_NS::FVector2& size, Condition cond) { }
    void SetNextWindowSize(const SR_MATH_NS::FVector2& size, Condition cond) { }
    void SetNextWindowPos(const SR_MATH_NS::FVector2& pos, Condition cond, const SR_MATH_NS::FVector2& pivot) { }
    SR_MATH_NS::FVector2 GetDisplaySize() { return SR_MATH_NS::FVector2(0.0f, 0.0f); }
    SR_MATH_NS::FVector4 GetStyleColorVec4(StyleColor idx) { return SR_MATH_NS::FVector4(0.0f, 0.0f, 0.0f, 0.0f); }
    void* GetWindowViewport() { return nullptr; }
    bool RadioButton(const char* label, bool active, float_t radius) { return false; }
    void SetDragDropPayload(const char* type, const void* data, size_t size, Condition cond) { }
    void Separator() { }
    void Text(const char* text, ...) { }
    void TextWrapped(const char* text, ...) { }
    void LabelText(const char* label, const char* text, ...) { }
    void TextColored(const SR_MATH_NS::FColor& color, const char* text, ...) { }
    void TextVertical(const char* text, SR_MATH_NS::FVector2 pos, SR_MATH_NS::FColor color) { }
    void PushID(const char* strId) { }
    void PushID(const void* ptrId) { }
    void PushID(int intId) { }
    void PopID() { }
    bool IsAnyItemHovered() { return false; }
    bool IsWindowHovered(HoveredFlags flags) { return false; }
    void WindowTreeNodeSetOpen(bool open, uint64_t id) { }
    void PushStyleVar(StyleVar idx, float val) { }
    void PushStyleVar(StyleVar idx, const SR_MATH_NS::FVector2& val) { }
    void PopStyleVar(uint32_t count) { }
    float GetStyleVarFloat(StyleVar idx) { return 0.0f; }
    SR_MATH_NS::FVector2 GetStyleVarVec2(StyleVar idx) { return SR_MATH_NS::FVector2(0.0f, 0.0f); }
    bool BeginPopup(const char* name) { return false; }
    void EndPopup() { }
    void SameLine(float_t offsetFromStartX, float_t spacing) { }
    bool Button(const char* label, const SR_MATH_NS::FVector2& size) { return false; }
    bool ButtonColored(const char* label, const SR_MATH_NS::FColor& color, const SR_MATH_NS::FVector2& size) { return false; }
    bool ButtonColoredText(const char* label, const SR_MATH_NS::FColor& color, const SR_MATH_NS::FVector2& size) { return false; }
    bool Checkbox(const char* label, bool* v) { return false; }
    bool IsCurrentlyDisabled() { return false; }
    bool IsItemHovered() { return false; }
    bool IsItemFocused() { return false; }
    bool DragScalar(const char* label, ImmediateDataType type, void* pData, float_t vSpeed, const void* pMin, const void* pMax, const char* format) { return false; }
    void PushItemWidth(float_t itemWidth) { }
    void PopItemWidth() { }
    void PushStyleColor(StyleColor idx, const SR_MATH_NS::FColor& color) { }
    void PopStyleColor(uint32_t count) { }
    void BeginGroup() { }
    void EndGroup() { }
    void EndGroupIfCan() { }
    void TreePop() { }
    bool BeginDragDropSource(DragDropFlags flags) { return false; }
    float_t GetFrameHeight() { return 0.0f; }
    void Dummy(const SR_MATH_NS::FVector2& size) { }
    bool BeginCombo(const char* label, const char* previewValue, ComboFlags flags) { return false; }
    void EndCombo() { }
    bool Selectable(const char* label, bool selected) { return false; }
    void SetItemDefaultFocus() { }
    uint32_t BeginForceEnabled() { return 0; }
    void EndForceEnabled(uint32_t stackSize) { }
    void BeginDisabled(bool disabled) { }
    void EndDisabled() { }
    void EndDragDropSource() { }
    void* GetCurrentWindow() { return nullptr; }
    SR_MATH_NS::FVector2 GetWindowCursorPos(void* pWindow) { return SR_MATH_NS::FVector2(0.0f, 0.0f); }
    SR_MATH_NS::FVector2 GetCursorScreenPos() { return SR_MATH_NS::FVector2(0.0f, 0.0f); }
    void* GetWindowDrawList(void* pWindow) { return nullptr; }
    uint32_t GetColorU32(StyleColor idx, float alpha_mul) { return 0; }
    void RenderArrow(void* pDrawList, const SR_MATH_NS::FVector2& pos, uint32_t color, Direction dir, float_t scale) { }
    void DrawListAddRect(void* pDrawList, const SR_MATH_NS::FVector2& min, const SR_MATH_NS::FVector2& max, uint32_t color, float rounding, float thickness) { }
    void DrawListAddRectFilled(void* pDrawList, const SR_MATH_NS::FVector2& min, const SR_MATH_NS::FVector2& max, uint32_t color, float rounding, DrawFlags flags) { }
    void DrawListAddLine(void* pDrawList, const SR_MATH_NS::FVector2& p1, const SR_MATH_NS::FVector2& p2, uint32_t color, float thickness) { }
    bool InputFloat(const char* label, float_t* v, float_t step, float_t stepFast, const char* format, InputTextFlags flags) { return false; }
    bool InputInt(const char* label, int* v, int step, int step_fast, InputTextFlags flags) { return false; }
    bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros) { return false; }
    bool Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items) { return false; }
    bool Begin(const char* name, bool* p_open, WindowFlags flags) { return false; }
    bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size) { return false; }
    bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding) { return false; }
    bool ImageButtonDouble(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding) { return false; }
    bool ImageButton(void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding) { return false; }
    bool ImageButton(void* pDescriptor, const SR_MATH_NS::FVector2& size) { return false; }
    bool BeginDragDropTargetWindow(const char* payloadType) { return false; }
    bool ImageButtonInternal(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2 &size, float_t framePadding, ButtonFlags flags) { return false; }
    bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::FVector2& size, float_t framePadding, ButtonFlags flags) { return false; }
    bool CollapsingHeader(const std::string& label, TreeNodeFlags flags) { return false; }
    void DrawMultiLineTextOnCenter(const std::string& text) { }
    void DrawMultiLineTextOnCenter(const std::string& text, const SR_MATH_NS::FColor& color) { }
    void DrawTextOnCenter(const std::string& text, const SR_MATH_NS::FColor& color) { }
    int ImTextCharToUtf8(char* buf, int32_t bufSize, uint32_t c) { return 0; }
    SR_MATH_NS::FVector2 DrawTexture(const void* pDescriptor, const SR_MATH_NS::FVector2& size, bool imposition) { return SR_MATH_NS::FVector2(0.0f, 0.0f); }
    SR_MATH_NS::FVector2 DrawImage(void* user_texture_id, const SR_MATH_NS::FVector2& size, const SR_MATH_NS::FVector2& uv0, const SR_MATH_NS::FVector2& uv1, const SR_MATH_NS::FColor& tint_col, const SR_MATH_NS::FColor& border_col, bool imposition) { return SR_MATH_NS::FVector2(0.0f, 0.0f); }
    bool BeginTabItem(const char* str_id) { return false; }
    void EndTabItem() { }
    bool BeginTabBar(const char* str_id) { return false; }
    void EndTabBar() { }
    void PushFont(void* pFont) { }
    void PopFont() { }
    void SetWindowFocus(const char* str_id) { }
    bool BeginChild(const char* str_id) { return false; }
    bool BeginChild(const char* str_id, const SR_MATH_NS::FVector2& size) { return false; }
    bool BeginChild(const char* str_id, const SR_MATH_NS::FVector2& size, bool border) { return false; }
    bool BeginChild(const char* str_id, const SR_MATH_NS::FVector2& size, bool border, WindowFlags flags) { return false; }
    void EndChild() { }
    const void* GetDragDropPayload() { return nullptr; }
    float_t GetScrollMaxY() { return 0.0f; }
    bool BeginDragDropTarget() { return false; }
    const void* AcceptDragDropPayload(const char* type) { return nullptr; }
    void EndDragDropTarget() { }
    void* GetDataFromDragDropPayload(const void* pPayload) { return nullptr; }
    const char* GetPayloadType(const void* pPayload) { return nullptr; }
    float_t GetFontSize() { return 0.f; }
    float_t GetScrollbarSize() { return 0.f; }
    void SetMousePos(const SR_MATH_NS::FVector2& pos) { }
    bool* GetMouseDown() { static bool mouseDown[5] = { false, false, false, false, false }; return mouseDown; }
    SR_MATH_NS::FVector2 GetMousePos() { return SR_MATH_NS::FVector2(); }
    SR_MATH_NS::FVector2 GetContentRegionAvail() { return SR_MATH_NS::FVector2(); }
    SR_MATH_NS::FVector2 GetFramePadding() { return SR_MATH_NS::FVector2(); }
    SR_MATH_NS::FVector2 GetItemRectSize() { return SR_MATH_NS::FVector2(); }
    SR_MATH_NS::FVector2 GetItemRectMin() { return SR_MATH_NS::FVector2(); }
    SR_MATH_NS::FVector2 CalcTextSize(const char* text) { return SR_MATH_NS::FVector2(); }
    void SetKeyboardFocusHere() { }
    void OpenPopup(const char* str_id) { }
    void AddText(void* pDrawList, const SR_MATH_NS::FVector2& pos, uint32_t color, const char* text) { }
    void CloseCurrentPopup() { }
    bool InputText(const char* label, std::string* str, InputTextFlags flags) { return false; }
    bool InputText(const char* label, char* str, size_t strSize, InputTextFlags flags) { return false; }
    bool InputTextMultiline(const char* label, std::string* str, const SR_MATH_NS::FVector2& size, InputTextFlags flags) { return false; }
    bool BeginMenu(const char* label) { return false; }
    bool MenuItem(const char* label) { return false; }
    void EndMenu() { }
    void BeginDocking() { }
    void EndDocking() { }
    bool BeginMainMenuBar() { return false; }
    bool IsItemToggledOpen() { return false; }
    bool IsItemDeactivatedAfterEdit() { return false; }
    bool IsWindowFocused() { return false; }
    void* GetCurrentContext() { return nullptr; }
    void TableNextRow() { }
    void EndMenuBar() { }
    void End() { }
    bool BeginListBox(const char* label, const SR_MATH_NS::FVector2& size) { return false; }
    void EndListBox() { }
    bool BeginTable(const char* str_id, int columns) { return false; }
    void EndTable() { }
    void TableSetColumnIndex(int column_n) { }
    bool IsMouseDragging(MouseButton button) { return false; }
    bool IsMouseDown(MouseButton button) { return false; }
    bool IsMouseReleased(MouseButton button) { return false; }
    bool IsItemClicked(MouseButton button) { return false; }
    bool IsMouseDoubleClicked(MouseButton button) { return false; }
    bool BeginPopupContextWindow(const char* str_id) { return false; }
    bool BeginPopupContextItem(const char* str_id) { return false; }
    bool TreeNodeEx(const void* ptr_id, TreeNodeFlags flags, const char* fmt, ...) { return false; }
    void* FindWindowByName(const char* name) { return nullptr; }
    void SetCursorPosX(float_t x) { }
    void SetCursorPosY(float_t y) { }
    SR_MATH_NS::FVector2 GetWindowSize() { return SR_MATH_NS::FVector2(); }
    SR_MATH_NS::FVector2 GetCursorPos() { return SR_MATH_NS::FVector2(); }
    SR_MATH_NS::FRect GetWindowRect(void* pWindow) { return SR_MATH_NS::FRect(); }
    bool SmallButton(const char* label) { return false; }
    void FocusTopMostWindowUnderOne() { }
    void SetCursorPos(const SR_MATH_NS::FVector2& pos) { }
    void LoadIniSettingsFromDisk() { }
    bool DragFloat(const char* label, float_t* v, float_t vSpeed, float_t min, float_t max, const char* format) { return false; }
    bool DragFloat2(const char* label, float_t v[2], float_t vSpeed, float_t min, float_t max, const char* format) { return false; }
    bool DragFloat3(const char* label, float_t v[3], float_t vSpeed, float_t min, float_t max, const char* format) { return false; }
    bool SliderFloat(const char* label, float_t* v, float_t min, float_t max, const char* format) { return false; }
    bool SliderInt(const char* label, int* v, int min, int max, const char* format) { return false; }
    float_t GetFramerate() { return 0.f; }
    float_t GetFrameHeightWithSpacing() { return 0.f; }
    ImmediateDataType GetDataType(std::string_view type) { return ImmediateDataType(); }
    ImmediateDataType GetDataType(uint64_t size, bool isSigned, bool isIntegral) { return ImmediateDataType(); }
    ImmediateDataTypeUnion ReadDataType(void* pData, ImmediateDataType type) { return ImmediateDataTypeUnion(); }
    ImmediateDataTypeUnion FloatToDataType(float_t value, ImmediateDataType type) { return ImmediateDataTypeUnion(); }
    void WriteDataType(void* pData, ImmediateDataType type, ImmediateDataTypeUnion value) { }
    void BeginVertical(const char* str_id, const SR_MATH_NS::FVector2& size, float align) { }
    void BeginVertical(const void* ptr_id, const SR_MATH_NS::FVector2& size, float align) { }
    void EndVertical() { }
    void BeginHorizontal(const char* str_id, const SR_MATH_NS::FVector2& size, float align) { }
    void BeginHorizontal(const void* ptr_id, const SR_MATH_NS::FVector2& size, float align) { }
    void EndHorizontal() { }
    void Spring(float weight, float spacing) { }
    void DrawPinIcon(const SR_MATH_NS::FVector2& size, SR_GRAPH_NS::GUI::IconType iconType, bool filled, const SR_MATH_NS::FColor& color, const SR_MATH_NS::FColor& innerColor) { }
    SR_MATH_NS::FVector2 GetItemRectMax() { return SR_MATH_NS::FVector2(0.0f, 0.0f); }
    void DrawListAddTriangleFilled(void* pDrawList, const SR_MATH_NS::FVector2& a, const SR_MATH_NS::FVector2& b, const SR_MATH_NS::FVector2& c, uint32_t color) { }
    bool IsItemVisible() { return false; }
    SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags GetNodeFlagsWithChild() { return SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnArrow | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::OpenOnDoubleClick; }
    SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags GetNodeFlagsWithoutChild() { return SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::NoTreePushOnOpen | SR_GRAPH_GUI_NS::Immediate::TreeNodeFlags::Leaf; }
    void ShowMetricsWindow(bool* pOpen = nullptr) { }

    bool BeginPlot(const char* title_id, const SR_MATH_NS::IVector2& size, PlotFlags flags) { return false; }
    void EndPlot() { }
#endif
}
