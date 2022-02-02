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
        gameObject.Lock();

        gameObject.Free([](GameObject* gm) {
            gm->Destroy(GameObject::DestroyBy::Scene);
            gm->Free();
        });

        gameObject.Unlock();
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
    } else {
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

    this->m_selectedGameObjects.clear();
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

bool Framework::Helper::World::Scene::Save(const std::string& folder) {
    auto xml = Xml::Document::New();
    if (auto root = xml.Root().AppendChild("Scene"); root.Valid()) {
        root.AppendAttribute("Name", std::string(m_name).c_str());
        auto settings = root.AppendChild("Settings"); {
            auto chunk = settings.AppendChild("Chunks"); {
                chunk.AppendChild("x_size").AppendAttribute("value", 100.f);
                chunk.AppendChild("y_size").AppendAttribute("value", 500.f);
                chunk.AppendChild("z_size").AppendAttribute("value", 100.f);
            }

            auto region = settings.AppendChild("Region"); {
                region.AppendChild("width").AppendAttribute("value", 50);
            }
        }

        auto gameObjects = root.AppendChild("GameObjects");
        for (const auto& gameObject : GetRootGameObjects()) {
            gameObjects.AppendChild(gameObject->Save().DocumentElement());
        }
    }

    return xml.Save(folder + "/" + std::string(m_name) + ".scene");
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
        auto gameObject = *m_selectedGameObjects.begin();
        return gameObject;
    }
}

void Framework::Helper::World::Scene::Update(float_t dt) {
    if (!m_observer->m_target.Valid())
        return;

    const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);
    const auto regSize = Math::IVector2(m_regionWidth);
    const auto regSize2 = Math::IVector2(m_regionWidth - 1);

    const World::Offset offset = m_observer->m_offset;
    Math::FVector3 observerPos;

    if (m_observer->m_target.LockIfValid()) {
        observerPos = m_observer->m_target->GetTransform()->GetPosition().Singular(chunkSize.Cast<Math::Unit>());

        auto&& lastChunk = m_observer->m_lastChunk;
        auto&& lastRegion = m_observer->m_lastRegion;

        m_observer->m_target.Unlock();

        auto chunk = AddOffset(IVector3(observerPos / chunkSize), -offset.m_chunk);

        if (lastChunk != chunk) {
            if (m_regions.find(lastRegion) != m_regions.end())
                m_regions.at(lastRegion)->GetChunk(m_observer->m_chunk)->OnExit();

            m_observer->SetChunk(chunk);

            auto region = AddOffset(chunk.XZ().Singular(regSize2) / regSize, -offset.m_region);

            if (auto regionDelta = (region - lastRegion); !regionDelta.Empty()) {
                m_observer->Move(regionDelta);
                SRAssert(!m_observer->m_region.HasZero());
            }

            if (m_regions.find(m_observer->m_region) == m_regions.end()) {
                auto pRegion = Region::Allocate(m_observer, m_regionWidth, m_chunkSize, m_observer->m_region);
                m_regions.insert(std::pair(m_observer->m_region, pRegion));
            }

            if (auto &&regionIt = m_regions.at(m_observer->m_region))
                regionIt->GetChunk(m_observer->m_chunk)->OnEnter();

            lastRegion = region;
            lastChunk = chunk;
        }
    }

    if (m_updateContainer)
        this->UpdateContainers();

    if (m_scopeEnabled) {
        for (auto&& pIt = m_regions.begin(); pIt != m_regions.end(); ) {
            const auto& pRegion = pIt->second;

            pRegion->Update(dt);

            if (pRegion->IsAlive())
                ++pIt;
            else {
                pRegion->Unload();
                delete pRegion;
                pIt = m_regions.erase(pIt);
            }
        }

        this->UpdateScope();
    }

    if (m_shiftEnabled)
        this->CheckShift(observerPos.Cast<int>() / chunkSize);
}

