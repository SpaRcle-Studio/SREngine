//
// Created by Monika on 07.08.2022.
//

#include <Graphics/Pass/PostProcessPass.h>
#include <Graphics/Pass/FramebufferPass.h>
#include <Graphics/Types/Texture.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(PostProcessPass)

    PostProcessPass::~PostProcessPass() {
        SetShader(nullptr);
    }

    bool PostProcessPass::PreRender() {
        return Super::PreRender();
    }

    bool PostProcessPass::Render() {
        if (!m_shader) {
            return false;
        }

        switch (m_shader->Use()) {
            case ShaderBindResult::Failed:
                return false;
            case ShaderBindResult::Success:
                break;
            case ShaderBindResult::Duplicated:
            case ShaderBindResult::ReAllocated:
                m_dirtyShader = true;
                break;
            default:
                SRHaltOnce0();
                return false;
        }

        auto&& uboManager = Memory::UBOManager::Instance();

        if (m_dirtyShader)
        {
            m_dirtyShader = false;

            m_virtualUBO = uboManager.ReAllocateUBO(m_virtualUBO, m_shader->GetUBOBlockSize(), m_shader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                uboManager.BindUBO(m_virtualUBO);
            }
            else {
                GetPassPipeline()->ResetDescriptorSet();
                return false;
            }

            m_shader->InitUBOBlock();
            m_shader->Flush();
            UseTextures();
            m_shader->FlushSamplers();
        }

        switch (uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                m_shader->InitUBOBlock();
                m_shader->Flush();
                UseTextures();
                m_shader->FlushSamplers();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
                GetPassPipeline()->Draw(3);
                break;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }

        m_shader->UnUse();

        return true;
    }

    void PostProcessPass::Update() {
        if (m_virtualUBO == SR_ID_INVALID) {
            return;
        }

        GetPassPipeline()->SetCurrentShader(m_shader);

        if (m_shader) {
            m_shader->SetFloat(SHADER_TIME, SR_HTYPES_NS::Time::Instance().FClock());
            m_shader->SetVec2(SHADER_RESOLUTION, GetContext()->GetWindowSize().Cast<float_t>());
        }

        if (m_shader && m_camera) {
            m_shader->SetVec3(SHADER_VIEW_POSITION, m_camera->GetPositionRef());
            m_shader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection());
            m_shader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            m_shader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            m_shader->SetMat4(SHADER_VIEW_NO_TRANSLATE_MATRIX, m_camera->GetViewRef());
        }

        if (m_uboManager.BindUBO(m_virtualUBO) == Memory::UBOManager::BindResult::Duplicated) {
            SR_ERROR("PostProcessPass::Update() : memory has been duplicated!");
        }

        m_shader->Flush();

        Super::Update();
    }

    bool PostProcessPass::Load(const SR_XML_NS::Node& passNode) {
        auto&& path = passNode.GetAttribute("Shader").ToString();
        if (auto&& pShader = SR_GTYPES_NS::Shader::Load(path)) {
            SetShader(pShader);
        }
        else {
            SR_ERROR("PostProcessPass::Load() : failed to load shader!\n\tPath: " + path);
            return false;
        }

        m_attachments.clear();

        if (auto&& attachmentsNode = passNode.TryGetNode("Attachments")) {
            for (auto&& attachmentNode : attachmentsNode.TryGetNodes("Attachment")) {
                Attachment attachment = Attachment();
                attachment.fboName = attachmentNode.GetAttribute("FBO").ToString();
                attachment.id = attachmentNode.GetAttribute("Id").ToString();

                if (auto&& depthAttribute = attachmentNode.TryGetAttribute("Depth")) {
                    attachment.depth = depthAttribute.ToBool();
                }

                if (!attachment.depth) {
                    attachment.index = attachmentNode.GetAttribute("Index").ToUInt64();
                }

                m_attachments.emplace_back(attachment);
            }
        }

        return Super::Load(passNode);
    }

    void PostProcessPass::SetShader(SR_GTYPES_NS::Shader* pShader) {
        if (m_shader == pShader) {
            return;
        }

        m_dirtyShader = true;

        if (m_shader) {
            RemoveDependency(m_shader);
            m_shader = nullptr;
        }

        if (!(m_shader = pShader)) {
            return;
        }

        AddDependency(m_shader);
    }

    void PostProcessPass::DeInit() {
        auto&& uboManager = Memory::UBOManager::Instance();
        if (m_virtualUBO != SR_ID_INVALID && !uboManager.FreeUBO(&m_virtualUBO)) {
            SR_ERROR("PostProcessPass::DeInit() : failed to free virtual uniform buffer object!");
        }
        Super::DeInit();
    }

    void PostProcessPass::UseTextures() {
        for (auto&& attachment : m_attachments) {
            if (!attachment.pFBO) {
                if (auto&& pFBOPass = dynamic_cast<IFramebufferPass*>(GetTechnique()->FindPass(attachment.fboName))) {
                    attachment.pFBO = pFBOPass->GetFramebuffer();
                }
            }

            uint32_t textureId = SR_ID_INVALID;

            if (attachment.pFBO) {
                if (attachment.depth) {
                    textureId = attachment.pFBO->GetDepthTexture();
                }
                else {
                    textureId = attachment.pFBO->GetColorTexture(attachment.index);
                }
            }

            if (textureId == SR_ID_INVALID) {
                textureId = GetContext()->GetDefaultTexture()->GetId();
            }

            m_shader->SetSampler2D(attachment.id, textureId);
        }
    }

    void PostProcessPass::OnResourceUpdated(SR_UTILS_NS::ResourceContainer *pContainer, int32_t depth) {
        if (dynamic_cast<SR_GTYPES_NS::Shader*>(pContainer) == m_shader && m_shader) {
            m_dirtyShader = true;
        }

        ResourceContainer::OnResourceUpdated(pContainer, depth);
    }

    void PostProcessPass::OnResize(const SR_MATH_NS::UVector2& size) {
        m_dirtyShader = true;
        Super::OnResize(size);
    }

    void PostProcessPass::OnSamplesChanged() {
        m_dirtyShader = true;
        BasePass::OnSamplesChanged();
    }
}