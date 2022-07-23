//
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Types/Thread.h>

namespace SR_UTILS_NS {
    SR_HTYPES_NS::Marshal Component::Save(SavableFlags flags) const {
        SR_LOCK_GUARD

        auto marshal = Entity::Save(flags);

        marshal.Write(m_name);
        marshal.Write(IsEnabled());
        marshal.Write<uint16_t>(ComponentManager::Instance().GetVersion(this));

        return marshal;
    }

    bool Component::IsActive() const noexcept {
        SR_LOCK_GUARD

        return IsEnabled() && (!m_parent || m_parent->m_isActive);
    }

    void Component::SetParent(GameObject *parent) {
        SR_LOCK_GUARD

        m_parent = parent;

        CheckActivity();
    }

    void Component::SetEnabled(bool value) {
        SR_LOCK_GUARD

        if (value == m_isEnabled) {
            return;
        }

        m_isEnabled = value;

        CheckActivity();
    }

    void Component::CheckActivity() {
        SR_LOCK_GUARD

        const bool isActive = IsActive();
        if (isActive == m_isActive) {
            return;
        }

        if ((m_isActive = isActive)) {
            OnEnabled();
        }
        else {
            OnDisabled();
        }
    }

    SR_WORLD_NS::Scene::Ptr Component::GetScene() const {
        SR_LOCK_GUARD

        if (!m_parent) {
            SRHalt("The component have not parent game object!");
            return SR_WORLD_NS::Scene::Ptr();
        }

        /// Игровой объект никогда не уничтожится до того, как не установит "m_parent" в "nullptr"
        return m_parent->GetScene();
    }

    bool Component::IsEnabled() const noexcept {
        SR_LOCK_GUARD

        return m_isEnabled;
    }

    GameObject *Component::GetParent() const {
        SR_LOCK_GUARD

        return m_parent;
    }
}

