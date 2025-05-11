

# File IMeshClusterPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**IMeshClusterPass.h**](IMeshClusterPass_8h.md)

[Go to the documentation of this file](IMeshClusterPass_8h.md)


```C++
//
// Created by Monika on 04.06.2023.
//

#ifndef SR_ENGINE_IMESHCLUSTERPASS_H
#define SR_ENGINE_IMESHCLUSTERPASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Render/MeshCluster.h>

namespace SR_GRAPH_NS {
    class ShadowMapPass;
    class CascadedShadowMapPass;

    class SR_DEPRECATED IMeshClusterPass : public BasePass {
        using Super = BasePass;
    public:
        struct Sampler {
            uint32_t textureId = SR_ID_INVALID;
            uint32_t fboId = SR_ID_INVALID;
            SR_UTILS_NS::StringAtom id;
            SR_UTILS_NS::StringAtom fboName;
            uint64_t index = 0;
            bool depth = false;
        };
        using Samplers = std::vector<Sampler>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        bool Init() override;

        void Prepare() override;
        bool Render() override;
        void Update() override;

        void OnResize(const SR_MATH_NS::UVector2& size) override;
        void OnMultisampleChanged() override;

    protected:
        SR_NODISCARD virtual MeshClusterType GetClusterType() const noexcept;
        SR_NODISCARD virtual ShaderPtr GetShader(SR_SRSL_NS::ShaderType shaderType) const { return nullptr; }

        virtual void UseSamplers(ShaderPtr pShader);
        virtual void UseUniforms(ShaderPtr pShader, MeshPtr pMesh);
        virtual void UseSharedUniforms(ShaderPtr pShader);
        virtual void UseConstants(ShaderPtr pShader);

        virtual void PrepareSamplers();
        virtual void PrepareFBODependencies();
        virtual void OnClusterDirty() { }

    protected:
        bool m_hasRendered = false;
        bool m_dirtySamplers = true;
        bool m_needUpdateMeshes = false;
        Samplers m_samplers;
        MeshClusterType m_meshClusters = MeshClusterType::None;

    };
}

#endif //SR_ENGINE_IMESHCLUSTERPASS_H
```


