//
// Created by Monika on 04.03.2022.
//

#ifndef SR_ENGINE_ENGINESETTINGS_H
#define SR_ENGINE_ENGINESETTINGS_H

namespace SR_CORE_GUI_NS {
    class EngineSettings : public SR_GRAPH_GUI_NS::Widget {
    public:
        EngineSettings();
        ~EngineSettings() override = default;

    protected:
        void Draw() override;

    private:
        void DrawMultiSampling();
        void DrawLighting();
        void DrawVSync();

    };
}

#endif //SR_ENGINE_ENGINESETTINGS_H
