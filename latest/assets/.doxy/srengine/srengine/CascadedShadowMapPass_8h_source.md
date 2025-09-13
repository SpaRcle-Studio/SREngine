

# File CascadedShadowMapPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**CascadedShadowMapPass.h**](CascadedShadowMapPass_8h.md)

[Go to the documentation of this file](CascadedShadowMapPass_8h.md)


```C++
//
// Created by Monika on 06.06.2023.
//

#ifndef SR_ENGINE_CASCADED_SHADOW_MAP_PASS_H
#define SR_ENGINE_CASCADED_SHADOW_MAP_PASS_H

#include <Graphics/Pass/MeshDrawerPass.h>

#include <Utils/Math/Matrix4x4.h>

namespace SR_GRAPH_NS {
    class CascadedShadowMapPass : public MeshDrawerPass {
        SR_CLASS()
        using Super = MeshDrawerPass;
    public:
        SR_NODISCARD const std::vector<SR_MATH_NS::Matrix4x4>& GetCascadeMatrices() const { return m_cascadeMatrices; }
        SR_NODISCARD const std::vector<float_t>& GetSplitDepths() const { return m_cascadeSplitDepths; }

    public:
        void Prepare() override;
        void PostUpdate() override;
        void UseSharedUniforms(SR_GTYPES_NS::Shader* pShader) override;
        void UseConstants(SR_GTYPES_NS::Shader* pShader) override;
        void UseUniformsFromAnotherPass(SR_GTYPES_NS::Shader* pShader) override;

    protected:
        bool CheckCamera();
        void UpdateCascades();

    protected:
        SR_MATH_NS::FVector3 m_directionalLightDirection;
        SR_MATH_NS::FVector3 m_cameraPosition;
        SR_MATH_NS::Quaternion m_cameraRotation;
        SR_MATH_NS::UVector2 m_screenSize;

        float_t m_near = 0.1f;
        float_t m_far = 100.f;
        float_t m_cascadeSplitLambda = 0.95f;

        std::vector<SR_MATH_NS::Matrix4x4> m_cascadeMatrices;
        std::vector<float_t> m_cascadeSplitDepths;
        std::vector<float_t> m_cascadeRadii;

    };
}

#endif //SR_ENGINE_CASCADED_SHADOW_MAP_PASS_H
```


