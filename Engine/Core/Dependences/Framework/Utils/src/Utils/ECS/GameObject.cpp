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
#include <Utils/Types/SafePtrLockGuard.h>

namespace SR_UTILS_NS {
    GameObject::GameObject(const Types::SafePtr<World::Scene> &scene, std::string name, std::string tag)
        : Types::SafePtr<GameObject>(this)
    {
        m_name = std::move(name);
        m_tag = std::move(tag);
        m_scene = scene;

        SetTransform(new Transform3D());

        UpdateEntityPath();
    }

    GameObject::~GameObject() {
        delete m_transform;
    }

    void GameObject::Free() {
        delete this;
    }

    Component *Framework::Helper::GameObject::GetComponent(const std::string &name) {
        Component *find = nullptr;

        m_components.Do([&](std::list<Component*>& data) {
            for (auto &&component : data) {
                if (component->GetComponentName() == name) {
                    find = component;
                    break;
                }
            }
        });

        return find;
    }

    void GameObject::Destroy(GODestroyByBits by /** = DestroyByFlags::DestroyBy_Other */) {
        if (m_isDestroy) {
            SR_ERROR("GameObject::Destroy() : \"" + m_name + "\" game object already destroyed!");
            return;
        }

#ifdef SR_DEBUG
        if (!IsLocked())
            SR_WARN("GameObject::Destroy() : game object \"" + GetName()
                                + "\" is not locked, crash or memory corruption possible!");

        //if (SR_UTILS_NS::Debug::Instance().GetLevel() >= Debug::Level::High) {
        //    SR_LOG("GameObject::Destroy() : destroying \"" + m_name + "\" game object contains " + std::to_string(m_components.size()) + " components...");
        //}
#endif

        if (m_scene.RecursiveLockIfValid()) {
            const bool byParent = by & GAMEOBJECT_DESTROY_BY_GAMEOBJECT;

            if (!byParent && m_parent.LockIfValid()) {
                GameObject::Ptr copy = m_parent;
                copy->RemoveChild(*this);
                copy.Unlock();
            }

            m_scene->Remove(*this);

            m_scene.Unlock();
        }

        m_components.Do([&](std::list<Component*>& data) {
            for (auto &&component : data) {
                component->OnDestroy();
            }
            data.clear();
        });

        for (GameObject::Ptr gameObject : m_children) {
            gameObject.AutoFree([by](GameObject *gm) {
                gm->Destroy(by | GAMEOBJECT_DESTROY_BY_GAMEOBJECT);
            });
        }
        m_children.clear();

        m_isDestroy = true;

        Free();
    }

    void GameObject::OnMatrixDirty() {
        m_components.Do([&](auto&& data) {
            for (Component *component : data)
                component->OnMatrixDirty();
        });
    }

