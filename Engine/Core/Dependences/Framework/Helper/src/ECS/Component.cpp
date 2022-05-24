//
// Created by Nikita on 27.11.2020.
//

#include <ECS/Component.h>
#include <ECS/GameObject.h>

namespace SR_UTILS_NS {
    void Framework::Helper::Component::OnAttachComponent() {
        ComponentManager::Instance().DoEvent(this, m_componentId);
    }

    SR_HTYPES_NS::Marshal Component::Save(SavableFlags flags) const {
        auto marshal = Entity::Save(flags);

        marshal.Write(m_name);

        return marshal;
    }

    bool ComponentManager::RegisterComponentImpl(size_t id, const std::string &name, const std::function<Component *(void)> &constructor) {
        m_names.insert(std::make_pair(id, name));
        m_ids.insert(std::make_pair(name, id));
        m_creators.insert(std::make_pair(id, constructor));

        Debug::System("ComponentManager::RegisterComponentImpl() : register \"" + name + "\"...");

        return true;
    }

    Component *Helper::ComponentManager::CreateComponentOfName(const std::string &name) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

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
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        m_lastComponent = marshal.Read<std::string>();

        auto&& uidIt = m_ids.find(m_lastComponent);

        if (uidIt == std::end(m_ids)) {
            SRAssert2(false, "Component \"" + m_lastComponent + "\" not found!");
            return nullptr;
        }

        return m_loaders.at(uidIt->second)(marshal, &m_context);
    }
}

