//
// Created by Nikita on 17.11.2020.
//

#include <ResourceManager/IResource.h>
#include <ResourceManager/ResourceManager.h>

namespace SR_UTILS_NS {
    IResource::IResource(const char *name)
        : IResource(name, false)
    { }

    IResource::IResource(const char *name, bool autoRemove)
        : m_resourceName(name)
        , m_lifetime(ResourceManager::ResourceLifeTime)
        , m_autoRemove(autoRemove)
    { }

    IResource::~IResource() {
        SRAssert(m_dependencies.empty());

        while (!m_parents.empty()) {
            (*m_parents.begin())->RemoveDependency(this);
        }
    }

    bool IResource::ForceDestroy() {
        if (m_force || IsDestroyed()) {
            SR_ERROR("IResource::ForceDestroy() : resource is already destroyed!");
            return false;
        }

        m_force = true;

        return Destroy();
    }

    void IResource::SetId(const std::string &id, bool autoRegister) {
        if (m_resourceId == "NoID") {
            m_resourceId = id;

            if (autoRegister) {
                ResourceManager::Instance().RegisterResource(this);
            }
        }
        else {
            SRAssert2(false, "Double set resource id!");
        }
    }

    IResource *IResource::Copy(IResource *destination) const {
        destination->m_autoRemove.store(m_autoRemove);
        destination->m_lifetime = m_lifetime;
        destination->m_loadState.store(m_loadState);
        destination->SetId(m_resourceId);
        destination->SetReadOnly(m_readOnly);

        return destination;
    }

    bool IResource::Destroy() {
        Helper::ResourceManager::Instance().Destroy(this);

        SRAssert(!IsDestroyed());
        m_isDestroyed = true;
        return true;
    }

    bool IResource::IsValid() const {
        return m_resourceId != "NoID" && !m_resourceId.empty() && std::string(m_resourceName) != "Unnamed";
    }

    bool IResource::Kill() {
        if (GetCountUses() == 0) {
            if (!IsDestroyed()) {
                Destroy();
            }

            m_lifetime = 0.f;

            return true;
        }

        return false;
    }

    uint64_t IResource::GetFileHash() const {
        auto&& path = GetResourcePath();
        auto&& fullPath = GetAssociatedPath().Concat(path);

        if (fullPath.Exists()) {
            return fullPath.GetFileHash();
        }

        return 0;
    }

    void IResource::SetResourceHash(uint64_t hash) {
        m_resourceHash = hash;
    }

    void IResource::AddDependency(IResource *pResource) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        pResource->AddUsePoint();

        m_dependencies.insert(pResource);
        pResource->m_parents.insert(this);
    }

    void IResource::RemoveDependency(IResource *pResource) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (SRVerifyFalse(m_dependencies.count(pResource) == 1)) {
            return;
        }

        if (SRVerifyFalse(pResource->m_parents.count(this) == 1)) {
            return;
        }

        m_dependencies.erase(pResource);
        pResource->m_parents.erase(this);

        pResource->RemoveUsePoint();
    }

    void IResource::UpdateResources(int32_t depth) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

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

    void IResource::OnResourceUpdated(IResource *pResource, int32_t depth) {
        SRAssert(depth != 0);

        if (depth > 0) {
            UpdateResources(depth + 1);
        }
        else {
            UpdateResources(depth - 1);
        }
    }
}