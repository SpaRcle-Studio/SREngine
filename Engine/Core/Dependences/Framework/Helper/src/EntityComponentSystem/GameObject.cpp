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

    UpdateEntityPath();
}

GameObject::~GameObject() {
    delete m_transform;
}

void GameObject::Free() {
    delete this;
}

bool Framework::Helper::GameObject::AddComponent(Framework::Helper::Component *component) {  // TODO: add security multi-threading
    if (this->m_isDestroy) {
        Debug::Error("GameObject::AddComponent() : this \""+m_name+"\" game object is destroyed!");
        return false;
    }

    component->SetParent(this);
    component->OnAttachComponent();
    m_components.push_back(component);

    UpdateComponents();

    return true;
}

Framework::Helper::Component *Framework::Helper::GameObject::GetComponent(const std::string& name) {
    Component* find = nullptr;

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

void GameObject::Destroy(DestroyBy by /* = DestroyBy::Other */) {
    if (m_isDestroy) {
        Helper::Debug::Error("GameObject::Destroy() : \"" + m_name + "\" game object already destroyed!");
        return;
    }

#ifdef SR_DEBUG
    if (!IsLocked())
        Helper::Debug::Warn("GameObject::Destroy() : game object \"" + GetName()
                            + "\" is not locked, crash or memory corruption possible!");

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("GameObject::Destroy() : destroying \"" + m_name + "\" game object contains " + std::to_string(m_components.size()) + " components...");
#endif

    if (m_scene.RecursiveLockIfValid()) {
        if (by == DestroyBy::Other && m_parent.LockIfValid()) {
            m_parent->RemoveChild(*this);
            m_parent.Unlock();
        }

        m_scene->Remove(*this);

        m_scene.Unlock();
    }

    for (Component* component : m_components)
        component->OnDestroyGameObject();
    m_components.clear();

    for (GameObject::Ptr gameObject : m_children) {
        gameObject.AutoFree([](GameObject* gm) {
            gm->Destroy(DestroyBy::GameObject);
            gm->Free();
        });
    }
    m_children.clear();

    m_isDestroy = true;

    if (by == DestroyBy::Other)
        Free();
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
    UpdateComponentsSkew();
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
    child->SetParent(*this);

    //!this->m_children.insert(std::make_pair(child, child));
    this->m_children.insert(child);

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

    if ((m_isSelect = value))
        m_scene->AddSelected(*this);
    else
       m_scene->RemoveSelected(*this);
}

std::string GameObject::GetName() const {
    return this->m_name;
}

std::vector<Component *> GameObject::GetComponents() {
    return m_components;
}

void GameObject::SetNameFromInspector(const std::string &name) {
    this->m_name = name;
    this->m_scene->OnChanged();
}

void GameObject::SetParent(const GameObject::Ptr& parent) {
    if (parent == m_parent) {
        return;
    }

    m_parent = parent;

    if (m_parent.Valid()) {
        m_transform->OnParentSet(m_parent->m_transform);
    }
    else
        m_transform->OnParentSet(nullptr);

    UpdateEntityPath();

    m_scene->OnChanged();
}

void GameObject::RemoveChild(const GameObject::Ptr& ptr) {
    if (!IsChild(ptr)) {
        SRAssert2(false, Format("GameObject %s is not child for %s!", ptr->GetName().c_str(), GetName().c_str()));
        return;
    }

    m_children.erase(ptr);
}

bool GameObject::ContainsComponent(const std::string &name) {
    for (auto comp : m_components)
        if (comp->GetComponentName() == name) {
            return true;
        }

    return false;
}

void GameObject::ForEachChild(const std::function<void(Types::SafePtr<GameObject>)> &fun) {
    for (auto child : m_children) {
        if (child.LockIfValid()) {
            fun(child);
            child.Unlock();
        }
    }
}

void GameObject::SetActive(bool value) {
    if (value != m_isActive)
        m_isActive = value;
    else
        return;

    for (auto child : m_children)
        if (child.LockIfValid()) {
            child->OnPrentSetActive(value);
            child.Unlock();
        }

    UpdateComponentsEnabled();
}

void GameObject::OnPrentSetActive(bool value) {
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
        if (!m_parent.Valid())
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
    for (auto component : m_components)
        if (!fun(component))
            break;
}

bool GameObject::RemoveComponent(Component *component) {
    for (auto it = m_components.begin(); it != m_components.end(); it++)
        if (*it == component) {
            component->OnRemoveComponent();
            m_components.erase(it);
            return true;
        }

    Helper::Debug::Error("GameObject::RemoveComponent() : component \"" + component->GetComponentName() + "\" not found!");

    return false;
}

Xml::Document GameObject::Save() const {
    auto doc = Xml::Document::New();
    auto root = doc.Root().AppendChild("GameObject");

    root.AppendAttribute("Name", m_name.c_str());
    root.AppendAttribute("Tag", m_tag.c_str());
    root.AppendAttribute("Enabled", IsEnabled());

    root.AppendChild(m_transform->Save().DocumentElement());

    if (!m_components.empty()) {
        auto components = root.AppendChild("Components");
        for (const auto &comp : m_components) {
            components.AppendChild(comp->Save().DocumentElement());
        }
    }

    if (!m_children.empty()) {
        auto children = root.AppendChild("Children");
        for (const auto &child : m_children)
            children.AppendChild(child->Save().DocumentElement());
    }

    return doc;
}

void GameObject::UpdateEntityPath() {
    GameObject::Ptr current = *this;
    EntityPath path;

    do {
        path.ConcatBack(current->GetEntityId());
        current = current->m_parent;
    }
    while(current.Valid());

    SetEntityPath(path);
}

bool GameObject::IsChild(const GameObject::Ptr &child) {
    return m_children.count(child) == 1;
}

void GameObject::UpdateComponentsSkew() {
    for (auto&& comp : m_components)
        comp->OnSkewed(m_transform->m_skew);
}

