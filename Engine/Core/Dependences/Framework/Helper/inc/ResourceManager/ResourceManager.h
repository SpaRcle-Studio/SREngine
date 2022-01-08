//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_RESOURCEMANAGER_H
#define HELPER_RESOURCEMANAGER_H

#include <Debug.h>
#include <FileSystem/Path.h>
#include <string>
#include <fstream>
#include <functional>
#include <mutex>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <Types/Thread.h>

#include "IResource.h"
#include <FileSystem/Path.h>
#include <Utils/Singleton.h>

#include <vector>
#include <queue>

namespace Framework::Helper {
    enum class PathType {
        Resources, Other, Mods
    };

    struct ResourceInfo {
        std::unordered_set<IResource*> m_group;
        std::unordered_map<std::string, std::unordered_set<IResource*>> m_copies;

        [[nodiscard]] IResource* Find(const std::string& id) {
            if (auto&& pIt = m_copies.find(id); pIt == m_copies.end())
                return nullptr;
            else {
                if (pIt->second.empty()) {
                    return nullptr;
                } else
                    return *pIt->second.begin();
            }
        }

        [[nodiscard]] bool IsLast(const std::string& id) {
            if (auto&& pIt = m_copies.find(id); pIt == m_copies.end())
                return true;
            else
                return pIt->second.size() == 1;
        }

        void Remove(IResource* resource) {
            const auto id = resource->GetResourceId();

            if (auto&& group = m_copies.find(id); group != m_copies.end()) {
                group->second.erase(resource);
            } else {
                SRAssert2(false, "Resource group not found!");
                return;
            }

            if (m_copies.at(id).empty())
                m_copies.erase(id);

            m_group.erase(resource);
        }

        void Add(IResource* resource) {
            m_copies[resource->GetResourceId()].insert(resource);
            m_group.insert(resource);
        }
    };

    typedef std::unordered_map<std::string, ResourceInfo> Resources;

    class ResourceManager : public Helper::Singleton<ResourceManager> {
        friend class Singleton<ResourceManager>;
    private:
        ~ResourceManager() override = default;

    public:
        static const float_t ResourceLifeTime;

    private:
        std::vector<IResource*> m_resourcesToDestroy = std::vector<IResource*>();
        Resources m_resources = Resources();

    private:
        Path m_resourcesFolder = "";
        bool m_isInit = false;
        std::recursive_mutex m_mutex = std::recursive_mutex();
        std::atomic<bool> m_force = false;
        std::atomic<bool> m_destroyIsEmpty = false;
        Types::Thread m_thread;

    private:
        /** \brief remove resource from resource manager */
        void Remove(IResource *resource);

        /** \brief Grabble collector */
        void GC();

    public:
        void Synchronize(bool force);
        IResource* Find(const std::string& Name, const std::string& ID);
        [[nodiscard]] bool IsLastResource(IResource* resource);

        bool RegisterType(const std::string& type_name);

        /** \warning Call only from IResource parents \brief Register resource in resource manager */
        void RegisterResource(IResource *resource);

        /** \warning Call only from IResource parents \brief Register resource to destroy in resource manager */
        bool Destroy(IResource *resource);
    public:
        /** \brief Init resource manager */
        bool Init(const std::string& resourcesFolder);

        /** \brief Stop resource manager */
        bool Stop();

        /** \brief Get current application memory usage of bytes */
        static uint64_t GetUsedMemoryLoad();

        Path GetResourcesFolder() { return m_resourcesFolder; }

    public:
        void PrintMemoryDump();
    };
}

#endif //HELPER_RESOURCEMANAGER_H
