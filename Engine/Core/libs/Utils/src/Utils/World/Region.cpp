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
                if (auto&& pMarshal = pChunk->Save(); pMarshal) {
                    if (pMarshal->Valid()) {
                        m_cached[pIt->first] = pMarshal;
                    }
                    else {
                        SR_SAFE_DELETE_PTR(pMarshal);
                    }
                }

                pChunk->Unload();

                delete pChunk;

                pIt = m_loadedChunks.erase(pIt);
            }
        }
    }

    Chunk* Region::GetChunk(const SR_MATH_NS::IVector3 &position) {
        if (position < 0 || position > static_cast<int32_t>(m_width)) {
            SR_ERROR(SR_FORMAT("Region::GetChunk() : incorrect position! "
                               "\n\tWidth: %i\n\tRegion position: %i, %i\n\tChunk position: %i, %i",
                               m_width, m_position.x, m_position.y, position.x, position.y
            ));
            SRHalt0();
            return nullptr;
        }

        Chunk* pChunk = nullptr;

        if (auto&& pChunkIt = m_loadedChunks.find(position); pChunkIt == m_loadedChunks.end()) {
            pChunk = m_loadedChunks[position] = Chunk::Allocate(m_observer, this, position, m_chunkSize);
        }
        else {
            pChunk = pChunkIt->second;
        }

        if (pChunk && pChunk->GetState() == Chunk::LoadState::Unload) {
            if (auto pCacheIt = m_cached.find(position); pCacheIt != m_cached.end()) {
                /// TODO: OPTIMIZE!!!!!!!!!!!!!!!!!!!
                pChunk->Load(pCacheIt->second->Copy());
                delete pCacheIt->second;
                m_cached.erase(pCacheIt);
            }
            else {
                pChunk->Load(SR_HTYPES_NS::Marshal());
            }
        }

        return pChunk;
    }

    Region::~Region() {
        SetDebugLoaded(BoolExt::False);

        for (auto&& [position, chunk] : m_loadedChunks) {
            delete chunk;
        }

        m_loadedChunks.clear();

        for (auto&& [position, pCachedMarshal] : m_cached) {
            delete pCachedMarshal;
        }
        m_cached.clear();
    }

    bool Region::Unload(bool force) {
        SR_LOG("Region::Unload() : unloading region at " + m_position.ToString());

        SetDebugLoaded(BoolExt::False);

        for (auto&& [position, pChunk] : m_loadedChunks) {
            if (!force) {
                if (auto&& pMarshal = pChunk->Save(); pMarshal) {
                    if (pMarshal->Valid()) {
                        m_cached[position] = pMarshal;
                    }
                    else {
                        SR_SAFE_DELETE_PTR(pMarshal);
                    }
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
        if (const auto& pIt = m_loadedChunks.find(position); pIt == m_loadedChunks.end()) {
            return nullptr;
        }
        else
            return pIt->second;
    }

    void Region::ApplyOffset() {
        for (auto&& [key, pChunk] : m_loadedChunks)
            pChunk->ApplyOffset();

        SetDebugLoaded(BoolExt::None);
    }

    Chunk *Region::GetChunk(const SR_MATH_NS::FVector3 &position) {
        return GetChunk(MakeChunk(m_observer->WorldPosToChunkPos(position), m_width));
    }

    void Region::Reload() {
        SR_LOG("Region::Reload() : reloading region at " + m_position.ToString());
        Unload(true /** force */);
        Load();
    }

    SR_HTYPES_NS::Marshal::Ptr Region::Save() const {
        auto&& pMarshal = new SR_HTYPES_NS::Marshal();

        std::list<SR_HTYPES_NS::Marshal::Ptr> available;

        for (const auto& [position, pChunk] : m_loadedChunks) {
            if (auto&& pChunkMarshal = pChunk->Save(); pChunkMarshal) {
                if (pChunkMarshal->Valid()) {
                    SRAssert(pChunkMarshal->BytesCount() > 0);
                    available.emplace_back(pChunkMarshal);
                }
                else {
                    SR_SAFE_DELETE_PTR(pChunkMarshal);
                }
            }
        }

        for (const auto& [position, pCache] : m_cached) {
            SRAssert(pCache->Valid());
            SRAssert(pCache->BytesCount() > 0);
            available.emplace_back(pCache->CopyPtr());
        }

        const uint64_t chunkCount = available.size();
        if (chunkCount == 0)
            return pMarshal;

        pMarshal->Write(VERSION);
        pMarshal->Write(chunkCount);

        for (auto&& pChunkMarshal : available) {
            SRAssert(pChunkMarshal->BytesCount() > 0);
            pMarshal->Write(pChunkMarshal->BytesCount());
            pMarshal->Append(pChunkMarshal);
        }

        return pMarshal;
    }

    bool Region::Load() {
        SR_LOG("Region::Load() : loading region at " + m_position.ToString());

        SRAssert(!m_position.HasZero());

        SetDebugLoaded(BoolExt::True);

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

                auto&& pMarshalChunk = marshal.ReadBytesPtr(size);

                auto&& position = pMarshalChunk->View<Math::IVector3>(0);
                if (pMarshalChunk->Valid()) {
                    m_cached[position] = pMarshalChunk;
                }
                else {
                    SRHalt("invalid cache!");
                    SR_SAFE_DELETE_PTR(pMarshalChunk);
                }
            }
        }

        return true;
    }

    Region::ScenePtr Region::GetScene() const {
        return m_observer->m_scene;
    }

    bool Region::IsChunkLoaded(const SR_MATH_NS::IVector3 &chunk) const {
        if (auto&& pChunkIt = m_loadedChunks.find(chunk); pChunkIt != m_loadedChunks.end()) {
            if (auto&& pChunk = pChunkIt->second) {
                return pChunk->GetState() != Chunk::LoadState::Unload;
            }
        }

        return false;
    }

    void Region::SetDebugLoaded(BoolExt enabled) {
        if (m_position.y != 1) {
            return;
        }

        if (enabled == BoolExt::True || (enabled == BoolExt::None && m_debugLoadedId != SR_ID_INVALID)) {
            const auto size = SR_MATH_NS::FVector3(m_width) * m_chunkSize.x;
            const SR_WORLD_NS::Offset offset = m_observer->m_offset;

            auto fPos = SR_WORLD_NS::AddOffset(m_position.Cast<SR_MATH_NS::Unit>(), offset.m_region);
            fPos = fPos * size + (size / 2);
            fPos = fPos.DeSingular(size);

            fPos += offset.m_chunk * m_chunkSize.x;

            m_debugLoadedId = SR_UTILS_NS::DebugDraw::Instance().DrawPlane(
                    SR_MATH_NS::FVector3(fPos.x, static_cast<SR_MATH_NS::Unit>(0.01), fPos.z),
                    SR_MATH_NS::Quaternion::Identity(),
                    SR_MATH_NS::FVector3(size.x / 2.f, 1.f, size.y / 2.f),
                    SR_MATH_NS::FColor(255, 0, 0, 255),
                    SR_FLOAT_MAX
            );
        }
        else if (m_debugLoadedId != SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().DrawPlane(m_debugLoadedId);
        }
    }
}
