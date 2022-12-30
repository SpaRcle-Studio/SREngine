//
// Created by Monika on 02.05.2022.
//

#include <Utils/ResourceManager/ResourceInfo.h>

namespace SR_UTILS_NS {
    IResource *ResourceType::Find(const ResourceType::ResourceId &id)  {
        if (auto&& pIt = m_copies.find(id); pIt == m_copies.end()) {
            return nullptr;
        }
        else {
            if (pIt->second.empty()) {
                return nullptr;
            }
            else {
                for (auto&& pResource : pIt->second) {
                    if (pResource->IsDestroyed()) {
                        continue;
                    }

                    return pResource;
                }

                return nullptr;
            }
        }
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
        auto&& path = pResource->GetResourceHashPath();

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

        auto&& info = m_info.at(path);

        info.m_loaded.erase(pResource);

        if (info.m_loaded.empty()) {
            m_info.erase(path);
        }

        /// -------------------------------------------------------------

        m_resources.erase(pResource);
    }

    void ResourceType::Add(IResource* pResource) {
        m_copies[pResource->GetResourceHashId()].insert(pResource);
        m_resources.insert(pResource);

        pResource->OnResourceRegistered();

        auto&& path = pResource->GetResourceHashPath();

        if (auto&& pIt = m_info.find(path); pIt != m_info.end()) {
            auto&& [_, info] = *pIt;
            info.m_loaded.insert(pResource);
        }
        else {
            (m_info[path] = ResourceInfo(
                    pResource->GetFileHash(),
                    pResource->GetResourceHash()
            )).m_loaded.insert(pResource);
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
}