//
// Created by Nikita on 30.11.2020.
//

#include "EntityComponentSystem/Scene.h"
#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Component.h>

#include <utility>
#include <Debug.h>

Framework::Helper::GameObject *Framework::Helper::Scene::Instance(std::string name) {
    if (Debug::GetLevel() >= Debug::Level::Medium)
        Debug::Log("Scene::Instance() : instance \""+name+"\" game object at \""+m_name+ "\" scene.");

    auto* gm = new GameObject(this, std::move(name));

    m_mutex.lock();

    m_gameObjects[gm] = gm;

    m_mutex.unlock();

    this->m_hierarchyIsChanged = true;

    return gm;
}

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
}

Framework::Helper::Scene::Scene() = default;
Framework::Helper::Scene::~Scene() = default;

Framework::Helper::Scene *Framework::Helper::Scene::New(std::string name) {
    Debug::Log("Scene::New() : creating new scene...");
    auto* scene = new Scene();
    scene->m_name = std::move(name);
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

    auto element = m_gameObjects.begin();
    while(element != m_gameObjects.end()){
        if (!element->second->m_parent)
            element->second->Destroy();
        element++;
    }

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

void pr(Framework::Helper::Branch<Framework::Helper::GameObject*>* tree, int deep){
    for (auto a : tree->m_branches) {
//        std::cout << std::string(deep + 1, '\t') << a->m_data->GetName() + "\n";
        pr(a, deep + 1);
    }
}
void Framework::Helper::Scene::Print() {
    /*Branch<GameObject*>* tree = this->GetTree();

    std::cout << std::endl;

    if (!tree->m_branches.empty()) {
        for (auto a : tree->m_branches) {
            std::cout << a->m_data->GetName() + "\n";
            pr(a, 0);
        }
    }*/
}

/*
void req(Framework::Helper::Branch<Framework::Helper::GameObject*>* tree, Framework::Helper::GameObject* gameObject, int deep) {
    for (auto a : gameObject->GetChildren()) {
        //std::cout << std::string(deep + 1, '\t') << a->GetName() << std::endl;
        auto branch = new Framework::Helper::Branch<Framework::Helper::GameObject *>(a);
        tree->AddChild(branch);
        req(branch, a, deep + 1);
    }
}
Framework::Helper::Branch<Framework::Helper::GameObject *> *Framework::Helper::Scene::GetTree()  {
    if (!m_hierarchyIsChanged && m_tree)
        return this->m_tree;
    else {
        if (m_tree)
            m_tree->Free();

        this->m_tree = new Branch<GameObject*>(nullptr);

        m_mutex.lock();

        for (auto& a : m_gameObjects)
            if (!a.second->m_parent) {
                //std::cout << a.second->GetName() << std::endl;
                auto* branch = new Branch<GameObject*>(a.second);
                m_tree->AddChild(branch);
                req(branch, a.second, 0);
            }

        m_mutex.unlock();

        return m_tree;
    }
}
*/

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
            if (!a.second->m_parent)
                m_rootObjects.push_back(a.second);

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
