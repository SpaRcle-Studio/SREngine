//
// Created by Nikita on 18.11.2020.
//

#include "Render/Camera.h"
#include "Window/Window.h"
#include <Debug.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <glm/gtx/string_cast.hpp>
#include <Math/Mathematics.h>

void Framework::Graphics::Camera::UpdateShader(Framework::Graphics::Shader *shader) noexcept {
    if (!m_isCreate) {
        Debug::Warn("Camera::UpdateShader() : camera is not create! Something went wrong...");
        return;
    }

    if (!m_isCalculate)
        this->Calculate();

    if (m_needUpdate){
        if (!this->m_postProcessing->ReCalcFrameBuffers(m_cameraSize.x, m_cameraSize.y)){
            Debug::Error("Camera::UpdateShader() : failed recalculated frame buffers!");
            return;
        }
        m_needUpdate = false;
        this->m_isBuffCalculate = true;
    }

    shader->SetMat4("viewMat", this->m_viewMat);
    shader->SetMat4("projMat", this->m_projection);

    /*
         mat4x4((1.357995, 0.000000, 0.000000, 0.000000), (0.000000, 2.414213, 0.000000, 0.000000), (0.000000, 0.000000, -1.000025,
               -1.000000), (0.000000, 0.000000, -0.200003, 0.000000))
     */
}

Framework::Graphics::Camera::Camera(unsigned char countHDRBuffers) : Component("Camera") {
    this->m_postProcessing = new PostProcessing(this, countHDRBuffers);
}

Framework::Graphics::Camera::~Camera() = default;

bool Framework::Graphics::Camera::Create(Framework::Graphics::Window *window) {
    Debug::Graph("Camera::Create() : creating camera...");
    if (m_isCreate){
        Debug::Error("Camera::Create() : camera already create!");
        return false;
    }

    this->m_window = window;

    this->UpdateView();

    this->m_isCreate = true;

    return true;
}

static inline glm::mat4 Mat4FromQuat(glm::quat & q) {
    glm::mat4 M;
    M[0][0] = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    M[0][1] = 2.0f * (q.x * q.y + q.z * q.w);
    M[0][2] = 2.0f * (q.x * q.z - q.y * q.w);
    M[0][3] = 0.0f;

    M[1][0] = 2.0f * (q.x * q.y - q.z * q.w);
    M[1][1] = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
    M[1][2] = 2.0f * (q.z * q.y + q.x * q.w);
    M[1][3] = 0.0f;

    M[2][0] = 2.0f * (q.x * q.z + q.y * q.w);
    M[2][1] = 2.0f * (q.y * q.z - q.x * q.w);
    M[2][2] = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
    M[2][3] = 0.0f;

    M[3][0] = 0;
    M[3][1] = 0;
    M[3][2] = 0;
    M[3][3] = 1.0f;
    return M;
}

bool inverse(int angle){
    angle = abs(angle % 360);
    return angle >= 90 && angle <= 270;
}

void Framework::Graphics::Camera::UpdateView() noexcept {
    //float camX = sin(m_yaw)   * cos(m_roll)  +  tan(m_pitch) * sin(m_roll);
    //float camY = tan(m_pitch) * cos(m_roll)  +  sin(m_yaw)   * sin(m_roll);

    //glm::quat q(glm::vec3(m_yaw, m_pitch, m_roll));
    //glm::mat4 view = Mat4FromQuat(q);
    //glm::mat4 trans = glm::translate(glm::mat4(1), -m_pos);
    //this->m_viewMat = trans * view;


    /*const glm::mat4 transMat = glm::translate(glm::mat4(1.f), {
            -m_pos.x,
            -m_pos.y,
            -m_pos.z
    });

    const glm::mat4 rotationMat = mat4_cast(glm::quat(glm::vec3(
            {
                    m_pitch,
                    -m_yaw + glm::radians(180.f),
                    m_roll
            }
    )));
    m_viewMat = rotationMat * transMat;*/

    glm::mat4 matrix(1.f);

    matrix = glm::rotate(matrix,
             m_pitch
            , {1, 0, 0}
        );
    matrix = glm::rotate(matrix,
             m_yaw
            , {0, 1, 0}
    );
    matrix = glm::rotate(matrix,
             m_roll
            , {0, 0, 1}
    );

    m_viewMat = glm::translate(matrix, {
        -m_pos.x,
        -m_pos.y,
        m_pos.z//-m_pos.z
    });

    //m_pitch * cos(m_roll)   +  m_yaw * sin(m_roll)    + m_roll * sin(m_yaw)
    //   * cos(m_roll)   + m_pitch * sin(m_roll)   + m_roll * sin(m_pitch)

    /*
    float posx = m_pos.x;
    float posy = m_pos.y;
    float posz = m_pos.z;

    float camX = sin(m_yaw);
    float camY = tan(m_pitch);
    float camZ = cos(m_yaw);

    //std::cout << camX << " " << camY << " " << camZ << std::endl;

    const float eye_radius = 1.f / 100.f; // most correctly

    glm::vec3 eyes = {
            camX,
            sin(m_pitch),
            cos(m_pitch) * camZ
    };

    glm::mat4 view = glm::lookAt(
            {
                    //glm::vec3(camX, camY, camZ) * eye_radius + glm::vec3(posx, posy, posz)
                    eyes * eye_radius + glm::vec3(posx, posy, posz)
            },
            {posx, posy, posz},
            glm::vec3(0, 1, 0)
    );

    //glm::mat4 roll = glm::rotate(glm::mat4(1), m_roll, glm::vec3(0, 0, 1));

    //std::cout << m_pitch / M_PI * 45.f * 4.f << std::endl;
    //std::cout << inverse((int)glm::degrees(m_pitch)) << std::endl;
    glm::mat4 roll = glm::rotate(glm::mat4(1), m_roll + glm::radians(180.f) * float(inverse((int)glm::degrees(m_pitch))), glm::vec3(0, 0, 1));

    //float(((int(glm::degrees(m_pitch)) / 90) % 2) == 1)
    //roll = glm::rotate(glm::mat4(1), glm::radians(180.f) * (float)(int(glm::degrees(m_pitch)) / 180), glm::vec3(0, 0, 1));

    m_viewMat = roll * view;
    */

    /*glm::mat4 cam = glm::rotate(glm::mat4(1.0), m_yaw, glm::vec3(1, 0, 0));
    cam = glm::rotate(cam, m_pitch, glm::vec3(0, 1, 0));
    cam = glm::rotate(cam, m_roll, glm::vec3(0, 0, 1));

    glm::mat4 camMove = glm::translate(glm::mat4(1.0), m_pos);

    this->m_viewMat = camMove * glm::inverse(cam);*/
}

