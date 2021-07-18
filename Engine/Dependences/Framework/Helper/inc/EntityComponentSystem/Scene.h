//
// Created by Nikita on 30.11.2020.
//

#ifndef GAMEENGINE_SCENE_H
#define GAMEENGINE_SCENE_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include "GameObject.h"
#include <Debug.h>
#include <stack>
#include <set>

namespace Framework::Helper {
    class Scene {
    private:
        Scene()  = default;
        ~Scene() = default;
    public:
        static Scene* New(const std::string& name);
        static Scene* Load(const std::string& name);
        bool Destroy();
        bool Free();
    private:
        bool                     m_hierarchyIsChanged   = false;
        bool                     m_isDestroy            = false;
        std::mutex               m_mutex                = std::mutex();
        std::string              m_name                 = "Unnamed";
        std::set<GameObject*>    m_gameObjects          = std::set<GameObject*>();
        uint32_t                 m_countUses            = 0;

        std::vector<GameObject*> m_selectedGameObjects  = std::vector<GameObject*>();
        std::mutex               m_selectedMutex        = std::mutex();
        uint32_t                 m_countSelected        = 0;

        std::vector<GameObject*> m_rootObjects          = std::vector<GameObject*>();
        bool                     m_rootObjectsEmpty     = true;
    public:
        [[nodiscard]] inline std::string GetName() const noexcept { return m_name; }
        inline std::vector<GameObject*> GetGameObjects() { // TODO: OPTIMIZE
            m_mutex.lock();

            std::vector<GameObject*> v = std::vector<GameObject*>();
            v.reserve(m_gameObjects.size());

            for (auto& a : m_gameObjects)
                v.push_back(a);

            m_mutex.unlock();

            return v;
        }

        std::vector<GameObject*>& GetRootGameObjects() noexcept;

        [[nodiscard]] inline uint32_t GetCountUsesPoints() const noexcept { return this->m_countUses; }

        inline void SetIsChanged(bool value) noexcept { this->m_hierarchyIsChanged = value; }
        [[nodiscard]] inline bool IsChanged() const noexcept { return this->m_hierarchyIsChanged; }

        inline void AddUsePoint() noexcept {
            m_countUses++;
        }
        inline bool RemoveUsePoint() noexcept {
            if (m_countUses == 0) {
                Helper::Debug::Error("Scene::RemoveUsePoint() : count uses points is equal zero! Something went wrong...");
                return false;
            }

            m_countUses--;

            return true;
        }
    public:
        [[nodiscard]] inline std::vector<GameObject*> GetSelected() const noexcept {
            if (m_countSelected == 0)
                return { };
            else
                return this->m_selectedGameObjects;
        }
        void UnselectAll();
        bool RemoveSelected(GameObject* gameObject);
        void AddSelected(GameObject* gameObject);
    public:
        GameObject* Instance(const std::string& name);
        //bool RemoveGameObject(const GameObject* gameObject);
        //bool DestroyGameObject(GameObject* gameObject);
    };
}

#endif //GAMEENGINE_SCENE_H
