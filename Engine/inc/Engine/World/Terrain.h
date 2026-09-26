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
    class Terrain;

    /// @abstract
    class ITerrainChunkData : public SR_HTYPES_NS::SharedPtr<ITerrainChunkData>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunkData>;
        SR_CLASS()
    public:
        ITerrainChunkData();

    };

    /// @abstract
    class ITerrainChunk : public SR_HTYPES_NS::SharedPtr<ITerrainChunk>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunk>;
        SR_CLASS()
    public:
        enum class Status : uint8_t {
            Pool, Created, Loaded
        };

    public:
        ITerrainChunk();

    public:
        void SetData(const ITerrainChunkData::Ptr& data) { m_data = data; }
        SR_NODISCARD const ITerrainChunkData::Ptr& GetData() const { return m_data; }
        void SetStatus(Status status) { m_status = status; }
        SR_NODISCARD Status GetStatus() const { return m_status; }
        SR_NODISCARD const SR_UTILS_NS::SceneObject::Ptr& GetObject() const { return m_object; }

        virtual void Activate(SR_UTILS_NS::SceneObject& pool, const SR_UTILS_NS::SceneObject& proto, SR_MATH_NS::FVector3 position);
        void Deactivate();

    protected:
        Status m_status = Status::Pool;
        ITerrainChunkData::Ptr m_data;
        SR_UTILS_NS::SceneObject::Ptr m_object;

    };

    /// @abstract
    class ITerrainChunkDataGenerator : public SR_HTYPES_NS::SharedPtr<ITerrainChunkDataGenerator>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunkDataGenerator>;
        SR_CLASS()
    public:
        ITerrainChunkDataGenerator();

    public:
        virtual void GenerateChunkData(Terrain& terrain, ITerrainChunk& chunk) { }

    };

    /// @abstract
    class ITerrainChunkGenerator : public SR_HTYPES_NS::SharedPtr<ITerrainChunkGenerator>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunkGenerator>;
        SR_CLASS()
    public:
        ITerrainChunkGenerator();

    public:
        virtual void Update(Terrain& terrain, float_t dt) { }
        virtual void LoadNextChunk(SR_HTYPES_NS::Function<void(ITerrainChunk&)> loaderFn) { }

    protected:
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_chunkObjectProto;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_poolObject;

    };

    struct TerrainObserverData {
        SR_MATH_NS::FVector3 position;
    };

    class Terrain : public SR_UTILS_NS::Component {
        using Super = SR_UTILS_NS::Component;
        SR_CLASS()
    public:
        void Update(float_t dt) override;

        SR_NODISCARD TerrainObserverData GetObserver() const;

    private:
        /// @property @tooltip(If not present, will be used main camera of the scene)
        SR_UTILS_NS::EntityRef<SR_GTYPES_NS::Camera> m_camera;
        /// @property @notNull
        ITerrainChunkDataGenerator::Ptr m_chunkDataGenerator;
        /// @property @notNull
        ITerrainChunkGenerator::Ptr m_chunkGenerator;

    };
}

#endif //SR_ENGINE_CORE_WORLD_TERRAIN_H
