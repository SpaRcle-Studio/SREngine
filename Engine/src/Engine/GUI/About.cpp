//
// Created by Igor on 12/03/2023.
//

#include <Engine/GUI/About.h>
#include <Engine/GUI/EditorBanner.h>

#include <Utils/Common/ToString.h>
#include <Utils/FileSystem/FileSystem.h>

#include <Codegen/About.generated.hpp>

#ifdef SR_COMMON_GIT_METADATA
    #include <git.h>
#endif

namespace SR_CORE_GUI_NS {
    About::About()
        : Super("About", SR_MATH_NS::IVector2(640, 600))
    {
        SetCenter(true);
        SetFlags(static_cast<SR_GRAPH_GUI_NS::WindowFlags>(SR_GRAPH_GUI_NS::WindowFlags::NoTitleBar
            | SR_GRAPH_GUI_NS::WindowFlags::NoCollapse
            | SR_GRAPH_GUI_NS::WindowFlags::NoMove
            | SR_GRAPH_GUI_NS::WindowFlags::NoDocking
            | SR_GRAPH_GUI_NS::WindowFlags::NoSavedSettings
        ));
        m_logo = "Engine/Textures/logo.png";
    }

    void About::CollectBuildInfo() {
        SR_TRACY_ZONE;

        m_commit = "unknown";
        m_branch = "unknown";
        m_commitDate = "unknown";

    #ifdef SR_COMMON_GIT_METADATA
        m_commit = SR_UTILS_NS::String(git_CommitSHA1()).substr(0, 10);
        m_branch = git_Branch();

        const std::time_t timestamp = strtoll(git_CommitDate(), nullptr, 10);
        if (const std::tm* pTimeUTC = std::gmtime(&timestamp)) {
            char buffer[64] = { 0 };
            if (std::strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M UTC", pTimeUTC) > 0) {
                m_commitDate = buffer;
            }
        }
    #endif

        m_modulesHash = SR_UTILS_NS::ToString(SR_UTILS_NS::FileSystem::GetExecutableAndModulesHash());

        m_buildInfo = SR_UTILS_NS::String("SpaRcle Engine v") + SR_ENGINE_VERSION
            + "\nCommit: " + m_commit
            + "\nBranch: " + m_branch
            + "\nDate: " + m_commitDate
            + "\nModules hash: " + m_modulesHash;
    }

    void About::Draw() {
        const float_t baseFontSize = SR_IMMEDIATE_GUI_NS::GetFontSize();
        const float_t spacing = baseFontSize * 0.75f;
        const float_t labelWidth = baseFontSize * 9.0f;

        if (m_buildInfo.empty()) {
            CollectBuildInfo();
        }

        /// ширина зависит от шрифта редактора, высота - от фактического содержимого прошлого кадра
        SR_MATH_NS::IVector2 windowSize = EditorBanner::CalcWindowSize(54.0f, 52.0f);
        if (m_contentHeight > 0.0f) {
            windowSize.y = static_cast<int32_t>(SR_MIN(m_contentHeight, SR_IMMEDIATE_GUI_NS::GetDisplaySize().y * 0.9f));
        }
        SetSize(windowSize);

        void* pLogoDescriptor = nullptr;
        if (m_logo) {
            pLogoDescriptor = m_logo.GetResource()->GetDescriptor();
        }

        if (EditorBanner::Draw(pLogoDescriptor, "SpaRcle Engine", "Open-source cross-platform game engine", "v" SR_ENGINE_VERSION, baseFontSize * 9.0f)) {
            Close();
            return;
        }

        /// Team
        EditorBanner::SectionTitle("Team");
        EditorBanner::InfoRow("Author", "Monika0000", labelWidth);
        EditorBanner::InfoRow("Contributors", "innerviewer, Drakeme, CaptainSlider", labelWidth);
        EditorBanner::InfoRow("Studio", "SpaRcle Studio", labelWidth);

        /// Libraries
        EditorBanner::SectionTitle("Built with");

        static constexpr std::array<const char*, 24> libraries = {
            "Vulkan", "EvoVulkan", "WebGPU", "Dear ImGui", "ImPlot", "PhysX",
            "Box2D", "OpenAL Soft", "Assimp", "AngelScript", "FreeType", "HarfBuzz",
            "msdfgen", "glslang", "KTX", "Yoga", "SDL", "meshoptimizer",
            "Tracy", "fmt", "curl", "OpenSSL", "zlib", "tree-sitter"
        };
        EditorBanner::Tags(libraries);

        SR_IMMEDIATE_GUI_NS::TextColored(EditorBanner::GetMutedTextColor(), "%s", "...and many other great open-source projects.");

        /// Build
        EditorBanner::SectionTitle("Build");
        EditorBanner::InfoRow("Version", SR_ENGINE_VERSION, labelWidth);
        EditorBanner::InfoRow("Commit", m_commit.c_str(), labelWidth);
        EditorBanner::InfoRow("Branch", m_branch.c_str(), labelWidth);
        EditorBanner::InfoRow("Date", m_commitDate.c_str(), labelWidth);
        EditorBanner::InfoRow("Modules hash", m_modulesHash.c_str(), labelWidth);

        /// Footer
        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, spacing));
        SR_IMMEDIATE_GUI_NS::Separator();
        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, spacing * 0.3f));

        EditorBanner::Link("GitHub", "https://github.com/SpaRcle-Studio/SREngine");
        SR_IMMEDIATE_GUI_NS::SameLine(0.0f, spacing);
        EditorBanner::Link("Documentation", "https://docs.sparcles.dev/");
        SR_IMMEDIATE_GUI_NS::SameLine(0.0f, spacing);
        EditorBanner::Link("Discord", "https://discord.gg/NHuhNwFtYQ");
        SR_IMMEDIATE_GUI_NS::SameLine(0.0f, spacing * 2.0f);
        SR_IMMEDIATE_GUI_NS::TextColored(EditorBanner::GetMutedTextColor(), "%s", "Licensed under the MIT License");

        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, spacing * 0.5f));

        const float_t buttonHeight = baseFontSize * 2.2f;
        const float_t buttonWidth = baseFontSize * 10.0f;
        const float_t buttonsX = SR_IMMEDIATE_GUI_NS::GetCursorPos().x + SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x - buttonWidth * 2.0f - spacing;

        SR_IMMEDIATE_GUI_NS::SetCursorPosX(buttonsX);

        if (EditorBanner::SecondaryButton("Copy build info", SR_MATH_NS::FVector2(buttonWidth, buttonHeight))) {
            SR_IMMEDIATE_GUI_NS::CopyTextToClipboard(m_buildInfo.c_str());
        }

        SR_IMMEDIATE_GUI_NS::SameLine(0.0f, spacing);

        if (EditorBanner::AccentButton("Close", SR_MATH_NS::FVector2(buttonWidth, buttonHeight))) {
            Close();
        }

        m_contentHeight = SR_IMMEDIATE_GUI_NS::GetCursorPos().y + SR_IMMEDIATE_GUI_NS::GetStyleVarVec2(SR_IMMEDIATE_GUI_NS::StyleVar::WindowPadding).y;
    }
}
