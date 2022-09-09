//
// Created by Monika on 16.11.2021.
//

#include <Utils/World/Chunk.h>
#include <Utils/World/Region.h>
#include <Utils/ECS/GameObject.h>

namespace SR_WORLD_NS {
    Chunk::Allocator Chunk::g_allocator = Chunk::Allocator();

    Chunk::Chunk(SRChunkAllocArgs)
        : m_loadState(LoadState::Unload)
        , m_observer(observer)
        , m_region(region)
        , m_position(position)
        , m_size(size)
        , m_lifetime(0.f)
    {
        SRAssert(m_observer);
        SRAssert(m_region);
        SRAssert(!m_position.HasZero());

        if (m_region) {
            m_regionPosition = m_region->GetPosition();
        }
    }

    void Chunk::Update(float_t dt) {
        if (m_lifetime > 0) {
            m_lifetime -= dt;
        }
    }

    bool Chunk::Belongs(const Math::FVector3 &point) {
        const float_t xMax = m_position.x + m_size.x;
        const float_t yMax = m_position.y + m_size.y;
        const float_t zMax = m_position.z + m_size.x;

        return point.x >= m_position.x && point.y >= m_position.y && point.z >= m_position.z &&
            point.x <= xMax && point.y <= yMax && point.z <= zMax;
    }

    bool Chunk::Access(float_t dt) {
        m_lifetime = dt + 2.f;
        return true;
    }

    bool Chunk::Unload() {
        m_loadState = LoadState::Unload;

        for (auto gameObject : m_observer->m_scene->GetGameObjectsAtChunk(m_regionPosition, m_position)) {
            gameObject.AutoFree([](auto gm) {
                gm->Destroy();
            });
        }

        return true;
    }

    void Chunk::OnExit() {
        m_region->OnExit();
    }

    void Chunk::OnEnter() {
        m_region->OnEnter();
    }

    void Chunk::SetAllocator(const Chunk::Allocator &allocator) {
        g_allocator = allocator;
    }

    Chunk *Chunk::Allocate(SRChunkAllocArgs) {
        if (g_allocator)
            return g_allocator(SRChunkAllocVArgs);

        return new Chunk(SRChunkAllocVArgs);
    }

    bool Chunk::Belongs(const SR_MATH_NS::IVector3 &position,
                        const SR_MATH_NS::IVector2 &size,
                        const SR_MATH_NS::FVector3 &point)
    {
        const float_t xMax = position.x + size.x;
        const float_t yMax = position.y + size.y;
        const float_t zMax = position.z + size.x;

        return point.x >= position.x && point.y >= position.y && point.z >= position.z &&
               point.x <= xMax && point.y <= yMax && point.z <= zMax;
    }

    bool Chunk::ApplyOffset() {
        return true;
    }

    bool Chunk::Load(SR_HTYPES_NS::Marshal&& marshal) {
        if (marshal.Valid()) {
            if (m_position != marshal.Read<Math::IVector3>()) {
                SRAssert2(false, "Something went wrong...");
                return false;
            }

            const uint64_t count = marshal.Read<uint64_t>();
            for (uint64_t i = 0; i < count; ++i) {
                if (auto &&ptr = m_observer->m_scene->Instance(marshal)) {
                    auto&& pTransform = ptr->GetTransform();

                    if (pTransform->GetMeasurement() == SR_UTILS_NS::Measurement::Space2D) {
                        continue;
                    }

                    pTransform->GlobalTranslate(GetWorldPosition());
                }
            }
        }

        m_loadState = LoadState::Loaded;
        Access(0.f);

        return true;
    }

    void Chunk::Reload() {

    }

    SR_HTYPES_NS::Marshal Chunk::Save() const {
        /// scene is locked

        std::list<SR_HTYPES_NS::Marshal> marshaled;

        auto&& gameObjects = m_observer->m_scene->GetGameObjectsAtChunk(m_regionPosition, m_position);

        for (auto&& gameObject : gameObjects) {
            if (gameObject.RecursiveLockIfValid()) {
                /// сохраняем объекты относительно начала координат чанка
                SR_THIS_THREAD->GetContext()->SetValue<SR_MATH_NS::FVector3>(-GetWorldPosition());

                if (auto &&gameObjectMarshal = gameObject->Save(SAVABLE_FLAG_ECS_NO_ID); gameObjectMarshal.Valid()) {
                    marshaled.emplace_back(std::move(gameObjectMarshal));
                }

                gameObject.Unlock();
            }
        }

        SR_THIS_THREAD->GetContext()->RemoveValue<SR_MATH_NS::FVector3>();

        SR_HTYPES_NS::Marshal marshal;

        if (marshaled.empty())
            return marshal;

        marshal.Write(m_position);
        marshal.Write(static_cast<uint64_t>(marshaled.size()));

        for (auto&& gameObject : marshaled)
            marshal.Append(std::move(gameObject));

        return marshal;
    }

    Math::FVector3 Chunk::GetWorldPosition(Math::Axis center) const {
        auto fPos = Helper::World::AddOffset(
                ((m_region->GetWorldPosition()) + (m_position - Math::FVector3(1, 1, 1))).Cast<Math::Unit>(),
                m_observer->m_offset.m_chunk.Cast<Math::Unit>()
        );

        fPos = Math::FVector3(
                fPos.x * m_size.x + (center & Math::AXIS_X ? (Math::Unit) m_size.x / 2 : 0),
                fPos.y * m_size.y + (center & Math::AXIS_Y ? (Math::Unit) m_size.y / 2 : 0),
                fPos.z * m_size.x + (center & Math::AXIS_Z ? (Math::Unit) m_size.x / 2 : 0)
        );

        fPos = fPos.DeSingular(Math::FVector3(m_size.x, m_size.y, m_size.x));

        return fPos;
    }

    Chunk::ScenePtr Chunk::GetScene() const {
        return m_observer->m_scene;
    }
}