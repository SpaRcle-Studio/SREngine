//
// Created by Monika on 25.09.2026.
//

#include <Engine/World/TerrainChunkCube.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform3D.h>

#include <Codegen/TerrainChunkCube.generated.hpp>

namespace SR_CORE_NS {
    float_t TerrainChunkCube::GetDistanceTo(const ITerrainChunk& other) const {
        auto&& pOther = dynamic_cast<const TerrainChunkCube*>(&other);
        if (!pOther) {
            SRHalt("TerrainChunkCube::GetDistanceTo() : other chunk is not a TerrainChunkCube!");
            return 0.f;
        }
        return static_cast<float_t>(m_node.GetCenter().Distance(pOther->GetNode().GetCenter()));
    }

    SR_MATH_NS::FVector3 TerrainChunkCubeGenerator::GetChunkWorldPosition(const TerrainChunkCube& chunk) const {
        /// Воксель v чанка с lodScale s берётся в точке плотности c * (N - 2) + 1 + (v - 1) * s (см. Density.srsl),
        /// вершины меша лежат в v - 0.5. Сдвиг совмещает границы чанков разных LOD.
        const float_t lodOffset = 0.5f * static_cast<float_t>(chunk.GetLodScale() - 1);
        return SR_MATH_NS::FVector3(chunk.GetPosition()) * m_chunkSize - m_chunkScale * lodOffset;
    }

    void TerrainChunkCubeGenerator::SetupChunkObject(ITerrainChunk& chunk, SR_UTILS_NS::SceneObject& object) {
        auto&& pCubeChunk = dynamic_cast<TerrainChunkCube*>(&chunk);
        if (!pCubeChunk) {
            SRHalt("TerrainChunkCubeGenerator::SetupChunkObject() : chunk is not a TerrainChunkCube!");
            return;
        }

        auto&& pGameObject = dynamic_cast<SR_UTILS_NS::GameObject*>(&object);
        if (!pGameObject) {
            return;
        }

        auto&& pTransform = pGameObject->GetTransform().DynamicCast<SR_UTILS_NS::Transform3D>();
        if (!pTransform) {
            return;
        }

        pTransform->SetAABB(SR_MATH_NS::AABB(SR_MATH_NS::FVector3(-1.f), m_chunkSize / m_chunkScale + SR_MATH_NS::FVector3(2.f)));
        pTransform->SetScale(m_chunkScale * static_cast<float_t>(pCubeChunk->GetLodScale()));
        pTransform->SetTranslation(GetChunkWorldPosition(*pCubeChunk));
    }

    void TerrainChunkCubeGenerator::LoadNextChunk(const SR_HTYPES_NS::Function<void(ITerrainChunk&)>& loaderFn) {
        SR_TRACY_ZONE;

        for (uint32_t i = 0; i < m_chunksPerFrame && !m_chunksToLoad.empty(); ++i) {
            LoadNearestChunk(loaderFn);
        }

        /// Отсчёт начинается только когда замена готова: новый объект активируется и регистрируется в рендере не в тот же кадр
        for (auto&& pReplaced : m_replacedChunks) {
            if (pReplaced->GetReplaceFrames() > 0 && IsReady(pReplaced->GetNode())) {
                pReplaced->SetReplaceFrames(pReplaced->GetReplaceFrames() - 1);
            }
        }

        ReleaseReplacedChunks();
    }

    void TerrainChunkCubeGenerator::LoadNearestChunk(const SR_HTYPES_NS::Function<void(ITerrainChunk&)>& loaderFn) {
        /// Сначала ближайшие к наблюдателю, при равном расстоянии - более детальные
        uint32_t index = 0;
        float_t bestScore = SR_FLOAT_MAX;
        for (uint32_t i = 0; i < m_chunksToLoad.size(); ++i) {
            auto&& pChunk = m_chunksToLoad[i];
            const float_t score = pChunk->GetNode().DistanceTo(m_observerNodePosition) + static_cast<float_t>(pChunk->GetLod()) * 0.01f;
            if (score < bestScore) {
                bestScore = score;
                index = i;
            }
        }

        TerrainChunkCube::Ptr pChunk = m_chunksToLoad[index];
        m_chunksToLoad[index] = m_chunksToLoad.back();
        m_chunksToLoad.pop_back();

        loaderFn(*pChunk);

        m_physicsDirty = true;
    }

