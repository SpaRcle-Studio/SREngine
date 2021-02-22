//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_RESOURCEMANAGER_H
#define HELPER_RESOURCEMANAGER_H
#include <string>
#include <functional>
#include <mutex>
#include <thread>

#include "IResource.h"

#include <Types/Map.h>

#include <vector>

using namespace Framework::Helper::Types;

namespace Framework::Helper {
    enum class PathType{
        Resources, Other, Mods
    };

    class ResourceManager {
    private:
        ResourceManager() = default;
        ~ResourceManager() = default;
    public:
        ResourceManager(ResourceManager &) = delete;
    private:
        inline static std::vector<IResource *> g_resourcesToDestroy = std::vector<IResource *>();
        volatile inline static size_t g_countResourcesToDestroy = 0;

        static inline volatile bool g_grabbleNow = false;

        inline static Map<std::string, std::vector<IResource *>> g_resources = Map<std::string, std::vector<IResource *>>();
    private:
        inline static std::string g_resourcesFolder = "UnSelected";
        inline volatile static bool g_isInit = false;
        inline static std::mutex g_mutex = std::mutex();
        inline static std::thread g_thread = std::thread();
    private:
        /** \brief remove resource from resource manager */
        static void Remove(IResource *resource);

        /** \brief Grabble collector */
        static void GC();

    public:
        static IResource* Find(const std::string& Name, const std::string& ID);

        static bool RegisterType(std::string type_name);

        /** \warning Call only from IResource parents \brief Register resource in resource manager */
        static void RegisterResource(IResource *resource);

        /** \warning Call only from IResource parents \brief Register resource to destroy in resource manager */
        static bool Destroy(IResource *resource);

    public:
        /** \brief Init resource manager */
        static bool Init(std::string resourcesFolder);

        /** \brief Stop resource manager */
        static bool Stop();

        /** \brief Get current application memory usage of bytes */
        static unsigned long long GetUsedMemoryLoad() noexcept;

        // TODO: MAKE A FUCKING COMMENTS
        inline static std::string GetResourcesFolder() noexcept { return ResourceManager::g_resourcesFolder; }
    public:
        // TODO: PLEASE
        static void PrintMemoryDump();
    };
}

#endif //HELPER_RESOURCEMANAGER_H
