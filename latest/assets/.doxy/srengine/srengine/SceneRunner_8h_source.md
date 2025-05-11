

# File SceneRunner.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**SceneRunner.h**](SceneRunner_8h.md)

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


