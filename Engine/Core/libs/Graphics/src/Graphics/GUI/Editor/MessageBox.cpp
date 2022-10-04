//
// Created by Monika on 10.02.2022.
//

#include <Graphics/GUI/Editor/MessageBox.h>
#include <Graphics/GUI/WidgetManager.h>

namespace SR_GRAPH_NS::GUI {
    MessageBoxWidget::MessageBoxWidget()
        : Widget("MessageBox")
    {
        GlobalWidgetManager::Instance().Register(this);

        SetCenter(true);
        SetFlags(ImGuiWindowFlags_NoMove
                 | ImGuiWindowFlags_NoDecoration
                 | ImGuiWindowFlags_AlwaysAutoResize
                 | ImGuiWindowFlags_NoSavedSettings);
    }

    MessageBoxWidget::~MessageBoxWidget() {
        GlobalWidgetManager::Instance().Remove(this);
    }

    void MessageBoxWidget::Draw() {
        SR_LOCK_GUARD_INHERIT(Widget)

        ImGui::TextColored(ImColor(255, 255, 0), "%s", m_header.c_str());

        ImGui::Spacing();
        ImGui::NextColumn();

        ImGui::Columns(1);
        ImGui::Separator();

        ImGui::Text("%s", m_message.c_str());

        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();

        if (ImGui::Button("Ok", ImVec2(50, 0))) {
            Close();
        }

        ImGui::SameLine(200);

        if (ImGui::Button("Close", ImVec2(50, 0))) {
            Close();
        }
    }

    void MessageBoxWidget::Show(const std::string& header, const std::string& message, MessageBoxType type, MessageBoxButton buttons) {
        SR_LOCK_GUARD_INHERIT(Widget)

        m_header = header;
        m_message = message;
        m_type = type;
        m_buttons = buttons;

        Open();
    }
}