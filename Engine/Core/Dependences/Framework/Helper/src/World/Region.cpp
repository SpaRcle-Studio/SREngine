//
// Created by Monika on 16.11.2021.
//

#include <World/Region.h>
#include <World/Chunk.h>

using namespace Framework::Helper::World;

Region::Allocator Region::g_allocator = Region::Allocator();

void Region::Update(float_t dt) {

}

Chunk* Region::GetChunk(const Framework::Helper::Math::IVector3 &position) {
    if (auto&& it = m_loadedChunks.find(position); it == m_loadedChunks.end()) {
        auto chunk = m_loadedChunks[position] = Chunk::Allocate(this, position, m_chunkSize);
        chunk->SetOffset(m_offset);
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
    else {
        Helper::Debug::Error("Region::Allocate() : allocator isn't set!");
        return nullptr;
    }
}

void Region::SetOffset(const Offset &offset) {
    m_offset = offset;

    for (auto&& [key, pChunk] : m_loadedChunks)
        pChunk->SetOffset(m_offset);
}

Framework::Helper::Math::IVector2 Region::GetWorldPosition() const {
    auto position = AddOffset(m_position, m_offset.m_region);

    if (position.x > 0) --position.x;
    if (position.y > 0) --position.y;

    if (position.x < 0) ++position.x;
    if (position.y < 0) ++position.y;

    return position * m_width;
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
