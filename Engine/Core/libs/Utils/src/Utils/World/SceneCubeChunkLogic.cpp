//
// Created by Monika on 22.12.2022.
//

#include <Utils/World/SceneCubeChunkLogic.h>

namespace SR_WORLD_NS {
    SceneCubeChunkLogic::SceneCubeChunkLogic(const ScenePtr& scene)
        : Super(scene)
        , m_observer(new Observer(scene))
    {
        ReloadConfig();
    }

    SceneCubeChunkLogic::~SceneCubeChunkLogic() {
        SR_SAFE_DELETE_PTR(m_observer);
    }

    bool SceneCubeChunkLogic::ReloadConfig() {
        /// TODO: возможно лучше сохранять в саму сцену?

        const std::string path = ResourceManager::Instance().GetResPath().Concat("Engine/Configs/World.xml");

        if (auto xml = SR_XML_NS::Document::Load(path); xml.Valid()) {
            const auto& configs = xml.Root().GetNode("Configs");

            m_chunkSize = Math::IVector2(
                    configs.TryGetNode("DefaultChunkWidth").TryGetAttribute("Value").ToInt(10),
                    configs.TryGetNode("DefaultChunkHeight").TryGetAttribute("Value").ToInt(10)
            );
            m_regionWidth = configs.TryGetNode("DefaultRegionWidth").TryGetAttribute("Value").ToInt(6);

            m_observer->SetWorldMetrics(m_chunkSize, m_regionWidth);
            m_observer->SetShiftDist(configs.TryGetNode("DefaultShiftDistance").TryGetAttribute("Value").ToInt(10));
            m_observer->SetScope(configs.TryGetNode("DefaultScope").TryGetAttribute("Value").ToInt(10));

            m_scopeEnabled = configs.TryGetNode("ScopeEnabled").TryGetAttribute("Value").ToBool(true);
            m_shiftEnabled = configs.TryGetNode("ShiftEnabled").TryGetAttribute("Value").ToBool(true);
            m_updateContainer = configs.TryGetNode("UpdateContainer").TryGetAttribute("Value").ToBool(true);

            return true;
        }
        else {
            SR_ERROR("SceneCubeChunkLogic::Scene() : file not found! Path: " + path);
            return false;
        }
    }

    bool SceneCubeChunkLogic::ReloadChunks() {
        for (auto&& [position, pRegion] : m_regions)
            pRegion->Reload();

        return true;
    }

    const Scene::GameObjects& SceneCubeChunkLogic::GetGameObjectsAtChunk(const SR_MATH_NS::IVector3 &region, const SR_MATH_NS::IVector3 &chunk) const {
        const auto key = TensorKey(region, chunk);
        if (m_tensor.count(key) == 0) {
            static GameObjects _default = GameObjects();
            return _default;
        }

        return m_tensor.at(key);
    }

    bool SceneCubeChunkLogic::Reload() {
        if (!ReloadConfig()) {
            SR_ERROR("SceneCubeChunkLogic::Reload() : failed to reload config!");
            return false;
        }

        if (!ReloadChunks()) {
            SR_ERROR("SceneCubeChunkLogic::Reload() : failed to reload chunks!");
            return false;
        }

        return true;
    }

    Chunk* SceneCubeChunkLogic::GetCurrentChunk() const {
        if (const auto& region = m_regions.find(m_observer->m_region); region != m_regions.end())
            return region->second->Find(m_observer->m_chunk);

        return nullptr;
    }

    bool SceneCubeChunkLogic::ScopeCheckFunction(int32_t x, int32_t y, int32_t z) const {
        if (!m_observer) {
            return false;
        }

        if (y > 1 || y < -1) {
            return false;
        }

        constexpr float_t alpha = 3.f;

        return ((SR_POW(x) / alpha) + (SR_POW(y) / alpha) + SR_POW(z) <= SR_POW(m_observer->m_scope));
    }

    SR_NODISCARD Region* SceneCubeChunkLogic::GetRegion(const SR_MATH_NS::IVector3& region) {
        if (m_regions.find(region) == m_regions.end()) {
            auto&& pRegion = Region::Allocate(m_observer, m_regionWidth, m_chunkSize, region);
            m_regions.insert(std::pair(region, pRegion));
            pRegion->Load();

            return pRegion;
        }

        return m_regions.at(region);
    }

