//
// Created by Nikita on 16.11.2020.
//

#ifndef GAMEENGINE_IRESOURCE_H
#define GAMEENGINE_IRESOURCE_H

#include <Utils/Debug.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Common/NonCopyable.h>

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
        explicit IResource(const char* name);
        IResource(const char* name, bool autoRemove);
        ~IResource() override;

    public:
        SR_NODISCARD virtual uint64_t GetFileHash() const;
        SR_NODISCARD bool IsRegistered() const noexcept { return m_isRegistered; }
        SR_NODISCARD bool IsLoaded() const noexcept { return m_loadState == LoadState::Loaded; }
        SR_NODISCARD bool IsReadOnly() const { return m_readOnly; }
        SR_NODISCARD bool IsDestroyed() const { return m_isDestroyed; }
        SR_NODISCARD bool IsForce() const { return m_force; }
        SR_NODISCARD bool IsAlive() const { return m_lifetime > 0; }
        SR_NODISCARD bool IsEnabledAutoRemove() const { return m_autoRemove; }
        SR_NODISCARD uint32_t GetCountUses() const { return m_countUses; }
        SR_NODISCARD float_t GetLifetime() const { return m_lifetime; }
        SR_NODISCARD const char *GetResourceName() const { return m_resourceName; }
        SR_NODISCARD std::string GetResourceId() const { return m_resourceId; }
        SR_NODISCARD virtual Path GetResourcePath() const { return m_resourceId; }
        SR_NODISCARD virtual uint64_t GetResourceHash() const { return m_resourceHash; }
        SR_NODISCARD virtual Path GetAssociatedPath() const { return Path(); }

        SR_NODISCARD virtual IResource* Copy(IResource* destination) const;

        /** Add one point to count uses current resource */
        void AddUsePoint() { ++m_countUses; }

        /** Remove one point from count uses current resource */
        virtual RemoveUPResult RemoveUsePoint() {
            if (m_countUses == 0) {
                SRHalt("Count use points is zero!");
                return RemoveUPResult::Error;
            }

            --m_countUses;

            if (m_countUses == 0 && m_autoRemove && !IsDestroyed()) {
                if (IsRegistered()) {
                    Destroy();
                    return RemoveUPResult::Destroy;
                }
                else {
                    /// так и не зарегистрировали ресурс
                    delete this;
                    return RemoveUPResult::Delete;
                }
            }

            return RemoveUPResult::Success;
        }

        virtual void OnResourceRegistered() {
            SRAssert2(!IsRegistered(), "Resource already are registered!");
            m_isRegistered = true;
        }

        virtual bool Reload() { return false; }

        virtual bool Unload() {
            if (m_loadState == LoadState::Unknown ||
                m_loadState == LoadState::Loaded ||
                m_loadState == LoadState::Reloading
            ) {
                m_loadState = LoadState::Unloaded;
                return true;
            }

            return false;
        }

        virtual bool Load() {
            if (m_loadState == LoadState::Unknown || m_loadState == LoadState::Unloaded) {
                m_loadState = LoadState::Loaded;
                return true;
            }
            return false;
        }

        void AddDependency(IResource* pResource);
        void RemoveDependency(IResource* pResource);

        /** Call only once | Register resource to destroy in resource manager */
        virtual bool Destroy();
        bool ForceDestroy();
        bool Kill();
        void SetReadOnly(bool value) { m_readOnly = value; }
        void SetId(const std::string& id, bool autoRegister = true);
        void SetAutoRemoveEnabled(bool enabled) { m_autoRemove = enabled; }
        void SetResourceHash(uint64_t hash);

    protected:
        void UpdateResources(int32_t depth = 0);
        virtual void OnResourceUpdated(IResource* pResource, int32_t depth);

    protected:
        /** \brief This is resource name. \example Mesh, Texture, Audio... */
        const char *m_resourceName = "Unnamed";

        std::atomic<LoadState> m_loadState = LoadState::Unknown;

        std::atomic<uint64_t> m_countUses = 0;

        mutable std::recursive_mutex m_mutex;

    private:
        float_t m_lifetime = 0;
        uint64_t m_resourceHash = 0;

        /// Принудительно уничтожить ресурс
        std::atomic<bool> m_force = false;
        std::atomic<bool> m_readOnly = false;
        std::atomic<bool> m_isDestroyed = false;
        std::atomic<bool> m_isRegistered = false;
        /// Автоматическое уничтожение ресурса по истечению use-point'ов
        std::atomic<bool> m_autoRemove = false;

        std::string m_resourceId = "NoID";

        std::unordered_set<IResource*> m_parents;
        std::unordered_set<IResource*> m_dependencies;

    };
}

#endif //GAMEENGINE_IRESOURCE_H
