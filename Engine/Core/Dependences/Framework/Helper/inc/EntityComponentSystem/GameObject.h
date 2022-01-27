//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <string>
#include <vector>
#include <mutex>
#include <json/json.hpp>
#include <map>
#include <glm/glm.hpp>

#include <Types/SafePointer.h>
#include <Math/Vector3.h>

#include <EntityComponentSystem/EntityManager.h>

namespace Framework {
    class API;
}

namespace Framework::Helper {
    namespace World {
        class Scene;
    };

    class Transform;
    class Component;

    class GameObject : public Types::SafePtr<GameObject>, public Entity {
        friend class World::Scene;
        friend class Transform;
        friend class ::Framework::API;

        enum class DestroyBy {
            Scene, GameObject, Other
        };

    public:
        typedef Types::SafePtr<GameObject> Ptr;

    private:
        GameObject(const Types::SafePtr<World::Scene>& scene, std::string name, std::string tag = "Untagged");
        virtual ~GameObject();

    public:
        [[nodiscard]] Types::SafePtr<World::Scene> GetScene() const { return this->m_scene; }
        [[nodiscard]] Transform* GetTransform() const { return this->m_transform; }
        [[nodiscard]] GameObject::Ptr GetParent() const { return m_parent; }
        [[nodiscard]] std::string GetName() const;
        [[nodiscard]] bool IsActive() const { return m_isActive && m_isParentActive; }
        [[nodiscard]] bool IsEnabled() const { return m_isActive; }
        [[nodiscard]] SR_INLINE bool HasChildren() const { return !m_children.empty(); }
        [[nodiscard]] SR_INLINE bool IsSelect() const { return this->m_isSelect; }
        [[nodiscard]] SR_INLINE std::unordered_set<Types::SafePtr<GameObject>>& GetChildrenRef() { return this->m_children; }
        [[nodiscard]] SR_INLINE std::unordered_set<Types::SafePtr<GameObject>> GetChildren() const { return this->m_children; }

        [[nodiscard]] Xml::Document Save() const override;

        Math::FVector3 GetBarycenter();
        Math::FVector3 GetHierarchyBarycenter();

        void ForEachComponent(const std::function<bool(Component*)>& fun);
        void ForEachChild(const std::function<void(Types::SafePtr<GameObject>)>& fun);
        void SetParent(const GameObject::Ptr& parent);
        void SetName(const std::string& name);
        void SetNameFromInspector(const std::string& name);
        /** \brief Get first needed component */
        Component* GetComponent(const std::string& name);
        std::vector<Component*> GetComponents(const std::string& name);
        std::vector<Component*> GetComponents();
        bool AddComponent(Component* component);
        bool RemoveComponent(Component* component);

        bool Contains(const Types::SafePtr<GameObject>& child);
        bool ContainsComponent(const std::string& name);
        void SetSelect(bool value);
        void SetActive(bool value);
        void Destroy(DestroyBy by = DestroyBy::Other);

        bool AddChild(const GameObject::Ptr& child);
        bool IsChild(const GameObject::Ptr& child);
        void RemoveChild(const GameObject::Ptr& child);

    private:
        void UpdateComponents();
        void UpdateComponentsPosition();
        void UpdateComponentsRotation();
        void UpdateComponentsScale();
        void UpdateComponentsSkew();

        void Free();
        void OnPrentSetActive(bool value);
        void UpdateComponentsEnabled();
        void UpdateEntityPath();

    private:
        std::atomic<bool>                   m_isActive       = true;
        std::atomic<bool>                   m_isParentActive = true;

        std::atomic<bool>                   m_isPrefab       = false;

        std::atomic<bool>                   m_isSelect       = false;
        GameObject::Ptr                     m_parent         = GameObject::Ptr();
        std::unordered_set<GameObject::Ptr> m_children       = std::unordered_set<GameObject::Ptr>();

        std::atomic<bool>                   m_isDestroy      = false;

        Types::SafePtr<World::Scene>        m_scene          = Types::SafePtr<World::Scene>();
        Transform*                          m_transform      = nullptr;

        std::vector<Component*>             m_components     = std::vector<Component*>();

        std::string                         m_name           = "Unnamed";
        std::string                         m_tag            = "None";

    };
}

#endif //GAMEENGINE_GAMEOBJECT_H
