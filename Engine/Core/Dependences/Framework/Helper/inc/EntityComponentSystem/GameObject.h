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

#include <EntityComponentSystem/ISavable.h>

namespace Framework {
    class API;
}

namespace Framework::Helper {
    namespace World {
        class Scene;
    };

    class Transform;
    class Component;
    class GameObject : public ISavable {
        friend class World::Scene;
        friend class Transform;
        friend class ::Framework::API;
    public:
        typedef Types::SafePtr<GameObject> Ptr;
    private:
        GameObject(const Types::SafePtr<World::Scene>& scene, std::string name, std::string tag = "Untagged");
        ~GameObject();
    private:
        void UpdateComponents();
        void UpdateComponentsPosition();
        void UpdateComponentsRotation();
        void UpdateComponentsScale();
    private:
        void DestroyFromScene();
        void Free();
    public:
        Xml::Document Save() override;
        bool Load(const Xml::Document& xml) override;
    public:
        [[nodiscard]] Types::SafePtr<World::Scene> GetScene() const noexcept { return this->m_scene; }
        Transform* GetTransform() const { return this->m_transform; }
    public:
        Math::FVector3 GetBarycenter();
        Math::FVector3 GetHierarchyBarycenter();

        void SetThis(const Types::SafePtr<GameObject>& _this) {
            m_this = _this;
        }
        void ForEachComponent(const std::function<bool(Component*)>& fun);
        void ForEachChild(const std::function<void(Types::SafePtr<GameObject>)>& fun);
        void SetParent(GameObject* gm);
        void RemoveParent(GameObject* gm);
        void SetName(const std::string& name);
        void SetNameFromInspector(const std::string& name);
        /** \brief Get first needed component */
        Component* GetComponent(const std::string& name);
        std::vector<Component*> GetComponents(const std::string& name);
        std::vector<Component*> GetComponents();
        bool AddComponent(Component* component);
        bool RemoveComponent(Component* component);
        bool AddChild(const Types::SafePtr<GameObject>& child);
        //TODO: Add remove child
        [[nodiscard]] inline std::vector<Types::SafePtr<GameObject>> GetChildren() const noexcept { return this->m_children; }
        [[nodiscard]] inline std::vector<Types::SafePtr<GameObject>>& GetChildrenRef() noexcept { return this->m_children; }
        [[nodiscard]] GameObject* GetParent() const noexcept { return this->m_parent; }
        [[nodiscard]] std::string GetName() noexcept;
        [[nodiscard]] inline bool HasChildren() const noexcept { return m_countChild > 0; }
        [[nodiscard]] inline bool IsSelect() const noexcept { return this->m_isSelect; }
        bool Contains(const Types::SafePtr<GameObject>& child);
        bool ContainsComponent(const std::string& name);
        [[nodiscard]] bool IsActive() const { return m_isActive && m_isParentActive; }
        void SetSelect(bool value);
        void SetActive(bool value);
    private:
        void OnPrentSetActive(bool value);
        void UpdateComponentsEnabled();
    private:
        Types::SafePtr<GameObject>              m_this           = Types::SafePtr<GameObject>();

        bool                                    m_isActive       = true;
        bool                                    m_isParentActive = true;

        bool                                    m_isPrefab       = false;

        bool                                    m_isSelect       = false;
        GameObject*                             m_parent         = nullptr;
        std::vector<Types::SafePtr<GameObject>> m_children       = std::vector<Types::SafePtr<GameObject>>();
        uint32_t                                m_countChild     = 0;

        bool                                    m_isDestroy      = false;

        std::recursive_mutex                    m_mutex          = std::recursive_mutex();

        Types::SafePtr<World::Scene>            m_scene          = Types::SafePtr<World::Scene>();
        Transform*                              m_transform      = nullptr;

        std::vector<Component*>                 m_components     = std::vector<Component*>();

        std::string                             m_name           = "Unnamed";
        std::string                             m_tag            = "None";
    };
}

#endif //GAMEENGINE_GAMEOBJECT_H
