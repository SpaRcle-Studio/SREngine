//
// Created by Monika on 07.08.2022.
//

#ifndef SRENGINE_POSTPROCESSPASS_H
#define SRENGINE_POSTPROCESSPASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class PostProcessPass : public BasePass {
        SR_REGISTER_LOGICAL_NODE(PostProcessPass, Post Process Pass, { "Passes" })
        struct Property {
            uint64_t hashId = 0;
            ShaderPropertyVariant data;
            ShaderVarType type = ShaderVarType::Unknown;
        };

        struct Attachment {
            uint64_t hashId = 0;
            uint64_t fboHashName = 0;
            uint64_t index = 0;
            bool depth = false;
            SR_GTYPES_NS::Framebuffer* pFBO = nullptr;
        };
        using Super = BasePass;
        using Properties = std::vector<Property>;
        using Attachments = std::vector<Attachment>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
    public:
        ~PostProcessPass() override;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        void OnResize(const SR_MATH_NS::UVector2& size) override;
        void OnSamplesChanged() override;

        bool PreRender() override;
        bool Render() override;
        void Update() override;

        void OnResourceUpdated(SR_UTILS_NS::ResourceContainer* pContainer, int32_t depth) override;

    protected:
        virtual void SetShader(SR_GTYPES_NS::Shader* pShader);
        virtual void UseTextures();

        void DeInit() override;

    protected:
        int32_t m_virtualUBO = SR_ID_INVALID;
        bool m_dirtyShader = true;
        ShaderPtr m_shader = nullptr;
        Attachments m_attachments;
        Properties m_properties;

    };
}

#endif //SRENGINE_POSTPROCESSPASS_H
