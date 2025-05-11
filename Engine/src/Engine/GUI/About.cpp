//
// Created by Igor on 12/03/2023.
//

#include <Engine/GUI/About.h>

#ifdef SR_COMMON_GIT_METADATA
    #include <git.h>
#endif

namespace SR_CORE_GUI_NS {
    About::About()
        : Super("About", SR_MATH_NS::IVector2(400, 300))
    { }

    void About::Draw() {
        if (SR_GRAPH_GUI_NS::Immediate::BeginTabBar("About")) {
            SR_GRAPH_GUI_NS::Immediate::Text("SpaRcle Engine v0.0.7");

            SR_GRAPH_GUI_NS::Immediate::Separator();
            SR_GRAPH_GUI_NS::Immediate::Separator();

            SR_GRAPH_GUI_NS::Immediate::Text("Author: ");
            SR_GRAPH_GUI_NS::Immediate::Text("   Monika0000");
            SR_GRAPH_GUI_NS::Immediate::Separator();
            SR_GRAPH_GUI_NS::Immediate::Text("Member contributors: ");
            SR_GRAPH_GUI_NS::Immediate::Text("   * innerviewer");
            SR_GRAPH_GUI_NS::Immediate::Text("   * Drakeme");
            SR_GRAPH_GUI_NS::Immediate::Text("   * CaptainSlider");
            SR_GRAPH_GUI_NS::Immediate::Text("   * GitHub Copilot");
            SR_GRAPH_GUI_NS::Immediate::Separator();
            SR_GRAPH_GUI_NS::Immediate::Text("Made thanks to the following libraries: ");
            SR_GRAPH_GUI_NS::Immediate::TextWrapped("    glm, GLFW, GLEW, glad, Bullet3, PhysX, Box2D, Dear ImGui, tinyobjloader, stbi, json, Assimp");
            SR_GRAPH_GUI_NS::Immediate::Separator();
            SR_GRAPH_GUI_NS::Immediate::Text("Build Version: 0.0.7");
    #ifdef SR_COMMON_GIT_METADATA
            static std::string metadata;
            if (metadata.empty()) {
                std::time_t timestamp = std::stoll(git_CommitDate());
                std::tm* timeUTC = std::gmtime(&timestamp);

                metadata += "build '" + std::string(git_CommitSHA1()).substr(0, 7) + "' in '" + git_Branch() + "by '" +
                    + git_AuthorName() + "' on\n\t" + std::asctime(timeUTC);
            }

            SR_GRAPH_GUI_NS::Immediate::Text(metadata.c_str());
    #endif
            SR_GRAPH_GUI_NS::Immediate::Text("Licensed under the MIT License");

            SR_GRAPH_GUI_NS::Immediate::EndTabBar();
        }
    }
}