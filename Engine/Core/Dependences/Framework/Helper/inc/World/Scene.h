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
#include <macros.h>
#include "EntityComponentSystem/GameObject.h"
#include <World/Observer.h>
#include <Debug.h>
#include <atomic>
#include <stack>
#include <unordered_set>
#include <Types/SafePointer.h>
#include <Types/StringAtom.h>

namespace Framework::Helper::World {
    class Region;
    class Chunk;

    typedef std::unordered_map<GameObject::Ptr, Chunk*> GameObjectPairs;
    typedef std::unordered_set<GameObject::Ptr> GameObjects;
    typedef std::unordered_map<Math::IVector2, Region*> Regions;

    class Scene : public Types::SafePtr<Scene> {
    public:
        typedef Types::SafePtr<Scene> Ptr;
        typedef std::function<Scene*(const std::string& name)> Allocator;

    protected:
        explicit Scene(const std::string& name);
        virtual ~Scene() = default;

    public:
        static Types::SafePtr<Scene> New(const std::string& name);
        static Types::SafePtr<Scene> Load(const std::string& name);
        static void SetAllocator(const Allocator& allocator) { g_allocator = allocator; }

        bool Save(const std::string& folder);
        bool Destroy();
        bool Free();
        void Update(float_t dt);

    public:
        virtual void BeginSync() = 0;
        virtual void EndSync() = 0;
        virtual bool TrySync() = 0;

        void SetObserver(const GameObject::Ptr& observer) { m_observer->m_target = observer; }

        [[nodiscard]] Observer* GetObserver() const { return m_observer; }
        Chunk* GetCurrentChunk() const;
        void SetWorldOffset(const World::Offset& offset);
        Types::SafePtr<GameObject> GetSelected() const;
        void ForEachRootObjects(const std::function<void(Types::SafePtr<GameObject>)>& fun);

        [[nodiscard]] SR_FORCE_INLINE std::string GetName() const { return m_name; }
        SR_FORCE_INLINE void SetName(const std::string& name) { m_name = name; }

        GameObjects GetGameObjects();
        GameObjects& GetRootGameObjects();

        GameObject::Ptr FindByComponent(const std::string& name);
        GameObject::Ptr Instance(const std::string& name);

    public:
        void DeSelectAll();
        bool Remove(const Types::SafePtr<GameObject>& gameObject);
        bool RemoveSelected(const Types::SafePtr<GameObject>& gameObject);
        void AddSelected(const Types::SafePtr<GameObject>& gameObject);

        void OnChanged();

    private:
        void CheckShift(const Math::IVector3& chunk);
        void UpdateContainers();
        void UpdateScope();
        bool ReloadConfig();

    private:
        SR_INLINE static Allocator   g_allocator           = Allocator();

        bool                         m_updateContainer     = false;
        bool                         m_shiftEnabled        = false;
        bool                         m_scopeEnabled        = false;
        bool                         m_isDestroy           = false;
        std::atomic<bool>            m_isHierarchyChanged  = false;

        StringAtom                   m_name                = "Unnamed";

        GameObjectPairs              m_gameObjectPairs     = GameObjectPairs();
        GameObjects                  m_gameObjects         = GameObjects();
        GameObjects                  m_selectedGameObjects = GameObjects();
        GameObjects                  m_rootObjects         = GameObjects();

        Regions                      m_regions             = Regions();
        Math::IVector2               m_chunkSize           = Math::IVector2(0, 0);
        uint32_t                     m_regionWidth         = 0;

        Observer*                    m_observer            = nullptr;

    };
}

#endif //GAMEENGINE_SCENE_H
