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
    unsigned long long ResourceManager::GetUsedMemoryLoad() noexcept {
        PROCESS_MEMORY_COUNTERS pmc;
        BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
        if (result)
            return (long long) pmc.PeakWorkingSetSize;
        else
            return -1;
    }

    bool ResourceManager::Init(std::string resourcesFolder) {
        Debug::Info("ResourceManager::Init() : initializing resource manager...\n\tResources folder: "+resourcesFolder);

        ResourceManager::g_resourcesFolder = resourcesFolder;
        ResourceManager::g_isInit = true;

        g_thread = std::thread(ResourceManager::GC);

        return true;
    }

    bool ResourceManager::Stop() {
        Debug::Info("ResourceManager::Stop() : stopping resource manager...");

        PrintMemoryDump();

        ResourceManager::g_isInit = false;

        if (g_thread.joinable()) g_thread.join();

        return true;
    }

    bool ResourceManager::Destroy(IResource *resource) {
        if (Debug::GetLevel() >= Debug::Level::High)
            Debug::Log("ResourceManager::Destroy() : destroying \""+ std::string(resource->m_resource_name) +"\"");

        //ret:
        //if (g_grabbleNow)
        //    goto ret;

        g_mutex.lock();

        g_resourcesToDestroy.push_back(resource);
        g_countResourcesToDestroy++;

        g_mutex.unlock();

        return true;
    }

    bool ResourceManager::RegisterType(const std::string& type_name) {
        Debug::Info("ResourceManager::RegisterType() : register new \""+std::string(type_name)+"\" type...");
        
        g_resources[type_name] = std::vector<IResource*>();
        g_resources[type_name].reserve(500 * 500);

        return true;
    }

    void ResourceManager::Remove(IResource *resource) {
        std::vector<IResource*> res;
        if (g_resources.GetOnly(resource->m_resource_name, &res)) {
            size_t size = res.size();
            for (size_t t = 0; t < size; t++){
                if (res[t] == resource) {
                    g_resources[resource->m_resource_name].erase(g_resources[resource->m_resource_name].begin() + t);
                    break;
                }
            }
        }
        else {
            Debug::Error(
                    "ResourceManager::Remove() : unknown resource! Name: " + std::string(resource->m_resource_name));
        }
    }

    void ResourceManager::GC() {
        while(g_isInit){
            if (g_countResourcesToDestroy == 0)
                continue;

            //if (!g_mutex.try_lock())
            //    continue;

            g_mutex.lock();

            g_grabbleNow = true;

            for (size_t t = 0; t < g_resourcesToDestroy.size(); t++) {
                //std::cout << g_resourcesToDestroy[t]->m_resource_name << " " << g_resourcesToDestroy[t]->m_countUses << std::endl;

                if (g_resourcesToDestroy[t]->m_countUses == 0 && g_resourcesToDestroy[t]->m_isDestroy) {
                    if (Debug::GetLevel() >= Debug::Level::High)
                        Debug::Log("ResourceManager::GC() : free \"" +
                                   std::string(g_resourcesToDestroy[t]->m_resource_name) + "\" resource");

                    // erase IResource from resources
                    ResourceManager::Remove(g_resourcesToDestroy[t]);

                    // delete IResource
                    //g_destroy_functions[g_resourcesToDestroy[t]->m_resource_name](g_resourcesToDestroy[t]);

                    //std::cout << g_resourcesToDestroy[t]->m_resource_id << " " << g_resourcesToDestroy[t]->m_countUses << " " << g_resourcesToDestroy[t]->m_isDestroy << std::endl;

                    // Free memory
                    g_resourcesToDestroy[t]->Free();

                    // remove "resources to destroy"
                    g_countResourcesToDestroy--;
                    g_resourcesToDestroy.erase(g_resourcesToDestroy.begin() + t);
                }
            }

            if (Debug::GetLevel() >= Debug::Level::High && g_countResourcesToDestroy == 0)
                Debug::Log("ResourceManager::GC() : complete garbage collection.");

            g_grabbleNow = false;

            g_mutex.unlock();
        }
    }

    void ResourceManager::RegisterResource(IResource *resource) {
        if (Debug::GetLevel() >= Debug::Level::High)
            Debug::Log("ResourceManager::RegisterResource() : add new \""+std::string(resource->GetResourceName())+"\" resource."); //\n\tResource IDd: "+resource->m_resource_id

        g_mutex.lock();

        g_resources[resource->m_resource_name].push_back(resource);

        g_mutex.unlock();
    }

    void ResourceManager::PrintMemoryDump() {
        std::string dump = "\n================================ MEMORY DUMP ================================";

        for (auto a : g_resources){
            dump += "\n\t\"" + a.x + "\": " + std::to_string(a.y.size());
            if (a.y.size() > 0)
                if (a.y[0]->m_resource_name == "Texture")
                {
                    std::string textures;
                    for (IResource* res : a.y){
                        textures += "\n\t\tUses = "+std::to_string(res->GetCountUses());
                    }
                    dump+= textures;
                }
        }



        std::string wait = "";
        for (auto res : g_resourcesToDestroy) {
            wait += "\n\t\t" + res->m_resource_id + "; uses = " +std::to_string(res->GetCountUses());
        }

        dump += "\n\tWait destroy:" + std::to_string(g_resourcesToDestroy.size()) + wait;

        dump += "\n=============================================================================";
        Debug::System(dump);
    }

    IResource *ResourceManager::Find(const std::string& Name, const std::string& ID) {
        IResource* res = nullptr;

        g_mutex.lock();

        for (auto find : g_resources[Name])
            if (find->m_resource_id == ID && !find->m_isDestroy)
            {
                res = find;
                break;
            }

        g_mutex.unlock();

        return res;
    }
}