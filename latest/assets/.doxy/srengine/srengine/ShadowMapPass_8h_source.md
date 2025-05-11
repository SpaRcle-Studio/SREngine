

# File ShadowMapPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**ShadowMapPass.h**](ShadowMapPass_8h.md)

[Go to the documentation of this file](ShadowMapPass_8h.md)


```C++
//
// Created by innerviewer on 5/21/2023.
//

#ifndef SR_ENGINE_SHADOW_MAP_PASS_H
#define SR_ENGINE_SHADOW_MAP_PASS_H

#include <Graphics/Pass/ShaderOverridePass.h>

namespace SR_GRAPH_NS {
    class ShadowMapPass : public ShaderOverridePass {
        SR_REGISTER_LOGICAL_NODE(ShadowMapPass, Shadow Map Pass, { "Passes" })
        using Super = ShaderOverridePass;
    public:
        bool Init() override;
        void DeInit() override;

        bool Render() override;

        bool Load(const SR_XML_NS::Node& passNode) override;

        SR_NODISCARD const SR_MATH_NS::Matrix4x4& GetLightSpaceMatrix() const noexcept { return m_lightSpaceMatrix; }

    protected:
        void UseSharedUniforms(ShaderPtr pShader) override;
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;

        SR_NODISCARD MeshClusterType GetClusterType() const noexcept override;

    private:
        SR_MATH_NS::Matrix4x4 m_lightSpaceMatrix;

    };
}

#endif //SR_ENGINE_SHADOW_MAP_PASS_H
```


