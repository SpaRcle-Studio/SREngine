//
// Created by Nikita on 18.11.2020.
//

#include <Render/Camera.h>
#include <Window/Window.h>
#include <GUI.h>

Framework::Graphics::Camera::Camera()
    : m_pipeline(Environment::Get()->GetPipeLine())
{
    SR_UTILS_NS::Component::InitComponent<Camera>();
}

void Framework::Graphics::Camera::UpdateShaderProjView(Framework::Graphics::Shader *shader) noexcept {
    if (!m_isCreate) {
        SR_WARN("Camera::UpdateShaderProjView() : camera is not create! Something went wrong...");
        return;
    }

    //if (m_needUpdate) {
    //    if (!CompleteResize()) {
   //         SR_ERROR("Camera::UpdateShaderProjView() : failed to complete resize!");
    //        return;
    //    }
   // }
}

bool Framework::Graphics::Camera::Create(Framework::Graphics::Window *window) {
    Debug::Graph("Camera::Create() : creating camera...");
    if (m_isCreate) {
        SR_ERROR("Camera::Create() : camera already create!");
        return false;
    }

    m_window = window;

    UpdateView();

    if (!m_isCalculate)
        Calculate();

    m_isCreate = true;

    return true;
}

void Framework::Graphics::Camera::UpdateView() noexcept {
    glm::mat4 matrix(1.f);

    if (m_pipeline == PipeLine::OpenGL) {
        matrix = glm::rotate(matrix, m_pitch, { 1, 0, 0 });
        matrix = glm::rotate(matrix, m_yaw + float(180.f * 3.14 / 45.f / 4.f), { 0, 1, 0 });
        matrix = glm::rotate(matrix, m_roll,   { 0, 0, 1 });

        m_viewMat = matrix;

        m_viewTranslateMat = glm::translate(matrix, {
                m_position.x,
                -m_position.y,
                -m_position.z//-m_pos.z
        });
    }
    else {
        matrix = glm::rotate(matrix, -m_pitch + float(M_PI), { 1, 0, 0 });
        matrix = glm::rotate(matrix, -m_yaw,  { 0, 1, 0 });
        matrix = glm::rotate(matrix, -m_roll,  { 0, 0, 1 });

        m_viewMat = matrix;

        m_viewTranslateMat = glm::translate(matrix, -m_position.ToGLM());
    }
}

void Framework::Graphics::Camera::OnRotate(const Math::FVector3& newValue) {
    m_yaw   = float_t(newValue.y * 3.14 / 45.f / 4.f);
    m_pitch = float_t(newValue.x * 3.14 / 45.f / 4.f);
    m_roll  = float_t(newValue.z * 3.14 / 45.f / 4.f);

    UpdateView();
}

void Framework::Graphics::Camera::OnMove(const Math::FVector3& newValue) {
    m_position = newValue;
    UpdateView();
}

void Framework::Graphics::Camera::UpdateProjection() {
    if (m_cameraSize.HasZero()) {
        SR_WARN("Camera::UpdateProjection() : camera size has zero!");
        m_aspect = 0.f;
    }
    else {
        m_aspect = static_cast<float_t>(m_cameraSize.x) / static_cast<float_t>(m_cameraSize.y);
    }

    m_projection = glm::perspective(glm::radians(m_FOV), m_aspect, m_near, m_far);
}

void Framework::Graphics::Camera::UpdateProjection(uint32_t w, uint32_t h) {
    m_cameraSize = { (int32_t)w, (int32_t)h };
    UpdateProjection();
}

bool Framework::Graphics::Camera::Calculate() noexcept {
    if (m_isCalculate)
        return false;

    SR_GRAPH_LOG("Camera::Calculate() : calculating camera...");

    m_isCalculate = true;

    return true;
}

void Framework::Graphics::Camera::OnDestroy() {
    if (m_window) {
        m_window->DestroyCamera(this);
        m_window = nullptr;
    }
}

bool Framework::Graphics::Camera::Free() {
    SR_GRAPH_LOG("Camera::Free() : free camera pointer...");

    delete this;
    return true;
}

Framework::Graphics::Camera *Framework::Graphics::Camera::Allocate(uint32_t width, uint32_t height) {
    auto&& camera = new Camera();
    camera->m_cameraSize = { (int32_t)width, (int32_t)height };
    camera->UpdateProjection();
    return camera;
}

bool Framework::Graphics::Camera::CompleteResize() {
    if (m_cameraSize.x <= 0 || m_cameraSize.y <= 0) {
        SR_ERROR("Camera::CompleteResize() : camera width or height equals or less zero!");
        return false;
    }

    UpdateProjection();

    m_isBuffCalculate = true;

    return true;
}

glm::mat4 Framework::Graphics::Camera::GetImGuizmoView() const noexcept {
    auto matrix = glm::rotate(glm::mat4(1), m_pitch, { 1, 0, 0 });
    matrix = glm::rotate(matrix, m_yaw + (float)Deg180InRad, { 0, 1, 0 });
    matrix = glm::rotate(matrix, m_roll, { 0, 0, 1 });

    return glm::translate(matrix, {
            m_position.x,
            -m_position.y,
            -m_position.z
    });
}

void Framework::Graphics::Camera::WaitBuffersCalculate() const {
ret:
    if (!m_isBuffCalculate)
        goto ret;
}

void Framework::Graphics::Camera::WaitCalculate() const  {
ret:
    if (!m_isCalculate)
        goto ret;
}

void Framework::Graphics::Camera::SetFar(float_t value) {
    m_far = value;
    UpdateProjection();
}

void Framework::Graphics::Camera::SetNear(float_t value) {
    m_near = value;
    UpdateProjection();
}

void Framework::Graphics::Camera::SetFOV(float_t value) {
    m_FOV = value;
    UpdateProjection();
}






