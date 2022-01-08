//
// Created by Nikita on 27.11.2020.
//

#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Transform.h>
#include <EntityComponentSystem/Component.h>
#include <World/Scene.h>

#include <utility>
#include <Debug.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include <Math/Vector3.h>
#include <Math/Quaternion.h>
#include <Math/Matrix4x4.h>

using namespace Framework::Helper;

Framework::Helper::GameObject::GameObject(const Types::SafePtr<World::Scene>& scene, std::string name, std::string tag)
    : Types::SafePtr<GameObject>(this)
{
    m_name  = std::move(name);
    m_tag   = std::move(tag);
    m_scene = scene;

    m_transform = new Transform(this);
}

bool Framework::Helper::GameObject::AddComponent(Framework::Helper::Component *component) {  // TODO: add security multi-threading
    if (this->m_isDestroy){
        Debug::Error("GameObject::AddComponent() : this \""+m_name+"\" game object is destroyed!");
        return false;
    }

    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    component->SetParent(this);
    component->OnAttachComponent();
    m_components.push_back(component);

    UpdateComponents();

    return true;
}

Framework::Helper::Component *Framework::Helper::GameObject::GetComponent(const std::string& name) {
    Component* find = nullptr;

    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    for (auto component : m_components)
        if (component->GetComponentName() == name) {
            find = component;
            break;
        }

    return find;
}

std::vector<Component *> Framework::Helper::GameObject::GetComponents(const std::string& name) {  // TODO: add security multi-threading
    return std::vector<Component *>();
}

void Framework::Helper::GameObject::DestroyFromScene() {
    if (m_isDestroy){
        Helper::Debug::Error("GameObject::Destroy() : \"" +m_name + "\" game object already destroyed!");
        return;
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("GameObject::Destroy() : destroying \""+m_name + "\" game object contains " + std::to_string(m_components.size()) + " components...");

    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    for (Component* component : m_components)
        component->OnDestroyGameObject();

    for (const auto& gm : m_children)
        gm->DestroyFromScene();

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

bool GameObject::AddChild(const Types::SafePtr<GameObject>& child) { // TODO: add security multi-threading
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

    /* TODO: Update child transforms with parent */

    this->m_scene->OnChanged();

    return true;
}

void GameObject::SetName(const std::string &name) {
    this->m_name = name;
    this->m_scene->OnChanged();
}

bool GameObject::Contains(const Types::SafePtr<GameObject>& child) {  // TODO: add security multi-threading
    for (const auto& a : m_children){
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
            m_scene->AddSelected(*this);
        else
           m_scene->RemoveSelected(*this);
    }
}

std::string GameObject::GetName() noexcept  {
    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    return this->m_name;
}

std::vector<Component *> GameObject::GetComponents() {
    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    return m_components;
}

void GameObject::SetNameFromInspector(const std::string &name) {
    this->m_name = name;
    this->m_scene->OnChanged();
}

void GameObject::SetParent(GameObject *gm)  {
    this->m_parent = gm;
    this->m_transform->OnParentSet(gm->m_transform);
    this->m_scene->OnChanged();
}

void GameObject::RemoveParent(GameObject *gm) {
    this->m_transform->OnParentRemove(gm->m_transform);
    this->m_parent = nullptr;
    this->m_scene->OnChanged();
}

bool GameObject::ContainsComponent(const std::string &name) {
    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    for (auto comp : m_components)
        if (comp->GetComponentName() == name) {
            return true;
        }

    return false;
}

void GameObject::Free() {
    delete this;
}

GameObject::~GameObject() {
    delete m_transform;
}

void GameObject::ForEachChild(const std::function<void(Types::SafePtr<GameObject>)> &fun) {
    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    for (auto child : m_children)
        if (child.LockIfValid()) {
            fun(child);
            child.Unlock();
        }
}

void GameObject::SetActive(bool value) {
    if (value != m_isActive)
        m_isActive = value;
    else
        return;

    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    for (auto child : m_children)
        if (child.LockIfValid()) {
            child->OnPrentSetActive(value);
            child.Unlock();
        }

    UpdateComponentsEnabled();
}

void GameObject::OnPrentSetActive(bool value) {
    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    m_isParentActive = value;

    for (auto child : m_children)
        if (child.LockIfValid()) {
            child->OnPrentSetActive(value);
            child.Unlock();
        }

    UpdateComponentsEnabled();
}

void GameObject::UpdateComponentsEnabled() {
    for (auto comp : m_components)
        comp->SetActive(m_isParentActive && m_isActive);
}

Math::FVector3 GameObject::GetBarycenter() {
    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    auto barycenter = Math::FVector3();
    uint32_t count = 0;

    for (auto comp : m_components)
        if (auto br = comp->GetBarycenter(); !br.IsInfinity()) {
            barycenter += br;
            count++;
        }

    if (count == 0)
        return Math::InfinityFV3;
    else {
        barycenter /= count;
        if (!m_parent)
            return barycenter;
        else
            return barycenter + m_transform->m_globalPosition;
    }
}

Math::FVector3 GameObject::GetHierarchyBarycenter() {
    auto barycenter = FVector3((Unit)0);
    uint32_t count = 0;

    if (auto self = this->GetBarycenter(); !self.IsInfinity()) {
        barycenter += self;
        count++;
    }

    ForEachChild([=](const Types::SafePtr<GameObject>& child) mutable {
        if (auto self = this->GetBarycenter(); !self.IsInfinity()) {
            barycenter += self;
            count++;
        }
    });

    return count == 0 ? Math::InfinityFV3 : barycenter / count;
}

void GameObject::ForEachComponent(const std::function<bool(Component*)> &fun) {
    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    for (auto component : m_components)
        if (!fun(component))
            break;
}

bool GameObject::RemoveComponent(Component *component) {
    std::lock_guard<std::recursive_mutex> locker(m_mutex);

    for (auto it = m_components.begin(); it != m_components.end(); it++)
        if (*it == component) {
            component->OnRemoveComponent();
            m_components.erase(it);
            return true;
        }

    Helper::Debug::Error("GameObject::RemoveComponent() : component \"" + component->GetComponentName() + "\" not found!");

    return false;
}
