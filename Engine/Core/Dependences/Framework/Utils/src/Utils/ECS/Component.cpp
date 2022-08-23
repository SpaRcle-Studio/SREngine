//
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Types/Thread.h>

namespace SR_UTILS_NS {
    SR_HTYPES_NS::Marshal Component::Save(SavableFlags flags) const {
        auto marshal = Entity::Save(flags);

        marshal.Write(m_name);
        marshal.Write(IsEnabled());
        marshal.Write<uint16_t>(ComponentManager::Instance().GetVersion(this));

        return marshal;
    }

    bool Component::IsActive() const noexcept {
        return m_isEnabled && (!m_parent || m_parent->m_isActive);
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
            m_parent->SetDirty();
        }
    }

    void Component::CheckActivity() {
        const bool isActive = IsActive();
        if (isActive == m_isActive) {
            return;
        }

        if (isActive) {
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
        }

        return root;
    }

    Transform *Component::GetTransform() const noexcept {
        return m_parent ? m_parent->GetTransform() : nullptr;
    }
}

