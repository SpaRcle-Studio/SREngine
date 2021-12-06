//
// Created by Nikita on 16.11.2020.
//

#ifndef GAMEENGINE_IRESOURCE_H
#define GAMEENGINE_IRESOURCE_H

#include <string>
#include <mutex>
#include <math.h>
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
        explicit IResource(const char *res_name);

        virtual ~IResource() = default;

    private:
        float_t m_lifetime = 0;
        std::atomic<bool> m_force = false;

    protected:
        bool m_autoRemove = false;

        std::atomic<bool> m_isDestroy = false;
        /* Count uses current resource now */
        std::atomic<uint64_t> m_countUses = 0;

        /** \brief This is resource name. \example Mesh, Texture, Audio... */
        const char *m_resource_name = "Unnamed";
        std::string m_resource_id = "NoID";

    public:
        [[nodiscard]] bool IsEnabledAutoRemove() const { return this->m_autoRemove; }

    public:
        /* Call only once | Register resource to destroy in resource manager */
        virtual bool Destroy() = 0;
        bool ForceDestroy();

        [[nodiscard]] bool IsDestroy() const { return m_isDestroy; }
        [[nodiscard]] bool IsForce() const { return m_force; }
        [[nodiscard]] bool IsAlive() const { return m_lifetime > 0; }

        /* Add one point to count uses current resource */
        void AddUsePoint() { m_countUses++; }

        /* Remove one point from count uses current resource */
        void RemoveUsePoint() {
            if (m_countUses == 0)
                Debug::Error("IResource::RemoveUsePoint() : count use points is zero!");
            m_countUses--;
        }

        [[nodiscard]] uint32_t GetCountUses() const { return this->m_countUses; }

        [[nodiscard]] const char *GetResourceName() const { return this->m_resource_name; }

        [[nodiscard]] std::string GetResourceID() const { return this->m_resource_id; }
    };
}

#endif //GAMEENGINE_IRESOURCE_H
