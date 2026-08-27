//
// Created by Monika on 27.08.2026.
//

#ifndef SR_ENGINE_CORE_WORLD_TERRAIN_H
#define SR_ENGINE_CORE_WORLD_TERRAIN_H

#include <Engine/stdInclude.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/ECS/EntityRef.h>

namespace SR_CORE_NS {
    class TerrainChunk : public SR_UTILS_NS::NonCopyable {

    };

    class Terrain : public SR_UTILS_NS::Component {
        using Super = SR_UTILS_NS::Component;
        SR_CLASS()
    public:

    private:
        /// @property @tooltip(If not present, will be used main camera of the scene)
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_observer;

    };
}

#endif //SR_ENGINE_CORE_WORLD_TERRAIN_H
