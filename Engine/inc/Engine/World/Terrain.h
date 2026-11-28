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
        /// Коллизия чанка уже в физическом мире (или не нужна: пустой чанк, геометрия не годится).
        /// Пока нет - заменяемый чанк держит свою коллизию, иначе под ногами дыра на время генерации и кукинга
        SR_NODISCARD virtual bool IsPhysicsReady() const { return true; }

    protected:
        ITerrainChunk* m_chunk = nullptr;

    };

    /// @abstract
    class ITerrainChunk : public SR_HTYPES_NS::SharedPtr<ITerrainChunk>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunk>;
        SR_CLASS()
    public:
        /// Generating - данные генерируются асинхронно (см. ITerrainChunkDataGenerator::BeginChunkData)
        enum class Status : uint8_t {
            Pool, Created, Generating, Loaded
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
        /// Синхронная генерация: данные готовы по возврату
        virtual void GenerateChunkData(Terrain& terrain, ITerrainChunk& chunk, const TerrainObserverData& observer, float_t distance) { }

        /// ---- Асинхронная генерация. По умолчанию сводится к синхронной.
        /// Можно ли начать ещё одну генерацию (асинхронные генераторы ограничены числом задач в полёте)
        SR_NODISCARD virtual bool CanBeginChunkData() const { return true; }
        /// Начать генерацию. true - данные будут готовы позже и придут в onLoaded из UpdateChunkData, false - уже готовы
        virtual bool BeginChunkData(Terrain& terrain, ITerrainChunk& chunk, const TerrainObserverData& observer) {
            GenerateChunkData(terrain, chunk, observer, 0.f);
            return false;
        }
        /// Завершает готовые асинхронные генерации, для каждого чанка вызывается onLoaded
        virtual void UpdateChunkData(Terrain& terrain, const SR_HTYPES_NS::Function<void(ITerrainChunk&)>& onLoaded) { }
        /// Чанк больше не нужен (ушёл в пул): результат его генерации выбрасывается
        virtual void CancelChunkData(ITerrainChunk& chunk) { }
        /// Дождаться и выбросить все генерации в полёте: ресурсы генератора больше не используются GPU
        virtual void Shutdown() { }

    };

    /// @abstract
    class ITerrainChunkGenerator : public SR_HTYPES_NS::SharedPtr<ITerrainChunkGenerator>, public SR_UTILS_NS::Serializable {
        using Super = SR_HTYPES_NS::SharedPtr<ITerrainChunkGenerator>;
        SR_CLASS()
    public:
        ITerrainChunkGenerator();

    public:
        virtual void Update(Terrain& terrain, const TerrainObserverData& observer, float_t dt) { }
        /// loaderFn начинает генерацию чанка, false - начать нельзя (нет свободных задач), чанк остаётся в очереди
        virtual void LoadNextChunk(const SR_HTYPES_NS::Function<bool(ITerrainChunk&)>& loaderFn) { }
        /// Данные чанка готовы (синхронно или по завершении асинхронной генерации)
        virtual void OnChunkLoaded(ITerrainChunk& chunk) { chunk.SetStatus(ITerrainChunk::Status::Loaded); }

        SR_NODISCARD virtual bool IsCollisionEnabledAt(const ITerrainChunk& chunk) const { return false; }
        /// Перегенерировать чанки, пересекающие область (координаты террейна)
        virtual void InvalidateRegion(const SR_MATH_NS::AABB& bounds) { }
        /// Размер вокселя самого детального уровня в метрах - шаг сетки правок плотности
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetVoxelSize() const { return SR_MATH_NS::FVector3(1.f); }

        /// Объект сцены выдаётся только чанкам с непустой геометрией. Объекты переиспользуются через пул.
        SR_UTILS_NS::SceneObject::Ptr AcquireChunkObject(ITerrainChunk& chunk);
        void ReleaseChunkObject(ITerrainChunk& chunk);

        /// Родитель объектов чанков: их локальные позиции - координаты террейна
        SR_NODISCARD SR_UTILS_NS::SceneObject::Ptr GetPoolObject() const { return m_poolObject.Get(); }

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

    /// Форма мира террейна: плоский (вверх - ось Y) или сферический (планета, вверх - от центра)
    SR_ENUM_NS_CLASS_T(TerrainShape, uint8_t,
        Flat,
        Sphere
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

        /// Мир строится и в редакторе - вокруг редакторной камеры (см. GetObserver)
        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

        void OnOriginShifted(const SR_MATH_NS::FVector3& delta) override;

        /// Наблюдатель в координатах террейна (см. GetTerrainOrigin)
        SR_NODISCARD TerrainObserverData GetObserver() const;

        /// Начало координат террейна в мире - позиция объекта пула чанков (без него - объекта террейна).
        /// Октодерево, чанки, плотность, правки и трава живут в этих координатах, поэтому сдвиг мира
        /// (FloatingOrigin) их не меняет. Поворот и масштаб пула не учитываются
        SR_NODISCARD SR_MATH_NS::FVector3 GetTerrainOrigin() const;
        SR_NODISCARD SR_MATH_NS::FVector3 ToTerrainSpace(const SR_MATH_NS::FVector3& worldPosition) const;

        SR_NODISCARD TerrainGrass* GetGrass() const noexcept;
        SR_NODISCARD ITerrainChunkGenerator* GetChunkGenerator() const noexcept;
        SR_NODISCARD ITerrainChunkDataGenerator* GetChunkDataGenerator() const noexcept { return const_cast<ITerrainChunkDataGenerator*>(m_chunkDataGenerator.Get()); }

        void LateUpdate() override;

        /// Деформация копится до LateUpdate, там впекается в правки плотности и затронутые чанки перегенерируются.
        /// Позиция - мировая, переводится в координаты террейна сразу
        /// @method
        void AddDeformation(const TerrainDeformation& deformation);

        /// Добавка к плотности в точке сетки самого детального уровня (координаты точки плотности, см. Density.srsl)
        SR_NODISCARD float_t GetDensityOffset(const SR_MATH_NS::IVector3& point) const;
        /// Есть ли правки плотности в области точек сетки [min, max]
        SR_NODISCARD bool HasDensityOffsets(const SR_MATH_NS::IVector3& min, const SR_MATH_NS::IVector3& max) const;

        SR_NODISCARD TerrainShape GetShape() const noexcept { return m_shape; }
        SR_NODISCARD const SR_MATH_NS::FVector3& GetSphereCenter() const noexcept { return m_sphereCenter; }
        SR_NODISCARD float_t GetSphereInnerRadius() const noexcept { return m_sphereInnerRadius; }
        SR_NODISCARD float_t GetSphereOuterRadius() const noexcept { return m_sphereOuterRadius; }

        /// Направление "вверх" поверхности в мировой точке: Y для плоского мира, от центра для сферы
        /// @method @evaluate
        SR_NODISCARD SR_MATH_NS::FVector3 GetUpDirection(const SR_MATH_NS::FVector3& position) const;
        /// То же для точки в координатах террейна
        SR_NODISCARD SR_MATH_NS::FVector3 GetLocalUpDirection(const SR_MATH_NS::FVector3& localPosition) const;
        /// Может ли в области (координаты террейна) быть поверхность. Для сферы - пересечение с оболочкой [inner, outer]
        SR_NODISCARD bool IsVolumeIntersects(const SR_MATH_NS::AABB& bounds) const;

    private:
        /// @property @group(Shape)
        TerrainShape m_shape = TerrainShape::Flat;
        /// @property @group(Shape) @tooltip(Центр сферы в координатах террейна - относительно объекта пула чанков)
        SR_MATH_NS::FVector3 m_sphereCenter;
        /// @property @group(Shape) @tooltip(Чанки глубже этого радиуса не создаются. Должен быть ниже самых глубоких пещер)
        float_t m_sphereInnerRadius = 900.f;
        /// @property @group(Shape) @tooltip(Чанки выше этого радиуса не создаются. Должен быть выше самых высоких гор)
        float_t m_sphereOuterRadius = 1100.f;

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
