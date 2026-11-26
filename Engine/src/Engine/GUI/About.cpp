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
            SR_IMMEDIATE_GUI_NS::TextWrapped("    GLFW, GLEW, glad, Bullet3, PhysX, Box2D, Dear ImGui, tinyobjloader, stbi, json, Assimp");
            SR_IMMEDIATE_GUI_NS::Separator();
            SR_IMMEDIATE_GUI_NS::Text("Build Version: %s", SR_ENGINE_VERSION);

        #ifdef SR_COMMON_GIT_METADATA
            static SR_UTILS_NS::String metadata;
            if (metadata.empty()) {
                std::time_t timestamp = strtoll(git_CommitDate(), nullptr, 10);
                std::tm* pTimeUTC = std::gmtime(&timestamp);

                metadata += SR_UTILS_NS::String("build '") + SR_UTILS_NS::String(git_CommitSHA1()).substr(0, 7) + "' in '" + git_Branch() + "by '" +
                    git_AuthorName() + "' on\n\t" + std::asctime(pTimeUTC);
            }

            SR_IMMEDIATE_GUI_NS::Text(metadata.c_str());
        #endif

            const SR_UTILS_NS::String executableAndModulesHash = SR_UTILS_NS::ToString(SR_UTILS_NS::FileSystem::GetExecutableAndModulesHash());
            SR_IMMEDIATE_GUI_NS::Text("Executable and modules hash: %s", executableAndModulesHash.c_str());

            SR_IMMEDIATE_GUI_NS::Text("Licensed under the MIT License");

            SR_IMMEDIATE_GUI_NS::EndTabBar();
        }
    }
}
