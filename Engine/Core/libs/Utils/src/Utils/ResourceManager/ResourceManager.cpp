//
// Created by Nikita on 16.11.2020.
//

#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/Features.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Common/Hashes.h>

namespace SR_UTILS_NS {
    /// Seconds
    const float_t ResourceManager::ResourceLifeTime = 30.f;

    bool ResourceManager::Init(const std::string& resourcesFolder) {
    #ifdef SR_ANDROID
        SR_INFO("ResourceManager::Init() : initializing resource manager...");
    #else
        SR_INFO("ResourceManager::Init() : initializing resource manager...\n\tResources folder: " + resourcesFolder);
    #endif

        m_folder = resourcesFolder;

        m_resources.max_load_factor(0.9f);

        m_isInit = true;

        m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create(std::thread(&ResourceManager::Thread, this));

        return true;
    }

    void ResourceManager::OnSingletonDestroy() {
        SR_INFO("ResourceManager::OnSingletonDestroy() : stopping resource manager...");

        PrintMemoryDump();

        m_isInit = false;

        Synchronize(true);

        SR_INFO("ResourceManager::OnSingletonDestroy() : stopping thread...");

        if (m_thread) {
            m_thread->TryJoin();
            m_thread->Free();
            m_thread = nullptr;
        }

        PrintMemoryDump();
    }

    bool ResourceManager::Destroy(IResource *resource) {
        if (Debug::Instance().GetLevel() >= Debug::Level::High) {
            SR_LOG("ResourceManager::Destroy() : destroying \"" + std::string(resource->GetResourceName()) + "\"");
        }

        SR_SCOPED_LOCK

        m_destroyed.emplace_back(resource);

        return true;
    }

    bool ResourceManager::RegisterType(const std::string& name, uint64_t hashTypeName) {
        SR_INFO("ResourceManager::RegisterType() : register new \"" + name + "\" type...");

        if (m_resources.count(hashTypeName) == 1) {
            SRHalt("ResourceManager::RegisterType() : type already registered!");
            return false;
        }

        m_resources.insert(std::make_pair(
            hashTypeName,
            ResourceType(name)
        ));

        return true;
    }

    void ResourceManager::Remove(IResource *pResource) {
        if (pResource->IsRegistered()) {
            auto&& [name, resourcesGroup] = *m_resources.find(pResource->GetResourceHashName());
            resourcesGroup.Remove(pResource);
        }
        else {
           SRHalt("Resource ins't registered! "
                "\n\tType: " + std::string(pResource->GetResourceName()) +
                "\n\tId: " + std::string(pResource->GetResourceId()));
        }
    }

    bool ResourceManager::IsLastResource(IResource* pResource) {
        auto&& [name, resourcesGroup] = *m_resources.find(pResource->GetResourceHashName());
        return resourcesGroup.IsLast(pResource->GetResourceHashId());
    }

    void ResourceManager::Thread() {
        do {
            auto time = clock();
            m_deltaTime = time - m_lastTime;
            m_lastTime = time;

            /// даем возможность другим потокам отдать ресурсы на уничтожение,
            /// чтобы сразу же не блокировать им эту возможность
            if (m_force) {
                SR_HTYPES_NS::Thread::Sleep(100);
            }
            else {
                SR_HTYPES_NS::Thread::Sleep(500);
            }

            SR_SCOPED_LOCK

            GC();

            if (Features::Instance().Enabled("AutoReloadResources", false)) {
                CheckResourceHashes();
            }
        }
        while(m_isInit);
    }

    void ResourceManager::GC() {
        if (m_destroyed.empty()) {
            return;
        }

        if (m_force) {
            for (auto&& [hashName, group] : m_resources) {
                group.CollectUnused();
            }
        }

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

            if (Debug::Instance().GetLevel() >= Debug::Level::Medium) {
                SR_LOG("ResourceManager::GC() : free \"" + std::string(resource->GetResourceId()) + "\" resource");
            }

            Remove(resource);

            {
                /// так как некоторые ресурсы рекурсивно уничтожают дочерныие ресурсы при вызове деструктора, например материал,
                /// то он добавит в m_resourcesToDestroy новый элемент (в этом же потоке), соответственно любой итератор
                /// инвалидируется, и здесь может потенциально случиться краш, поэтому этот порядок нужно строго союлюдать

                m_destroyed.erase(resourceIt);
                delete resource;
                resourceIt = m_destroyed.begin();
            }
        }

