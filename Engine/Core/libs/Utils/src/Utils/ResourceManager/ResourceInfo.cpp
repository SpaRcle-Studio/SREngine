//
// Created by Monika on 02.05.2022.
//

#include <Utils/ResourceManager/ResourceInfo.h>
#include <Utils/ResourceManager/IResourceReloader.h>

namespace SR_UTILS_NS {
    ResourceType::~ResourceType() {
        SetReloader(nullptr);
    }

    IResource* ResourceType::Find(const ResourceType::ResourceId &id)  {
        auto&& pIt = m_copies.find(id);
        if (pIt == m_copies.end()) {
            return nullptr;
        }

        if (pIt->second.empty()) {
            return nullptr;
        }

        for (auto&& pResource : pIt->second) {
            const bool skip = pResource->Execute([pResource](){
                if (!pResource->IsDestroyed()) {
                    return false;
                }

                if (pResource->IsAllowedToRevive()) {
                    if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Medium) {
                        SR_LOG("ResourceType::Find() : revive resource \"" + pResource->GetResourceId() + "\"");
                    }
                    pResource->ReviveResource();
                    return false;
                }

                return true;
            });

            if (skip) {
                continue;
            }

            return pResource;
        }

        return nullptr;
    }

    bool ResourceType::IsLast(const ResourceType::ResourceId &id) {
        if (auto&& pIt = m_copies.find(id); pIt == m_copies.end()) {
            return true;
        }
        else
            return pIt->second.size() == 1;
    }

    void ResourceType::Remove(IResource *pResource) {
        const auto id = pResource->GetResourceHashId();
        auto&& hashPath = pResource->GetResourceHashPath();

        /// -------------------------------------------------------------

        if (auto &&group = m_copies.find(id); group != m_copies.end()) {
            group->second.erase(pResource);
        }
        else {
            SRHalt("Resource not found!");
            return;
        }

        if (m_copies.at(id).empty()) {
            m_copies.erase(id);
        }

        /// -------------------------------------------------------------

        auto&& pInfo = m_info.at(hashPath);

        pInfo->m_loaded.erase(pResource);

        if (pInfo->m_loaded.empty()) {
            m_info.erase(hashPath);
        }

        /// -------------------------------------------------------------

        m_resources.erase(pResource);
    }

    void ResourceType::Add(IResource* pResource) {
        m_copies[pResource->GetResourceHashId()].insert(pResource);
        m_resources.insert(pResource);

        pResource->OnResourceRegistered();

        auto&& path = pResource->GetResourceHashPath();
        auto&& pIt = m_info.find(path);

    retry:
        if (pIt != m_info.end()) {
            auto&& [_, pInfo] = *pIt;
            pInfo->m_loaded.insert(pResource);
            pResource->m_resourceInfo = pInfo.get();
        }
        else {
            auto&& pInfo = std::make_shared<ResourceInfo>(pResource->GetFileHash(), pResource->GetResourceHash(), this);
            pIt = m_info.insert(std::make_pair(path, pInfo)).first;
            goto retry;
        }
    }

    const ResourceType::CopiesMap& ResourceType::GetCopiesRef() const {
        return m_copies;
    }

    ResourceType::Info& ResourceType::GetInfo() {
        return m_info;
    }

    void ResourceType::CollectUnused() {
        for (auto&& pResource : m_resources) {
            pResource->Execute([pResource]() -> bool {
                if (pResource->GetCountUses() > 0) {
                    return false;
                }

                if (pResource->IsDestroyed()) {
                    return false;
                }

                pResource->Destroy();

                return true;
            });
        }
    }

    std::pair<ResourceType::ResourcePath, ResourceInfo::HardPtr> ResourceType::GetInfoByIndex(uint64_t index) {
        if (index >= m_info.size()) {
            return std::make_pair(0, nullptr);
        }

        auto&& [hash, info] = *std::next(m_info.begin(), index);

        return std::make_pair(hash, info);
    }

    void ResourceType::SetReloader(IResourceReloader *pReloader) {
        if (m_reloader) {
            delete m_reloader;
            m_reloader = nullptr;
        }
        m_reloader = pReloader;
    }

    IResource::Ptr ResourceInfo::GetResource() const {
        if (m_loaded.size() != 1) {
            SRHalt("Incorrect function usage!");
            return nullptr;
        }

        return *m_loaded.begin();
    }

    IResource *ResourceInfo::GetFirstResource() const {
        if (m_loaded.size() == 0) {
            SRHalt("Incorrect function usage!");
            return nullptr;
        }

        return *m_loaded.begin();
    }
}