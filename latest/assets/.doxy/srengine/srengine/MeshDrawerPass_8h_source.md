

# File MeshDrawerPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**MeshDrawerPass.h**](MeshDrawerPass_8h.md)

[Go to the documentation of this file](MeshDrawerPass_8h.md)


```C++
//
// Created by Monika on 18.01.2024.
//

#ifndef SR_ENGINE_MESH_DRAWER_PASS_H
#define SR_ENGINE_MESH_DRAWER_PASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Pass/ISamplersPass.h>
#include <Graphics/Render/RenderPredicates.h>
#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/SRSL/ShaderType.h>

namespace SR_GRAPH_NS {
    class RenderStrategy;
    class RenderQueue;
    class CascadedShadowMapPass;
    class ShadowMapPass;

    class MeshDrawerPass : public BasePass, public ISamplersPass, public LayerFilterPredicate, public ShaderReplacePredicate, public PriorityFilterPredicate {
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
        using RenderQueuePtr = SR_HTYPES_NS::SharedPtr<RenderQueue>;

    public:
        MeshDrawerPass();
        ~MeshDrawerPass() override;

        bool Load(const SR_XML_NS::Node& passNode) override;

        bool Init() override;
        void DeInit() override;
        void Prepare() override;
        bool Render() override;
        void Update() override;

        SR_NODISCARD bool HasPreRender() const noexcept override { return false; }
        SR_NODISCARD bool HasPostRender() const noexcept override { return false; }
        SR_NODISCARD virtual bool IsNeedUpdate() const noexcept { return false; }
        SR_NODISCARD virtual bool IsNeedUseMaterials() const noexcept { return m_useMaterials; }
        SR_NODISCARD virtual uint8_t GetMeshDrawerFBOLayers() const noexcept { return 1; }

        virtual void UseUniforms(ShaderUseInfo info, MeshPtr pMesh);
        virtual void UseSharedUniforms(ShaderUseInfo info);
        virtual void UseConstants(ShaderUseInfo info);

        SR_NODISCARD ShaderUseInfo ReplaceShader(ShaderPtr pShader) const override;
        SR_NODISCARD bool IsLayerAllowed(SR_UTILS_NS::StringAtom layer) const override;
        SR_NODISCARD bool IsPriorityAllowed(int64_t priority) const override { return true; }

        SR_NODISCARD const std::vector<RenderQueuePtr>& GetRenderQueues() const noexcept { return m_renderQueues; }

    protected:
        void OnResize(const SR_MATH_NS::UVector2& size) override;
        void OnMultisampleChanged() override;
        void OnSamplersChanged() override;
        void SetRenderTechnique(IRenderTechnique* pRenderTechnique) override;

        SR_NODISCARD RenderStrategy* GetRenderStrategy() const;
        SR_NODISCARD virtual RenderQueuePtr AllocateRenderQueue();

    private:
        void ClearOverrideShaders();

    private:
        bool m_useMaterials = true;
        bool m_passWasRendered = false;

        std::vector<RenderQueuePtr> m_renderQueues;

        ShadowMapPass* m_shadowMapPass = nullptr;
        CascadedShadowMapPass* m_cascadedShadowMapPass = nullptr;

        SR_HTYPES_NS::Time& m_time;

        std::vector<SR_UTILS_NS::StringAtom> m_materialVariants;
        ska::flat_hash_map<ShaderPtr, ShaderUseInfo> m_shaderReplacements;
        ska::flat_hash_map<SR_SRSL_NS::ShaderType, ShaderUseInfo> m_shaderTypeReplacements;
        std::set<SR_UTILS_NS::StringAtom> m_allowedLayers;
        std::set<SR_UTILS_NS::StringAtom> m_disallowedLayers;

    };
}

#endif //SR_ENGINE_MESH_DRAWER_PASS_H
```


