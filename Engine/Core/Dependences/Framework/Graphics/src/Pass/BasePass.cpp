//
// Created by Monika on 17.07.2022.
//

#include <Pass/BasePass.h>
#include <Environment/Environment.h>
#include <Render/RenderTechnique.h>
#include <Render/RenderContext.h>
#include <Render/RenderScene.h>

namespace SR_GRAPH_NS {
    RenderPassMap& GetRenderPassMap() {
        static RenderPassMap renderPassMap;
        return renderPassMap;
    }

    BasePass::BasePass(RenderTechnique* pTechnique)
        : m_technique(pTechnique)
        , m_context(nullptr)
        , m_pipeline(Environment::Get())
        , m_camera(nullptr)
        , m_uboManager(Memory::UBOManager::Instance())
        , m_isInit(false)
    { }

    bool BasePass::Load(const SR_XML_NS::Node &passNode) {
        m_name = passNode.Name();
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
}