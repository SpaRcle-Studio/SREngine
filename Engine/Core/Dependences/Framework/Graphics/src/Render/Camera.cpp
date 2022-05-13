//
// Created by Nikita on 18.11.2020.
//

#include <Render/Camera.h>
#include <Window/Window.h>
#include <GUI.h>

Framework::Graphics::Camera::Camera()
    : m_env(Environment::Get())
    , m_pipeline(Environment::Get()->GetPipeLine())
{
    SR_UTILS_NS::Component::Init<Camera>();
}

void Framework::Graphics::Camera::UpdateShaderProjView(Framework::Graphics::Shader *shader) noexcept {
    if (!m_isCreate) {
        SR_WARN("Camera::UpdateShaderProjView() : camera is not create! Something went wrong...");
        return;
    }

    if (m_needUpdate) {
        if (!CompleteResize()) {
            SR_ERROR("Camera::UpdateShaderProjView() : failed to complete resize!");
            return;
        }
    }

    //shader->SetMat4(SR_RU"viewMat", m_viewTranslateMat);
    //shader->SetMat4("projMat", m_projection);
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
    m_yaw   = float(newValue.y * 3.14 / 45.f / 4.f);
    m_pitch = float(newValue.x * 3.14 / 45.f / 4.f);
    m_roll  = float(newValue.z * 3.14 / 45.f / 4.f);

    UpdateView();
}

void Framework::Graphics::Camera::OnMove(const Math::FVector3& newValue) {
    m_position = newValue;
    UpdateView();
}

void Framework::Graphics::Camera::UpdateProjection() {
    m_projection = glm::perspective(glm::radians(65.f), (float)m_cameraSize.x / (float)m_cameraSize.y, m_near.load(), m_far.load());
}

void Framework::Graphics::Camera::UpdateProjection(unsigned int w, unsigned int h) {
    m_cameraSize = { (int32_t)w, (int32_t)h };
    m_projection = glm::perspective(glm::radians(65.f), (float)w / (float)h, m_near.load(), m_far.load());
    m_needUpdate = true;
}

bool Framework::Graphics::Camera::Calculate() noexcept {
    if (m_isCalculate)
        return false;

    Debug::Graph("Camera::Calculate() : calculating camera...");

    m_postProcessing->Init(m_window->GetRender());

    m_needUpdate = true;
    m_isCalculate = true;

    return true;
}

void Framework::Graphics::Camera::OnDestroyGameObject() {
    if (m_window) {
        m_window->DestroyCamera(this);
        m_window = nullptr;
    }
}

bool Framework::Graphics::Camera::Free() {
    Debug::Graph("Camera::Free() : free camera pointer...");

    m_postProcessing->Destroy();
    m_postProcessing->Free();

    delete this;
    return true;
}

Framework::Graphics::Camera *Framework::Graphics::Camera::Allocate(uint32_t width, uint32_t height) {
    auto camera = new Camera();
    camera->m_postProcessing = PostProcessing::Allocate(camera);
    camera->m_cameraSize = { (int32_t)width, (int32_t)height };
    if (!camera->m_postProcessing) {
        Debug::Error("Camera::Allocate() : failed to allocate post processing!");
        return nullptr;
    }
    return camera;
}

bool Framework::Graphics::Camera::CompleteResize() {
    if (m_cameraSize.x <= 0 || m_cameraSize.y <= 0) {
        SR_ERROR("Camera::CompleteResize() : camera width or height equals or less zero!");
        return false;
    }

    UpdateProjection();

    if (!m_postProcessing->OnResize(m_cameraSize.x, m_cameraSize.y)) {
        Debug::Error("Camera::CompleteResize() : failed recalculated frame buffers!");
        return false;
    }

    m_needUpdate = false;
    m_isBuffCalculate = true;

    return true;
}

void Framework::Graphics::Camera::PoolEvents()  {
    m_isEnableDirectOut.first = m_isEnableDirectOut.second;
}

void Framework::Graphics::Camera::OnReady(bool ready) {
    m_env->SetBuildState(false);
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

void Framework::Graphics::Camera::OnRemoveComponent() {
    OnDestroyGameObject();
}

void Framework::Graphics::Camera::SetDirectOutput(bool value) {
    m_isEnableDirectOut.second = value;
}

void Framework::Graphics::Camera::SetFar(float_t value) {
    m_far = value;
    UpdateProjection();
}

void Framework::Graphics::Camera::SetNear(float_t value) {
    m_near = value;
    UpdateProjection();
}






