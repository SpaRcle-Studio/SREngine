//
// Created by Monika on 24.12.2022.
//

#ifndef SR_ENGINE_SCENEPREFABLOGIC_H
#define SR_ENGINE_SCENEPREFABLOGIC_H

#include <Utils/World/SceneLogic.h>

namespace SR_WORLD_NS {
    class ScenePrefabLogic : public SceneLogic {
        using Super = SceneLogic;
    public:
        explicit ScenePrefabLogic(const ScenePtr& scene);
        ~ScenePrefabLogic() override = default;

    public:
        bool Save(const Path& path) override;
        bool Load(const Path& path) override;

        bool Reload() override;
        void Destroy() override;
        void Update(float_t dt) override;

    };
}

#endif //SR_ENGINE_SCENEPREFABLOGIC_H
