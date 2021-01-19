//
// Created by Nikita on 30.11.2020.
//

#include "EntityComponentSystem/Scene.h"
#include <EntityComponentSystem/GameObject.h>

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
        Helper::Debug::Warn("Scene::Destroy() : scene game objects now using at "+std::to_string(m_countUses)+" points!");
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
        std::cout << std::string(deep + 1, '\t') << a->m_data->GetName() + "\n";
        pr(a, deep + 1);
    }
}
void Framework::Helper::Scene::Print() {
    Branch<GameObject*>* tree = this->GetTree();

    std::cout << std::endl;

    if (!tree->m_branches.empty()) {
        for (auto a : tree->m_branches) {
            std::cout << a->m_data->GetName() + "\n";
            pr(a, 0);
        }
    }
}

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

        /*
        auto child1 = new Branch<GameObject*>(nullptr);
        m_tree->AddChild(child1);

        auto child11 = new Branch<GameObject*>(nullptr);
        child1->AddChild(child11);

        auto child12 = new Branch<GameObject*>(nullptr);
        child1->AddChild(child12);

        auto child121 = new Branch<GameObject*>(nullptr);
        child12->AddChild(child121);

        auto child2 = new Branch<GameObject*>(nullptr);
        m_tree->AddChild(child2);
        */

        /*std::stack<GameObject*> stack_gm;
        std::stack<Branch<GameObject*>*> stack_br;

        stack_br.push(m_tree);

        for (auto& a : m_gameObjects) {
            if (a.second->m_parent)
                continue;
            else {
                stack_gm.push(a.second);

                if (stack_gm.top()->m_children.empty()) {
                    stack_br.top()->AddChild(new Branch<GameObject *>(stack_gm.top()));
                    stack_gm.pop();
                }
                else {

                }
            }
        }

        stack_br.pop();*/

        m_mutex.unlock();

        return m_tree;
    }
}
