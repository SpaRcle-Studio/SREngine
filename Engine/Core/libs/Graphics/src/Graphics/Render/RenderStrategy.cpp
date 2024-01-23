//
// Created by Monika on 20.01.2024.
//

#include <Graphics/Render/RenderStrategy.h>

#include <Utils/ECS/LayerManager.h>

namespace SR_GRAPH_NS {
    RenderStrategy::RenderStrategy(RenderScene* pRenderScene)
        : Super()
        , m_renderScene(pRenderScene)
    { }

    RenderStrategy::~RenderStrategy() {
        SRAssert(m_layers.empty());
        SRAssert(m_meshCount == 0);
    }

    RenderContext* RenderStrategy::GetRenderContext() const {
        return m_renderScene->GetContext();
    }

    bool RenderStrategy::Render() {
        SR_TRACY_ZONE;

        m_errors.clear();

        bool isRendered = false;

        SR_MAYBE_UNUSED auto&& guard = SR_UTILS_NS::LayerManager::Instance().ScopeLockSingleton();

        auto&& layers = SR_UTILS_NS::LayerManager::Instance().GetLayers();

        for (auto&& layer : layers) {
            SR_TRACY_ZONE_S(layer.c_str());

            if (m_layerFilter && !m_layerFilter(layer)) {
                continue;
            }

            if (auto&& pIt = m_layers.find(layer); pIt != m_layers.end()) {
                isRendered |= pIt->second->Render();
            }
        }

        GetRenderContext()->GetPipeline()->ResetLastShader();

        return isRendered;
    }

    void RenderStrategy::Update() {
        SR_TRACY_ZONE;

        SR_MAYBE_UNUSED auto&& guard = SR_UTILS_NS::LayerManager::Instance().ScopeLockSingleton();

        for (auto&& [layer, pStage] : m_layers) {
            SR_TRACY_ZONE_S(layer.c_str());

            if (!SR_UTILS_NS::LayerManager::Instance().HasLayer(layer)) {
                SetError(SR_FORMAT("Layer \"{}\" is not registered!", layer.c_str()));
            }

            if (m_layerFilter && !m_layerFilter(layer)) {
                continue;
            }

            pStage->Update();
        }
    }

    void RenderStrategy::RegisterMesh(SR_GTYPES_NS::Mesh* pMesh) {
        SR_TRACY_ZONE;

        if (pMesh->IsMeshRegistered()) {
            SRHalt("Double mesh registration!");
            return;
        }

        MeshRegistrationInfo info;

        info.pMesh = pMesh;
        info.pShader = pMesh->GetShader();
        info.layer = pMesh->GetMeshLayer();
        info.VBO = pMesh->GetVBO();
        info.pScene = GetRenderScene();

        if (pMesh->HasSortingPriority()) {
            info.priority = pMesh->GetSortingPriority();
        }
        else {
            info.priority = std::nullopt;
        }

        RegisterMesh(info);
    }

    void RenderStrategy::UnRegisterMesh(SR_GTYPES_NS::Mesh* pMesh) {
        SR_TRACY_ZONE;

        if (!pMesh->IsMeshRegistered()) {
            SRHalt("Mesh is not registered!");
            return;
        }

        UnRegisterMesh(pMesh->GetMeshRegistrationInfo());
    }

    bool RenderStrategy::IsPriorityAllowed(int64_t priority) const {
        SR_TRACY_ZONE;
        return !m_priorityCallback || m_priorityCallback(priority);
    }

    RenderStrategy::ShaderPtr RenderStrategy::ReplaceShader(RenderStrategy::ShaderPtr pShader) const {
        SR_TRACY_ZONE;
        return m_shaderReplaceCallback ? m_shaderReplaceCallback(pShader) : pShader;
    }

    void RenderStrategy::UseSharedUniforms(RenderStrategy::ShaderPtr pShader) {
        SR_TRACY_ZONE;

        if (m_sharedUniformsCallback) {
            m_sharedUniformsCallback(pShader);
        }
    }

    void RenderStrategy::UseConstants(RenderStrategy::ShaderPtr pShader) {
        SR_TRACY_ZONE;

        if (m_constantsCallback) {
            m_constantsCallback(pShader);
        }
    }

