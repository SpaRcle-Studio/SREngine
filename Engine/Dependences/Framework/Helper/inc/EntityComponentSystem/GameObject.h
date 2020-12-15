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

namespace Framework::Helper {
    class Transform;
    class Scene;
    class Component;
    class GameObject {
        friend class Scene;
        friend class Transform;
    private:
        GameObject(Scene* scene, std::string name, std::string tag = "Untagged");
        ~GameObject();
    private:
        void UpdateComponentsPosition();
        void UpdateComponentsRotation();
        void UpdateComponentsScale();
    private:
        //void OnDestroyParent();

        void Destroy();
    public:
        Transform* GetTransform() noexcept { return this->m_transform; }
    public:
        nlohmann::json Save();
    public:
        /** \brief Get first needed component */
        Component* GetComponent(std::string name);
        std::vector<Component*> GetComponents(std::string name);
        bool AddComponent(Component* component);
        bool AddChild(GameObject* child);
    private:
        //std::vector<GameObject*>    m_children      = std::vector<GameObject*>();

        GameObject*                             m_parent        = nullptr;
        std::map<GameObject*, GameObject*>      m_children      = std::map<GameObject*, GameObject*>();

        bool                                    m_isDestroy     = false;

        std::mutex                              m_mutex         = std::mutex();

        Scene*                                  m_scene         = nullptr;
        Transform*                              m_transform     = nullptr;

        std::vector<Component*>                 m_components    = std::vector<Component*>();

        std::string                             m_name          = "Unnamed";
        std::string                             m_tag           = "None";
    };
}

#endif //GAMEENGINE_GAMEOBJECT_H
