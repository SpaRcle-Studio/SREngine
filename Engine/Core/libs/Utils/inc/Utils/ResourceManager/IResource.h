//
// Created by Nikita on 16.11.2020.
//

#ifndef GAMEENGINE_IRESOURCE_H
#define GAMEENGINE_IRESOURCE_H

#include <Utils/Debug.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/ResourceManager/ResourceContainer.h>
#include <Utils/ResourceManager/FileWatcher.h>

namespace SR_UTILS_NS {
    class ResourceManager;
    class ResourceType;
    class FileWatcher;

    struct ResourceInfo;

    class SR_DLL_EXPORT IResource : public ResourceContainer {
        friend class ResourceType;
        using Super = ResourceContainer;
        using ResourceInfoWeakPtr = std::weak_ptr<ResourceInfo>;
    public:
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

        /// является ли ресурс файловым
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
        SR_NODISCARD uint64_t GetResourceHashId() const noexcept { return m_resourceHashId; }
        SR_NODISCARD LoadState GetResourceLoadState() const { return m_loadState; }
        SR_NODISCARD uint64_t GetResourceHashPath() const noexcept { return m_resourceHashPath; }
        SR_NODISCARD uint64_t GetResourceHash() const noexcept { return m_resourceHash; }
        SR_NODISCARD ResourceInfoWeakPtr GetResourceInfo() const noexcept { return m_resourceInfo; }
        SR_NODISCARD bool IsResourceFromMemory() const noexcept { return m_isFromMemory; }

        SR_NODISCARD std::string_view GetResourceName() const;
        SR_NODISCARD const Path& GetResourcePath() const;
        SR_NODISCARD const std::string& GetResourceId() const;
        SR_NODISCARD uint16_t GetCountUses() const noexcept;

        SR_NODISCARD virtual IResource* CopyResource(IResource* destination) const;

        /** Add one point to count uses current resource */
        void AddUsePoint();

        /** Remove one point from count uses current resource */
        virtual RemoveUPResult RemoveUsePoint();

        virtual void CheckResourceUsage();

        virtual void OnResourceRegistered() {
            SRAssert2(!IsRegistered(), "Resource already are registered!");
            m_isRegistered = true;
        }

        virtual void OnReloadDone() { }

        /** Вызывается только из ResourceManager и IResource, удаляет экземпляр класса,
         * или не удаляет, но это уже не его проблема, а того, как он переопределен.
         * Задача данного метода - сделать финальное оповещение что ресурс не нужен и не отслеживается более. */
        virtual void DeleteResource();

        virtual void StartWatch();
        virtual void StopWatch();

        virtual bool Reload();
        virtual bool Unload();
        virtual bool Load();

        void UpdateResourceLifeTime();
        void SignalWatch();

        /** Call only once | Register resource to destroy in resource manager */
        virtual bool Destroy();
        bool ForceDestroy();
        bool Kill();
        void SetResourceHash(uint64_t hash);
        void SetLifetime(int64_t lifeTime) { m_lifetime = lifeTime; }

        void SetId(const std::string& id, bool autoRegister = true);
        void SetId(uint64_t hashId, bool autoRegister = true);

        virtual void ReviveResource();

        template<typename T> bool IsResourceType() const noexcept {
            return m_resourceHashName == SR_COMPILE_TIME_CRC32_TYPE_NAME(T);
        }

    protected:
        const uint64_t m_resourceHashName = 0;

        std::atomic<LoadState> m_loadState = LoadState::Unknown;

        /// не рекомендуется вручную обращаться к счетчику при наследовании
        std::atomic<uint16_t> m_countUses = 0;

        std::atomic<bool> m_isFromMemory = false;

        std::list<SR_HTYPES_NS::SharedPtr<FileWatcher>> m_watchers;

    private:
        ResourceInfoWeakPtr m_resourceInfo;

        uint64_t m_resourceHashId = 0;
        uint64_t m_resourceHash = 0;
        uint64_t m_resourceHashPath = 0;

        uint16_t m_reloadCount = 0;

        int64_t m_lifetime = 0;

        std::atomic<bool> m_isForceDestroyed = false;
        std::atomic<bool> m_isDestroyed = false;
        std::atomic<bool> m_isRegistered = false;

    };
}

#endif //GAMEENGINE_IRESOURCE_H
