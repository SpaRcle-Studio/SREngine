//
// Created by Monika on 25.09.2026.
//

#include <Engine/World/TerrainChunkCube.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform3D.h>

#include <Codegen/TerrainChunkCube.generated.hpp>

namespace SR_CORE_NS {
    const SR_MATH_NS::IVector3& TerrainChunkCube::GetPosition() const noexcept {
        return m_position;
    }

    bool TerrainChunkCubeLessPredicate::operator()(const TerrainChunkCube::Ptr& pLeft, const TerrainChunkCube::Ptr& pRight) const noexcept {
        return pLeft->GetPosition() < pRight->GetPosition();
    }

    void TerrainChunkCubeGenerator::LoadNextChunk(SR_HTYPES_NS::Function<void(ITerrainChunk&)> loaderFn) {
        SR_TRACY_ZONE;

        {
            SR_TRACY_ZONE_N("Erase invalid chunks");
            m_chunksToLoad.erase_if([&](const TerrainChunkCube::Ptr &pChunk) {
                return pChunk->GetStatus() != ITerrainChunk::Status::Created;
            });
        }

        if (m_chunksToLoad.empty()) {
            return;
        }

        uint32_t index = 0;
        TerrainChunkCube::Ptr pNearestChunk;
        for (auto&& pChunk : m_chunksToLoad) {
            if (!pNearestChunk || pChunk->GetPosition().Distance(m_observerChunkPosition) < pNearestChunk->GetPosition().Distance(m_observerChunkPosition)) {
                pNearestChunk = pChunk;
            }
            index++;
        }
        m_chunksToLoad.erase(m_chunksToLoad.begin() + index - 1);

        if (!pNearestChunk) {
            SRHalt("TerrainChunkCubeGenerator::LoadNextChunk() : chunk is null!");
            return;
        }

        loaderFn(*pNearestChunk);
    }

    void TerrainChunkCubeGenerator::Update(Terrain& terrain, float_t dt) {
        SR_TRACY_ZONE;

        auto&& pChunkObjectProto = m_chunkObjectProto.Get();
        if (!pChunkObjectProto) {
            SR_ERROR("TerrainChunkCubeGenerator::Update() : chunk object proto is null!");
            return;
        }

        auto&& pPoolObject = m_poolObject.Get();
        if (!pPoolObject) {
            SR_ERROR("TerrainChunkCubeGenerator::Update() : pool object is null!");
            return;
        }

        if (!m_chunkProto) {
            SR_ERROR("TerrainChunkCubeGenerator::Update() : chunk proto is null!");
            return;
        }

        auto&& observer = terrain.GetObserver();

        SR_MATH_NS::IVector3 observerChunkPosition = SR_MATH_NS::IVector3(
            static_cast<int32_t>(std::floor(observer.position.x / m_chunkSize.x)),
            static_cast<int32_t>(std::floor(observer.position.y / m_chunkSize.y)),
            static_cast<int32_t>(std::floor(observer.position.z / m_chunkSize.z))
        );

        if (observerChunkPosition == m_observerChunkPosition) {
            return;
        }

        m_observerChunkPosition = observerChunkPosition;

        //{
        //    SR_TRACY_ZONE_N("Unload chunks");
        //    /// unload chunks that are outside of the unload distance
        //    for (auto pIt = m_chunks.begin(); pIt != m_chunks.end();) {
        //        auto&& pChunk = *pIt;
        //        const auto chunkPosition = pChunk->GetPosition();
        //        if (std::abs(chunkPosition.x - observerChunkPosition.x) > m_unloadDistance.x ||
        //            std::abs(chunkPosition.y - observerChunkPosition.y) > m_unloadDistance.y ||
        //            std::abs(chunkPosition.z - observerChunkPosition.z) > m_unloadDistance.z)
        //        {
        //            pChunk->Deactivate();
        //            pChunk->SetStatus(ITerrainChunk::Status::Pool);
        //            m_freeChunks.emplace_back(pChunk);
        //            pIt = m_chunks.erase(pIt);
        //        }
        //        else {
        //            ++pIt;
        //        }
        //    }
        //}

        {
            SR_TRACY_ZONE_N("Load chunks");
            for (int32_t x = -m_minLoadDistance.x; x <= m_maxLoadDistance.x; ++x) {
                for (int32_t y = -m_minLoadDistance.y; y <= m_maxLoadDistance.y; ++y) {
                    for (int32_t z = -m_minLoadDistance.z; z <= m_maxLoadDistance.z; ++z) {
                        const auto chunkPosition = SR_MATH_NS::IVector3(
                            observerChunkPosition.x + x,
                            observerChunkPosition.y + y,
                            observerChunkPosition.z + z
                        );
                        m_chunkProto->SetPosition(chunkPosition);

                        auto&& pFoundChunk = m_chunks.FindNoCompare(m_chunkProto);
                        if (!pFoundChunk || (*pFoundChunk)->GetPosition() != chunkPosition) {
                            TerrainChunkCube::Ptr pNewChunk;
                            bool isNewChunk = false;
                            if (!m_freeChunks.empty()) {
                                pNewChunk = m_freeChunks.back();
                                m_freeChunks.pop_back();
                            }
                            else {
                                pNewChunk = SR_UTILS_NS::Factory::Instance().Create<TerrainChunkCube>(m_chunkProto->GetMeta()->GetFactoryName());
                                m_chunkProto->CloneTo(*pNewChunk);
                                isNewChunk = true;
                            }

                            pNewChunk->SetPosition(chunkPosition);
                            pNewChunk->Activate(*pPoolObject, *pChunkObjectProto, SR_MATH_NS::FVector3(
                                static_cast<float_t>(chunkPosition.x) * m_chunkSize.x,
                                static_cast<float_t>(chunkPosition.y) * m_chunkSize.y,
                                static_cast<float_t>(chunkPosition.z) * m_chunkSize.z
                            ));

                            if (isNewChunk) {
                                if (auto&& pGameObject = pNewChunk->GetObject().DynamicCast<SR_UTILS_NS::GameObject>()) {
                                    if (auto&& pTransform = pGameObject->GetTransform().DynamicCast<SR_UTILS_NS::Transform3D>()) {
                                        const auto aabb = SR_MATH_NS::AABB(SR_MATH_NS::FVector3(), m_chunkSize);
                                        pTransform->SetAABB(aabb);
                                        pTransform->SetScale(m_chunkScale);
                                    }
                                }
                            }

                            m_chunksToLoad.emplace_back(pNewChunk);
                            pNewChunk->SetStatus(ITerrainChunk::Status::Created);

                            if (!m_chunks.Add(pNewChunk)) {
                                SRHalt("TerrainChunkCubeGenerator::Update() : failed to add chunk!");
                            }
                        }
                    }
                }
            }
        }
    }
}