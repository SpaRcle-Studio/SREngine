

# File MeshDrawerPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**MeshDrawerPass.h**](MeshDrawerPass_8h.md)

[Go to the documentation of this file](MeshDrawerPass_8h.md)


```C++
//
// Created by Monika on 18.01.2024.
//

#ifndef SR_ENGINE_MESH_DRAWER_PASS_H
#define SR_ENGINE_MESH_DRAWER_PASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Render/RenderPredicates.h>
#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/SRSL/ShaderType.h>

namespace SR_GRAPH_NS {
    class RenderStrategy;
    class RenderQueue;

    struct MeshDrawerSharedUniforms : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        
        bool camera = true;
        bool time = true;
        bool light = true;
        std::set<SR_UTILS_NS::StringAtom> useFromPass;

    };

    struct MeshDrawerMaterialUniforms : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        
        bool useMaterial = true;
        bool modelMatrix = true;

    };

    struct MeshDrawerUniforms : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        
        MeshDrawerSharedUniforms shared;
        MeshDrawerMaterialUniforms material;

    };

    class MeshDrawerPass : public BasePass, public LayerFilterPredicate, public PriorityFilterPredicate {
        SR_CLASS()
        using Super = BasePass;
    public:
        using RenderQueuePtr = SR_HTYPES_NS::SharedPtr<RenderQueue>;

    public:
        MeshDrawerPass();
        ~MeshDrawerPass() override;

        bool Init() override;
        void DeInit() override;
        void Prepare() override;
        bool Render() override;
        void Update() override;

        SR_NODISCARD bool HasPreRender() const noexcept override { return false; }
        SR_NODISCARD bool HasPostRender() const noexcept override { return false; }
        SR_NODISCARD virtual bool IsNeedUpdate() const noexcept { return false; }

        void SetRenderTechnique(SR_GRAPH_NS::IRenderTechnique* pRenderTechnique) override;

        virtual void UseUniforms(SR_GTYPES_NS::Shader* pShader, MeshPtr pMesh);
        virtual void UseSharedUniforms(SR_GTYPES_NS::Shader* pShader);
        virtual void UseConstants(SR_GTYPES_NS::Shader* pShader);
        void UseSamplers(SR_GTYPES_NS::Shader* pShader) override;

        void OnMultisampleChanged() override;
        void OnResize(const SR_MATH_NS::UVector2& size) override;

        SR_NODISCARD bool IsLayerAllowed(SR_UTILS_NS::StringAtom layer) const override;
        SR_NODISCARD bool IsPriorityAllowed(int64_t priority) const override { return true; }

        SR_NODISCARD const std::vector<RenderQueuePtr>& GetRenderQueues() const noexcept { return m_renderQueues; }
        SR_NODISCARD const SR_SRSL_NS::ShaderMacrosParams& GetShaderMacros() const noexcept { return m_shaderMacros; }
        SR_NODISCARD uint8_t GetLayersCount() const noexcept { return m_renderLayers; }

    protected:
        SR_NODISCARD RenderStrategy* GetRenderStrategy() const;
        SR_NODISCARD virtual RenderQueuePtr AllocateRenderQueue();

    private:
        std::vector<RenderQueuePtr> m_renderQueues;
        SR_HTYPES_NS::Time& m_time;
        SR_SRSL_NS::ShaderMacrosParams m_shaderMacros;

        uint8_t m_renderLayers = 1;
        std::set<SR_UTILS_NS::StringAtom> m_allowedLayers;
        std::set<SR_UTILS_NS::StringAtom> m_disallowedLayers;
        std::set<std::string> m_shaderDefines;
        SamplersPassData m_samplers;
        MeshDrawerUniforms m_uniforms;

    };
}

#endif //SR_ENGINE_MESH_DRAWER_PASS_H
```