    void TerrainChunkCubeGenerator::Update(Terrain& terrain, const TerrainObserverData& observer, float_t dt) {
        SR_TRACY_ZONE;

        if (!m_chunkProto) {
            SR_ERROR("TerrainChunkCubeGenerator::Update() : chunk proto is null!");
            return;
        }

        const SR_MATH_NS::FVector3 observerNodePosition = observer.position / m_chunkSize;

        m_observerChunkPosition = SR_MATH_NS::IVector3(
            static_cast<int32_t>(std::floor(observerNodePosition.x)),
            static_cast<int32_t>(std::floor(observerNodePosition.y)),
            static_cast<int32_t>(std::floor(observerNodePosition.z))
        );

        float_t drawDistance = m_drawDistance > 0.f ? m_drawDistance : observer.farPlane;
        if (observer.farPlane > 0.f) {
            drawDistance = std::min(drawDistance, observer.farPlane);
        }

        const bool isDrawDistanceChanged = std::abs(drawDistance - m_currentDrawDistance) > 1.f;

        if (isDrawDistanceChanged || m_observerNodePosition.x == SR_MATH_NS::UnitMAX || m_observerNodePosition.Distance(observerNodePosition) > m_rebuildThreshold) {
            m_observerNodePosition = observerNodePosition;
            m_observerPosition = observer.position;
            m_currentDrawDistance = drawDistance;
            RebuildTree();
            m_physicsDirty = true;
        }

        if (m_physicsDirty) {
            UpdatePhysics();
        }
    }

    bool TerrainChunkCubeGenerator::IsNodeAllowed(const SR_MATH_NS::OctreeNodeId& node) const {
        if (m_useHeightLimits && (node.position.y > m_maxHeight || node.position.y + node.GetSize() <= m_minHeight)) {
            return false;
        }

        if (m_currentDrawDistance > 0.f) {
            /// Узел целиком дальше дальности прорисовки - не нужен ни он, ни его дети
            const SR_MATH_NS::FVector3 min = node.GetMin() * m_chunkSize;
            const SR_MATH_NS::FVector3 max = node.GetMax() * m_chunkSize;
            const float_t dx = std::max({ min.x - m_observerPosition.x, m_observerPosition.x - max.x, 0.f });
            const float_t dy = std::max({ min.y - m_observerPosition.y, m_observerPosition.y - max.y, 0.f });
            const float_t dz = std::max({ min.z - m_observerPosition.z, m_observerPosition.z - max.z, 0.f });
            if (dx * dx + dy * dy + dz * dz > m_currentDrawDistance * m_currentDrawDistance) {
                return false;
            }
        }

        return true;
    }

    void TerrainChunkCubeGenerator::RebuildTree() {
        SR_TRACY_ZONE;

        SR_MATH_NS::LodOctree::Settings settings;
        settings.maxLevel = static_cast<uint8_t>(std::min<uint32_t>(m_lodLevels, 8));
        settings.splitDistance = m_splitDistance;
        settings.rootRadius = m_rootRadius;

        m_octree.Build(m_observerNodePosition, settings, [this](const SR_MATH_NS::OctreeNodeId& node) {
            return IsNodeAllowed(node);
        });

        auto&& leaves = m_octree.GetLeaves();

        SR_HTYPES_NS::FlatHashMap<SR_MATH_NS::OctreeNodeId, TerrainChunkCube::Ptr> chunks;
        chunks.reserve(leaves.size());

        for (auto&& node : leaves) {
            if (auto&& pIt = m_chunks.find(node); pIt != m_chunks.end()) {
                chunks[node] = std::move(pIt->second);
                m_chunks.erase(pIt);
                continue;
            }

            /// Узел снова стал листом, пока его ещё показывали в ожидании замены
            bool isRevived = false;
            for (uint32_t i = 0; i < m_replacedChunks.size(); ++i) {
                if (m_replacedChunks[i]->GetNode() == node) {
                    m_replacedChunks[i]->SetReplaceFrames(0);
                    chunks[node] = m_replacedChunks[i];
                    m_replacedChunks[i] = m_replacedChunks.back();
                    m_replacedChunks.pop_back();
                    isRevived = true;
                    break;
                }
            }

            if (isRevived) {
                continue;
            }

            chunks[node] = CreateChunk(node);
        }

        /// Узлы, которые больше не являются листьями. Видимые остаются до загрузки замены.
        for (auto&& [node, pChunk] : m_chunks) {
            if (pChunk->GetStatus() == ITerrainChunk::Status::Loaded && pChunk->GetObject()) {
                pChunk->SetReplaceFrames(m_replaceDelayFrames);
                m_replacedChunks.emplace_back(pChunk);
            }
            else {
                ReleaseChunk(pChunk);
            }
        }

        m_chunks = std::move(chunks);
        m_activeChunksCount = static_cast<uint32_t>(m_chunks.size());

        /// Юбки строятся только на гранях с соседом другого LOD. Если набор таких граней изменился - чанк перегенерируется.
        for (auto&& [node, pChunk] : m_chunks) {
            const uint8_t lodBorders = CalculateLodBorders(node);
            if (lodBorders == pChunk->GetLodBorders()) {
                continue;
            }
            /// У пустого чанка геометрии нет - юбки ему не нужны
            if (pChunk->GetStatus() == ITerrainChunk::Status::Loaded && pChunk->GetObject()) {
                /// Перегенерация в отдельный чанк: старый остаётся видимым до загрузки нового.
                /// Обновление меша на месте перерегистрирует его в рендере, и чанк моргает.
                pChunk->SetReplaceFrames(m_replaceDelayFrames);
                m_replacedChunks.emplace_back(pChunk);
                pChunk = CreateChunk(node);
            }
            pChunk->SetLodBorders(lodBorders);
        }

        ReleaseReplacedChunks();
    }

