//
// Created by Monika on 27.08.2026.
//

#ifndef SR_ENGINE_CORE_WORLD_TERRAIN_H
#define SR_ENGINE_CORE_WORLD_TERRAIN_H

#include <Engine/stdInclude.h>
#include <Engine/World/TerrainGrass.h>

#include <Graphics/Types/Camera.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/ECS/EntityRef.h>
#include <Utils/Math/AABB.h>
#include <Utils/Types/FlatHashMap.h>
#include <Utils/Types/RawPointerHolder.h>

namespace SR_CORE_NS {
    class Terrain;
    class TerrainObserverData;
    class ITerrainChunk;

    /// @abstract
    class ITerrainChunkData : public SR_HTYPES_NS::SharedPtr<ITerrainChunkData>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunkData>;
        SR_CLASS()
    public:
        ITerrainChunkData();

    public:
        virtual void Deactivate() { }
        void SetChunk(ITerrainChunk* chunk) { m_chunk = chunk; }
        virtual void SwitchPhysics(bool enable) { }
        SR_NODISCARD virtual bool IsPhysicsEnabled() const { return false; }
        /// Меш чанка уже попал в рендер. Пока нет - заменяемый чанк должен оставаться видимым, иначе моргание
        SR_NODISCARD virtual bool IsRenderReady() const { return true; }

    protected:
        ITerrainChunk* m_chunk = nullptr;

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
        void SetObject(const SR_UTILS_NS::SceneObject::Ptr& pObject) { m_object = pObject; }
        /// Система травы, которой чанк сообщит о своей деактивации
        void SetGrass(TerrainGrass* pGrass) noexcept { m_grass = pGrass; }
        /// Трава чанка сгенерирована (или её нет). Пока нет - заменяемый чанк держит свою траву, иначе место останется голым
        SR_NODISCARD bool IsGrassReady() const;

        SR_NODISCARD virtual float_t GetDistanceTo(const ITerrainChunk& other) const { return 0.f; }
        void Deactivate();

