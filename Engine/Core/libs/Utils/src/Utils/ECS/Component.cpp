//
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Types/Thread.h>

namespace SR_UTILS_NS {
    SR_HTYPES_NS::Marshal::Ptr Component::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SavableFlags flags) const {
        pMarshal = Entity::Save(pMarshal, flags);

        pMarshal->Write(m_name);
        pMarshal->Write(IsEnabled());
        pMarshal->Write<uint16_t>(ComponentManager::Instance().GetVersion(this));

        return pMarshal;
    }

    void Component::SetParent(GameObject *parent) {
        m_parent = parent;
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
        const bool isActive = m_isEnabled && (!m_parent || m_parent->m_isActive);
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

    SR_WORLD_NS::Scene::Ptr Component::GetScene() const {
        if (!m_parent) {
            SRHalt("The component have not parent game object!");
            return SR_WORLD_NS::Scene::Ptr();
        }

        /// Игровой объект никогда не уничтожится до того, как не установит "m_parent" в "nullptr"
        return m_parent->GetScene();
    }

    SR_WORLD_NS::Scene::Ptr Component::TryGetScene() const {
        return m_parent ? m_parent->GetScene() : SR_WORLD_NS::Scene::Ptr();
    }

    GameObject *Component::GetParent() const {
        return m_parent;
    }

    GameObject::Ptr Component::GetRoot() const {
        if (!m_parent) {
            return GameObjectPtr();
        }

        GameObjectPtr root = m_parent->GetThis();

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

    Transform *Component::GetTransform() const noexcept {
        return m_parent ? m_parent->GetTransform() : nullptr;
    }
}

