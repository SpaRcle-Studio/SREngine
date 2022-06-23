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

    bool Component::IsActive() const {
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

    Component *Helper::ComponentManager::CreateComponentOfName(const std::string &name) {
        SR_SCOPED_LOCK

        if (m_ids.count(name) == 0) {
            SR_ERROR("ComponentManager::CreateComponentOfName() : component \"" + name + "\" not found!");
            return nullptr;
        }

        return CreateComponentImpl(m_ids.at(name));
    }

    Component *Helper::ComponentManager::CreateComponentImpl(size_t id) {
        if (m_meta.count(id) == 0) {
            SR_ERROR("ComponentManager::CreateComponentImpl() : component \"" + std::to_string(id) + "\" not found!");
            return nullptr;
        }

        return m_meta.at(id).constructor();
    }

    Component *ComponentManager::Load(SR_HTYPES_NS::Marshal& marshal) {
        SR_SCOPED_LOCK

        m_lastComponent = marshal.Read<std::string>(); /// name
        auto&& enabled = marshal.Read<bool>();         /// enabled
        auto&& version = marshal.Read<uint16_t>();     /// version

        auto&& uidIt = m_ids.find(m_lastComponent);

        if (uidIt == std::end(m_ids)) {
            SRAssert2(false, "Component \"" + m_lastComponent + "\" not found!");
            return nullptr;
        }

        if (auto&& pComponent = m_meta.at(uidIt->second).loader(marshal, &m_context)) {
            pComponent->SetEnabled(enabled);
            return pComponent;
        }

        return nullptr;
    }
}

