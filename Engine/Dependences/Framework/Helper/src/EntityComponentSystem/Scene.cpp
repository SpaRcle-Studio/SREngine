//
// Created by Nikita on 30.11.2020.
//

#include "EntityComponentSystem/Scene.h"
#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Component.h>

#include <utility>
#include <Debug.h>

Framework::Helper::GameObject *Framework::Helper::Scene::Instance(const std::string& name) {
    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Scene::Instance() : instance \""+name+"\" game object at \""+m_name+ "\" scene.");

    auto* gm = new GameObject(this, name);

    m_mutex.lock();

    m_gameObjects.insert(gm);

    m_mutex.unlock();

    this->m_hierarchyIsChanged = true;

    return gm;
}

/*
bool Framework::Helper::Scene::DestroyGameObject(Framework::Helper::GameObject *gameObject) {
    if (gameObject->m_scene != this)
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Scene::Destroy(GameObject*) : destroying \""+gameObject->m_name + "\" game object...");

    m_mutex.lock();

    m_gameObjects.erase(gameObject);

    gameObject->Destroy();

    m_mutex.unlock();

    this->m_hierarchyIsChanged = true;

    return true;
}*/

Framework::Helper::Scene *Framework::Helper::Scene::New(const std::string& name) {
    Debug::Log("Scene::New() : creating new scene...");
    auto* scene = new Scene();
    scene->m_name = name;
    return scene;
}

Framework::Helper::Scene *Framework::Helper::Scene::Load(const std::string& name) {
    return nullptr;
}

bool Framework::Helper::Scene::Destroy() {
    if (m_isDestroy) {
        Debug::Error("Scene::Destroy() : scene \""+m_name+"\" already destroyed!");
        return false;
    }

    Debug::Log("Scene::Destroy() : destroying \""+m_name+"\" scene contains "+ std::to_string(m_gameObjects.size()) +" game objects...");

    if (m_countUses) {
        Helper::Debug::Error("Scene::Destroy() : scene game objects now using at "+std::to_string(m_countUses)+" points! Wait...");
        ret:
            if (m_countUses)
                goto ret;
    }

    m_mutex.lock();

    /*
    auto element = m_gameObjects.begin();
    while(element != m_gameObjects.end()){
        if (!element->second->m_parent)
            element->second->Destroy();
        element++;
    }*/

    for (auto gameObject : m_gameObjects)
        if (!gameObject->GetParent())
            gameObject->Destroy();

    m_mutex.unlock();

    this->m_isDestroy = true;

    this->m_hierarchyIsChanged = true;

    return true;
}

bool Framework::Helper::Scene::Free() {
    if (!this->m_isDestroy) {
        Debug::Error("Scene::Free() : scene \""+m_name+"\" is not destroyed!");
        return false;
    }

    Debug::Log("Scene::Free() : free \""+m_name+"\" scene pointer...");

    delete this;
    return true;
}

// Please, call from only one thread!
std::vector<Framework::Helper::GameObject *>& Framework::Helper::Scene::GetRootGameObjects() noexcept {
    if (!m_hierarchyIsChanged && !m_rootObjectsEmpty)
        return this->m_rootObjects;
    else {
        m_mutex.lock();

        if (!m_rootObjectsEmpty) {
            m_rootObjects.clear();
            m_rootObjects.reserve(2000); //TODO: change to count_gm * 25 / 100
            m_rootObjectsEmpty = true;
        }

        for (auto& a : m_gameObjects)
            if (!a->GetParent())
                m_rootObjects.push_back(a);

        m_rootObjectsEmpty = false;
        m_mutex.unlock();
        return m_rootObjects;
    }
}

void Framework::Helper::Scene::AddSelected(Framework::Helper::GameObject *gameObject) {
    m_selectedMutex.lock();

    this->m_selectedGameObjects.push_back(gameObject);

    auto components = gameObject->GetComponents();
    for (Framework::Helper::Component* comp : components)
        comp->OnSelected(true);

    this->m_countSelected++;

    m_selectedMutex.unlock();
}

bool Framework::Helper::Scene::RemoveSelected(Framework::Helper::GameObject *gameObject) {
    m_selectedMutex.lock();

    bool found = false;

    auto components = gameObject->GetComponents();
    for (Framework::Helper::Component* comp : components)
        comp->OnSelected(false);

    for (size_t t = 0; t < m_selectedGameObjects.size(); t++)
        if (gameObject == m_selectedGameObjects[t]){
            this->m_countSelected--;
            m_selectedGameObjects.erase(m_selectedGameObjects.begin() + t);
            found = true;
            break;
        }

    if (!found)
        Helper::Debug::Error("Scene::RemoveSelected() : \""+gameObject->GetName() + "\" not found!");
    else {

    }

    m_selectedMutex.unlock();

    return found;
}

void Framework::Helper::Scene::UnselectAll() {
    m_selectedMutex.lock();

    for (auto gameObject : m_selectedGameObjects) {
        auto components = gameObject->GetComponents();
        for (Framework::Helper::Component* comp : components)
            comp->OnSelected(false);

        gameObject->m_isSelect = false;
    }

    this->m_countSelected = 0;
    this->m_selectedGameObjects.clear();

    m_selectedMutex.unlock();
}

Framework::Helper::GameObject *Framework::Helper::Scene::FindByComponent(const std::string &name) {
    GameObject* find = nullptr;

    m_mutex.lock();

    for (auto gm : m_gameObjects)
        if (gm->ContainsComponent(name)) {
            find = gm;
            break;
        }

    m_mutex.unlock();

    return find;
}

//bool Framework::Helper::Scene::RemoveGameObject(const GameObject* gameObject) {
//    return false; // TODO!
//}