    bool SceneCubeChunkLogic::IsChunkLoaded(const SR_MATH_NS::IVector3 &region, const SR_MATH_NS::IVector3 &chunk) const {
        if (m_regions.find(region) == m_regions.end()) {
            return false;
        }

        if (auto&& pRegion = m_regions.at(region)) {
            return pRegion->IsChunkLoaded(chunk);
        }

        return false;
    }

    void SceneCubeChunkLogic::SetObserver(const GameObject::Ptr& target) {
        SR_LOCK_GUARD

        if (target != m_observer->m_target) {
            m_observer->SetTarget(target);
        }
    }

    SR_MATH_NS::FVector3 SceneCubeChunkLogic::GetWorldPosition(const SR_MATH_NS::IVector3 &region, const SR_MATH_NS::IVector3 &chunk) {
        if (auto&& pRegionIt = m_regions.find(region); pRegionIt != m_regions.end()) {
            auto&& [_, pRegion] = *pRegionIt;
            if (auto&& pChunk = pRegion->Find(chunk)) {
                return pChunk->GetWorldPosition();
            }
        }

        return SR_MATH_NS::FVector3();
    }

    void SceneCubeChunkLogic::SetWorldOffset(const Offset &offset) {
        SR_LOCK_GUARD

        const auto prevOffset = m_observer->m_offset;
        const auto region = (offset.m_chunk / static_cast<int32_t>(m_regionWidth));

        m_observer->m_offset = World::Offset(
                offset.m_region + region,
                offset.m_chunk - region * m_regionWidth
        );

        SR_LOG("SceneCubeChunkLogic::SetWorldOffset() : set new offset " + m_observer->m_offset.ToString());

        const auto deltaOffset = m_observer->m_offset - prevOffset;

        const auto fOffset = ((deltaOffset.m_region * m_regionWidth + deltaOffset.m_chunk)
                              * Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x)).Cast<Math::Unit>();

        auto&& root = m_scene->GetRootGameObjects();
        for (const GameObject::Ptr& gameObject : root)
            gameObject->GetTransform()->GlobalTranslate(fOffset);

