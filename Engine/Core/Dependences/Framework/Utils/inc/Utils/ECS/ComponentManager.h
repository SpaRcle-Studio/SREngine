//
// Created by Monika on 27.05.2022.
//

#ifndef SRENGINE_COMPONENTMANAGER_H
#define SRENGINE_COMPONENTMANAGER_H

#include <Utils/ECS/EntityManager.h>
#include <Utils/ECS/Component.h>
#include <Utils/Types/Thread.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Types/DataStorage.h>

namespace SR_UTILS_NS {
    class Component;
    class GameObject;

    class SR_DLL_EXPORT ComponentManager : public Singleton<ComponentManager> {
        friend class Singleton<ComponentManager>;
        typedef std::function<void(Component*)> Event;
        typedef std::function<Component*(void)> Construction;
        typedef std::function<Component*(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage)> Loader;
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


        template<typename T> bool RegisterComponent(const Construction& constructor) {
            SR_SCOPED_LOCK

            const auto&& code = typeid(T).hash_code();

            m_loaders.insert(std::make_pair(code, [](SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) -> Component* {
                return T::LoadComponent(marshal, dataStorage);
            }));

            return RegisterComponentImpl(code, StringUtils::BackRead(typeid(T).name(), ':'), constructor);
        }

        bool LoadComponents(const std::function<bool(Types::DataStorage& context)>& loader) {
            SR_SCOPED_LOCK

            const bool result = loader(m_context);

            m_context.Clear();

            return result;
        }

        SR_NODISCARD std::string GetLastComponentName() const {
            SR_SCOPED_LOCK
            return m_lastComponent;
        }

        Component* Load(SR_HTYPES_NS::Marshal& marshal);

        SR_HTYPES_NS::DataStorage* GetContext() { return &m_context; }

    private:
        bool RegisterComponentImpl(size_t id, const std::string& name, const Construction& constructor);
        Component* CreateComponentImpl(size_t id);

    private:
        std::unordered_map<size_t, Construction> m_creators;
        std::unordered_map<size_t, Loader> m_loaders;
        std::unordered_map<size_t, std::string> m_names;
        std::unordered_map<std::string, size_t> m_ids;
        SR_HTYPES_NS::DataStorage m_context;
        std::string m_lastComponent;

    };
}

#endif //SRENGINE_COMPONENTMANAGER_H
