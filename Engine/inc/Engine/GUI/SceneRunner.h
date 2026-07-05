//
// Created by Monika on 05.07.2022.
//

#ifndef SR_ENGINE_SCENERUNNER_H
#define SR_ENGINE_SCENERUNNER_H

#include <Graphics/GUI/Widget.h>

#include <Utils/Types/SafePointer.h>
#include <Utils/World/Scene.h>
#include <Utils/Input/InputEvents.h>

namespace SR_CORE_NS {
    class Engine;
}

namespace SR_CORE_GUI_NS {
    class EditorGUI;

    /// @hidden
    class SceneRunner : public SR_GRAPH_NS::GUI::Widget {
        SR_CLASS()
    public:
        SceneRunner();
        ~SceneRunner() override = default;

    public:
        void SetScene(const SR_WORLD_NS::Scene::Ptr &scene) override;

        static bool PlayScene(SR_WORLD_NS::Scene::Ptr pScene, Engine* pEngine);
        bool PlayScene();
        void ReturnScene();

    private:
        void Draw() override;

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
