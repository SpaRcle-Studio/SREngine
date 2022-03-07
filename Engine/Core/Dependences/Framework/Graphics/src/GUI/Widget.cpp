//
// Created by Monika on 14.02.2022.
//

#include <GUI/Widget.h>

namespace Framework::Graphics::GUI {
    void Widget::DrawWindow()  {
        if (m_center) {
            ImGuiIO& io = ImGui::GetIO();
            ImVec2 pos(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
            ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        }

        WindowFlags flags = m_flags;

        if (!m_size.Contains(SR_INT32_MAX)) {
            ImGui::SetNextWindowSize(ImVec2(m_size.x, m_size.y));
            flags |= ImGuiWindowFlags_::ImGuiWindowFlags_NoResize;
        }

        bool open = m_open;
        if (ImGui::Begin(m_name.c_str(), &open, flags)) {
            m_focused = ImGui::IsWindowFocused();

            if (!open) {
                Close();
            }
            else
                Draw();

            ImGui::End();
        }
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
}