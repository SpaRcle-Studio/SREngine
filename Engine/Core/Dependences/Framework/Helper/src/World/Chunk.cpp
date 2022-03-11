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

bool Chunk::Load(const Xml::Node& xml) {
    for (const auto& gameObjectXml : xml.TryGetNodes()) {
        m_observer->m_scene->Instance(gameObjectXml);
    }

    m_loadState = LoadState::Loaded;
    Access(0.f);

    return true;
}

void Chunk::Reload() {

}

Xml::Document Chunk::Save() const {
    /// scene already locked
    const auto& container = m_observer->m_scene->GetGameObjectsAtChunk(m_regionPosition, m_position);
    if (container.empty())
        return Xml::Document::Empty();

    auto document = Xml::Document::New();

    auto&& chunkXml = document.Root().AppendChild("Chunk");
    chunkXml.AppendAttribute(m_position);

    for (const auto& gameObject : container) {
        if (gameObject.LockIfValid()) {
            chunkXml.AppendChild(gameObject->Save(SAVABLE_FLAG_ECS_NO_ID).DocumentElement());
            gameObject.Unlock();
        }
    }

    return document;
}

Chunk::~Chunk() = default;

