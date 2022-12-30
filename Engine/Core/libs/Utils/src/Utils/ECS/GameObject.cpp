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
#include <Utils/Common/Hashes.h>

namespace SR_UTILS_NS {
    GameObject::GameObject(std::string name, Transform* pTransform, std::string tag)
        : Super(this)
    {
        SetName(std::move(name));
        m_tag = std::move(tag);

        SetTransform(pTransform);

        UpdateEntityPath();
    }

    GameObject::GameObject(std::string name, std::string tag)
        : GameObject(std::move(name), new Transform3D(), std::move(tag))
    { }

    GameObject::~GameObject() {
        delete m_transform;
    }

    void GameObject::Destroy(GODestroyByBits by /** = DestroyByFlags::DestroyBy_Other */) {
        if (m_isDestroy) {
            SR_ERROR("GameObject::Destroy() : \"" + m_name + "\" game object already destroyed!");
            return;
        }

        /// сцены может и не быть, к примеру, если это префаб
        if (m_scene && m_scene->RecursiveLockIfValid()) {
            const bool byParent = by & GAMEOBJECT_DESTROY_BY_GAMEOBJECT;

            if (!byParent && m_parent.RecursiveLockIfValid()) {
                GameObject::Ptr copy = m_parent;
                copy->RemoveChild(*this);
                copy.Unlock();
            }

            m_scene->Remove(*this);

            m_scene->Unlock();
        }

        IComponentable::DestroyComponents();

        for (auto&& gameObject : m_children) {
            gameObject.AutoFree([by](GameObject *gm) {
                gm->Destroy(by | GAMEOBJECT_DESTROY_BY_GAMEOBJECT);
            });
        }
        m_children.clear();

        m_isDestroy = true;

        delete this;
    }

    void GameObject::OnMatrixDirty() {
        for (auto&& pComponent : m_components) {
            pComponent->OnMatrixDirty();
        }
    }

    bool GameObject::AddChild(const GameObject::Ptr& child) {
        if (child.Get() == this) {
            SRHalt("It is impossible to make the parent a child!");
            return false;
        }

        if (child->GetParent()) {
            SRHalt("Child has parent!");
            return false;
        }

        if (Contains(child)) {
            SRHalt("This child already exists in this game object!");
            return false;
        }

        if (!child->SetParent(*this)) {
            SR_WARN("GameObject::AddChild() : failed to set parent!");
            return false;
        }

        m_children.push_back(child);

        child->OnAttached();

        if (m_scene) {
            m_scene->OnChanged();
        }

        SetDirty(true);

        return true;
    }

    void GameObject::SetName(std::string name) {
        m_name = std::move(name);
        m_hashName = SR_UTILS_NS::HashCombine(m_name);

        if (m_scene) {
            m_scene->OnChanged();
        }
    }

    void GameObject::SetTag(const std::string &tag) {
        m_tag = tag;

        if (m_scene) {
            m_scene->OnChanged();
        }
    }

     void GameObject::SetIdInScene(uint64_t id) {
         m_idInScene = id;
     }

     void GameObject::SetScene(ScenePtr pScene) {
         m_scene = pScene;
     }

    bool GameObject::Contains(const GameObject::Ptr& gameObject) {
        for (auto&& children : m_children) {
            if (children.Get() == gameObject.Get()) {
                return true;
            }
        }

        return false;
    }

