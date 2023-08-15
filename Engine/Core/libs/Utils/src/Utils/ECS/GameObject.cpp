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
    GameObject::GameObject(std::string name, Transform* pTransform) {
        SetName(std::move(name));
        SetTransform(pTransform);
        UpdateEntityPath();
    }

    GameObject::GameObject(std::string name)
        : GameObject(std::move(name), new Transform3D())
    { }

    GameObject::~GameObject() {
        SRAssert(m_children.empty());
        if (GetPrefab()) {
            UnlinkPrefab();
        }
        SRAssert(!GetPrefab());
        delete m_transform;
    }

    void GameObject::Destroy() {
        if (m_isDestroyed) {
            SRHalt("GameObject::Destroy() : \"" + m_name + "\" game object already destroyed!");
            return;
        }

        m_isDestroyed = true;

        /// сцену не блокируем, предполагается, что и так в контексте заблокированной сцены работаем

        if (GetPrefab()) {
            UnlinkPrefab();
        }

        if (auto&& pParent = GetParent()) {
            auto&& thisPtr = GetThis().DynamicCast<GameObject>();
            pParent->RemoveChild(thisPtr);
        }

        if (m_scene) {
            m_scene->Remove(GetThis().DynamicCast<GameObject>());
            while (!m_children.empty()) {
                (*m_children.begin())->Destroy();
            }
        }
        else {
            while (!m_children.empty()) {
                auto&& pChild = *m_children.begin();
                pChild.AutoFree([](auto&& pData) {
                    pData->Destroy();
                });
            }

            DestroyComponents();
            DestroyImpl();
        }
    }

    void GameObject::DestroyImpl() {
        GameObject::Ptr copy = GetThis().DynamicCast<GameObject>();

        /// это должно быть единственное место,
        /// где мы уничтожаем объект
        copy.AutoFree([](GameObject* pGameObject) {
            delete pGameObject;
        });
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

        if (!child->SetParent(GetThis().DynamicCast<GameObject>())) {
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
        m_hashName = SR_HASH_STR(m_name);

        if (m_scene) {
            m_scene->OnChanged();
        }
    }

    void GameObject::SetIdInScene(uint64_t id) {
        m_idInScene = id;
    }

    void GameObject::SetScene(ScenePtr pScene) {
        SRAssert(!m_scene);
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

    bool GameObject::SetParent(const GameObject::Ptr& parent) {
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

    void GameObject::RemoveChild(const GameObject::Ptr& ptr) {
        ptr->SetParent(GameObject::Ptr());

        for (uint16_t i = 0; i < m_children.size(); ++i) {
            if (ptr == m_children[i]) {
                m_children.erase(m_children.begin() + i);
                return;
            }
        }

        SRHalt(Format("GameObject %s is not child for %s!", ptr->GetName().c_str(), GetName().c_str()));
    }

    void GameObject::RemoveAllChildren() {
        for (auto&& child : m_children) {
            child->SetParent(GameObject::Ptr());
        }
        m_children.clear();
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

    void GameObject::CheckActivity(bool force) noexcept {
        if (!force && !IsDirty()) {
            return;
        }

        const bool isActivePrev = m_isActive;
        m_isActive = IsEnabled() && (!m_parent || m_parent->m_isActive);

        /// нет смысла продолжать цепочку, все и так выключено
        if (!m_isActive && m_isActive == isActivePrev) {
            return;
        }

        /// обновляем компоненты
        IComponentable::CheckActivity(force);

        for (auto&& child : m_children) {
            child->CheckActivity(true);
        }
    }

    void GameObject::Awake(bool force, bool isPaused) noexcept {
        /// Проверяем на IsEnabled а не на IsActive,
        /// так как если родитель не активен, то метод не вызвался бы.
        if ((!force && !IsDirty()) || !IsEnabled()) {
            return;
        }

        IComponentable::Awake(force, isPaused);

        for (auto&& child : m_children) {
            child->Awake(true, isPaused);
        }
    }

    void GameObject::Start(bool force) noexcept {
        /// Проверяем на IsEnabled а не на IsActive,
        /// так как если родитель не активен, то метод не вызвался бы.
        if ((!force && !IsDirty()) || !IsEnabled()) {
            return;
        }

        IComponentable::Start(force);

        for (auto&& child : m_children) {
            child->Start(true);
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

        return SR_MATH_NS::FVector3(SR_MATH_NS::InfinityFV3);
    }

    SR_MATH_NS::FVector3 GameObject::GetHierarchyBarycenter() {
        auto barycenter = SR_MATH_NS::FVector3((SR_MATH_NS::Unit) 0);
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

        return count == 0 ? SR_MATH_NS::InfinityFV3 : barycenter / count;
    }

     bool GameObject::PostLoad(bool force) {
         if (!IComponentable::PostLoad(force)) {
             return false;
         }

         for (auto&& child : m_children) {
             child->PostLoad(true);
         }

         return true;
     }

    SR_HTYPES_NS::Marshal::Ptr GameObject::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SavableFlags flags) const {
        if (GetFlags() & GAMEOBJECT_FLAG_NO_SAVE) {
            return pMarshal;
        }

        pMarshal = Entity::Save(pMarshal, flags);
        pMarshal->Write<uint16_t>(GetEntityVersion());

        if (auto&& pPrefab = GetPrefab(); pPrefab && IsPrefabOwner()) {
            pMarshal->Write<bool>(true);
            pMarshal->Write<std::string>(pPrefab->GetResourcePath().ToStringRef());
            pMarshal->Write<std::string>(GetName());
            pMarshal->Write<uint64_t>(GetTag());
            pMarshal->Write<bool>(IsEnabled());
            pMarshal = GetTransform()->Save(pMarshal, flags);
            return pMarshal;
        }
        else {
            pMarshal->Write<bool>(false);
        }

        pMarshal->Write(IsEnabled());
        pMarshal->Write(m_name);

        pMarshal->Write<uint64_t>(m_tag);

        pMarshal = m_transform->Save(pMarshal, flags);

        /// save components

        pMarshal = SaveComponents(pMarshal, flags);

        /// save children

        uint16_t childrenNum = 0;
        for (auto&& child : m_children) {
            if (child->GetFlags() & GAMEOBJECT_FLAG_NO_SAVE) {
                continue;
            }
            ++childrenNum;
        }

        pMarshal->Write(static_cast<uint16_t>(childrenNum));
        for (auto&& child : m_children) {
            if (child->GetFlags() & GAMEOBJECT_FLAG_NO_SAVE) {
                continue;
            }

            pMarshal = child->Save(pMarshal, flags);
        }

        return pMarshal;
    }

    bool GameObject::UpdateEntityPath() {
        GameObject::Ptr current = GetThis().DynamicCast<GameObject>();
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

    void GameObject::SetTransform(Transform* pTransform) {
        if (!pTransform) {
            SRHalt("pTransform is nullptr!");
            return;
        }

        if (pTransform->GetMeasurement() == Measurement::Holder && GetParent()) {
            SRHalt("Incorrect HOLDER transform usage!");
            return;
        }

        if (m_transform == pTransform) {
            SR_WARN("GameObject::SetTransform() : invalid transform!");
        }
        else {
            if (m_transform) {
                delete m_transform;
            }
            m_transform = pTransform;
            m_transform->SetGameObject(this);
            SetDirty(true);
        }

        for (auto&& pComponent : m_components) {
            pComponent->OnTransformSet();
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
                copy->RemoveChild(GetThis().DynamicCast<GameObject>());
                copy->Unlock();
            }
        }

        if (destination.Valid()){
            return destination->AddChild(GetThis().DynamicCast<GameObject>());
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
        return m_tag != 0;
    }

    void GameObject::OnAttached() {
        if (auto&& parent = GetParentTransform()) {
            m_transform->UpdateTree();
        }
        else {
            SR_WARN("GameObject::OnAttached() : GameObject doesn't have parent to get transform!");
        }
    }

    bool GameObject::SetDirty(bool dirty) {
        if (IsDirty() == dirty) {
            return IComponentable::SetDirty(dirty);
        }

        const bool isDirty = IComponentable::SetDirty(dirty);

        /// Грязный флаг передаем вверх, а чистый вниз.
        /// Это нужно для оптимизации
        if (dirty) {
            if (m_parent) {
                m_parent->SetDirty(dirty);
            }

            return isDirty;
        }
        else {
            bool hasDirtyChild = false;

            for (auto&& children : m_children) {
                hasDirtyChild |= children->SetDirty(dirty);
            }

            if (hasDirtyChild) {
                return isDirty || IComponentable::SetDirty(true);
            }

            return isDirty;
        }
    }

    GameObject::Ptr GameObject::Load(SR_HTYPES_NS::Marshal& marshal, const ScenePtr& scene) {
        SR_UTILS_NS::GameObject::Ptr gameObject;

        /// для экономии памяти стека при рекурсивном создании объектов, кладем все переменные в эту область видимости.
        {
            auto&& entityId = marshal.Read<uint64_t>();
            auto&& version = marshal.Read<uint16_t>();

            const uint16_t newVersion = SR_UTILS_NS::GameObject::VERSION;

            if (version != newVersion) {
                SR_INFO("GameObject::Load() : game object has different version! Trying to migrate from " +
                        SR_UTILS_NS::ToString(version) + " to " + SR_UTILS_NS::ToString(newVersion) + "..."
                );

                static const auto GAME_OBJECT_HASH_NAME = SR_HASH_STR("GameObject");

                if (!Migration::Instance().Migrate(GAME_OBJECT_HASH_NAME, marshal, version)) {
                    SR_ERROR("GameObject::Load() : failed to migrate game object!");
                    return gameObject;
                }
            }

            if (marshal.Read<bool>()) { /// is prefab
                auto&& prefabPath = marshal.Read<std::string>();
                auto&& objectName = marshal.Read<std::string>();
                auto&& tag = marshal.Read<uint64_t>();
                auto&& isEnabled = marshal.Read<bool>();
                auto&& pTransform = Transform::Load(marshal, nullptr);

                if (!pTransform) {
                    SRHalt("Failed to load transform!");
                    return gameObject;
                }

                if (auto&& pPrefab = Prefab::Load(prefabPath)) {
                    gameObject = pPrefab->Instance(scene);
                    pPrefab->CheckResourceUsage();
                }

                if (!gameObject) {
                    SR_LOG("GameObject::Load() : failed to load prefab!\n\tPath: " + prefabPath);
                    delete pTransform;
                    return gameObject;
                }

                gameObject->SetName(objectName);
                gameObject->SetEnabled(isEnabled);
                gameObject->m_tag = tag;
                gameObject->SetTransform(pTransform);
                return gameObject;
            }

            auto&& enabled = marshal.Read<bool>();
            auto&& name = marshal.Read<std::string>();

            auto&& tag = marshal.Read<uint64_t>();

            if (entityId == UINT64_MAX) {
                gameObject = new GameObject(name);
            }
            else {
                SR_UTILS_NS::EntityManager::Instance().GetReserved(entityId, [&gameObject, name]() -> SR_UTILS_NS::Entity::Ptr {
                    gameObject = new GameObject(name);
                    return gameObject.DynamicCast<SR_UTILS_NS::Entity>();
                });
            }

            if (!gameObject.Valid()) {
                SRHalt("GameObject::Load() : failed to create new game object!");
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

            gameObject->m_tag = tag;

            /// ----------------------

            auto&& components = ComponentManager::Instance().LoadComponents(marshal);
            for (auto&& pComponent : components) {
                gameObject->AddComponent(pComponent);
            }
        }

        auto&& childrenCount = marshal.Read<uint16_t>();
        for (uint16_t i = 0; i < childrenCount; ++i) {
            if (auto&& child = Load(marshal, scene)) {
                gameObject->AddChild(child);
            }
        }

        return gameObject;
    }

    std::string GameObject::GetEntityInfo() const {
        return "GameObject: " + GetName();
    }

    GameObject::Ptr GameObject::Copy(const GameObject::ScenePtr& scene) const {
        GameObject::Ptr gameObject = new GameObject(GetName(), GetTransform()->Copy());

        gameObject->SetEnabled(IsEnabled());

        gameObject->m_tag = m_tag;

        if (scene) {
            scene->RegisterGameObject(gameObject);
        }

        for (auto&& pComponent : m_components) {
            gameObject->AddComponent(pComponent->CopyComponent());
        }

        for (auto&& pComponent : m_loadedComponents) {
            gameObject->AddComponent(pComponent->CopyComponent());
        }

        for (auto&& children : GetChildrenRef()) {
            gameObject->AddChild(children->Copy(scene));
        }

        if (IsPrefabOwner()) {
            gameObject->SetPrefab(GetPrefab(), true);
        }

        return gameObject;
    }

    void GameObject::SetTag(const std::string& tag) {
        m_tag = TagManager::Instance().HashTag(tag);
    }

    std::string GameObject::GetTagString() const {
        return TagManager::Instance().GetTag(GetTag());
    }

    Tag GameObject::GetTag() const {
        return m_tag;
    }

    GameObject::Ptr GameObject::Find(uint64_t hashName) const noexcept {
        for (auto&& child : m_children) {
            if (child->GetHashName() == hashName) {
                return child;
            }
        }

        return GameObject::Ptr();
    }

    GameObject::Ptr GameObject::GetRoot() const noexcept {
        /// TODO: optimize

        if (m_parent) {
            return m_parent->GetRoot();
        }

        return DynamicCast<GameObject>();
    }

    GameObject::Ptr GameObject::Find(const std::string &name) const noexcept {
        return Find(SR_HASH_STR(name));
    }

    void GameObject::SetPrefab(Prefab* pPrefab, bool owner) {
        SRAssert2(pPrefab, "Invalid prefab!");
        SRAssert2(!GetPrefab() && !IsPrefabOwner(), "Prefab is already set!");

        if (pPrefab && !GetPrefab()) {
            m_prefab.first = pPrefab;
            m_prefab.first->AddUsePoint();
        }
        else {
            return;
        }

        m_prefab.second = owner;

        for (auto&& child : m_children) {
            /// наткнулись на другой префаб
            if (child->IsPrefabOwner()) {
                continue;
            }

            child->SetPrefab(pPrefab, false);
        }
    }

    void GameObject::UnlinkPrefab() {
        SRAssert2(GetPrefab(), "Is not a prefab!");

        m_prefab.second = false;

        if (m_prefab.first) {
            m_prefab.first->RemoveUsePoint();
            m_prefab.first = nullptr;
        }

        for (auto&& child : m_children) {
            /// наткнулись на другой префаб или он не задан
            if (child->IsPrefabOwner() || !child->GetPrefab()) {
                continue;
            }

            child->UnlinkPrefab();
        }
    }
}