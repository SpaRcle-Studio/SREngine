//
// Created by Nikita on 30.11.2020.
//

#include "EntityComponentSystem/Scene.h"
#include <EntityComponentSystem/GameObject.h>

#include <utility>
#include <Debug.h>

Framework::Helper::GameObject *Framework::Helper::Scene::Instance(std::string name) {
    GameObject* gm = new GameObject(this, std::move(name));

    m_mutex.lock();

    m_gameObjects[gm] = gm;

    m_mutex.unlock();

    return gm;
}

bool Framework::Helper::Scene::Destroy(Framework::Helper::GameObject *gameObject) {
    if (gameObject->m_scene != this)
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Scene::Destroy(GameObject*) : destroying \""+gameObject->m_name + "\" game object...");

    m_mutex.lock();

    m_gameObjects.erase(gameObject);

    gameObject->Destroy();

    m_mutex.unlock();

    return true;
}

Framework::Helper::Scene::Scene() {

}

Framework::Helper::Scene::~Scene() {

}

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

    m_mutex.lock();

    auto element = m_gameObjects.begin();
    while(element != m_gameObjects.end()){
        if (!element->second->m_parent)
            element->second->Destroy();
        element++;
    }

    m_mutex.unlock();

    this->m_isDestroy = true;

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
