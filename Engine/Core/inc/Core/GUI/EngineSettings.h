//
// Created by Monika on 04.03.2022.
//

#ifndef SRENGINE_ENGINESETTINGS_H
#define SRENGINE_ENGINESETTINGS_H

namespace Framework::Core::GUI {
    class EngineSettings : public Graphics::GUI::Widget {
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
