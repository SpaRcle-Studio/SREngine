//
// Created by Monika on 18.01.2024.
//

#ifndef SR_ENGINE_MESH_DRAWER_PASS_H
#define SR_ENGINE_MESH_DRAWER_PASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/SRSL/ShaderType.h>

namespace SR_GRAPH_NS {
    class RenderStrategy;

    class CascadedShadowMapPass;
    class ShadowMapPass;

    class MeshDrawerPass : public BasePass {
        SR_REGISTER_LOGICAL_NODE(MeshDrawerPass, Mesh Drawer Pass, { "Passes" })
        using Super = BasePass;
        struct Sampler {
            uint32_t textureId = SR_ID_INVALID;
            uint32_t fboId = SR_ID_INVALID;
            SR_UTILS_NS::StringAtom id;
            SR_UTILS_NS::StringAtom fboName;
            uint64_t index = 0;
            bool depth = false;
        };
        using Samplers = std::vector<Sampler>;
    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        bool Init() override;
        void DeInit() override;
        void Prepare() override;
        void Bind() override;
        bool Render() override;
        void Update() override;

        bool HasPreRender() const noexcept override { return false; }
        bool HasPostRender() const noexcept override { return false; }

    protected:
        virtual void UseUniforms(ShaderPtr pShader, MeshPtr pMesh);
        virtual void UseSharedUniforms(ShaderPtr pShader);
        virtual void UseConstants(ShaderPtr pShader);
        virtual void UseSamplers(ShaderPtr pShader);

        void OnResize(const SR_MATH_NS::UVector2& size) override;
        void OnSamplesChanged() override;

    private:
        void PrepareSamplers();
        void ClearOverrideShaders();

        ShaderPtr ReplaceShader(ShaderPtr pShader) const;

        bool IsLayerAllowed(SR_UTILS_NS::StringAtom layer) const;

        SR_NODISCARD RenderStrategy* GetRenderStrategy() const;

    private:
        bool m_useMaterials = true;

        bool m_passWasRendered = false;

        bool m_dirtySamplers = true;
        bool m_needUpdateMeshes = false;

        ShadowMapPass* m_shadowMapPass = nullptr;
        CascadedShadowMapPass* m_cascadedShadowMapPass = nullptr;

        Samplers m_samplers;

        std::map<ShaderPtr, ShaderPtr> m_shaderReplacements;
        std::map<SR_SRSL_NS::ShaderType, ShaderPtr> m_shaderTypeReplacements;
        std::set<SR_UTILS_NS::StringAtom> m_allowedLayers;
        std::set<SR_UTILS_NS::StringAtom> m_disallowedLayers;

    };
}

#endif //SR_ENGINE_MESH_DRAWER_PASS_H
