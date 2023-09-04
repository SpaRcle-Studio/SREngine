//
// Created by Nikita on 15.03.2021.
//

#ifndef GAMEENGINE_GUI_H
#define GAMEENGINE_GUI_H

#include <Utils/Debug.h>

#ifdef SR_USE_IMGUI
    //#define IMGUI_DISABLE

    #define IMGUI_UNLIMITED_FRAME_RATE
    #define IMGUI_DEFINE_MATH_OPERATORS
    #define IMGUI_USE_WCHAR32

    #ifndef IM_ASSERT
        #define IM_ASSERT(_EXP) SRAssert1Once(_EXP)
    #endif

    #ifndef IM_ASSERT_USER_ERROR
        #define IM_ASSERT_USER_ERROR(_EXP, _MSG) SRAssert2Once(_EXP, _MSG)
    #endif

    #include <imgui.h>
        #include <misc/cpp/imgui_stdlib.h>
    #include <imgui_internal.h>

    #ifdef SR_WIN32
        #include <backends/imgui_impl_win32.h>
    #endif

    #ifdef SR_USE_VULKAN
        #include <backends/imgui_impl_vulkan.h>

        #ifdef min
            #undef min
        #endif

        #ifdef max
            #undef max
        #endif
    #endif

    #ifdef SR_USE_OPENGL
        #define GL_GLEXT_PROTOTYPES
        //#include <GL/glew.h>
        //#include <GL/wglew.h>
        #include <backends/imgui_impl_opengl3.h>
        #include <backends/imgui_impl_opengl3_loader.h>

        //#include <GL/gl3w.h>
    #endif

    #ifdef SR_USE_GLFW3
        #include <backends/imgui_impl_glfw.h>
    #endif

    #include <ImGuizmo.h>
#endif

namespace SR_UTILS_NS::GUI {
    inline static void DrawTextOnCenter(const std::string& text, bool sameLine = true) {
        const auto font_size = ImGui::GetFontSize() * text.size() / 2;

        if (sameLine) {
            ImGui::SameLine(
                    ImGui::GetWindowSize().x / 2 -
                    font_size + (font_size / 2)
            );
        }

        ImGui::Text("%s", text.c_str());
    }

    inline static void DrawMultiLineTextOnCenter(const std::string& text) {
        float win_width = ImGui::GetWindowSize().x;
        float text_width = ImGui::CalcTextSize(text.c_str()).x;

        // calculate the indentation that centers the text on one line, relative
        // to window left, regardless of the `ImGuiStyleVar_WindowPadding` value
        float text_indentation = (win_width - text_width) * 0.5f;

        // if text is too long to be drawn on one line, `text_indentation` can
        // become too small or even negative, so we check a minimum indentation
        float min_indentation = 20.0f;
        if (text_indentation <= min_indentation) {
            text_indentation = min_indentation;
        }

        ImGui::SameLine(text_indentation);
        ImGui::PushTextWrapPos(win_width - text_indentation);
        ImGui::TextWrapped("%s", text.c_str());
        ImGui::PopTextWrapPos();
    }

    inline static void DrawMultiLineTextOnCenter(const std::string& text, ImVec4 color) {
        float win_width = ImGui::GetWindowSize().x;
        float text_width = ImGui::CalcTextSize(text.c_str()).x;

        // calculate the indentation that centers the text on one line, relative
        // to window left, regardless of the `ImGuiStyleVar_WindowPadding` value
        float text_indentation = (win_width - text_width) * 0.5f;

        // if text is too long to be drawn on one line, `text_indentation` can
        // become too small or even negative, so we check a minimum indentation
        float min_indentation = 20.0f;
        if (text_indentation <= min_indentation) {
            text_indentation = min_indentation;
        }

        ImGui::SameLine(text_indentation);

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::PushTextWrapPos(win_width - text_indentation);

        ImGui::TextWrapped("%s", text.c_str());

        ImGui::PopTextWrapPos();
        ImGui::PopStyleColor();
    }

    inline static void DrawTextOnCenter(const std::string& text, ImVec4 color) {
        const auto font_size = ImGui::GetFontSize() * text.size() / 2;

        ImGui::SameLine(
                ImGui::GetWindowSize().x / 2 -
                font_size + (font_size / 2)
        );

        ImGui::TextColored(color, "%s", text.c_str());
    }
}

#endif //GAMEENGINE_GUI_H
