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
#include <Types/SafePointer.h>

namespace Framework::Helper {
    class Scene {
    private:
        Scene(const std::string& name) {
            m_name = name;
        }
        ~Scene() = default;
    public:
        static Types::SafePtr<Scene> New(const std::string& name);
        static Types::SafePtr<Scene> Load(const std::string& name);
        bool Destroy();
        bool Free();
    private:
        Types::SafePtr<Scene>                   m_this                = Types::SafePtr<Scene>();

        bool                                    m_isDestroy           = false;
        bool                                    m_isHierarchyChanged  = false;

        std::mutex                              m_mutex               = std::mutex();
        std::mutex                              m_displayListMutex    = std::mutex();
        std::mutex                              m_selectedMutex       = std::mutex();

        std::string                             m_name                = "Unnamed";
        std::set<Types::SafePtr<GameObject>>    m_gameObjects         = std::set<Types::SafePtr<GameObject>>();

        std::set<Types::SafePtr<GameObject>>    m_selectedGameObjects = std::set<Types::SafePtr<GameObject>>();

        std::vector<Types::SafePtr<GameObject>> m_rootObjects         = std::vector<Types::SafePtr<GameObject>>();
        bool                                    m_displayListEnabled  = true;
    public:
        void SetThis(const Types::SafePtr<Scene>& _this) {
            m_this = _this;
        }
        Types::SafePtr<GameObject> GetSelected() {
            if (auto size = m_selectedGameObjects.size(); size == 0 || size > 1)
                return Types::SafePtr<GameObject>();
            else {
                m_selectedMutex.lock();
                auto gameObject = *m_selectedGameObjects.begin();
                m_selectedMutex.unlock();
                return gameObject;
            }
        }
        void ForEachRootObjects(const std::function<void(Types::SafePtr<GameObject>)>& fun);
        [[nodiscard]] inline std::string GetName() const noexcept { return m_name; }
        inline std::vector<Types::SafePtr<GameObject>> GetGameObjects() { // TODO: OPTIMIZE
            m_mutex.lock();

            auto v = std::vector<Types::SafePtr<GameObject>>();
            v.reserve(m_gameObjects.size());

            for (auto& a : m_gameObjects)
                v.push_back(a);

            m_mutex.unlock();

            return v;
        }

        std::vector<Types::SafePtr<GameObject>>& GetRootGameObjects() noexcept;
    public:
        void UnselectAll();
        bool RemoveSelected(const Types::SafePtr<GameObject>& gameObject);
        void AddSelected(const Types::SafePtr<GameObject>& gameObject);
        void OnGameObjectNameChanged();
    public:
        Types::SafePtr<GameObject> FindByComponent(const std::string& name);
        Types::SafePtr<GameObject> Instance(const std::string& name);
        //bool RemoveGameObject(const GameObject* gameObject);
        //bool DestroyGameObject(GameObject* gameObject);
    };
}

#endif //GAMEENGINE_SCENE_H
