//
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
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
        return IsEnabled() && (!m_parent || m_parent->m_isActive);
    }

    void Component::SetParent(GameObject *parent) {
        m_parent = parent;

        CheckActivity();
    }

    void Component::SetEnabled(bool value) {
        if (value == m_isEnabled) {
            return;
        }

        m_isEnabled = value;

        CheckActivity();
    }

    void Component::CheckActivity() {
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
}

