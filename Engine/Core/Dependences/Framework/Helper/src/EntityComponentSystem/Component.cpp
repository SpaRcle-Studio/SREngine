//
// Created by Nikita on 27.11.2020.
//

#include "EntityComponentSystem/Component.h"
#include <EntityComponentSystem/GameObject.h>

namespace Framework::Helper {
    void Framework::Helper::Component::OnAttachComponent() {
        ComponentManager::Instance().DoEvent(this, m_componentId);
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
            Helper::Debug::Error("ComponentManager::CreateComponentOfName() : component \"" + name + "\" not found!");
            return nullptr;
        }

        return CreateComponentImpl(m_ids.at(name));
    }

    Component *Helper::ComponentManager::CreateComponentImpl(size_t id) {
        if (m_creators.count(id) == 0) {
            Helper::Debug::Error("ComponentManager::CreateComponentImpl() : component if \"" + std::to_string(id) + "\" not found!");
            return nullptr;
        }

        return m_creators.at(id)();
    }

    Component *ComponentManager::Load(const MarshalDecodeNode& node) {
        const auto&& name = node.Name();

        if (m_ids.count(name) == 0) {
            SR_ERROR("ComponentManager::Load() : component \"" + name + "\" not found!");
            return nullptr;
        }

        return m_loaders.at(m_ids.at(name))(node, &m_context);
    }
}