Framework::Helper::World::Scene::Scene(const std::string &name)
    : Types::SafePtr<Scene>(this)
    , m_name(name)
    , m_observer(new Observer(GetThis()))
{
    ReloadConfig();
}

void Framework::Helper::World::Scene::SetWorldOffset(const Framework::Helper::World::Offset &offset) {
    const auto prevOffset = m_observer->m_offset;
    const auto region = (offset.m_chunk / static_cast<int32_t>(m_regionWidth)).ZeroAxis(Math::AXIS_Y);
    m_observer->m_offset = World::Offset(offset.m_region + region.XZ(), offset.m_chunk - region * m_regionWidth);

    Helper::Debug::Log("Scene::SetWorldOffset() : set new offset " + m_observer->m_offset.ToString());

    const auto deltaOffset = m_observer->m_offset - prevOffset;

    const auto fOffset = ((Math::IVector3::XZ(deltaOffset.m_region * m_regionWidth) + deltaOffset.m_chunk)
            * Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x)).Cast<Math::Unit>();

    /// пытаемсы синхронно сдвинуть все объекты, если невозможно (в случае двойной блокировки) то делаем асинхронно,
    /// т.к. вероятнее всего находимся в том же потоке
    bool sync = this->TrySync();
    {
        for (const GameObject::Ptr &gameObject : this->GetRootGameObjects())
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

void Scene::UpdateScope() {
    const auto scope = m_observer->m_scope;

    const auto& update = [this](const Math::IVector3& point) -> void {
        const auto neighbour = m_observer->MathNeighbour(point);

        /// если объект находится за пределами загруженной области, то нужно ее загрузить и поместить туда его
        if (m_regions.find(neighbour.m_region) == m_regions.end())
            m_regions.insert(
                    std::pair(neighbour.m_region, Region::Allocate(m_observer, m_regionWidth, m_chunkSize,
                                                                   neighbour.m_region)));

        auto chunk = m_regions.at(neighbour.m_region)->GetChunk(neighbour.m_chunk);
        if (chunk->GetState() == Chunk::LoadState::Unload)
            chunk->Load();

        chunk->Access();
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
    Math::IVector3 offset = m_observer->m_offset.m_chunk + Math::IVector3::XZ(m_observer->m_offset.m_region * m_regionWidth);

    if (chunk.x > shift) {
        offset.x -= abs(chunk.x);

        SetWorldOffset(Offset({ 0, 0 }, offset));
    } else if (chunk.x < -shift) {
        offset.x += abs(chunk.x);

        SetWorldOffset(Offset({ 0, 0 }, offset));
    }
}

void Scene::UpdateContainers() {
    const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);
    const auto regSize = Math::IVector2(m_regionWidth);
    const auto regSize2 = Math::IVector2(m_regionWidth - 1);

    for (const GameObject::Ptr& gameObject : this->GetRootGameObjects()) {
        const auto gmPosition = gameObject->GetTransform()->GetPosition();
        auto position = AddOffset(
                Math::IVector3(gmPosition.Singular(chunkSize.Cast<Math::Unit>())) / chunkSize,
                -m_observer->m_offset.m_chunk
        );

        auto region = AddOffset(position.XZ().Singular(regSize2) / regSize, -m_observer->m_offset.m_region);

        /// если объект находится за пределами загруженной области, то нужно ее загрузить и поместить туда его
        if (m_regions.find(region) == m_regions.end())
            m_regions.insert(std::pair(region, Region::Allocate(m_observer, m_regionWidth, m_chunkSize, region)));

        auto&& chunk = m_regions.at(region)->GetChunk(gmPosition);

        if (auto&& pair = m_gameObjectPairs.find(gameObject); pair != m_gameObjectPairs.end()) {
            if (pair->second != chunk) {
                pair->second->Erase(gameObject);
                pair->second = nullptr;
            }
        }

        chunk->Insert(gameObject);
        m_gameObjectPairs[gameObject] = chunk;
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



