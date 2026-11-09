//
// Created by Igor on 12/03/2023.
//

#include <Engine/GUI/About.h>

#include <Utils/Common/ToString.h>
#include <Utils/FileSystem/FileSystem.h>

#include <Codegen/About.generated.hpp>

#ifdef SR_COMMON_GIT_METADATA
    #include <git.h>
#endif

namespace SR_CORE_GUI_NS {
    About::About()
        : Super("About", SR_MATH_NS::IVector2(400, 300))
    { }

    void About::Draw() {
        if (SR_IMMEDIATE_GUI_NS::BeginTabBar("About")) {
            SR_IMMEDIATE_GUI_NS::Text("SpaRcle Engine v%s", SR_ENGINE_VERSION);

            SR_IMMEDIATE_GUI_NS::Separator();
            SR_IMMEDIATE_GUI_NS::Separator();

            SR_IMMEDIATE_GUI_NS::Text("Author: ");
            SR_IMMEDIATE_GUI_NS::Text("   Monika0000");
            SR_IMMEDIATE_GUI_NS::Separator();
            SR_IMMEDIATE_GUI_NS::Text("Member contributors: ");
            SR_IMMEDIATE_GUI_NS::Text("   * innerviewer");
            SR_IMMEDIATE_GUI_NS::Text("   * Drakeme");
            SR_IMMEDIATE_GUI_NS::Text("   * CaptainSlider");
            SR_IMMEDIATE_GUI_NS::Text("   * GitHub Copilot");
            SR_IMMEDIATE_GUI_NS::Separator();
            SR_IMMEDIATE_GUI_NS::Text("Made thanks to the following libraries: ");
            SR_IMMEDIATE_GUI_NS::TextWrapped("    glm, GLFW, GLEW, glad, Bullet3, PhysX, Box2D, Dear ImGui, tinyobjloader, stbi, json, Assimp");
            SR_IMMEDIATE_GUI_NS::Separator();
            SR_IMMEDIATE_GUI_NS::Text("Build Version: %s", SR_ENGINE_VERSION);

        #ifdef SR_COMMON_GIT_METADATA
            static std::string metadata;
            if (metadata.empty()) {
                std::time_t timestamp = std::stoll(git_CommitDate());
                std::tm* timeUTC = std::gmtime(&timestamp);

                metadata += "build '" + std::string(git_CommitSHA1()).substr(0, 7) + "' in '" + git_Branch() + "by '" +
                    + git_AuthorName() + "' on\n\t" + std::asctime(timeUTC);
            }

            SR_IMMEDIATE_GUI_NS::Text(metadata.c_str());
        #endif

            const std::string executableAndModulesHash = SR_UTILS_NS::ToString(SR_UTILS_NS::FileSystem::GetExecutableAndModulesHash());
            SR_IMMEDIATE_GUI_NS::Text("Executable and modules hash: %s", executableAndModulesHash.c_str());

            SR_IMMEDIATE_GUI_NS::Text("Licensed under the MIT License");

            SR_IMMEDIATE_GUI_NS::EndTabBar();
        }
    }
}
