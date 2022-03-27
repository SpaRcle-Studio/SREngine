//
// Created by Nikita on 30.11.2020.
//

#include "World/Scene.h"
#include <EntityComponentSystem/Component.h>
#include <EntityComponentSystem/Transform.h>
#include <EntityComponentSystem/GameObject.h>

#include <World/Region.h>
#include <World/Chunk.h>

#include <utility>
#include <Debug.h>

Framework::Helper::Types::SafePtr<Framework::Helper::GameObject> Framework::Helper::World::Scene::Instance(const std::string& name) {
    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Scene::Instance() : instance \"" + name + "\" game object at \"" + std::string(m_name) + "\" scene.");

    Types::SafePtr<GameObject> gm = *(new GameObject(*this, name));

    m_gameObjects.insert(gm);

    m_isHierarchyChanged = true;

    return gm;
}

Framework::Helper::Types::SafePtr<Framework::Helper::World::Scene> Framework::Helper::World::Scene::New(const std::string& name) {
    if (Debug::GetLevel() > Debug::Level::None)
        Debug::Log("Scene::New() : creating new scene...");

    if (!g_allocator) {
        Helper::Debug::Error("Scene::New() : allocator is not set!");
        return Types::SafePtr<Scene>();
    }

    return *g_allocator(name);
}

Framework::Helper::Types::SafePtr<Framework::Helper::World::Scene> Framework::Helper::World::Scene::Load(const std::string& name) {
    Types::SafePtr<Scene> scene;
    return scene;
}

bool Framework::Helper::World::Scene::Destroy() {
    if (m_isDestroy) {
        Debug::Error("Scene::Destroy() : scene \"" + std::string(m_name) + "\" already destroyed!");
        return false;
    }

    if (Debug::GetLevel() > Debug::Level::None)
        Debug::Log("Scene::Destroy() : unload " + std::to_string(m_regions.size()) + " regions...");

    for (auto&& [position, region] : m_regions) {
        region->Unload();
        delete region;
    }

    if (Debug::GetLevel() > Debug::Level::None) {
        Debug::Log("Scene::Destroy() : complete unloading!");
        Debug::Log("Scene::Destroy() : destroying \"" + std::string(m_name) + "\" scene contains "+ std::to_string(m_gameObjects.size()) +" game objects...");
    }

    for (auto gameObject : GetRootGameObjects()) {
        gameObject.AutoFree([](GameObject* gm) {
            gm->Destroy(GameObject::DestroyBy_Scene);
        });
    }

    if (!m_gameObjects.empty()) {
        Helper::Debug::Warn(Format("Scene::Destroy() : after destroying the root objects, "
                                   "there are %i objects left!", m_gameObjects.size()));
        m_gameObjects.clear();
    }

    m_isDestroy = true;
    m_isHierarchyChanged = true;

    if (Debug::GetLevel() > Debug::Level::None)
        Debug::Log("Scene::Destroy() : scene successfully destroyed!");

    return true;
}

bool Framework::Helper::World::Scene::Free() {
    if (!m_isDestroy) {
        Debug::Error("Scene::Free() : scene \"" + std::string(m_name) + "\" is not destroyed!");
        return false;
    }

    if (Debug::GetLevel() > Debug::Level::None)
        Debug::Log("Scene::Free() : free \"" + std::string(m_name) + "\" scene pointer...");

    if (m_observer) {
        delete m_observer;
        m_observer = nullptr;
    }

    delete this;
    return true;
}

Framework::Helper::World::GameObjects& Framework::Helper::World::Scene::GetRootGameObjects() {
    if (!m_isHierarchyChanged)
        return m_rootObjects;

    m_rootObjects.clear();

    for (const auto& gm : m_gameObjects)
        if (!gm->GetParent().Valid())
            m_rootObjects.insert(gm);

    m_isHierarchyChanged = false;

    return m_rootObjects;
}

