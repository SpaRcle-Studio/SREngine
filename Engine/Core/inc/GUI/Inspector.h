//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_INSPECTOR_H
#define SRENGINE_INSPECTOR_H

#include <GUI/Widget.h>
#include <EntityComponentSystem/GameObject.h>
#include <World/Scene.h>

namespace Framework::Core::GUI {
    class Inspector : public Graphics::GUI::Widget {
    public:
        Inspector();
        ~Inspector() override = default;

    public:
        void Update();
        void SetScene(const Helper::World::Scene::Ptr& scene);

    protected:
        void Draw() override;
        void DrawComponents();

    private:
        Types::SafePtr<Helper::GameObject> m_gameObject;
        Types::SafePtr<World::Scene> m_scene;

    };
}

#endif //SRENGINE_INSPECTOR_H
