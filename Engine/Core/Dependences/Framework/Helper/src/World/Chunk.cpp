//
// Created by Monika on 16.11.2021.
//

#include <World/Chunk.h>
#include <World/Region.h>
#include <EntityComponentSystem/Transform.h>

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

bool Chunk::Access() {
    m_lifetime = 2.f;
    return true;
}

bool Chunk::Unload() {
    m_loadState = LoadState::Unload;
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
    return true;
}

bool Chunk::Load() {
    m_loadState = LoadState::Loaded;
    return true;
}

void Chunk::Reload() {

}

Chunk::~Chunk() = default;

