//
// Created by Monika on 25.01.2024.
//

#ifndef SR_ENGINE_OFF_SCREEN_MESH_DRAWER_PASS_H
#define SR_ENGINE_OFF_SCREEN_MESH_DRAWER_PASS_H

#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Pass/MeshDrawerPass.h>

namespace SR_GRAPH_NS {
    class OffScreenMeshDrawerPass : public IFramebufferPass, public MeshDrawerPass {
    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        bool Init() override;
        void OnResize(const SR_MATH_NS::UVector2 &size) override;

        bool Render() override;
        void Update() override;

        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;

        SR_NODISCARD IRenderTechnique* GetFrameBufferRenderTechnique() const override { return GetTechnique(); }

    protected:
        void RenderFrameBufferInner() override;
        void UpdateFrameBufferInner() override;

    };
}

#endif //SR_ENGINE_OFF_SCREEN_MESH_DRAWER_PASS_H
