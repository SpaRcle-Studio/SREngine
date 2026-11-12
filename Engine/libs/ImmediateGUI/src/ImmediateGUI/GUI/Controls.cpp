//
// Created by OpenAI Codex on 12.11.2026.
//

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#ifdef SR_USE_IMGUI
    #include <ImmediateGUI/Impl/ImGUI.h>
#endif

namespace SR_IMMEDIATE_GUI_NS {
    void SetCurrentContext(void* context) {
    #ifdef SR_USE_IMGUI
        ImGui::SetCurrentContext(static_cast<ImGuiContext*>(context));
    #endif
    }

    bool IsScrolledToBottom() {
    #ifdef SR_USE_IMGUI
        return ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 1.f;
    #else
        return true;
    #endif
    }

    void CopyTextToClipboard(const char* text) {
    #ifdef SR_USE_IMGUI
        ImGui::SetClipboardText(text);
    #endif
    }

    void ScrollToBottom() {
    #ifdef SR_USE_IMGUI
        ImGui::SetScrollHereY(1.f);
    #endif
    }
#ifdef SR_USE_IMGUI
    void BeginDisabled(bool disabled) {
        ImGui::BeginDisabled(disabled);
    }

    void EndDisabled() {
        ImGui::EndDisabled();
    }

    void ProgressBar(float_t fraction, const SR_MATH_NS::FVector2& size, const char* overlay) {
        const float_t value = fraction < 0.f ? -static_cast<float_t>(ImGui::GetTime()) : fraction;
        ImGui::ProgressBar(value, ImVec2(size.x, size.y), overlay);
    }

    void AlignTextToFramePadding() {
        ImGui::AlignTextToFramePadding();
    }
#else
    void BeginDisabled(bool disabled) {
    }

    void EndDisabled() {
    }

    void ProgressBar(float_t fraction, const SR_MATH_NS::FVector2& size, const char* overlay) {
    }

    void AlignTextToFramePadding() {
    }
#endif
}
