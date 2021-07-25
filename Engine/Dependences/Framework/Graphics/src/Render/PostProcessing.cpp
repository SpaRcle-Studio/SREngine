//
// Created by Nikita on 19.11.2020.
//
#include <Environment/Environment.h>

#include "Render/PostProcessing.h"

#include <Debug.h>
#include <Render/Render.h>
#include <Render/Camera.h>

#include <Debug.h>

#include <Render/Implementations/OpenGLPostProcessing.h>
#include <Render/Implementations/VulkanPostProcessing.h>

Framework::Graphics::PostProcessing::PostProcessing(Camera* camera) : m_env(Environment::Get()){
    this->m_camera = camera;
}

Framework::Graphics::PostProcessing* Framework::Graphics::PostProcessing::Allocate(Framework::Graphics::Camera *camera) {
    if (Environment::Get()->GetPipeLine() == PipeLine::OpenGL)
        return new OpenGLPostProcessing(camera);
    else if (Environment::Get()->GetPipeLine() == PipeLine::Vulkan)
        return new VulkanPostProcessing(camera);

    Helper::Debug::Error("PostProcessing::Allocate() : implementation not found!");
    return nullptr;
}

bool Framework::Graphics::PostProcessing::Init(Render* render) {
    if (m_isInit) {
        Debug::Error("PostProcessing::Init() : post processing already initialize!");
        return false;
    }

    this->m_render = render;

    Debug::Graph("PostProcessing::Init() : initializing post processing...");

    {
        this->m_postProcessingShader = new Shader(m_render, "engine/postProcessing");
        this->m_postProcessingShader->SetCreateInfo({
            .polygonMode  = PolygonMode::Fill,
            .cullMode     = CullMode::Back,
            .depthCompare = DepthCompare::LessOrEqual,
            .blendEnabled = true,
            .depthWrite   = false,
            .depthTest    = false
        });
        /*
         *  0 - ubo
         *  1 - geometry
         *  2 - skybox
         */
        this->m_postProcessingShader->SetUniforms({
            {{0, UBOType::Common}, sizeof(PostProcessingUBO)},
        });

        this->m_blurShader = new Shader(m_render, "engine/blur");
    }

    m_isInit = true;

    return true;
}

bool Framework::Graphics::PostProcessing::Destroy() {
    Helper::Debug::Graph("PostProcessing::Destroy() : destroying post processing...");

    if (!m_isInit)
        return false;

    if (m_frameBuffer != -1)
        if (!m_env->FreeFBO(m_frameBuffer) || !m_env->FreeTextures(m_colors.data(), m_colors.size())) {
            Helper::Debug::Error("PostProcessing::Destroy() : failed to destroy framebuffer!");
            return false;
        }

    if (m_finalFBO != -1)
        if (!m_env->FreeFBO(m_finalFBO) || !m_env->FreeTexture(m_finalColorBuffer)) {
            Helper::Debug::Error("PostProcessing::Destroy() : failed to destroy framebuffer!");
            return false;
        }

    return true;
}

bool Framework::Graphics::PostProcessing::OnResize(uint32_t w, uint32_t h) {
    Helper::Debug::Graph("PostProcessing::OnResize() : re-create frame buffers...");

    if (!m_env->CreateSingleFrameBuffer({w, h}, m_finalDepth, m_finalFBO, m_finalColorBuffer)) {
        Helper::Debug::Error("PostProcessing::OnResize() : failed to create single frame buffer object!");
        return false;
    }

    if (!m_env->CreateFrameBuffer({w, h}, m_depth, m_frameBuffer, m_colors)) {
        Helper::Debug::Error("PostProcessing::OnResize() : failed to create frame buffer object!");
        return false;
    }

    return true;
}

