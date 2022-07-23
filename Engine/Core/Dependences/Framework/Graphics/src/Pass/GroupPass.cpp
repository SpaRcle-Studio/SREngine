//
// Created by Monika on 22.07.2022.
//

#include <Pass/GroupPass.h>

namespace SR_GRAPH_NS {
    GroupPass::GroupPass(RenderTechnique *pTechnique)
        : BasePass(pTechnique)
    { }

    GroupPass::~GroupPass() {
        for (auto&& pPass : m_passes) {
            delete pPass;
        }
        m_passes.clear();
    }

    bool GroupPass::Load(const SR_XML_NS::Node &passNode) {
        for (auto&& subPassNode : passNode.GetNodes()) {
            if (auto&& pPass = SR_ALLOCATE_RENDER_PASS(GetTechnique(), subPassNode)) {
                m_passes.emplace_back(pPass);
            }
            else {
                SR_ERROR("GroupPass::Load() : failed to load \"" + subPassNode.Name() + "\" pass!");
            }
        }

        return BasePass::Load(passNode);
    }

    bool GroupPass::Init() {
        for (auto&& pPass : m_passes) {
            pPass->Init();
        }

        return BasePass::Init();
    }

    void GroupPass::DeInit() {
        for (auto&& pPass : m_passes) {
            pPass->DeInit();
        }

        BasePass::DeInit();
    }

    void GroupPass::PreRender() {
        for (auto&& pPass : m_passes) {
            pPass->PreRender();
        }

        BasePass::PreRender();
    }

    void GroupPass::Render() {
        for (auto&& pPass : m_passes) {
            pPass->Render();
        }

        BasePass::Render();
    }

    void GroupPass::PostRender() {
        for (auto&& pPass : m_passes) {
            pPass->PostRender();
        }

        BasePass::PostRender();
    }

    void GroupPass::Update() {
        for (auto&& pPass : m_passes) {
            pPass->Update();
        }

        BasePass::Update();
    }

    void GroupPass::Overlay() {
        for (auto&& pPass : m_passes) {
            pPass->Overlay();
        }

        BasePass::Overlay();
    }

    void GroupPass::OnResize(const SR_MATH_NS::IVector2 &size) {
        for (auto&& pPass : m_passes) {
            pPass->OnResize(size);
        }

        BasePass::OnResize(size);
    }
}