    TerrainChunkCube::Ptr TerrainChunkCubeGenerator::CreateChunk(const SR_MATH_NS::OctreeNodeId& node) {
        TerrainChunkCube::Ptr pChunk;
        if (!m_freeChunks.empty()) {
            pChunk = m_freeChunks.back();
            m_freeChunks.pop_back();
        }
        else {
            pChunk = SR_UTILS_NS::Factory::Instance().Create<TerrainChunkCube>(m_chunkProto->GetMeta()->GetFactoryName());
            m_chunkProto->CloneTo(*pChunk);
        }

        pChunk->SetNode(node);
        pChunk->SetLodBorders(0);
        pChunk->SetStatus(ITerrainChunk::Status::Created);
        m_chunksToLoad.emplace_back(pChunk);

        return pChunk;
    }

    const SR_MATH_NS::OctreeNodeId* TerrainChunkCubeGenerator::FindLeafAt(const SR_MATH_NS::IVector3& position) const {
        /// Листья не пересекаются, поэтому точку содержит не больше одного. Ищем по всем уровням, от детального к грубому.
        const uint8_t maxLevel = static_cast<uint8_t>(std::min<uint32_t>(m_lodLevels, 8));
        for (uint8_t level = 0; level <= maxLevel; ++level) {
            const int32_t size = 1 << level;
            SR_MATH_NS::OctreeNodeId node;
            node.level = level;
            node.position = SR_MATH_NS::IVector3(
                static_cast<int32_t>(std::floor(static_cast<float_t>(position.x) / static_cast<float_t>(size))) * size,
                static_cast<int32_t>(std::floor(static_cast<float_t>(position.y) / static_cast<float_t>(size))) * size,
                static_cast<int32_t>(std::floor(static_cast<float_t>(position.z) / static_cast<float_t>(size))) * size
            );
            if (auto&& pIt = m_chunks.find(node); pIt != m_chunks.end()) {
                return &pIt->first;
            }
        }
        return nullptr;
    }

    uint8_t TerrainChunkCubeGenerator::CalculateLodBorders(const SR_MATH_NS::OctreeNodeId& node) const {
        uint8_t mask = 0;
        const int32_t size = node.GetSize();

        for (int32_t axis = 0; axis < 3; ++axis) {
            if (axis == 1) {
                continue; /// юбки только на боковых гранях
            }
            for (int32_t side = 0; side < 2; ++side) {
                /// Юбки нужны с обеих сторон стыка: щель закрывает юбка того чанка, чей край выше.
                /// Одной точки достаточно: если область соседа того же размера поделена - любая её точка лежит в более мелком листе,
                /// иначе - в листе того же или большего размера.
                SR_MATH_NS::IVector3 probe = node.position;
                probe[axis] += side == 0 ? -1 : size;
                if (auto&& pNeighbour = FindLeafAt(probe); pNeighbour && pNeighbour->level != node.level) {
                    mask |= static_cast<uint8_t>(1u << (axis * 2 + side));
                }
            }
        }

        return mask;
    }