    void RenderStrategy::UseSamplers(RenderStrategy::ShaderPtr pShader) {
        SR_TRACY_ZONE;

        if (m_samplersCallback) {
            m_samplersCallback(pShader);
        }
    }

    void RenderStrategy::UseUniforms(ShaderPtr pShader, MeshPtr pMesh) {
        SR_TRACY_ZONE;

        if (m_uniformsCallback) {
            m_uniformsCallback(pShader, pMesh);
        }
    }

    void RenderStrategy::RegisterMesh(const MeshRegistrationInfo& info) {
        if (auto&& pIt = m_layers.find(info.layer); pIt != m_layers.end()) {
            if (!pIt->second->RegisterMesh(info)) {
                return;
            }
        }
        else {
            auto&& pLayerStage = new LayerRenderStage(this);
            if (!pLayerStage->RegisterMesh(info)) {
                delete pLayerStage;
                return;
            }
            m_layers[info.layer] = pLayerStage;
        }

        info.pMesh->SetMeshRegistrationInfo(info);
        ++m_meshCount;
    }

    void RenderStrategy::UnRegisterMesh(const MeshRegistrationInfo& info) {
        if (auto&& pLayerIt = m_layers.find(info.layer); pLayerIt != m_layers.end()) {
            pLayerIt->second->UnRegisterMesh(info);
            if (pLayerIt->second->IsEmpty()) {
                delete pLayerIt->second;
                m_layers.erase(pLayerIt);
            }
        }
        else {
            SRHalt("Layer \"{}\" not found!", info.layer.c_str());
        }

        info.pMesh->SetMeshRegistrationInfo(std::nullopt);

        SRAssert(m_meshCount != 0);
        --m_meshCount;
    }

    void RenderStrategy::ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const {
        SR_TRACY_ZONE;

        for (auto&& [layer, pStage] : m_layers) {
            pStage->ForEachMesh(callback);
        }
    }

    void RenderStrategy::OnResourceReloaded(SR_UTILS_NS::IResource* pResource) const {
        SR_TRACY_ZONE;

        std::list<MeshPtr> meshesToReRegister;

        ForEachMesh([pResource, &meshesToReRegister](auto&& pMesh) {
            if (pMesh->OnResourceReloaded(pResource)) {
                meshesToReRegister.emplace_back(pMesh);
            }
        });

        for (auto&& pMesh : meshesToReRegister) {
            pMesh->ReRegisterMesh();
        }
    }

    /// ----------------------------------------------------------------------------------------------------------------

    bool LayerRenderStage::Render() {
        SR_TRACY_ZONE;

        m_isRendered = false;

        for (auto&& pStage : m_priorityStages) {
            if (m_renderStrategy->IsPriorityAllowed(pStage->GetPriority())) {
                m_isRendered |= pStage->Render();
            }
        }

        for (auto&& [pShader, pShaderStage] : m_shaderStages) {
            m_isRendered |= pShaderStage->Render();
        }

        return IsRendered();
    }

    void LayerRenderStage::Update() {
        SR_TRACY_ZONE;

        if (!IsRendered()) {
            return;
        }

        for (auto&& pPriorityStage : m_priorityStages) {
            if (m_renderStrategy->IsPriorityAllowed(pPriorityStage->GetPriority())) {
                pPriorityStage->Update();
            }
        }

        for (auto&& [pShader, pShaderStage] : m_shaderStages) {
            pShaderStage->Update();
        }
    }

    bool LayerRenderStage::RegisterMesh(const MeshRegistrationInfo& info) {
        SR_TRACY_ZONE;

        if (info.priority.has_value()) {
            const int64_t index = FindPriorityStageIndex(info.priority.value(), false);

            if (index == SR_ID_INVALID) {
                auto&& pStage = new PriorityRenderStage(m_renderStrategy, info.priority.value());
                if (!pStage->RegisterMesh(info)) {
                    delete pStage;
                    return false;
                }
                InsertPriorityStage(pStage);
                return true;
            }

            return m_priorityStages[index]->RegisterMesh(info);
        }

        if (auto&& pIt = m_shaderStages.find(info.pShader); pIt != m_shaderStages.end()) {
            return pIt->second->RegisterMesh(info);
        }
        else {
            auto&& pStage = new ShaderRenderStage(m_renderStrategy, info.pShader);
            if (!pStage->RegisterMesh(info)) {
                delete pStage;
                return false;
            }
            m_shaderStages[info.pShader] = pStage;
        }

        return true;
    }

