//
// Created by Monika on 25.09.2026.
//

#include <Engine/World/TerrainChunkCube.h>

#include <Physics/PhysicsScene.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/World/Scene.h>

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

        auto&& aabb = SR_MATH_NS::AABB(SR_MATH_NS::FVector3(-1.f), m_chunkSize / m_chunkScale + SR_MATH_NS::FVector3(2.f));
        pGameObject->ForEachComponent([&aabb](SR_UTILS_NS::Component& component) {
            if (auto&& pRenderComponent = dynamic_cast<SR_GTYPES_NS::IRenderComponent*>(&component)) {
                pRenderComponent->SetAABB(aabb);
            }
            return true;
        });

        auto&& pTransform = pGameObject->GetTransform().DynamicCast<SR_UTILS_NS::Transform3D>();
        if (!pTransform) {
            return;
        }

        pTransform->SetScale(m_chunkScale * static_cast<float_t>(pCubeChunk->GetLodScale()));
        pTransform->SetTranslation(GetChunkWorldPosition(*pCubeChunk));
    }

    void TerrainChunkCubeGenerator::LoadNextChunk(const SR_HTYPES_NS::Function<bool(ITerrainChunk&)>& loaderFn) {
        SR_TRACY_ZONE;

        /// Синхронная генерация (compute + чтение с GPU) ограничена и числом, и временем: при подлёте к поверхности
        /// чанков в очереди сотни, и фиксированное число за кадр либо грузит медленно, либо проседает FPS.
        /// Асинхронная дополнительно ограничена числом задач в полёте (loaderFn вернёт false)
        const auto startTime = std::chrono::steady_clock::now();
        for (uint32_t i = 0; i < m_chunksPerFrame && !m_chunksToLoad.empty(); ++i) {
            if (i > 0 && m_generationBudgetMs > 0.f) {
                const float_t elapsedMs = std::chrono::duration<float_t, std::milli>(std::chrono::steady_clock::now() - startTime).count();
                if (elapsedMs >= m_generationBudgetMs) {
                    break;
                }
            }
            if (!LoadNearestChunk(loaderFn)) {
                break;
            }
        }

        /// Отсчёт идёт только пока замена готова и начинается заново, если готовность пропала.
        /// При редактировании замена пересоздаётся каждый кадр - без сброса счётчик успевал дойти до нуля
        /// на предыдущей замене, и старый чанк освобождался в кадр загрузки новой (моргание).
        /// Множества считаются раз за кадр (дорого при тысячах чанков) и тут же используются ReleaseReplacedChunks
        UpdateChunkSets();
        for (auto&& pReplaced : m_replacedChunks) {
            if (!IsReady(pReplaced->GetNode())) {
                pReplaced->SetReplaceFrames(m_replaceDelayFrames);
            }
            else if (pReplaced->GetReplaceFrames() > 0) {
                pReplaced->SetReplaceFrames(pReplaced->GetReplaceFrames() - 1);
            }
        }

        ReleaseReplacedChunks();
    }

    bool TerrainChunkCubeGenerator::LoadNearestChunk(const SR_HTYPES_NS::Function<bool(ITerrainChunk&)>& loaderFn) {
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
        if (!loaderFn(*pChunk)) {
            return false;
        }

        /// Ищем заново: при синхронной генерации loaderFn уже мог поменять очередь (OnChunkLoaded)
        for (uint32_t i = 0; i < m_chunksToLoad.size(); ++i) {
            if (m_chunksToLoad[i] == pChunk) {
                m_chunksToLoad[i] = m_chunksToLoad.back();
                m_chunksToLoad.pop_back();
                break;
            }
        }

        return true;
    }

    void TerrainChunkCubeGenerator::OnChunkLoaded(ITerrainChunk& chunk) {
        Super::OnChunkLoaded(chunk);

        auto&& pChunk = dynamic_cast<TerrainChunkCube*>(&chunk);
        if (!pChunk) {
            SRHalt("TerrainChunkCubeGenerator::OnChunkLoaded() : chunk is not a TerrainChunkCube!");
            return;
        }

        /// Место ещё закрыто заменяемым чанком: новый показывается только вместе со всей заменой (RevealHiddenChunks).
        /// Выключение в кадр получения объекта из пула - no-op для выключенного объекта, лишней перерегистрации нет
        if (auto&& pObject = pChunk->GetObject(); pObject && IntersectsReplaced(pChunk->GetNode())) {
            pObject->SetEnabled(false);
            pChunk->SetHidden(true);
        }

        m_physicsDirty = true;
    }

    void TerrainChunkCubeGenerator::Update(Terrain& terrain, const TerrainObserverData& observer, float_t dt) {
        SR_TRACY_ZONE;

        if (!m_chunkProto) {
            SR_ERROR("TerrainChunkCubeGenerator::Update() : chunk proto is null!");
            return;
        }

        m_terrain = &terrain;

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

        const SR_MATH_NS::FVector3 min = node.GetMin() * m_chunkSize;
        const SR_MATH_NS::FVector3 max = node.GetMax() * m_chunkSize;

        /// Узел вне объёма, где может быть поверхность (например, вне оболочки планеты) - пустой, как и все его дети
        if (m_terrain && !m_terrain->IsVolumeIntersects(SR_MATH_NS::AABB(min, max))) {
            return false;
        }

        if (m_currentDrawDistance > 0.f) {
            /// Узел целиком дальше дальности прорисовки - не нужен ни он, ни его дети
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
        settings.maxLevel = static_cast<uint8_t>(std::min<uint32_t>(m_lodLevels, 12));
        settings.splitDistance = m_splitDistance;
        settings.rootRadius = m_rootRadius;

        m_octree.Build(m_observerNodePosition, settings, [this](const SR_MATH_NS::OctreeNodeId& node) {
            return IsNodeAllowed(node);
        });

        auto&& leaves = m_octree.GetLeaves();

        SR_HTYPES_NS::FlatHashMap<SR_MATH_NS::OctreeNodeId, TerrainChunkCube::Ptr> chunks;
        chunks.reserve(leaves.size());

        {
            SR_TRACY_ZONE_N("Match leaves");

            /// Множество заменяемых только отсеивает листья перед линейным поиском. Пока идёт цикл, оно может
            /// содержать уже оживлённые узлы (лишнее совпадение отсеет поиск), поэтому пересобирается один раз после
            /// цикла, а не после каждого оживления - иначе квадратичная сложность при движении туда-обратно
            auto&& replacedSet = GetReplacedSet();
            bool isReplacedChanged = false;

            for (auto&& node : leaves) {
                if (auto&& pIt = m_chunks.find(node); pIt != m_chunks.end()) {
                    chunks[node] = std::move(pIt->second);
                    m_chunks.erase(pIt);
                    continue;
                }

                /// Узел снова стал листом, пока его ещё показывали в ожидании замены
                bool isRevived = false;
                /// Сначала проверка по множеству: перебор заменяемых на каждый лист стоил листья x заменяемые
                const bool isReplacedNode = !m_replacedChunks.empty() && replacedSet.Contains(node);
                for (uint32_t i = 0; isReplacedNode && i < m_replacedChunks.size(); ++i) {
                    if (m_replacedChunks[i]->GetNode() == node) {
                        m_replacedChunks[i]->SetReplaceFrames(0);
                        chunks[node] = m_replacedChunks[i];
                        m_replacedChunks[i] = m_replacedChunks.back();
                        m_replacedChunks.pop_back();
                        isReplacedChanged = true;
                        isRevived = true;
                        break;
                    }
                }

                if (isRevived) {
                    continue;
                }

                chunks[node] = CreateChunk(node);
            }

            if (isReplacedChanged) {
                m_isReplacedSetDirty = true;
            }
        }

        {
            SR_TRACY_ZONE_N("Retire chunks");

            /// Узлы, которые больше не являются листьями. Видимые остаются до загрузки замены.
            for (auto&& [node, pChunk] : m_chunks) {
                RetireChunk(pChunk);
            }
        }

        m_chunks = std::move(chunks);
        m_activeChunksCount = static_cast<uint32_t>(m_chunks.size());

        {
            SR_TRACY_ZONE_N("Update LOD borders");

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
                    RetireChunk(pChunk);
                    pChunk = CreateChunk(node);
                }
                pChunk->SetLodBorders(lodBorders);
            }
        }

        /// ReleaseReplacedChunks здесь не нужен: только что заменённые чанки ждут replaceDelayFrames и в этом кадре
        /// не освобождаются. Освобождение, показ скрытых и перегенерация грязных - в LoadNextChunk следующего кадра,
        /// с одним UpdateChunkSets на кадр (при движении он стоил ~2 мс на вызов)
    }

    void TerrainChunkCubeGenerator::InvalidateRegion(const SR_MATH_NS::AABB& bounds) {
        SR_TRACY_ZONE;

        /// Запас в 2 вокселя: вершины на гранях чанка зависят от соседних вокселей
        const SR_MATH_NS::FVector3 margin = m_chunkScale * 2.f;
        const SR_MATH_NS::FVector3 regionMin = bounds.min - margin;
        const SR_MATH_NS::FVector3 regionMax = bounds.max + margin;

        for (auto&& [node, pChunk] : m_chunks) {
            const SR_MATH_NS::FVector3 nodeMin = node.GetMin() * m_chunkSize;
            const SR_MATH_NS::FVector3 nodeMax = node.GetMax() * m_chunkSize;
            if (nodeMax.x < regionMin.x || nodeMin.x > regionMax.x ||
                nodeMax.y < regionMin.y || nodeMin.y > regionMax.y ||
                nodeMax.z < regionMin.z || nodeMin.z > regionMax.z)
            {
                continue;
            }

            /// Генерация уже идёт со старыми правками плотности - перегенерировать после загрузки (см. ReleaseReplacedChunks)
            if (pChunk->GetStatus() == ITerrainChunk::Status::Generating) {
                pChunk->SetDirty(true);
                continue;
            }

            /// Ещё не сгенерирован - деформации прочитаются при генерации
            if (pChunk->GetStatus() != ITerrainChunk::Status::Loaded) {
                continue;
            }

            /// Пустой чанк не виден, его можно перегенерировать на месте: после выкапывания у него может появиться геометрия
            if (!pChunk->GetObject()) {
                pChunk->SetStatus(ITerrainChunk::Status::Created);
                m_chunksToLoad.emplace_back(pChunk);
                continue;
            }

            /// Место ещё закрыто заменяемым чанком (деформации идут каждый кадр). Выбросить текущий нельзя:
            /// он уже загружен и вот-вот заменит старый - иначе новая геометрия моргает, а старая висит до конца деформации.
            /// Перегенерируем его, как только он покажется (см. ReleaseReplacedChunks)
            if (IsCoveredByReplaced(node)) {
                pChunk->SetDirty(true);
                continue;
            }

            RegenerateChunk(pChunk);
        }
    }

    void TerrainChunkCubeGenerator::RegenerateChunk(TerrainChunkCube::Ptr& pChunk) {
        /// Перегенерация в отдельный чанк: старый остаётся видимым до загрузки нового (без моргания)
        const SR_MATH_NS::OctreeNodeId node = pChunk->GetNode();
        const uint8_t lodBorders = pChunk->GetLodBorders();

        pChunk->SetDirty(false);
        RetireChunk(pChunk);

        pChunk = CreateChunk(node);
        pChunk->SetLodBorders(lodBorders);
    }

    void TerrainChunkCubeGenerator::RetireChunk(const TerrainChunkCube::Ptr& pChunk) {
        if (pChunk->GetStatus() == ITerrainChunk::Status::Loaded && pChunk->GetObject() && !pChunk->IsHidden()) {
            pChunk->SetReplaceFrames(m_replaceDelayFrames);
            m_replacedChunks.emplace_back(pChunk);
            m_isReplacedSetDirty = true;
        }
        else {
            /// Скрытый чанк ничего не закрывает - держать его нет смысла
            ReleaseChunk(pChunk);
        }
    }

    const SR_MATH_NS::OctreeNodeSet& TerrainChunkCubeGenerator::GetReplacedSet() const {
        if (m_isReplacedSetDirty) {
            SR_TRACY_ZONE_N("Rebuild replaced set");

            m_replacedSet.Clear();
            const uint8_t maxLevel = GetMaxLevel();
            for (auto&& pReplaced : m_replacedChunks) {
                /// В список попадают только видимые чанки с объектом (RetireChunk), но проверка дешёвая
                if (pReplaced->GetObject()) {
                    m_replacedSet.Add(pReplaced->GetNode(), maxLevel);
                }
            }
            m_isReplacedSetDirty = false;
        }
        return m_replacedSet;
    }

    void TerrainChunkCubeGenerator::UpdateChunkSets() {
        SR_TRACY_ZONE;

        m_notLoadedSet.Clear();
        m_notReadySet.Clear();

        const uint8_t maxLevel = GetMaxLevel();
        const bool isPhysicsSimulating = IsPhysicsSimulating();

        for (auto&& [node, pChunk] : m_chunks) {
            const bool isLoaded = pChunk->GetStatus() == ITerrainChunk::Status::Loaded;
            if (!isLoaded) {
                m_notLoadedSet.Add(node, maxLevel);
            }

            /// Трава замены тоже должна быть готова: иначе либо место голое, либо (если держать обе) травы вдвое больше
            bool isReady = isLoaded && pChunk->IsGrassReady();
            if (isReady && pChunk->GetObject() && pChunk->GetData() && !pChunk->GetData()->IsRenderReady()) {
                isReady = false;
            }

            /// Коллизия замены тоже: заменяемый чанк держит свою, пока новая не попадет в физический мир.
            /// Иначе на время генерации, сборки и кукинга (по одному за кадр) под ногами дыра - персонаж проваливается.
            /// Без симуляции (редактор) тела в мир не попадают - не ждем
            if (isReady && isPhysicsSimulating && pChunk->GetData() && IsCollisionEnabledAt(*pChunk) && !pChunk->GetData()->IsPhysicsReady()) {
                isReady = false;
            }

            if (!isReady) {
                m_notReadySet.Add(node, maxLevel);
            }
        }
    }

    bool TerrainChunkCubeGenerator::IntersectsReplaced(const SR_MATH_NS::OctreeNodeId& node) const {
        return GetReplacedSet().Intersects(node, GetMaxLevel());
    }

    bool TerrainChunkCubeGenerator::IsAreaLoaded(const SR_MATH_NS::OctreeNodeId& node) const {
        return !m_notLoadedSet.Intersects(node, GetMaxLevel());
    }

    void TerrainChunkCubeGenerator::RevealHiddenChunks() {
        SR_TRACY_ZONE;

        bool hasHidden = false;
        for (auto&& [node, pChunk] : m_chunks) {
            if (pChunk->IsHidden()) {
                hasHidden = true;
                break;
            }
        }

        if (!hasHidden) {
            return;
        }

        const uint8_t maxLevel = GetMaxLevel();

        /// Заменяемые чанки, чья замена загружена не целиком: пересекающие их скрытые чанки ждут
        m_unrevealableSet.Clear();
        for (auto&& pReplaced : m_replacedChunks) {
            if (pReplaced->GetObject() && !IsAreaLoaded(pReplaced->GetNode())) {
                m_unrevealableSet.Add(pReplaced->GetNode(), maxLevel);
            }
        }

        for (auto&& [node, pChunk] : m_chunks) {
            if (!pChunk->IsHidden()) {
                continue;
            }

            /// Показываем, когда загружена вся замена каждого заменяемого чанка, который пересекает этот.
            /// Все чанки одной замены проходят проверку в одном кадре и появляются вместе
            if (m_unrevealableSet.Intersects(node, maxLevel)) {
                continue;
            }

            pChunk->SetHidden(false);
            if (auto&& pObject = pChunk->GetObject()) {
                pObject->SetEnabled(true);
            }
        }
    }

    bool TerrainChunkCubeGenerator::IsCoveredByReplaced(const SR_MATH_NS::OctreeNodeId& node) const {
        /// Заменённый узел должен накрывать текущий целиком - то есть быть им самим или его предком
        return GetReplacedSet().ContainsSelfOrAncestor(node, GetMaxLevel());
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
        pChunk->SetDirty(false);
        pChunk->SetHidden(false);
        pChunk->SetStatus(ITerrainChunk::Status::Created);
        m_chunksToLoad.emplace_back(pChunk);

        return pChunk;
    }

    const SR_MATH_NS::OctreeNodeId* TerrainChunkCubeGenerator::FindLeafAt(const SR_MATH_NS::IVector3& position) const {
        /// Листья не пересекаются, поэтому точку содержит не больше одного. Ищем по всем уровням, от детального к грубому.
        const uint8_t maxLevel = static_cast<uint8_t>(std::min<uint32_t>(m_lodLevels, 12));
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

        /// Юбки вытягиваются против нормали поверхности, поэтому нужны на всех гранях: на сфере "боковых" граней нет
        for (int32_t axis = 0; axis < 3; ++axis) {
            for (int32_t side = 0; side < 2; ++side) {
                /// Юбки нужны с обеих сторон стыка: щель закрывает юбка того чанка, чей край выше.
                /// Одной точки достаточно: если область соседа того же размера поделена - любая её точка лежит в более мелком листе,
                /// иначе - в листе того же или большего размера.
                SR_MATH_NS::IVector3 probe = node.position;
                probe[axis] += side == 0 ? -1 : size;

                /// Обычно сосед - лист того же уровня: один поиск вместо перебора всех уровней (FindLeafAt).
                /// Его позиция выровнена по size, как у узла, который FindLeafAt нашёл бы на этом уровне
                SR_MATH_NS::OctreeNodeId sameLevel = node;
                sameLevel.position[axis] += side == 0 ? -size : size;
                if (m_chunks.contains(sameLevel)) {
                    continue;
                }

                if (auto&& pNeighbour = FindLeafAt(probe); pNeighbour && pNeighbour->level != node.level) {
                    mask |= static_cast<uint8_t>(1u << (axis * 2 + side));
                }
            }
        }

        return mask;
    }

    bool TerrainChunkCubeGenerator::IsReady(const SR_MATH_NS::OctreeNodeId& node) const {
        /// По множеству, собранному в UpdateChunkSets
        return !m_notReadySet.Intersects(node, GetMaxLevel());
    }

    void TerrainChunkCubeGenerator::ReleaseReplacedChunks() {
        SR_TRACY_ZONE;

        RevealHiddenChunks();

        for (uint32_t i = 0; i < m_replacedChunks.size();) {
            auto&& pReplaced = m_replacedChunks[i];
            if (pReplaced->GetReplaceFrames() == 0 && IsReady(pReplaced->GetNode())) {
                ReleaseChunk(pReplaced);
                m_replacedChunks[i] = m_replacedChunks.back();
                m_replacedChunks.pop_back();
                m_isReplacedSetDirty = true;
            }
            else {
                ++i;
            }
        }

        /// Чанки, получившие деформацию, пока их место было закрыто: теперь они видны и перегенерируются по последним правкам
        for (auto&& [node, pChunk] : m_chunks) {
            if (!pChunk->IsDirty() || pChunk->GetStatus() != ITerrainChunk::Status::Loaded || IsCoveredByReplaced(node)) {
                continue;
            }

            if (!pChunk->GetObject()) {
                pChunk->SetDirty(false);
                pChunk->SetStatus(ITerrainChunk::Status::Created);
                m_chunksToLoad.emplace_back(pChunk);
                continue;
            }

            RegenerateChunk(pChunk);
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

        /// Чанк уйдёт в пул и может достаться другому узлу - результат его генерации применять нельзя
        if (pChunk->GetStatus() == ITerrainChunk::Status::Generating && m_terrain) {
            if (auto&& pDataGenerator = m_terrain->GetChunkDataGenerator()) {
                pDataGenerator->CancelChunkData(*pChunk);
            }
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

        /// Заменяемый чанк держит коллизию до освобождения: замена считается готовой только с коллизией (UpdateChunkSets)
        for (auto&& pChunk : m_replacedChunks) {
            if (auto&& pChunkData = pChunk->GetData()) {
                pChunkData->SwitchPhysics(IsCollisionEnabledAt(*pChunk));
            }
        }
    }

    bool TerrainChunkCubeGenerator::IsPhysicsSimulating() const {
        auto&& pScene = m_terrain ? m_terrain->TryGetScene() : nullptr;
        if (!pScene) {
            return false;
        }

        auto&& pPhysicsScene = dynamic_cast<SR_PHYSICS_NS::PhysicsScene*>(pScene->GetModule("Physics"));
        return pPhysicsScene && pPhysicsScene->IsSimulating();
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
