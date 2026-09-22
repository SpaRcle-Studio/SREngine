//
// Created by Monika on 27.08.2026.
//

#ifndef SR_ENGINE_CORE_WORLD_TERRAIN_H
#define SR_ENGINE_CORE_WORLD_TERRAIN_H

#include <Engine/stdInclude.h>

#include <Graphics/Types/Camera.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/ECS/EntityRef.h>

namespace SR_CORE_NS {
    /// @abstract
    class ITerrainChunk : public SR_HTYPES_NS::SharedPtr<ITerrainChunk>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunk>;
        SR_CLASS()
    public:
        ITerrainChunk();

    };

    /// @abstract
    class ITerrainGenerator : public SR_HTYPES_NS::SharedPtr<ITerrainGenerator>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainGenerator>;
        SR_CLASS()
    public:
        ITerrainGenerator();

    };

    class Terrain : public SR_UTILS_NS::Component {
        using Super = SR_UTILS_NS::Component;
        SR_CLASS()
    public:
        void Update(float dt) override;

    private:
        /// @property @tooltip(If not present, will be used main camera of the scene)
        SR_UTILS_NS::EntityRef<SR_GTYPES_NS::Camera> m_camera;
        /// @property @notNull
        ITerrainGenerator::Ptr m_generator;
        /// @property @notNull
        ITerrainChunk::Ptr m_chunkProto;

    };
}

#endif //SR_ENGINE_CORE_WORLD_TERRAIN_H
