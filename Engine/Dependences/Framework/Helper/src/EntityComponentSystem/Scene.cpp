//
// Created by Nikita on 30.11.2020.
//

#include "EntityComponentSystem/Scene.h"
#include <EntityComponentSystem/Component.h>

#include <utility>
#include <Debug.h>

Framework::Helper::Types::SafePtr<Framework::Helper::GameObject> Framework::Helper::Scene::Instance(const std::string& name) {
    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Scene::Instance() : instance \"" + name + "\" game object at \"" + std::string(m_name) + "\" scene.");

    Types::SafePtr<GameObject> gm;
    gm = new GameObject(m_this, name);
    gm->SetThis(gm);

    m_mutex.lock();
    m_gameObjects.insert(gm);
    m_mutex.unlock();

    m_isHierarchyChanged = true;

    return gm;
}

Framework::Helper::Types::SafePtr<Framework::Helper::Scene> Framework::Helper::Scene::New(const std::string& name) {
    if (Debug::GetLevel() > Debug::Level::None)
        Debug::Log("Scene::New() : creating new scene...");

    Types::SafePtr<Scene> scene;
    scene = new Scene(name);
    scene->SetThis(scene);
    return scene;
}

Framework::Helper::Types::SafePtr<Framework::Helper::Scene> Framework::Helper::Scene::Load(const std::string& name) {
    Types::SafePtr<Scene> scene;
    return scene;
}

bool Framework::Helper::Scene::Destroy() {
    if (m_isDestroy) {
        Debug::Error("Scene::Destroy() : scene \"" + std::string(m_name) + "\" already destroyed!");
        return false;
    }

    if (Debug::GetLevel() > Debug::Level::None)
        Debug::Log("Scene::Destroy() : destroying \"" + std::string(m_name) + "\" scene contains "+ std::to_string(m_gameObjects.size()) +" game objects...");

    m_mutex.lock();

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

    m_mutex.unlock();

    this->m_isDestroy = true;

    m_isHierarchyChanged = true;

    return true;
}

bool Framework::Helper::Scene::Free() {
    if (!this->m_isDestroy) {
        Debug::Error("Scene::Free() : scene \"" + std::string(m_name) + "\" is not destroyed!");
        return false;
    }

    if (Debug::GetLevel() > Debug::Level::None)
        Debug::Log("Scene::Free() : free \"" + std::string(m_name) + "\" scene pointer...");

    delete this;
    return true;
}

std::vector<Framework::Helper::Types::SafePtr<Framework::Helper::GameObject>>& Framework::Helper::Scene::GetRootGameObjects() noexcept {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    m_rootObjects.clear();

    for (const auto& gm : m_gameObjects)
        if (!gm->GetParent())
            m_rootObjects.push_back(gm);

    return m_rootObjects;
}

void Framework::Helper::Scene::AddSelected(const Types::SafePtr<GameObject>& gameObject) {
    m_selectedMutex.lock();

    this->m_selectedGameObjects.insert(gameObject);

    auto components = gameObject->GetComponents();
    for (Framework::Helper::Component* comp : components) // TODO: unsafe
        comp->OnSelected(true);

    m_selectedMutex.unlock();
}

bool Framework::Helper::Scene::RemoveSelected(const Types::SafePtr<GameObject>& gameObject) {
    m_selectedMutex.lock();

    auto components = gameObject->GetComponents();
    for (Framework::Helper::Component* comp : components) // TODO: unsafe
        comp->OnSelected(false);

    if (auto find = m_selectedGameObjects.find(gameObject); find == m_selectedGameObjects.end()) {
        Helper::Debug::Error("Scene::RemoveSelected() : \""+gameObject->GetName() + "\" not found!");
        m_selectedMutex.unlock();
        return false;
    } else {
        m_selectedGameObjects.erase(find);
        m_selectedMutex.unlock();
        return true;
    }
}

void Framework::Helper::Scene::UnselectAll() {
    m_selectedMutex.lock();

    for (const auto& gameObject : m_selectedGameObjects) {
        auto components = gameObject->GetComponents(); //TODO: double lock?
        for (Framework::Helper::Component* comp : components)
            comp->OnSelected(false);

        gameObject->m_isSelect = false;
    }

    this->m_selectedGameObjects.clear();

    m_selectedMutex.unlock();
}

Framework::Helper::Types::SafePtr<Framework::Helper::GameObject> Framework::Helper::Scene::FindByComponent(const std::string &name) {
    Types::SafePtr<GameObject> find;

    m_mutex.lock();

    for (const auto& gm : m_gameObjects)
        if (gm->ContainsComponent(name)) {
            find = gm;
            break;
        }

    m_mutex.unlock();

    return find;
}

void Framework::Helper::Scene::OnGameObjectNameChanged() {
    m_isHierarchyChanged = true;
}

void Framework::Helper::Scene::ForEachRootObjects(const std::function<void(Types::SafePtr<GameObject>)> &fun) {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    for (auto gm : m_gameObjects)
        if (gm.LockIfValid()) {
            if (!gm->GetParent())
                fun(gm);
            gm.Unlock();
        }
}

bool Framework::Helper::Scene::Save(const std::string& folder) {
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

