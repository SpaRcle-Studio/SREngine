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

namespace SR_UTILS_NS {
    class ResourceManager;

    class SR_DLL_EXPORT IResource : public NonCopyable {
        friend class ResourceManager;

    public:
        enum class LoadState : uint8_t {
            Unknown, Loaded, Reloading, Loading, Unloading, Unloaded, Error
        };

        enum class RemoveUPResult : uint8_t {
            Delete, Destroy, Success, Error
        };

    protected:
        explicit IResource(uint64_t hashName);
        IResource(uint64_t hashName, bool autoRemove);
        ~IResource() override;

    public:
        SR_NODISCARD virtual Path InitializeResourcePath() const;

        bool TryExecute(const SR_HTYPES_NS::Function<bool()>& fun, bool def) const;
        bool Execute(const SR_HTYPES_NS::Function<bool()>& fun) const;

        SR_NODISCARD virtual uint64_t GetFileHash() const;
        SR_NODISCARD bool IsRegistered() const noexcept { return m_isRegistered; }
        SR_NODISCARD bool IsLoaded() const noexcept { return m_loadState == LoadState::Loaded; }
        SR_NODISCARD bool IsReadOnly() const { return m_readOnly; }
        SR_NODISCARD bool IsDestroyed() const noexcept;
        SR_NODISCARD virtual bool IsAllowRevive() const { return false; }
        SR_NODISCARD bool IsForce() const { return m_force; }
        SR_NODISCARD bool IsAlive() const { return m_lifetime > 0; }
        SR_NODISCARD bool IsEnabledAutoRemove() const { return m_autoRemove; }
        SR_NODISCARD uint16_t GetCountUses() const noexcept;
        SR_NODISCARD float_t GetLifetime() const noexcept { return m_lifetime; }
        SR_NODISCARD std::string_view GetResourceName() const;
        SR_NODISCARD uint64_t GetResourceHashName() const noexcept { return m_resourceHashName; }
        SR_NODISCARD const std::string& GetResourceId() const;
        SR_NODISCARD uint64_t GetResourceHashId() const noexcept { return m_resourceHashId; }
        SR_NODISCARD LoadState GetResourceLoadState() const { return m_loadState; }
        SR_NODISCARD const Path& GetResourcePath() const;
        SR_NODISCARD uint64_t GetResourceHashPath() const noexcept { return m_resourceHashPath; }
        SR_NODISCARD uint64_t GetResourceHash() const noexcept { return m_resourceHash; }
        SR_NODISCARD virtual Path GetAssociatedPath() const;

        SR_NODISCARD const std::unordered_set<IResource*>& GetResourceParents() const { return m_parents; }

        SR_NODISCARD virtual IResource* CopyResource(IResource* destination) const;

        /** Add one point to count uses current resource */
        void AddUsePoint();

        /** Remove one point from count uses current resource */
        virtual RemoveUPResult RemoveUsePoint();

        virtual void OnResourceRegistered() {
            SRAssert2(!IsRegistered(), "Resource already are registered!");
            m_isRegistered = true;
        }

        virtual void OnReloadDone() { }

        virtual bool Reload();

        virtual bool Unload() {
            if (m_loadState == LoadState::Unknown ||
                m_loadState == LoadState::Loaded ||
                m_loadState == LoadState::Unloading ||
                m_loadState == LoadState::Reloading
            ) {
                m_loadState = LoadState::Unloaded;
                return true;
            }

            return false;
        }

        virtual bool Load() {
            if (m_loadState == LoadState::Unknown ||
                m_loadState == LoadState::Unloaded ||
                m_loadState == LoadState::Reloading ||
                m_loadState == LoadState::Loading
            ) {
                m_loadState = LoadState::Loaded;
                return true;
            }
            return false;
        }

        void UpdateResourceLifeTime();

        void AddDependency(IResource* pResource);
        void RemoveDependency(IResource* pResource);

        /** Call only once | Register resource to destroy in resource manager */
        virtual bool Destroy();
        bool ForceDestroy();
        bool Kill();
        void SetReadOnly(bool value) { m_readOnly = value; }
        void SetAutoRemoveEnabled(bool enabled) { m_autoRemove = enabled; }
        void SetResourceHash(uint64_t hash);

        void SetId(const std::string& id, bool autoRegister = true);
        void SetId(uint64_t hashId, bool autoRegister = true);

        virtual void ReviveResource();

    protected:
        void UpdateResources(int32_t depth = 0);
        virtual void OnResourceUpdated(IResource* pResource, int32_t depth);

    protected:
        const uint64_t m_resourceHashName = 0;

        std::atomic<LoadState> m_loadState = LoadState::Unknown;

        mutable std::recursive_mutex m_mutex;

        /// не рекомендуется вручную обращаться к счетчику при наследовании
        std::atomic<uint16_t> m_countUses = 0;

    private:
        uint64_t m_resourceHashId = 0;
        uint64_t m_resourceHash = 0;
        uint64_t m_resourceHashPath = 0;

        float_t m_lifetime = 0;

        /// Принудительно уничтожить ресурс
        std::atomic<bool> m_force = false;
        std::atomic<bool> m_readOnly = false;
        std::atomic<bool> m_isDestroyed = false;
        std::atomic<bool> m_isRegistered = false;

        /// Автоматическое уничтожение ресурса по истечению use-point'ов
        /// \warning ReadOnly
        bool m_autoRemove = false;

        std::unordered_set<IResource*> m_parents;
        std::unordered_set<IResource*> m_dependencies;

    };
}

#endif //GAMEENGINE_IRESOURCE_H
