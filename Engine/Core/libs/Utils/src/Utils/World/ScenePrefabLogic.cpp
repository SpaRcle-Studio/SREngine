//
// Created by Monika on 24.12.2022.
//

#include <Utils/World/ScenePrefabLogic.h>

namespace SR_WORLD_NS {
    ScenePrefabLogic::ScenePrefabLogic(const SceneLogic::ScenePtr& scene)
        : Super(scene)
    { }

    bool ScenePrefabLogic::Reload() {
        return SceneLogic::Reload();
    }

    void ScenePrefabLogic::Destroy() {
        SceneLogic::Destroy();
    }

    void ScenePrefabLogic::Update(float_t dt) {
        SceneLogic::Update(dt);
    }

    bool ScenePrefabLogic::Save(const Path &path) {
        return SceneLogic::Save(path);
    }
}