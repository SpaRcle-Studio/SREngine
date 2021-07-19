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

namespace Framework {
    class API;
}

namespace Framework::Helper {
    class Transform;
    class Scene;
    class Component;
    class GameObject {
        friend class Scene;
        friend class Transform;
        friend class ::Framework::API;
    private:
        GameObject(Scene* scene, std::string name, std::string tag = "Untagged");
        ~GameObject();
    private:
        void UpdateComponents();
        void UpdateComponentsPosition();
        void UpdateComponentsRotation();
        void UpdateComponentsScale();
    private:
        void Destroy();
    public:
        [[nodiscard]] Scene* GetScene() const noexcept { return this->m_scene; }
        Transform* GetTransform() noexcept { return this->m_transform; }
    public:
        void SetParent(GameObject* gm);
        void RemoveParent(GameObject* gm);
        void SetName(const std::string& name);
        void SetNameFromInspector(const std::string& name);
        /** \brief Get first needed component */
        Component* GetComponent(const std::string& name);
        std::vector<Component*> GetComponents(const std::string& name);
        std::vector<Component*> GetComponents();
        bool AddComponent(Component* component);
        bool AddChild(GameObject* child);
        //TODO: Add remove child
        [[nodiscard]] inline std::vector<GameObject*> GetChildren() const noexcept { return this->m_children; }
        [[nodiscard]] inline std::vector<GameObject*>& GetChildrenRef() noexcept { return this->m_children; }
        [[nodiscard]] inline GameObject* GetParent() const noexcept { return this->m_parent; }
        [[nodiscard]] std::string GetName() noexcept;
        [[nodiscard]] inline bool HasChildren() const noexcept { return m_countChild > 0; }
        [[nodiscard]] inline bool IsSelect() const noexcept { return this->m_isSelect; }
        bool Contains(GameObject* child);
        bool ContainsComponent(const std::string& name);
        void SetSelect(bool value);
    private:
        bool                     m_isSelect      = false;
        GameObject*              m_parent        = nullptr;
        std::vector<GameObject*> m_children      = std::vector<GameObject*>();
        uint32_t                 m_countChild    = 0;

        bool                     m_isDestroy     = false;

        std::mutex               m_mutex         = std::mutex();

        Scene*                   m_scene         = nullptr;
        Transform*               m_transform     = nullptr;

        std::vector<Component*>  m_components    = std::vector<Component*>();

        std::string              m_name          = "Unnamed";
        std::string              m_tag           = "None";
    };
}

#endif //GAMEENGINE_GAMEOBJECT_H
