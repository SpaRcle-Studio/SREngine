//
// Created by Monika on 22.12.2022.
//

#include <Utils/World/SceneLogic.h>

#include <Utils/World/SceneDefaultLogic.h>
#include <Utils/World/SceneCubeChunkLogic.h>
#include <Utils/World/ScenePrefabLogic.h>

namespace SR_WORLD_NS {
    SceneLogic::SceneLogic(const SceneLogic::ScenePtr &scene)
        : SR_HTYPES_NS::SafePtr<SceneLogic>(this)
        , m_scene(scene)
    { }

    SceneLogic::Ptr SceneLogic::CreateByExt(const SceneLogic::ScenePtr &scene, const std::string &ext) {
        if (ext == "scene") {
            return (new SceneCubeChunkLogic(scene))->GetThis();
        }

        if (ext == SR_UTILS_NS::Prefab::EXTENSION) {
            return (new ScenePrefabLogic(scene))->GetThis();
        }

        SRHalt("SceneLogic::CreateByExt() : unknown extension! Create default...\n\tExtension: " + ext);

        return (new SceneDefaultLogic(scene))->GetThis();
    }
}