void Framework::Helper::World::Scene::AddSelected(const Types::SafePtr<GameObject>& gameObject) {
    this->m_selectedGameObjects.insert(gameObject);

    auto components = gameObject->GetComponents();
    for (Framework::Helper::Component* comp : components) // TODO: unsafe
        comp->OnSelected(true);
}

bool Framework::Helper::World::Scene::RemoveSelected(const GameObject::Ptr& gameObject) {
    auto components = gameObject->GetComponents();
    for (Framework::Helper::Component* comp : components) // TODO: unsafe
        comp->OnSelected(false);

    if (auto find = m_selectedGameObjects.find(gameObject); find == m_selectedGameObjects.end()) {
        Helper::Debug::Error("Scene::RemoveSelected() : \""+gameObject->GetName() + "\" not found!");
        return false;
    }
    else {
        m_selectedGameObjects.erase(find);
        return true;
    }
}

void Framework::Helper::World::Scene::DeSelectAll() {
    for (auto gameObject : m_selectedGameObjects) {
        if (gameObject.RecursiveLockIfValid()) {
            auto components = gameObject->GetComponents();
            for (auto comp : components)
                comp->OnSelected(false);

            gameObject->m_isSelect = false;

            gameObject.Unlock();
        }
    }

    m_selectedGameObjects.clear();
}

Framework::Helper::Types::SafePtr<Framework::Helper::GameObject> Framework::Helper::World::Scene::FindByComponent(const std::string &name) {
    for (const auto& gm : m_gameObjects)
        if (gm->ContainsComponent(name))
            return gm;

    return Types::SafePtr<Framework::Helper::GameObject>();
}

void Framework::Helper::World::Scene::OnChanged() {
    m_isHierarchyChanged = true;
}

void Framework::Helper::World::Scene::ForEachRootObjects(const std::function<void(Types::SafePtr<GameObject>)> &fun) {
    for (auto gm : GetRootGameObjects()) {
        if (gm.LockIfValid()) {
            fun(gm);
            gm.Unlock();
        }
    }
}

bool Framework::Helper::World::Scene::Save() {
    return SaveAt(m_path);
}

void Scene::SaveRegion(Region* pRegion) const {
    const auto regions = m_path.Concat(std::string(m_name)).Concat("regions");

    regions.Make(Path::Type::Folder);

    const auto& regPath = regions.Concat(pRegion->GetPosition().ToString()).ConcatExt("dat");
    if (auto&& regionMarshal = pRegion->Save(); regionMarshal.Valid()) {
        regionMarshal.Save(regPath);
        /// debug: regionMarshal.Save(regPath.ConcatExt("json"), MarshalSaveMode::Json);
    }
    else if (regPath.Exists()) {
        FileSystem::Delete(regPath.CStr());
        /// debug: FileSystem::Delete(regPath.ConcatExt("json").CStr());
    }
}

