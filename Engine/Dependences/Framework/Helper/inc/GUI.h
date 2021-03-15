//
// Created by Nikita on 15.03.2021.
//

#ifndef GAMEENGINE_GUI_H
#define GAMEENGINE_GUI_H

#include <imgui.h>
#include <string>

namespace Framework::Helper::GUI {
    inline static void DrawTextOnCenter(const std::string& text, bool sameLine = true) {
        float font_size = ImGui::GetFontSize() * text.size() / 2;

        if (sameLine)
            ImGui::SameLine(
                    ImGui::GetWindowSize().x / 2 -
                    font_size + (font_size / 2)
            );

        ImGui::Text("%s", text.c_str());
    }
}

#endif //GAMEENGINE_GUI_H
