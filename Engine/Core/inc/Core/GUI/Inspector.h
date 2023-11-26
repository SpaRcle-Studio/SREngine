//
// Created by Monika on 14.02.2022.
//

#ifndef SR_ENGINE_CORE_INSPECTOR_H
#define SR_ENGINE_CORE_INSPECTOR_H

#include <Core/GUI/ComponentDrawer.h>
#include <Core/GUI/PropertyDrawer.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

#include <Graphics/GUI/Widget.h>

namespace SR_UTILS_NS {
    class Transform3D;
    class Transform2D;
}

namespace SR_CORE_GUI_NS {
    class EditorGUI;
    class Hierarchy;

    class Inspector : public SR_GRAPH_GUI_NS::Widget {
    public:
        explicit Inspector(Hierarchy* hierarchy);
        ~Inspector() override = default;

    public:
        void Update(float_t dt) override;

        void SetScene(const SR_WORLD_NS::Scene::Ptr& scene) override;

    protected:
        void Draw() override;

        void InspectGameObject();
        void InspectScene();

        void DrawComponents(SR_UTILS_NS::IComponentable* pIComponentable);

        void DrawSwitchTransform();
        void DrawTransform2D(SR_UTILS_NS::Transform2D* transform) const;
        void DrawTransform3D(SR_UTILS_NS::Transform3D* transform);

        void DrawComponentProperties(SR_UTILS_NS::Component* pComponent);

        SR_MAYBE_UNUSED void BackupTransform(const SR_UTILS_NS::GameObject::Ptr& ptr, const std::function<void()>& operation) const;

        void DrawComponent(SR_UTILS_NS::Component* pComponent, uint32_t& index);

    private:
        std::list<SR_UTILS_NS::Component::Ptr> m_pointersHolder;
        SR_UTILS_NS::GameObject::Ptr m_gameObject;
        Hierarchy* m_hierarchy = nullptr;
        SR_WORLD_NS::Scene::Ptr m_scene;

        ///Для DrawTransform3D и может быть DrawTransofrm2D
        bool m_isUsed = false;
        SR_HTYPES_NS::Marshal* m_oldTransformMarshal = nullptr;
    };
}

#endif //SR_ENGINE_CORE_INSPECTOR_H
