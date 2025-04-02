

# File EngineSettings.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**EngineSettings.h**](EngineSettings_8h.md)

[Go to the documentation of this file](EngineSettings_8h.md)


```C++
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
        void DrawEditorSettings();

    };
}

#endif //SR_ENGINE_ENGINESETTINGS_H
```


