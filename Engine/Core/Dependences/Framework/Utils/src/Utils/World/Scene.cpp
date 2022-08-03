//
// Created by Nikita on 30.11.2020.
//

#include <Utils/World/Scene.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>

#include <Utils/World/Region.h>
#include <Utils/World/Chunk.h>

namespace SR_WORLD_NS {
    bool SceneAllocator::Init(const SceneAllocator::Allocator &allocator) {
        if (m_allocator) {
            SR_WARN("SceneAllocator::Init() : allocator already initialized!");
            return false;
        }

        m_allocator = allocator;

        return true;
    }

    SceneAllocator::ScenePtr SceneAllocator::Allocate() {
        if (!m_allocator) {
            SRHalt("SceneAllocator::Allocate() : allocator isn't initialized!");
            Platform::Terminate();
        }

        return *m_allocator();
    }

    Scene::Scene()
        : Scene("Unnamed")
    { }

    Scene::Scene(const std::string &name)
        : Super(this)
        , m_name(name)
        , m_observer(new Observer(GetThis()))
    {
        ReloadConfig();
    }

    SR_HTYPES_NS::SafePtr<GameObject> Scene::Instance(const std::string& name) {
        if (Debug::Instance().GetLevel() >= Debug::Level::High) {
            SR_LOG("Scene::Instance() : instance \"" + name + "\" game object at \"" + std::string(m_name) + "\" scene.");
        }

        Types::SafePtr<GameObject> gm = *(new GameObject(GetThis(), name));

        m_gameObjects.emplace_back(gm);

        m_isHierarchyChanged = true;

        return gm;
    }

    SR_HTYPES_NS::SafePtr<Scene> Scene::New(const Path& path) {
        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::New() : creating new scene...");
        }

        auto&& scene = SceneAllocator::Instance().Allocate();

        if (!scene) {
            SR_ERROR("Scene::New() : failed to allocate scene!");
            return Types::SafePtr<Scene>();
        }

        scene->SetPath(path);
        scene->SetName(path.GetBaseName());

