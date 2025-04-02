

# File IResource.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Resources**](dir_324d400546bb3f221a744d7d2624d5c6.md) **>** [**IResource.h**](IResource_8h.md)

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
#include <Utils/Resources/ResourceContainer.h>
#include <Utils/Resources/FileWatcher.h>

namespace SR_UTILS_NS {
    class ResourceManager;
    class ResourceType;
    class FileWatcher;

    struct ResourceInfo;

    class SR_DLL_EXPORT IResource : public ResourceContainer, public SubscriptionHolder {
        friend class ResourceType;
        using Super = ResourceContainer;
        using ResourceInfoWeakPtr = std::weak_ptr<ResourceInfo>;
    public:
        SR_INLINE_STATIC const StringAtom RELOAD_BEGIN_EVENT = "ReloadBegin";
        SR_INLINE_STATIC const StringAtom RELOAD_DONE_EVENT = "ReloadDone";

        using Ptr = IResource*;

        enum class LoadState : uint8_t {
            Unknown, Loaded, Reloading, Loading, Unloading, Unloaded, Error
        };

        enum class RemoveUPResult : uint8_t {
            Delete, Destroy, Success, Error
        };

    protected:
        explicit IResource(uint64_t hashName);
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
        SR_NODISCARD bool IsLoaded() const noexcept { return m_loadState == LoadState::Loaded; }
        SR_NODISCARD bool IsDestroyed() const noexcept { return m_isDestroyed; }
        SR_NODISCARD bool IsForceDestroyed() const { return m_isForceDestroyed; }
        SR_NODISCARD bool IsAlive() const { return m_lifetime > 0; }
        SR_NODISCARD uint16_t GetReloadCount() const noexcept { return m_reloadCount; }
        SR_NODISCARD uint64_t GetLifetime() const noexcept { return m_lifetime; }
        SR_NODISCARD uint64_t GetResourceHashName() const noexcept { return m_resourceHashName; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetResourceId() const noexcept { return m_resourceId; }
        SR_NODISCARD LoadState GetResourceLoadState() const { return m_loadState; }
        SR_NODISCARD uint64_t GetResourceHash() const noexcept { return m_resourceHash; }
        SR_NODISCARD ResourceInfoWeakPtr GetResourceInfo() const noexcept { return m_resourceInfo; }
        SR_NODISCARD bool IsResourceFromMemory() const noexcept { return m_isFromMemory; }

        SR_NODISCARD std::string_view GetResourceName() const;
        SR_NODISCARD StringAtom GetResourcePath() const;
        SR_NODISCARD uint16_t GetCountUses() const noexcept;

        SR_NODISCARD virtual IResource* CopyResource(IResource* destination) const;

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

        template<typename T> bool IsResourceType() const noexcept {
            return m_resourceHashName == SR_COMPILE_TIME_CRC32_TYPE_NAME(T);
        }

    protected:
        const uint64_t m_resourceHashName = 0;

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
        SR_UTILS_NS::StringAtom m_resourcePath;

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


