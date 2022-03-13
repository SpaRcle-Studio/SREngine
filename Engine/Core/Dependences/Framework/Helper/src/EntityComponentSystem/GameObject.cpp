//
// Created by Nikita on 27.11.2020.
//

#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Transform3D.h>
#include <EntityComponentSystem/Component.h>
#include <World/Scene.h>

#include <utility>
#include <Debug.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include <Math/Vector3.h>
#include <Math/Quaternion.h>
#include <Math/Matrix4x4.h>
#include <Math/Mathematics.h>

using namespace Framework::Helper;

Framework::Helper::GameObject::GameObject(const Types::SafePtr<World::Scene>& scene, std::string name, std::string tag)
    : Types::SafePtr<GameObject>(this)
{
    m_name  = std::move(name);
    m_tag   = std::move(tag);
    m_scene = scene;

    m_transform = new Transform3D(this);

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

void GameObject::Destroy(DestroyByFlagBits by /* = DestroyByFlags::DestroyBy_Other */) {
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
        const bool byParent = by & DestroyBy_GameObject;

        if (!byParent && m_parent.LockIfValid()) {
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
        gameObject.AutoFree([by](GameObject* gm) {
            gm->Destroy(by | DestroyBy_GameObject);
        });
    }
    m_children.clear();

    m_isDestroy = true;

    Free();
}

void GameObject::UpdateComponents() {
    UpdateComponentsPosition();
    UpdateComponentsRotation();
    UpdateComponentsScale();
    UpdateComponentsSkew();
}

void GameObject::UpdateComponentsPosition() {
    for (Component* component : m_components)
        component->OnMove(m_transform->GetTranslation());
}

void GameObject::UpdateComponentsRotation() {
    for (Component* component : m_components)
        component->OnRotate(m_transform->GetRotation());
}

void GameObject::UpdateComponentsScale() {
    for (Component* component : m_components)
        component->OnScaled(m_transform->GetScale());
}

void GameObject::UpdateComponentsSkew() {
    for (Component* component : m_components)
        component->OnSkewed(m_transform->m_skew);
}

bool GameObject::AddChild(const Types::SafePtr<GameObject>& child) { // TODO: add security multi-threading
    if (Contains(child)) {
        Debug::Warn("GameObject::AddChild() : this child already exists in this game object!");
        return false;
    }

    child->SetParent(*this);

    m_children.insert(child);

    /* TODO: Update child transforms with parent */

    m_scene->OnChanged();

    return true;
}

void GameObject::SetName(const std::string &name) {
    m_name = name;
    m_scene->OnChanged();
}

bool GameObject::Contains(const Types::SafePtr<GameObject>& gameObject) {  // TODO: add security multi-threading
    return m_children.count(gameObject) == 1;
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
    return m_name;
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

void GameObject::ForEachChild(const std::function<void(Types::SafePtr<GameObject>&)> &fun) {
    for (Types::SafePtr<GameObject> child : m_children) {
        if (child.LockIfValid()) {
            fun(child);
            child.Unlock();
        }
    }
}

void GameObject::ForEachChild(const std::function<void(const Types::SafePtr<GameObject>&)> &fun) const {
    for (const auto& child : m_children) {
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

    if (count != 0) {
        barycenter /= count;
        if (!m_parent.Valid())
            return barycenter;
        ///else
            ///return barycenter + m_transform->m_globalPosition;
    }

    return Math::FVector3(Math::InfinityFV3);
}

Math::FVector3 GameObject::GetHierarchyBarycenter() {
    auto barycenter = Math::FVector3((Math::Unit)0);
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

MarshalEncodeNode GameObject::Save(SavableFlags flags) const {
    MarshalEncodeNode marshal("GameObject");

    marshal.Append("Name", m_name);

    if (!(flags & Helper::SAVABLE_FLAG_ECS_NO_ID)) {
        marshal.Append("EntityId", static_cast<uint64_t>(GetEntityId()));
    }

    marshal.AppendDef("Tag", m_tag, "Untagged");
    marshal.AppendDef("Enabled", IsEnabled(), true);

    marshal.Append(m_transform->Save(flags));

    if (!m_components.empty()) {
        MarshalEncodeNode components("Components");
        for (const auto &comp : m_components) {
            if (auto compNode = comp->Save(flags); compNode.Valid()) {
                components.Append(compNode);
            }
        }
        marshal.Append(components);
    }

    if (!m_children.empty()) {
        MarshalEncodeNode children("Children");
        for (const auto &child : m_children)
            children.Append(child->Save(flags));
        marshal.Append(children);
    }

    return marshal;
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

Component *GameObject::GetComponent(size_t id) {
    for (auto&& component : m_components)
        if (component->GetComponentId() == id)
           return component;
    return nullptr;
}

void GameObject::SetTransform(Transform3D* transform3D) {
    if (m_transform == transform3D || !transform3D) {
        SR_WARN("GameObject::SetTransform() : invalid transform!");
    }
    else {
        delete m_transform;
        m_transform = transform3D;
        m_transform->SetGameObject(this);
    }
}

std::list<EntityBranch> GameObject::GetEntityBranches() const {
    std::list<EntityBranch> branches;

    ForEachChild([&branches](const GameObject::Ptr& ptr) {
        branches.emplace_back(ptr->GetEntityTree());
    });

    return std::move(branches);
}


