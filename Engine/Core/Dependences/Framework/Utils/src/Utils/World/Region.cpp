//
// Created by Monika on 16.11.2021.
//

#include <Utils/World/Region.h>
#include <Utils/World/Chunk.h>

namespace SR_WORLD_NS {
    Region::Allocator Region::g_allocator = Region::Allocator();

    const uint16_t Region::VERSION = 1000;

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

    Chunk* Region::GetChunk(const SR_MATH_NS::IVector3 &position) {
        SRAssert(position <= static_cast<int32_t>(m_width) && position > 0);

        Chunk* pChunk = nullptr;

        if (auto&& pChunkIt = m_loadedChunks.find(position); pChunkIt == m_loadedChunks.end()) {
            pChunk = m_loadedChunks[position] = Chunk::Allocate(m_observer, this, position, m_chunkSize);
        }
        else {
            pChunk = pChunkIt->second;
        }

        if (pChunk && pChunk->GetState() == Chunk::LoadState::Unload) {
            if (auto pCacheIt = m_cached.find(position); pCacheIt != m_cached.end()) {
                pChunk->Load(std::move(pCacheIt->second));
                m_cached.erase(pCacheIt);
            }
            else {
                pChunk->Load(SR_HTYPES_NS::Marshal());
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

    bool Region::Unload(bool force) {
        SR_LOG("Region::Unload() : unloading region at " + m_position.ToString());

        for (auto&& [position, pChunk] : m_loadedChunks) {
            if (!force) {
                if (auto&& marshal = pChunk->Save(); marshal.Valid()) {
                    m_cached[position] = std::move(marshal);
                }
            }

            pChunk->Unload();
        }

        m_loadedChunks.clear();

        return true;
    }

    void Region::OnEnter() {
        m_containsObserver = true;
    }

    void Region::OnExit() {
        m_containsObserver = false;
    }

    void Region::SetAllocator(const Region::Allocator &allocator) {
        g_allocator = allocator;
    }

    Region *Region::Allocate(SRRegionAllocArgs) {
        if (g_allocator)
            return g_allocator(SRRegionAllocVArgs);

        return new Region(SRRegionAllocVArgs);
    }

    SR_MATH_NS::IVector3 Region::GetWorldPosition() const {
        const Math::IVector3 offset = m_observer->m_offset.m_region;
        auto position = AddOffset(m_position, offset) * m_width;

        if (position.x > 0) position.x -= m_width - 1;
        if (position.y > 0) position.y -= m_width - 1;
        if (position.z > 0) position.z -= m_width - 1;

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

    Chunk *Region::GetChunk(const SR_MATH_NS::FVector3 &position) {
        return GetChunk(MakeChunk(m_observer->WorldPosToChunkPos(position), m_width));
    }

    void Region::Reload() {
        SR_LOG("Region::Reload() : reloading region at " + m_position.ToString());
        Unload(true /** force */);
        Load();
    }

    SR_HTYPES_NS::Marshal Region::Save() const {
        SR_HTYPES_NS::Marshal marshal;

        std::list<SR_HTYPES_NS::Marshal> available;

        for (const auto& [position, pChunk] : m_loadedChunks) {
            if (auto&& chunkMarshal = pChunk->Save(); chunkMarshal.Valid()) {
                SRAssert(chunkMarshal.BytesCount() > 0);
                available.emplace_back(std::move(chunkMarshal));
            }
        }

        for (const auto& [position, cache] : m_cached) {
            SRAssert(cache.Valid());
            SRAssert(cache.BytesCount() > 0);
            available.emplace_back(std::move(cache.Copy()));
        }

        const uint64_t chunkCount = available.size();
        if (chunkCount == 0)
            return marshal;

        marshal.Write(VERSION);
        marshal.Write(chunkCount);

        for (auto&& chunk : available) {
            SRAssert(chunk.BytesCount() > 0);
            marshal.Write(chunk.BytesCount());
            marshal.Append(std::move(chunk));
        }

        return marshal;
    }

    bool Region::Load() {
        SR_LOG("Region::Load() : loading region at " + m_position.ToString());

        const auto&& path = m_observer->m_scene->GetRegionsPath().Concat(m_position.ToString()).ConcatExt("dat");
        if (path.Exists()) {
            auto &&marshal = SR_HTYPES_NS::Marshal::Load(path);

            if (marshal.Read<uint16_t>() != VERSION) {
                SR_ERROR("Region::Load() : version is different!");
                return false;
            }

            const uint64_t count = marshal.Read<uint64_t>();

            for (uint64_t i = 0; i < count; ++i) {
                const uint64_t size = marshal.Read<uint64_t>();

                SRAssert(size != 0);

                SR_HTYPES_NS::Marshal chunk = marshal.ReadBytes(size);

                auto&& position = chunk.View<Math::IVector3>(0);
                if (chunk.Valid()) {
                    m_cached[position] = std::move(chunk);
                }
                else {
                    SRHalt("invalid cache!");
                }
            }
        }

        return true;
    }
}
