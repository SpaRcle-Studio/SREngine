//
// Created by Nikita on 30.11.2020.
//

#ifndef GAMEENGINE_SCENE_H
#define GAMEENGINE_SCENE_H

#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/World/Observer.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Types/Marshal.h>
#include <Utils/World/CameraData.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/World/TensorKey.h>

namespace SR_UTILS_NS {
    class GameObject;

    namespace Types {
        class RawMesh;
    }
}

namespace SR_WORLD_NS {
    class SR_DLL_EXPORT Scene : public Types::SafePtr<Scene> {
    public:
        typedef Types::SafePtr<Scene> Ptr;
        using Super = Ptr;
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;
        using GameObjects = std::vector<GameObjectPtr>;

        virtual ~Scene();

    protected:
        Scene();
        explicit Scene(const std::string& name);

    public:
        static Scene::Ptr New(const Path& path);
        static Scene::Ptr Load(const Path& path);

        bool Save();
        bool SaveAt(const Path& path);
        bool Destroy();
        void Update(float_t dt);

    public:
        void SetWorldOffset(const World::Offset& offset);
        void SetName(const std::string& name) { m_name = name; }
        void SetPath(const Path& path) { m_path = path; }
        void SetObserver(const GameObjectPtr& target);

        SR_NODISCARD Path GetRegionsPath() const { return m_path.Concat("regions"); }
        SR_NODISCARD Path GetPath() const { return m_path; }
        SR_NODISCARD std::string GetName() const { return m_name; }
        SR_NODISCARD Observer* GetObserver() const { return m_observer; }
        SR_NODISCARD SR_HTYPES_NS::DataStorage& GetDataStorage() { return m_dataStorage; }
        SR_NODISCARD const SR_HTYPES_NS::DataStorage& GetDataStorage() const { return m_dataStorage; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetWorldPosition(const SR_MATH_NS::IVector3& region, const SR_MATH_NS::IVector3& chunk);

        SR_NODISCARD Region* GetRegion(const SR_MATH_NS::IVector3& region);

        GameObjects& GetRootGameObjects();
        GameObjects GetGameObjectsAtChunk(const SR_MATH_NS::IVector3& region, const SR_MATH_NS::IVector3& chunk);
        Chunk* GetCurrentChunk() const;

        GameObjectPtr FindByComponent(const std::string& name);
        GameObjectPtr Find(const std::string& name);

        virtual GameObjectPtr InstanceFromFile(const std::string& path);
        virtual GameObjectPtr FindOrInstance(const std::string& name);
        virtual GameObjectPtr Instance(const std::string& name);
        virtual GameObjectPtr Instance(const Types::RawMesh* rawMesh);
        virtual GameObjectPtr Instance(SR_HTYPES_NS::Marshal& marshal) = 0;

        virtual bool ScopeCheckFunction(int32_t x, int32_t y, int32_t z) const;

    public:
        bool Remove(const GameObjectPtr& gameObject);

        void OnChanged();

        bool Reload();
        bool ReloadConfig();
        bool ReloadChunks();

    private:
        void CheckShift(const SR_MATH_NS::IVector3& chunk);
        void UpdateContainers();
        void UpdateScope(float_t dt);
        void SaveRegion(Region* pRegion) const;

    protected:
        Observer*                 m_observer           = nullptr;

    private:
        bool                      m_updateContainer    = false;
        bool                      m_shiftEnabled       = false;
        bool                      m_scopeEnabled       = false;
        bool                      m_isDestroy          = false;

        std::atomic<bool>         m_isHierarchyChanged = false;

        StringAtom                m_name               = "Unnamed";
        Path                      m_path               = Path();

        World::Tensor             m_tensor             = World::Tensor();

        SR_HTYPES_NS::DataStorage m_dataStorage        = SR_HTYPES_NS::DataStorage();

        GameObjects               m_gameObjects        = GameObjects();
        GameObjects               m_rootObjects        = GameObjects();

        Regions                   m_regions            = Regions();
        Math::IVector2            m_chunkSize          = Math::IVector2();
        uint32_t                  m_regionWidth        = 0;

    };
}

#endif //GAMEENGINE_SCENE_H
