//
// Created by Monika on 04.03.2022.
//

#ifndef SR_ENGINE_ENGINESETTINGS_H
#define SR_ENGINE_ENGINESETTINGS_H

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

#include <Graphics/GUI/Widget.h>
#include <Graphics/Settings/ActiveGraphicsSettings.h>

#include <Utils/Types/SetVector.h>

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
        void DrawVSync();
        void DrawEditorSettings();
        void DrawGraphicsSettings();

        void PrepareRenderPresets();

    private:
        float_t m_scrollBarWidth = 0.0f;
        std::string m_renderPresetsMemory;
        SR_HTYPES_NS::SetVector<SR_UTILS_NS::StringAtom> m_renderPresets;
        int32_t m_activeRenderPreset = 0;
        SR_UTILS_NS::Subscription m_onRenderSettingsChanged;
        ObjectPropertyDrawer::Ptr m_graphicsSettingsDrawer;
        SR_GRAPH_NS::ActiveGraphicsSettings m_cachedGraphicsSettings;

    };
}

#endif //SR_ENGINE_ENGINESETTINGS_H
