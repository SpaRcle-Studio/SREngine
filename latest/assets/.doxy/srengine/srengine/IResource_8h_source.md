

# File IResource.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**IResource.h**](IResource_8h.md)

[Go to the documentation of this file](IResource_8h.md)


```C++
//
// Created by Nikita on 16.11.2020.
//

#ifndef SR_ENGINE_IRESOURCE_H
#define SR_ENGINE_IRESOURCE_H

#include <Utils/Debug.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/SubscriptionHolder.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Serialization/Serializable.h>
#include <Utils/Resources/ResourceContainer.h>
#include <Utils/Resources/FileWatcher.h>

namespace SR_UTILS_NS {
    class ResourceManager;
    class ResourceType;
    class FileWatcher;

    struct ResourceInfo;

    class SR_COMMON_DLL_API IResource : public ResourceContainer, public SubscriptionHolder, public Serializable {
        SR_CLASS()
        friend class ResourceType;
        using ResourceInfoWeakPtr = std::weak_ptr<ResourceInfo>;
    public:
        SR_INLINE_STATIC const StringAtom RELOAD_BEGIN_EVENT = "ReloadBegin";
        SR_INLINE_STATIC const StringAtom RELOAD_DONE_EVENT = "ReloadDone";

        using Ptr = SR_HTYPES_NS::SharedPtr<IResource>;

        enum class LoadState : uint8_t {
            Unknown, Loaded, Reloading, Loading, Unloading, Unloaded, Error
        };

        enum class RemoveUPResult : uint8_t {
            Delete, Destroy, Success, Error
        };

    public:
        IResource();
        ~IResource() override;

    public:
        SR_NODISCARD virtual Path InitializeResourcePath() const;

        bool Execute(const SR_HTYPES_NS::Function<bool()>& fun) const;

        SR_NODISCARD virtual bool IsFileResource() const noexcept { return true; }

        SR_NODISCARD virtual uint64_t GetFileHash() const;
        SR_NODISCARD virtual bool IsAllowedToRevive() const { return false; }
        SR_NODISCARD virtual Path GetAssociatedPath() const;

        SR_NODISCARD bool IsResourceWillBeDeleted() const;
        SR_NODISCARD bool IsRegistered() const noexcept { return m_isRegistered; }
        SR_NODISCARD bool IsLoaded() const noexcept;
        SR_NODISCARD bool IsDestroyed() const noexcept;
        SR_NODISCARD bool IsForceDestroyed() const { return m_isForceDestroyed; }
        SR_NODISCARD bool IsAlive() const { return m_lifetime > 0; }
        SR_NODISCARD uint16_t GetReloadCount() const noexcept;
        SR_NODISCARD uint64_t GetLifetime() const noexcept { return m_lifetime; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetResourceId() const noexcept;
        SR_NODISCARD LoadState GetResourceLoadState() const { return m_loadState; }
        SR_NODISCARD uint64_t GetResourceHash() const noexcept { return m_resourceHash; }
        SR_NODISCARD ResourceInfoWeakPtr GetResourceInfo() const noexcept { return m_resourceInfo; }
        SR_NODISCARD bool IsResourceFromMemory() const noexcept { return m_isFromMemory; }

        SR_NODISCARD SR_UTILS_NS::Path GetResourcePath() const;
        SR_NODISCARD uint16_t GetCountUses() const noexcept;

        void AddUsePoint();

        virtual RemoveUPResult RemoveUsePoint();

        virtual void CheckResourceUsage();

        virtual void OnResourceRegistered() {
            SRAssert2(!IsRegistered(), "Resource already are registered!");
            m_isRegistered = true;
        }

        virtual void OnReloadDone();

        virtual void DeleteResource();

        virtual void StartWatch();
        virtual void StopWatch();

        virtual bool Reload();
        virtual bool Unload();
        virtual bool Load();

        void UpdateResourceLifeTime();
        void SignalWatch();

        virtual bool Destroy();
        bool ForceDestroy();
        bool Kill();
        void SetResourceHash(uint64_t hash);
        void SetLifetime(int64_t lifeTime) { m_lifetime = lifeTime; }

        void SetId(SR_UTILS_NS::StringAtom id, bool autoRegister = true);

        virtual void ReviveResource();

    protected:
        std::atomic<LoadState> m_loadState = LoadState::Unknown;

        std::atomic<uint16_t> m_countUses = 0;

        std::atomic<bool> m_isFromMemory = false;

        std::list<SR_HTYPES_NS::SharedPtr<FileWatcher>> m_watchers;

        std::list<SR_UTILS_NS::StringAtom> m_debugUseStackTraces;
        std::list<SR_UTILS_NS::StringAtom> m_debugUnUseStackTraces;

    private:
        ResourceInfoWeakPtr m_resourceInfo;

        uint64_t m_resourceHash = 0;

        SR_UTILS_NS::StringAtom m_resourceId;
        SR_UTILS_NS::Path m_resourcePath;

        uint16_t m_reloadCount = 0;

        int64_t m_lifetime = 0;

        std::atomic<bool> m_isForceDestroyed = false;
        std::atomic<bool> m_isDestroyed = false;
        std::atomic<bool> m_isRegistered = false;

        bool m_deleteVerifyFlag = false;

    };
}

#endif //SR_ENGINE_IRESOURCE_H
```


