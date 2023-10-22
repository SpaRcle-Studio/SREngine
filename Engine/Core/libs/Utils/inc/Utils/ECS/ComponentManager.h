//
// Created by Monika on 27.05.2022.
//

#ifndef SRENGINE_COMPONENTMANAGER_H
#define SRENGINE_COMPONENTMANAGER_H

#include <Utils/ECS/EntityManager.h>
#include <Utils/ECS/Component.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/Function.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Types/DataStorage.h>

namespace SR_UTILS_NS {
    class Component;
    class GameObject;

    SR_ENUM_NS_CLASS_T(ComponentLoadResult, uint8_t,
        Success,
        Migrated,
        Error,
        Fatal
    );

    class SR_DLL_EXPORT ComponentManager : public Singleton<ComponentManager> {
        friend class Singleton<ComponentManager>;
        typedef SR_HTYPES_NS::Function<void(Component*)> Event;
        typedef SR_HTYPES_NS::Function<Component*(void)> Construction;
        typedef SR_HTYPES_NS::Function<Component*(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage)> Loader;
        using ContextInitializerFn = SR_HTYPES_NS::Function<void(SR_HTYPES_NS::DataStorage&)>;
        using Hash = uint64_t;

        struct MetaComponent {
            Construction constructor;
            Loader loader;
            std::string name;
            uint16_t version;
        };
    public:
        SR_NODISCARD bool IsSingletonCanBeDestroyed() const override {
            return false;
        }

        Component* CreateComponentOfName(const std::string& name);
        Component* CreateComponentOfName(Hash hashName);

        template<typename T> T* CreateComponent() {
            SR_SCOPED_LOCK
            auto&& pComponent = CreateComponentImpl(T::COMPONENT_HASH_NAME);
            if (!pComponent) {
                return nullptr;
            }

            if (auto&& pImpl = dynamic_cast<T*>(pComponent)) {
                return pImpl;
            }

            pComponent->OnDestroy();

            SRHalt0();

            return nullptr;
        }

        const std::unordered_map<std::string, Hash>& GetComponentsNames() const {
            SR_SCOPED_LOCK
            return m_ids;
        }

        uint16_t GetVersion(const Component* pComponent) const;
        uint16_t GetVersionById(uint64_t id) const;

        template<typename T> bool RegisterComponent(const Construction& constructor) {
            SR_SCOPED_LOCK

            auto&& hashName = T::COMPONENT_HASH_NAME;

            m_meta[hashName].loader = [](SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) -> Component* {
                return T::LoadComponent(marshal, dataStorage);
            };

            m_meta[hashName].name = T::COMPONENT_NAME;
            m_meta[hashName].constructor = constructor;
            m_meta[hashName].version = T::VERSION;

            m_ids.insert(std::make_pair(T::COMPONENT_NAME, hashName));

            /// не логируем, так как вызывается до инициализации отладчика
            /// SR_SYSTEM_LOG("ComponentManager::RegisterComponent() : register \"" + T::COMPONENT_NAME + "\"...");

            return true;
        }

        std::vector<SR_UTILS_NS::Component*> LoadComponents(SR_HTYPES_NS::Marshal& marshal);
        bool LoadComponents(const SR_HTYPES_NS::Function<bool(SR_HTYPES_NS::DataStorage& context)>& loader);

        void SetContextInitializer(const ContextInitializerFn& fn);

        std::pair<Component*, ComponentLoadResult> Load(SR_HTYPES_NS::Marshal& marshal);

        SR_HTYPES_NS::DataStorage* GetContext() { return &m_context; }
        SR_NODISCARD std::string GetLastComponentName() const;

    private:
        Component* CreateComponentImpl(size_t id);

    private:
        ContextInitializerFn m_contextInitializer;

        std::unordered_map<size_t, MetaComponent> m_meta;
        std::unordered_map<std::string, Hash> m_ids;

        SR_HTYPES_NS::DataStorage m_context;
        uint64_t m_lastComponent = 0;

    };
}

#define SR_REGISTER_COMPONENT_CUSTOM(name, constructor)                                                                                                         \
    SR_INLINE_STATIC const bool SR_CODEGEN_REGISTER_COMPONENT_##name = SR_UTILS_NS::ComponentManager::Instance().RegisterComponent< name >([]() { /** NOLINT */ \
         constructor                                                                                                                                            \
    });                                                                                                                                                         \

#define SR_REGISTER_COMPONENT(name)                                                                                                                             \
    SR_INLINE_STATIC const bool SR_CODEGEN_REGISTER_COMPONENT_##name = SR_UTILS_NS::ComponentManager::Instance().RegisterComponent< name >([]() { /** NOLINT */ \
         return new name ();                                                                                                                                    \
    });                                                                                                                                                         \

#endif //SRENGINE_COMPONENTMANAGER_H
