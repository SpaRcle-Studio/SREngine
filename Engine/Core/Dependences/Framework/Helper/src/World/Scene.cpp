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

    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    Types::SafePtr<GameObject> gm;
    gm = new GameObject(m_this, name);
    gm->SetThis(gm);

    m_gameObjects.insert(gm);

    m_isHierarchyChanged = true;

    return gm;
}

Framework::Helper::Types::SafePtr<Framework::Helper::World::Scene> Framework::Helper::World::Scene::New(const std::string& name) {
    if (Debug::GetLevel() > Debug::Level::None)
        Debug::Log("Scene::New() : creating new scene...");

    Types::SafePtr<Scene> scene;
    scene = new Scene(name);
    scene->SetThis(scene);
    return scene;
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
        Debug::Log("Scene::Destroy() : destroying \"" + std::string(m_name) + "\" scene contains "+ std::to_string(m_gameObjects.size()) +" game objects...");

    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    for (auto&& [position, region] : m_regions) {
        region->Unload();
        delete region;
    }

    for (auto gameObject : m_gameObjects) {
        if (!gameObject->GetParent()) {
            gameObject.Lock();

            gameObject.Free([](GameObject* gm){
                gm->DestroyFromScene();
                gm->Free();
            });

            gameObject.Unlock();
        }
    }
    m_gameObjects.clear();

    this->m_isDestroy = true;
    m_isHierarchyChanged = true;

    return true;
}

bool Framework::Helper::World::Scene::Free() {
    if (!this->m_isDestroy) {
        Debug::Error("Scene::Free() : scene \"" + std::string(m_name) + "\" is not destroyed!");
        return false;
    }

    if (Debug::GetLevel() > Debug::Level::None)
        Debug::Log("Scene::Free() : free \"" + std::string(m_name) + "\" scene pointer...");

    delete this;
    return true;
}

Framework::Helper::World::GameObjects& Framework::Helper::World::Scene::GetRootGameObjects() {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (!m_isHierarchyChanged)
        return m_rootObjects;

    m_rootObjects.clear();

    for (const auto& gm : m_gameObjects)
        if (!gm->GetParent())
            m_rootObjects.insert(gm);

    m_isHierarchyChanged = false;

    return m_rootObjects;
}

void Framework::Helper::World::Scene::AddSelected(const Types::SafePtr<GameObject>& gameObject) {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    this->m_selectedGameObjects.insert(gameObject);

    auto components = gameObject->GetComponents();
    for (Framework::Helper::Component* comp : components) // TODO: unsafe
        comp->OnSelected(true);
}

bool Framework::Helper::World::Scene::RemoveSelected(const GameObject::Ptr& gameObject) {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

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

void Framework::Helper::World::Scene::UnselectAll() {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    for (const auto& gameObject : m_selectedGameObjects) {
        auto components = gameObject->GetComponents(); //TODO: double lock?
        for (Framework::Helper::Component* comp : components)
            comp->OnSelected(false);

        gameObject->m_isSelect = false;
    }

    this->m_selectedGameObjects.clear();
}

Framework::Helper::Types::SafePtr<Framework::Helper::GameObject> Framework::Helper::World::Scene::FindByComponent(const std::string &name) {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    for (const auto& gm : m_gameObjects)
        if (gm->ContainsComponent(name))
            return gm;

    return Types::SafePtr<Framework::Helper::GameObject>();
}

void Framework::Helper::World::Scene::OnChanged() {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    m_isHierarchyChanged = true;
}

void Framework::Helper::World::Scene::ForEachRootObjects(const std::function<void(Types::SafePtr<GameObject>)> &fun) {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    for (auto gm : m_gameObjects)
        if (gm.LockIfValid()) {
            if (!gm->GetParent())
                fun(gm);
            gm.Unlock();
        }
}

bool Framework::Helper::World::Scene::Save(const std::string& folder) {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

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
    }

    return xml.Save(folder + "/" + std::string(m_name) + ".scene");
}

Framework::Helper::World::GameObjects Framework::Helper::World::Scene::GetGameObjects()  {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    auto v = GameObjects();
    v.reserve(m_gameObjects.size());

    for (const auto& a : m_gameObjects)
        v.insert(a);

    return v;
}

