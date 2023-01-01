//
// Created by Monika on 23.12.2022.
//

#include <Utils/World/SceneDefaultLogic.h>

namespace SR_WORLD_NS {
    SceneDefaultLogic::SceneDefaultLogic(const SceneLogic::ScenePtr& scene)
        : Super(scene)
    { }

    bool SceneDefaultLogic::Reload() {
        return SceneLogic::Reload();
    }

    void SceneDefaultLogic::Destroy() {
        SceneLogic::Destroy();
    }

    void SceneDefaultLogic::Update(float_t dt) {
        SceneLogic::Update(dt);
    }

    bool SceneDefaultLogic::Save(const Path &path) {
        return SceneLogic::Save(path);
    }
}