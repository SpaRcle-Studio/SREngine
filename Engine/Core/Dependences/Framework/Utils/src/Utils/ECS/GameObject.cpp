 //
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/Component.h>

#include <Utils/World/Scene.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Math/Quaternion.h>
#include <Utils/Math/Matrix4x4.h>
#include <Utils/Math/Mathematics.h>

namespace SR_UTILS_NS {
    GameObject::GameObject(const Types::SafePtr<World::Scene> &scene, std::string name, std::string tag)
        : Types::SafePtr<GameObject>(this)
    {
        m_name = std::move(name);
        m_tag = std::move(tag);
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

    bool GameObject::AddComponent(Component *component) {  // TODO: add security multi-threading
        if (m_isDestroy) {
            SR_ERROR("GameObject::AddComponent() : this \"" + m_name + "\" game object is destroyed!");
            return false;
        }

        component->SetParent(this);
        m_components.push_back(component);

        UpdateComponents();

        return true;
    }

    Component *Framework::Helper::GameObject::GetComponent(const std::string &name) {
        Component *find = nullptr;

        for (auto&& component : m_components) {
            if (component->GetComponentName() == name) {
                find = component;
                break;
            }
        }

        return find;
    }

    void GameObject::Destroy(GODestroyByFlagBits by /** = DestroyByFlags::DestroyBy_Other */) {
        if (m_isDestroy) {
            SR_ERROR("GameObject::Destroy() : \"" + m_name + "\" game object already destroyed!");
            return;
        }

#ifdef SR_DEBUG
        if (!IsLocked())
            SR_WARN("GameObject::Destroy() : game object \"" + GetName()
                                + "\" is not locked, crash or memory corruption possible!");

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= Debug::Level::High) {
            SR_LOG("GameObject::Destroy() : destroying \"" + m_name + "\" game object contains " + std::to_string(m_components.size()) + " components...");
        }
#endif

        if (m_scene.RecursiveLockIfValid()) {
            const bool byParent = by & GameObject_DestroyBy_GameObject;

            if (!byParent && m_parent.LockIfValid()) {
                GameObject::Ptr copy = m_parent;
                copy->RemoveChild(*this);
                copy.Unlock();
            }

            m_scene->Remove(*this);

            m_scene.Unlock();
        }

        for (auto&& component : m_components) {
            component->SetParent(nullptr);
            component->OnDestroy();
        }
        m_components.clear();

        for (GameObject::Ptr gameObject : m_children) {
            gameObject.AutoFree([by](GameObject *gm) {
                gm->Destroy(by | GameObject_DestroyBy_GameObject);
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
        for (Component *component : m_components)
            component->OnMove(m_transform->GetTranslation());
    }

    void GameObject::UpdateComponentsRotation() {
        for (Component *component : m_components)
            component->OnRotate(m_transform->GetRotation());
    }

    void GameObject::UpdateComponentsScale() {
        for (Component *component : m_components)
            component->OnScaled(m_transform->GetScale());
    }

    void GameObject::UpdateComponentsSkew() {
        for (Component *component : m_components)
            component->OnSkewed(m_transform->m_skew);
    }

    bool GameObject::AddChild(const Types::SafePtr<GameObject> &child) {
        if (child == *this) {
            SRAssert2(false, "It is impossible to make a parent a child!");
            return false;
        }

        if (child->GetParent()) {
            SRAssert2(false, "Child has parent!");
            return false;
        }

        if (Contains(child)) {
            SRAssert2(false, "This child already exists in this game object!");
            return false;
        }

        if (!child->SetParent(*this)) {
            SR_WARN("GameObject::AddChild() : failed to set parent!");
            return false;
        }

        m_children.insert(child);

        /* TODO: Update child transforms with parent */

        m_scene->OnChanged();

        return true;
    }

    void GameObject::SetName(const std::string &name) {
        m_name = name;
        m_scene->OnChanged();
    }

    void GameObject::SetTag(const std::string &tag) {
        m_tag = tag;
        m_scene->OnChanged();
    }

    bool GameObject::Contains(const Types::SafePtr<GameObject> &gameObject) {  // TODO: add security multi-threading
        return m_children.count(gameObject) == 1;
    }

    std::string GameObject::GetName() const {
        return m_name;
    }

    bool GameObject::SetParent(const GameObject::Ptr &parent) {
        if (parent == m_parent) {
            return false;
        }

        GameObject::Ptr oldParent = m_parent;
        m_parent = parent;

        if (!UpdateEntityPath()) {
            m_parent = oldParent;
            return false;
        }

        if (m_parent.Valid()) {
            m_transform->OnParentSet(m_parent->m_transform);
        }
        else
            m_transform->OnParentSet(nullptr);

        m_scene->OnChanged();

        return true;
    }

    void GameObject::RemoveChild(const GameObject::Ptr &ptr) {
        if (!IsChild(ptr)) {
            SRAssert2(false, Format("GameObject %s is not child for %s!", ptr->GetName().c_str(), GetName().c_str()));
            return;
        }

        ptr->SetParent(GameObject::Ptr());
        m_children.erase(ptr);
    }

    bool GameObject::ContainsComponent(const std::string &name) {
        for (auto&& pComponent : m_components) {
            if (pComponent->GetComponentName() == name) {
                return true;
            }
        }

        return false;
    }

    void GameObject::ForEachChild(const std::function<void(Types::SafePtr<GameObject> &)> &fun) {
        for (Types::SafePtr<GameObject> child : m_children) {
            if (child.LockIfValid()) {
                fun(child);
                child.Unlock();
            }
        }
    }

    void GameObject::ForEachChild(const std::function<void(const Types::SafePtr<GameObject> &)> &fun) const {
        for (const auto &child : m_children) {
            if (child.LockIfValid()) {
                fun(child);
                child.Unlock();
            }
        }
    }

    void GameObject::SetEnabled(bool value) {
        if (m_isEnabled == value) {
            return;
        }

        m_isEnabled = value;

        CheckActivity();
    }

    bool GameObject::IsActive() const {
        if (m_parent.RecursiveLockIfValid()) {
            const bool parentActive = m_parent->m_isActive;
            m_parent.Unlock();
            return IsEnabled() && parentActive;
        }

        return IsEnabled();
    }

    void GameObject::CheckActivity(bool force) {
        const bool isActive = IsActive();
        if (isActive == m_isActive && !force) {
            return;
        }

        m_isActive = isActive;

        for (auto&& child : m_children) {
            if (child.LockIfValid()) {
                child->CheckActivity(force);
                child.Unlock();
            }
        }

        for (auto&& pComponent : m_components) {
            pComponent->CheckActivity();
        }
    }

    SR_MATH_NS::FVector3 GameObject::GetBarycenter() {
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
        auto barycenter = Math::FVector3((Math::Unit) 0);
        uint32_t count = 0;

        if (auto self = this->GetBarycenter(); !self.IsInfinity()) {
            barycenter += self;
            count++;
        }

        ForEachChild([=](const Types::SafePtr<GameObject> &child) mutable {
            if (auto self = this->GetBarycenter(); !self.IsInfinity()) {
                barycenter += self;
                count++;
            }
        });

        return count == 0 ? Math::InfinityFV3 : barycenter / count;
    }

    void GameObject::ForEachComponent(const std::function<bool(Component *)> &fun) {
        for (auto&& component : m_components) {
            if (!fun(component)) {
                break;
            }
        }
    }

    bool GameObject::RemoveComponent(Component *component) {
        for (auto it = m_components.begin(); it != m_components.end(); ++it) {
            if (*it == component) {
                component->OnDestroy();
                m_components.erase(it);
                return true;
            }
        }

        SR_ERROR("GameObject::RemoveComponent() : component \"" + component->GetComponentName() + "\" not found!");

        return false;
    }

    SR_HTYPES_NS::Marshal GameObject::Save(SavableFlags flags) const {
        SR_HTYPES_NS::Marshal marshal = Entity::Save(flags);

        marshal.Write(VERSION);

        marshal.Write(IsEnabled());
        marshal.Write(m_name);

        if (HasTag()) {
            marshal.Write(true);
            marshal.Write(m_tag);
        }
        else {
            marshal.Write(false);
        }

        marshal.Append(m_transform->Save(flags));

        marshal.Write(static_cast<uint32_t>(m_components.size()));
        for (auto&& component : m_components) {
            auto&& marshalComponent = component->Save(flags);
            marshal.Write<uint64_t>(marshalComponent.BytesCount());
            marshal.Append(std::move(marshalComponent));
        }

        marshal.Write(static_cast<uint32_t>(m_children.size()));
        for (auto&& child : m_children) {
            marshal.Append(child->Save(flags));
        }

        return marshal;
    }

    bool GameObject::UpdateEntityPath() {
        GameObject::Ptr current = *this;
        EntityPath path;

        do {
            path.ConcatBack(current->GetEntityId());
            current = current->m_parent;

            if (current && current->GetEntityId() == GetEntityId()) {
                SRAssert2(false, "Recursive entity path!");
                return false;
            }
        } while (current.Valid());

        SetEntityPath(path);

        return true;
    }

    bool GameObject::IsChild(const GameObject::Ptr &child) {
        return m_children.count(child) == 1;
    }

    Component *GameObject::GetComponent(size_t id) {
        for (auto &&component : m_components) {
            if (component->GetComponentId() == id) {
                return component;
            }
        }

        return nullptr;
    }

    void GameObject::SetTransform(Transform3D *transform3D) {
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

        ForEachChild([&branches](const GameObject::Ptr &ptr) {
            branches.emplace_back(ptr->GetEntityTree());
        });

        return std::move(branches);
    }

    bool GameObject::MoveToTree(const GameObject::Ptr &destination) {
        if (m_parent) {
            GameObject::Ptr copy = m_parent;
            if (copy.RecursiveLockIfValid()) {
                copy->RemoveChild(*this);
                copy->Unlock();
            }
        }

        return destination->AddChild(*this);
    }

    bool GameObject::HasTag() const {
        return m_tag != "Untagged";
    }

    void GameObject::Awake() {
        if (!IsEnabled()) {
            return;
        }

        for (auto&& pComponent : m_components) {
            pComponent->Awake();
        }

        for (auto&& child : m_children) {
            child->Awake();
        }
    }

    void GameObject::Start() {
        if (!IsEnabled()) {
            return;
        }

        for (auto&& pComponent : m_components) {
            pComponent->Start();
        }

        for (auto&& child : m_children) {
            child->Start();
        }
    }
}