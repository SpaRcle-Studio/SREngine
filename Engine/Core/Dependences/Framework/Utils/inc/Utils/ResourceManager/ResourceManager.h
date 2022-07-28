//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_RESOURCEMANAGER_H
#define HELPER_RESOURCEMANAGER_H

#include <Utils/Debug.h>
#include <Utils/ResourceManager/ResourceInfo.h>
#include <Utils/Types/Thread.h>
#include <Utils/ResourceManager/IResource.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT ResourceManager : public Singleton<ResourceManager> {
        friend class Singleton<ResourceManager>;
    public:
        static const float_t ResourceLifeTime;

    public:
        SR_NODISCARD bool IsLastResource(IResource* resource);
        SR_NODISCARD Path GetResPath() const { return m_folder; }
        SR_NODISCARD Path GetCachePath() const { return m_folder.Concat("Cache"); }

        IResource* Find(const std::string& Name, const std::string& ID);

        void Synchronize(bool force);

        void InspectResources(const std::function<void(const ResourcesTypes &)>& callback);

        template<typename T> T* Find(const std::string& id) {
            return dynamic_cast<T*>(Find(typeid(T).name(), id));
        }

        template<typename T> T* Find(const Path& path) {
            return dynamic_cast<T*>(Find(typeid(T).name(), path.ToString()));
        }

        bool RegisterType(const std::string& type_name);

        template<typename T> bool RegisterType() {
            return RegisterType(typeid(T).name());
        }

        /** \warning Call only from IResource parents \brief Register resource in resource manager */
        void RegisterResource(IResource *resource);

        /** \warning Call only from IResource parents \brief Register resource to destroy in resource manager */
        bool Destroy(IResource *resource);

    public:
        /** \brief Init resource manager */
        bool Init(const std::string& resourcesFolder);

        void OnSingletonDestroy() override;

        void PrintMemoryDump();

    private:
        void Remove(IResource *resource);
        void GC();
        void CheckResourceHashes();
        void Thread();

    private:
        ResourcesList m_destroyed = ResourcesList();
        ResourcesTypes m_resources = ResourcesTypes();

    private:
        std::atomic<bool> m_isInit = false;
        std::atomic<bool> m_force = false;
        std::atomic<bool> m_destroyIsEmpty = false;

        Path m_folder = Path();
        Types::Thread::Ptr m_thread = nullptr;
        uint64_t m_lastTime = 0;
        uint64_t m_deltaTime = 0;

    };
}

#endif //HELPER_RESOURCEMANAGER_H
