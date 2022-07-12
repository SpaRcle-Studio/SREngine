//
// Created by Nikita on 19.11.2020.
//
#include <Environment/Environment.h>

#include <Render/PostProcessing.h>

#include <Render/Render.h>
#include <Render/Camera.h>

#include <Render/Implementations/OpenGLPostProcessing.h>
#include <Render/Implementations/VulkanPostProcessing.h>

Framework::Graphics::PostProcessing::PostProcessing(Camera* camera)
    : m_env(Environment::Get())
    , m_camera(camera)
{ }

Framework::Graphics::PostProcessing* Framework::Graphics::PostProcessing::Allocate(Framework::Graphics::Camera *camera) {
    if (Environment::Get()->GetPipeLine() == PipeLine::OpenGL)
        return new OpenGLPostProcessing(camera);
    else if (Environment::Get()->GetPipeLine() == PipeLine::Vulkan)
        return new VulkanPostProcessing(camera);

    SR_ERROR("PostProcessing::Allocate() : implementation not found!");
    return nullptr;
}

bool Framework::Graphics::PostProcessing::Init(Render* render) {
    if (m_isInit) {
        SR_ERROR("PostProcessing::Init() : post processing already initialize!");
        return false;
    }

    m_render = render;

    SR_GRAPH("PostProcessing::Init() : initializing post processing...");

    {
        m_postProcessingShader = Shader::Load("postProcessing");
        //m_blurShader = new Shader("engine/blur");
    }

    m_isInit = true;

    return true;
}

bool Framework::Graphics::PostProcessing::Destroy() {
    SR_GRAPH("PostProcessing::Destroy() : destroying post processing...");

    if (m_postProcessingShader) {
        m_postProcessingShader->FreeVideoMemory();
        m_postProcessingShader->Destroy();
        m_postProcessingShader = nullptr;
    }

    if (m_blurShader) {
        m_blurShader->FreeVideoMemory();
        m_blurShader->Destroy();
        m_blurShader = nullptr;
    }

    if (!m_isInit)
        return false;

    if (m_frameBuffer != -1) {
        if (!m_env->FreeFBO(m_frameBuffer) || !m_env->FreeTextures(m_colors.data(), m_colors.size())) {
            SR_ERROR("PostProcessing::Destroy() : failed to destroy framebuffer!");
            return false;
        }
        m_colors.clear();
        m_frameBuffer = -1;
    }

    if (m_finalFBO != -1) {
        //if (!m_env->FreeFBO(m_finalFBO) || !m_env->FreeTexture(m_finalColorBuffer)) {
        //    SR_ERROR("PostProcessing::Destroy() : failed to destroy framebuffer!");
        //    return false;
        //}
        m_finalFBO = m_finalColorBuffer = -1;
    }

    return true;
}

bool Framework::Graphics::PostProcessing::OnResize(uint32_t w, uint32_t h) {
    SR_GRAPH("PostProcessing::OnResize() : re-create frame buffers...");

    if (!m_env->CreateSingleFrameBuffer({w, h}, m_finalDepth, m_finalFBO, m_finalColorBuffer)) {
        SR_ERROR("PostProcessing::OnResize() : failed to create single frame buffer object!");
        return false;
    }

    if (!m_env->CreateFrameBuffer({w, h}, m_depth, m_frameBuffer, m_colors)) {
        SR_ERROR("PostProcessing::OnResize() : failed to create frame buffer object!");
        return false;
    }

    return true;
}

