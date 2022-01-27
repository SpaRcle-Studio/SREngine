//
// Created by Nikita on 16.11.2020.
//

#ifndef GAMEENGINE_IRESOURCE_H
#define GAMEENGINE_IRESOURCE_H

#include <string>
#include <mutex>
#include <cmath>
#include <atomic>
#include <Debug.h>

namespace Framework {
    class API;
}

namespace Framework::Helper {
    class ResourceManager;

    class IResource {
        friend class ResourceManager;
        friend class ::Framework::API;

    protected:
        explicit IResource(const char* name);

        virtual ~IResource() = default;

    public:
        [[nodiscard]] bool IsValid() const;
        [[nodiscard]] bool IsLoaded() const { return m_loaded; }
        [[nodiscard]] bool IsReadOnly() const { return m_readOnly; }
        [[nodiscard]] bool IsDestroy() const { return m_isDestroy; }
        [[nodiscard]] bool IsForce() const { return m_force; }
        [[nodiscard]] bool IsAlive() const { return m_lifetime > 0; }
        [[nodiscard]] bool IsEnabledAutoRemove() const { return this->m_autoRemove; }
        [[nodiscard]] uint32_t GetCountUses() const { return this->m_countUses; }
        [[nodiscard]] const char *GetResourceName() const { return this->m_resourceName; }
        [[nodiscard]] std::string GetResourceId() const { return this->m_resourceId; }

        [[nodiscard]] virtual IResource* Copy(IResource* destination) const;

        /** Add one point to count uses current resource */
        void AddUsePoint() { m_countUses++; }

        /** Remove one point from count uses current resource */
        void RemoveUsePoint() {
            SRAssert2(m_countUses > 0, "count use points is zero!");
            m_countUses--;
        }

        virtual bool Unload() {
            if (m_loaded) {
                m_loaded = false;
                return true;
            }
            return false;
        }

        virtual bool Load() {
            if (!m_loaded) {
                m_loaded = true;
                return true;
            }
            return false;
        }

        /** Call only once | Register resource to destroy in resource manager */
        virtual bool Destroy();
        bool ForceDestroy();
        void SetReadOnly(bool value) { m_readOnly = value; }
        void SetId(const std::string& id);
        void SetAutoRemoveEnabled(bool enabled) { m_autoRemove = enabled; }

    protected:
        /** \brief This is resource name. \example Mesh, Texture, Audio... */
        const char *m_resourceName = "Unnamed";

    private:
        float_t m_lifetime = 0;
        std::atomic<bool> m_force = false;
        std::atomic<bool> m_readOnly = false;
        std::atomic<bool> m_loaded = true;
        std::string m_resourceId = "NoID";
        bool m_autoRemove = false;

        std::atomic<bool> m_isDestroy = false;
        /* Count uses current resource now */
        std::atomic<uint64_t> m_countUses = 0;

    };
}

#endif //GAMEENGINE_IRESOURCE_H
