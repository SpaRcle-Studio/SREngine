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

    bool ComponentManager::RegisterComponentImpl(size_t id, const std::string &name, const Construction& constructor) {
        m_names.insert(std::make_pair(id, name));
        m_ids.insert(std::make_pair(name, id));
        m_creators.insert(std::make_pair(id, constructor));

        SR_SYSTEM_LOG("ComponentManager::RegisterComponentImpl() : register \"" + name + "\"...");

        return true;
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
        if (m_creators.count(id) == 0) {
            SR_ERROR("ComponentManager::CreateComponentImpl() : component \"" + std::to_string(id) + "\" not found!");
            return nullptr;
        }

        return m_creators.at(id)();
    }

    Component *ComponentManager::Load(SR_HTYPES_NS::Marshal& marshal) {
        SR_SCOPED_LOCK

        m_lastComponent = marshal.Read<std::string>();
        const auto&& enabled = marshal.Read<bool>();

        auto&& uidIt = m_ids.find(m_lastComponent);

        if (uidIt == std::end(m_ids)) {
            SRAssert2(false, "Component \"" + m_lastComponent + "\" not found!");
            return nullptr;
        }

        if (auto&& pComponent = m_loaders.at(uidIt->second)(marshal, &m_context)) {
            pComponent->SetEnabled(enabled);
            return pComponent;
        }

        return nullptr;
    }
}

