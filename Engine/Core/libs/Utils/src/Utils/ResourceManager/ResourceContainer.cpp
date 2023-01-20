//
// Created by Monika on 20.01.2023.
//

#include <Utils/ResourceManager/ResourceContainer.h>
#include <Utils/ResourceManager/IResource.h>

namespace SR_UTILS_NS {
    ResourceContainer::~ResourceContainer() {
        SRAssert(m_dependencies.empty());

        while (!m_parents.empty()) {
            (*m_parents.begin())->RemoveDependency(this);
        }
    }

    void ResourceContainer::AddDependency(ResourceContainer* pContainer) {
        SR_LOCK_GUARD

        if (auto&& pResource = dynamic_cast<IResource*>(pContainer)) {
            pResource->AddUsePoint();
        }

        m_dependencies.insert(pContainer);
        pContainer->m_parents.insert(this);
    }

    void ResourceContainer::RemoveDependency(ResourceContainer* pContainer) {
        SR_LOCK_GUARD

        if (!SRVerifyFalse(m_dependencies.count(pContainer) == 0)) {
            return;
        }

        if (!SRVerifyFalse(pContainer->m_parents.count(this) == 0)) {
            return;
        }

        m_dependencies.erase(pContainer);
        pContainer->m_parents.erase(this);

        if (auto&& pResource = dynamic_cast<IResource*>(pContainer)) {
            pResource->RemoveUsePoint();
        }
    }

    void ResourceContainer::UpdateResources(int32_t depth) {
        SR_LOCK_GUARD

        /// вверх по иерархии
        if (depth == 0 || depth > 0) {
            for (auto &&pResource : m_parents) {
                pResource->OnResourceUpdated(this, depth + 1);
            }
        }

        /// вниз по иерархии
        if (depth == 0 || depth < 0) {
            for (auto &&pResource : m_dependencies) {
                pResource->OnResourceUpdated(this, depth - 1);
            }
        }
    }

    void ResourceContainer::OnResourceUpdated(ResourceContainer* pContainer, int32_t depth) {
        SRAssert(depth != 0);

        if (depth > 0) {
            UpdateResources(depth + 1);
        }
        else {
            UpdateResources(depth - 1);
        }
    }
}