        if (Debug::Instance().GetLevel() >= Debug::Level::High && m_destroyed.empty()) {
            SR_LOG("ResourceManager::GC() : complete garbage collection.");
        }
    }

    void ResourceManager::RegisterResource(IResource *pResource) {
        SRAssert(!pResource->IsRegistered());

        if (Debug::Instance().GetLevel() >= Debug::Level::Full) {
            SR_LOG("ResourceManager::RegisterResource() : add new \"" + std::string(pResource->GetResourceName()) + "\" resource.");
        }

        SR_SCOPED_LOCK

    #ifdef SR_DEBUG
        if (m_resources.count(pResource->GetResourceHashName()) == 0) {
            SRAssert2(false, "Unknown resource type!");
            return;
        }
    #endif

        auto&& [name, resourcesGroup] = *m_resources.find(pResource->GetResourceHashName());
        resourcesGroup.Add(pResource);
    }

    void ResourceManager::PrintMemoryDump() {
        SR_SCOPED_LOCK

        uint64_t count = 0;

        std::string dump = "\n================================ MEMORY DUMP ================================";

        for (const auto& [hashName, type] : m_resources) {
            dump += "\n\t\"" + std::string(type.GetName()) + "\": " + std::to_string(type.m_copies.size());

            uint32_t id = 0;
            for (auto& pRes : type.m_resources) {
                dump += SR_UTILS_NS::Format("\n\t\t%u: %s = %u", id++, pRes->GetResourceId().data(), pRes->GetCountUses());
                ++count;
            }
        }

        std::string wait;
        for (auto&& pResource : m_destroyed) {
            wait += "\n\t\t" + GetResourceId(pResource->GetResourceHashId()) + "; uses = " +std::to_string(pResource->GetCountUses());
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

    IResource *ResourceManager::Find(uint64_t hashTypeName, const std::string& id) {
        SR_SCOPED_LOCK

    #if defined(SR_DEBUG)
        if (m_resources.count(hashTypeName) == 0) {
            SRHalt("Unknown resource type!");
            return nullptr;
        }
    #endif

        auto&& [name, resourcesGroup] = *m_resources.find(hashTypeName);

        if (auto&& pResource = resourcesGroup.Find(SR_HASH_STR(id))) {
            return pResource;
        }

        return nullptr;
    }

    void ResourceManager::Synchronize(bool force) {
        {
            SR_SCOPED_LOCK
            m_force = true;
        }

        /// TODO: добавить таймер, по истечению которого поток будет умирать, чтобы не стоять в deadlock'е

        for (uint8_t i = 0; i < 255; ++i) 
        {
            for (;;)
            {
                {
                    SR_SCOPED_LOCK
                    if (m_destroyed.empty()) {
                        break;
                    }
                }

                if (!m_thread->Joinable()) {
                    SR_ERROR("ResourceManager::Synchronize() : thread is dead!");
                    break;
                }
            }
        }

        {
            SR_SCOPED_LOCK
            m_force = false;
        }
    }

    void ResourceManager::InspectResources(const std::function<void(const ResourcesTypes &)> &callback) {
        SR_SCOPED_LOCK

        callback(m_resources);
    }

    void ResourceManager::CheckResourceHashes() {
        SR_LOCK_GUARD

        for (auto&& [_, type] : m_resources) {
            for (auto&& [path, info] : type.GetInfo()) {
                bool needReload = false;

                for (auto&& pResource : info.m_loaded) {
                    if (pResource->IsDestroyed()) {
                        continue;
                    }

                    auto&& fileHash = pResource->GetFileHash();
                    if (fileHash != info.m_fileHash) {
                        needReload = true;
                        info.m_fileHash = fileHash;
                    }
                }

                if (!needReload) {
                    continue;
                }

                for (auto&& pResource : info.m_loaded) {
                    if (pResource->IsDestroyed()) {
                        continue;
                    }

                    auto&& loadState = pResource->GetResourceLoadState();

                    using LS = IResource::LoadState;
                    if (loadState == LS::Reloading || loadState == LS::Loading || loadState == LS::Unloading) {
                        continue;
                    }

                    pResource->Reload();
                }
            }
        }
    }

    std::string_view ResourceManager::GetTypeName(uint64_t hashName) const {
        SR_SCOPED_LOCK

        if (auto&& pIt = m_resources.find(hashName); pIt != m_resources.end()) {
            return pIt->second.GetName();
        }

        SRHalt("ResourceManager::GetTypeName() : unknown hash name!");

        return "Unknown";
    }

    const std::string& ResourceManager::GetResourceId(ResourceManager::Hash hashId) const {
        SR_SCOPED_LOCK

        auto&& pIt = m_hashIds.find(hashId);

        if (pIt == m_hashIds.end()) {
            SRHalt("ResourceManager::GetResourceId() : id is not registered!");
            static std::string defaultId;
            return defaultId;
        }

        return pIt->second;
    }

    ResourceManager::Hash ResourceManager::RegisterResourceId(const std::string& resourceId) {
        SR_SCOPED_LOCK

        const ResourceManager::Hash hash = SR_HASH_STR(resourceId);

        auto&& pIt = m_hashIds.find(hash);

        if (pIt == m_hashIds.end()) {
            m_hashIds.insert(std::make_pair(hash, resourceId));
        }

        return hash;
    }

    const Path &ResourceManager::GetResourcePath(ResourceManager::Hash hashPath) const {
        SR_SCOPED_LOCK

        auto&& pIt = m_hashPaths.find(hashPath);

        if (pIt == m_hashPaths.end()) {
            SRHalt("ResourceManager::GetResourcePath() : path is not registered!");
            static Path defaultPath;
            return defaultPath;
        }

        return pIt->second;
    }

    ResourceManager::Hash ResourceManager::RegisterResourcePath(const Path &path) {
        SR_SCOPED_LOCK

        const ResourceManager::Hash hash = path.GetHash();

        auto&& pIt = m_hashPaths.find(hash);

        if (pIt == m_hashPaths.end()) {
            m_hashPaths.insert(std::make_pair(hash, path));
        }

        return hash;
    }
}