        return scene;
    }

    SR_HTYPES_NS::SafePtr<Scene> World::Scene::Load(const Path& path) {
        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::Load() : loading scene...\n\tPath: " + path.ToString());
        }

        auto&& scene = SceneAllocator::Instance().Allocate();

        if (!scene) {
            SR_ERROR("Scene::Load() : failed to allocate scene!");
            return Types::SafePtr<Scene>();
        }

        scene->SetPath(path);
        scene->SetName(path.GetBaseName());

        return scene;
    }

    bool Scene::Destroy() {
        if (m_isDestroy) {
            SR_ERROR("Scene::Destroy() : scene \"" + std::string(m_name) + "\" already destroyed!");
            return false;
        }

        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::Destroy() : unload " + std::to_string(m_regions.size()) + " regions...");
        }

        for (auto&& [position, region] : m_regions) {
            region->Unload(true);
            delete region;
        }

        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::Destroy() : complete unloading!");
            SR_LOG("Scene::Destroy() : destroying \"" + std::string(m_name) + "\" scene contains "+ std::to_string(m_gameObjects.size()) +" game objects...");
        }

        for (auto gameObject : GetRootGameObjects()) {
            gameObject.AutoFree([](GameObject* gm) {
                gm->Destroy(GAMEOBJECT_DESTROY_BY_SCENE);
            });
        }

        if (!m_gameObjects.empty()) {
            SR_WARN(Format("Scene::Destroy() : after destroying the root objects, "
                                       "there are %i objects left!", m_gameObjects.size()));
            m_gameObjects.clear();
        }

        m_isDestroy = true;
        m_isHierarchyChanged = true;

        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::Destroy() : scene successfully destroyed!");
        }

        return true;
    }

    bool Scene::Free() {
        if (!m_isDestroy) {
            SR_ERROR("Scene::Free() : scene \"" + std::string(m_name) + "\" is not destroyed!");
            return false;
        }

        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("Scene::Free() : free \"" + std::string(m_name) + "\" scene pointer...");
        }

        if (m_observer) {
            delete m_observer;
            m_observer = nullptr;
        }

        delete this;
        return true;
    }

    GameObjects& Scene::GetRootGameObjects() {
        if (!m_isHierarchyChanged)
            return m_rootObjects;

        m_rootObjects.clear();

        for (const auto& gm : m_gameObjects) {
            if (!gm->GetParent().Valid())
                m_rootObjects.emplace_back(gm);
        }

        m_isHierarchyChanged = false;

        return m_rootObjects;
    }

    SR_HTYPES_NS::SafePtr<GameObject> Scene::FindByComponent(const std::string &name) {
        for (const auto& gm : m_gameObjects)
            if (gm->ContainsComponent(name))
                return gm;

        return Types::SafePtr<GameObject>();
    }

    void Scene::OnChanged() {
        m_isHierarchyChanged = true;
    }

    void Scene::ForEachRootObjects(const std::function<void(Types::SafePtr<GameObject>)> &fun) {
        for (auto gm : GetRootGameObjects()) {
            if (gm.LockIfValid()) {
                fun(gm);
                gm.Unlock();
            }
        }
    }

    bool Scene::Save() {
        return SaveAt(m_path);
    }

    void Scene::SaveRegion(Region* pRegion) const {
        auto&& regionsPath = GetRegionsPath();

        regionsPath.Make(Path::Type::Folder);

        auto&& regPath = regionsPath.Concat(pRegion->GetPosition().ToString()).ConcatExt("dat");
        if (auto&& regionMarshal = pRegion->Save(); regionMarshal.Valid()) {
            regionMarshal.Save(regPath);
        }
        else if (regPath.Exists(Path::Type::File)) {
            Platform::Delete(regPath);
        }
    }

    bool Scene::SaveAt(const Path& path) {
        SR_INFO(SR_FORMAT("Scene::SaveAt() : save scene...\n\tPath: %s", path.CStr()));

        SetPath(path);
        SetName(path.GetBaseName());

        UpdateContainers();

        auto xml = Xml::Document::New();
        if (auto&& root = xml.AppendChild("Scene"); root.Valid()) {
            root.AppendAttribute("Name", std::string(m_name).c_str());
            if (auto&& settings = root.AppendChild("Settings")) {
                if (auto&& chunk = settings.AppendChild("Chunks")) {
                    chunk.AppendChild("x_size").AppendAttribute("value", m_chunkSize.x);
                    chunk.AppendChild("y_size").AppendAttribute("value", m_chunkSize.y);
                    chunk.AppendChild("z_size").AppendAttribute("value", m_chunkSize.x);
                }

                if (auto&& region = settings.AppendChild("Region")) {
                    region.AppendChild("width").AppendAttribute("value", m_regionWidth);
                }
            }
        }


        for (auto&& [position, pRegion] : m_regions) {
            SaveRegion(pRegion);
        }


        m_path.Normalize();

        return xml.Save(m_path.Concat("main.scene"));
    }

    void Scene::Update(float_t dt) {
        const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);
        const auto regSize = Math::IVector3(m_regionWidth);
        const auto regSize2 = Math::IVector3(m_regionWidth - 1);

        const World::Offset offset = m_observer->m_offset;

        if (m_observer->m_target.LockIfValid()) {
            m_observer->m_targetPosition = m_observer->m_target->GetTransform()->GetTranslation().Singular(chunkSize.Cast<Math::Unit>());
            m_observer->m_target.Unlock();
        }

        auto&& lastChunk = m_observer->m_lastChunk;
        auto&& lastRegion = m_observer->m_lastRegion;

        auto&& chunk = AddOffset(SR_MATH_NS::IVector3(m_observer->m_targetPosition / chunkSize), -offset.m_chunk);

        if (lastChunk != chunk) {
            if (m_regions.find(lastRegion) != m_regions.end())
                m_regions.at(lastRegion)->GetChunk(m_observer->m_chunk)->OnExit();

            m_observer->SetChunk(chunk);

            auto region = AddOffset(chunk.Singular(regSize2) / regSize, -offset.m_region);

            if (auto regionDelta = (region - lastRegion); !regionDelta.Empty()) {
                m_observer->MoveRegion(regionDelta);
                SRAssert(!m_observer->m_region.HasZero());
            }

            if (m_regions.find(m_observer->m_region) == m_regions.end()) {
                auto pRegion = Region::Allocate(m_observer, m_regionWidth, m_chunkSize, m_observer->m_region);
                pRegion->Load();
                m_regions.insert(std::pair(m_observer->m_region, pRegion));
            }

            if (auto &&regionIt = m_regions.at(m_observer->m_region)) {
                if (auto&& pChunk = regionIt->GetChunk(m_observer->m_chunk)) {
                    pChunk->OnEnter();
                }
            }

            lastRegion = region;
            lastChunk = chunk;
        }

        if (m_updateContainer)
            UpdateContainers();

        if (m_scopeEnabled) {
            UpdateScope(dt);

            for (auto&& pIt = m_regions.begin(); pIt != m_regions.end(); ) {
                const auto& pRegion = pIt->second;

                pRegion->Update(dt);

                if (pRegion->IsAlive()) {
                    ++pIt;
                }
                else {
                    pRegion->Unload();
                    SaveRegion(pRegion);
                    delete pRegion;
                    pIt = m_regions.erase(pIt);
                }
            }
        }

        if (m_isActive) {
            UpdateTree();
        }

        if (m_shiftEnabled) {
            CheckShift(m_observer->m_targetPosition.Cast<int>() / chunkSize);
        }
    }

    void Scene::SetWorldOffset(const Offset &offset) {
        const auto prevOffset = m_observer->m_offset;
        const auto region = (offset.m_chunk / static_cast<int32_t>(m_regionWidth));

        m_observer->m_offset = World::Offset(
                offset.m_region + region,
                offset.m_chunk - region * m_regionWidth
        );

        SR_LOG("Scene::SetWorldOffset() : set new offset " + m_observer->m_offset.ToString());

        const auto deltaOffset = m_observer->m_offset - prevOffset;

        const auto fOffset = ((deltaOffset.m_region * m_regionWidth + deltaOffset.m_chunk)
                * Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x)).Cast<Math::Unit>();

        /// TODO: блокировать объект!
        for (const GameObject::Ptr& gameObject : GetRootGameObjects())
            gameObject->GetTransform()->GlobalTranslate(fOffset);

        for (const auto& [position, pRegion] : m_regions)
            pRegion->ApplyOffset();
    }

    Chunk* Scene::GetCurrentChunk() const {
        if (const auto& region = m_regions.find(m_observer->m_region); region != m_regions.end())
            return region->second->Find(m_observer->m_chunk);

        return nullptr;
    }

    void Scene::UpdateScope(float_t dt) {
        const auto scope = m_observer->m_scope;

        const auto& update = [&](const Math::IVector3& point) -> void {
            const auto neighbour = m_observer->MathNeighbour(point);

            /// если объект находится за пределами загруженной области, то нужно ее загрузить и поместить туда его
            if (m_regions.find(neighbour.m_region) == m_regions.end()) {
                auto&& pRegion = Region::Allocate(m_observer, m_regionWidth, m_chunkSize, neighbour.m_region);
                m_regions.insert(std::pair(neighbour.m_region, pRegion));
                pRegion->Load();
            }

            if (auto chunk = m_regions.at(neighbour.m_region)->GetChunk(neighbour.m_chunk)) {
                chunk->Access(dt);
            }
        };

        for (int32_t x = -scope; x <= scope; ++x) {
            for (int32_t y = -scope; y <= scope; ++y) {
                for (int32_t z = -scope; z <= scope; ++z) {
                    if (SR_POW(x) + SR_POW(y) + SR_POW(z) <= SR_POW(scope))
                        update(Math::IVector3(x, y, z));
                }
            }
        }
    }

    void Scene::CheckShift(const SR_MATH_NS::IVector3 &chunk) {
        const auto shift = m_observer->m_shiftDistance;
        Math::IVector3 offset = m_observer->m_offset.m_chunk + (m_observer->m_offset.m_region * m_regionWidth);

        if (chunk.x > shift) {
            offset.x -= abs(chunk.x);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }
        else if (chunk.x < -shift) {
            offset.x += abs(chunk.x);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }

        if (chunk.y > shift) {
            offset.y -= abs(chunk.y);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }
        else if (chunk.y < -shift) {
            offset.y += abs(chunk.y);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }

        if (chunk.z > shift) {
            offset.z -= abs(chunk.z);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }
        else if (chunk.z < -shift) {
            offset.z += abs(chunk.z);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }
    }

    void Scene::UpdateContainers() {
        const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);

        m_tensor.clear();

        for (const GameObject::Ptr& gameObject : GetRootGameObjects()) {
            const Math::FVector3 gmPosition = gameObject->GetTransform()->GetTranslation();

            auto chunk = AddOffset(SR_MATH_NS::IVector3(gmPosition.Singular(chunkSize.Cast<Math::Unit>()) / chunkSize), -m_observer->m_offset.m_chunk);
            auto region = AddOffset(chunk.Singular(Math::IVector3(m_regionWidth - 1)) / Math::IVector3(m_regionWidth), -m_observer->m_offset.m_region);

            const TensorKey key = TensorKey(region, MakeChunk(chunk, m_regionWidth));
            m_tensor[key].emplace_back(gameObject);
        }
    }

    bool Scene::ReloadConfig() {
        const std::string path = ResourceManager::Instance().GetResPath().Concat("Engine/Configs/World.xml");

        if (auto xml = Xml::Document::Load(path); xml.Valid()) {
            const auto& configs = xml.Root().GetNode("Configs");

            m_chunkSize = Math::IVector2(
                    configs.TryGetNode("DefaultChunkWidth").TryGetAttribute("Value").ToInt(10),
                    configs.TryGetNode("DefaultChunkHeight").TryGetAttribute("Value").ToInt(10)
            );
            m_regionWidth = configs.TryGetNode("DefaultRegionWidth").TryGetAttribute("Value").ToInt(6);

            m_observer->SetWorldMetrics(m_chunkSize, m_regionWidth);
            m_observer->SetShiftDist(configs.TryGetNode("DefaultShiftDistance").TryGetAttribute("Value").ToInt(10));
            m_observer->SetScope(configs.TryGetNode("DefaultScope").TryGetAttribute("Value").ToInt(10));

            m_scopeEnabled = configs.TryGetNode("ScopeEnabled").TryGetAttribute("Value").ToBool(true);
            m_shiftEnabled = configs.TryGetNode("ShiftEnabled").TryGetAttribute("Value").ToBool(true);
            m_updateContainer = configs.TryGetNode("UpdateContainer").TryGetAttribute("Value").ToBool(true);

            return true;
        }
        else {
            SR_ERROR("Scene::Scene() : file not found! Path: " + path);
            return false;
        }
    }

    bool Scene::Remove(const Types::SafePtr<GameObject> &gameObject) {
        for (auto pIt = m_gameObjects.begin(); pIt != m_gameObjects.end(); ++pIt) {
            if (pIt->Get() != gameObject.Get()) {
                continue;
            }

            m_gameObjects.erase(pIt);

            OnChanged();

            return true;
        }

        SRHalt("Scene::Remove() : game object not found!");

        return false;
    }

    bool Scene::ReloadChunks() {
        for (auto&& [position, pRegion] : m_regions)
            pRegion->Reload();

        return true;
    }

    GameObjects Scene::GetGameObjectsAtChunk(const SR_MATH_NS::IVector3 &region, const SR_MATH_NS::IVector3 &chunk) {
        const auto key = TensorKey(region, chunk);
        if (m_tensor.count(key) == 0)
            return GameObjects();

        return m_tensor.at(key);
    }

    Types::SafePtr<GameObject> Scene::Instance(const Types::RawMesh *rawMesh) {
        SRAssert2(false, "Method isn't implemented!");
        return Types::SafePtr<GameObject>();
    }

    SR_HTYPES_NS::SafePtr<GameObject> Scene::InstanceFromFile(const std::string &path) {
        if (auto&& raw = SR_HTYPES_NS::RawMesh::Load(path)) {
            GameObject::Ptr root = Instance(raw);

            if (raw->GetCountUses() == 0) {
                raw->Destroy();
            }

            return root;
        }

        return SR_HTYPES_NS::SafePtr<GameObject>();
    }

    bool Scene::Reload() {
        SR_INFO("Scene::Reload() : reload scene...");
        return ReloadConfig() && ReloadChunks();
    }

    Types::SafePtr<GameObject> Scene::Find(const std::string &name) {
        for (auto&& object : m_gameObjects) {
            /// блокировать объекты не нужно, так как уничтожиться они могут только из сцены
            /// Но стоит предусмотреть защиту от одновременного изменения имени
            if (object->GetName() == name) {
                return object;
            }
        }

        return SafePtr<GameObject>(nullptr);
    }

    void Scene::UpdateTree() {
        auto&& root = GetRootGameObjects();

        for (auto&& gameObject : root) {
            gameObject->Awake();
        }

        for (auto&& gameObject : root) {
            gameObject->Start();
        }
    }

    void Scene::RunScene() {
        m_isActive = true;
    }

    void Scene::StopScene() {
        m_isActive = false;
    }

    void Scene::SetObserver(const Scene::GameObjectPtr &target) {
        if (target != m_observer->m_target) {
            m_observer->SetTarget(target);
        }
    }
}