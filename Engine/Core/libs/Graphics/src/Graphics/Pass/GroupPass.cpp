//
// Created by Monika on 22.07.2022.
//

#include <Graphics/Pass/GroupPass.h>

namespace SR_GRAPH_NS {
    GroupPass::~GroupPass() {
        for (auto&& pPass : m_passes) {
            delete pPass;
        }
        m_passes.clear();
    }

    bool GroupPass::Load(const SR_XML_NS::Node &passNode) {
        SR_TRACY_ZONE;

        for (auto&& subPassNode : passNode.TryGetNodes()) {
            if (auto&& pPass = SR_ALLOCATE_RENDER_PASS(subPassNode)) {
                m_passes.emplace_back(pPass);
            }
            else {
                SR_ERROR("GroupPass::Load() : failed to load \"" + subPassNode.Name() + "\" pass!");
            }
        }

        return BasePass::Load(passNode);
    }

    bool GroupPass::Init() {
        SR_TRACY_ZONE;

        for (auto&& pPass : m_passes) {
            pPass->Init();
        }

        return BasePass::Init();
    }

    void GroupPass::DeInit() {
        SR_TRACY_ZONE;

        for (auto&& pPass : m_passes) {
            pPass->DeInit();
        }

        BasePass::DeInit();
    }

    void GroupPass::Prepare() {
        SR_TRACY_ZONE;

        for (auto&& pPass : m_passes) {
            pPass->Prepare();
        }

        BasePass::Prepare();
    }

    bool GroupPass::PreRender() {
        SR_TRACY_ZONE;

        bool hasDrawData = false;
        for (auto&& pPass : m_passes) {
            hasDrawData |= pPass->PreRender();
        }

        return hasDrawData;
    }

    bool GroupPass::Render() {
        SR_TRACY_ZONE;

        bool hasDrawData = false;
        for (auto&& pPass : m_passes) {
            SR_TRACY_ZONE_S(pPass->GetName().data());
            hasDrawData |= pPass->Render();
        }

        return hasDrawData;
    }

    bool GroupPass::PostRender() {
        bool hasDrawData = false;
        for (auto&& pPass : m_passes) {
            SR_TRACY_ZONE_S(pPass->GetName().data());
            hasDrawData |= pPass->PostRender();
        }

        return hasDrawData;
    }

    void GroupPass::Update() {
        for (auto&& pPass : m_passes) {
            SR_TRACY_ZONE_S(pPass->GetName().data());
            pPass->Update();
        }

        BasePass::Update();
    }

    bool GroupPass::Overlay() {
        bool hasDrawData = false;
        for (auto&& pPass : m_passes) {
            SR_TRACY_ZONE_S(pPass->GetName().data());
            hasDrawData |= pPass->Overlay();
        }

        return hasDrawData;
    }

    void GroupPass::OnResize(const SR_MATH_NS::UVector2 &size) {
        for (auto&& pPass : m_passes) {
            SR_TRACY_ZONE_S(pPass->GetName().data());
            pPass->OnResize(size);
        }

        BasePass::OnResize(size);
    }

    void GroupPass::OnMeshAdded(SR_GTYPES_NS::Mesh *pMesh, bool transparent) {
        for (auto&& pPass : m_passes) {
            pPass->OnMeshAdded(pMesh, transparent);
        }

        BasePass::OnMeshAdded(pMesh, transparent);
    }

    void GroupPass::OnMeshRemoved(SR_GTYPES_NS::Mesh *pMesh, bool transparent) {
        for (auto&& pPass : m_passes) {
            pPass->OnMeshRemoved(pMesh, transparent);
        }

        BasePass::OnMeshRemoved(pMesh, transparent);
    }

    bool GroupPass::ForEachPass(const SR_HTYPES_NS::Function<bool(BasePass*)>& callback) const {
        for (auto&& pPass : m_passes) {
            if (!callback(pPass)) {
                return false;
            }

            if (auto&& pGroupPass = dynamic_cast<GroupPass*>(pPass)) {
                if (!pGroupPass->ForEachPass(callback)) {
                    return false;
                }
            }
        }
        return true;
    }

    BasePass *GroupPass::FindPass(const SR_UTILS_NS::StringAtom& name) const {
        for (auto&& pPass : m_passes) {
            if (auto&& pGroupPass = dynamic_cast<GroupPass*>(pPass)) {
                if (auto&& pFoundPass = pGroupPass->FindPass(name)) {
                    return pFoundPass;
                }
            }

            if (pPass->GetName() != name) {
                continue;
            }

            return pPass;
        }

        return nullptr;
    }

    void GroupPass::OnSamplesChanged() {
        for (auto&& pPass : m_passes) {
            pPass->OnSamplesChanged();
        }
        BasePass::OnSamplesChanged();
    }

    void GroupPass::SetRenderTechnique(RenderTechnique* pRenderTechnique) {
        for (auto&& pPass : m_passes) {
            pPass->SetRenderTechnique(pRenderTechnique);
        }
        BasePass::SetRenderTechnique(pRenderTechnique);
    }
}