    void LayerRenderStage::UnRegisterMesh(const MeshRegistrationInfo& info) {
        if (info.priority.has_value()) {
            const int64_t index = FindPriorityStageIndex(info.priority.value(), false);
            if (index == SR_ID_INVALID) {
                SRHalt("Priority {} not found!", info.priority.value());
                return;
            }

            m_priorityStages[index]->UnRegisterMesh(info);

            if (m_priorityStages[index]->IsEmpty()) {
                delete m_priorityStages[index];

                memcpy(
                m_priorityStages.data() + index,
                m_priorityStages.data() + index + 1,
                ((m_priorityStages.size() - index) - 1) * sizeof(void *)
                );

                m_priorityStages.resize(m_priorityStages.size() - 1);
            }
        }
        else {
            if (auto&& pIt = m_shaderStages.find(info.pShader); pIt != m_shaderStages.end()) {
                pIt->second->UnRegisterMesh(info);
                if (pIt->second->IsEmpty()) {
                    delete pIt->second;
                    m_shaderStages.erase(pIt);
                }
            }
            else {
                SRHalt("Shader not found!");
            }
        }
    }

    int64_t LayerRenderStage::FindPriorityStageIndex(int64_t priority, bool nearest) const {
        if (m_priorityStages.empty()) {
            return SR_ID_INVALID;
        }

        auto&& pIt = std::lower_bound(m_priorityStages.begin(), m_priorityStages.end(), priority, [](auto&& pLeft, auto&& right) -> bool {
            return pLeft->GetPriority() < right;
        });

        if (pIt == m_priorityStages.end()) {
            return SR_ID_INVALID;
        }

        if (!nearest && (*pIt)->GetPriority() != priority) {
            return SR_ID_INVALID;
        }

        return std::distance(m_priorityStages.begin(), pIt);
    }

    void LayerRenderStage::InsertPriorityStage(PriorityRenderStage* pStage) {
        if (m_priorityStages.empty()) {
            m_priorityStages.emplace_back(pStage);
            return;
        }

        const auto priority = pStage->GetPriority();

        if (priority <= m_priorityStages.front()->GetPriority()) {
            m_priorityStages.resize(m_priorityStages.size() + 1);
            memcpy(m_priorityStages.data() + 1, m_priorityStages.data(), (m_priorityStages.size() - 1) * sizeof(void*));
            m_priorityStages[0] = pStage;
            return;
        }

        if (priority >= m_priorityStages.back()->GetPriority()) {
            m_priorityStages.emplace_back(pStage);
            return;
        }

        const int64_t index = FindPriorityStageIndex(priority, true);
        if (index == SR_ID_INVALID) {
            SRHalt("Invalid index!");
            return;
        }

        m_priorityStages.resize(m_priorityStages.size() + 1);

        memcpy(
            m_priorityStages.data() + index + 1,
            m_priorityStages.data() + index,
            ((m_priorityStages.size() - index) - 1) * sizeof(void*)
        );

        m_priorityStages[index] = pStage;
    }

    void LayerRenderStage::ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const {
        for (auto&& pStage : m_priorityStages) {
            pStage->ForEachMesh(callback);
        }

        for (auto&& [pShader, pStage] : m_shaderStages) {
            pStage->ForEachMesh(callback);
        }
    }

    /// ----------------------------------------------------------------------------------------------------------------

    bool PriorityRenderStage::Render() {
        SR_TRACY_ZONE;

        m_isRendered = false;

        for (auto&& [pShader, pShaderStage] : m_shaderStages) {
            m_isRendered |= pShaderStage->Render();
        }

        return IsRendered();
    }

