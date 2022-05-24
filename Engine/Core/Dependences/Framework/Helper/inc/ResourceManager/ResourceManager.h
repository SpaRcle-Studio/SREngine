//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_RESOURCEMANAGER_H
#define HELPER_RESOURCEMANAGER_H

#include <Debug.h>
#include <ResourceManager/ResourceInfo.h>
#include <Types/Thread.h>
#include <ResourceManager/IResource.h>
#include <Utils/Singleton.h>

namespace SR_UTILS_NS {
    class ResourceManager : public Helper::Singleton<ResourceManager> {
        friend class Singleton<ResourceManager>;
    public:
        static const float_t ResourceLifeTime;

    public:
        SR_NODISCARD bool IsLastResource(IResource* resource);
        SR_NODISCARD Path GetResPath() const { return m_folder; }
        SR_NODISCARD Path GetCachePath() const { return m_folder.Concat("Cache"); }
        SR_NODISCARD Path GetConfigPath() const { return m_folder.Concat("Configs"); }
        SR_NODISCARD Path GetFontsPath() const { return m_folder.Concat("Fonts"); }
        SR_NODISCARD Path GetMaterialsPath() const { return m_folder.Concat("Materials"); }
        SR_NODISCARD Path GetTexturesPath() const { return m_folder.Concat("Textures"); }
        SR_NODISCARD Path GetModelsPath() const { return m_folder.Concat("Models"); }
        SR_NODISCARD Path GetUtilsPath() const { return m_folder.Concat("Utilities"); }
        SR_NODISCARD Path GetShadersPath() const { return m_folder.Concat("Shaders"); }

        IResource* Find(const std::string& Name, const std::string& ID);

        void Synchronize(bool force);

        void InspectResources(const std::function<void(const ResourcesTypes &)>& callback);

        template<typename T> T* Find(const std::string& ID) {
            return dynamic_cast<T*>(Find(typeid(T).name(), ID));
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

        /** \brief Stop resource manager */
        bool Stop();

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
        std::recursive_mutex m_mutex = std::recursive_mutex();
        Types::Thread::Ptr m_thread;
        uint64_t m_lastTime = 0;
        uint64_t m_deltaTime = 0;

    };
}

#endif //HELPER_RESOURCEMANAGER_H
