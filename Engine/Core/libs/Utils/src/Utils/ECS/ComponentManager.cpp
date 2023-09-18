//
// Created by Monika on 24.06.2022.
//

#include <Utils/ECS/ComponentManager.h>
#include <Utils/ECS/Migration.h>

namespace SR_UTILS_NS {
    Component* ComponentManager::CreateComponentOfName(const std::string &name) {
        SR_SCOPED_LOCK

        if (m_ids.count(name) == 0) {
            SR_ERROR("ComponentManager::CreateComponentOfName() : component \"" + name + "\" not found!");
            return nullptr;
        }

        return CreateComponentOfName(m_ids.at(name));
    }

    Component* ComponentManager::CreateComponentOfName(ComponentManager::Hash hashName) {
        SR_SCOPED_LOCK
        return CreateComponentImpl(hashName);
    }

    Component* ComponentManager::CreateComponentImpl(size_t id) {
        if (m_meta.count(id) == 0) {
            SR_ERROR("ComponentManager::CreateComponentImpl() : component \"" + std::to_string(id) + "\" not found!");
            return nullptr;
        }

        return m_meta.at(id).constructor();
    }

    std::pair<Component*, ComponentLoadResult> ComponentManager::Load(SR_HTYPES_NS::Marshal& marshal) {
        SR_SCOPED_LOCK

        ComponentLoadResult result = ComponentLoadResult::Success;

        m_lastComponent = marshal.Read<uint64_t>(); /// name
        auto&& enabled = marshal.Read<bool>();      /// enabled
        auto&& version = marshal.Read<uint16_t>();  /// version

        const uint16_t newVersion = GetVersionById(m_lastComponent);

        if (version != newVersion) {
            result = ComponentLoadResult::Migrated;

            auto&& pMetadataIt = m_meta.find(m_lastComponent);
            if (pMetadataIt == m_meta.end()) {
                SRHalt("Unknown component!");
                return std::make_pair(nullptr, ComponentLoadResult::Error);
            }

            SR_INFO("ComponentManager::Load() : \"" + pMetadataIt->second.name + "\" has different version! " +
                 "Trying to migrate from " + SR_UTILS_NS::ToString(version) + " to " + SR_UTILS_NS::ToString(newVersion) + "..."
            );

            if (!Migration::Instance().Migrate(m_lastComponent, marshal, version)) {
                SR_ERROR("ComponentManager::Load() : failed to migrate component!");
                return std::make_pair(nullptr, ComponentLoadResult::Error);
            }
        }

        if (auto&& pComponent = m_meta.at(m_lastComponent).loader(marshal, &m_context)) {
            pComponent->m_isEnabled = enabled;
            return std::make_pair(pComponent, result);
        }

        return std::make_pair(nullptr, ComponentLoadResult::Error);
    }

    uint16_t ComponentManager::GetVersion(const Component *pComponent) const {
        SR_SCOPED_LOCK

        return GetVersionById(pComponent->GetComponentHashName());
    }

    uint16_t ComponentManager::GetVersionById(uint64_t id) const {
        SR_SCOPED_LOCK

        auto&& pIt = m_meta.find(id);

        if (pIt == m_meta.end()) {
            return 0;
        }

        return pIt->second.version;
    }

    bool ComponentManager::LoadComponents(const SR_HTYPES_NS::Function<bool(Types::DataStorage & )> &loader) {
        SR_SCOPED_LOCK

        const bool result = loader(m_context);

        m_context.Clear();

        return result;
    }

    std::string ComponentManager::GetLastComponentName() const {
        SR_SCOPED_LOCK

        auto&& pMetadataIt = m_meta.find(m_lastComponent);
        if (pMetadataIt == m_meta.end()) {
            return "\"Unknown component\"";
        }

        return pMetadataIt->second.name;
    }

    std::vector<SR_UTILS_NS::Component*> ComponentManager::LoadComponents(SR_HTYPES_NS::Marshal &marshal) {
        std::vector<SR_UTILS_NS::Component*> components;

        LoadComponents([&](SR_HTYPES_NS::DataStorage& context) -> bool {
            if (m_contextInitializer) {
                m_contextInitializer(context);
            }

            auto&& componentCount = marshal.Read<uint16_t>();
            components.reserve(componentCount);
            SRAssert2(componentCount <= 2048, "While loading the component errors occurred!");

            for (uint32_t i = 0; i < componentCount; ++i) {
                auto&& bytesCount = marshal.Read<uint32_t>();
                auto&& position = marshal.GetPosition();

                /// TODO: use entity id
                SR_MAYBE_UNUSED auto&& compEntityId = marshal.Read<uint64_t>();

                auto&& [pComponent, loadResult] = Load(marshal);

                if (pComponent) {
                    components.emplace_back(pComponent);
                }
                else {
                    SR_WARN("ComponentManager::LoadComponents() : failed to load \"" + GetLastComponentName() + "\" component!");
                }

                const uint64_t readBytes = marshal.GetPosition() - position;
                const int64_t lostBytes = static_cast<int64_t>(bytesCount) - readBytes;

                if (lostBytes < 0 && loadResult != ComponentLoadResult::Migrated) {
                    SRHalt("ComponentManager::LoadComponents() : component is read incorrectly!");
                    return false;
                }

                if (lostBytes > 0 && loadResult != ComponentLoadResult::Migrated) {
                    SR_WARN("ComponentManager::LoadComponents() : bytes were lost when loading the component!\n\tBytes count: " + std::to_string(lostBytes));
                    if (lostBytes >= UINT16_MAX) {
                        SRHalt("Something went wrong!");
                        return false;
                    }
                    marshal.Skip(lostBytes);
                }
            }

            return true;
        });

        return std::move(components);
    }

    void ComponentManager::SetContextInitializer(const ComponentManager::ContextInitializerFn &fn) {
        m_contextInitializer = fn;
    }
}