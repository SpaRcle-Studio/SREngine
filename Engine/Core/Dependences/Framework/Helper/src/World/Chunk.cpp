//
// Created by Monika on 16.11.2021.
//

#include <World/Chunk.h>
#include <World/Region.h>

using namespace Framework::Helper::World;

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
    m_lifetime -= dt;
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

bool Chunk::Belongs(const Framework::Helper::Math::IVector3 &position,
                    const Framework::Helper::Math::IVector2 &size,
                    const Framework::Helper::Math::FVector3 &point)
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

bool Chunk::Load(const MarshalDecodeNode& node) {
    for (const auto& gameObjectNode : node.GetNodes()) {
        auto&& ptr = m_observer->m_scene->Instance(gameObjectNode);
        ptr->GetTransform()->GlobalTranslate(GetWorldPosition());
    }

    m_loadState = LoadState::Loaded;
    Access(0.f);

    return true;
}

void Chunk::Reload() {

}

MarshalEncodeNode Chunk::Save() const {
    /// scene already locked
    const auto& container = m_observer->m_scene->GetGameObjectsAtChunk(m_regionPosition, m_position);
    if (container.empty())
        return MarshalEncodeNode();

    MarshalEncodeNode marshal("Chunk");
    marshal.Append(m_position);

    for (const auto& gameObject : container) {
        if (gameObject.LockIfValid()) {
            /// сохраняем объект относительно начала координат чанка
            gameObject->GetTransform()->GlobalTranslate(-GetWorldPosition());
            marshal.Append(gameObject->Save(SAVABLE_FLAG_ECS_NO_ID));
            gameObject.Unlock();
        }
    }

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

Chunk::~Chunk() = default;