/*glm::quat p(0, glm::vec3(0, 0, 1));
glm::vec3 axis = { 1, 0, 0 };
axis = glm::normalize(axis);
glm::quat q(m_pitch, axis);
q = glm::normalize(q);
glm::quat inv = glm::inverse(q);
glm::quat yaw_q = (q * p * inv);
glm::vec3 yaw(yaw_q.x, yaw_q.y, yaw_q.z);*/

void Framework::Graphics::Camera::OnRotate(glm::vec3 newValue) noexcept {
    this->m_yaw   = float(newValue.y * 3.14 / 45.f / 4.f);
    this->m_pitch = float(newValue.x * 3.14 / 45.f / 4.f);
    this->m_roll  = float(newValue.z * 3.14 / 45.f / 4.f);

    this->UpdateView();
}

void Framework::Graphics::Camera::OnMove(glm::vec3 newValue) noexcept {
    this->m_pos = {
             newValue.x,
             newValue.y,
            -newValue.z
    };
    this->UpdateView();
}

void Framework::Graphics::Camera::UpdateProjection(unsigned int w, unsigned int h) {
    this->m_cameraSize = {w, h};
    m_projection = glm::perspective(glm::radians(45.f), float(w) / (float)h, m_near, m_far);
    m_needUpdate = true;
}

bool Framework::Graphics::Camera::Calculate() noexcept {
    if (m_isCalculate)
        return false;

    Debug::Graph("Camera::Calculate() : calculating camera...");

    this->m_postProcessing->Init(m_window->GetRender());
    m_needUpdate = true;
    m_isCalculate = true;

    return true;
}

void Framework::Graphics::Camera::OnDestroyGameObject() noexcept {
    //if (m_isUse)
    if (m_window) {
        m_window->DestroyCamera(this);
        m_window = nullptr;
    }
    /*ret: if (m_isUse) {
        if (m_window)
            if (m_window->IsWindowOpen())
                goto ret;
    }
    this->Free();*/
}

nlohmann::json Framework::Graphics::Camera::Save() {
    nlohmann::json camera;
    camera["Camera"]["Far"] = m_far;
    camera["Camera"]["Near"] = m_near;

    camera["Camera"]["PostProcessing"]["ColorCorrection"] = {
            m_postProcessing->GetColorCorrection().r,
            m_postProcessing->GetColorCorrection().g,
            m_postProcessing->GetColorCorrection().b
        };
    camera["Camera"]["PostProcessing"]["Gamma"] = m_postProcessing->GetGamma();

    return camera;
}

/*
void Framework::Graphics::Camera::AwaitFree() {
    ret:
    if (m_isUse) {
        if (m_window)
            if (m_window->IsWindowOpen())
                goto ret;
    }
    this->Free();
}*/

bool Framework::Graphics::Camera::Free() {
    ///if (m_isUse && m_window && m_window->IsWindowOpen()) {
     //   Debug::Error("Camera::Free() : camera used now!");
    //    return false;
    //}
    //else{
        Debug::Log("Camera::Free() : free camera pointer...");
        this->m_postProcessing->Free();
        delete this;
        return true;
   // }
}

