//
// Created by Monika on 12.09.2023.
//

#include <Graphics/GUI/ImGUI.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GRAPH_GUI_NS {
#ifdef SR_USE_IMGUI
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

    bool CollapsingHeader(const std::string& label, ImGuiTreeNodeFlags flags) {
        ImGuiWindow* pWindow = ImGui::GetCurrentWindow();
        if (pWindow->SkipItems) {
            return false;
        }

        ImGuiID id = pWindow->GetID(label.c_str());
        flags |= ImGuiTreeNodeFlags_CollapsingHeader;
        flags |= ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_ClipLabelForTrailingButton;

        return ImGui::TreeNodeBehavior(id, flags, label.c_str());
    }

    bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding, ImGuiButtonFlags flags) {
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

        const bool result = ImageButtonInternal(imageId.data(), pDescriptor, size, framePadding, flags);

        ImGui::PopStyleColor();

        return result;
    }

    bool ImageButtonInternal(std::string_view &&imageId, void* pDescriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding, ImGuiButtonFlags flags) {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        if (window->SkipItems)
            return false;

        ImVec4 bg_col = ImVec4(0,0,0,0);
        ImVec4 tint_col = ImVec4(1,1,1,1);
        ImVec2 uv0, uv1;

        /// if (m_pipeLine == Graphics::PipelineType::OpenGL) {
        ///     uv0 = ImVec2(0, 1);
        ///     uv1 = ImVec2(1, 0);
        /// }
        /// else {
        uv0 = ImVec2(-1, 0);
        uv1 = ImVec2(0, 1);
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
        ImGui::RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, g.Style.FrameRounding));
        if (bg_col.w > 0.0f)
            window->DrawList->AddRectFilled(bb.Min + padding, bb.Max - padding, ImGui::GetColorU32(bg_col));
        window->DrawList->AddImage((ImTextureID)pDescriptor, bb.Min + padding, bb.Max - padding, uv0, uv1, ImGui::GetColorU32(tint_col));

        return pressed;
    }

    ImVec2 DrawTexture(void* pDescriptor, const SR_MATH_NS::IVector2& size, SR_GRAPH_NS::PipelineType pipelineType, bool imposition) {
        if (!pDescriptor) {
            return ImVec2(); /// NOLINT
        }

        auto&& fSize = size.Cast<float_t>();

        switch (pipelineType) {
            case PipelineType::Vulkan:
                return DrawImage(pDescriptor, ImVec2(fSize.x, fSize.y), ImVec2(-1, 0), ImVec2(0, 1), { 1, 1, 1, 1 }, { 0, 0, 0, 0 }, imposition);
            case PipelineType::OpenGL:
                return DrawImage(pDescriptor, ImVec2(fSize.x, fSize.y), ImVec2(0, 1), ImVec2(1, 0), { 1, 1, 1, 1 }, { 0, 0, 0, 0 }, imposition);
            default:
                return ImVec2(); /// NOLINT
        }
    }

    ImVec2 DrawImage(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col, bool imposition) {
        ImGuiWindow* pWindow = ImGui::GetCurrentWindow();
        if (pWindow->SkipItems) {
            return ImVec2(); /// NOLINT
        }

        ImRect bb(pWindow->DC.CursorPos, pWindow->DC.CursorPos + size);
        if (border_col.w > 0.0f) {
            bb.Max = bb.Max + ImVec2(2, 2);
        }

        if (!imposition) {
            ImGui::ItemSize(bb);
            if (!ImGui::ItemAdd(bb, 0)) {
                return ImVec2(); /// NOLINT
            }
        }

        if (border_col.w > 0.0f) {
            pWindow->DrawList->AddRect(bb.Min, bb.Max, ImGui::GetColorU32(border_col), 0.0f);
            pWindow->DrawList->AddImage(user_texture_id, bb.Min + ImVec2(1, 1), bb.Max - ImVec2(1, 1), uv0, uv1, ImGui::GetColorU32(tint_col));
        }
        else {
            pWindow->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, ImGui::GetColorU32(tint_col));
        }

        return bb.GetTL();
    }

    bool BeginDragDropTargetWindow(const std::string& payloadType) {
        ImRect inner_rect = ImGui::GetCurrentWindow()->InnerRect;

        if (ImGui::BeginDragDropTargetCustom(inner_rect, ImGui::GetID("##WindowBgArea")))
        {
            auto&& pPayload = ImGui::AcceptDragDropPayload(payloadType.c_str(), ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect);
            if (pPayload) {
                if (pPayload->IsPreview()) {
                    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
                    draw_list->AddRectFilled(inner_rect.Min, inner_rect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget, 0.05f));
                    draw_list->AddRect(inner_rect.Min, inner_rect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget), 0.0f, 0, 2.0f);
                }

                if (pPayload->IsDelivery()) {
                    return true;
                }

                ImGui::EndDragDropTarget();
            }
        }

        return false;
    }

    bool ImageButton(void* pDescriptor, const SR_MATH_NS::IVector2& size) {
        return ImageButton(pDescriptor, size, -1);
    }

    bool ImageButton(void* pDescriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding) {
        return ImageButton("##image", pDescriptor, size, framePadding);
    }

    bool ImageButtonDouble(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding) {
        return ImageButton(imageId.data(), pDescriptor, size, framePadding, ImGuiButtonFlags_PressedOnDoubleClick);
    }

    bool ImageButton(std::string_view&& imageId, void* pDescriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding) {
        return ImageButton(imageId.data(), pDescriptor, size, framePadding, ImGuiButtonFlags_None);
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

    bool IsVec4Null(const ImVec4& v1) {
        return (v1.x == 0) && (v1.y == 0) && (v1.z == 0) && (v1.w == 0);
    }

    bool IsVec2Null(const ImVec2& v1) {
        return (v1.x == 0) && (v1.y == 0);
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

    ImVec2 DrawTexture(SR_GRAPH_NS::Pipeline* pPipeline, uint32_t textureId, const SR_MATH_NS::IVector2 &size, bool imposition) {
        void* pDescriptor = nullptr;

        switch (pPipeline->GetType()) {
            case SR_GRAPH_NS::PipelineType::Vulkan:
                pDescriptor = pPipeline->GetOverlayTextureDescriptorSet(textureId, SR_GRAPH_NS::OverlayType::ImGui);
                break;
            case SR_GRAPH_NS::PipelineType::OpenGL:
                pDescriptor = reinterpret_cast<void*>(static_cast<uint64_t>(textureId));
                break;
            default:
                break;
        }

        return SR_GRAPH_GUI_NS::DrawTexture(pDescriptor, size, pPipeline->GetType(), false);
    }
#endif
}