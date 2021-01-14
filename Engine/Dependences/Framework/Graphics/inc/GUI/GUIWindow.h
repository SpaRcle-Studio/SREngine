//
// Created by Nikita on 14.01.2021.
//

#ifndef GAMEENGINE_GUIWINDOW_H
#define GAMEENGINE_GUIWINDOW_H

#include <Debug.h>
#include <imgui.h>
#include <imgui_internal.h>

namespace Framework::Graphics::GUI {
    class GUIWindow {
    public:
        GUIWindow() = delete;
        ~GUIWindow() = delete;
    public:
        static inline void Begin(const std::string& winName) noexcept {
            ImGui::Begin(winName.c_str());
        }
        static inline void BeginChild(const std::string& winName) noexcept {
            ImGui::BeginChild(winName.c_str());
        }

        static inline void End() noexcept {
            ImGui::End();
        }
        static inline void EndChild() noexcept {
            ImGui::EndChild();
        }
    };
}

#endif //GAMEENGINE_GUIWINDOW_H
