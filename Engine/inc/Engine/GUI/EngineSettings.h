//
// Created by Monika on 04.03.2022.
//

#ifndef SR_ENGINE_ENGINESETTINGS_H
#define SR_ENGINE_ENGINESETTINGS_H

#include <Engine/stdInclude.h>
#include <Graphics/GUI/Widget.h>

/**
 * Engine settings widget for configuring rendering and editor options.
 */
 
/**
 * Construct an EngineSettings widget instance.
 */
 
/**
 * Destroy the EngineSettings widget and release any subscriptions.
 */
 
/**
 * Render the widget's UI elements.
 */
 
/**
 * Called when the widget is opened; performs initialization required on open.
 */
 
/**
 * Draw multisampling-related controls and apply changes to rendering settings.
 */
 
/**
 * Draw lighting-related controls and apply changes to scene lighting settings.
 */
 
/**
 * Draw VSync-related controls and apply vertical sync settings.
 */
 
/**
 * Draw editor-specific settings and persist any editor preferences.
 */
 
/**
 * Populate or refresh the available render presets from stored memory.
 */
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