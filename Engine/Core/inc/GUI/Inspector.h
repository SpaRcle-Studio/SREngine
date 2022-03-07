//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_INSPECTOR_H
#define SRENGINE_INSPECTOR_H

#include <GUI/Widget.h>
#include <GUI/ComponentDrawer.h>
#include <EntityComponentSystem/GameObject.h>
#include <World/Scene.h>

namespace Framework::Helper {
    class Transform3D;
}

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
        void DrawTransform(Helper::Transform3D* transform) const;

        template<typename T> void DrawComponent(Helper::Component* component, const std::string& name) {
            auto&& pComponent = dynamic_cast<T*>(component);

            if (!pComponent)
                return;

            if (ImGui::CollapsingHeader(component->GetComponentName().c_str()))
                ComponentDrawer::DrawComponent(pComponent);
        }

    private:
        Helper::Types::SafePtr<Helper::GameObject> m_gameObject;
        Helper::Types::SafePtr<World::Scene> m_scene;

    };
}

#endif //SRENGINE_INSPECTOR_H
