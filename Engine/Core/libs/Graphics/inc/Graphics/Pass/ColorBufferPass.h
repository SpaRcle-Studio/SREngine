//
// Created by Monika on 10.10.2022.
//

#ifndef SRENGINE_COLORBUFFERPASS_H
#define SRENGINE_COLORBUFFERPASS_H

#include <Graphics/Pass/ShaderOverridePass.h>

namespace SR_GRAPH_NS {
    class ColorBufferPass : public ShaderOverridePass {
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using Super = ShaderOverridePass;
    public:
        explicit ColorBufferPass(RenderTechnique* pTechnique, BasePass* pParent);

    public:
        void Update() override;

        SR_NODISCARD MeshPtr GetMesh(float_t x, float_t y) const;
        SR_NODISCARD uint32_t GetIndex(float_t x, float_t y) const;
        SR_NODISCARD SR_MATH_NS::FColor GetColor(float_t x, float_t y) const;
        SR_NODISCARD MeshClusterTypeFlag GetClusterType() const noexcept override;

    protected:
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;
        void UseSharedUniforms(ShaderPtr pShader) override;

        void SetMeshIndex(MeshPtr pMesh, uint32_t colorId);

    private:
        std::vector<MeshPtr> m_table;
        uint32_t m_colorId = 0;

    };
}

#endif //SRENGINE_COLORBUFFERPASS_H
