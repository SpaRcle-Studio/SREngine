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

#include "PropertyDrawers/ObjectPropertyDrawer.h"

namespace SR_UTILS_NS {
    class Transform3D;
    class Transform2D;
}

namespace SR_CORE_GUI_NS {
    class EditorGUI;
    class Hierarchy;

    class Inspector : public SR_GRAPH_GUI_NS::Widget {
        struct ComponentCategory {
            std::vector<SR_UTILS_NS::StringAtom> components;
            std::map<SR_UTILS_NS::StringAtom, ComponentCategory> categories;
        };
    public:
        Inspector() = default;
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

        void InspectTag(SR_UTILS_NS::StringAtom tag, SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)> callback);
        void InspectLayer(SR_UTILS_NS::StringAtom layer, SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)> callback);

        bool DrawSwitchTransform();
        bool DrawTransform2D(SR_UTILS_NS::Transform2D* transform) const;
        bool DrawTransform3D(SR_UTILS_NS::Transform3D* transform);

        SR_MAYBE_UNUSED void BackupTransform(const SR_UTILS_NS::GameObject::Ptr& ptr, const std::function<void()>& operation) const;

        void DrawComponent(SR_UTILS_NS::Component* pComponent, uint32_t& index);

    private:
        void DrawComponentCategory(SR_UTILS_NS::IComponentable* pComponentable, ComponentCategory& category, SR_UTILS_NS::StringAtom categoryName);

    private:
        std::string m_componentSearchBuffer;

        std::vector<SR_UTILS_NS::StringAtom> m_availableComponents;
        ComponentCategory m_componentsCategories;

        std::list<SR_UTILS_NS::Component::Ptr> m_pointersHolder;
        SR_UTILS_NS::SceneObject::Ptr m_sceneObject;
        Hierarchy* m_hierarchy = nullptr;
        SR_WORLD_NS::Scene::Ptr m_scene;

        struct ComponentContext {
            ObjectPropertyDrawer::Ptr pObjectDrawer;
        };
        std::map<SR_UTILS_NS::Component::Ptr, ComponentContext> m_componentContexts;

        ///Для DrawTransform3D и может быть DrawTransofrm2D
        bool m_isUsed = false;
        float_t m_scrollBarWidth = 0.0f;
        SR_HTYPES_NS::Marshal* m_oldTransformMarshal = nullptr;
    };
}

#endif //SR_ENGINE_CORE_INSPECTOR_H
