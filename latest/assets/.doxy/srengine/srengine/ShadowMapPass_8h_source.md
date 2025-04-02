

# File ShadowMapPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**ShadowMapPass.h**](ShadowMapPass_8h.md)

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


