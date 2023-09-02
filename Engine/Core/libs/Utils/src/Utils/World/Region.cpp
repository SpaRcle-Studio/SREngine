//
// Created by Monika on 16.11.2021.
//

#include <Utils/World/Region.h>
#include <Utils/World/Chunk.h>

namespace SR_WORLD_NS {
    Region::Allocator Region::g_allocator = Region::Allocator();

    const uint16_t Region::VERSION = 1000;

    void Region::Update(float_t dt) {
        if (m_loadedChunks.empty()) {
            return;
        }

        SR_HTYPES_NS::DataStorage* pContext = nullptr;

        for (auto&& pIt = m_loadedChunks.begin(); pIt != m_loadedChunks.end(); ) {
            const auto& pChunk = pIt->second;

            pChunk->Update(dt);

            if (pChunk->IsAlive()) {
                ++pIt;
            }
            else {
                if (!pContext) {
                    pContext = SR_THIS_THREAD->GetContext();
                }

                if (auto&& pMarshal = pChunk->Save(pContext); pMarshal) {
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
                               "\n\tWidth: %i\n\tRegion position: %i, %i, %i\n\tChunk position: %i, %i, %i",
                               m_width, m_position.x, m_position.y, m_position.z, position.x, position.y, position.z
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
                SR_HTYPES_NS::Marshal copy = pCacheIt->second->Copy();
                pChunk->PreLoad(&copy);

                delete pCacheIt->second;
                m_cached.erase(pCacheIt);
            }
            else {
                pChunk->PreLoad(nullptr);
            }
        }

        return pChunk;
    }

    Region::~Region() {
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
        SR_TRACY_ZONE;

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= Debug::Level::Full) {
            SR_LOG("Region::Unload() : unloading region at " + m_position.ToString());
        }

        if (m_loadedChunks.empty()) {
            return true;
        }

        auto&& pContext = SR_THIS_THREAD->GetContext();

        for (auto&& [position, pChunk] : m_loadedChunks) {
            if (!force) {
                if (auto&& pMarshal = pChunk->Save(pContext); pMarshal) {
                    if (pMarshal->Valid()) {
                        m_cached[position] = pMarshal;
                    }
                    else {
                        SR_SAFE_DELETE_PTR(pMarshal);
                    }
                }
            }

            pChunk->Unload();
            delete pChunk;
            pChunk = nullptr;
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

    Region* Region::Allocate(SRRegionAllocArgs) {
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
        for (auto&& [key, pChunk] : m_loadedChunks) {
            pChunk->ApplyOffset();
        }
    }

    Chunk* Region::GetChunk(const SR_MATH_NS::FVector3 &position) {
        return GetChunk(MakeChunk(m_observer->WorldPosToChunkPos(position), m_width));
    }

    void Region::Reload() {
        SR_TRACY_ZONE;

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= Debug::Level::Full) {
            SR_LOG("Region::Reload() : reloading region at " + m_position.ToString());
        }

        Unload(true /** force */);
        Load();
    }

    SR_HTYPES_NS::Marshal::Ptr Region::Save(SR_HTYPES_NS::DataStorage* pContext) const {
        SR_TRACY_ZONE;

        auto&& pMarshal = new SR_HTYPES_NS::Marshal();

        std::list<SR_HTYPES_NS::Marshal::Ptr> available;

        for (const auto& [position, pChunk] : m_loadedChunks) {
            if (auto&& pChunkMarshal = pChunk->Save(pContext); pChunkMarshal) {
                if (pChunkMarshal->Valid()) {
                    SRAssert(pChunkMarshal->Size() > 0);
                    available.emplace_back(pChunkMarshal);
                }
                else {
                    SR_SAFE_DELETE_PTR(pChunkMarshal);
                }
            }
        }

        for (const auto& [position, pCache] : m_cached) {
            SRAssert(pCache->Valid());
            SRAssert(pCache->Size() > 0);
            available.emplace_back(pCache->CopyPtr());
        }

        const uint64_t chunkCount = available.size();
        if (chunkCount == 0)
            return pMarshal;

        pMarshal->Write<uint16_t>(VERSION);
        pMarshal->Write<uint64_t>(chunkCount);

        for (auto&& pChunkMarshal : available) {
            SRAssert(pChunkMarshal->Size() > 0);
            pMarshal->Write<uint64_t>(pChunkMarshal->Size());
            pMarshal->Append(pChunkMarshal);
        }

        return pMarshal;
    }

    bool Region::Load() {
        SR_TRACY_ZONE;

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= Debug::Level::Full) {
            SR_LOG("Region::Load() : loading region at " + m_position.ToString());
        }

        SRAssert(!m_position.HasZero());

        auto&& pLogic = m_observer->m_scene->GetLogicBase().DynamicCast<SceneCubeChunkLogic>();
        const auto&& path = pLogic->GetRegionsPath().Concat(m_position.ToString()).ConcatExt("dat");

        if (path.Exists()) {
            auto &&marshal = SR_HTYPES_NS::Marshal::Load(path);

            const uint16_t version = marshal.Read<uint16_t>();
            if (version != VERSION) {
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

    bool Region::PostLoad() {
        SR_TRACY_ZONE;

        for (auto&& [pos, pChunk] : m_loadedChunks) {
            if (pChunk->IsPreLoaded()) {
                pChunk->Load();
            }
        }

        return true;
    }
}
