//
// Created by Monika on 15.09.2023.
//

#include <Graphics/Overlay/ImGuiOverlay.h>
#include <Graphics/GUI/Editor/Theme.h>
#include <Graphics/GUI/Icons.h>

namespace SR_GRAPH_NS {
    bool ImGuiOverlay::Init() {
        SR_GRAPH("ImGuiOverlay::Init() : initializing ImGui...");

        m_context = ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGuiStyle& style = ImGui::GetStyle();

        auto&& fontPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Fonts/tahoma.ttf");

        SR_GRAPH("ImGuiOverlay::Init() : load editor font...\n\tPath: " + fontPath.ToString());
        if (fontPath.Exists()) {
            ImFontConfig font_config;
            font_config.OversampleH = 1; /// Or 2 is the same
            font_config.OversampleV = 1;
            font_config.PixelSnapH = true;

            static const ImWchar ranges[] = {
                0x0020, 0x00FF, /// Basic Latin + Latin Supplement
                0x0400, 0x044F, /// Cyrillic
                0,
            };

            m_mainFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 12.0f, nullptr, ranges);
        }
        else {
            SR_ERROR("ImGuiOverlay::Init() : file not found!\n\tPath: " + fontPath.ToString());
        }

        auto&& iconsFont = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Fonts/fa-solid-900.ttf");

        SR_GRAPH("ImGuiOverlay::Init() : load icon font...\n\tPath: " + iconsFont.ToString());
        if (iconsFont.Exists()) {
            ImFontConfig config;
            config.MergeMode = false;
            config.GlyphMinAdvanceX = 13.0f;
            static const ImWchar icon_ranges[] = { SR_ICON_MIN, SR_ICON_MAX, 0 };
            m_iconFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(iconsFont.CStr(), 40.0f, &config, icon_ranges);
        }
        else {
            SR_ERROR("ImGuiOverlay::Init() : file not found! \n\tPath: " + iconsFont.ToString());
        }

        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigDockingWithShift = true;
        io.ConfigWindowsResizeFromEdges = true;

        if (SR_UTILS_NS::Features::Instance().Enabled("Undocking", false)) {
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }

        if (auto&& pTheme = SR_GRAPH_GUI_NS::Theme::Load("Engine/Configs/Themes/Dark.xml")) {
            pTheme->Apply(style);
            delete pTheme;
        }
        else {
            SR_ERROR("Engine::InitializeRender() : failed to load theme!");
        }

        auto&& resourcesManager = SR_UTILS_NS::ResourceManager::Instance();

        m_iniPathEditor = resourcesManager.GetCachePath().Concat("Editor/Configs/ImGuiEditor.config");
        m_iniPathWidgets = resourcesManager.GetCachePath().Concat("Editor/Configs/EditorWidgets.xml");

        if (!m_iniPathEditor.Exists()) {
            m_iniPathEditor.Create();
            SR_UTILS_NS::Platform::Copy(resourcesManager.GetResPath().Concat("Editor/Configs/ImGuiEditor.config"), m_iniPathEditor);
        }

        if (!m_iniPathWidgets.Exists()) {
            m_iniPathWidgets.Create();
            SR_UTILS_NS::Platform::Copy(resourcesManager.GetResPath().Concat("Editor/Configs/EditorWidgets.xml"), m_iniPathWidgets);
        }

        io.IniFilename = m_iniPathEditor.CStr();

        return true;
    }

    void ImGuiOverlay::Destroy() {
        if (m_context) {
            ImGui::DestroyContext(m_context);
            m_context = nullptr;
        }
    }

    bool ImGuiOverlay::IsUndockingActive() const {
        if (m_context && ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            return m_context->Viewports.size() > 1;
        }

        return false;
    }
}