    void PriorityRenderStage::Update() {
        SR_TRACY_ZONE;

        if (!IsRendered()) {
            return;
        }

        for (auto&& [pShader, pShaderStage] : m_shaderStages) {
            pShaderStage->Update();
        }
    }

    bool PriorityRenderStage::RegisterMesh(const MeshRegistrationInfo& info) {
        SR_TRACY_ZONE;

        if (auto&& pIt = m_shaderStages.find(info.pShader); pIt != m_shaderStages.end()) {
            return pIt->second->RegisterMesh(info);
        }
        else {
            auto&& pStage = new ShaderRenderStage(m_renderStrategy, info.pShader);
            if (!pStage->RegisterMesh(info)) {
                delete pStage;
                return false;
            }
            m_shaderStages[info.pShader] = pStage;
        }

        return true;
    }

    void PriorityRenderStage::UnRegisterMesh(const MeshRegistrationInfo& info) {
        if (auto&& pIt = m_shaderStages.find(info.pShader); pIt != m_shaderStages.end()) {
            pIt->second->UnRegisterMesh(info);
            if (pIt->second->IsEmpty()) {
                delete pIt->second;
                m_shaderStages.erase(pIt);
            }
        }
        else {
            SRHalt("Shader not found!");
        }
    }

    void PriorityRenderStage::ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const {
        for (auto&& [pShader, pStage] : m_shaderStages) {
            pStage->ForEachMesh(callback);
        }
    }

    /// ----------------------------------------------------------------------------------------------------------------

    ShaderRenderStage::ShaderRenderStage(RenderStrategy* pRenderStrategy, SR_GTYPES_NS::Shader* pShader)
        : Super(pRenderStrategy)
        , m_shader(pShader)
    {
        if (m_shader) {
            m_shader->AddUsePoint();
        }
    }

    ShaderRenderStage::~ShaderRenderStage() {
        SRAssert(m_VBOStages.empty());
        if (m_shader) {
            m_shader->RemoveUsePoint();
        }
    }

    bool ShaderRenderStage::Render() {
        SR_TRACY_ZONE;

        m_isRendered = false;

        if (!IsValid()) {
            m_renderStrategy->SetError("Shader is nullptr!");
            return false;
        }

        auto&& pShader = m_renderStrategy->ReplaceShader(m_shader);
        if (!pShader || !HasActiveMesh()) {
            return false;
        }

        SR_TRACY_TEXT_N("Shader", pShader->GetResourcePath().ToStringRef());

        if (pShader->Use() == ShaderBindResult::Failed) {
            return false;
        }

        if (GetRenderContext()->GetPipeline()->IsShaderChanged()) {
            m_renderStrategy->UseConstants(pShader);
            m_renderStrategy->UseSamplers(pShader);
        }

        if (!pShader->IsSamplersValid()) {
            m_renderStrategy->SetError("Shader samplers is not valid!");
            pShader->UnUse();
            return false;
        }

        for (auto&& [VBO, pStage] : m_VBOStages) {
            m_isRendered |= pStage->Render();
        }

        pShader->UnUse();

        return IsRendered();
    }

    void ShaderRenderStage::Update() {
        SR_TRACY_ZONE;

        if (!IsRendered()) {
            return;
        }

        auto&& pShader = m_renderStrategy->ReplaceShader(m_shader);
        if (!pShader) {
            return;
        }

        if (!pShader || !pShader->Ready() || !pShader->IsAvailable()) {
            return;
        }

        SR_TRACY_TEXT_N("Shader", pShader->GetResourcePath().ToStringRef());

        GetRenderContext()->SetCurrentShader(pShader);

        m_renderStrategy->UseSharedUniforms(pShader);

        for (auto&& [VBO, pVBOStage] : m_VBOStages) {
            pVBOStage->Update(pShader);
        }

        GetRenderScene()->SetCurrentSkeleton(nullptr);
        GetRenderContext()->SetCurrentShader(nullptr);
    }

    bool ShaderRenderStage::HasActiveMesh() const {
        SR_TRACY_ZONE;

        if (!m_renderStrategy->IsNeedCheckMeshActivity()) {
            return true;
        }

        for (auto&& [VBO, pVBOStage] : m_VBOStages) {
            if (pVBOStage->HasActiveMesh()) {
                return true;
            }
        }

        return false;
    }

