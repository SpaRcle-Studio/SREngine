//
// Created by Monika on 24.06.2022.
//

#include <Utils/ECS/ComponentManager.h>
#include <Utils/ECS/Migration.h>
#include <Utils/Common/ToString.h>

namespace SR_UTILS_NS {
    Component* ComponentManager::CreateComponentOfName(StringAtom name) {
        SR_SCOPED_LOCK;

        if (m_meta.count(name) == 0) {
            SR_ERROR("ComponentManager::CreateComponentImpl() : component \"" + name.ToStringRef() + "\" not found!");
            return nullptr;
        }

        auto&& pComponent = m_meta.at(name).constructor();
        if (pComponent) {
            if (!pComponent->InitializeEntity()) {
                SR_ERROR("ComponentManager::CreateComponentImpl() : failed to initialize entity!");
                pComponent->AutoFree([](auto&& pData) {
                    delete pData;
                });
                return nullptr;
            }
        }

        return pComponent;
    }

    std::pair<Component*, ComponentLoadResult> ComponentManager::Load(SR_HTYPES_NS::Marshal& marshal) {
        SR_SCOPED_LOCK;

        ComponentLoadResult result = ComponentLoadResult::Success;

        m_lastComponent = SR_HASH_TO_STR_ATOM(marshal.Read<uint64_t>()); /// name
        auto&& enabled = marshal.Read<bool>();      /// enabled
        auto&& version = marshal.Read<uint16_t>();  /// version

        const uint16_t newVersion = GetVersionByName(m_lastComponent);

        if (version != newVersion) {
            result = ComponentLoadResult::Migrated;

            auto&& pMetadataIt = m_meta.find(m_lastComponent);
            if (pMetadataIt == m_meta.end()) {
                SR_ERROR("ComponentManager::Load() : unknown component! Name: {}", m_lastComponent.c_str());
                return std::make_pair(nullptr, ComponentLoadResult::Error);
            }

            SR_INFO("ComponentManager::Load() : \"" + pMetadataIt->first.ToStringRef() + "\" has different version! " +
                 "Trying to migrate from " + SR_UTILS_NS::ToString(version) + " to " + SR_UTILS_NS::ToString(newVersion) + "..."
            );

            if (!Migration::Instance().Migrate(m_lastComponent, marshal, version, newVersion)) {
                SR_WARN("ComponentManager::Load() : failed to migrate component!");
                return std::make_pair(CreateComponentOfName(m_lastComponent), ComponentLoadResult::Error);
            }
        }

        auto&& loader = m_meta.at(m_lastComponent).loader;
        auto&& pComponent = loader ? loader(marshal, &m_context) : LoadComponent(m_lastComponent, marshal);

        if (pComponent) {
            pComponent->m_isEnabled = enabled;
            return std::make_pair(pComponent, result);
        }

        return std::make_pair(nullptr, ComponentLoadResult::Error);
    }

    uint16_t ComponentManager::GetVersion(const Component* pComponent) const {
        SR_SCOPED_LOCK;
        return GetVersionByName(pComponent->GetComponentName());
    }

    uint16_t ComponentManager::GetVersionByName(SR_UTILS_NS::StringAtom name) const {
        SR_SCOPED_LOCK;

        auto&& pIt = m_meta.find(name);

        if (pIt == m_meta.end()) {
            return 0;
        }

        return pIt->second.version;
    }

    bool ComponentManager::LoadComponents(const SR_HTYPES_NS::Function<bool(Types::DataStorage & )> &loader) {
        SR_SCOPED_LOCK;

        const bool result = loader(m_context);

        m_context.Clear();

        return result;
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
                    SR_WARN("ComponentManager::LoadComponents() : failed to load \"" + m_lastComponent.ToStringRef() + "\" component!");
                }

                const uint64_t readBytes = marshal.GetPosition() - position;
                const int64_t lostBytes = static_cast<int64_t>(bytesCount) - readBytes;

                if (lostBytes < 0 && loadResult != ComponentLoadResult::Migrated) {
                    SRHalt("ComponentManager::LoadComponents() : component is read incorrectly!");
                    continue;
                }

                if (lostBytes > 0 && loadResult != ComponentLoadResult::Migrated) {
                    SR_WARN("ComponentManager::LoadComponents() : bytes were lost when loading the component!\n\tBytes count: " + std::to_string(lostBytes));
                    if (lostBytes >= UINT16_MAX) {
                        SRHalt("Something went wrong!");
                        continue;
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

    bool ComponentManager::HasLoader(StringAtom name) const {
        auto&& pMetadataIt = m_meta.find(name);
        if (pMetadataIt == m_meta.end()) {
            return false;
        }

        return static_cast<bool>(pMetadataIt->second.loader);
    }
}