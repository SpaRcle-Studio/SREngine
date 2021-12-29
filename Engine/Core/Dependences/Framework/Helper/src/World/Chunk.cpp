//
// Created by Monika on 16.11.2021.
//

#include <World/Chunk.h>
#include <World/Region.h>
#include <EntityComponentSystem/Transform.h>

using namespace Framework::Helper::World;

Chunk::Allocator Chunk::g_allocator = Chunk::Allocator();

Chunk::Chunk(SRChunkAllocArgs)
    : m_region(region)
    , m_position(position)
    , m_size(size)
    , m_lifetime(0.f)
{
    SRAssert(!m_position.HasZero())
}

void Chunk::Update(float_t dt) {
    m_lifetime -= dt;

    if (m_lifetime <= 0) {

    }
}

bool Chunk::Belongs(const Math::FVector3 &point) {
    const float_t xMax = m_position.x + m_size.x;
    const float_t yMax = m_position.y + m_size.y;
    const float_t zMax = m_position.z + m_size.x;

    return point.x >= m_position.x && point.y >= m_position.y && point.z >= m_position.z &&
        point.x <= xMax && point.y <= yMax && point.z <= zMax;
}

bool Chunk::Access(const Math::FVector3 &point) {
    return false;
}

bool Chunk::Unload() {
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
    else {
        Helper::Debug::Error("Chunk::Allocate() : allocator isn't set!");
        return nullptr;
    }
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

void Chunk::SetOffset(const World::Offset& offset) {
    m_delta = offset - m_offset;
    m_offset = offset;
}

bool Chunk::Clear() {
    if (m_container.empty())
        return false;

    m_container.clear();

    return true;
}

void Chunk::Insert(const GameObject::Ptr& ptr) {
    m_container.insert(ptr);
}

void Chunk::Erase(const Framework::Helper::GameObject::Ptr &ptr) {
    m_container.erase(ptr);
}

uint32_t Chunk::GetContainerSize() const {
    return static_cast<uint32_t>(m_container.size());
}

bool Chunk::ApplyOffset() {
    if (m_container.empty() || m_delta.Empty())
        return false;

    auto fOffset = ((Helper::Math::IVector3::XZ(m_delta.m_region) * m_region->GetWidth()) + m_delta.m_chunk).Cast<Math::Unit>();

    fOffset.x *= m_size.x;
    fOffset.y *= m_size.y;
    fOffset.z *= m_size.x;

    for (auto& object : m_container)
        object->GetTransform()->GlobalTranslate(fOffset);

    return true;
}

Chunk::~Chunk() = default;