    bool GameObject::SetParent(const GameObject::Ptr &parent) {
        if (parent == m_parent) {
            SRHalt("GameObject::SetParent() : parent is already set!");
            return false;
        }

        GameObject::Ptr oldParent = m_parent;
        m_parent = parent;

        if (!UpdateEntityPath()) {
            SRHalt("GameObject::SetParent() : failed to update entity path!");
            m_parent = oldParent;
            return false;
        }

        if (m_scene) {
            m_scene->OnChanged();
        }

        m_transform->UpdateTree();

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

    void GameObject::ForEachChild(const std::function<void(GameObject::Ptr &)> &fun) {
        for (auto&& child : m_children) {
            if (child.Valid()) {
                fun(child);
            }
        }
    }

    void GameObject::ForEachChild(const std::function<void(const GameObject::Ptr &)> &fun) const {
        for (auto&& child : m_children) {
            if (child.RecursiveLockIfValid()) {
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

        SetDirty(true);
    }

    bool GameObject::IsActive() const noexcept {
        if (m_parent.RecursiveLockIfValid()) {
            const bool parentActive = m_parent->m_isActive;
            m_parent.Unlock();
            return IsEnabled() && parentActive;
        }

        return IsEnabled();
    }

    void GameObject::CheckActivity() noexcept {
        if (!m_dirty) {
            return;
        }

        m_isActive = IsEnabled() && (!m_parent || m_parent->m_isActive);

        IComponentable::CheckActivity();

        for (auto&& child : m_children) {
            child->m_dirty = true;
            child->CheckActivity();
        }
    }


    void GameObject::Awake(bool isPaused) noexcept {
        /// Проверяем на IsEnabled а не на IsActive,
        /// так как если родитель не активен, то метод не вызвался бы.
        if (!m_dirty || !IsEnabled()) {
            return;
        }

        IComponentable::Awake(isPaused);

        for (auto&& child : m_children) {
            child->m_dirty = true;
            child->Awake(isPaused);
        }
    }

    void GameObject::Start() noexcept {
        /// Проверяем на IsEnabled а не на IsActive,
        /// так как если родитель не активен, то метод не вызвался бы.
        if (!m_dirty || !IsEnabled()) {
            return;
        }

        IComponentable::Start();

        for (auto&& child : m_children) {
            child->m_dirty = true;
            child->Start();
        }
    }

    SR_MATH_NS::FVector3 GameObject::GetBarycenter() {
        //auto barycenter = Math::FVector3();
        //uint32_t count = 0;

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

        if (auto self = GetBarycenter(); !self.IsInfinity()) {
            barycenter += self;
            count++;
        }

        ForEachChild([=](const GameObject::Ptr &child) mutable {
            if (auto self = GetBarycenter(); !self.IsInfinity()) {
                barycenter += self;
                count++;
            }
        });

        return count == 0 ? Math::InfinityFV3 : barycenter / count;
    }

     bool GameObject::PostLoad() {
        if (!IComponentable::PostLoad()) {
            return false;
        }

         for (auto&& child : m_children) {
             child->m_dirty = true;
             child->PostLoad();
         }

         return true;
     }

    SR_HTYPES_NS::Marshal::Ptr GameObject::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SavableFlags flags) const {
        if (GetFlags() & GAMEOBJECT_FLAG_NO_SAVE) {
            return pMarshal;
        }

        pMarshal = Entity::Save(pMarshal, flags);

        pMarshal->Write(VERSION);

        pMarshal->Write(IsEnabled());
        pMarshal->Write(m_name);

        if (HasTag()) {
            pMarshal->Write(true);
            pMarshal->Write(m_tag);
        }
        else {
            pMarshal->Write(false);
        }

        pMarshal = m_transform->Save(pMarshal, flags);

        /// save components

        pMarshal = SaveComponents(pMarshal, flags);

        /// save children

        uint32_t childrenNum = 0;
        for (auto&& child : m_children) {
            if (child->GetFlags() & GAMEOBJECT_FLAG_NO_SAVE) {
                continue;
            }
            ++childrenNum;
        }

        pMarshal->Write(static_cast<uint32_t>(childrenNum));
        for (auto&& child : m_children) {
            if (child->GetFlags() & GAMEOBJECT_FLAG_NO_SAVE) {
                continue;
            }
            pMarshal = child->Save(pMarshal, flags);
        }

        return pMarshal;
    }

    bool GameObject::UpdateEntityPath() {
        GameObject::Ptr current = *this;
        EntityPath path;

        do {
            path.ConcatBack(current->GetEntityId());
            current = current->m_parent;

            if (current && current->GetEntityId() == GetEntityId()) {
                SRHalt("Recursive entity path!");
                return false;
            }
        } while (current.Valid());

        SetEntityPath(path);

        return true;
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
            SetDirty(true);
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

        if (destination.Valid()){
            return destination->AddChild(*this);
        }
        else {
            if (GetParent()){
                SRHalt("GameObject::MoveToTree() : GameObject has parent!");
                return false;
            }

            return true;
        }
    }

    bool GameObject::HasTag() const {
        return m_tag != "Untagged";
    }

    void GameObject::OnAttached() {
        if (auto&& parent = GetParentTransform()){
            m_transform->UpdateTree();
        } else {
            SR_WARN("GameObject::OnAttached() : GameObject doesn't have parent to get transform!");
        }
    }

    void GameObject::SetDirty(bool dirty) {
        if (m_dirty == dirty) {
            return;
        }

        /// Грязный флаг передаем вверх, а чистый вниз.
        /// Это нужно для оптимизации
        if ((m_dirty = dirty)) {
            if (m_parent) {
                m_parent->SetDirty(dirty);
            }
        }
        else {
            for (auto&& children : m_children) {
                children->SetDirty(dirty);
            }
        }
    }

    GameObject::Ptr GameObject::Load(SR_HTYPES_NS::Marshal& marshal, const ScenePtr& scene) {
        SR_UTILS_NS::GameObject::Ptr gameObject;

        /// для экономии памяти стека при рекурсивном создании объектов, кладем все переменные в эту область видимости.
        {
            auto&& entityId = marshal.Read<uint64_t>();

            auto&& version = marshal.Read<uint16_t>();
            if (version != SR_UTILS_NS::GameObject::VERSION) {
                SRAssert2Once(false, "Version is different! Version: " + Helper::ToString(version));
                return gameObject;
            }

            auto&& enabled = marshal.Read<bool>();
            auto&& name = marshal.Read<std::string>();
            auto&& hasTag = marshal.Read<bool>();

           auto&& tag = hasTag ? marshal.Read<std::string>() : std::string();

           if (entityId == UINT64_MAX) {
               gameObject = *(new GameObject(name));
           }
           else {
               SR_UTILS_NS::EntityManager::Instance().GetReserved(entityId, [&gameObject, name]() -> SR_UTILS_NS::Entity* {
                   gameObject = *(new GameObject(name));
                   return gameObject.DynamicCast<SR_UTILS_NS::Entity*>();
               });
           }

           if (!gameObject.Valid()) {
               SRHalt("GameObject::Load() : failed to create new gameobject!");
               return SR_UTILS_NS::GameObject::Ptr();
           }

           if (scene) {
               scene->RegisterGameObject(gameObject);
           }

            /// ----------------------

            gameObject->SetEnabled(enabled);

            gameObject->SetTransform(SR_UTILS_NS::Transform::Load(
                    marshal,
                    gameObject.Get()
            ));

            if (hasTag) {
                gameObject->SetTag(tag);
            }

            /// ----------------------

            auto&& components = ComponentManager::Instance().LoadComponents(marshal);
            for (auto&& pComponent : components) {
                gameObject->LoadComponent(pComponent);
            }
        }

        auto&& childrenCount = marshal.Read<uint32_t>();
        for (uint32_t i = 0; i < childrenCount; ++i) {
            if (auto&& child = Load(marshal, scene)) {
                gameObject->AddChild(child);
            }
        }

        return gameObject;
    }

    std::string GameObject::GetEntityInfo() const {
        return "GameObject: " + GetName();
    }

    GameObject::Ptr GameObject::Copy(const GameObject::ScenePtr &scene) const {
        GameObject::Ptr gameObject = *(new GameObject(GetName(), GetTransform()->Copy(), GetTag()));

        gameObject->SetEnabled(IsEnabled());

        if (scene) {
            scene->RegisterGameObject(gameObject);
        }

        for (auto&& pComponent : m_components) {
            gameObject->LoadComponent(pComponent->CopyComponent());
        }

        for (auto&& pComponent : m_loadedComponents) {
            gameObject->LoadComponent(pComponent->CopyComponent());
        }

        for (auto&& children : GetChildrenRef()) {
            gameObject->AddChild(children->Copy(scene));
        }

        return gameObject;
    }
}