bool Framework::Helper::World::Scene::SaveAt(const std::string& folder) {
    m_path = folder;

    UpdateContainers();

    auto xml = Xml::Document::New();
    if (auto&& root = xml.Root().AppendChild("Scene"); root.Valid()) {
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

    const auto scene = m_path.Concat(std::string(m_name));

    return xml.Save(scene.Concat("main.scene"));
}

Framework::Helper::World::GameObjects Framework::Helper::World::Scene::GetGameObjects()  {
    auto v = GameObjects();
    v.reserve(m_gameObjects.size());

    for (const auto& a : m_gameObjects)
        v.insert(a);

    return v;
}

Framework::Helper::Types::SafePtr<Framework::Helper::GameObject> Framework::Helper::World::Scene::GetSelected() const  {
    if (auto size = m_selectedGameObjects.size(); size == 0 || size > 1)
        return Types::SafePtr<GameObject>();
    else {
        return *m_selectedGameObjects.begin();
    }
}

void Framework::Helper::World::Scene::Update(float_t dt) {
    if (!m_observer->m_target.Valid()) {
        if (!m_regions.empty()) {
            for (auto&& [pos, pRegion] : m_regions) {
                pRegion->Unload();
                SaveRegion(pRegion);
                delete pRegion;
            }

            m_regions.clear();
        }

        return;
    }

    const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);
    const auto regSize = Math::IVector3(m_regionWidth);
    const auto regSize2 = Math::IVector3(m_regionWidth - 1);

    const World::Offset offset = m_observer->m_offset;
    Math::FVector3 observerPos;

    if (m_observer->m_target.LockIfValid()) {
        observerPos = m_observer->m_target->GetTransform()->GetTranslation().Singular(chunkSize.Cast<Math::Unit>());

        auto&& lastChunk = m_observer->m_lastChunk;
        auto&& lastRegion = m_observer->m_lastRegion;

        m_observer->m_target.Unlock();

        auto chunk = AddOffset(IVector3(observerPos / chunkSize), -offset.m_chunk);

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

            if (auto &&regionIt = m_regions.at(m_observer->m_region))
                regionIt->GetChunk(m_observer->m_chunk)->OnEnter();

            lastRegion = region;
            lastChunk = chunk;
        }
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

    if (m_shiftEnabled)
        CheckShift(observerPos.Cast<int>() / chunkSize);
}

Framework::Helper::World::Scene::Scene(const std::string &name)
    : Types::SafePtr<Scene>(this)
    , m_name(name)
    , m_observer(new Observer(GetThis()))
{
    m_path = ResourceManager::Instance().GetCachePath().Concat("Scenes");
    ReloadConfig();
}

void Framework::Helper::World::Scene::SetWorldOffset(const Framework::Helper::World::Offset &offset) {
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

    /// пытаемсы синхронно сдвинуть все объекты, если невозможно (в случае двойной блокировки) то делаем асинхронно,
    /// т.к. вероятнее всего находимся в том же потоке
    bool sync = this->TrySync();
    {
        for (const GameObject::Ptr& gameObject : GetRootGameObjects())
            gameObject->GetTransform()->GlobalTranslate(fOffset);
    }
    if (sync) this->EndSync();

    for (const auto& [position, pRegion] : m_regions)
        pRegion->ApplyOffset();
}

Framework::Helper::World::Chunk *Framework::Helper::World::Scene::GetCurrentChunk() const {
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

void Scene::CheckShift(const IVector3 &chunk) {
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

        auto chunk = AddOffset(IVector3(gmPosition.Singular(chunkSize.Cast<Math::Unit>()) / chunkSize), -m_observer->m_offset.m_chunk);
        auto region = AddOffset(chunk.Singular(Math::IVector3(m_regionWidth - 1)) / Math::IVector3(m_regionWidth), -m_observer->m_offset.m_region);

        const TensorKey key = TensorKey(region, MakeChunk(chunk, m_regionWidth));
        m_tensor[key].insert(gameObject);
    }
}

bool Scene::ReloadConfig() {
    const std::string path = Helper::ResourceManager::Instance().GetResPath().Concat("/Configs/World.xml");

    if (auto xml = Helper::Xml::Document::Load(path); xml.Valid()) {
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
        Helper::Debug::Error("Scene::Scene() : file not found! Path: " + path);
        return false;
    }
}

bool Scene::Remove(const Types::SafePtr<GameObject> &gameObject) {
    if (m_selectedGameObjects.count(gameObject))
        m_selectedGameObjects.erase(gameObject);

    m_gameObjects.erase(gameObject);
    OnChanged();

    return true;
}

void Scene::ReloadChunks() {
    for (auto&& [position, pRegion] : m_regions)
        pRegion->Reload();
}

GameObjects Scene::GetGameObjectsAtChunk(const IVector3 &region, const IVector3 &chunk) {
    const auto key = TensorKey(region, chunk);
    if (m_tensor.count(key) == 0)
        return GameObjects();

    return m_tensor.at(key);
}





