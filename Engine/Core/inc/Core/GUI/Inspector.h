//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_INSPECTOR_H
#define SRENGINE_INSPECTOR_H

#include <Core/GUI/ComponentDrawer.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

#include <Graphics/GUI/Widget.h>

namespace SR_UTILS_NS {
    class Transform3D;
    class Transform2D;
}

namespace SR_CORE_NS::GUI {
    class EditorGUI;
    class Hierarchy;

    class Inspector : public Graphics::GUI::Widget {
    public:
        explicit Inspector(Hierarchy* hierarchy);
        ~Inspector() override = default;

    public:
        void Update();

        void SetScene(const SR_WORLD_NS::Scene::Ptr& scene);

    protected:
        void Draw() override;

        void InspectGameObject();
        void InspectScene();

        void DrawComponents(SR_UTILS_NS::IComponentable* pIComponentable);

        void DrawSwitchTransform();
        void DrawTransform2D(SR_UTILS_NS::Transform2D* transform) const;
        void DrawTransform3D(SR_UTILS_NS::Transform3D* transform) const;

        void BackupTransform(const SR_UTILS_NS::GameObject::Ptr& ptr, const std::function<void()>& operation) const;

        template<typename T> SR_UTILS_NS::Component* DrawComponent(SR_UTILS_NS::Component* component, const std::string& name, uint32_t& index) {
            auto&& pComponent = dynamic_cast<T*>(component);
            auto&& context = dynamic_cast<EditorGUI*>(GetManager());

            if (!pComponent || !context) {
                return component;
            }

            ++index;

            bool enabled = pComponent->IsEnabled();
            if (ImGui::Checkbox(SR_UTILS_NS::Format("##%s-%i-checkbox", name.c_str(), index).c_str(), &enabled)) {
                pComponent->SetEnabled(enabled);
            }

            ImGui::SameLine();

            if (ImGui::CollapsingHeader(SR_UTILS_NS::Format("[%i] %s", index, component->GetComponentName().c_str()).c_str()))
                ComponentDrawer::DrawComponent(pComponent, context, index);

            return dynamic_cast<SR_UTILS_NS::Component*>(pComponent);
        }

    private:
        SR_UTILS_NS::GameObject::Ptr m_gameObject;
        Hierarchy* m_hierarchy = nullptr;
        SR_WORLD_NS::Scene::Ptr m_scene;
    };
}

#endif //SRENGINE_INSPECTOR_H
