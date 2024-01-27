//
// Created by Nikita on 17.11.2020.
//

#include <Utils/ResourceManager/IResource.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/ResourceManager/FileWatcher.h>

namespace SR_UTILS_NS {
    IResource::IResource(uint64_t hashName)
        : Super()
        , m_resourceHashName(hashName)
        , m_lifetime(ResourceManager::ResourceLifeTime)
    { }

    IResource::~IResource() {
        SRAssert2(GetCountUses() == 0, "Resource has uses!");
        SRAssert2(m_watchers.empty(), "Watchers has not stopped!");
    }

    bool IResource::Reload() {
        SR_TRACY_ZONE;
        SR_TRACY_TEXT_N("Path", GetResourceId());

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Medium) {
            SR_LOG("IResource::Reload() : reloading \"" + std::string(GetResourceId()) + "\" resource...");
        }

        m_loadState = LoadState::Reloading;

        Unload();

        if (!Load()) {
            m_loadState = LoadState::Error;
            return false;
        }

        m_loadState = LoadState::Loaded;

        UpdateResources();
        OnReloadDone();

        ++m_reloadCount;

        return true;
    }

    bool IResource::ForceDestroy() {
        if (m_isForceDestroyed || IsDestroyed()) {
            SR_ERROR("IResource::ForceDestroy() : resource is already destroyed!");
            return false;
        }

        m_isForceDestroyed = true;

        return Destroy();
    }

    std::string_view IResource::GetResourceName() const {
        return ResourceManager::Instance().GetTypeName(m_resourceHashName);
    }

    void IResource::DeleteResource() {
        StopWatch();
        delete this;
    }

    void IResource::SetId(SR_UTILS_NS::StringAtom id, bool autoRegister) {
        SRAssert2(!id.empty(), "Invalid id!");

        if (m_resourceId.empty()) {
            auto&& resourcesManager = ResourceManager::Instance();

            m_resourceId = id;

            SRAssert(m_resourceHashPath == 0);

            auto&& path = InitializeResourcePath();

            m_resourceHashPath = resourcesManager.RegisterResourcePath(path);

            StartWatch();

            if (autoRegister) {
                resourcesManager.RegisterResource(this);
            }
        }
        else {
            SRHalt("Double set resource id!");
        }
    }

    void IResource::CheckResourceUsage() {
        ResourceManager::Instance().Execute([this]() {
            if (m_countUses == 0 && !IsDestroyed()) {
                if (IsRegistered()) {
                    Destroy();
                    return;
                }
                else {
                    /// так и не зарегистрировали ресурс
                    DeleteResource();
                    return;
                }
            }
        });
    }

    IResource::RemoveUPResult IResource::RemoveUsePoint() {
        RemoveUPResult result;

        /// тут нужно делать синхронно, иначе может произойти deadlock
        /// TODO: а вообще опасное место, нужно переделать
        ResourceManager::Instance().Execute([this, &result]() {
            if (m_countUses == 0) {
                SRHalt("Count use points is zero!");
                result = RemoveUPResult::Error;
                return;
            }

            --m_countUses;

            if (m_countUses == 0 && !IsDestroyed()) {
                if (IsRegistered()) {
                    Destroy();
                    result = RemoveUPResult::Destroy;
                    return;
                }
                else {
                    /// так и не зарегистрировали ресурс
                    delete this;
                    result = RemoveUPResult::Delete;
                    return;
                }
            }

            result = RemoveUPResult::Success;

            if (SR_UTILS_NS::ResourceManager::Instance().IsUsePointStackTraceProfilingEnabled()) {
                m_debugUnUseStackTraces.emplace_back(SR_UTILS_NS::GetStacktrace());
            }
        });

        return result;
    }

    void IResource::AddUsePoint() {
        SRAssert(m_countUses != SR_UINT16_MAX);

        if (m_isRegistered && m_countUses == 0 && m_isDestroyed) {
            SRHalt("IResource::AddUsePoint() : potential multi threading error! Path: " + GetResourcePath().ToStringRef());
        }

        ++m_countUses;

        if (SR_UTILS_NS::ResourceManager::Instance().IsUsePointStackTraceProfilingEnabled()) {
            m_debugUseStackTraces.emplace_back(SR_UTILS_NS::GetStacktrace());
        }
    }

    uint16_t IResource::GetCountUses() const noexcept {
        return m_countUses;
    }

    IResource* IResource::CopyResource(IResource *destination) const {
        /// destination->m_lifetime = m_lifetime;
        destination->m_resourceHashPath = m_resourceHashPath;
        destination->m_loadState.store(m_loadState);

        destination->SetId(m_resourceId, true /** auto register */);

        return destination;
    }

    bool IResource::Destroy() {
        SRAssert(!IsDestroyed());
        m_isDestroyed = true;

        ResourceManager::Instance().Destroy(this);

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
        if (IsResourceFromMemory()) {
            return 0;
        }

        SR_TRACY_ZONE;

        auto&& path = Path(GetResourcePath());

        SR_TRACY_TEXT_N("Path", path.ToStringRef());

        if (!path.IsAbs()) {
            path = GetAssociatedPath().Concat(path);
        }

        if (path.Exists(Path::Type::File)) {
            if (auto&& hash = path.GetFileHash(); hash != SR_UINT64_MAX) {
                return hash;
            }
        }

        SRHaltOnce("IResource::GetFileHash() : failed to get resource hash! \n\tResource id: " + std::string(GetResourceId()) +
            "\n\tResource path: " + path.ToString());

        return 0;
    }

    void IResource::SetResourceHash(uint64_t hash) {
        m_resourceHash = hash;
    }

    const Path& IResource::GetResourcePath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetResourcePath(m_resourceHashPath);
    }

    Path IResource::InitializeResourcePath() const {
        return SR_UTILS_NS::Path(GetResourceId(), false /** fast */);
    }

    Path IResource::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetResPath();
    }

    bool IResource::Unload() {
        if (m_loadState == LoadState::Unknown ||
            m_loadState == LoadState::Loaded ||
            m_loadState == LoadState::Unloading ||
            m_loadState == LoadState::Reloading
        ) {
            m_loadState = LoadState::Unloaded;
            return true;
        }

        for (auto&& pWatch : m_watchers) {
            pWatch->Pause();
        }

        return false;
    }

    bool IResource::Load() {
        if (m_loadState == LoadState::Unknown ||
            m_loadState == LoadState::Unloaded ||
            m_loadState == LoadState::Reloading ||
            m_loadState == LoadState::Loading
        ) {
            m_loadState = LoadState::Loaded;
            return true;
        }

        for (auto&& pWatch : m_watchers) {
            pWatch->Resume();
        }

        return false;
    }

    bool IResource::Execute(const SR_HTYPES_NS::Function<bool()>& fun) const {
        SR_TRACY_ZONE;
        return fun();
    }

    void IResource::ReviveResource() {
        SRAssert(m_isDestroyed && m_isRegistered);

        m_isDestroyed = false;

        UpdateResourceLifeTime();
    }

    void IResource::UpdateResourceLifeTime() {
        m_lifetime = ResourceManager::ResourceLifeTime;
    }

    void IResource::StopWatch() {
        for (auto&& pWatcher : m_watchers) {
            if (!pWatcher) {
                SRHalt("Watcher is nullptr!");
                continue;
            }
            pWatcher->Stop();
        }
        m_watchers.clear();
    }

    void IResource::StartWatch() {
        if (IsResourceFromMemory()) {
            return;
        }

        auto&& resourcesManager = ResourceManager::Instance();

        auto&& path = GetResourcePath();
        auto&& pWatch = resourcesManager.StartWatch(resourcesManager.GetResPath().Concat(path));
        if (!pWatch) {
            return;
        }

        pWatch->SetCallBack([this](auto&& pWatcher) {
            SignalWatch();
        });

        m_watchers.emplace_back(pWatch);
    }

    void IResource::SignalWatch() {
        if (IsDestroyed() || IsForceDestroyed()) {
            return;
        }

        ResourceManager::Instance().ReloadResource(this);
    }

    bool IResource::IsResourceWillBeDeleted() const {
        return GetCountUses() == 1 && !IsDestroyed() && !IsRegistered();
    }
}