//
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Types/Thread.h>
#include <Utils/World/Scene.h>

namespace SR_UTILS_NS {
    Component::~Component() {
        /// если срабатывает ассерт, значит, вероятнее всего, какой-то игровой объект до сих пор удерживает компонент,
        /// а значит, будет падение.
        SRAssert(!GetParent());
    }

    SR_HTYPES_NS::Marshal::Ptr Component::Save(SavableSaveData data) const {
        data.pMarshal = Entity::Save(data);

        data.pMarshal->Write<uint64_t>(GetComponentHashName());
        data.pMarshal->Write(IsEnabled());
        data.pMarshal->Write<uint16_t>(GetEntityVersion());

        return data.pMarshal;
    }

    void Component::SetParent(IComponentable* pParent) {
        m_parent = pParent;

        if (auto&& pGameObject = dynamic_cast<SR_UTILS_NS::GameObject*>(m_parent)) {
            m_gameObject = pGameObject->GetThis().DynamicCast<GameObject>();
        }
        else {
            m_gameObject.Reset();
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
        SRAssert1Once(m_gameObject);

        /// если родителя нет, или он отличается от ожидаемого, то будем считать, что родитель активен.
        /// сцена выключенной (в понимании игровых объектов) быть не может.
        const bool isActive = m_isEnabled && (!m_gameObject || m_gameObject->m_isActive);
        if (isActive == m_isActive) {
            return;
        }

        if ((m_isActive = isActive)) {
            OnEnable();
        }
        else {
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
        /// Игровой объект или сцена никогда не уничтожится до того,
        /// как не установит "m_parent" в "nullptr"

        /// наиболее часто ожидаемое поведение, это GameObject-родитель, поэтому проверяем его первым делом
        if (m_gameObject) {
            return m_gameObject->GetScene();
        }

        if (auto&& pScene = dynamic_cast<SR_WORLD_NS::Scene*>(m_parent)) {
            return pScene;
        }

        return nullptr;
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

    Component* Component::CopyComponent() const {
        SRHalt("Not implemented! [" + GetComponentName() + "]");
        return nullptr;
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
}

