

# File Scene.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**Scene.h**](Scene_8h.md)

[Go to the documentation of this file](Scene_8h.md)


```C++
//
// Created by Nikita on 30.11.2020.
//

#ifndef SR_ENGINE_SCENE_H
#define SR_ENGINE_SCENE_H

#include <Utils/ECS/IComponentable.h>

#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Types/Marshal.h>
#include <Utils/Types/DataStorage.h>

#include <Utils/World/TensorKey.h>
#include <Utils/World/Observer.h>
#include <Utils/World/SceneLogicType.h>
#include <Utils/World/CameraData.h>

namespace SR_UTILS_NS {
    class SceneObject;
    class Prefab;
}

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_WORLD_NS {
    class SceneLogic;
    class SceneUpdater;

    class SR_COMMON_DLL_API Scene : public SR_UTILS_NS::IComponentable {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Scene>;
        using SceneLogicPtr = SR_HTYPES_NS::SharedPtr<SceneLogic>;
        using Super = SR_UTILS_NS::IComponentable;
        using SceneObjectPtr = SR_HTYPES_NS::SharedPtr<SceneObject>;
        using SceneObjects = std::vector<SceneObjectPtr>;
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;

        SR_MAYBE_UNUSED SR_INLINE_STATIC const Path RuntimeScenePath = "Scenes/Runtime-cache-scene"; 
        SR_MAYBE_UNUSED SR_INLINE_STATIC const Path NewScenePath = "Scenes/New-cache-scene"; 
        SR_MAYBE_UNUSED SR_INLINE_STATIC const Path NewPrefabPath = "Scenes/New-cache-prefab"; 

    public:
        Scene();
        ~Scene() override;

    public:
        static Scene::Ptr CreateEmptyScene();
        static Scene::Ptr NewScene(const Path& path, SceneLogicType type);
        static Scene::Ptr LoadScene(const Path& path);
        static bool IsExists(const Path& path);
        static Path GetAbsPath(const Path& path);

        void Init();
        void Prepare();

        bool SaveScene();
        bool SaveSceneAt(const Path& path);
        bool Destroy();
        bool SetDirty(bool dirty) override;

        void SetPath(const Path& path);

    public:
        SR_NODISCARD std::string GetName() const;
        SR_NODISCARD Path GetPath() const { return m_path; }
        SR_NODISCARD Path GetAbsPath() const;
        SR_NODISCARD bool IsPrefab() const noexcept override;
        SR_NODISCARD SR_HTYPES_NS::DataStorage& GetDataStorage();
        SR_NODISCARD const SR_HTYPES_NS::DataStorage& GetDataStorage() const;
        SR_NODISCARD SR_INLINE SceneUpdater* GetSceneUpdater() const { return m_sceneUpdater; }
        SR_NODISCARD SR_INLINE SceneLogicPtr GetLogicBase() const { return m_logic; }
        SR_NODISCARD const SR_UTILS_NS::EntityController::Ptr& GetEntityController() const { return m_pEntityController; }

        SR_NODISCARD virtual bool IsPlayingMode() const { return false; }
        SR_NODISCARD virtual bool IsPausedMode() const { return false; }

        SceneObjects& GetRootSceneObjects();

        SceneObjectPtr FindByComponent(const std::string& name);
        SceneObjectPtr Find(const std::string& name);
        SceneObjectPtr Find(const char* name);
        SceneObjectPtr Find(uint64_t hashName);
        SceneObjectPtr Find(SR_UTILS_NS::StringAtom name);

        void RegisterSceneObject(const SceneObjectPtr& pSO);

        virtual SceneObjectPtr InstanceFromFile(const SR_UTILS_NS::Path& path);
        virtual SceneObjectPtr Instance(const Types::RawMesh* rawMesh);

        virtual GameObjectPtr FindOrInstanceGameObject(SR_UTILS_NS::StringAtom name);
        virtual GameObjectPtr InstanceGameObject(SR_UTILS_NS::StringAtom name);

        IComponentable::ScenePtr GetScene() const override { return const_cast<ScenePtr>(this); }

    public:
        bool Remove(const SceneObjectPtr& gameObject);
        void Remove(const Component::Ptr& pComponent);

        void OnChanged();

        bool Reload();

        void OnPostLoad() override;

    private:
        void RegisterSceneObjectImpl(const SceneObjectPtr& pSO);
        void ProcessNewSO(const SceneObjectPtr& pSO);

    private:
        mutable std::map<EntityId, EntityId> m_registerEntityIdReplaceCache;
        mutable std::map<SR_UTILS_NS::Prefab*, std::vector<Entity*>> m_registerEntityCache;

        SceneUpdater* m_sceneUpdater = nullptr;

        bool m_isInitialized = false;
        bool m_isPreDestroyed = false;
        bool m_isDestroyed = false;

        std::atomic<bool> m_isHierarchyChanged = false;

        SR_HTYPES_NS::DataStorage m_dataStorage;

        std::list<uint64_t> m_freeObjIndices;
        std::list<SceneObjectPtr> m_newQueue;
        std::list<SceneObjectPtr> m_deleteQueue;

        std::list<Component::Ptr> m_destroyedComponents;

        Path m_path;
        Path m_absPath;

        SceneObjects m_sceneObjects;

        SR_UTILS_NS::EntityController::Ptr m_pEntityController;

    private:
        SR_HTYPES_NS::SharedPtr<SceneLogic> m_logic;
        SceneObjects m_root;

    };
}

#endif //SR_ENGINE_SCENE_H
```


