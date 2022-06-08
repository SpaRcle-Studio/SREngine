//
// Created by Nikita on 16.11.2020.
//

#include <ResourceManager/ResourceManager.h>
#include <Utils/Features.h>

namespace SR_UTILS_NS {
    const float_t ResourceManager::ResourceLifeTime = 30.f; // seconds

    bool ResourceManager::Init(const std::string& resourcesFolder) {
        SR_INFO("ResourceManager::Init() : initializing resource manager...\n\tResources folder: "+resourcesFolder);

        m_folder = resourcesFolder;
        m_folder.Normalize();

        m_isInit = true;

        m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create(std::thread(&ResourceManager::Thread, this));

        return true;
    }

    bool ResourceManager::Stop() {
        SR_INFO("ResourceManager::Stop() : stopping resource manager...");

        PrintMemoryDump();

        m_isInit = false;

        Synchronize(true);

        SR_INFO("ResourceManager::Stop() : stopping thread...");

        if (m_thread) {
            m_thread->TryJoin();
            m_thread->Free();
            m_thread = nullptr;
        }

        PrintMemoryDump();

        return true;
    }

    bool ResourceManager::Destroy(IResource *resource) {
        if (Debug::GetLevel() >= Debug::Level::High)
            SR_LOG("ResourceManager::Destroy() : destroying \""+ std::string(resource->m_resourceName) +"\"");

        SR_SCOPED_LOCK

        m_destroyed.emplace_back(resource);

        return true;
    }

    bool ResourceManager::RegisterType(const std::string& type_name) {
        SR_INFO("ResourceManager::RegisterType() : register new \"" + type_name + "\" type...");
        
        m_resources[type_name] = ResourceType();

        return true;
    }

    void ResourceManager::Remove(IResource *pResource) {
        if (pResource->IsValid()) {
            auto &&resourcesGroup = m_resources.at(pResource->m_resourceName);
            resourcesGroup.Remove(pResource);
        }
        else {
            SRAssert2(false, "Invalid resource! "
                             "\n\tType: " + std::string(pResource->GetResourceName()) +
                             "\n\tId: " + pResource->GetResourceId());
        }
    }

    bool ResourceManager::IsLastResource(IResource* resource) {
        return m_resources[resource->m_resourceName].IsLast(resource->m_resourceId);
    }

    void ResourceManager::Thread() {
        do {
            auto time = clock();
            m_deltaTime = time - m_lastTime;
            m_lastTime = time;

            /// даем возможность другим потокам отдать ресурсы на уничтожение,
            /// чтобы сразу же не блокировать им эту возможность
            Types::Thread::Sleep(100);

            SR_SCOPED_LOCK

            GC();

            if (Features::Instance().Enabled("AutoReloadResources", false)) {
                CheckResourceHashes();
            }
        }
        while(m_isInit);
    }

    void ResourceManager::GC() {
        if ((m_destroyIsEmpty = m_destroyed.empty()))
            return;

        auto resourceIt = m_destroyed.begin();
        for (; resourceIt != m_destroyed.end(); ) {
            auto resource = *resourceIt;

            const bool usageNow = resource->GetCountUses() > 0 || !resource->IsDestroyed();

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
                SR_LOG("ResourceManager::GC() : free \"" + std::string(resource->m_resourceName) + "\" resource");

            Remove(resource);

            {
                /// так как некоторые ресурсы рекурсивно уничтожают дочерныие ресурсы при вызове деструктора, например материал,
                /// то он добавит в m_resourcesToDestroy новый элемент (в этом же потоке), соответственно любой итератор
                /// инвалидируется, и здесь может потенциально случиться краш, поэтому этот порядок нужно строго союлюдать

                m_destroyed.erase(resourceIt);
                delete resource;
                resourceIt = m_destroyed.begin();
                m_destroyIsEmpty = m_destroyed.empty();
            }
        }

        if (Debug::GetLevel() >= Debug::Level::High && m_destroyIsEmpty) {
            SR_LOG("ResourceManager::GC() : complete garbage collection.");
        }
    }

    void ResourceManager::RegisterResource(IResource *resource) {
        SRAssert(resource->IsValid());

        if (Debug::GetLevel() >= Debug::Level::Full)
            SR_LOG("ResourceManager::RegisterResource() : add new \"" + std::string(resource->GetResourceName()) + "\" resource.");

        SR_SCOPED_LOCK

    #ifdef SR_DEBUG
        if (m_resources.count(resource->m_resourceName) == 0) {
            SRAssert2(false, "Unknown resource type!");
            return;
        }
    #endif

        m_resources.at(resource->m_resourceName).Add(resource);
    }

    void ResourceManager::PrintMemoryDump() {
        SR_SCOPED_LOCK

        uint64_t count = 0;

        std::string dump = "\n================================ MEMORY DUMP ================================";

        for (const auto& [name, type] : m_resources) {
            dump += "\n\t\"" + name + "\": " + std::to_string(type.m_copies.size());

            uint32_t id = 0;
            for (auto& pRes : type.m_resources) {
                dump += Helper::Format("\n\t\t%u: %s = %u", id++, pRes->GetResourceId().c_str(), pRes->GetCountUses());
                ++count;
            }
        }

        std::string wait;
        for (auto res : m_destroyed) {
            wait += "\n\t\t" + res->m_resourceId + "; uses = " +std::to_string(res->GetCountUses());
            ++count;
        }

        dump += "\n\tWait destroy: " + std::to_string(m_destroyed.size()) + wait;

        dump += "\n=============================================================================";

        if (count > 0) {
            SR_SYSTEM_LOG(dump);
        }
        else {
            SR_SYSTEM_LOG("Memory dump is empty!");
        }
    }

    IResource *ResourceManager::Find(const std::string& Name, const std::string& ID) {
        SR_SCOPED_LOCK

    #if defined(SR_DEBUG)
        if (m_resources.count(Name) == 0) {
            SRAssert2(false, "Unknown resource type!");
            return nullptr;
        }
    #endif

        IResource* pResource = m_resources.at(Name).Find(ID);

        if (pResource && !pResource->IsDestroyed())
            return pResource;

        return nullptr;
    }

    void ResourceManager::Synchronize(bool force) {
        {
            SR_SCOPED_LOCK
            m_force = true;
        }

        while (!m_destroyIsEmpty) {
            if (!m_thread->Joinable()) {
                SR_ERROR("ResourceManager::Synchronize() : thread is dead!");
                break;
            }
        }

        m_force = false;
    }

    void ResourceManager::InspectResources(const std::function<void(const ResourcesTypes &)> &callback) {
        SR_SCOPED_LOCK

        callback(m_resources);
    }

    void ResourceManager::CheckResourceHashes() {
        for (auto&& [_, type] : m_resources) {
            for (auto&& [path, info] : type.GetInfo()) {
                for (auto&& pResource : info.m_loaded) {
                    auto&& fileHash = pResource->GetFileHash();
                    if (fileHash != info.m_fileHash) {
                        pResource->Reload();
                        info.m_fileHash = fileHash;
                    }
                }
            }
        }
    }
}