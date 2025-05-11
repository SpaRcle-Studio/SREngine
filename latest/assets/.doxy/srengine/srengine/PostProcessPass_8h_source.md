

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

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class PostProcessPass : public BasePass, public ISamplersPass {
        SR_REGISTER_LOGICAL_NODE(PostProcessPass, Post Process Pass, { "Passes" })
        struct Property {
            SR_UTILS_NS::StringAtom id;
            ShaderPropertyVariant data = {};
            ShaderVarType type = ShaderVarType::Unknown;
        };

        using Super = BasePass;
        using Properties = std::vector<Property>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
    public:
        ~PostProcessPass() override;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        void OnResize(const SR_MATH_NS::UVector2& size) override;
        void OnMultisampleChanged() override;

        void Prepare() override;
        bool PreRender() override;
        bool Render() override;
        void Update() override;

        void OnResourceUpdated(SR_UTILS_NS::ResourceContainer* pContainer, int32_t depth) override;

    protected:
        void SetShader(SR_GTYPES_NS::Shader* pShader);
        void SetRenderTechnique(IRenderTechnique* pRenderTechnique) override;

        void DeInit() override;

    protected:
        int32_t m_virtualDescriptor = SR_ID_INVALID;
        int32_t m_virtualUBO = SR_ID_INVALID;
        bool m_dirtyShader = true;
        ShaderPtr m_shader = nullptr;
        Properties m_properties;
        uint32_t m_vertices = 0;

    };
}

#endif //SR_ENGINE_GRAPHICS_POST_PROCESS_PASS_H
```


