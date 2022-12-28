//
// Created by Nikita on 17.11.2020.
//

#include <Utils/ResourceManager/IResource.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_UTILS_NS {
    IResource::IResource(uint64_t hashName)
        : m_resourceHashName(hashName)
        , m_lifetime(ResourceManager::ResourceLifeTime)
    { }

    IResource::IResource(uint64_t hashName, bool autoRemove)
        : m_resourceHashName(hashName)
        , m_lifetime(ResourceManager::ResourceLifeTime)
        , m_autoRemove(autoRemove)
    { }

    IResource::~IResource() {
        SRAssert(m_dependencies.empty());

        while (!m_parents.empty()) {
            (*m_parents.begin())->RemoveDependency(this);
        }
    }

    bool IResource::Reload() {
        SR_LOCK_GUARD

        SR_LOG("IResource::Reload() : reloading \"" + std::string(GetResourceId()) + "\" resource...");

        m_loadState = LoadState::Reloading;

        Unload();

        if (!Load()) {
            m_loadState = LoadState::Error;
            return false;
        }

        m_loadState = LoadState::Loaded;

        UpdateResources();
        OnReloadDone();

        return true;
    }

    bool IResource::ForceDestroy() {
        if (m_force || IsDestroyed()) {
            SR_ERROR("IResource::ForceDestroy() : resource is already destroyed!");
            return false;
        }

        m_force = true;

        return Destroy();
    }

    std::string_view IResource::GetResourceName() const {
        return ResourceManager::Instance().GetTypeName(m_resourceHashName);
    }

    void IResource::SetId(const std::string &id, bool autoRegister) {
        SRAssert2(!id.empty(), "Invalid id!");

        if (m_resourceId == "NoID") {
            m_resourceId = id;

            if (autoRegister) {
                ResourceManager::Instance().RegisterResource(this);
            }
        }
        else {
            SRHalt("Double set resource id!");
        }
    }

    void IResource::AddUsePoint() {
        SR_LOG(std::to_string(m_resourceHashName) + ": m_countUses: " + std::to_string(m_countUses));
        SRAssert(m_countUses <= 65535);
        if (m_isRegistered && m_countUses == 0 && m_isDestroyed) {
            SRHalt("IResource::AddUsePoint() : potential multi threading error!");
        }

        ++m_countUses;
    }

    IResource *IResource::CopyResource(IResource *destination) const {
        destination->m_autoRemove = m_autoRemove;
        destination->m_lifetime = m_lifetime;
        destination->m_loadState.store(m_loadState);
        destination->SetId(m_resourceId);
        destination->SetReadOnly(m_readOnly);

        return destination;
    }

    bool IResource::Destroy() {
        ResourceManager::Instance().Destroy(this);

        SRAssert(!IsDestroyed());
        m_isDestroyed = true;
        return true;
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
        auto&& path = Path(GetResourcePath());

        if (!path.IsAbs()) {
            path = GetAssociatedPath().Concat(path);
        }

        if (path.Exists(Path::Type::File)) {
            if (auto&& hash = path.GetFileHash(); hash != SR_UINT64_MAX) {
                return hash;
            }
        }

        SRAssert2Once(false, "Failed to get resource hash! \n\tResource id: " + std::string(GetResourceId()) +
            "\n\tResource path: " + path.ToString());

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

        if (!SRVerifyFalse(m_dependencies.count(pResource) == 0)) {
            return;
        }

        if (!SRVerifyFalse(pResource->m_parents.count(this) == 0)) {
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