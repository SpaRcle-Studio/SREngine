//
// Created by Nikita on 16.11.2020.
//

#ifndef GAMEENGINE_IRESOURCE_H
#define GAMEENGINE_IRESOURCE_H

#include <string>
#include <mutex>
// TODO: Make a comments

namespace Framework::Helper {
    class ResourceManager;

    class IResource {
        friend class ResourceManager;
    protected:
        IResource(const char *res_name);
        ~IResource() = default;
    protected:
        /* free resource pointer */
        virtual bool Free() = 0;
    protected:
        volatile bool m_isDestroy = false;
        /* Count uses current resource now */
        volatile unsigned long m_countUses = 0;

        /** \brief This is resource name. \example Mesh, Texture, Audio... */
        const char *m_resource_name = "Unnamed";
        std::string m_resource_id = "NoID";

    public:
        /* Call only once | Register resource to destroy in resource manager */
        virtual bool Destroy() = 0;

        [[nodiscard]] bool IsDestroy() const noexcept { return m_isDestroy; }

        /* Add one point to count uses current resource */
        void AddUsePoint() { m_countUses++; }

        /* Remove one point from count uses current resource */
        void RemoveUsePoint() { m_countUses--; }

        [[nodiscard]] unsigned int GetCountUses() const noexcept { return this->m_countUses; }

        [[nodiscard]] const char *GetResourceName() const noexcept { return this->m_resource_name; }
        [[nodiscard]] std::string GetResourceID() const noexcept { return this->m_resource_id; }
    };
}

#endif //GAMEENGINE_IRESOURCE_H
