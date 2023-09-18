//
// Created by Nikita on 30.11.2020.
//

#include <Utils/World/Scene.h>

#include <Utils/World/Region.h>
#include <Utils/World/Chunk.h>
#include <Utils/World/SceneAllocator.h>
#include <Utils/World/SceneLogic.h>
#include <Utils/World/SceneCubeChunkLogic.h>
#include <Utils/World/SceneDefaultLogic.h>
#include <Utils/World/SceneBuilder.h>
#include <Utils/World/ScenePrefabLogic.h>

#include <Utils/Types/RawMesh.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>

#include <Utils/Platform/Platform.h>

namespace SR_WORLD_NS {
    Scene::Scene()
        : Super(this)
        , m_sceneBuilder(new SR_WORLD_NS::SceneBuilder(this))
    { }

    Scene::~Scene() {
        SRAssert(m_isDestroyed);

        if (Debug::Instance().GetLevel() >= Debug::Level::Low) {
            SR_LOG("Scene::~Scene() : free \"" + GetName() + "\" scene pointer...");
        }

        SRAssert(m_newQueue.empty());
        SRAssert(m_deleteQueue.empty());
        SRAssert(m_destroyedComponents.empty());
        SRAssert(m_freeObjIndices.size() == m_gameObjects.size());

        SR_SAFE_DELETE_PTR(m_sceneBuilder);
    }

    GameObject::Ptr Scene::Instance(const std::string& name) {
        if (Debug::Instance().GetLevel() >= Debug::Level::High) {
            SR_LOG("Scene::Instance() : instance \"" + name + "\" game object at \"" + GetName() + "\" scene.");
        }

        GameObject::Ptr gm = new GameObject(name);

        RegisterGameObject(gm);

        return gm;
    }

    Scene::GameObjectPtr Scene::FindOrInstance(const std::string &name) {
        if (auto&& pFound = Find(name)) {
            return pFound;
        }

        return Instance(name);
    }

    Scene::GameObjectPtr Scene::Instance(SR_HTYPES_NS::Marshal &marshal) {
        return GameObject::Load(marshal, this);
    }

    Scene::Ptr Scene::Empty() {
        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::Empty() : creating new empty scene...");
        }

        auto&& scene = SceneAllocator::Instance().Allocate();

        if (!scene) {
            SR_ERROR("Scene::New() : failed to allocate scene!");
            return Scene::Ptr();
        }

        scene->m_logic = new SceneDefaultLogic(scene);

