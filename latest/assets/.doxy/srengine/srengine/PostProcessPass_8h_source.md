

# File PostProcessPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**PostProcessPass.h**](PostProcessPass_8h.md)

[Go to the documentation of this file](PostProcessPass_8h.md)


```C++
//
// Created by Monika on 07.08.2022.
//

#ifndef SR_ENGINE_GRAPHICS_POST_PROCESS_PASS_H
#define SR_ENGINE_GRAPHICS_POST_PROCESS_PASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/Material/MaterialData.h>
#include <Graphics/Material/UniqueMaterial.h>

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_GRAPH_NS {
    class PostProcessPass : public BasePass {
        SR_CLASS()

        struct Property {
            SR_UTILS_NS::StringAtom id;
            ShaderPropertyVariant data = {};
            ShaderVarType type = ShaderVarType::Unknown;
        };

        using Super = BasePass;
        using Properties = std::vector<Property>;
        using ShaderPtr = SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Shader>;
    public:
        ~PostProcessPass() override;

    public:
        bool Init() override;
        void OnResize(const SR_MATH_NS::UVector2& size) override;
        void OnMultisampleChanged() override;

        bool PreRender() override;
        bool Render() override;
        void Update() override;
        void Prepare() override;

    protected:
        void UseSamplers(SR_GTYPES_NS::Shader* pShader) override;
        void SetRenderTechnique(SR_GRAPH_NS::IRenderTechnique* pRenderTechnique) override;
        void DeInit() override;

    protected:
        SR_UTILS_NS::Subscription m_onShaderReloaded;
        int32_t m_virtualDescriptor = SR_ID_INVALID;
        int32_t m_virtualUBO = SR_ID_INVALID;
        bool m_dirtyShader = true;
        Properties m_properties;

        uint32_t m_vertices = 3;
        SamplersPassData m_samplers;
        BaseMaterial::Ptr m_material;

    };
}

#endif //SR_ENGINE_GRAPHICS_POST_PROCESS_PASS_H
```


