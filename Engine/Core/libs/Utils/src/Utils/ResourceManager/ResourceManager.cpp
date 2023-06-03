//
// Created by Nikita on 16.11.2020.
//

#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/ResourceManager/IResourceReloader.h>
#include <Utils/Common/Features.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Common/Hashes.h>

namespace SR_UTILS_NS {
    /// Milliseconds
    const uint64_t ResourceManager::ResourceLifeTime = 30 * 1000;

    bool ResourceManager::Init(const SR_UTILS_NS::Path& resourcesFolder) {
    #ifdef SR_ANDROID
        SR_INFO("ResourceManager::Init() : initializing resource manager...");
    #else
        SR_INFO("ResourceManager::Init() : initializing resource manager...\n\tResources folder: " + resourcesFolder.ToString());
    #endif

        m_defaultReloader = new DefaultResourceReloader();

        m_folder = resourcesFolder;

        m_resources.max_load_factor(0.9f);

        m_isInit = true;

        return true;
    }

    void ResourceManager::OnSingletonDestroy() {
        SR_INFO("ResourceManager::OnSingletonDestroy() : stopping resource manager...");

        PrintMemoryDump();

        m_isInit = false;
        m_isRun = false;

        Synchronize(true);

        SR_INFO("ResourceManager::OnSingletonDestroy() : stopping thread...");

        if (m_thread) {
            m_thread->TryJoin();
            m_thread->Free();
            m_thread = nullptr;
        }

        PrintMemoryDump();

        SR_SAFE_DELETE_PTR(m_defaultReloader);

        for (auto&& [hashTypeName, pResourceType] : m_resources) {
            delete pResourceType;
        }
        m_resources.clear();
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
            new ResourceType(name)
        ));

        m_checkResourceGroupIt = m_resources.begin();

        return true;
    }

    void ResourceManager::Remove(IResource *pResource) {
        if (pResource->IsRegistered()) {
            auto&& pGroupIt = m_resources.find(pResource->GetResourceHashName());
            auto&& [name, resourcesGroup] = *pGroupIt;
            resourcesGroup->Remove(pResource);
        }
        else {
           SRHalt("Resource ins't registered! "
                "\n\tType: " + std::string(pResource->GetResourceName()) +
                "\n\tId: " + std::string(pResource->GetResourceId()));
        }
    }

    bool ResourceManager::IsLastResource(IResource* pResource) {
        auto&& [name, resourcesGroup] = *m_resources.find(pResource->GetResourceHashName());
        return resourcesGroup->IsLast(pResource->GetResourceHashId());
    }

    void ResourceManager::Thread() {
        do {
            SR_PLATFORM_NS::Sleep(25);

            SR_TRACY_ZONE;

            auto time = clock();
            m_deltaTime = static_cast<uint64_t>(time - m_lastTime); /// miliseconds
            m_lastTime = time;

            m_GCDt += m_deltaTime;
            m_hashCheckDt += m_deltaTime;

            if (m_hashCheckDt > 25 /** ms */) {
                CheckResourceHashes();
                m_hashCheckDt = 0;
            }

            if (m_GCDt > (m_force ? 500 : 100) /** ms */) {
                /** если какой-то ресурс больше не используется, то уничтожаем его.
                 * все происходящее в GC должно быть потоко-безопасным, то есть при освобождении
                 * ресурсов не должны блокироваться другие потоки, иначе будут проблемы. */
                GC();
                m_GCDt = 0;
            }
        }
        while(m_isRun);

        SR_INFO("ResourceManager::Thread() : exit from thread-function.");
    }

    void ResourceManager::GC() {
        SR_TRACY_ZONE;
        SR_SCOPED_LOCK

        if (m_destroyed.empty()) {
            return;
        }

        if (m_force) {
            for (auto&& [hashName, group] : m_resources) {
                group->CollectUnused();
            }
        }

        auto resourceIt = m_destroyed.begin();
        for (; resourceIt != m_destroyed.end(); ) {
            auto pResource = *resourceIt;

            /// ресурс был оживлен
            if (!pResource->IsDestroyed()) {
                m_destroyed.erase(resourceIt);
                resourceIt = m_destroyed.begin();
                continue;
            }

            const bool usageNow = pResource->GetCountUses() > 0 || !pResource->IsDestroyed();

            if (usageNow) {
                pResource->SetLifetime(ResourceLifeTime);
            }
            else if (IsLastResource(pResource)) {
                pResource->SetLifetime(pResource->GetLifetime() - m_GCDt);
            }
            else {
                /// нам не нужно ждать завершения времени жизни ресурса, у которого еще есть копии
                pResource->SetLifetime(0);
            }

            const bool resourceAlive = !pResource->IsForce() && pResource->IsAlive() && !m_force;

            if (usageNow || resourceAlive) {
                ++resourceIt;
                continue;
            }

            if (Debug::Instance().GetLevel() >= Debug::Level::Medium) {
                SR_LOG("ResourceManager::GC() : free \"" + std::string(pResource->GetResourceId()) + "\" resource");
            }

            Remove(pResource);

            {
                /// так как некоторые ресурсы рекурсивно уничтожают дочерныие ресурсы при вызове деструктора, например материал,
                /// то он добавит в m_resourcesToDestroy новый элемент (в этом же потоке), соответственно любой итератор
                /// инвалидируется, и здесь может потенциально случиться краш, поэтому этот порядок нужно строго союлюдать

                m_destroyed.erase(resourceIt);
                pResource->DeleteResource();
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

        auto&& pGroupIt = m_resources.find(pResource->GetResourceHashName());
        auto&& [name, resourcesGroup] = *pGroupIt;

        resourcesGroup->Add(pResource);
    }

    void ResourceManager::PrintMemoryDump() {
        SR_SCOPED_LOCK

        uint64_t count = 0;

        std::string dump = "\n================================ MEMORY DUMP ================================";

        for (const auto& [hashName, type] : m_resources) {
            dump += "\n\t\"" + std::string(type->GetName()) + "\": " + std::to_string(type->GetCopiesRef().size());

            uint32_t id = 0;
            for (auto& pRes : type->m_resources) {
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
        SR_TRACY_ZONE;
        SR_SCOPED_LOCK

    #if defined(SR_DEBUG)
        if (m_resources.count(hashTypeName) == 0) {
            SRHalt("Unknown resource type!");
            return nullptr;
        }
    #endif

        auto&& [name, resourcesGroup] = *m_resources.find(hashTypeName);

        if (auto&& pResource = resourcesGroup->Find(SR_HASH_STR(id))) {
            /// раз ресурс ищем, значит он все еще может быть нужен.
            pResource->UpdateResourceLifeTime();
            return pResource;
        }

        return nullptr;
    }

    void ResourceManager::Synchronize(bool force) {
        SR_TRACY_ZONE;

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

    void ResourceManager::Execute(const SR_HTYPES_NS::Function<void()>& fun)
    {
        SR_SCOPED_LOCK

        fun();
    }

    void ResourceManager::InspectResources(const SR_HTYPES_NS::Function<void(const ResourcesTypes &)> &callback) {
        SR_SCOPED_LOCK

        callback(m_resources);
    }

    void ResourceManager::CheckResourceHashes() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD

        if (m_resources.empty()) {
            return;
        }

        if (m_checkResourceGroupIt == m_resources.end()) {
            m_checkResourceGroupIt = m_resources.begin();
            m_checkInfoIndex = 0;
            return;
        }

        auto&& [hashPath, pResourceInfo] = m_checkResourceGroupIt->second->GetInfoByIndex(m_checkInfoIndex);
        if (!pResourceInfo) {
            m_checkResourceGroupIt = std::next(m_checkResourceGroupIt);
            m_checkInfoIndex = 0;
            return;
        }

        if (auto&& pResource = pResourceInfo->GetFirstResource()) {
            auto&& fileHash = pResource->GetFileHash();
            if (fileHash != pResourceInfo->m_fileHash) {
                /// если дважды положим один и тот же ресурс (слишком быстро перезагрузили), то будем считать,
                /// что не повезло и перезагрузим дважды.
                m_dirtyResources.emplace_back(pResourceInfo);
                pResourceInfo->m_fileHash = fileHash;
            }
        }

        ++m_checkInfoIndex;
    }

    std::string_view ResourceManager::GetTypeName(uint64_t hashName) const {
        SR_SCOPED_LOCK

        if (auto&& pIt = m_resources.find(hashName); pIt != m_resources.end()) {
            return pIt->second->GetName();
        }

        SRHalt("ResourceManager::GetTypeName() : unknown hash name!");

        return "Unknown";
    }

    const std::string& ResourceManager::GetResourceId(ResourceManager::Hash hashId) const {
        SR_SCOPED_LOCK

        /// пустая строка
        if (hashId == 0) {
            static SR_UTILS_NS::Path emptyPath;
            return emptyPath;
        }

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

    const Path& ResourceManager::GetResourcePath(ResourceManager::Hash hashPath) const {
        SR_TRACY_ZONE;
        SR_SCOPED_LOCK

        /// пустая строка
        if (hashPath == 0) {
            static SR_UTILS_NS::Path emptyPath;
            return emptyPath;
        }

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

        if (path.Empty()) {
            SRHalt("ResourceManager::RegisterResourcePath() : empty path!");
        }

        const ResourceManager::Hash hash = path.GetHash();

        auto&& pIt = m_hashPaths.find(hash);

        if (pIt == m_hashPaths.end()) {
            m_hashPaths.insert(std::make_pair(hash, path));
        }

        return hash;
    }

    bool ResourceManager::Run() {
        if (m_isRun) {
            SRHalt("ResourceManager::Run() : is already ran!");
            return false;
        }

        m_isRun = true;

        m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create(std::thread(&ResourceManager::Thread, this));

        return true;
    }

    bool ResourceManager::RegisterReloader(IResourceReloader *pReloader, uint64_t hashTypeName) {
        SR_SCOPED_LOCK

        if (auto&& pIt = m_resources.find(hashTypeName); pIt != m_resources.end()) {
            auto&& [_, resourceType] = *pIt;
            resourceType->SetReloader(pReloader);
            return true;
        }

        SRHalt("ResourceManager::RegisterReloader() : unknown hash name!");

        return false;
    }

    void ResourceManager::ReloadResources(float_t dt) {
        SR_TRACY_ZONE;

        /// не блокируем поток, иначе не будет смысла от разделения.
        /// если прочитаем некорректные данные из empty, будем считать, что не повезло.
        if (m_dirtyResources.empty()) {
            return;
        }

        SR_SCOPED_LOCK;

        for (auto&& pResourceInfo : m_dirtyResources) {
            /// ресурс мог быть освобожден в GC
            auto&& pHardPtr = pResourceInfo.lock();
            if (!pHardPtr) {
                continue;
            }

            IResourceReloader* pResourceReloader = nullptr;

            if (auto&& pGroupReloader = m_checkResourceGroupIt->second->GetReloader()) {
                pResourceReloader = pGroupReloader;
            }
            else {
                pResourceReloader = m_defaultReloader;
            }

            auto&& path = GetResourcePath(pHardPtr->m_pathHash);

            if (path.Empty()) {
                SR_ERROR("ResourceManager::ReloadResources() : resource have empty path!\n\tResource name: " +
                    pHardPtr->m_resourceType->GetName() + "\n\tHash name: " + std::to_string(pHardPtr->m_resourceHash) +
                    "\n\tFile hash: " + std::to_string(pHardPtr->m_fileHash) +
                    "\n\tPath hash: " + std::to_string(pHardPtr->m_pathHash)
                );
                continue;
            }

            if (pResourceReloader && !pResourceReloader->Reload(path, pHardPtr.get())) {
                SR_ERROR("ResourceManager::ReloadResources() : failed to reload resource!\n\tPath: " + path.ToStringRef());
            }
        }

        m_dirtyResources.clear();
    }
}