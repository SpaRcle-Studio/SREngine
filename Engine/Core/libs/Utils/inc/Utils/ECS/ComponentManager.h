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

    class SR_DLL_EXPORT ComponentManager : public Singleton<ComponentManager> {
        friend class Singleton<ComponentManager>;
        typedef SR_HTYPES_NS::Function<void(Component*)> Event;
        typedef SR_HTYPES_NS::Function<Component*(void)> Construction;
        typedef SR_HTYPES_NS::Function<Component*(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage)> Loader;
        using ContextInitializerFn = SR_HTYPES_NS::Function<void(SR_HTYPES_NS::DataStorage&)>;

        struct MetaComponent {
            Construction constructor;
            Loader loader;
            std::string name;
            uint16_t version;
        };
    public:
        Component* CreateComponentOfName(const std::string& name);

        template<typename T> Component* CreateComponent() {
            SR_SCOPED_LOCK
            return CreateComponentImpl(typeid(T).hash_code());
        }

        std::unordered_map<std::string, size_t> GetComponentsNames() {
            SR_SCOPED_LOCK
            return m_ids;
        }

        uint16_t GetVersion(const Component* pComponent) const;
        uint16_t GetVersionById(uint64_t id) const;

        template<typename T> bool RegisterComponent(const Construction& constructor) {
            SR_SCOPED_LOCK

            auto&& code = typeid(T).hash_code();

            m_meta[code].loader = [](SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) -> Component* {
                return T::LoadComponent(marshal, dataStorage);
            };

            /// TODO: mingw and clang (Android) bad class name
            auto&& name = StringUtils::BackRead(typeid(T).name(), ':');

            m_meta[code].name = name;
            m_meta[code].constructor = constructor;
            m_meta[code].version = T::VERSION;

            m_ids.insert(std::make_pair(name, code));

            SR_SYSTEM_LOG("ComponentManager::RegisterComponent() : register \"" + name + "\"...");

            return true;
        }

        std::vector<SR_UTILS_NS::Component*> LoadComponents(SR_HTYPES_NS::Marshal& marshal);
        bool LoadComponents(const SR_HTYPES_NS::Function<bool(SR_HTYPES_NS::DataStorage& context)>& loader);

        void SetContextInitializer(const ContextInitializerFn& fn);

        Component* Load(SR_HTYPES_NS::Marshal& marshal);

        SR_HTYPES_NS::DataStorage* GetContext() { return &m_context; }
        SR_NODISCARD std::string GetLastComponentName() const;

    private:
        Component* CreateComponentImpl(size_t id);

    private:
        ContextInitializerFn m_contextInitializer;

        std::unordered_map<size_t, MetaComponent> m_meta;
        std::unordered_map<std::string, size_t> m_ids;

        SR_HTYPES_NS::DataStorage m_context;
        std::string m_lastComponent;

    };
}

#endif //SRENGINE_COMPONENTMANAGER_H
