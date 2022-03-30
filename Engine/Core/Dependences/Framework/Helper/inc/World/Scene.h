//
// Created by Nikita on 30.11.2020.
//

#ifndef GAMEENGINE_SCENE_H
#define GAMEENGINE_SCENE_H

#include <Types/SafePointer.h>
#include <World/Observer.h>
#include <Types/StringAtom.h>

namespace SR_UTILS_NS::World {
    struct TensorKey {
        TensorKey() = default;
        TensorKey(const Framework::Helper::Math::IVector3& _region, const Framework::Helper::Math::IVector3& _chunk)
            : region(_region)
            , chunk(_chunk)
        { }

        Framework::Helper::Math::IVector3 region;
        Framework::Helper::Math::IVector3 chunk;

        bool operator==(const TensorKey &other) const {
            return region == other.region && chunk == other.chunk;
        }
    };
}

namespace std {
    template<> struct hash<Framework::Helper::World::TensorKey> {
        size_t operator()(Framework::Helper::World::TensorKey const& vecPair) const {
            std::size_t res = 0;

            std::hash<Framework::Helper::Math::IVector3> hFirst;
            std::hash<Framework::Helper::Math::IVector3> hSecond;

            res ^= hFirst(vecPair.region) + 0x9e3779b9 + (res << 6u) + (res >> 2u);
            res ^= hSecond(vecPair.chunk) + 0x9e3779b9 + (res << 6u) + (res >> 2u);

            return res;
        }
    };
}

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_UTILS_NS::World {
    class Region;
    class Chunk;

    typedef std::unordered_set<Types::SafePtr<GameObject>> GameObjects;
    typedef std::unordered_map<TensorKey, GameObjects> Tensor;
    typedef std::unordered_map<Math::IVector3, Region*> Regions;

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

        bool Save();
        bool SaveAt(const std::string& folder);
        bool Destroy();
        bool Free();
        void Update(float_t dt);

    public:
        virtual void BeginSync() = 0;
        virtual void EndSync() = 0;
        virtual bool TrySync() = 0;
        virtual Types::SafePtr<GameObject> Instance(const MarshalDecodeNode& node) = 0;

        void SetObserver(const Types::SafePtr<GameObject>& observer) { m_observer->m_target = observer; }

        SR_NODISCARD Observer* GetObserver() const { return m_observer; }
        Chunk* GetCurrentChunk() const;
        void SetWorldOffset(const World::Offset& offset);
        void ForEachRootObjects(const std::function<void(Types::SafePtr<GameObject>)>& fun);

        SR_NODISCARD Path GetRegionsPath() const { return m_path.Concat(m_name.ToString()).Concat("regions"); }
        SR_NODISCARD Path GetPath() const { return m_path; }
        SR_NODISCARD std::string GetName() const { return m_name; }
        void SetName(const std::string& name) { m_name = name; }

        GameObjects GetGameObjects();
        GameObjects& GetRootGameObjects();
        GameObjects GetGameObjectsAtChunk(const Math::IVector3& region, const Math::IVector3& chunk);

        Types::SafePtr<GameObject> FindByComponent(const std::string& name);
        Types::SafePtr<GameObject> Instance(const std::string& name);

    public:
        bool Remove(const Types::SafePtr<GameObject>& gameObject);

        void OnChanged();

        bool ReloadConfig();
        void ReloadChunks();

    private:
        void CheckShift(const Math::IVector3& chunk);
        void UpdateContainers();
        void UpdateScope(float_t dt);
        void SaveRegion(Region* pRegion) const;

    private:
        SR_INLINE static Allocator   g_allocator           = Allocator();

        bool                         m_updateContainer     = false;
        bool                         m_shiftEnabled        = false;
        bool                         m_scopeEnabled        = false;
        bool                         m_isDestroy           = false;
        std::atomic<bool>            m_isHierarchyChanged  = false;

        StringAtom                   m_name                = "Unnamed";
        Path                         m_path                = Path();

        World::Tensor                m_tensor              = World::Tensor();

        GameObjects                  m_gameObjects         = GameObjects();
        GameObjects                  m_rootObjects         = GameObjects();

        Regions                      m_regions             = Regions();
        Math::IVector2               m_chunkSize           = Math::IVector2();
        uint32_t                     m_regionWidth         = 0;

        Observer*                    m_observer            = nullptr;

    };
}

#endif //GAMEENGINE_SCENE_H