    bool ShaderRenderStage::RegisterMesh(const MeshRegistrationInfo& info) {
        SR_TRACY_ZONE;

        if (auto&& pIt = m_VBOStages.find(info.VBO); pIt != m_VBOStages.end()) {
            return pIt->second->RegisterMesh(info);
        }
        else {
            auto&& pStage = new VBORenderStage(m_renderStrategy, info.VBO);
            if (!pStage->RegisterMesh(info)) {
                delete pStage;
                return false;
            }
            m_VBOStages[info.VBO] = pStage;
        }

        return true;
    }

    void ShaderRenderStage::UnRegisterMesh(const MeshRegistrationInfo &info) {
        if (auto&& pIt = m_VBOStages.find(info.VBO); pIt != m_VBOStages.end()) {
            pIt->second->UnRegisterMesh(info);
            if (pIt->second->IsEmpty()) {
                delete pIt->second;
                m_VBOStages.erase(pIt);
            }
        }
        else {
            SRHalt("VBO {} not found!", info.VBO);
        }
    }

    void ShaderRenderStage::ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const {
        for (auto&& [VBO, pStage] : m_VBOStages) {
            pStage->ForEachMesh(callback);
        }
    }

    /// ----------------------------------------------------------------------------------------------------------------

    RenderContext* IRenderStage::GetRenderContext() const {
        return m_renderStrategy->GetRenderContext();
    }

    RenderScene* IRenderStage::GetRenderScene() const {
        return m_renderStrategy->GetRenderScene();
    }

    /// ----------------------------------------------------------------------------------------------------------------

    VBORenderStage::VBORenderStage(RenderStrategy* pRenderStrategy, int32_t VBO)
        : Super(pRenderStrategy)
        , m_uboManager(SR_GRAPH_NS::Memory::UBOManager::Instance())
        , m_VBO(VBO)
    {
        m_meshes.reserve(64);
    }

    bool VBORenderStage::HasActiveMesh() const {
        SR_TRACY_ZONE;

        for (auto&& pMesh : m_meshes) {
            if (pMesh->IsMeshActive()) {
                return true;
            }
        }

        return false;
    }

    bool VBORenderStage::Render() {
        SR_TRACY_ZONE;

        m_isRendered = false;

        if (!IsValid()) {
            m_renderStrategy->SetError("VBO is not valid!");
            return false;
        }

        if ((m_isRendered = !m_meshes.empty())) {
            if (!m_meshes[0]->BindMesh()) {
                return false;
            }
        }

        for (auto&& pMesh : m_meshes) {
            pMesh->Draw();
        }

        return IsRendered();
    }

    void VBORenderStage::Update(ShaderPtr pShader) {
        SR_TRACY_ZONE;

        if (!IsRendered()) {
            return;
        }

        for (auto&& pMesh : m_meshes) {
            if (!pMesh->IsMeshActive()) {
                continue;
            }

            auto&& virtualUbo = pMesh->GetVirtualUBO();
            if (virtualUbo == SR_ID_INVALID) {
                continue;
            }

            m_renderStrategy->UseUniforms(pShader, pMesh);

            if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                SR_ERROR("VBORenderStage::Update() : memory has been duplicated!");
            }

            pShader->Flush();
        }
    }

    bool VBORenderStage::RegisterMesh(const MeshRegistrationInfo& info) {
        SR_TRACY_ZONE;
        m_meshes.emplace_back(info.pMesh);
        return true;
    }

    void VBORenderStage::UnRegisterMesh(const MeshRegistrationInfo& info) {
        if (auto&& pIt = std::find(m_meshes.begin(), m_meshes.end(), info.pMesh); pIt != m_meshes.end()) {
            m_meshes.erase(pIt);
            return;
        }

        SRHalt("VBO {} not found!", info.VBO);
    }

    void VBORenderStage::ForEachMesh(const SR_HTYPES_NS::Function<void(MeshPtr)>& callback) const {
        for (auto&& pMesh : m_meshes) {
            if (!pMesh) {
                continue;
            }
            callback(pMesh);
        }
    }
}