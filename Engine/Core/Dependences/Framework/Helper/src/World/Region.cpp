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

        if (pChunk->IsAlive()) {
            ++pIt;
        }
        else {
            if (auto&& marshal = pChunk->Save(); marshal.Valid()) {
                m_cached[pIt->first] = std::move(marshal);
            }

            pChunk->Unload();

            delete pChunk;

            pIt = m_loadedChunks.erase(pIt);
        }
    }
}

Chunk* Region::GetChunk(const Framework::Helper::Math::IVector3 &position) {
    SRAssert(position.XZ() <= static_cast<int32_t>(m_width) && position.XZ() > 0);

    Chunk* pChunk = nullptr;

    if (auto&& pChunkIt = m_loadedChunks.find(position); pChunkIt == m_loadedChunks.end()) {
        pChunk = m_loadedChunks[position] = Chunk::Allocate(m_observer, this, position, m_chunkSize);
    }
    else {
        pChunk = pChunkIt->second;
    }

    if (pChunk && pChunk->GetState() == Chunk::LoadState::Unload) {
        if (auto pCacheIt = m_cached.find(position); pCacheIt != m_cached.end()) {
            pChunk->Load(pCacheIt->second.Decode());
            m_cached.erase(pCacheIt);
        }
        else {
            pChunk->Load(MarshalDecodeNode());
        }
    }

    return pChunk;
}

Region::~Region() {
    for (auto&& [position, chunk] : m_loadedChunks) {
        delete chunk;
    }

    m_loadedChunks.clear();
    m_cached.clear();
}

bool Region::Unload() {
    SR_LOG("Region::Unload() : unloading region at " + m_position.ToString());

    for (auto&& [position, pChunk] : m_loadedChunks) {
        if (auto&& marshal = pChunk->Save(); marshal.Valid()) {
            m_cached[position] = std::move(marshal);
        }

        pChunk->Unload();
    }

    m_loadedChunks.clear();

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
    return GetChunk(MakeChunk(m_observer->WorldPosToChunkPos(position), m_width));
}

void Region::Reload() {
    for (auto&& [position, pChunk] : m_loadedChunks)
        pChunk->Reload();
}

MarshalEncodeNode Region::Save() const {
    MarshalEncodeNode marshal("Region");
    marshal.Append(m_position);

    bool hasValid = !m_cached.empty();

    for (const auto& [position, pChunk] : m_loadedChunks) {
        if (const auto&& chunkMarshal = pChunk->Save(); chunkMarshal.Valid()) {
            hasValid = true;
            marshal.Append(chunkMarshal);
        }
    }

    for (const auto& [position, cache] : m_cached) {
        if (cache.Valid()) {
            marshal.Append(cache);
        }
        else {
            SRAssert2(false, "invalid cache!");
        }
    }

    if (hasValid) {
        return marshal;
    }
    else
        return MarshalEncodeNode();
}

bool Region::Load() {
    SR_LOG("Scene::Update() : loading region at " + m_position.ToString());

    const auto&& path = m_observer->m_scene->GetRegionsPath().Concat(m_position.ToString()).ConcatExt("dat");
    if (path.Exists()) {
        auto&& decoded = MarshalDecodeNode::Load(path);
        for (const auto& chunk : decoded.GetNodes()) {
            const auto&& position = chunk.GetAttribute<Math::IVector3>();
            if (auto&& cache = chunk.Encode(); cache.Valid()) {
                m_cached[position] = std::move(cache);
            }
            else {
                SRAssert2(false, "invalid cache!");
            }
        }
    }

    return true;
}