        return scene;
    }

    Scene::Ptr Scene::New(const Path& path) {
        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::New() : creating new scene...");
        }

        if (SR_PLATFORM_NS::IsExists(path)) {
            SRHalt("Scene::New() : scene already exists!\n\tPath: " + path.ToString());
            return Scene::Ptr();
        }

        auto&& scene = SceneAllocator::Instance().Allocate();

        if (!scene) {
            SR_ERROR("Scene::New() : failed to allocate scene!");
            return Scene::Ptr();
        }

        SRAssert(!path.IsAbs());

        scene->m_absPath = GetAbsPath(path);
        scene->m_path = path;
        scene->m_logic = SceneLogic::CreateByExt(scene, path.GetExtension());

        return scene;
    }

    Scene::Ptr World::Scene::Load(const Path& path) {
        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::Load() : loading scene...\n\tPath: " + path.ToString());
        }

        auto&& scene = SceneAllocator::Instance().Allocate();

        if (!scene) {
            SR_ERROR("Scene::Load() : failed to allocate scene!");
            return Scene::Ptr();
        }

        SRAssert(!path.IsAbs());

        scene->m_absPath = GetAbsPath(path);
        scene->m_path = path;
        scene->m_logic = SceneLogic::CreateByExt(scene, path.GetExtension());

        if (!scene->m_logic->Load(scene->m_absPath)) {
            SR_ERROR("Scene::Load() : failed to load scene logic!");

            scene.AutoFree([](SR_WORLD_NS::Scene* pScene) {
                pScene->Destroy();
                delete pScene;
            });

            return Scene::Ptr();
        }

        return scene;
    }

    bool Scene::Destroy() {
        if (m_isDestroyed) {
            SR_ERROR("Scene::Destroy() : scene \"" + GetName() + "\" already destroyed!");
            return false;
        }

        m_isPreDestroyed = true;

        IComponentable::DestroyComponents();

        m_logic.AutoFree([](auto&& pLogic) {
            pLogic->Destroy();
            delete pLogic;
        });

        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            const uint64_t count = m_gameObjects.size() - m_freeObjIndices.size();
            SR_LOG("Scene::Destroy() : complete unloading!");
            SR_LOG("Scene::Destroy() : destroying \"" + GetName() + "\" scene contains "+ std::to_string(count) +" game objects...");
        }

        for (auto gameObject : GetRootGameObjects()) {
            gameObject->Destroy();
        }

        Prepare();

        if (m_gameObjects.size() != m_freeObjIndices.size()) {
            SRHalt(SR_UTILS_NS::Format("Scene::Destroy() : after destroying the root objects, "
                                       "there are %i objects left!", m_gameObjects.size() - m_freeObjIndices.size()));
        }

        m_isDestroyed = true;
        m_isHierarchyChanged = true;

        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::Destroy() : scene successfully destroyed!");
        }

        return true;
    }

    Scene::GameObjects & Scene::GetRootGameObjects() {
        if (!m_isHierarchyChanged) {
            return m_rootObjects;
        }

        m_rootObjects.clear();
        m_rootObjects.reserve(m_gameObjects.size() / 2);

        for (auto&& gameObject : m_gameObjects) {
            if (!gameObject) {
                continue;
            }

            if (!gameObject->GetParent()) {
                m_rootObjects.emplace_back(gameObject);
            }
        }

        m_isHierarchyChanged = false;

        return m_rootObjects;
    }

    GameObject::Ptr Scene::FindByComponent(const std::string &name) {
        for (auto&& gameObject : m_gameObjects) {
            if (gameObject->ContainsComponent(name)) {
                return gameObject;
            }
        }

        return GameObject::Ptr();
    }

    void Scene::OnChanged() {
        m_isHierarchyChanged = true;
    }

    bool Scene::Save() {
        return SaveAt(m_path);
    }

    bool Scene::SaveAt(const Path& path) {
        SR_INFO(SR_FORMAT("Scene::SaveAt() : saving scene...\n\tPath: %s", path.CStr()));

        SRAssert(!path.IsAbs());

        if (m_path.GetExtensionView() != path.GetExtensionView()) {
            SR_ERROR("Scene::SaveAt() : different extensions!\n\tSave path: " + path.ToString() + "\n\tScene path: " + m_path.ToString());
            return false;
        }

        if (!m_logic->Save(GetAbsPath(path))) {
            SR_ERROR("Scene::SaveAt() : failed to save scene logic!");
            return false;
        }

        return true;
    }

    bool Scene::Remove(const GameObject::Ptr& gameObject) {
        SRAssert(!m_isDestroyed);

        m_deleteQueue.emplace_back(gameObject);

        const uint64_t idInScene = gameObject->GetIdInScene();

        if (idInScene >= m_gameObjects.size()) {
            SRHalt("Scene::Prepare() : invalid game object id!");
            return false;
        }

        if (m_gameObjects.at(idInScene) != gameObject) {
            SRHalt("Scene::Prepare() : game objects do not match!");
            return false;
        }

        m_gameObjects.at(idInScene) = GameObject::Ptr();
        m_freeObjIndices.emplace_back(idInScene);

        SetDirty(true);
        OnChanged();

        return true;
    }

    GameObject::Ptr Scene::Instance(const SR_HTYPES_NS::RawMesh *rawMesh) {
        SRHalt("Method isn't implemented!");
        return GameObject::Ptr();
    }

    GameObject::Ptr Scene::InstanceFromFile(const std::string &path) {
        auto&& extension = SR_UTILS_NS::StringUtils::GetExtensionFromFilePath(path);

        if (extension == Prefab::EXTENSION) {
            auto&& pPrefab = Prefab::Load(path);

            if (pPrefab) {
                auto&& instanced = pPrefab->Instance(this);
                pPrefab->CheckResourceUsage();
                return instanced;
            }

            return GameObject::Ptr();
        }

        if (auto&& raw = SR_HTYPES_NS::RawMesh::Load(path)) {
            GameObject::Ptr root = Instance(raw);

            if (raw->GetCountUses() == 0) {
                raw->Destroy();
            }

            return root;
        }

        return GameObject::Ptr();
    }

    bool Scene::Reload() {
        SR_INFO("Scene::Reload() : reload scene...");
        return m_logic->Reload();
    }

    GameObject::Ptr Scene::Find(uint64_t hashName) {
        for (auto&& object : m_gameObjects) {
            /// блокировать объекты не нужно, так как уничтожиться они могут только из сцены
            /// Но стоит предусмотреть защиту от одновременного изменения имени
            if (object && object->GetHashName() == hashName) {
                return object;
            }
        }

        return GameObject::Ptr();
    }

    GameObject::Ptr Scene::Find(const std::string &name) {
        return Find(SR_HASH_STR(name));
    }

    std::string Scene::GetName() const {
        return m_path.GetBaseName();
    }

    bool Scene::IsPrefab() const {
        return m_logic.DynamicCast<ScenePrefabLogic>();
    }

    void Scene::RegisterGameObject(const Scene::GameObjectPtr& ptr) {
        SRAssert(!m_isPreDestroyed);
        SRAssert(!ptr->GetScene());

        m_newQueue.emplace_back(ptr);

        ptr->SetScene(this);

        for (auto&& child : ptr->GetChildrenRef()) {
            RegisterGameObject(child);
        }

        SetDirty(true);
        OnChanged();
    }

    void Scene::Prepare() {
        if (!m_deleteQueue.empty() || !m_newQueue.empty() || !m_destroyedComponents.empty()) {
            SetDirty(true);
            OnChanged();
        }

        if (m_isPreDestroyed) {
            for (auto&& gameObject : m_newQueue) {
                if (!gameObject) {
                    continue;
                }
                gameObject->Destroy();
            }
        } 
        else {
            for (auto&& gameObject : m_newQueue) {
                const uint64_t id = m_freeObjIndices.empty() ? m_gameObjects.size() : m_freeObjIndices.front();

                gameObject->SetIdInScene(id);

                if (m_freeObjIndices.empty()) {
                    m_gameObjects.emplace_back(gameObject);
                }
                else {
                    m_gameObjects[m_freeObjIndices.front()] = gameObject;
                    m_freeObjIndices.erase(m_freeObjIndices.begin());
                }
            }
        }

        m_newQueue.clear();

        for (auto&& gameObject : m_deleteQueue) {
            gameObject->DestroyComponents();
        }

        for (auto&& pComponent : m_destroyedComponents) {
            pComponent->OnDestroy();
        }

        m_destroyedComponents.clear();

        for (auto&& gameObject : m_deleteQueue) {
            gameObject->DestroyImpl();
        }

        m_deleteQueue.clear();
    }

    void Scene::Remove(Component* pComponent) {
        m_destroyedComponents.emplace_back(pComponent);
    }

    Path Scene::GetAbsPath() const {
        return m_absPath;
    }

    bool Scene::IsExists(const Path& path) {
        return GetAbsPath(path).Exists();
    }

    Path Scene::GetAbsPath(const Path& path) {
        if (path.Contains(RuntimeScenePath.ToStringRef()) ||
            path.Contains(NewScenePath.ToStringRef()) ||
            path.Contains(NewPrefabPath.ToStringRef())
        ) {
            return SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat(path);
        }

        return SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path);
    }
}