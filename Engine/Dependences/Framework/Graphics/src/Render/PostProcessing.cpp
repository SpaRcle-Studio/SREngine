//
// Created by Nikita on 19.11.2020.
//
#include <easy/profiler.h>

#include "Render/PostProcessing.h"

#include <Debug.h>
#include <Render/Render.h>
#include <Render/Camera.h>

using namespace Framework::Helper;

Framework::Graphics::PostProcessing::PostProcessing(Camera* camera, unsigned char countHDRBuffers) : m_env(Environment::Get()){
    this->m_camera = camera;
    if (countHDRBuffers < 4){
        Debug::Error("PostProcessing::Constructor(): count buffers is < 4! Skip arg.");
    } else if (countHDRBuffers > 4) {
        this->m_ColorBuffers = std::vector<unsigned int>(countHDRBuffers);
        this->m_countColorBuffers = countHDRBuffers;
    }
}

bool Framework::Graphics::PostProcessing::Init(Render* render) {
    if (m_isInit) {
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
    //m_env->BindFrameBuffer(m_PingPongFrameBuffers[0]);
    //m_env->ClearBuffers();
    //m_env->BindFrameBuffer(m_PingPongFrameBuffers[1]);
    //m_env->ClearBuffers();

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
    if (m_bloom){
        this->BlurBloom();
        if (m_bloomClear)
            m_bloomClear = false;
    }
    else if (!m_bloomClear) {
        m_env->BindFrameBuffer(m_PingPongFrameBuffers[0]);
        m_env->ClearColorBuffers(0,0,0,0);
        m_env->ClearBuffers();
        m_env->BindFrameBuffer(m_PingPongFrameBuffers[1]);
        m_env->ClearColorBuffers(0,0,0,0);
        m_env->ClearBuffers();

        m_env->BindFrameBuffer(0);

        m_bloomClear = true;
    }

    if (m_camera->IsDirectOutput())
        m_env->BindFrameBuffer(0);
    else {
        m_env->BindFrameBuffer(this->m_finalFBO);
        m_env->ClearBuffers();
    }

    m_postProcessingShader->Use();

    {
        m_postProcessingShader->SetFloat("gamma", m_gamma);
        m_postProcessingShader->SetFloat("exposure", m_exposure);
        m_postProcessingShader->SetFloat("saturation", m_saturation);
        m_postProcessingShader->SetVec3("ColorCorrection", m_color_correction);
        m_postProcessingShader->SetVec3("BloomColor", m_bloomColor);
    }

    /*if (m_bloom) {
        //if (m_debugDisplayBloomMask) {
        //    m_postProcessingShader->SetInt("scene", 0);
        //    m_env->BindTexture(1, m_ColorBuffers[1]);
        //    m_postProcessingShader->SetInt("bloomBlur", 1);
        //} else {
            m_env->BindTexture(0, m_ColorBuffers[0]);
            m_postProcessingShader->SetInt("scene", 0);

            m_env->BindTexture(1, m_PingPongColorBuffers[!m_horizontal]);
            m_postProcessingShader->SetInt("bloomBlur", 1);

            m_env->BindTexture(2, m_skyboxColorBuffer);
            m_postProcessingShader->SetInt("skybox", 2);
        //}
    }else {
        m_env->BindTexture(0, m_ColorBuffers[0]);
        m_postProcessingShader->SetInt("scene", 0);

        m_env->BindTexture(1, 0);
        m_postProcessingShader->SetInt("bloomBlur", 1);

        m_env->BindTexture(2, m_skyboxColorBuffer);
        m_postProcessingShader->SetInt("skybox", 2);
    }*/

    m_env->BindTexture(0, m_ColorBuffers[0]);
    m_postProcessingShader->SetInt("scene", 0);

    if (m_bloom)
        m_env->BindTexture(1, m_PingPongColorBuffers[!m_horizontal]);
    else
        m_env->BindTexture(1, 0);
    m_postProcessingShader->SetInt("bloomBlur", 1);

    m_env->BindTexture(2, m_skyboxColorBuffer);
    m_postProcessingShader->SetInt("skybox", 2);

    m_env->BindTexture(3, m_ColorBuffers[3]);
    m_postProcessingShader->SetInt("stencil", 3);

    m_env->BindTexture(4, m_ColorBuffers[2]);
    m_postProcessingShader->SetInt("depth", 4);

    m_env->DrawQuad(m_VAO);

    if (!m_camera->IsDirectOutput())
        m_env->BindFrameBuffer(0);

    return false;
}

bool Framework::Graphics::PostProcessing::ReCalcFrameBuffers(int w, int h) {
    //Debug::Log("PostProcessing::ReCalcFrameBuffers() : re-calc...");

    if (!m_env->CreateSingleHDRFrameBO({w, h}, m_finalRBO, m_finalFBO, m_finalColorBuffer)) {
        return false;
    }

    if (!m_env->CreateSingleHDRFrameBO({w, h}, m_skyboxRBO, m_skyboxFBO, m_skyboxColorBuffer)) {
        return false;
    }

    if (!m_env->CreateHDRFrameBufferObject({w, h}, m_RBODepth, m_HDRFrameBufferObject, m_ColorBuffers)) {
        return false;
    }

    return m_env->CreatePingPongFrameBufferObject({w, h}, m_PingPongFrameBuffers, m_PingPongColorBuffers);

}

bool Framework::Graphics::PostProcessing::Destroy() {
    Debug::Graph("PostProcessing::Destroy() : destroying post processing...");

    return false;
}

void Framework::Graphics::PostProcessing::BeginSkybox() {
    m_env->BindFrameBuffer(this->m_skyboxFBO);
    //m_env->BindFrameBuffer(this->m_finalFBO);
    m_env->ClearBuffers();
}

void Framework::Graphics::PostProcessing::EndSkybox() {
    m_env->BindFrameBuffer(0);
}

void Framework::Graphics::PostProcessing::BeginStencil() {

}

void Framework::Graphics::PostProcessing::EndStencil() {

}


