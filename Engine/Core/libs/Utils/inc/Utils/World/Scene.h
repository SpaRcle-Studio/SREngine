//
// Created by Nikita on 30.11.2020.
//

#ifndef SRENGINE_SCENE_H
#define SRENGINE_SCENE_H

#include <Utils/ECS/IComponentable.h>
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
}

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_WORLD_NS {
    class SceneLogic;
    class SceneBuilder;

    class SR_DLL_EXPORT Scene : public SR_HTYPES_NS::SafePtr<Scene>, public SR_UTILS_NS::IComponentable {
    public:
        using Ptr = SR_HTYPES_NS::SafePtr<Scene>;
        using SceneLogicPtr = SR_HTYPES_NS::SafePtr<SceneLogic>;
        using Super = Ptr;
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;
        using GameObjects = std::vector<GameObjectPtr>;

        SR_MAYBE_UNUSED SR_INLINE_STATIC const Path RuntimeScenePath = "Scenes/Runtime-cache-scene"; /// NOLINT
        SR_MAYBE_UNUSED SR_INLINE_STATIC const Path NewScenePath = "Scenes/New-cache-scene"; /// NOLINT
        SR_MAYBE_UNUSED SR_INLINE_STATIC const Path NewPrefabPath = "Scenes/New-cache-prefab"; /// NOLINT

        ~Scene() override;

    protected:
        Scene();

    public:
        static Scene::Ptr Empty();
        static Scene::Ptr New(const Path& path);
        static Scene::Ptr Load(const Path& path);
        static bool IsExists(const Path& path);
        static Path GetAbsPath(const Path& path);

        void Prepare();

        bool Save();
        bool SaveAt(const Path& path);
        bool Destroy();

    public:
        SR_NODISCARD std::string GetName() const;
        SR_NODISCARD Path GetPath() const { return m_path; }
        SR_NODISCARD Path GetAbsPath() const;
        SR_NODISCARD bool IsPrefab() const;
        SR_NODISCARD SR_HTYPES_NS::DataStorage& GetDataStorage() { return m_dataStorage; }
        SR_NODISCARD const SR_HTYPES_NS::DataStorage& GetDataStorage() const { return m_dataStorage; }
        SR_NODISCARD SR_INLINE SceneBuilder* GetSceneBuilder() const { return m_sceneBuilder; }
        SR_NODISCARD SR_INLINE SceneLogicPtr GetLogicBase() const { return m_logic; }

        /// Запущена ли сцена
        SR_NODISCARD virtual bool IsPlayingMode() const { return false; }
        /// На паузе ли сцена (если запущена)
        SR_NODISCARD virtual bool IsPausedMode() const { return false; }

        GameObjects& GetRootGameObjects();

        GameObjectPtr FindByComponent(const std::string& name);
        GameObjectPtr Find(const std::string& name);
        GameObjectPtr Find(uint64_t hashName);

        void RegisterGameObject(const GameObjectPtr& ptr);

        virtual GameObjectPtr InstanceFromFile(const std::string& path);
        virtual GameObjectPtr FindOrInstance(const std::string& name);
        virtual GameObjectPtr Instance(const std::string& name);
        virtual GameObjectPtr Instance(const Types::RawMesh* rawMesh);
        virtual GameObjectPtr Instance(SR_HTYPES_NS::Marshal& marshal);

        IComponentable::ScenePtr GetScene() const override { return const_cast<ScenePtr>(this); }

    public:
        bool Remove(const GameObjectPtr& gameObject);
        void Remove(Component* pComponent);

        void OnChanged();

        bool Reload();

    private:
        SceneLogicPtr m_logic;
        SceneBuilder* m_sceneBuilder = nullptr;

        bool m_isPreDestroyed = false;
        bool m_isDestroyed = false;

        std::atomic<bool> m_isHierarchyChanged = false;

        SR_HTYPES_NS::DataStorage m_dataStorage;

        std::list<uint64_t> m_freeObjIndices;
        std::list<GameObjectPtr> m_newQueue;
        std::list<GameObjectPtr> m_deleteQueue;

        std::list<Component*> m_destroyedComponents;

        GameObjects m_gameObjects;
        GameObjects m_rootObjects;

        Path m_path;
        Path m_absPath;

    };
}

#endif //SRENGINE_SCENE_H
