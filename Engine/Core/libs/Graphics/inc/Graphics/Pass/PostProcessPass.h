//
// Created by Monika on 07.08.2022.
//

#ifndef SRENGINE_POSTPROCESSPASS_H
#define SRENGINE_POSTPROCESSPASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Environment/Basic/IShaderProgram.h>

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_GRAPH_NS {
    class PostProcessPass : public BasePass {
        struct Property {
            std::string id;
            ShaderPropertyVariant data;
            ShaderVarType type;
        };
        using Properties = std::list<Property>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
    public:
        explicit PostProcessPass(RenderTechnique* pTechnique, BasePass* pParent);
        ~PostProcessPass() override = default;

    public:
        bool PreRender() override;
        bool Render() override;
        void Update() override;

    private:
        ShaderPtr m_shader = nullptr;
        Properties m_properties;

    };
}

#endif //SRENGINE_POSTPROCESSPASS_H
