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

namespace Framework::Helper {
    template<typename T> class Branch {
    private:
        ~Branch() {
            for (auto a : m_branches)
                a->Free();
        };
    public:
        inline void Free() {
            delete this;
        };
        inline void AddChild(Branch<T>* child) {
            this->m_branches.push_back(child);
        }
    public:
        explicit Branch(T data) {
            this->m_data = data;
        };
        Branch(T data, Branch<T>* parent) {
            this->m_parent = parent;
            this->m_parent->m_branches.push_back(this);
            this->m_data = data;
        }
    public:
        Branch<T>*              m_parent   = nullptr;
        std::vector<Branch<T>*> m_branches = std::vector<Branch<T>*>();
        T                       m_data     = nullptr;
    };

    typedef Branch<GameObject*>* SceneTree;

    class GameObject;
    class Scene {
    private:
        Scene();
        ~Scene();
    public:
        static Scene* New(std::string name);
        static Scene* Load(const std::string& name);
        bool Destroy();
        bool Free();
    private:
        bool                                m_hierarchyIsChanged   = false;
        bool                                m_isDestroy            = false;
        std::mutex                          m_mutex                = std::mutex();
        std::string                         m_name                 = "Unnamed";
        std::map<GameObject*, GameObject*>  m_gameObjects          = std::map<GameObject*, GameObject*>();
        unsigned int                        m_countUses            = 0;
        Branch<GameObject*>*                m_tree                 = nullptr;
    public:
        void Print();
        inline std::vector<GameObject*> GetGameObjects() { // TODO: OPTIMIZE
            m_mutex.lock();

            std::vector<GameObject*> v = std::vector<GameObject*>();
            v.reserve(m_gameObjects.size());

            for (auto& a : m_gameObjects)
                v.push_back(a.second);

            m_mutex.unlock();

            return v;
        }
        Branch<GameObject*>* GetTree();

        [[nodiscard]] inline unsigned int GetCountUsesPoints() const noexcept { return this->m_countUses; }

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
        GameObject* Instance(std::string name);
        bool DestroyGameObject(GameObject* gameObject);
    };
}

#endif //GAMEENGINE_SCENE_H
