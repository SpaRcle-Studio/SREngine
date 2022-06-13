//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <ECS/EntityManager.h>

#include <Math/Vector3.h>
#include <Types/SafePointer.h>

namespace SR_UTILS_NS::World {
    class Scene;
}

namespace SR_UTILS_NS {
    class Transform3D;
    class Component;

    class GameObject : public Types::SafePtr<GameObject>, public Entity {
        friend class World::Scene;
        friend class Transform3D;
        friend class Component;

        typedef enum {
            DestroyBy_Unknown    = 0,
            DestroyBy_Scene      = 1 << 0,
            DestroyBy_GameObject = 1 << 1,
            DestroyBy_Other      = 1 << 2,
            DestroyBy_Command    = 1 << 3
        } DestroyByFlag;

        typedef uint64_t DestroyByFlagBits;

    public:
        typedef Types::SafePtr<GameObject> Ptr;
        static const uint16_t VERSION;

    private:
        GameObject(const Types::SafePtr<World::Scene>& scene, std::string name, std::string tag = "Untagged");
        ~GameObject() override;

    public:
        SR_NODISCARD Types::SafePtr<World::Scene> GetScene() const { return m_scene; }
        SR_NODISCARD Transform3D* GetTransform() const { return m_transform; }
        SR_NODISCARD GameObject::Ptr GetParent() const { return m_parent; }
        SR_NODISCARD std::string GetName() const;
        SR_NODISCARD bool IsActive() const;
        SR_NODISCARD bool IsEnabled() const { return m_isEnabled; }
        SR_NODISCARD SR_INLINE bool HasChildren() const { return !m_children.empty(); }
        SR_NODISCARD SR_INLINE std::unordered_set<Types::SafePtr<GameObject>>& GetChildrenRef() { return m_children; }
        SR_NODISCARD SR_INLINE std::unordered_set<Types::SafePtr<GameObject>> GetChildren() const { return m_children; }

        SR_NODISCARD SR_HTYPES_NS::Marshal Save(SavableFlags flags) const override;
        SR_NODISCARD std::list<EntityBranch> GetEntityBranches() const override;

        Math::FVector3 GetBarycenter();
        Math::FVector3 GetHierarchyBarycenter();

        void ForEachChild(const std::function<void(Types::SafePtr<GameObject>&)>& fun);
        void ForEachChild(const std::function<void(const Types::SafePtr<GameObject>&)>& fun) const;
        bool SetParent(const GameObject::Ptr& parent);
        void SetName(const std::string& name);

        Component* GetComponent(const std::string& name);
        Component* GetComponent(size_t id);
        std::list<Component*> GetComponents() { return m_components; }
        bool AddComponent(Component* component);
        bool RemoveComponent(Component* component);
        bool ContainsComponent(const std::string& name);
        void ForEachComponent(const std::function<bool(Component*)>& fun);

        bool Contains(const Types::SafePtr<GameObject>& child);
        void SetEnabled(bool value);
        void Destroy(DestroyByFlagBits by = DestroyBy_Other);
        void SetTransform(Transform3D* transform3D);

        bool MoveToTree(const GameObject::Ptr& destination);
        bool AddChild(const GameObject::Ptr& child);
        bool IsChild(const GameObject::Ptr& child);
        void RemoveChild(const GameObject::Ptr& child);

    public:
        template<typename T> T* GetComponent() {
            return dynamic_cast<T*>(GetComponent(typeid(T).hash_code()));
        }

    private:
        void UpdateComponents();
        void UpdateComponentsPosition();
        void UpdateComponentsRotation();
        void UpdateComponentsScale();
        void UpdateComponentsSkew();

        /// TODO: remove this method
        void Free();

        bool UpdateEntityPath();

        void CheckActivity();

    private:
        std::atomic<bool>                   m_isEnabled      = true;
        std::atomic<bool>                   m_isActive       = true;

        std::atomic<bool>                   m_isDestroy      = false;

        GameObject::Ptr                     m_parent         = GameObject::Ptr();
        std::unordered_set<GameObject::Ptr> m_children       = std::unordered_set<GameObject::Ptr>();


        Types::SafePtr<World::Scene>        m_scene          = Types::SafePtr<World::Scene>();
        Transform3D*                        m_transform      = nullptr;

        std::list<Component*>               m_components     = std::list<Component*>();

        std::string                         m_name           = "Unnamed";
        std::string                         m_tag            = "None";

    };
}

#endif //GAMEENGINE_GAMEOBJECT_H
