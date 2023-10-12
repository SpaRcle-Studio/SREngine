//
// Created by Monika on 17.07.2022.
//

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderScene.h>

namespace SR_GRAPH_NS {
    RenderPassMap& GetRenderPassMap() {
        static RenderPassMap renderPassMap;
        return renderPassMap;
    }

    BasePass::BasePass()
        : Super()
        , m_uboManager(Memory::UBOManager::Instance())
    { }

    bool BasePass::Load(const SR_XML_NS::Node &passNode) {
        /// Некоторые проходы имеют свое уникальное имя, нужное для поиска.
        SetName(passNode.TryGetAttribute("Name").ToString(passNode.Name()));
        return true;
    }

    bool BasePass::Init() {
        SRAssert2(!m_isInit, "Pass already initialized!");

        m_context = m_technique->GetContext();
        m_camera = m_technique->GetCamera();

        m_isInit = true;

        return true;
    }

    void BasePass::DeInit() {
        SRAssert2(m_isInit, "Pass isn't initialized!");

        m_isInit = false;
    }

    BasePass::RenderScenePtr BasePass::GetRenderScene() const {
        return m_technique->GetRenderScene();
    }

    std::string_view BasePass::GetName() const {
        return m_name;
    }

    void BasePass::SetRenderTechnique(RenderTechnique* pRenderTechnique) {
        SRAssert(pRenderTechnique);
        m_technique = pRenderTechnique;
        m_pipeline = m_technique ? m_technique->GetPipeline() : nullptr;
    }

    void BasePass::SetName(const std::string& name) {
        m_name = name;
        m_hashName = SR_HASH_STR(name);
    }

    void StartPassNode::InitNode() {
        IExecutableNode::InitNode();
        AddOutputData<SR_SRLM_NS::DataTypeFlow>();
    }
}