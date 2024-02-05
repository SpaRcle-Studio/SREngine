//
// Created by Monika on 25.01.2024.
//

#include <Graphics/Pass/OffScreenMeshDrawerPass.h>
#include <Graphics/Types/Framebuffer.h>

namespace SR_GRAPH_NS {
    bool OffScreenMeshDrawerPass::Load(const SR_XML_NS::Node& passNode) {
        LoadFramebufferSettings(passNode);
        return MeshDrawerPass::Load(passNode);
    }

    std::vector<SR_GTYPES_NS::Framebuffer*> OffScreenMeshDrawerPass::GetFrameBuffers() const {
        if (!GetFramebuffer()) {
            return std::vector<SR_GTYPES_NS::Framebuffer*>(); /// NOLINT
        }
        return { GetFramebuffer() };
    }

    bool OffScreenMeshDrawerPass::Init() {
        return MeshDrawerPass::Init();
    }

    void OffScreenMeshDrawerPass::OnResize(const SR_MATH_NS::UVector2& size) {
        MeshDrawerPass::OnResize(size);
    }

    bool OffScreenMeshDrawerPass::Render() {
        return RenderFrameBuffer(GetPassPipeline());
    }

    void OffScreenMeshDrawerPass::Update() {
        UpdateFrameBuffer(GetPassPipeline());
    }

    void OffScreenMeshDrawerPass::RenderFrameBufferInner() {
        MeshDrawerPass::Render();
    }

    void OffScreenMeshDrawerPass::UpdateFrameBufferInner() {
        MeshDrawerPass::Update();
    }
}