//
// Created by Monika on 27.05.2022.
//

#ifndef SR_ENGINE_COMPONENT_MANAGER_H
#define SR_ENGINE_COMPONENT_MANAGER_H

#include <Utils/ECS/EntityManager.h>
#include <Utils/ECS/Component.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Common/StringUtils.h>

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
        SR_REGISTER_SINGLETON(ComponentManager)
        typedef SR_HTYPES_NS::Function<void(Component*)> Event;
        typedef SR_HTYPES_NS::Function<Component*(void)> Construction;
        typedef SR_HTYPES_NS::Function<Component*(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage)> Loader;
        using ContextInitializerFn = SR_HTYPES_NS::Function<void(SR_HTYPES_NS::DataStorage&)>;
        using Hash = uint64_t;

        struct MetaComponent {
            Construction constructor;
            Loader loader;
            uint16_t version;
        };
    public:
        SR_NODISCARD bool IsSingletonCanBeDestroyed() const override {
            return false;
        }

        Component* CreateComponentOfName(StringAtom name);

        SR_NODISCARD bool HasLoader(StringAtom name) const;

        template<typename T> T* CreateComponent() {
            SR_SCOPED_LOCK;
            auto&& pComponent = CreateComponentOfName(T::COMPONENT_NAME);
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

        SR_NODISCARD Component* LoadComponent(StringAtom name, SR_HTYPES_NS::Marshal& marshal) {
            SR_SCOPED_LOCK;
            SR_TRACY_ZONE;

            if (auto&& pComponent = CreateComponentOfName(name)) {
                pComponent->GetComponentProperties().LoadProperty(marshal);
                return pComponent;
            }

            return nullptr;
        }

        const std::vector<StringAtom>& GetComponentsNames() const {
            SR_SCOPED_LOCK;
            return m_names;
        }

        SR_NODISCARD uint16_t GetVersion(const Component* pComponent) const;
        SR_NODISCARD uint16_t GetVersionByName(SR_UTILS_NS::StringAtom name) const;

        template<typename T> bool RegisterComponentLoader(const Construction& constructor) {
            SR_SCOPED_LOCK;

            m_meta[T::COMPONENT_NAME].loader = [](SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) -> Component* {
                return T::LoadComponent(marshal, dataStorage);
            };

            m_meta[T::COMPONENT_NAME].constructor = constructor;
            m_meta[T::COMPONENT_NAME].version = T::VERSION;

            m_names.emplace_back(T::COMPONENT_NAME);

            /// не логируем, так как вызывается до инициализации отладчика
            /// SR_SYSTEM_LOG("ComponentManager::RegisterComponent() : register \"" + T::COMPONENT_NAME + "\"...");

            return true;
        }

        template<typename T> bool RegisterComponent(const Construction& constructor) {
            SR_SCOPED_LOCK;

            m_meta[T::COMPONENT_NAME].constructor = constructor;
            m_meta[T::COMPONENT_NAME].version = T::VERSION;

            m_names.emplace_back(T::COMPONENT_NAME);

            /// не логируем, так как вызывается до инициализации отладчика
            /// SR_SYSTEM_LOG("ComponentManager::RegisterComponent() : register \"" + T::COMPONENT_NAME + "\"...");

            return true;
        }

        std::vector<SR_UTILS_NS::Component*> LoadComponents(SR_HTYPES_NS::Marshal& marshal);
        bool LoadComponents(const SR_HTYPES_NS::Function<bool(SR_HTYPES_NS::DataStorage& context)>& loader);

        void SetContextInitializer(const ContextInitializerFn& fn);

        std::pair<Component*, ComponentLoadResult> Load(SR_HTYPES_NS::Marshal& marshal);

        SR_HTYPES_NS::DataStorage* GetContext() { return &m_context; }

    private:
        ContextInitializerFn m_contextInitializer;

        std::unordered_map<StringAtom, MetaComponent> m_meta;
        std::vector<StringAtom> m_names;

        SR_HTYPES_NS::DataStorage m_context;
        SR_UTILS_NS::StringAtom m_lastComponent;

    };
}

#define SR_REGISTER_COMPONENT_CUSTOM(name, constructor)                                                                                                             \
    SR_INLINE_STATIC const bool SR_CODEGEN_REGISTER_COMPONENT_##name = SR_UTILS_NS::ComponentManager::Instance().RegisterComponentLoader<name>([]() { /** NOLINT */ \
         constructor                                                                                                                                                \
    });                                                                                                                                                             \

#define SR_REGISTER_COMPONENT(name)                                                                                                                                 \
    SR_INLINE_STATIC const bool SR_CODEGEN_REGISTER_COMPONENT_##name = SR_UTILS_NS::ComponentManager::Instance().RegisterComponentLoader<name>([]() { /** NOLINT */ \
         return new name ();                                                                                                                                        \
    });                                                                                                                                                             \


#define SR_REGISTER_NEW_COMPONENT(className, version)                                                                                                     \
    SR_INITIALIZE_COMPONENT(className)                                                                                                                    \
    SR_ENTITY_SET_VERSION(version);                                                                                                                       \
    SR_INLINE_STATIC SR_UTILS_NS::Component* AllocateNew() { return (new className())->BaseComponent(); }                                                 \
    SR_INLINE_STATIC bool CODEGEN_REGISTER_COMPONENT_STATUS = SR_UTILS_NS::ComponentManager::Instance().RegisterComponent<className>([]() { /** NOLINT */ \
        return AllocateNew();                                                                                                                             \
    });                                                                                                                                                   \

#endif //SR_ENGINE_COMPONENTMANAGER_H
