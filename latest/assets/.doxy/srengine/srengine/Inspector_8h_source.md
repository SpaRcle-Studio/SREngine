

# File Inspector.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**Inspector.h**](Inspector_8h.md)

[Go to the documentation of this file](Inspector_8h.md)


```C++
//
// Created by Monika on 14.02.2022.
//

#ifndef SR_ENGINE_CORE_INSPECTOR_H
#define SR_ENGINE_CORE_INSPECTOR_H

#include <Engine/GUI/ComponentDrawer.h>
#include <Engine/GUI/PropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/PointerPropertyDrawer.h>

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
        struct ComponentCategory {
            struct ComponentInfo {
                SR_UTILS_NS::StringAtom name;
                SR_UTILS_NS::StringAtom displayName;
                bool isBehaviour = false;
            };
            std::vector<ComponentInfo> components;
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

        void InspectTag(SR_UTILS_NS::StringAtom tag, const SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)>& callback);
        void InspectLayer(SR_UTILS_NS::StringAtom layer, const SR_HTYPES_NS::Function<void(SR_UTILS_NS::StringAtom)>& callback);
        void DrawComponent(SR_UTILS_NS::Component* pComponent, uint32_t& index);

        void InitCategories();

    private:
        void DrawGameObject(const SR_UTILS_NS::GameObject::Ptr& pGameObject);
        void DrawSceneObject(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject);

        void DrawComponentCategory(SR_UTILS_NS::IComponentable* pComponentable, ComponentCategory& category, SR_UTILS_NS::StringAtom categoryName);

        SR_NODISCARD PropertyDrawerContext CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue);

    private:
        std::string m_componentSearchBuffer;
        bool m_componentSearchOpened = false;

        std::vector<SR_UTILS_NS::StringAtom> m_availableComponents;
        std::vector<SR_UTILS_NS::StringAtom> m_availableCppBehaviours;
        ComponentCategory m_componentsCategories;

        std::list<SR_UTILS_NS::Component::Ptr> m_pointersHolder;
        SR_UTILS_NS::SceneObject::Ptr m_sceneObject;
        Hierarchy* m_hierarchy = nullptr;
        SR_WORLD_NS::Scene::Ptr m_scene;

        struct ComponentContext {
            SR_UTILS_NS::TimePointType lastUsage;
            ObjectPropertyDrawer::Ptr pObjectDrawer;
        };
        std::map<SR_UTILS_NS::EntityId, ComponentContext> m_componentContexts;
        uint64_t m_maxComponentContexts = 100;

        SR_CORE_GUI_NS::PointerPropertyDrawer::Ptr m_pPointerDrawer;

        float_t m_scrollBarWidth = 0.0f;

        bool m_isDragMode = false;
        SR_HTYPES_NS::Function<void(bool drag)> m_onBeforeChangeCallback;
        std::unique_ptr<SR_UTILS_NS::ISerializer> m_pSOSerializer;
        std::unique_ptr<SR_UTILS_NS::ISerializer> m_pTransformSerializer;
        std::unique_ptr<SR_UTILS_NS::ISerializer> m_pComponentsSerializer;
        std::unique_ptr<SR_UTILS_NS::ISerializer> m_pComponentSerializer;
        SR_UTILS_NS::Component::Ptr m_editableComponent;
        SR_UTILS_NS::Subscription m_moduleReloadSubscription;

    };
}

#endif //SR_ENGINE_CORE_INSPECTOR_H
```


