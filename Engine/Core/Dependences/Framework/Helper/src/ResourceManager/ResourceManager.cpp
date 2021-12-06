//
// Created by Nikita on 16.11.2020.
//

#include "ResourceManager/ResourceManager.h"

#include <string>
#include <thread>
#include <random>

#ifdef SR_WIN32
    #define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

    #include <Psapi.h>
    #include <Windows.h>
#endif

#include <Debug.h>

namespace Framework::Helper {
    const float_t ResourceManager::ResourceLifeTime = 5.f; // seconds

    uint64_t ResourceManager::GetUsedMemoryLoad() {
    #ifdef SR_WIN32
        PROCESS_MEMORY_COUNTERS pmc;
        BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
        if (result)
            return (long long) pmc.PeakWorkingSetSize;
        else
            return -1;
    #else
        return -1;
    #endif
    }

    bool ResourceManager::Init(const std::string& resourcesFolder) {
        Debug::Info("ResourceManager::Init() : initializing resource manager...\n\tResources folder: "+resourcesFolder);

        m_resourcesFolder = resourcesFolder;
        m_isInit = true;

        m_thread = std::thread(&ResourceManager::GC, this);

        return true;
    }

    bool ResourceManager::Stop() {
        Debug::Info("ResourceManager::Stop() : stopping resource manager...");

        m_isInit = false;

        Synchronize(true);

        if (m_thread.joinable())
            m_thread.join();

        PrintMemoryDump();

        return true;
    }

    bool ResourceManager::Destroy(IResource *resource) {
        if (Debug::GetLevel() >= Debug::Level::High)
            Debug::Log("ResourceManager::Destroy() : destroying \""+ std::string(resource->m_resource_name) +"\"");

        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

        m_resourcesToDestroy.push_back(resource);
        m_countResourcesToDestroy++;

        return true;
    }

    bool ResourceManager::RegisterType(const std::string& type_name) {
        Debug::Info("ResourceManager::RegisterType() : register new \""+std::string(type_name)+"\" type...");
        
        m_resources[type_name] = std::vector<IResource*>();
        m_resources[type_name].reserve(500 * 500);

        return true;
    }

    void ResourceManager::Remove(IResource *resource) {
        if (auto&& resourcesGroup = m_resources.find(resource->m_resource_name); resourcesGroup != m_resources.end()) {
            auto&& resources = resourcesGroup->second;
            for (auto&& resourceIt = resources.begin(); resourceIt != resources.end(); ++resourceIt) {
                if (*resourceIt == resource) {
                    m_resources[resource->m_resource_name].erase(resourceIt);
                    return;
                }
            }
        }

        Debug::Error("ResourceManager::Remove() : unknown resource! Name: " + std::string(resource->m_resource_name));
    }

    void ResourceManager::GC() {
        do {
            auto beginFrame = clock();

            if (m_countResourcesToDestroy == 0)
                continue;

            const std::lock_guard<std::recursive_mutex> lock(m_mutex);

            auto resourceIt = m_resourcesToDestroy.begin();
            for (; resourceIt != m_resourcesToDestroy.end(); ) {
                auto resource = *resourceIt;

                resource->m_lifetime -= double_t(clock() - beginFrame) / (double_t) CLOCKS_PER_SEC;

                bool resourceAlive = !resource->IsForce() && resource->IsAlive() && !m_force;
                if (resource->GetCountUses() > 0 || !resource->IsDestroy() || resourceAlive) {
                    ++resourceIt;
                    continue;
                }

                if (Debug::GetLevel() >= Debug::Level::High)
                    Debug::Log("ResourceManager::GC() : free \"" + std::string(resource->m_resource_name) + "\" resource");

                this->Remove(resource);

                m_countResourcesToDestroy--;
                resourceIt = m_resourcesToDestroy.erase(resourceIt);

                delete resource;
            }

            if (Debug::GetLevel() >= Debug::Level::High && m_countResourcesToDestroy == 0)
                Debug::Log("ResourceManager::GC() : complete garbage collection.");
        } while(m_isInit);
    }

    void ResourceManager::RegisterResource(IResource *resource) {
        if (Debug::GetLevel() >= Debug::Level::Full)
            Debug::Log("ResourceManager::RegisterResource() : add new \""+std::string(resource->GetResourceName())+"\" resource."); //\n\tResource IDd: "+resource->m_resource_id

        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

        m_resources[resource->m_resource_name].push_back(resource);
    }

    void ResourceManager::PrintMemoryDump() {
        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

        std::string dump = "\n================================ MEMORY DUMP ================================";

        for (const auto& [resType, resources] : m_resources){
            dump += "\n\t\"" + resType + "\": " + std::to_string(resources.size());
            if (!resources.empty())
                if (strcmp(resources[0]->m_resource_name, "Texture") == 0) {
                    std::string textures;
                    for (IResource* res : resources){
                        textures += "\n\t\tUses = "+std::to_string(res->GetCountUses());
                    }
                    dump+= textures;
                }
        }



        std::string wait;
        for (auto res : m_resourcesToDestroy) {
            wait += "\n\t\t" + res->m_resource_id + "; uses = " +std::to_string(res->GetCountUses());
        }

        dump += "\n\tWait destroy: " + std::to_string(m_resourcesToDestroy.size()) + wait;

        dump += "\n=============================================================================";
        Debug::System(dump);
    }

    IResource *ResourceManager::Find(const std::string& Name, const std::string& ID) {
        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

        for (auto find : m_resources[Name])
            if (find->m_resource_id == ID && !find->m_isDestroy)
                return find;

        return nullptr;
    }

    void ResourceManager::Synchronize(bool force) {
        m_force = true;
        while (m_countResourcesToDestroy > 0);
        m_force = false;
    }
}