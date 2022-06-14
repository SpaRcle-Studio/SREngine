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
        enum class LoadState {
            Unknown, Loaded, Reloading, Loading, Unloading, Unloaded
        };

    protected:
        explicit IResource(const char* name);
        IResource(const char* name, bool autoRemove);
        ~IResource() override;

    public:
        SR_NODISCARD virtual uint64_t GetFileHash() const;
        SR_NODISCARD virtual bool IsValid() const;
        SR_NODISCARD bool IsLoaded() const { return m_loadState == LoadState::Loaded; }
        SR_NODISCARD bool IsReadOnly() const { return m_readOnly; }
        SR_NODISCARD bool IsDestroyed() const { return m_isDestroyed; }
        SR_NODISCARD bool IsForce() const { return m_force; }
        SR_NODISCARD bool IsAlive() const { return m_lifetime > 0; }
        SR_NODISCARD bool IsEnabledAutoRemove() const { return m_autoRemove; }
        SR_NODISCARD uint32_t GetCountUses() const { return m_countUses; }
        SR_NODISCARD float_t GetLifetime() const { return m_lifetime; }
        SR_NODISCARD const char *GetResourceName() const { return m_resourceName; }
        SR_NODISCARD std::string GetResourceId() const { return m_resourceId; }
        SR_NODISCARD virtual std::string GetResourcePath() const { return m_resourceId; }
        SR_NODISCARD virtual uint64_t GetResourceHash() const { return m_resourceHash; }
        SR_NODISCARD virtual Path GetAssociatedPath() const { return Path(); }

        SR_NODISCARD virtual IResource* Copy(IResource* destination) const;

        /** Add one point to count uses current resource */
        void AddUsePoint() { ++m_countUses; }

        /** Remove one point from count uses current resource */
        void RemoveUsePoint() {
            SRAssert2(m_countUses > 0, "count use points is zero!");
            --m_countUses;

            if (m_countUses == 0 && m_autoRemove && !IsDestroyed())
                Destroy();
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
            SRAssert2(IsValid(), "Invalid resource!");
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

        mutable std::recursive_mutex m_mutex;

    private:
        float_t m_lifetime = 0;
        uint64_t m_resourceHash = 0;

        std::atomic<bool> m_force = false;
        std::atomic<bool> m_readOnly = false;
        std::atomic<bool> m_isDestroyed = false;
        std::atomic<bool> m_autoRemove = false;

        std::string m_resourceId = "NoID";

        std::unordered_set<IResource*> m_parents;
        std::unordered_set<IResource*> m_dependencies;

        std::atomic<uint64_t> m_countUses = 0;

    };
}

#endif //GAMEENGINE_IRESOURCE_H