    protected:
        Status m_status = Status::Pool;
        ITerrainChunkData::Ptr m_data;
        SR_UTILS_NS::SceneObject::Ptr m_object;
        TerrainGrass::Ptr m_grass;

    };

    /// @abstract
    class ITerrainChunkDataGenerator : public SR_HTYPES_NS::SharedPtr<ITerrainChunkDataGenerator>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunkDataGenerator>;
        SR_CLASS()
    public:
        ITerrainChunkDataGenerator();

    public:
        virtual void GenerateChunkData(Terrain& terrain, ITerrainChunk& chunk, const TerrainObserverData& observer, float_t distance) { }

    };

    /// @abstract
    class ITerrainChunkGenerator : public SR_HTYPES_NS::SharedPtr<ITerrainChunkGenerator>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunkGenerator>;
        SR_CLASS()
    public:
        ITerrainChunkGenerator();

    public:
        virtual void Update(Terrain& terrain, const TerrainObserverData& observer, float_t dt) { }
        virtual void LoadNextChunk(const SR_HTYPES_NS::Function<void(ITerrainChunk&)>& loaderFn) { }

        SR_NODISCARD virtual bool IsCollisionEnabledAt(const ITerrainChunk& chunk) const { return false; }
        /// Перегенерировать чанки, пересекающие область (мировые координаты)
        virtual void InvalidateRegion(const SR_MATH_NS::AABB& bounds) { }
        /// Размер вокселя самого детального уровня в метрах - шаг сетки правок плотности
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetVoxelSize() const { return SR_MATH_NS::FVector3(1.f); }

        /// Объект сцены выдаётся только чанкам с непустой геометрией. Объекты переиспользуются через пул.
        SR_UTILS_NS::SceneObject::Ptr AcquireChunkObject(ITerrainChunk& chunk);
        void ReleaseChunkObject(ITerrainChunk& chunk);

    protected:
        virtual void SetupChunkObject(ITerrainChunk& chunk, SR_UTILS_NS::SceneObject& object) { }

    protected:
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_chunkObjectProto;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_poolObject;
        /// @property @range(0, 4096) @tooltip(Сколько свободных объектов чанков держать в пуле, остальные уничтожаются)
        uint32_t m_maxFreeObjects = 32;

    private:
        SR_UTILS_NS::Vector<SR_UTILS_NS::SceneObject::Ptr> m_freeObjects;

    };

    struct TerrainObserverData {
        SR_MATH_NS::FVector3 position;
        SR_MATH_NS::FVector3 direction = SR_MATH_NS::FVector3(0.f, 0.f, 1.f);
        float_t fovY = 0.f;   /// вертикальный угол обзора в радианах, 0 - камеры нет
        float_t aspect = 0.f; /// ширина / высота
        float_t farPlane = 0.f; /// дальность прорисовки камеры, 0 - камеры нет
    };

    class TerrainLODManager : public SR_UTILS_NS::Serializable {
        using Super = SR_UTILS_NS::Serializable;
        SR_CLASS()
    public:
        virtual void Update(Terrain& terrain, float_t dt) { }
    };

    /// Сторона блока правок плотности в точках сетки
    static constexpr int32_t SR_TERRAIN_EDIT_BLOCK_SIZE = 16;

    SR_ENUM_NS_CLASS_T(TerrainDeformationShape, uint8_t,
        Sphere,
        Box
    )

    struct TerrainDeformation : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        /// @property
        SR_MATH_NS::FVector3 position;
        /// @property @tooltip(Насколько сильно меняется плотность в центре формы (в единицах плотности, ~метрах). Повторные деформации накапливаются)
        float_t strength = 0.f;
        /// @property
        TerrainDeformationShape shape = TerrainDeformationShape::Sphere;
        /// @property @tooltip(Радиусы сферы или половины сторон коробки, в метрах)
        SR_MATH_NS::FVector3 size = SR_MATH_NS::FVector3(1.f);
        /// @property @tooltip(true - добавить грунт, false - вырезать)
        bool isAdditive = true;

        SR_NODISCARD SR_MATH_NS::AABB GetBounds() const noexcept;
    };

    class Terrain : public SR_UTILS_NS::Component {
        using Super = SR_UTILS_NS::Component;
        SR_CLASS()
    public:
        void Update(float_t dt) override;

        void OnDestroy() override;

        SR_NODISCARD TerrainObserverData GetObserver() const;

        SR_NODISCARD TerrainGrass* GetGrass() const noexcept;
        SR_NODISCARD ITerrainChunkGenerator* GetChunkGenerator() const noexcept;

        void LateUpdate() override;

        /// Деформация копится до LateUpdate, там впекается в правки плотности и затронутые чанки перегенерируются
        /// @method
        void AddDeformation(const TerrainDeformation& deformation);

        /// Добавка к плотности в точке сетки самого детального уровня (координаты точки плотности, см. Density.srsl)
        SR_NODISCARD float_t GetDensityOffset(const SR_MATH_NS::IVector3& point) const;
        /// Есть ли правки плотности в области точек сетки [min, max]
        SR_NODISCARD bool HasDensityOffsets(const SR_MATH_NS::IVector3& min, const SR_MATH_NS::IVector3& max) const;

    private:
        /// @property @tooltip(If not present, will be used main camera of the scene)
        SR_UTILS_NS::EntityRef<SR_GTYPES_NS::Camera> m_camera;
        /// @property @notNull
        ITerrainChunkDataGenerator::Ptr m_chunkDataGenerator;
        /// @property @notNull
        ITerrainChunkGenerator::Ptr m_chunkGenerator;
        /// @property
        TerrainLODManager m_lodManager;
        /// @property @tooltip(Опциональная система травы. Можно оставить пустым)
        TerrainGrass::Ptr m_grass;

    private:
        void ApplyDeformation(const TerrainDeformation& deformation);

    private:
        /// Блок правок плотности: SR_TERRAIN_EDIT_BLOCK_SIZE^3 точек сетки самого детального уровня
        struct DensityEditBlock {
            std::array<float_t, SR_TERRAIN_EDIT_BLOCK_SIZE * SR_TERRAIN_EDIT_BLOCK_SIZE * SR_TERRAIN_EDIT_BLOCK_SIZE> values = { };
        };

        /// Накопленные за кадр деформации, применяются в LateUpdate
        SR_UTILS_NS::Vector<TerrainDeformation> m_pendingDeformations;
        /// Правки плотности хранятся только там, где была деформация. Ключ - координата блока
        SR_HTYPES_NS::FlatHashMap<SR_MATH_NS::IVector3, SR_UTILS_NS::RawPointerHolder<DensityEditBlock>> m_editBlocks;

    };
}

#endif //SR_ENGINE_CORE_WORLD_TERRAIN_H
