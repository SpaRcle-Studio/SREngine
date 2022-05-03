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
}