    bool GameObject::AddChild(const Types::SafePtr<GameObject> &child) {
        if (child.Get() == this) {
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

        m_children.push_back(child);

        /* TODO: Update child transforms with parent */

        child->OnAttached();

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

    bool GameObject::Contains(const Types::SafePtr<GameObject> &gameObject) {
        for (auto&& children : m_children) {
            if (children.Get() == gameObject.Get()) {
                return true;
            }
        }

        return false;
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

        m_scene->OnChanged();

        return true;
    }

    void GameObject::RemoveChild(const GameObject::Ptr &ptr) {
        ptr->SetParent(GameObject::Ptr());

        for (auto pIt = m_children.begin(); pIt != m_children.end(); ) {
            if (pIt->Get() == ptr.Get()) {
                pIt = m_children.erase(pIt);
                return;
            }

            ++pIt;
        }

        SRHalt(Format("GameObject %s is not child for %s!", ptr->GetName().c_str(), GetName().c_str()));
    }

    bool GameObject::ContainsComponent(const std::string &name) {
        return m_components.Do<bool>([&](auto&& data) -> bool {
            for (auto &&pComponent : data) {
                if (pComponent->GetComponentName() == name) {
                    return true;
                }
            }

            return false;
        });
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
    }

    bool GameObject::IsActive() const {
        if (m_parent.RecursiveLockIfValid()) {
            const bool parentActive = m_parent->m_isActive;
            m_parent.Unlock();
            return IsEnabled() && parentActive;
        }

        return IsEnabled();
    }

    void GameObject::CheckActivity() {
        m_isActive = IsEnabled() && (!m_parent || m_parent->m_isActive);

        for (auto&& pComponent : m_components.Get()) {
            pComponent->CheckActivity();
        }

        for (auto&& child : m_children) {
            child->CheckActivity();
        }
    }


    void GameObject::Awake() {
        /// Проверяем на IsEnabled а не на IsActive,
        /// так как если родитель не активен, то метод не вызвался бы.
        if (!IsEnabled()) {
            return;
        }

        for (auto&& pComponent : m_components.Get()) {
            if (pComponent->IsAwake()) {
                continue;
            }

            pComponent->Awake();
        }

        for (auto&& child : m_children) {
            child->Awake();
        }
    }

    void GameObject::Start() {
        /// Проверяем на IsEnabled а не на IsActive,
        /// так как если родитель не активен, то метод не вызвался бы.
        if (!IsEnabled()) {
            return;
        }

        for (auto&& pComponent : m_components.Get()) {
            if (pComponent->IsStarted()) {
                continue;
            }

            pComponent->Start();
        }

        for (auto&& child : m_children) {
            child->Start();
        }
    }

    SR_MATH_NS::FVector3 GameObject::GetBarycenter() {
        auto barycenter = Math::FVector3();
        uint32_t count = 0;

        //for (auto comp : m_components)
        //    if (auto br = comp->GetBarycenter(); !br.IsInfinity()) {
        //        barycenter += br;
        //        count++;
        //    }
        //
        //if (count != 0) {
        //    barycenter /= count;
        //    if (!m_parent.Valid())
        //        return barycenter;
        //    ///else
        //    ///return barycenter + m_transform->m_globalPosition;
        //}

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
        m_components.Do([&](auto&& data) {
            for (auto &&component : data) {
                if (!fun(component)) {
                    break;
                }
            }
        });
    }

    bool GameObject::LoadComponent(Component *pComponent) {
        if (m_isDestroy) {
            SR_ERROR("GameObject::LoadComponent() : this \"" + m_name + "\" game object is destroyed!");
            return false;
        }

        m_components.Do([&](std::list<Component*>& data) {
            data.emplace_back(pComponent);
            pComponent->SetParent(this);
            pComponent->OnAttached();
        });

        return true;
    }

    bool GameObject::AddComponent(Component* pComponent) {
        if (m_isDestroy) {
            SR_ERROR("GameObject::AddComponent() : this \"" + m_name + "\" game object is destroyed!");
            return false;
        }

        m_components.Do([&](std::list<Component*>& data) {
            data.emplace_back(pComponent);
            pComponent->SetParent(this);
            pComponent->OnAttached();
        });

        return true;
    }

    bool GameObject::RemoveComponent(Component *component) {
        return m_components.Do<bool>([&](auto&& data) -> bool {
            for (auto it = data.begin(); it != data.end(); ++it) {
                if (*it != component) {
                    continue;
                }

                if (component->GetParent() != this) {
                    SRHalt0();
                }

                component->OnDestroy();
                data.erase(it);

                return true;
            }

            SR_ERROR("GameObject::RemoveComponent() : component \"" + component->GetComponentName() + "\" not found!");

            return false;
        });
    }

    bool GameObject::ReplaceComponent(Component *source, Component *destination) {
        if (m_isDestroy) {
            SR_ERROR("GameObject::ReplaceComponent() : this \"" + m_name + "\" game object is destroyed!");
            return false;
        }

        return m_components.Do<bool>([&](auto&& data) -> bool {
            for (auto it = data.begin(); it != data.end(); ++it) {
                if (*it == source) {
                    source->OnDestroy();
                    *it = destination;

                    destination->SetParent(this);
                    destination->OnAttached();

                    return true;
                }
            }

            SR_ERROR("GameObject::ReplaceComponent() : component \"" + source->GetComponentName() + "\" not found!");

            return false;
        });
    }

    SR_HTYPES_NS::Marshal GameObject::Save(SavableFlags flags) const {
        if (GetFlags() & GAMEOBJECT_FLAG_NO_SAVE) {
            return SR_HTYPES_NS::Marshal();
        }

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

        /// save components

        m_components.Do([&](auto&& data) {
            marshal.Write(static_cast<uint32_t>(data.size()));
            for (auto &&component : data) {
                auto &&marshalComponent = component->Save(flags);
                marshal.Write<uint64_t>(marshalComponent.BytesCount());
                marshal.Append(std::move(marshalComponent));
            }
        });

        /// save children

        uint32_t childrenNum = 0;
        for (auto&& child : m_children) {
            if (child->GetFlags() & GAMEOBJECT_FLAG_NO_SAVE) {
                continue;
            }
            ++childrenNum;
        }

        marshal.Write(static_cast<uint32_t>(childrenNum));
        for (auto&& child : m_children) {
            if (child->GetFlags() & GAMEOBJECT_FLAG_NO_SAVE) {
                continue;
            }
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

    Component *GameObject::GetComponent(size_t id) {
        return m_components.Do<Component*>([&](auto&& data) -> Component* {
            for (auto &&component : data) {
                if (component->GetComponentId() != id) {
                    continue;
                }

                return component;
            }

            return nullptr;
        });
    }

    void GameObject::SetTransform(Transform *transform) {
        if (m_transform == transform || !transform) {
            SR_WARN("GameObject::SetTransform() : invalid transform!");
        }
        else {
            if (m_transform) {
                delete m_transform;
            }
            m_transform = transform;
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

    void GameObject::OnAttached() {

    }

    void GameObject::FixedUpdate() {
        /// Проверяем на IsEnabled а не на IsActive,
        /// так как если родитель не активен, то метод не вызвался бы.
        if (!IsEnabled()) {
            return;
        }

        for (auto &&pComponent : m_components.Get()) {
            if (!pComponent->IsEnabled() || !pComponent->IsStarted()) {
                continue;
            }

            pComponent->FixedUpdate();
        }

        for (auto&& child : m_children) {
            child->FixedUpdate();
        }
    }

    void GameObject::Update(float_t dt) {
        /// Проверяем на IsEnabled а не на IsActive,
        /// так как если родитель не активен, то метод не вызвался бы.
        if (!IsEnabled()) {
            return;
        }

        for (auto &&pComponent : m_components.Get()) {
            if (!pComponent->IsEnabled() || !pComponent->IsStarted()) {
                continue;
            }

            pComponent->Update(dt);
        }

        for (auto&& child : m_children) {
            child->Update(dt);
        }
    }
}