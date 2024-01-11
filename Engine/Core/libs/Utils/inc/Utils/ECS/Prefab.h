//
// Created by Monika on 26.11.2022.
//

#ifndef SR_ENGINE_PREFAB_H
#define SR_ENGINE_PREFAB_H

#include <Utils/ResourceManager/IResource.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_HTYPES_NS {
    class Marshal;
}

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_UTILS_NS {
    class GameObject;

    class SR_DLL_EXPORT Prefab : public IResource {
    public:
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<GameObject>;
        using ScenePtr = SR_WORLD_NS::Scene*;

        static constexpr const char* EXTENSION = "prefab";

    private:
        Prefab();
        ~Prefab() override;

    public:
        static Prefab *Load(const SR_UTILS_NS::Path& rawPath);

        SR_NODISCARD GameObjectPtr Instance(const ScenePtr& scene) const;
        SR_NODISCARD const GameObjectPtr& GetData() const noexcept { return m_data; }

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        GameObjectPtr m_data;

    };
}

#endif //SR_ENGINE_PREFAB_H
