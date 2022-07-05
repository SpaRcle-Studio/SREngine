//
// Created by Monika on 05.07.2022.
//

#ifndef SRENGINE_SCENERUNNER_H
#define SRENGINE_SCENERUNNER_H

#include <GUI/Widget.h>

#include <Utils/Types/SafePointer.h>
#include <Utils/World/Scene.h>
#include <Utils/Input/InputEvents.h>

namespace SR_CORE_NS::GUI {
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

    private:
        bool m_isActive = false;
        bool m_isPaused = false;

        SR_WORLD_NS::Scene::Ptr m_scene;
        SR_UTILS_NS::Path m_lastPath;
        SR_UTILS_NS::Path m_scenePath;

    };
}

#endif //SRENGINE_SCENERUNNER_H
