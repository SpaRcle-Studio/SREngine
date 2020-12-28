//
// Created by Nikita on 27.11.2020.
//

#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Transform.h>
#include <EntityComponentSystem/Component.h>

#include <utility>
#include <Debug.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

using namespace Framework::Helper;

Framework::Helper::GameObject::GameObject(Scene* scene, std::string name, std::string tag) {
    m_name = std::move(name);
    m_tag = std::move(tag);
    m_scene = scene;

    m_transform = new Transform(this);
}

Framework::Helper::GameObject::~GameObject() {
    delete this->m_transform;
}

bool Framework::Helper::GameObject::AddComponent(Framework::Helper::Component *component) {
    if (this->m_isDestroy){
        Debug::Error("GameObject::AddComponent() : this \""+m_name+"\" game object is destroyed!");
        return false;
    }

    m_mutex.lock();

    m_components.push_back(component);

    m_mutex.unlock();
    return true;
}

Framework::Helper::Component *Framework::Helper::GameObject::GetComponent(std::string name) {
    Component* find = nullptr;

    m_mutex.lock();

    // TODO

    m_mutex.unlock();

    return find;
}

std::vector<Component *> Framework::Helper::GameObject::GetComponents(std::string name) {
    return std::vector<Component *>();
}

void Framework::Helper::GameObject::Destroy() {
    if (m_isDestroy){
        Helper::Debug::Error("GameObject::Destroy() : \"" +m_name + "\" game object already destroyed!");
        return;
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("GameObject::Destroy() : destroying \""+m_name + "\" game object contains "+std::to_string(m_components.size())+" components...");

    m_mutex.lock();

    for (Component* component : m_components)
        component->OnDestroyGameObject();

    for (auto gm : m_children)
        gm.second->Destroy();

    m_mutex.unlock();

    m_isDestroy = true;
}

void GameObject::UpdateComponentsPosition() {
    for (Component* component : m_components)
        component->OnMove(m_transform->m_globalPosition);
        //component->OnMove(m_transform->m_position + m_transform->m_parent_position);
}

void GameObject::UpdateComponentsRotation() {
    for (Component* component : m_components)
        component->OnRotate(m_transform->m_globalRotation);
        //component->OnRotate(m_transform->m_rotation); // + m_transform->m_parent_rotation //  - m_transform->m_parent_rotation * 2.f
}

void GameObject::UpdateComponentsScale() {
    for (Component* component : m_components)
        component->OnScaled(m_transform->m_globalScale); // or multiple
        //component->OnScaled(m_transform->m_scale + m_transform->m_parent_scale); // or multiple
}

nlohmann::json GameObject::Save() {
    nlohmann::json json;

    json["GameObject"]["Name"] = m_name;
    json["GameObject"]["Tag"] = m_tag;

    std::vector<nlohmann::json> comps = { m_transform->Save() };

    for (auto c : m_components)
        comps.push_back(c->Save());

    json["GameObject"]["Components"] = comps;

    return json;
}

bool GameObject::AddChild(GameObject *child) {
    auto find = m_children.find(child);
    if (find!=m_children.end()){
        Debug::Warn("GameObject::AddChild() : this child already exists in this game object!");
        return false;
    }

    child->m_parent = this;

    this->m_children.insert(std::make_pair(child, child));

    /* Update child transforms with parent */

    {
        child->m_transform->m_localPosition = child->m_transform->m_globalPosition - this->m_transform->m_globalPosition;
        std::cout << glm::to_string(child->m_transform->m_localPosition) << std::endl;
        child->UpdateComponentsPosition();
        child->m_transform->UpdateChildPosition(this->m_transform);
    }

    child->m_transform->m_childDefRotation = child->m_transform->GetNormalizedAngleOfPoint(m_transform->GetPosition());

    //child->m_transform->UpdateChildRotation(this->m_transform);
    //child->m_transform->UpdateChildScale(this->m_transform);

    //child->m_transform->Rotate();
    //child->m_transform->Scaling();

    return true;
}

