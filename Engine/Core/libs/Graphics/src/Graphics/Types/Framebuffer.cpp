//
// Created by Monika on 06.05.2022.
//

#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Environment/Environment.h>
#include <Graphics/Types/Shader.h>

namespace SR_GTYPES_NS {
    Framebuffer::Framebuffer()
        : Super(SR_COMPILE_TIME_CRC32_TYPE_NAME(Framebuffer), true /** auto remove */)
    {
        SR_UTILS_NS::ResourceManager::Instance().RegisterResource(this);
    }

    Framebuffer::~Framebuffer() {
        SRAssert(m_frameBuffer == SR_ID_INVALID);

        for (auto&& [texture, format] : m_colors) {
            SRAssert(texture == SR_ID_INVALID);
        }

        SRAssert(m_depth.texture == SR_ID_INVALID);
    }

    Framebuffer::Ptr Framebuffer::Create(uint32_t images, const SR_MATH_NS::IVector2 &size) {
        std::list<ColorFormat> colors;

        for (uint32_t i = 0; i < images; ++i) {
            colors.emplace_back(ColorFormat::RGBA8_UNORM);
        }

        return Create(colors, DepthFormat::Auto, size);
    }

    Framebuffer::Ptr Framebuffer::Create(const std::list<ColorFormat> &colors, DepthFormat depth, const SR_MATH_NS::IVector2 &size) {
        Framebuffer* fbo = new Framebuffer();

        SRAssert(!size.HasZero() && !size.HasNegative());

        fbo->SetSize(size);
        fbo->m_depth.format = depth;

        for (auto&& color : colors) {
            ColorLayer layer;
            layer.format = color;
            fbo->m_colors.emplace_back(layer);
        }

        return fbo;
    }

    Framebuffer::Ptr Framebuffer::Create(const std::list<ColorFormat> &colors, DepthFormat depth) {
        return Create(colors, depth, SR_MATH_NS::IVector2(0, 0));
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

    /*bool Framebuffer::InitShader() {
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
            m_shader->SetSampler2D(SHADER_COLOR_ATTACHMENTS[i], m_colors[i].texture);
        }

        m_shader->SetSampler2D(SHADER_DEPTH_ATTACHMENT, m_depth.texture);

        /// сбрасываем значение
        uboManager.SetIgnoreCameras(false);

        return true;
    }*/

    void Framebuffer::FreeVideoMemory() {
        if (!m_isInit) {
            return;
        }

        auto&& environment = Environment::Get();

        if (m_frameBuffer != SR_ID_INVALID) {
            SRVerifyFalse(!environment->FreeFBO(m_frameBuffer));
            m_frameBuffer = SR_ID_INVALID;
        }

        if (m_depth.texture != SR_ID_INVALID) {
            SRVerifyFalse(!environment->FreeTexture(&m_depth.texture));
        }

        for (auto&& [texture, format] : m_colors) {
            if (texture == SR_ID_INVALID) {
                continue;
            }

            SRVerifyFalse(!environment->FreeTexture(&texture));
        }
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

        if (!Environment::Get()->CreateFrameBuffer(m_size.ToGLM(), m_frameBuffer, &m_depth, m_colors)) {
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

    bool Framebuffer::BeginRender(const Framebuffer::ClearColors &clearColors, float_t depth) {
        auto&& env = Environment::Get();

        env->ClearBuffers(clearColors, depth);

        if (!env->BeginRender()) {
            return false;
        }

        env->SetViewport(m_size.x, m_size.y);
        env->SetScissor(m_size.x, m_size.y);

        return true;
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

    /*void Framebuffer::Draw() {
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
    }*/

    int32_t Framebuffer::GetId() {
        if (m_hasErrors) {
            return SR_ID_INVALID;
        }

        if ((!m_isInit || m_needResize) && !Init()) {
            SR_ERROR("Framebuffer::GetId() : failed to initialize framebuffer!");
        }

        return m_frameBuffer;
    }

    uint64_t Framebuffer::GetFileHash() const {
        return 0;
    }

    int32_t Framebuffer::GetColorTexture(uint32_t layer) const {
        if (layer >= m_colors.size() || m_hasErrors || m_needResize) {
            return SR_ID_INVALID;
        }

        return m_colors.at(layer).texture;
    }

    bool Framebuffer::BeginRender(const SR_MATH_NS::FColor &clearColor, float_t depth) {
        return BeginRender(Framebuffer::ClearColors{ clearColor }, depth);
    }
}