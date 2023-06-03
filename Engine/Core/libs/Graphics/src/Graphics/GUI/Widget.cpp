//
// Created by Monika on 14.02.2022.
//

#include <Graphics/GUI/Widget.h>

namespace Framework::Graphics::GUI {
    void Widget::DrawAsSubWindow() {
        m_widgetFlags = WIDGET_FLAG_NONE;

        if (m_center) {
            ImGuiIO& io = ImGui::GetIO();
            ImVec2 pos(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
            ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        }

        WindowFlags flags = m_windowFlags;

        if (IsFocused() || IsHovered()) {
            ImVec4 color = ImGui::GetStyleColorVec4(ImGuiCol_::ImGuiCol_WindowBg);
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_WindowBg, color + ImVec4(0.02, 0.02, 0.02, 0));
        }

        auto&& size = m_size.Contains(SR_INT32_MAX) ? ImVec2(0, 0) : ImVec2(m_size.x, m_size.y);
        if (ImGui::BeginChild(m_name.c_str(), size, false, flags)) {
            Draw();
        }

        if (IsFocused() || IsHovered())
            ImGui::PopStyleColor();

        InternalCheckFocused();
        InternalCheckHovered();

        ImGui::EndChild();
    }

    void Widget::DrawWindow()  {
        m_widgetFlags = WIDGET_FLAG_NONE;

        if (m_center) {
            ImGuiIO& io = ImGui::GetIO();
            ImVec2 pos(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
            ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        }

        WindowFlags flags = m_windowFlags;

        if (IsFocused() || IsHovered()) {
            ImVec4 color = ImGui::GetStyleColorVec4(ImGuiCol_::ImGuiCol_WindowBg);
            ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_WindowBg, color + ImVec4(0.02, 0.02, 0.02, 0));
        }

        if (!m_size.Contains(SR_INT32_MAX)) {
            ImGui::SetNextWindowSize(ImVec2(m_size.x, m_size.y));
            flags |= ImGuiWindowFlags_::ImGuiWindowFlags_NoResize;
        }

        auto&& pPreviousViewport = ImGui::GetWindowViewport();

        bool open = m_open;
        if (ImGui::Begin(m_name.c_str(), &open, flags)) {
            auto&& pCurrentViewport = ImGui::GetWindowViewport();

            if (pPreviousViewport != pCurrentViewport) {
                ViewportsTableManager::Instance().RegisterWidget(this, pCurrentViewport);
            }

            if (!open) {
                Close();
            }
            else
                Draw();
        }

        if (IsFocused() || IsHovered())
            ImGui::PopStyleColor();

        InternalCheckFocused();
        InternalCheckHovered();

        ImGui::End();
    }

    void Widget::TextCenter(const std::string &text) const {
        float font_size = ImGui::GetFontSize() * text.size() / 2;

        ImGui::SameLine(
                ImGui::GetWindowSize().x / 2 -
                font_size + (font_size / 2)
        );

        ImGui::Text("%s", text.c_str());
    }

    void Widget::Open()  {
        if (!m_open)
            OnOpen();

        m_open = true;
    }

    void Widget::Close() {
        if (m_open)
            OnClose();

        m_open = false;
    }

    void Widget::InternalCheckFocused() {
        if (ImGui::IsWindowFocused() || m_widgetFlags & WIDGET_FLAG_FOCUSED) {
            m_internalFlags |= WIDGET_FLAG_FOCUSED;
        }
        else if (IsFocused()) {
            m_internalFlags ^= WIDGET_FLAG_FOCUSED;
        }
    }

    void Widget::InternalCheckHovered() {
        if (ImGui::IsWindowHovered() || m_widgetFlags & WIDGET_FLAG_HOVERED) {
            m_internalFlags |= WIDGET_FLAG_HOVERED;
        }
        else if (IsHovered()) {
            m_internalFlags ^= WIDGET_FLAG_HOVERED;
        }
    }

    void Widget::CheckFocused() {
        m_widgetFlags |= ImGui::IsWindowFocused() ? WIDGET_FLAG_FOCUSED : WIDGET_FLAG_NONE;
    }

    void Widget::CheckHovered() {
        m_widgetFlags |= ImGui::IsWindowHovered() ? WIDGET_FLAG_HOVERED : WIDGET_FLAG_NONE;
    }

    void Widget::SetManager(WidgetManager* manager) {
        m_manager = manager;
    }

    Widget::RenderScenePtr Widget::GetRenderScene() const {
        return m_manager->GetRenderScene();
    }

    Widget::ContextPtr Widget::GetContext() const {
        return m_manager->GetContext();
    }

    void Widget::ResetWeakStorage() {
        m_weakStorage.Clear();
    }

    void Widget::ResetStrongStorage() {
        m_strongStorage.Clear();
    }
}