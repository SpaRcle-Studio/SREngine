//
// Created by Monika on 04.03.2022.
//

#ifndef SR_ENGINE_ENGINESETTINGS_H
#define SR_ENGINE_ENGINESETTINGS_H

#include <Engine/stdInclude.h>
#include <Graphics/GUI/Widget.h>

namespace SR_CORE_GUI_NS {
    class EngineSettings : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        EngineSettings();
        ~EngineSettings() override;

    protected:
        void Draw() override;
        void OnOpen() override;

    private:
        void DrawMultiSampling();
        void DrawLighting();
        void DrawVSync();
        void DrawEditorSettings();

        void PrepareRenderPresets();

    private:
        std::string m_renderPresetsMemory;
        std::set<std::string> m_renderPresets;
        int32_t m_activeRenderPreset = 0;
        SR_UTILS_NS::Subscription m_onRenderSettingsChanged;

    };
}

#endif //SR_ENGINE_ENGINESETTINGS_H
