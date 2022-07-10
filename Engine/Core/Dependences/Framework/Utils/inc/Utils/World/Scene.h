//
// Created by Nikita on 30.11.2020.
//

#ifndef GAMEENGINE_SCENE_H
#define GAMEENGINE_SCENE_H

#include <Utils/Types/SafePointer.h>
#include <Utils/World/Observer.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Types/Marshal.h>
#include <Utils/World/CameraData.h>

namespace SR_WORLD_NS {
    struct SR_DLL_EXPORT TensorKey {
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

    namespace Types {
        class RawMesh;
    }
}

namespace SR_WORLD_NS {
    class Region;
    class Chunk;

    typedef std::unordered_set<Types::SafePtr<GameObject>> GameObjects;
    typedef std::unordered_map<TensorKey, GameObjects> Tensor;
    typedef std::unordered_map<Math::IVector3, Region*> Regions;

    class SR_DLL_EXPORT SceneAllocator : public SR_UTILS_NS::Singleton<SceneAllocator> {
        friend class SR_UTILS_NS::Singleton<SceneAllocator>;
        typedef std::function<Scene*(void)> Allocator;
        using ScenePtr = Types::SafePtr<Scene>;
    protected:
        ~SceneAllocator() override = default;

    public:
        bool Init(const Allocator& allocator);
        ScenePtr Allocate();

    private:
        Allocator m_allocator;

    };

    class SR_DLL_EXPORT Scene : public Types::SafePtr<Scene> {
    public:
        typedef Types::SafePtr<Scene> Ptr;
        using Super = Types::SafePtr<Scene>;

    protected:
        Scene();
        explicit Scene(const std::string& name);
        virtual ~Scene() = default;

    public:
        static Types::SafePtr<Scene> New(const Path& path);
        static Types::SafePtr<Scene> Load(const Path& path);

        bool Save();
        bool SaveAt(const Path& path);
        bool Destroy();
        bool Free();
        void Update(float_t dt);
        void RunScene();
        void StopScene();

    public:
        void SetWorldOffset(const World::Offset& offset);
        void ForEachRootObjects(const std::function<void(Types::SafePtr<GameObject>)>& fun);
        void SetName(const std::string& name) { m_name = name; }
        void SetPath(const Path& path) { m_path = path; }
        void SetActive(bool value) { m_isActive = value; }
        void SetPaused(bool value) { m_isPaused = value; }

        SR_NODISCARD Path GetRegionsPath() const { return m_path.Concat("regions"); }
        SR_NODISCARD Path GetPath() const { return m_path; }
        SR_NODISCARD std::string GetName() const { return m_name; }
        SR_NODISCARD Observer* GetObserver() const { return m_observer; }
        SR_NODISCARD bool IsPaused() const { return m_isPaused; }
        SR_NODISCARD bool IsActive() const { return m_isActive; }

        GameObjects& GetRootGameObjects();
        GameObjects GetGameObjectsAtChunk(const Math::IVector3& region, const Math::IVector3& chunk);
        Chunk* GetCurrentChunk() const;

        Types::SafePtr<GameObject> FindByComponent(const std::string& name);
        Types::SafePtr<GameObject> Find(const std::string& name);

        virtual SR_HTYPES_NS::SafePtr<GameObject> InstanceFromFile(const std::string& path);
        virtual SR_HTYPES_NS::SafePtr<GameObject> Instance(const std::string& name);
        virtual SR_HTYPES_NS::SafePtr<GameObject> Instance(const Types::RawMesh* rawMesh);
        virtual SR_HTYPES_NS::SafePtr<GameObject> Instance(SR_HTYPES_NS::Marshal& marshal) = 0;

    public:
        bool Remove(const Types::SafePtr<GameObject>& gameObject);

        void OnChanged();

        bool Reload();
        bool ReloadConfig();
        bool ReloadChunks();

        void UpdateTree();

    private:
        virtual void FindObserver() { }
        void CheckShift(const Math::IVector3& chunk);
        void UpdateContainers();
        void UpdateScope(float_t dt);
        void SaveRegion(Region* pRegion) const;

    protected:
        Observer*                    m_observer            = nullptr;

    private:
        bool                         m_updateContainer     = false;
        bool                         m_shiftEnabled        = false;
        bool                         m_scopeEnabled        = false;
        bool                         m_isDestroy           = false;

        std::atomic<bool>            m_isHierarchyChanged  = false;
        std::atomic<bool>            m_isActive            = false;
        std::atomic<bool>            m_isPaused            = false;

        StringAtom                   m_name                = "Unnamed";
        Path                         m_path                = Path();

        World::Tensor                m_tensor              = World::Tensor();

        GameObjects                  m_gameObjects         = GameObjects();
        GameObjects                  m_rootObjects         = GameObjects();

        Regions                      m_regions             = Regions();
        Math::IVector2               m_chunkSize           = Math::IVector2();
        uint32_t                     m_regionWidth         = 0;

    };
}

#endif //GAMEENGINE_SCENE_H