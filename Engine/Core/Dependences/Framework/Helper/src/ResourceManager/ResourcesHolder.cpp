//
// Created by Monika on 18.03.2022.
//

#include <ResourceManager/ResourcesHolder.h>

namespace SR_UTILS_NS {
    bool ResourcesHolder::Add(IResource *pResource) {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_resources.count(pResource) == 1) {
            SRAssert2(false, "Resource already hold!");
            return false;
        }

        pResource->AddUsePoint();
        m_resources.insert(pResource);

        return true;
    }

    bool ResourcesHolder::Remove(IResource *pResource) {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_resources.count(pResource) == 0) {
            SRAssert2(false, "Resource isn't hold!");
            return false;
        }

        pResource->RemoveUsePoint();
        m_resources.erase(pResource);

        return true;
    }

    void ResourcesHolder::Release() {
        std::lock_guard<std::mutex> lock(m_mutex);

        for (IResource* pResource : m_resources) {
            pResource->RemoveUsePoint();
        }

        m_resources.clear();
    }
}