        for (const auto& [position, pRegion] : m_regions)
            pRegion->ApplyOffset();
    }

    void SceneCubeChunkLogic::UpdateScope(float_t dt) {
        SR_LOCK_GUARD

        if (m_observer->m_region.HasZero()) {
            m_observer->MoveRegion(SR_MATH_NS::IVector3(-1, -1, -1));
        }

        SRAssert(!m_observer->m_region.HasZero());

        const auto scope = m_observer->m_scope;

        const auto& update = [&](const Math::IVector3& point) -> void {
            const auto neighbour = m_observer->MathNeighbour(point);

            /// если объект находится за пределами загруженной области, то нужно ее загрузить и поместить туда его
            if (m_regions.find(neighbour.m_region) == m_regions.end()) {
                auto&& pRegion = Region::Allocate(m_observer, m_regionWidth, m_chunkSize, neighbour.m_region);
                m_regions.insert(std::pair(neighbour.m_region, pRegion));
                pRegion->Load();
            }

            if (auto chunk = m_regions.at(neighbour.m_region)->GetChunk(neighbour.m_chunk)) {
                chunk->Access(dt);
            }
        };

        for (int32_t x = -scope; x <= scope; ++x) {
            for (int32_t y = -scope; y <= scope; ++y) {
                for (int32_t z = -scope; z <= scope; ++z) {
                    if (!ScopeCheckFunction(x, y, z)) {
                        continue;
                    }

                    update(SR_MATH_NS::IVector3(x, y, z));
                }
            }
        }

        auto&& pContext = SR_THIS_THREAD->GetContext();

        for (auto&& pIt = m_regions.begin(); pIt != m_regions.end(); ) {
            const auto& pRegion = pIt->second;

            pRegion->Update(dt);

            if (pRegion->IsAlive()) {
                ++pIt;
            }
            else {
                pRegion->Unload();
                SaveRegion(pRegion, pContext);
                delete pRegion;
                pIt = m_regions.erase(pIt);
            }
        }
    }

    void SceneCubeChunkLogic::CheckShift(const SR_MATH_NS::IVector3 &chunk) {
        SR_LOCK_GUARD

        const auto shift = m_observer->m_shiftDistance;
        Math::IVector3 offset = m_observer->m_offset.m_chunk + (m_observer->m_offset.m_region * m_regionWidth);

        if (chunk.x > shift) {
            offset.x -= abs(chunk.x);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }
        else if (chunk.x < -shift) {
            offset.x += abs(chunk.x);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }

        if (chunk.y > shift) {
            offset.y -= abs(chunk.y);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }
        else if (chunk.y < -shift) {
            offset.y += abs(chunk.y);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }

        if (chunk.z > shift) {
            offset.z -= abs(chunk.z);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }
        else if (chunk.z < -shift) {
            offset.z += abs(chunk.z);
            SetWorldOffset(Offset(Math::IVector3::Zero(), offset));
        }
    }

    void SceneCubeChunkLogic::UpdateContainers() {
        SR_LOCK_GUARD

        const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);

        const uint64_t reserved = m_tensor.size();
        m_tensor.clear();
        m_tensor.reserve(reserved);

        auto&& root = m_scene->GetRootGameObjects();

        for (GameObject::Ptr gameObject : root) {
            const Math::FVector3 gmPosition = gameObject->GetTransform()->GetTranslation();

            if (!gmPosition.IsFinite() || gmPosition.ContainsNaN()) {
                continue;
            }

            auto chunk = AddOffset(SR_MATH_NS::IVector3(gmPosition.Singular(chunkSize.Cast<Math::Unit>()) / chunkSize), -m_observer->m_offset.m_chunk);
            auto region = AddOffset(chunk.Singular(Math::IVector3(m_regionWidth - 1)) / Math::IVector3(m_regionWidth), -m_observer->m_offset.m_region);

            const TensorKey key = TensorKey(region, MakeChunk(chunk, m_regionWidth));

            if (auto&& pIt = m_tensor.find(key); pIt != m_tensor.end()) {
                pIt->second.emplace_back(std::move(gameObject));
            }
            else {
                m_tensor[key].emplace_back(std::move(gameObject));

                if (GetRegion(key.region)->GetChunk(key.chunk)) {
                    /// подгружаем чанк, чтобы объект не остался висеть в пустоте
                }
            }
        }
    }

    void SceneCubeChunkLogic::SaveRegion(Region* pRegion, SR_HTYPES_NS::DataStorage* pContext) const {
        SR_LOCK_GUARD

        auto&& regionsPath = GetRegionsPath();

        regionsPath.Make(Path::Type::Folder);

        auto&& regPath = regionsPath.Concat(pRegion->GetPosition().ToString()).ConcatExt("dat");
        if (auto&& pRegionMarshal = pRegion->Save(pContext); pRegionMarshal) {
            if (pRegionMarshal->Valid()) {
                pRegionMarshal->Save(regPath);
            }
            else if (regPath.IsFile()) {
                SR_PLATFORM_NS::Delete(regPath);
            }

            SR_SAFE_DELETE_PTR(pRegionMarshal);
        }
        else if (regPath.Exists(Path::Type::File)) {
            Platform::Delete(regPath);
        }
    }

    Path SceneCubeChunkLogic::GetRegionsPath() const {
        /// TODO: cache path
        return m_scene->GetPath().Concat("regions");
    }

    bool SceneCubeChunkLogic::Save(const Path &path) {
        SR_LOCK_GUARD

        auto&& currentChunk = CalculateCurrentChunk();
        m_observer->SetChunk(currentChunk);

        UpdateContainers();
        UpdateScope(0.f);

        auto&& pContext = SR_THIS_THREAD->GetContext();

        for (auto&& [position, pRegion] : m_regions) {
            SaveRegion(pRegion, pContext);
        }

        auto&& pSceneRootMarshal = m_scene->SaveComponents(nullptr, SAVABLE_FLAG_NONE);
        if (!pSceneRootMarshal->Save(path.Concat("data/components.bin"))) {
            SR_ERROR("SceneCubeChunkLogic::Save() : failed to save scene components!");
        }
        SR_SAFE_DELETE_PTR(pSceneRootMarshal);

        auto&& sceneMainXmlPath = path.Concat("main.scene");
        if (!SR_XML_NS::Document::New().Save(sceneMainXmlPath)) {
            SR_ERROR("SceneCubeChunkLogic::Save() : failed to save xml!\n\tPath: " + sceneMainXmlPath.ToString());
            return false;
        }

        return true;
    }

    bool SceneCubeChunkLogic::Load(const Path &path) {
        SR_LOCK_GUARD

        auto&& componentsPath = m_scene->GetPath().Concat("data/components.bin");

        if (auto&& rootComponentsMarshal = SR_HTYPES_NS::Marshal::LoadPtr(componentsPath)) {
            auto&& components = SR_UTILS_NS::ComponentManager::Instance().LoadComponents(*rootComponentsMarshal);
            delete rootComponentsMarshal;
            for (auto&& pComponent : components) {
                m_scene->LoadComponent(pComponent);
            }
        }
        else {
            SR_ERROR("SceneCubeChunkLogic::Load() : file not found!\n\tPath: " + componentsPath.ToString());
            return false;
        }

        return true;
    }

    void SceneCubeChunkLogic::Destroy() {
        SR_LOCK_GUARD

        if (Debug::Instance().GetLevel() > Debug::Level::None) {
            SR_LOG("SceneCubeChunkLogic::Destroy() : unload " + std::to_string(m_regions.size()) + " regions...");
        }

        for (auto&& [position, region] : m_regions) {
            region->Unload(true);
            delete region;
        }
    }

    void SceneCubeChunkLogic::Update(float_t dt) {
        SR_LOCK_GUARD

        const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);
        const auto regSize = Math::IVector3(m_regionWidth);
        const auto regSize2 = Math::IVector3(m_regionWidth - 1);

        const World::Offset& offset = m_observer->m_offset;

        if (m_observer->m_target) {
            m_observer->m_targetPosition = m_observer->m_target->GetTransform()->GetTranslation().Singular(chunkSize.Cast<Math::Unit>());
        }

        auto&& lastChunk = m_observer->m_lastChunk;
        auto&& lastRegion = m_observer->m_lastRegion;

        auto&& currentChunk = CalculateCurrentChunk();

        if (lastChunk != currentChunk) {
            if (m_regions.find(lastRegion) != m_regions.end()) {
                auto&& pChunk = m_regions.at(lastRegion)->GetChunk(m_observer->m_chunk);

                SRAssert(pChunk == m_currentChunk);
                SRAssert(pChunk);

                if (pChunk) {
                    pChunk->OnExit();
                }

                m_currentChunk = nullptr;
            }

            m_observer->SetChunk(currentChunk);

            auto region = AddOffset(currentChunk.Singular(regSize2) / regSize, -offset.m_region);

            if (auto regionDelta = (region - lastRegion); !regionDelta.Empty()) {
                m_observer->MoveRegion(regionDelta);
                SRAssert(!m_observer->m_region.HasZero());
            }

            if (m_regions.find(m_observer->m_region) == m_regions.end()) {
                auto pRegion = Region::Allocate(m_observer, m_regionWidth, m_chunkSize, m_observer->m_region);
                pRegion->Load();
                m_regions.insert(std::pair(m_observer->m_region, pRegion));
            }

            if (auto &&regionIt = m_regions.at(m_observer->m_region)) {
                if (auto&& pChunk = regionIt->GetChunk(m_observer->m_chunk)) {
                    SRAssert(!m_currentChunk);

                    m_currentChunk = pChunk;

                    pChunk->OnEnter();
                }
            }

            lastRegion = region;
            lastChunk = currentChunk;
        }

        if (m_updateContainer)
            UpdateContainers();

        if (m_scopeEnabled) {
            UpdateScope(dt);
        }

        if (m_shiftEnabled) {
            CheckShift(m_observer->m_targetPosition.Cast<int>() / chunkSize);
        }
    }

    SR_MATH_NS::IVector3 SceneCubeChunkLogic::CalculateCurrentChunk() const {
        const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);
        const World::Offset& offset = m_observer->m_offset;

        auto&& currentRegion = SR_MATH_NS::IVector3(m_observer->m_targetPosition / chunkSize);

        if (currentRegion.x == 0) { currentRegion.x = -1; }
        if (currentRegion.y == 0) { currentRegion.y = -1; }
        if (currentRegion.z == 0) { currentRegion.z = -1; }

        auto&& currentChunk = AddOffset(
                currentRegion,
                -offset.m_chunk
        );

        SRAssertOnce(!currentChunk.HasZero());

        return currentChunk;
    }
}
