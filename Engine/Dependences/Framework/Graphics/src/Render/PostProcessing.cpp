//
// Created by Nikita on 19.11.2020.
//

#include "Render/PostProcessing.h"

#include <Debug.h>
#include <Render/Render.h>
#include <Render/Camera.h>

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
        this->m_blurShader           = new Shader(m_render, "engine/blur");
    }

    m_isInit = true;

    return true;
}

bool Framework::Graphics::PostProcessing::Destroy() { // TODO
    Helper::Debug::Graph("PostProcessing::Destroy() : destroying post processing...");

    return false;
}

