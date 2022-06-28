//
// Created by Monika on 24.06.2022.
//

#include <Utils/ECS/ComponentManager.h>

namespace SR_UTILS_NS {
    Component* ComponentManager::CreateComponentOfName(const std::string &name) {
        SR_SCOPED_LOCK

        if (m_ids.count(name) == 0) {
            SR_ERROR("ComponentManager::CreateComponentOfName() : component \"" + name + "\" not found!");
            return nullptr;
        }

        return CreateComponentImpl(m_ids.at(name));
    }

    Component* ComponentManager::CreateComponentImpl(size_t id) {
        if (m_meta.count(id) == 0) {
            SR_ERROR("ComponentManager::CreateComponentImpl() : component \"" + std::to_string(id) + "\" not found!");
            return nullptr;
        }

        return m_meta.at(id).constructor();
    }

    Component* ComponentManager::Load(SR_HTYPES_NS::Marshal& marshal) {
        SR_SCOPED_LOCK

        m_lastComponent = marshal.Read<std::string>(); /// name
        auto&& enabled = marshal.Read<bool>();         /// enabled
        auto&& version = marshal.Read<uint16_t>();     /// version

        auto&& uidIt = m_ids.find(m_lastComponent);
        if (uidIt == std::end(m_ids)) {
            SRAssert2(false, "Component \"" + m_lastComponent + "\" not found!");
            return nullptr;
        }

        if (version != GetVersionById(uidIt->second)) {
            SR_WARN("ComponentManager::Load() : \"" + m_lastComponent + "\" has different version!");
            return nullptr;
        }

        if (auto&& pComponent = m_meta.at(uidIt->second).loader(marshal, &m_context)) {
            pComponent->SetEnabled(enabled);
            return pComponent;
        }

        return nullptr;
    }

    uint16_t ComponentManager::GetVersion(const Component *pComponent) const {
        SR_SCOPED_LOCK

        return GetVersionById(pComponent->GetComponentId());
    }

    uint16_t ComponentManager::GetVersionById(uint64_t id) const {
        SR_SCOPED_LOCK

        auto&& pIt = m_meta.find(id);

        if (pIt == m_meta.end()) {
            return 0;
        }

        return pIt->second.version;
    }

    bool ComponentManager::LoadComponents(const std::function<bool(Types::DataStorage & )> &loader) {
        SR_SCOPED_LOCK

        const bool result = loader(m_context);

        m_context.Clear();

        return result;
    }

    std::string ComponentManager::GetLastComponentName() const {
        SR_SCOPED_LOCK
        return m_lastComponent;
    }
}