Framework::Helper::Types::SafePtr<Framework::Helper::GameObject> Framework::Helper::World::Scene::GetSelected() const  {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (auto size = m_selectedGameObjects.size(); size == 0 || size > 1)
        return Types::SafePtr<GameObject>();
    else {
        auto gameObject = *m_selectedGameObjects.begin();
        return gameObject;
    }
}

void Framework::Helper::World::Scene::Update(float_t dt) {
    const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);
    const auto regSize = Math::IVector2(m_regionWidth);
    const auto regSize2 = Math::IVector2(m_regionWidth - 1);

    if (m_observer.m_target.LockIfValid()) {
        auto position = m_observer.m_target->GetTransform()->GetPosition().Singular(chunkSize.Cast<Math::Unit>());

        auto&& lastChunk = m_observer.m_lastChunk;
        auto&& lastRegion = m_observer.m_lastRegion;

        m_observer.m_target.Unlock();

        auto chunk = AddOffset(IVector3(position / chunkSize), -m_observer.m_offset.m_chunk);

        if (lastChunk != chunk) {
            if (m_regions.find(lastRegion) != m_regions.end())
                m_regions.at(lastRegion)->GetChunk(m_observer.m_chunk)->OnExit();

            m_observer.SetChunk(chunk);

            auto region = AddOffset(chunk.XZ().Singular(regSize2) / regSize, -m_observer.m_offset.m_region);

            if (auto regionDelta = (region - lastRegion); !regionDelta.Empty()) {
                m_observer.Move(regionDelta);
                SRAssert(!m_observer.m_region.HasZero());
            }

            if (m_regions.find(m_observer.m_region) == m_regions.end()) {
                auto pRegion = Region::Allocate(m_regionWidth, m_chunkSize, m_observer.m_region);
                pRegion->SetOffset(m_observer.m_offset);
                m_regions.insert(std::pair(m_observer.m_region, pRegion));
            }

            if (auto &&regionIt = m_regions.at(m_observer.m_region))
                regionIt->GetChunk(m_observer.m_chunk)->OnEnter();

            lastRegion = region;
            lastChunk = chunk;
        }
    }

    for (const GameObject::Ptr& gameObject : this->GetRootGameObjects()) {
        auto position = //AddOffset(
                Math::IVector3(gameObject->GetTransform()->GetPosition().Singular(chunkSize.Cast<Math::Unit>())) / chunkSize;//,
       //         -m_observer.m_offset.m_chunk
       // );

        //auto region = AddOffset(position.XZ().Singular(regSize2) / regSize, -m_observer.m_offset.m_region);
        auto region = position.XZ().Singular(regSize2) / regSize;
        position -= Math::IVector3::XZ(region.Singular(-1)) * m_regionWidth;

        if (m_regions.find(region) == m_regions.end())
            m_regions.insert(std::pair(region, Region::Allocate(m_regionWidth, m_chunkSize, region)));

        auto&& chunk = m_regions.at(region)->GetChunk(position);

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

Framework::Helper::World::Scene::Scene(const std::string &name) : m_name(name) {
    m_chunkSize = Math::IVector2(5, 20);
    m_regionWidth = 6;

    m_observer.SetWorldMetrics(m_chunkSize, m_regionWidth);
}

void Framework::Helper::World::Scene::SetWorldOffset(const Framework::Helper::World::Offset &offset) {
    const auto region = (offset.m_chunk / static_cast<int32_t>(m_regionWidth)).ZeroAxis(Math::AXIS_Y);
    m_observer.m_offset = World::Offset(offset.m_region + region.XZ(), offset.m_chunk - region * m_regionWidth);

    for (auto&& [key, pRegion] : m_regions) {
        pRegion->SetOffset(m_observer.m_offset);
        pRegion->ApplyOffset();
    }
}

Framework::Helper::World::Chunk *Framework::Helper::World::Scene::GetCurrentChunk() const {
    Chunk* chunk = nullptr;
    if (const auto& region = m_regions.find(m_observer.m_region); region != m_regions.end())
        chunk = region->second->Find(m_observer.m_chunk);
    return chunk;
}
