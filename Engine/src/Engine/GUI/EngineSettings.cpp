//
// Created by Monika on 04.03.2022.
//

#include <Engine/GUI/EngineSettings.h>

#include <Graphics/Lighting/LightSystem.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Utils/Common/StoreUtils.h>
#include <Utils/Events/Broadcaster.h>

namespace SR_CORE_GUI_NS {
    /**
     * @brief Initializes the Settings widget and subscribes to render-settings updates.
     *
     * Constructs the EngineSettings widget (named "Settings") and registers a subscription
     * to the render-settings-changed event. When that event fires, the subscription
     * will invoke PrepareRenderPresets() to refresh available render presets. The
     * subscription handle is stored in m_onRenderSettingsChanged.
     */
    EngineSettings::EngineSettings()
        : SR_GRAPH_NS::GUI::Widget("Settings")
    {
        m_onRenderSettingsChanged = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_ON_RENDER_SETTINGS_CHANGED_ID, [this](auto&&) {
            PrepareRenderPresets();
        });
    }

    EngineSettings::~EngineSettings() {
        m_onRenderSettingsChanged.Reset();
    }

    void EngineSettings::Draw() {
        DrawMultiSampling();
        SR_GRAPH_GUI_NS::Immediate::Separator();
        DrawVSync();
        SR_GRAPH_GUI_NS::Immediate::Separator();
        DrawLighting();
        SR_GRAPH_GUI_NS::Immediate::Separator();
        DrawEditorSettings();
    }

    void EngineSettings::DrawMultiSampling() {
        static const char* SR_SAMPLE_COUNT_NAME_LIST = {
                "Sample 1\0"
                "Sample 2\0"
                "Sample 4\0"
                "Sample 8\0"
                "Sample 16\0"
                "Sample 32\0"
                "Sample 64\0"
        };

        static std::map<uint8_t, int32_t> SR_SAMPLE_COUNT_KEY_LIST = {
                { 1, 0 },
                { 2, 1 },
                { 4, 2 },
                { 8, 3 },
                { 16, 4 },
                { 32, 5 },
                { 64, 6 },
        };

        static std::vector<uint8_t> SR_SAMPLE_COUNT_VALUE_LIST = {
                1, 2, 4, 8, 16, 32, 64
        };

        auto&& pPipeline = GetContext()->GetPipeline();
        int32_t currentItem = SR_SAMPLE_COUNT_KEY_LIST.at(pPipeline->GetSamplesCount());

        if (SR_GRAPH_GUI_NS::Immediate::Combo("Multi-sampling", &currentItem, SR_SAMPLE_COUNT_NAME_LIST)) {
            pPipeline->SetSampleCount(SR_SAMPLE_COUNT_VALUE_LIST.at(currentItem));
            SR_UTILS_NS::StoreUtils::User::SetInt("MultiSampling", SR_SAMPLE_COUNT_VALUE_LIST.at(currentItem));
        }

        bool optimizedRenderUpdate = GetContext()->IsOptimizedRenderUpdateEnabled();
        if (SR_GRAPH_GUI_NS::Immediate::Checkbox("Optimized render update", &optimizedRenderUpdate)) {
            GetContext()->SetOptimizedRenderUpdateEnabled(optimizedRenderUpdate);
        }
    }

    void EngineSettings::DrawLighting() {

    }

    void EngineSettings::DrawVSync() {
        auto&& pPipeline = GetContext()->GetPipeline();
        if (!pPipeline) {
            return;
        }

        bool vsync = pPipeline->IsVSyncEnabled();
        if (SR_GRAPH_GUI_NS::Immediate::Checkbox("VSync", &vsync)) {
            pPipeline->SetVSyncEnabled(vsync);
        }

        int32_t swapchainImages = SR_UTILS_NS::StoreUtils::User::GetInt("SwapchainImages", pPipeline->GetSwapchainImagesCount());

        if (SR_GRAPH_GUI_NS::Immediate::InputInt("Swapchain images", &swapchainImages, 1, 1, SR_GRAPH_GUI_NS::Immediate::InputTextFlags::EnterReturnsTrue)) {
            swapchainImages = SR_CLAMP(swapchainImages, 1, 16);
            SR_UTILS_NS::StoreUtils::User::SetInt("SwapchainImages", swapchainImages);
        }

        if (swapchainImages != pPipeline->GetSwapchainImagesCount()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Yellow(), "Requires restart!");
        }
    }

    void EngineSettings::DrawEditorSettings() {
        float_t fontSize = SR_UTILS_NS::StoreUtils::User::GetFloat("ImGuiFontSize", 0.f);
        float_t iconFontSize = SR_UTILS_NS::StoreUtils::User::GetFloat("ImGuiIconFontSize", 0.f);
        bool showEntityId = SR_UTILS_NS::StoreUtils::User::GetBool("ShowEntityId", false);
        bool showHiddenEntities = SR_UTILS_NS::StoreUtils::User::GetBool("ShowHiddenEntities", false);

        if (SR_GRAPH_GUI_NS::Immediate::InputFloat("Font size", &fontSize, 1.0f, 1.0f, "%.1f", SR_GRAPH_GUI_NS::Immediate::InputTextFlags::EnterReturnsTrue)) {
            SR_UTILS_NS::StoreUtils::User::SetFloat("ImGuiFontSize", fontSize);
        }

        if (SR_GRAPH_GUI_NS::Immediate::InputFloat("Icon font size", &iconFontSize, 1.0f, 1.0f, "%.1f", SR_GRAPH_GUI_NS::Immediate::InputTextFlags::EnterReturnsTrue)) {
            SR_UTILS_NS::StoreUtils::User::SetFloat("ImGuiIconFontSize", iconFontSize);
        }

        if (SR_GRAPH_GUI_NS::Immediate::Checkbox("Show entity id", &showEntityId)) {
            SR_UTILS_NS::StoreUtils::User::SetBool("ShowEntityId", showEntityId);
        }

        if (SR_GRAPH_GUI_NS::Immediate::Checkbox("Show hidden entities", &showHiddenEntities)) {
            SR_UTILS_NS::StoreUtils::User::SetBool("ShowHiddenEntities", showHiddenEntities);
        }

        if (SR_GRAPH_GUI_NS::Immediate::Combo("Render preset", &m_activeRenderPreset, m_renderPresetsMemory.c_str())) {
            uint32_t index = 0;
            for (auto&& preset : m_renderPresets) {
                if (index == m_activeRenderPreset) {
                    GetContext()->SetActivePreset(preset);
                    break;
                }
                index++;
            }
        }

        if (SR_GRAPH_GUI_NS::Immediate::Button("Save")) {
            SR_UTILS_NS::StoreUtils::Storage::Instance().Save();
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        if (SR_GRAPH_GUI_NS::Immediate::Button("Load")) {
            SR_UTILS_NS::StoreUtils::Storage::Instance().Load();
        }
    }

    void EngineSettings::PrepareRenderPresets() {
        m_renderPresets.clear();
        m_renderPresetsMemory.clear();
        m_activeRenderPreset = 0;

        m_renderPresets.insert("Default");
        m_renderPresets.insert(GetContext()->GetSettings().defaultPreset.name);

        for (auto&& preset : GetContext()->GetSettings().presets) {
            m_renderPresets.insert(preset.name);
        }

        uint32_t index = 0;
        for (auto&& preset : m_renderPresets) {
            if (preset == GetContext()->GetActivePreset()) {
                m_activeRenderPreset = index;
                break;
            }
            index++;
        }

        for (auto&& preset : m_renderPresets) {
            m_renderPresetsMemory += preset + '\0';
        }
    }

    void EngineSettings::OnOpen() {
        Super::OnOpen();
        PrepareRenderPresets();
    }
}