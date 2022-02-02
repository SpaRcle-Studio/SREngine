//
// Created by Monika on 16.11.2021.
//

#include <World/Region.h>
#include <World/Chunk.h>

using namespace Framework::Helper::World;

Region::Allocator Region::g_allocator = Region::Allocator();

void Region::Update(float_t dt) {
    for (auto&& pIt = m_loadedChunks.begin(); pIt != m_loadedChunks.end(); ) {
        const auto& pChunk = pIt->second;

        pChunk->Update(dt);

        if (pChunk->IsAlive())
            ++pIt;
        else {
            pChunk->Unload();
            delete pChunk;
            pIt = m_loadedChunks.erase(pIt);
        }
    }
}

Chunk* Region::GetChunk(const Framework::Helper::Math::IVector3 &position) {
    SRAssert(position.XZ() <= static_cast<int32_t>(m_width) && position.XZ() > 0);

    if (auto&& it = m_loadedChunks.find(position); it == m_loadedChunks.end()) {
        auto chunk = m_loadedChunks[position] = Chunk::Allocate(m_observer, this, position, m_chunkSize);
        chunk->Load();
        return chunk;
    }
    else
        return it->second;
}

Region::~Region() {
    for (auto&& [position, chunk] : m_loadedChunks) {
        delete chunk;
    }

    m_loadedChunks.clear();
}

bool Region::Unload() {
    Helper::Debug::Log("Region::Unload() : unloading region at " + m_position.ToString());

    for (auto&& [position, chunk] : m_loadedChunks) {
        chunk->Unload();
    }

    return true;
}

void Region::OnEnter() {

}

void Region::OnExit() {

}

void Region::SetAllocator(const Region::Allocator &allocator) {
    g_allocator = allocator;
}

Region *Region::Allocate(SRRegionAllocArgs) {
    if (g_allocator)
        return g_allocator(SRRegionAllocVArgs);

    return new Region(SRRegionAllocVArgs);
}

Framework::Helper::Math::IVector2 Region::GetWorldPosition() const {
    const Math::IVector2 offset = m_observer->m_offset.m_region;
    auto position = AddOffset(m_position, offset) * m_width;

    if (position.x > 0) position.x -= m_width - 1;
    if (position.y > 0) position.y -= m_width - 1;

    return position;
}

Chunk *Region::At(const Helper::Math::IVector3& position) const {
    return m_loadedChunks.at(position);
}

Chunk *Region::Find(const Framework::Helper::Math::IVector3 &position) const {
    if (const auto& pIt = m_loadedChunks.find(position); pIt == m_loadedChunks.end())
        return nullptr;
    else
        return pIt->second;
}

void Region::ApplyOffset() {
    for (auto&& [key, pChunk] : m_loadedChunks)
        pChunk->ApplyOffset();
}

Chunk *Region::GetChunk(const FVector3 &position) {
    const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);

    const auto targetPos = AddOffset(
            position.Singular(Math::FVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x)).Cast<int>() / chunkSize,
            -m_observer->m_offset.m_chunk
    );

    return GetChunk(MakeChunk(targetPos, m_width));
}

void Region::Reload() {
    for (auto&& [position, pChunk] : m_loadedChunks)
        pChunk->Reload();
}
