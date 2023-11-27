//
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Types/Thread.h>
#include <Utils/World/Scene.h>
#include <Utils/World/SceneUpdater.h>

namespace SR_UTILS_NS {
    Component::~Component() {
        /// если срабатывает ассерт, значит, вероятнее всего, какой-то игровой объект до сих пор удерживает компонент,
        /// а значит, будет падение.
        SRAssert(!GetParent());
    }

    SR_HTYPES_NS::Marshal::Ptr Component::Save(SavableSaveData data) const {
        if (!(data.pMarshal = Entity::Save(data))) {
            return data.pMarshal;
        }

        data.pMarshal->Write<uint64_t>(GetComponentHashName());
        data.pMarshal->Write(IsEnabled());
        data.pMarshal->Write<uint16_t>(GetEntityVersion());

        if (!SR_UTILS_NS::ComponentManager::Instance().HasLoader(GetComponentHashName())) {
            GetComponentProperties().SaveProperty(*data.pMarshal);
        }

        return data.pMarshal;
    }

    void Component::SetParent(IComponentable* pParent) {
        if ((m_parent = pParent)) {
            if (auto&& pGameObject = dynamic_cast<SR_UTILS_NS::GameObject*>(m_parent)) {
                m_gameObject = pGameObject->GetThis().DynamicCast<GameObject>();
                m_scene = m_gameObject->GetScene();
            }
            else {
                m_gameObject.Reset();
                m_scene = dynamic_cast<SR_WORLD_NS::Scene*>(m_parent);
            }

            SRAssert(m_scene);
        }
        else {
            m_gameObject.Reset();
            m_scene = nullptr;
        }
    }

    void Component::SetEnabled(bool value) {
        if (m_isEnabled == value) {
            return;
        }

        m_isEnabled = value;

        if (m_parent) {
            m_parent->SetDirty(true);
        }
    }

    void Component::CheckActivity() {
        /// если родителя нет, или он отличается от ожидаемого, то будем считать, что родитель активен.
        /// сцена выключенной (в понимании игровых объектов) быть не может.
        const bool isActive = m_isEnabled && (!m_gameObject || m_gameObject->IsActive());
        if (isActive == m_isActive) {
            return;
        }

        if ((m_isActive = isActive)) {
            m_scene->GetSceneUpdater()->RegisterComponent(this);
            OnEnable();
        }
        else {
            if (m_indexInSceneUpdater != SR_ID_INVALID) {
                m_scene->GetSceneUpdater()->UnRegisterComponent(this);
            }
            OnDisable();
        }
    }

    Component::ScenePtr Component::GetScene() const {
        if (auto&& pScene = TryGetScene()) {
            return pScene;
        }

        SRHalt("The component have not a valid scene!");

        return nullptr;
    }

    Component::ScenePtr Component::TryGetScene() const {
        return m_scene;
    }

    Component::GameObjectPtr Component::GetGameObject() const {
        SRAssert(m_parent);
        return m_gameObject;
    }

    IComponentable* Component::GetParent() const {
        return m_parent;
    }

    GameObject::Ptr Component::GetRoot() const {
        SRAssert(m_parent);

        if (!m_gameObject) {
            return GameObjectPtr();
        }

        GameObjectPtr root = m_gameObject;

        while (root.Valid()) {
            if (auto&& parent = root->GetParent()) {
                root = parent;
            }
            else {
                break;
            }
        }

        return root;
    }

    Transform* Component::GetTransform() const noexcept {
        SRAssert(m_parent);

        if (m_gameObject) {
            return m_gameObject->GetTransform();
        }

        return nullptr;
    }

    std::string Component::GetEntityInfo() const {
        return "Component: " + GetComponentName();
    }

    bool Component::IsUpdatable() const noexcept {
        return m_isStarted && m_isActive;
    }

    Component* Component::CopyComponent() const {
        auto&& pComponent = SR_UTILS_NS::ComponentManager::Instance().CreateComponentOfName(GetComponentHashName());
        if (!pComponent) {
            return nullptr;
        }

        /// TODO: non-optimized way
        SR_HTYPES_NS::Marshal marshal;
        GetComponentProperties().SaveProperty(marshal);
        marshal.SetPosition(0);
        pComponent->GetComponentProperties().LoadProperty(marshal);

        return pComponent;
    }

    bool Component::IsPlayingMode() const {
        if (auto&& pScene = TryGetScene()) {
            return pScene->IsPlayingMode();
        }

        return false;
    }

    bool Component::IsPausedMode() const {
        if (auto&& pScene = TryGetScene()) {
            return pScene->IsPausedMode();
        }

        return false;
    }

    void Component::Detach() {
        if (m_parent && IsAttached()) {
            m_parent->RemoveComponent(this);
        }
    }

    void Component::OnEnable() {

    }

    void Component::OnDisable() {

    }

    void Component::Start() {
        m_isStarted = true;
    }

    void Component::OnDetached() {
        if (m_indexInSceneUpdater != SR_ID_INVALID) {
            m_scene->GetSceneUpdater()->UnRegisterComponent(this);
        }
        m_isAttached = false;
    }
}

