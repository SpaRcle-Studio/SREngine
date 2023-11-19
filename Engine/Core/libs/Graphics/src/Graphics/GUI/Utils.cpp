//
// Created by Monika on 15.07.2023.
//

#include <Graphics/GUI/Utils.h>

namespace SR_GRAPH_GUI_NS {
    bool RadioButton(const char* label, bool active, float_t radius)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        const float square_sz = ImGui::GetFrameHeight() * radius;
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
        const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), (label_size.y + style.FramePadding.y * 2.0f) / 1.75f));
        ImGui::ItemSize(total_bb, style.FramePadding.y / 1.75f);
        if (!ImGui::ItemAdd(total_bb, id))
            return false;

        ImVec2 center = check_bb.GetCenter();
        center.x = IM_ROUND(center.x);
        center.y = IM_ROUND(center.y);
        const float radiusInternal = (square_sz - 1.0f) * 0.5f;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
        if (pressed)
            ImGui::MarkItemEdited(id);

        ImGui::RenderNavHighlight(total_bb, id);
        window->DrawList->AddCircleFilled(center, radiusInternal, ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);
        if (active)
        {
            const float pad = ImMax(1.0f, IM_FLOOR(square_sz / 6.0f));
            window->DrawList->AddCircleFilled(center, radiusInternal - pad, ImGui::GetColorU32(ImGuiCol_CheckMark), 16);
        }

        if (style.FrameBorderSize > 0.0f)
        {
            window->DrawList->AddCircle(center + ImVec2(1, 1), radiusInternal, ImGui::GetColorU32(ImGuiCol_BorderShadow), 16, style.FrameBorderSize);
            window->DrawList->AddCircle(center, radiusInternal, ImGui::GetColorU32(ImGuiCol_Border), 16, style.FrameBorderSize);
        }

        ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);
         if (g.LogEnabled)
             ImGui::LogRenderedText(&label_pos, active ? "(x)" : "( )");
         if (label_size.x > 0.0f)
             ImGui::RenderText(label_pos, label);

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
        return pressed;
    }

    bool CheckboxNoNavFocus(const char *label, bool *v) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiID backupId = g.ActiveId;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        const float square_sz = ImGui::GetFrameHeight();
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id))
        {
            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
            return false;
        }

        bool hovered = false, held = false;
        bool pressed = ButtonBehaviorNoNavFocus(total_bb, id, &hovered, &held);
        if (pressed)
        {
            *v = !(*v);
            ImGui::MarkItemEdited(id);
        }

        const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
        ImGui::RenderNavHighlight(total_bb, id);
        ImGui::RenderFrame(check_bb.Min, check_bb.Max, ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), true, style.FrameRounding);
        ImU32 check_col = ImGui::GetColorU32(ImGuiCol_CheckMark);
        bool mixed_value = (g.LastItemData.InFlags & ImGuiItemFlags_MixedValue) != 0;
        if (mixed_value) {
            ImVec2 pad(ImMax(1.0f, IM_FLOOR(square_sz / 3.6f)), ImMax(1.0f, IM_FLOOR(square_sz / 3.6f)));
            window->DrawList->AddRectFilled(check_bb.Min + pad, check_bb.Max - pad, check_col, style.FrameRounding);
        }
        else if (*v)
        {
            const float pad = ImMax(1.0f, IM_FLOOR(square_sz / 6.0f));
            ImGui::RenderCheckMark(window->DrawList, check_bb.Min + ImVec2(pad, pad), check_col, square_sz - pad * 2.0f);
        }

        ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);
        if (g.LogEnabled)
            ImGui::LogRenderedText(&label_pos, mixed_value ? "[~]" : *v ? "[x]" : "[ ]");
        if (label_size.x > 0.0f)
            ImGui::RenderText(label_pos, label);

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));

        ImGui::SetActiveID(backupId, window);

        return pressed;
    }

    bool ButtonBehaviorNoNavFocus(const ImRect &bb, ImGuiID id, bool *out_hovered, bool *out_held, ImGuiButtonFlags flags) {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = ImGui::GetCurrentWindow();

        // Default only reacts to left mouse button
        if ((flags & ImGuiButtonFlags_MouseButtonMask_) == 0)
            flags |= ImGuiButtonFlags_MouseButtonDefault_;

        // Default behavior requires click + release inside bounding box
        if ((flags & ImGuiButtonFlags_PressedOnMask_) == 0)
            flags |= ImGuiButtonFlags_PressedOnDefault_;

        ImGuiWindow* backup_hovered_window = g.HoveredWindow;
        const bool flatten_hovered_children = (flags & ImGuiButtonFlags_FlattenChildren) && g.HoveredWindow && g.HoveredWindow->RootWindowDockTree == window->RootWindowDockTree;
        if (flatten_hovered_children)
            g.HoveredWindow = window;

        bool pressed = false;
        bool hovered = ImGui::ItemHoverable(bb, id);

        // Drag source doesn't report as hovered
        if (hovered && g.DragDropActive && g.DragDropPayload.SourceId == id && !(g.DragDropSourceFlags & ImGuiDragDropFlags_SourceNoDisableHover))
            hovered = false;

        if (flatten_hovered_children)
            g.HoveredWindow = backup_hovered_window;

        // AllowOverlap mode (rarely used) requires previous frame HoveredId to be null or to match. This allows using patterns where a later submitted widget overlaps a previous one.
        if (hovered && (flags & ImGuiButtonFlags_AllowItemOverlap) && (g.HoveredIdPreviousFrame != id && g.HoveredIdPreviousFrame != 0))
            hovered = false;

        // Mouse handling
        if (hovered)
        {
            if (!(flags & ImGuiButtonFlags_NoKeyModifiers) || (!g.IO.KeyCtrl && !g.IO.KeyShift && !g.IO.KeyAlt))
            {
                // Poll buttons
                int mouse_button_clicked = -1;
                if ((flags & ImGuiButtonFlags_MouseButtonLeft) && g.IO.MouseClicked[0])         { mouse_button_clicked = 0; }
                else if ((flags & ImGuiButtonFlags_MouseButtonRight) && g.IO.MouseClicked[1])   { mouse_button_clicked = 1; }
                else if ((flags & ImGuiButtonFlags_MouseButtonMiddle) && g.IO.MouseClicked[2])  { mouse_button_clicked = 2; }

                if (mouse_button_clicked != -1 && g.ActiveId != id)
                {
                    if (flags & (ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnClickReleaseAnywhere))
                    {
                        ImGui::SetActiveID(id, window);
                        g.ActiveIdMouseButton = mouse_button_clicked;
                        //if (!(flags & ImGuiButtonFlags_NoNavFocus))
                        //    SetFocusID(id, window);
                        //FocusWindow(window);
                    }
                    if ((flags & ImGuiButtonFlags_PressedOnClick) || ((flags & ImGuiButtonFlags_PressedOnDoubleClick) && g.IO.MouseClickedCount[mouse_button_clicked] == 2))
                    {
                        pressed = true;
                        if (flags & ImGuiButtonFlags_NoHoldingActiveId)
                            ImGui::ClearActiveID();
                        else
                            ImGui::SetActiveID(id, window); // Hold on ID
                        //if (!(flags & ImGuiButtonFlags_NoNavFocus))
                        //    SetFocusID(id, window);
                        g.ActiveIdMouseButton = mouse_button_clicked;
                        //FocusWindow(window);
                    }
                }
                if (flags & ImGuiButtonFlags_PressedOnRelease)
                {
                    int mouse_button_released = -1;
                    if ((flags & ImGuiButtonFlags_MouseButtonLeft) && g.IO.MouseReleased[0])        { mouse_button_released = 0; }
                    else if ((flags & ImGuiButtonFlags_MouseButtonRight) && g.IO.MouseReleased[1])  { mouse_button_released = 1; }
                    else if ((flags & ImGuiButtonFlags_MouseButtonMiddle) && g.IO.MouseReleased[2]) { mouse_button_released = 2; }
                    if (mouse_button_released != -1)
                    {
                        const bool has_repeated_at_least_once = (flags & ImGuiButtonFlags_Repeat) && g.IO.MouseDownDurationPrev[mouse_button_released] >= g.IO.KeyRepeatDelay; // Repeat mode trumps on release behavior
                        if (!has_repeated_at_least_once)
                            pressed = true;
                        //if (!(flags & ImGuiButtonFlags_NoNavFocus))
                        //    SetFocusID(id, window);
                        ImGui::ClearActiveID();
                    }
                }

                // 'Repeat' mode acts when held regardless of _PressedOn flags (see table above).
                // Relies on repeat logic of IsMouseClicked() but we may as well do it ourselves if we end up exposing finer RepeatDelay/RepeatRate settings.
                if (g.ActiveId == id && (flags & ImGuiButtonFlags_Repeat))
                    if (g.IO.MouseDownDuration[g.ActiveIdMouseButton] > 0.0f && ImGui::IsMouseClicked(g.ActiveIdMouseButton, true))
                        pressed = true;
            }

            if (pressed)
                g.NavDisableHighlight = true;
        }

        // Gamepad/Keyboard navigation
        // We report navigated item as hovered but we don't set g.HoveredId to not interfere with mouse.
        if (g.NavId == id && !g.NavDisableHighlight && g.NavDisableMouseHover && (g.ActiveId == 0 || g.ActiveId == id || g.ActiveId == window->MoveId))
            if (!(flags & ImGuiButtonFlags_NoHoveredOnFocus))
                hovered = true;
        if (g.NavActivateDownId == id)
        {
            bool nav_activated_by_code = (g.NavActivateId == id);
            bool nav_activated_by_inputs = (g.NavActivatePressedId == id);
            if (!nav_activated_by_inputs && (flags & ImGuiButtonFlags_Repeat))
            {
                // Avoid pressing both keys from triggering double amount of repeat events
                const ImGuiKeyData* key1 = ImGui::GetKeyData(ImGuiKey_Space);
                const ImGuiKeyData* key2 = ImGui::GetKeyData(ImGuiKey_NavGamepadActivate);
                const float t1 = ImMax(key1->DownDuration, key2->DownDuration);
                nav_activated_by_inputs = ImGui::CalcTypematicRepeatAmount(t1 - g.IO.DeltaTime, t1, g.IO.KeyRepeatDelay, g.IO.KeyRepeatRate) > 0;
            }
            if (nav_activated_by_code || nav_activated_by_inputs)
            {
                // Set active id so it can be queried by user via IsItemActive(), equivalent of holding the mouse button.
                pressed = true;
                ImGui::SetActiveID(id, window);
                g.ActiveIdSource = ImGuiInputSource_Nav;
                //if (!(flags & ImGuiButtonFlags_NoNavFocus))
                //    SetFocusID(id, window);
            }
        }

        // Process while held
        bool held = false;
        if (g.ActiveId == id)
        {
            if (g.ActiveIdSource == ImGuiInputSource_Mouse)
            {
                if (g.ActiveIdIsJustActivated)
                    g.ActiveIdClickOffset = g.IO.MousePos - bb.Min;

                const int mouse_button = g.ActiveIdMouseButton;
                IM_ASSERT(mouse_button >= 0 && mouse_button < ImGuiMouseButton_COUNT);
                if (g.IO.MouseDown[mouse_button])
                {
                    held = true;
                }

                bool release_in = hovered && (flags & ImGuiButtonFlags_PressedOnClickRelease) != 0;
                bool release_anywhere = (flags & ImGuiButtonFlags_PressedOnClickReleaseAnywhere) != 0;
                if ((release_in || release_anywhere) && !g.DragDropActive)
                {
                    // Report as pressed when releasing the mouse (this is the most common path)
                    bool is_double_click_release = (flags & ImGuiButtonFlags_PressedOnDoubleClick) && g.IO.MouseReleased[mouse_button] && g.IO.MouseClickedLastCount[mouse_button] == 2;
                    bool is_repeating_already = (flags & ImGuiButtonFlags_Repeat) && g.IO.MouseDownDurationPrev[mouse_button] >= g.IO.KeyRepeatDelay; // Repeat mode trumps <on release>
                    if (!is_double_click_release && !is_repeating_already)
                        pressed = true;
                }
                ImGui::ClearActiveID();

                if (!(flags & ImGuiButtonFlags_NoNavFocus))
                    g.NavDisableHighlight = true;
            }
            else if (g.ActiveIdSource == ImGuiInputSource_Nav)
            {
                // When activated using Nav, we hold on the ActiveID until activation button is released
                if (g.NavActivateDownId != id)
                    ImGui::ClearActiveID();
            }
            if (pressed)
                g.ActiveIdHasBeenPressedBefore = true;
        }

        if (out_hovered) *out_hovered = hovered;
        if (out_held) *out_held = held;

        return pressed;
    }

    bool DrawDataType(SR_SRLM_NS::DataType* pData, bool* pIsEnum, void* pProvider, float_t width, uint32_t deep) {
        if (pIsEnum) {
            *pIsEnum = false;
        }

        switch (pData->GetClass()) {
            case SR_SRLM_NS::DataTypeClass::Struct:
                if (!pProvider) {
                    break;
                }

                if (auto&& pStruct = dynamic_cast<SR_SRLM_NS::DataTypeStruct*>(pData)) {
                    if (SR_SRLM_NS::DataTypeManager::Instance().IsStructExists(pStruct->GetHashName())) {
                        ImGui::Text("%s", SR_HASH_TO_STR(pStruct->GetHashName()).c_str());

                        for (auto&& [hashName, pVar] : pStruct->GetVariables()) {
                            ImGui::BeginDisabled(true);
                            ImGui::Button(SR_HASH_TO_STR(hashName).c_str(), ImVec2(width * 0.25f, 20));
                            ImGui::EndDisabled();

                            ImGui::SameLine();

                            DrawDataType(pVar, pIsEnum, pProvider, width, deep + 1);

                            ImGui::Separator();
                        }
                    }
                }
                break;
            case SR_SRLM_NS::DataTypeClass::Bool:
                CheckboxNoNavFocus(SR_FORMAT_C("##Pin-{}", pProvider), pData->GetBool());
                break;
            case SR_SRLM_NS::DataTypeClass::Enum: {
                auto&& pEnum = dynamic_cast<SR_SRLM_NS::DataTypeEnum*>(pData);
                if (!pEnum) {
                    break;
                }

                auto&& pReflector = pEnum->GetReflector();

                if (!pIsEnum) {
                    ImGui::PushItemWidth(width > 0.f ? width : 80.0f);
                    SR_GRAPH_GUI_NS::EnumCombo(SR_FORMAT_C("Enum##PinE-{}", pProvider), pReflector, [pEnum](auto&& pNewReflector) {
                        pEnum->SetReflector(pNewReflector);
                        pEnum->SetValue(0);
                    });
                    ImGui::PopItemWidth();
                }

                if (!pReflector) {
                    break;
                }

                auto&& enumValue = pReflector->ToStringInternal(*pEnum->GetEnum());

                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);

                if (pIsEnum) {
                    if (ImGui::Button(enumValue.has_value() ? enumValue.value().ToCStr() : "Unknown", ImVec2(80, 20))) {
                        *pIsEnum = true;
                    }

                    ImGui::PopStyleVar();

                    ImGui::Text("%s", pReflector->GetNameInternal().ToCStr());
                }
                else {
                    ImGui::PushItemWidth(width > 0.f ? width : 80.0f);
                    SR_GRAPH_GUI_NS::EnumCombo(SR_FORMAT_C("##PinE-{}", pProvider), pReflector, enumValue, [pEnum, pReflector](auto&& value) {
                        if (auto&& integral = pReflector->FromStringInternal(value)) {
                            pEnum->SetValue(integral.value());
                        }
                    });
                    ImGui::PopItemWidth();
                    ImGui::PopStyleVar();
                }

                break;
            }
            case SR_SRLM_NS::DataTypeClass::Int8:
            case SR_SRLM_NS::DataTypeClass::Int16:
            case SR_SRLM_NS::DataTypeClass::Int32:
            case SR_SRLM_NS::DataTypeClass::Int64:
            case SR_SRLM_NS::DataTypeClass::UInt8:
            case SR_SRLM_NS::DataTypeClass::UInt16:
            case SR_SRLM_NS::DataTypeClass::UInt32:
            case SR_SRLM_NS::DataTypeClass::UInt64: {
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
                int32_t number = *pData->GetInt32();
                ImGui::PushItemWidth(width > 0.f ? width : 40.0f);
                if (ImGui::InputInt(SR_FORMAT_C("##Pin-{}", pProvider), &number, 0)) {
                    *pData->GetInt32() = number;
                }
                ImGui::PopItemWidth();
                ImGui::PopStyleVar();
                break;
            }
            case SR_SRLM_NS::DataTypeClass::Float:
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
                ImGui::PushItemWidth(width > 0.f ? width : 40.0f);
                ImGui::InputFloat(SR_FORMAT_C("##Pin-{}", pProvider), pData->GetFloat());
                ImGui::PopItemWidth();
                ImGui::PopStyleVar();
                break;
            case SR_SRLM_NS::DataTypeClass::String:
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
                ImGui::PushItemWidth(width > 0.f ? width : 80.0f);
                ImGui::InputText(SR_FORMAT_C("##Pin-{}", pProvider), pData->GetString());
                ImGui::PopStyleVar();
                break;
            default:
                break;
        }

        return true;
    }
}