    bool TerrainChunkCubeGenerator::IsReady(const SR_MATH_NS::OctreeNodeId& node) const {
        for (auto&& [otherNode, pChunk] : m_chunks) {
            if (!otherNode.Intersects(node)) {
                continue;
            }
            /// Трава замены тоже должна быть готова: иначе либо место голое, либо (если держать обе) травы вдвое больше
            if (pChunk->GetStatus() != ITerrainChunk::Status::Loaded || !pChunk->IsGrassReady()) {
                return false;
            }
        }
        return true;
    }

    void TerrainChunkCubeGenerator::ReleaseReplacedChunks() {
        SR_TRACY_ZONE;

        for (uint32_t i = 0; i < m_replacedChunks.size();) {
            auto&& pReplaced = m_replacedChunks[i];
            if (IsReady(pReplaced->GetNode()) && pReplaced->GetReplaceFrames() == 0) {
                ReleaseChunk(pReplaced);
                m_replacedChunks[i] = m_replacedChunks.back();
                m_replacedChunks.pop_back();
            }
            else {
                ++i;
            }
        }

        uint32_t withObject = 0;
        for (auto&& [node, pChunk] : m_chunks) {
            withObject += pChunk->GetObject() ? 1 : 0;
        }
        for (auto&& pChunk : m_replacedChunks) {
            withObject += pChunk->GetObject() ? 1 : 0;
        }
        m_chunksWithObjectCount = withObject;
    }

    void TerrainChunkCubeGenerator::ReleaseChunk(const TerrainChunkCube::Ptr& pChunk) {
        SR_TRACY_ZONE;

        if (pChunk->GetStatus() == ITerrainChunk::Status::Created) {
            m_chunksToLoad.erase_if([&](const TerrainChunkCube::Ptr& pOther) {
                return pOther == pChunk;
            });
        }

        ReleaseChunkObject(*pChunk);
        pChunk->SetStatus(ITerrainChunk::Status::Pool);

        if (m_freeChunks.size() < m_maxFreeChunks) {
            m_freeChunks.emplace_back(pChunk);
        }
    }

    void TerrainChunkCubeGenerator::UpdatePhysics() {
        SR_TRACY_ZONE;

        m_physicsDirty = false;

        uint32_t builds = 0;

        for (auto&& [node, pChunk] : m_chunks) {
            auto&& pChunkData = pChunk->GetData();
            if (!pChunkData || pChunk->GetStatus() != ITerrainChunk::Status::Loaded) {
                continue;
            }

            const bool isWithinPhysicsDistance = IsCollisionEnabledAt(*pChunk);

            /// Построение коллизии дорогое, поэтому не больше m_maxPhysicsBuildsPerFrame за кадр
            if (isWithinPhysicsDistance && !pChunkData->IsPhysicsEnabled()) {
                if (builds >= m_maxPhysicsBuildsPerFrame) {
                    m_physicsDirty = true;
                    continue;
                }
                pChunkData->SwitchPhysics(true);
                builds += pChunkData->IsPhysicsEnabled() ? 1 : 0;
                continue;
            }

            pChunkData->SwitchPhysics(isWithinPhysicsDistance);
        }

        for (auto&& pChunk : m_replacedChunks) {
            if (auto&& pChunkData = pChunk->GetData()) {
                pChunkData->SwitchPhysics(false);
            }
        }
    }

    bool TerrainChunkCubeGenerator::IsCollisionEnabledAt(const ITerrainChunk& chunk) const {
        auto&& pCubeChunk = dynamic_cast<const TerrainChunkCube*>(&chunk);
        if (!pCubeChunk) {
            SRHalt("TerrainChunkCubeGenerator::IsCollisionEnabledAt() : chunk is not a TerrainChunkCube!");
            return false;
        }

        if (pCubeChunk->GetLod() != 0) {
            return false;
        }

        const auto chunkPosition = pCubeChunk->GetPosition();
        return
            static_cast<uint32_t>(std::abs(chunkPosition.x - m_observerChunkPosition.x)) <= m_physicsDistance &&
            static_cast<uint32_t>(std::abs(chunkPosition.y - m_observerChunkPosition.y)) <= m_physicsDistance &&
            static_cast<uint32_t>(std::abs(chunkPosition.z - m_observerChunkPosition.z)) <= m_physicsDistance;
    }
}
