//
// Created by Nikita on 16.11.2020.
//

#include "ResourceManager/ResourceManager.h"

#ifdef SR_WIN32
    #define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

    #include <Psapi.h>
    #include <Windows.h>
#endif

namespace Framework::Helper {
    const float_t ResourceManager::ResourceLifeTime = 10.f; // seconds

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
        m_resourcesFolder.Normalize();

        m_isInit = true;

        m_thread = Types::Thread(std::thread(&ResourceManager::GC, this));

        return true;
    }

    bool ResourceManager::Stop() {
        Debug::Info("ResourceManager::Stop() : stopping resource manager...");

        m_isInit = false;

        Synchronize(true);

        Debug::Info("ResourceManager::Stop() : stopping thread...");

        m_thread.TryJoin();

        PrintMemoryDump();

        return true;
    }

    bool ResourceManager::Destroy(IResource *resource) {
        if (Debug::GetLevel() >= Debug::Level::High)
            SR_LOG("ResourceManager::Destroy() : destroying \""+ std::string(resource->m_resourceName) +"\"");

        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

        m_resourcesToDestroy.emplace_back(resource);

        return true;
    }

    bool ResourceManager::RegisterType(const std::string& type_name) {
        Debug::Info("ResourceManager::RegisterType() : register new \""+std::string(type_name)+"\" type...");
        
        m_resources[type_name] = ResourceInfo();

        return true;
    }

    void ResourceManager::Remove(IResource *resource) {
        SRAssert(resource->IsValid());
            auto&& resourcesGroup = m_resources.at(resource->m_resourceName);
        resourcesGroup.Remove(resource);
    }

    bool ResourceManager::IsLastResource(IResource* resource) {
        return m_resources[resource->m_resourceName].IsLast(resource->m_resourceId);
    }

    void ResourceManager::GC() {
        do {
            auto time = clock();
            m_deltaTime = time - m_lastTime;
            m_lastTime = time;

            /// даем возможность другим потокам отдать ресурсы на уничтожение,
            /// чтобы сразу же не блокировать им эту возможность
            Types::Thread::Sleep(100);

            const std::lock_guard<std::recursive_mutex> lock(m_mutex);

            if ((m_destroyIsEmpty = m_resourcesToDestroy.empty()))
                continue;

            auto resourceIt = m_resourcesToDestroy.begin();
            for (; resourceIt != m_resourcesToDestroy.end(); ) {
                auto resource = *resourceIt;

                const bool usageNow = resource->GetCountUses() > 0 || !resource->IsDestroy();

                if (usageNow) {
                    resource->m_lifetime = ResourceLifeTime;
                }
                else if (IsLastResource(resource)) {
                    resource->m_lifetime -= double_t(m_deltaTime) / (double_t)CLOCKS_PER_SEC;
                }
                else {
                    /// нам не нужно ждать завершения времени жизни ресурса, у которого еще есть копии
                    resource->m_lifetime = 0.f;
                }

                const bool resourceAlive = !resource->IsForce() && resource->IsAlive() && !m_force;


                if (usageNow || resourceAlive) {
                    ++resourceIt;
                    continue;
                }

                if (Debug::GetLevel() >= Debug::Level::High)
                    Debug::Log("ResourceManager::GC() : free \"" + std::string(resource->m_resourceName) + "\" resource");

                Remove(resource);

                {
                    /// так как некоторые ресурсы рекурсивно уничтожают дочерныие ресурсы при вызове деструктора, например материал,
                    /// то он добавит в m_resourcesToDestroy новый элемент (в этом же потоке), соответственно любой итератор
                    /// инвалидируется, и здесь может потенциально случиться краш, поэтому этот порядок нужно строго союлюдать

                    m_resourcesToDestroy.erase(resourceIt);
                    delete resource;
                    resourceIt = m_resourcesToDestroy.begin();
                    m_destroyIsEmpty = m_resourcesToDestroy.empty();
                }
            }

            if (Debug::GetLevel() >= Debug::Level::High && m_destroyIsEmpty) {
                Debug::Log("ResourceManager::GC() : complete garbage collection.");
            }
        }
        while(m_isInit);
    }

    void ResourceManager::RegisterResource(IResource *resource) {
        SRAssert(resource->IsValid());

        if (Debug::GetLevel() >= Debug::Level::Full)
            Debug::Log("ResourceManager::RegisterResource() : add new \"" + std::string(resource->GetResourceName()) + "\" resource.");

        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    #if defined(SR_DEBUG)
        if (m_resources.count(resource->m_resourceName) == 0) {
            SRAssert2(false, "Unknown resource type!");
            return;
        }
    #endif

        m_resources.at(resource->m_resourceName).Add(resource);
    }

    void ResourceManager::PrintMemoryDump() {
        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

        std::string dump = "\n================================ MEMORY DUMP ================================";

        for (const auto& [resType, group] : m_resources) {
            dump += "\n\t\"" + resType + "\": " + std::to_string(group.m_copies.size());

            uint32_t id = 0;
            for (auto& pRes : group.m_group) {
                dump += Helper::Format("\n\t\t%u: %s", id++, pRes->GetResourceId().c_str());
            }
        }

        std::string wait;
        for (auto res : m_resourcesToDestroy) {
            wait += "\n\t\t" + res->m_resourceId + "; uses = " +std::to_string(res->GetCountUses());
        }

        dump += "\n\tWait destroy: " + std::to_string(m_resourcesToDestroy.size()) + wait;

        dump += "\n=============================================================================";
        Debug::System(dump);
    }

    IResource *ResourceManager::Find(const std::string& Name, const std::string& ID) {
        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    #if defined(SR_DEBUG)
        if (m_resources.count(Name) == 0) {
            SRAssert2(false, "Unknown resource type!");
            return nullptr;
        }
    #endif

        IResource* pResource = m_resources.at(Name).Find(ID);

        if (pResource && !pResource->m_isDestroy)
            return pResource;

        return nullptr;
    }

    void ResourceManager::Synchronize(bool force) {
        {
            const std::lock_guard<std::recursive_mutex> lock(m_mutex);
            m_force = true;
        }

        while (!m_destroyIsEmpty) {
            if (!m_thread.Joinable()) {
                SR_ERROR("ResourceManager::Synchronize() : thread is dead!");
            }
        }

        m_force = false;
    }
}