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
            //m_hasBranches = true;
            this->m_count++;
        }
        [[nodiscard]] inline bool HasBranches() const noexcept { return m_count > 0; }
        [[nodiscard]] inline unsigned long GetCountBranches() const noexcept { return m_count; }
    public:
        explicit Branch(T data) {
            this->m_data = data;
        };
        Branch(T data, Branch<T>* parent) {
            this->m_parent = parent;
            this->m_parent->m_branches.push_back(this);
            this->m_data = data;
        }
    private:
        //bool                    m_hasBranches   = false;
        unsigned long           m_count         = 0;
        Branch<T>*              m_parent        = nullptr;
    public:
        std::vector<Branch<T>*> m_branches      = std::vector<Branch<T>*>();
        T                       m_data          = nullptr;
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

        std::vector<GameObject*>            m_selectedGameObjects  = std::vector<GameObject*>();
        std::mutex                          m_selectedMutex        = std::mutex();
        size_t                              m_countSelected        = 0;

        std::vector<GameObject*>            m_rootObjects          = std::vector<GameObject*>();
        bool                                m_rootObjectsEmpty     = true;
    public:
        void Print();
        [[nodiscard]] inline std::string GetName() const noexcept { return m_name; }
        inline std::vector<GameObject*> GetGameObjects() { // TODO: OPTIMIZE
            m_mutex.lock();

            std::vector<GameObject*> v = std::vector<GameObject*>();
            v.reserve(m_gameObjects.size());

            for (auto& a : m_gameObjects)
                v.push_back(a.second);

            m_mutex.unlock();

            return v;
        }
        //Branch<GameObject*>* GetTree();


        std::vector<GameObject*>& GetRootGameObjects() noexcept;

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
        [[nodiscard]] inline GameObject* GetSelected() const noexcept {
            if (m_countSelected == 0 || m_countSelected > 1)
                return nullptr;
            else
                return this->m_selectedGameObjects[0];
        }
        inline void UnselectAll() {
            m_selectedMutex.lock();

            for (auto a : m_selectedGameObjects)
                a->m_isSelect = false;

            this->m_countSelected = 0;
            this->m_selectedGameObjects.clear();

            m_selectedMutex.unlock();
        }
        inline bool RemoveSelected(GameObject* gameObject) {
            m_selectedMutex.lock();

            bool found = false;

            for (size_t t = 0; t < m_selectedGameObjects.size(); t++)
                if (gameObject == m_selectedGameObjects[t]){
                    this->m_countSelected--;
                    m_selectedGameObjects.erase(m_selectedGameObjects.begin() + t);
                    found = true;
                    break;
                }

            if (!found)
                Helper::Debug::Error("Scene::RemoveSelected() : \""+gameObject->GetName() + "\" not found!");

            m_selectedMutex.unlock();

            return found;
        }
        inline void AddSelected(GameObject* gameObject) {
            m_selectedMutex.lock();

            this->m_selectedGameObjects.push_back(gameObject);
            this->m_countSelected++;

            m_selectedMutex.unlock();
        }
    public:
        GameObject* Instance(std::string name);
        bool DestroyGameObject(GameObject* gameObject);
    };
}

#endif //GAMEENGINE_SCENE_H
