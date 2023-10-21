//
// Created by Monika on 04.03.2022.
//

#ifndef SRENGINE_ENGINESETTINGS_H
#define SRENGINE_ENGINESETTINGS_H

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

#endif //SRENGINE_ENGINESETTINGS_H
