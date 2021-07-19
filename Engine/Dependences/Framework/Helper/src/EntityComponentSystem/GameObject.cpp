//
// Created by Nikita on 27.11.2020.
//

#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Transform.h>
#include <EntityComponentSystem/Component.h>
#include <EntityComponentSystem/Scene.h>

#include <utility>
#include <Debug.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include <Math/Vector3.h>
#include <Math/Quaternion.h>
#include <Math/Matrix4x4.h>

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

bool Framework::Helper::GameObject::AddComponent(Framework::Helper::Component *component) {  // TODO: add security multi-threading
    if (this->m_isDestroy){
        Debug::Error("GameObject::AddComponent() : this \""+m_name+"\" game object is destroyed!");
        return false;
    }

    m_mutex.lock();

    component->SetParent(this);
    m_components.push_back(component);

    UpdateComponents();

    m_mutex.unlock();
    return true;
}

Framework::Helper::Component *Framework::Helper::GameObject::GetComponent(const std::string& name) {  // TODO: add security multi-threading
    Component* find = nullptr;

    m_mutex.lock();

    for (auto component : m_components)
        if (component->GetComponentName() == name) {
            find = component;
            break;
        }

    m_mutex.unlock();

    return find;
}

std::vector<Component *> Framework::Helper::GameObject::GetComponents(const std::string& name) {  // TODO: add security multi-threading
    return std::vector<Component *>();
}

void Framework::Helper::GameObject::Destroy() { // TODO: remove from scene!
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
        gm->Destroy();

    m_mutex.unlock();

    m_isDestroy = true;
}


void GameObject::UpdateComponents() {
    /*for (Component* component : m_components){
        component->OnMove(m_transform->m_globalPosition.ToGLM());
        //component->OnRotate(glm::degrees(glm::eulerAngles(m_transform->m_globalRotation)));
        //component->OnRotate(m_transform->m_globalRotation.EulerAngle().Degrees().ToGLM());
        component->OnRotate(m_transform->m_globalRotation.ToGLM());
        component->OnScaled(m_transform->m_globalScale.ToGLM());
    }*/
    UpdateComponentsPosition();
    UpdateComponentsRotation();
    UpdateComponentsScale();
}

void GameObject::UpdateComponentsPosition() {
    for (Component* component : m_components)
        component->OnMove(m_transform->m_globalPosition);
        //component->OnMove(m_transform->m_position + m_transform->m_parent_position);
}

void GameObject::UpdateComponentsRotation() {
    for (Component* component : m_components)
        //component->OnRotate(m_transform->m_globalRotation.EulerAngle().Degrees().ToGLM());
        component->OnRotate(m_transform->m_globalRotation);
        //component->OnRotate(glm::degrees(glm::eulerAngles(m_transform->m_globalRotation);
        //component->OnRotate(m_transform->m_rotation); // + m_transform->m_parent_rotation //  - m_transform->m_parent_rotation * 2.f

}

void GameObject::UpdateComponentsScale() {
    for (Component* component : m_components)
        component->OnScaled(m_transform->m_globalScale.ToGLM()); // or multiple
        //component->OnScaled(m_transform->m_scale + m_transform->m_parent_scale); // or multiple
}

bool GameObject::AddChild(GameObject *child) { // TODO: add security multi-threading
    //!auto find = m_children.find(child);
    //!if (find!=m_children.end()){
    if (Contains(child)) {
        Debug::Warn("GameObject::AddChild() : this child already exists in this game object!");
        return false;
    }

    //child->m_parent = this;
    child->SetParent(this);

    //!this->m_children.insert(std::make_pair(child, child));
    this->m_children.push_back(child);
    this->m_countChild++;

    /* Update child transforms with parent */

    //TODO
    {
        //!child->m_transform->m_localPosition = child->m_transform->m_globalPosition - this->m_transform->m_globalPosition;
        //std::cout << glm::to_string(child->m_transform->m_localPosition) << std::endl;
        //!child->UpdateComponentsPosition();
        //!child->m_transform->UpdateChildPosition(this->m_transform, glm::vec3(0,0,0)); //TODO!!!!!!!!!
    }

    //child->m_transform->m_childDefRotation = child->m_transform->GetNormalizedAngleOfPoint(m_transform->GetPosition());

    //child->m_transform->UpdateChildRotation(this->m_transform);
    //child->m_transform->UpdateChildScale(this->m_transform);

    //child->m_transform->Rotate();
    //child->m_transform->Scaling();

    this->m_scene->SetIsChanged(true);

    return true;
}

void GameObject::SetName(const std::string &name) {
    ret:
    if (m_scene->GetCountUsesPoints() > 0)
        goto ret;
    else
        m_scene->AddUsePoint();

    this->m_name = name;

    m_scene->RemoveUsePoint();
}

bool GameObject::Contains(GameObject *child) {  // TODO: add security multi-threading
    for (auto a : m_children){
        if (a == child)
            return true;
    }
    return false;
}

void GameObject::SetSelect(bool value) {
    if (value == m_isSelect)
        return;
    else {
        m_isSelect = value;

        if (m_isSelect)
            m_scene->AddSelected(this);
        else
           m_scene->RemoveSelected(this);
    }
}

std::string GameObject::GetName() noexcept  { // TODO: UNSAFE
    /*ret:
    if (m_scene->GetCountUsesPoints() > 0)
        goto ret;
    else
        m_scene->AddUsePoint();

    std::string str = m_name;

    m_scene->RemoveUsePoint();

    return str;*/
    return this->m_name;
}

std::vector<Component *> GameObject::GetComponents() { // TODO: MAYBE UNSAFE
    std::vector<Component *> comps = std::vector<Component *>();

    m_mutex.lock();

    comps = m_components;

    m_mutex.unlock();

    return comps;
}

void GameObject::SetNameFromInspector(const std::string &name) {
    if (m_scene->GetCountUsesPoints() > 1) {
        Debug::Error("GameObject::SetNameFromInspector(): count uses more 1, something went wrong...");
        return;
    }

    m_scene->AddUsePoint();

    this->m_name = name;

    m_scene->RemoveUsePoint();
}

void GameObject::SetParent(GameObject *gm)  {
    this->m_parent = gm;
    this->m_transform->OnParentSet(gm->m_transform);
}

void GameObject::RemoveParent(GameObject *gm) {
    this->m_transform->OnParentRemove(gm->m_transform);
    this->m_parent = nullptr;
}

bool GameObject::ContainsComponent(const std::string &name) {
    m_mutex.lock();

    for (auto comp : m_components)
        if (comp->GetComponentName() == name) {
            m_mutex.unlock();
            return true;
        }

    m_mutex.unlock();
    return false;
}
