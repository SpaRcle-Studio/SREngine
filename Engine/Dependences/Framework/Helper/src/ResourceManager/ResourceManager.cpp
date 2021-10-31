//
// Created by Nikita on 16.11.2020.
//

#include "ResourceManager/ResourceManager.h"

#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <random>
#include <ostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <Psapi.h>

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

#include <Debug.h>

namespace Framework::Helper {
    uint64_t ResourceManager::GetUsedMemoryLoad() noexcept {
        PROCESS_MEMORY_COUNTERS pmc;
        BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
        if (result)
            return (long long) pmc.PeakWorkingSetSize;
        else
            return -1;
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
        std::vector<IResource*> res;
        if (m_resources.GetOnly(resource->m_resource_name, &res)) {
            size_t size = res.size();
            for (size_t t = 0; t < size; t++){
                if (res[t] == resource) {
                    m_resources[resource->m_resource_name].erase(m_resources[resource->m_resource_name].begin() + t);
                    break;
                }
            }
        }
        else {
            Debug::Error("ResourceManager::Remove() : unknown resource! Name: " + std::string(resource->m_resource_name));
        }
    }

    void ResourceManager::GC() {
        while(m_isInit){
            if (m_countResourcesToDestroy == 0)
                continue;

            const std::lock_guard<std::recursive_mutex> lock(m_mutex);

            for (auto resourceIt = m_resourcesToDestroy.begin(); resourceIt != m_resourcesToDestroy.end(); ++resourceIt) {
                auto resource = *resourceIt;

                if (resource->m_countUses > 0 || !resource->m_isDestroy)
                    continue;

                if (Debug::GetLevel() >= Debug::Level::High)
                    Debug::Log("ResourceManager::GC() : free \"" + std::string(resource->m_resource_name) + "\" resource");

                this->Remove(resource);

                m_countResourcesToDestroy--;
                m_resourcesToDestroy.erase(resourceIt);

                delete resource;

                break;
            }

            if (Debug::GetLevel() >= Debug::Level::High && m_countResourcesToDestroy == 0)
                Debug::Log("ResourceManager::GC() : complete garbage collection.");
        }
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

        for (const auto& resource : m_resources){
            dump += "\n\t\"" + resource.x + "\": " + std::to_string(resource.y.size());
            if (!resource.y.empty())
                if (strcmp(resource.y[0]->m_resource_name, "Texture") == 0) {
                    std::string textures;
                    for (IResource* res : resource.y){
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

    void ResourceManager::Synchronize() {
        while (m_countResourcesToDestroy > 0);
    }
}