//
// Created by Monika on 04.03.2022.
//

#include <Engine/GUI/EngineSettings.h>
#include <Graphics/Lighting/LightSystem.h>

#include <Utils/Common/StoreUtils.h>

namespace SR_CORE_GUI_NS {
    EngineSettings::EngineSettings()
        : SR_GRAPH_NS::GUI::Widget("Settings") {}

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
        static const char* SR_SAMPLE_COUNT_NAME_LIST = {"Sample 1\0"
                                                        "Sample 2\0"
                                                        "Sample 4\0"
                                                        "Sample 8\0"
                                                        "Sample 16\0"
                                                        "Sample 32\0"
                                                        "Sample 64\0"};

        static std::map<uint8_t, int32_t> SR_SAMPLE_COUNT_KEY_LIST = {
            {1, 0}, {2, 1}, {4, 2}, {8, 3}, {16, 4}, {32, 5}, {64, 6},
        };

        static std::vector<uint8_t> SR_SAMPLE_COUNT_VALUE_LIST = {1, 2, 4, 8, 16, 32, 64};

        auto&& pPipeline = GetContext()->GetPipeline();
        int32_t currentItem = SR_SAMPLE_COUNT_KEY_LIST.at(pPipeline->GetSamplesCount());

        if (SR_GRAPH_GUI_NS::Immediate::Combo("Multi-sampling", &currentItem, SR_SAMPLE_COUNT_NAME_LIST)) {
            pPipeline->SetSampleCount(SR_SAMPLE_COUNT_VALUE_LIST.at(currentItem));
        }

        bool optimizedRenderUpdate = GetContext()->IsOptimizedRenderUpdateEnabled();
        if (SR_GRAPH_GUI_NS::Immediate::Checkbox("Optimized render update", &optimizedRenderUpdate)) {
            GetContext()->SetOptimizedRenderUpdateEnabled(optimizedRenderUpdate);
        }
    }

    void EngineSettings::DrawLighting() {
        SR_MATH_NS::FVector3 position = GetRenderScene()->GetLightSystem()->GetDirectionalLightPosition();
        // if (SR_GRAPH_NS::GUI::DrawVec3Control("Directional light position",
        // position)) {
        //     GetRenderScene()->GetLightSystem()->SetDirectionalLightPosition(position);
        // }
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
    }

    void EngineSettings::DrawEditorSettings() {
        float_t fontSize = SR_UTILS_NS::StoreUtils::User::GetFloat("ImGuiFontSize", 0.f);
        float_t iconFontSize = SR_UTILS_NS::StoreUtils::User::GetFloat("ImGuiIconFontSize", 0.f);
        bool showEntityId = SR_UTILS_NS::StoreUtils::User::GetBool("ShowEntityId", false);
        bool showHiddenEntities = SR_UTILS_NS::StoreUtils::User::GetBool("ShowHiddenEntities", false);

        if (SR_GRAPH_GUI_NS::Immediate::InputFloat(
                "Font size", &fontSize, 1.0f, 1.0f, "%.1f", SR_GRAPH_GUI_NS::Immediate::InputTextFlags::EnterReturnsTrue
            )) {
            SR_UTILS_NS::StoreUtils::User::SetFloat("ImGuiFontSize", fontSize);
        }

        if (SR_GRAPH_GUI_NS::Immediate::InputFloat(
                "Icon font size", &iconFontSize, 1.0f, 1.0f, "%.1f",
                SR_GRAPH_GUI_NS::Immediate::InputTextFlags::EnterReturnsTrue
            )) {
            SR_UTILS_NS::StoreUtils::User::SetFloat("ImGuiIconFontSize", iconFontSize);
        }

        if (SR_GRAPH_GUI_NS::Immediate::Checkbox("Show entity id", &showEntityId)) {
            SR_UTILS_NS::StoreUtils::User::SetBool("ShowEntityId", showEntityId);
        }

        if (SR_GRAPH_GUI_NS::Immediate::Checkbox("Show hidden entities", &showHiddenEntities)) {
            SR_UTILS_NS::StoreUtils::User::SetBool("ShowHiddenEntities", showHiddenEntities);
        }

        if (SR_GRAPH_GUI_NS::Immediate::Button("Save")) {
            SR_UTILS_NS::StoreUtils::Storage::Instance().Save();
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        if (SR_GRAPH_GUI_NS::Immediate::Button("Load")) {
            SR_UTILS_NS::StoreUtils::Storage::Instance().Load();
        }
    }
} // namespace SR_CORE_GUI_NS
