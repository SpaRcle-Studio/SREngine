//
// Created by Nikita on 28.06.2021.
//

#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/Features.h>

#include <Graphics/Pipeline/Environment.h>
#include <Graphics/GUI/Icons.h>
#include <Graphics/Pipeline/Vulkan.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Render/RenderContext.h>

bool SR_GRAPH_NS::Environment::PreInitGUI(const SR_UTILS_NS::Path &fontPath) {
    SR_GRAPH("Environment::InitGUI() : pre-initializing ImGUI library...");

    {
        //IMGUI_CHECKVERSION();
        m_guiContext = ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        SR_GRAPH("Environment::InitGUI() : load editor font...\n\tPath: " + fontPath.ToString());
        if (fontPath.Exists()) {
            ImFontConfig font_config;
            font_config.OversampleH = 1; //or 2 is the same
            font_config.OversampleV = 1;
            font_config.PixelSnapH = 1;

            static const ImWchar ranges[] =
            {
                    0x0020, 0x00FF, // Basic Latin + Latin Supplement
                    0x0400, 0x044F, // Cyrillic
                    0,
            };

            SR_MAYBE_UNUSED ImFont *pFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 12.0f, nullptr, ranges);
        }
        else {
            SR_ERROR("Environment::PreInitGUI() : file not found! \n\tPath: " + fontPath.ToString());
        }

        const auto&& iconsFont = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Fonts/fa-solid-900.ttf");

        SR_GRAPH("Environment::InitGUI() : load icon font...\n\tPath: " + iconsFont.ToString());
        if (iconsFont.Exists()) {
            ImFontConfig config;
            config.MergeMode = false;
            config.GlyphMinAdvanceX = 13.0f;
            static const ImWchar icon_ranges[] = {SR_ICON_MIN, SR_ICON_MAX, 0};
            m_iconFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(iconsFont.CStr(), 40.0f, &config, icon_ranges);
        }
        else {
            SR_ERROR("Environment::PreInitGUI() : file not found! \n\tPath: " + iconsFont.ToString());
        }

        //io.IniFilename = NULL;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        //io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigDockingWithShift       = true;
        io.ConfigWindowsResizeFromEdges = true;

        if (SR_UTILS_NS::Features::Instance().Enabled("Undocking", false)) {
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }

        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        //io.ConfigDockingWithShift = true;
        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
    }

    return true;
}

void SR_GRAPH_NS::Environment::OnMultiSampleChanged() {
    m_renderContext->OnMultiSampleChanged();
}

void Framework::Graphics::Environment::SetWinCallBack(const std::function<void(WinEvents, void * , void * , void * )>& callback) {
    g_callback = std::move(callback);
}

Framework::Graphics::Environment *Framework::Graphics::Environment::Get() {
    if (g_environment == nullptr) {
        g_environment = new Vulkan();
    }
    return g_environment;
}

uint8_t Framework::Graphics::Environment::GetSamplesCount() const {
    SRAssert(m_currentSampleCount >= 1 && m_currentSampleCount <= 64);
    return m_currentSampleCount;
}

void Framework::Graphics::Environment::SetCurrentFramebuffer(SR_GTYPES_NS::Framebuffer *pFramebuffer) {
    m_currentFramebuffer = pFramebuffer;

    if (m_currentFramebuffer) {
        SRAssert(!m_currentFramebuffer->IsDirty());
    }
}

void Framework::Graphics::Environment::Destroy() {
    if (g_environment) {
        delete g_environment;
        g_environment = nullptr;
    }
}
