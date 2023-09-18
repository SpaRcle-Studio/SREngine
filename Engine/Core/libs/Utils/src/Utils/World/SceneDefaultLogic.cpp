//
// Created by Monika on 23.12.2022.
//

#include <Utils/World/SceneDefaultLogic.h>

namespace SR_WORLD_NS {
    SceneDefaultLogic::SceneDefaultLogic(const Super::ScenePtr& scene)
        : Super(scene)
    { }

    bool SceneDefaultLogic::Reload() {
        return Super::Reload();
    }

    void SceneDefaultLogic::Destroy() {
        Super::Destroy();
    }

    void SceneDefaultLogic::Update(float_t dt) {
        Super::Update(dt);
    }

    bool SceneDefaultLogic::Save(const Path& path) {
        return Super::Save(path);
    }
}