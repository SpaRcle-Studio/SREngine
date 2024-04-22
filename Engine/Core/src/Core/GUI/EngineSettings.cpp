//
// Created by Monika on 04.03.2022.
//

#include <Core/GUI/EngineSettings.h>

#include <Graphics/Lighting/LightSystem.h>

namespace SR_CORE_GUI_NS {
    EngineSettings::EngineSettings()
        : SR_GRAPH_NS::GUI::Widget("Settings")
    { }

    void EngineSettings::Draw() {
        DrawMultiSampling();
        ImGui::Separator();
        DrawVSync();
        ImGui::Separator();
        DrawLighting();
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

        if (ImGui::Combo("Multi-sampling", &currentItem, SR_SAMPLE_COUNT_NAME_LIST)) {
            pPipeline->SetSampleCount(SR_SAMPLE_COUNT_VALUE_LIST.at(currentItem));
        }
    }

    void EngineSettings::DrawLighting() {
        auto&& position = GetRenderScene()->GetLightSystem()->m_position;
        SR_GRAPH_NS::GUI::DrawVec3Control("Directional light position", position);
    }

    void EngineSettings::DrawVSync() {
        auto&& pPipeline = GetContext()->GetPipeline();
        if (!pPipeline) {
            return;
        }

        bool vsync = pPipeline->IsVSyncEnabled();
        if (ImGui::Checkbox("VSync", &vsync)) {
            pPipeline->SetVSyncEnabled(vsync);
        }
    }
}
