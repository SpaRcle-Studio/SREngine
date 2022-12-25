//
// Created by Monika on 16.11.2021.
//

#include <Utils/World/Chunk.h>
#include <Utils/World/Region.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/World/SceneCubeChunkLogic.h>

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

    Chunk::~Chunk() {
        SetDebugActive(BoolExt::False);
        SetDebugLoaded(BoolExt::False);
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
        m_lifetime = dt + 10.f;
        SRAssert(m_loadState != LoadState::Unload);
        return true;
    }

    bool Chunk::Unload() {
        m_loadState = LoadState::Unload;

        SetDebugLoaded(BoolExt::False);

        auto&& pLogic = m_observer->m_scene->GetLogic<SceneCubeChunkLogic>();
        auto&& gameObjects = pLogic->GetGameObjectsAtChunk(m_regionPosition, m_position);

        for (auto gameObject : gameObjects) {
            gameObject.AutoFree([](auto gm) {
                gm->Destroy();
            });
        }

        return true;
    }

    void Chunk::OnExit() {
        SetDebugActive(BoolExt::False);
        m_region->OnExit();
    }

    void Chunk::OnEnter() {
        SetDebugActive(BoolExt::True);
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
        SetDebugLoaded(BoolExt::None);
        SetDebugActive(BoolExt::None);

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
        SetDebugLoaded(BoolExt::True);

        return true;
    }

    void Chunk::Reload() {

    }

    SR_HTYPES_NS::Marshal::Ptr Chunk::Save() const {
        /// scene is locked

        std::list<SR_HTYPES_NS::Marshal::Ptr> marshaled;

        auto&& pLogic = m_observer->m_scene->GetLogic<SceneCubeChunkLogic>();
        auto&& gameObjects = pLogic->GetGameObjectsAtChunk(m_regionPosition, m_position);

        /// сохраняем объекты относительно начала координат чанка
        SR_THIS_THREAD->GetContext()->SetValue<SR_MATH_NS::FVector3>(-GetWorldPosition());

        for (auto&& gameObject : gameObjects) {
            if (gameObject.RecursiveLockIfValid()) {
                if (auto &&gameObjectMarshal = gameObject->Save(nullptr, SAVABLE_FLAG_ECS_NO_ID); gameObjectMarshal) {
                    if (gameObjectMarshal->Valid()) {
                        marshaled.emplace_back(gameObjectMarshal);
                    }
                    else {
                        SR_SAFE_DELETE_PTR(gameObjectMarshal);
                    }
                }

                gameObject.Unlock();
            }
        }

        SR_THIS_THREAD->GetContext()->RemoveValue<SR_MATH_NS::FVector3>();

        auto&& pMarshal = new SR_HTYPES_NS::Marshal();

        if (marshaled.empty())
            return pMarshal;

        pMarshal->Write(m_position);
        pMarshal->Write(static_cast<uint64_t>(marshaled.size()));

        for (auto&& gameObject : marshaled)
            pMarshal->Append(gameObject);

        return pMarshal;
    }

    SR_MATH_NS::FVector3 Chunk::GetWorldPosition(SR_MATH_NS::Axis center) const {
        auto fPos = SR_UTILS_NS::World::AddOffset(
                ((m_region->GetWorldPosition()) + (m_position - SR_MATH_NS::FVector3(1, 1, 1))).Cast<SR_MATH_NS::Unit>(),
                m_observer->m_offset.m_chunk.Cast<SR_MATH_NS::Unit>()
        );

        fPos = SR_MATH_NS::FVector3(
                fPos.x * m_size.x + (center & SR_MATH_NS::AXIS_X ? (SR_MATH_NS::Unit) m_size.x / 2 : 0),
                fPos.y * m_size.y + (center & SR_MATH_NS::AXIS_Y ? (SR_MATH_NS::Unit) m_size.y / 2 : 0),
                fPos.z * m_size.x + (center & SR_MATH_NS::AXIS_Z ? (SR_MATH_NS::Unit) m_size.x / 2 : 0)
        );

        fPos = fPos.DeSingular(SR_MATH_NS::FVector3(m_size.x, m_size.y, m_size.x));

        return fPos;
    }

    Chunk::ScenePtr Chunk::GetScene() const {
        return m_observer->m_scene;
    }

    void Chunk::SetDebugActive(BoolExt enabled) {
        if (!Features::Instance().Enabled("DebugChunks", false)) {
            enabled = BoolExt::False;
        }

        if (enabled == BoolExt::True || (enabled == BoolExt::None && m_debugActiveId != SR_ID_INVALID)) {
            m_debugActiveId = SR_UTILS_NS::DebugDraw::Instance().DrawCube(
                    GetWorldPosition(SR_MATH_NS::AXIS_XYZ),
                    SR_MATH_NS::Quaternion::Identity(),
                    SR_MATH_NS::FVector3(m_size.x, m_size.y, m_size.x) / 2,
                    SR_MATH_NS::FColor(0, 255, 0, 255),
                    SR_FLOAT_MAX
            );
        }
        else if (m_debugActiveId != SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().DrawPlane(m_debugActiveId);
        }
    }

    void Chunk::SetDebugLoaded(BoolExt enabled) {
        if (m_position.y != 1 || m_regionPosition.y != 1) {
            return;
        }

        if (!Features::Instance().Enabled("DebugChunks", false)) {
            enabled = BoolExt::False;
        }

        if (enabled == BoolExt::True || (enabled == BoolExt::None && m_debugLoadedId != SR_ID_INVALID)) {
            m_debugLoadedId = SR_UTILS_NS::DebugDraw::Instance().DrawPlane(
                    GetWorldPosition(SR_MATH_NS::AXIS_XZ),
                    SR_MATH_NS::Quaternion::Identity(),
                    SR_MATH_NS::FVector3(m_size.x, m_size.y, m_size.x) / 2,
                    SR_MATH_NS::FColor(255, 255, 0, 255),
                    SR_FLOAT_MAX
            );
        }
        else if (m_debugLoadedId != SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().DrawPlane(m_debugLoadedId);
        }
    }
}