//
// Created by Nikita on 19.11.2020.
//

#include "Render/PostProcessing.h"

#include <Debug.h>
#include <Render/Render.h>
#include <Render/Camera.h>

using namespace Framework::Helper;

bool Framework::Graphics::PostProcessing::Init(Render* render) {
    if (m_isInit){
        Debug::Error("PostProcessing::Init() : post processing already initialize!");
        return false;
    }

    this->m_render = render;

    Debug::Graph("PostProcessing::Init() : initializing post processing...");

    {
        this->m_postProcessingShader = new Shader(m_render, "postProcessing");
        this->m_postProcessingShader->Init();

        this->m_blurShader = new Shader(m_render, "blur");
        this->m_blurShader->Init();
    }

    m_env->CalculateQuad(m_VBO, m_VAO);

    m_isInit = true;

    return true;
}

bool Framework::Graphics::PostProcessing::Begin() {
    m_env->BindFrameBuffer(m_HDRFrameBufferObject);
    m_env->ClearBuffers();

    return false;
}

void Framework::Graphics::PostProcessing::BlurBloom() {
    m_env->BindFrameBuffer(0);

    m_horizontal = true; m_firstIteration = true;

    unsigned int amount = 15;
    m_blurShader->Use();

    m_blurShader->SetFloat("BloomIntensity", m_bloomIntensity);

    for (unsigned int i = 0; i < m_bloomAmount; i++)
    {
        m_env->BindFrameBuffer(m_PingPongFrameBuffers[m_horizontal]);

        m_blurShader->SetBool("horizontal", m_horizontal);

        m_env->BindTexture(0,m_firstIteration ? m_ColorBuffers[1] : m_PingPongColorBuffers[!m_horizontal]);
        m_blurShader->SetInt("image", 0);

        m_env->DrawQuad(m_VAO);
        m_horizontal = !m_horizontal;
        if (m_firstIteration)
            m_firstIteration = false;
    }
}

bool Framework::Graphics::PostProcessing::End() {
    if (m_bloom)
        this->BlurBloom();

    if (m_camera->IsDirectOutput())
        m_env->BindFrameBuffer(0);
    else
        m_env->BindFrameBuffer(this->m_finalFBO);

    m_postProcessingShader->Use();

    {
        m_postProcessingShader->SetFloat("gamma", m_gamma);
        m_postProcessingShader->SetFloat("exposure", m_exposure);
    }

    if (m_bloom) {
        if (m_debugDisplayBloomMask) {
            m_postProcessingShader->SetInt("scene", 0);
            m_env->BindTexture(1, m_ColorBuffers[1]);
            m_postProcessingShader->SetInt("bloomBlur", 1);
        } else {
            m_env->BindTexture(0, m_ColorBuffers[0]);
            m_postProcessingShader->SetInt("scene", 0);
            m_env->BindTexture(1, m_PingPongColorBuffers[!m_horizontal]);
            m_postProcessingShader->SetInt("bloomBlur", 1);
        }
    }else {
        m_env->BindTexture(0, m_ColorBuffers[0]);
        m_postProcessingShader->SetInt("scene", 0);
    }

    m_env->DrawQuad(m_VAO);

    if (!m_camera->IsDirectOutput())
        m_env->BindFrameBuffer(0);

    return false;
}

Framework::Graphics::PostProcessing::PostProcessing(Camera* camera) : m_env(Environment::Get()){
    this->m_camera = camera;
}

unsigned int Framework::Graphics::PostProcessing::GetFinally() noexcept {
    return m_finalColorBuffer;
}

bool Framework::Graphics::PostProcessing::ReCalcFrameBuffers(int w, int h) {
    //Debug::Log("PostProcessing::ReCalcFrameBuffers() : re-calc...");

    std::vector<unsigned int> temp = { 0 };
    if (!m_env->CreateHDRFrameBufferObject({w, h}, m_finalRBO, m_finalFBO, temp)) {
        return false;
    }
    m_finalColorBuffer = temp[0];

    if (!m_env->CreateHDRFrameBufferObject({w, h}, m_RBODepth, m_HDRFrameBufferObject, m_ColorBuffers)) {
        return false;
    }

    if (!m_env->CreatePingPongFrameBufferObject({w, h}, m_PingPongFrameBuffers, m_PingPongColorBuffers))
    {
        return false;
    }

    return true;
}

bool Framework::Graphics::PostProcessing::Destroy() {
    Debug::Graph("PostProcessing::Destroy() : destroying post processing...");

    return false;
}