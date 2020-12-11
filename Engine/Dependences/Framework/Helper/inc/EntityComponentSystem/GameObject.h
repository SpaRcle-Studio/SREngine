//
// Created by Nikita on 27.11.2020.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include <string>
#include <vector>
#include <mutex>

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
        void Destroy();
    public:
        Transform* GetTransform() noexcept { return this->m_transform; }
    public:
        /** \brief Get first needed component */
        Component* GetComponent(std::string name);
        std::vector<Component*> GetComponents(std::string name);
        bool AddComponent(Component* component);
    private:
        bool                        m_isDestroy     = false;

        std::mutex                  m_mutex         = std::mutex();

        Scene*                      m_scene         = nullptr;
        Transform*                  m_transform     = nullptr;

        std::vector<GameObject*>    m_children      = std::vector<GameObject*>();
        std::vector<Component*>     m_components    = std::vector<Component*>();

        std::string                 m_name          = "Unnamed";
        std::string                 m_tag           = "None";
    };
}

#endif //GAMEENGINE_GAMEOBJECT_H
