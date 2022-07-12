//
// Created by Monika on 06.05.2022.
//

#include <Types/Framebuffer.h>
#include <Environment/Environment.h>
#include <Render/Shader.h>

namespace SR_GTYPES_NS {
    Framebuffer::Framebuffer()
        : Super(typeid(Framebuffer).name(), true /** auto destroy */)
    { }

    Framebuffer::~Framebuffer() {
        SRAssert(m_frameBuffer == SR_ID_INVALID);

        for (auto&& color : m_colors) {
            SRAssert(color == SR_ID_INVALID);
        }

        SRAssert(m_shader);
    }

    Framebuffer *Framebuffer::Create(uint32_t images, const SR_MATH_NS::IVector2 &size) {
        return Create(images, size, "Engine/framebuffer.srsl");
    }

    Framebuffer::Ptr Framebuffer::Create(uint32_t images, const SR_MATH_NS::IVector2 &size, const std::string& shaderPath) {
        Framebuffer* fbo = new Framebuffer();

        SRAssert(!size.HasZero() && !size.HasNegative() && images > 0);

        fbo->SetSize(size);
        fbo->SetImagesCount(images);
        fbo->m_shaderPath = shaderPath;

        return fbo;
    }

    bool Framebuffer::Bind() {
        if (m_hasErrors) {
            return false;
        }

        if ((!m_isInit || m_needResize) && !Init()) {
            SR_ERROR("Framebuffer::Bind() : failed to initialize framebuffer!");
        }

        Environment::Get()->BindFrameBuffer(m_frameBuffer);

        return true;
    }

    bool Framebuffer::Init() {
        if (!OnResize()) {
            SR_ERROR("Framebuffer::OnResize() : failed to resize frame buffer!");
            return false;
        }

        m_isInit = true;

        return true;
    }

    bool Framebuffer::InitShader() {
        if (!m_shader) {
            if (!(m_shader = Shader::Load(m_shaderPath))) {
                m_hasErrors = false;
                return false;
            }

            m_shader->AddUsePoint();
        }

        auto&& uboManager = Memory::UBOManager::Instance();
        auto&& env = Environment::Get();

        auto&& uboBlockSize = m_shader->GetUBOBlockSize();
        auto&& samplersCount = m_shader->GetSamplersCount();

        env->SetCurrentShaderId(m_shader->GetID());

        /// кадровый буфер работает незваисимо от камеры
        uboManager.SetIgnoreCameras(true);

        if ((m_virtualUBO = uboManager.ReAllocateUBO(m_virtualUBO, uboBlockSize, samplersCount)) != SR_ID_INVALID) {
            uboManager.BindUBO(m_virtualUBO);
        }
        else {
            env->ResetDescriptorSet();
            m_hasErrors = true;
            return false;
        }

        m_shader->InitUBOBlock();
        m_shader->Flush();

        for (uint32_t i = 0; i < static_cast<uint32_t>(m_colors.size()); ++i) {
            m_shader->SetSampler2D(SHADER_COLOR_ATTACHMENTS[i], m_colors[i]);
        }

        m_shader->SetSampler2D(SHADER_DEPTH_ATTACHMENT, m_depth);

        /// сбрасываем значение
        uboManager.SetIgnoreCameras(false);

        return true;
    }

    void Framebuffer::Free() {
        if (!m_isInit) {
            return;
        }

        auto&& environment = Environment::Get();

        if (m_frameBuffer != SR_ID_INVALID) {
            SRVerifyFalse(!environment->FreeFBO(m_frameBuffer));
            m_frameBuffer = SR_ID_INVALID;
        }

        for (auto&& color : m_colors) {
            if (color == SR_ID_INVALID) {
                continue;
            }

            SRVerifyFalse(!environment->FreeTexture(&color));
        }

        if (m_shader) {
            m_shader->RemoveUsePoint();
            m_shader = nullptr;
        }

        delete this;
    }

    bool Framebuffer::OnResize() {
        if (m_colors.empty()) {
            SR_ERROR("Framebuffer::OnResize() : colors count is not set!");
            m_hasErrors = true;
            return false;
        }

        if (m_size.HasZero() || m_size.HasNegative()) {
            SR_ERROR("Framebuffer::OnResize() : incorrect FBO size!");
            m_hasErrors = true;
            return false;
        }

        if (!Environment::Get()->CreateFrameBuffer(m_size.ToGLM(), m_depth, m_frameBuffer, m_colors)) {
            SR_ERROR("Framebuffer::OnResize() : failed to create frame buffer!");
            m_hasErrors = true;
            return false;
        }

        m_hasErrors = false;
        m_needResize = false;

        return true;
    }

    void Framebuffer::SetSize(const SR_MATH_NS::IVector2 &size) {
        m_size = size;
        m_needResize = true;
    }

    void Framebuffer::SetImagesCount(uint32_t count) {
        if (m_isInit) {
            SRHalt("Frame buffer is initialized!");
            return;
        }

        m_colors.resize(count);
    }

    bool Framebuffer::BeginRender() {
        auto&& env = Environment::Get();

        env->ClearBuffers();

        if (!env->BeginRender()) {
            return false;
        }

        env->SetViewport(m_size.x, m_size.y);
        env->SetScissor(m_size.x, m_size.y);

        return true;
    }

    void Framebuffer::EndRender() {
        Environment::Get()->EndRender();
    }

    void Framebuffer::Draw() {
        if (m_hasErrors) {
            return;
        }

        if ((!m_shader || m_dirtyShader) && !InitShader()) {
            return;
        }

        auto&& env = Environment::Get();
        auto&& uboManager = Memory::UBOManager::Instance();

        if (!m_shader->Use()) {
            m_hasErrors = false;
            return;
        }

        /// кадровый буфер работает незваисимо от камеры
        uboManager.SetIgnoreCameras(true);

        switch (uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Success:
                env->Draw(3);
                break;
            case Memory::UBOManager::BindResult::Duplicated:
                SRHalt("Framebuffer memory has been duplicated!");
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }

        /// сбрасываем значение
        uboManager.SetIgnoreCameras(false);

        m_shader->UnUse();
    }

    void Framebuffer::OnResourceUpdated(IResource* pResource, int32_t deep) {
        if (dynamic_cast<Shader*>(pResource) == m_shader && m_shader) {
            m_dirtyShader = true;
            m_hasErrors = false;
        }

        Super::UpdateResources(deep);
    }

    int32_t Framebuffer::GetId() {
        if (m_hasErrors) {
            return SR_ID_INVALID;
        }

        if ((!m_isInit || m_needResize) && !Init()) {
            SR_ERROR("Framebuffer::GetId() : failed to initialize framebuffer!");
        }

        return m_frameBuffer;
    }
}