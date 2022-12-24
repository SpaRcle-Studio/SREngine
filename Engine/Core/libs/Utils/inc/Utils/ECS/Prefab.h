//
// Created by Monika on 26.11.2022.
//

#ifndef SRENGINE_PREFAB_H
#define SRENGINE_PREFAB_H

#include <Utils/ResourceManager/IResource.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_HTYPES_NS {
    class Marshal;
}

namespace SR_UTILS_NS {
    class GameObject;

    class SR_DLL_EXPORT Prefab : public IResource {
    public:
        static constexpr const char* EXTENSION = "prefab";

    private:
        Prefab();
        ~Prefab() override;

    public:
        static Prefab *Load(const SR_UTILS_NS::Path& rawPath);

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        SR_HTYPES_NS::SharedPtr<GameObject> m_data;

    };
}

#endif //SRENGINE_PREFAB_H
