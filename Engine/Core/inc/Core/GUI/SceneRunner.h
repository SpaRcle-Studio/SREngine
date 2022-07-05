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
        SR_WORLD_NS::Scene::Ptr m_scene;
        std::atomic<bool> m_isActive;
        std::atomic<bool> m_isPaused;
        SR_UTILS_NS::Path m_scenePath;

    };
}

#endif //SRENGINE_SCENERUNNER_H
