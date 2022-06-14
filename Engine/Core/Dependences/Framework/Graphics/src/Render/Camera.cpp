//
// Created by Nikita on 18.11.2020.
//

#include <Render/Camera.h>
#include <Render/CameraManager.h>
#include <Window/Window.h>
#include <Utils/Types/DataStorage.h>

namespace SR_GRAPH_NS {
    Camera::Camera()
        : m_pipeline(Environment::Get()->GetPipeLine())
    {
        SR_UTILS_NS::Component::InitComponent<Camera>();
        CameraManager::Instance().RegisterCamera(this);
    }

    void Camera::OnDestroy() {
        CameraManager::Instance().DestroyCamera(this);
        Component::OnDestroy();
    }

    SR_HTYPES_NS::Marshal Camera::Save(Framework::Helper::SavableFlags flags) const {
        SR_HTYPES_NS::Marshal marshal = Component::Save(flags);

        marshal.Write(m_far);
        marshal.Write(m_near);
        marshal.Write(m_FOV);

        return marshal;
    }

    SR_UTILS_NS::Component * Camera::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        const auto&& _far = marshal.Read<float_t>();
        const auto&& _near = marshal.Read<float_t>();
        const auto&& FOV = marshal.Read<float_t>();

        auto&& pWindow = dataStorage->GetPointer<Window>();

        if (!SRVerifyFalse(!pWindow)) {
            return nullptr;
        }

        auto&& viewportSize = pWindow->GetWindowSize();

        if (auto&& pCamera = Allocate(viewportSize.x, viewportSize.y)) {
            pCamera->SetFar(_far);
            pCamera->SetNear(_near);
            pCamera->SetFOV(FOV);

            pCamera->UpdateView();
            pCamera->UpdateProjection();

            return pCamera;
        }

        return nullptr;
    }

    void Camera::UpdateView() noexcept {
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

    void Camera::OnRotate(const SR_MATH_NS::FVector3& newValue) {
        m_yaw   = float_t(newValue.y * 3.14 / 45.f / 4.f);
        m_pitch = float_t(newValue.x * 3.14 / 45.f / 4.f);
        m_roll  = float_t(newValue.z * 3.14 / 45.f / 4.f);

        UpdateView();
    }

    void Camera::OnMove(const SR_MATH_NS::FVector3& newValue) {
        m_position = newValue;
        UpdateView();
    }

    void Camera::UpdateProjection() {
        if (m_viewportSize.HasZero()) {
            SRHalt("Camera::UpdateProjection() : viewport size has zero!");
            m_aspect = 0.f;
        }
        else {
            m_aspect = static_cast<float_t>(m_viewportSize.x) / static_cast<float_t>(m_viewportSize.y);
        }

        m_projection = glm::perspective(glm::radians(m_FOV), m_aspect, m_near, m_far);
    }

    void Camera::UpdateProjection(uint32_t w, uint32_t h) {
        m_viewportSize = { (int32_t)w, (int32_t)h };
        UpdateProjection();
    }

    Camera* Camera::Allocate(uint32_t width, uint32_t height) {
        auto&& camera = new Camera();
        camera->m_viewportSize = { (int32_t)width, (int32_t)height };
        camera->UpdateProjection();
        camera->UpdateView();
        return camera;
    }

    glm::mat4 Camera::GetImGuizmoView() const noexcept {
        auto matrix = glm::rotate(glm::mat4(1), m_pitch, { 1, 0, 0 });
        matrix = glm::rotate(matrix, m_yaw + (float)Deg180InRad, { 0, 1, 0 });
        matrix = glm::rotate(matrix, m_roll, { 0, 0, 1 });

        return glm::translate(matrix, {
                m_position.x,
                -m_position.y,
                -m_position.z
        });
    }

    void Camera::SetFar(float_t value) {
        m_far = value;
        UpdateProjection();
    }

    void Camera::SetNear(float_t value) {
        m_near = value;
        UpdateProjection();
    }

    void Camera::SetFOV(float_t value) {
        m_FOV = value;
        UpdateProjection();
    }

    void Camera::OnEnabled() {
        Environment::Get()->SetBuildState(false);
        Component::OnEnabled();
    }

    void Camera::OnDisabled() {
        Environment::Get()->SetBuildState(false);
        Component::OnDisabled();
    }
}