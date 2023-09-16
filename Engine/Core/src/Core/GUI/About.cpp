//
// Created by Igor on 12/03/2023.
//

#include <Core/GUI/About.h>

namespace Framework::Core::GUI {
    About::About()
            : Graphics::GUI::Widget("About") {}

    void About::Draw() {
        if (ImGui::BeginTabBar("About")) {

            ImGui::Text("SpaRcle Engine v0.0.5");
            ImGui::Separator();
            ImGui::Text("Author: ");
            ImGui::Text("   Monika0000");
            ImGui::Separator();
            ImGui::Text("Previous contributors: ");
            ImGui::Text( "innerviewer, Drakeme, Danilka");
            ImGui::Separator();
            ImGui::Text("Made thanks to the following libraries: ");
            ImGui::TextWrapped("glm, OpenGL, GLFW, GLEW, glad, Bullet3, PhysX, Box2D, Dear ImGui, ImGuizmo, tinyobjloader, imgui-node-editor, stbi, json, Assimp");
            ImGui::Separator();
            ImGui::Text("Build Version: 0.0.5");
            ImGui::Text("Build Date: ??.??.2023");
            ImGui::Text("Licensed under the MIT License");

            ImGui::EndTabBar();
        }
    }
}