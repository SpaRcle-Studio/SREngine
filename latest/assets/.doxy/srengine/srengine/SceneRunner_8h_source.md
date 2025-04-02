

# File SceneRunner.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**SceneRunner.h**](SceneRunner_8h.md)

[Go to the documentation of this file](SceneRunner_8h.md)


```C++
//
// Created by Monika on 05.07.2022.
//

#ifndef SR_ENGINE_SCENERUNNER_H
#define SR_ENGINE_SCENERUNNER_H

#include <Graphics/GUI/Widget.h>

#include <Utils/Types/SafePointer.h>
#include <Utils/World/Scene.h>
#include <Utils/Input/InputEvents.h>

namespace SR_CORE_GUI_NS {
    class SceneRunner : public SR_GRAPH_NS::GUI::Widget {
    public:
        SceneRunner();
        ~SceneRunner() override = default;

    public:
        void SetScene(const SR_WORLD_NS::Scene::Ptr &scene);

    private:
        void Draw() override;

        bool PlayScene();
        void ReturnScene();

        SR_NODISCARD EditorGUI* GetEditor() const;

    private:
        bool m_isActive = false;
        bool m_isPaused = false;

        SR_WORLD_NS::Scene::Ptr m_scene;
        SR_UTILS_NS::Path m_lastPath;
        SR_UTILS_NS::Path m_scenePath;

    };
}

#endif //SR_ENGINE_SCENERUNNER_H
```


