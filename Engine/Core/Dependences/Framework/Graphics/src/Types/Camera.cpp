//
// Created by Nikita on 18.11.2020.
//

#include <Types/Camera.h>
#include <Memory/CameraManager.h>
#include <Window/Window.h>
#include <Utils/Types/DataStorage.h>
#include <Render/RenderTechnique.h>
#include <Utils/Types/SafePtrLockGuard.h>

namespace SR_GTYPES_NS {
    Camera::Camera(uint32_t width, uint32_t height)
        : m_viewportSize(SR_MATH_NS::IVector2(width, height))
    {
        SR_UTILS_NS::Component::InitComponent<Camera>();

        UpdateProjection();
        UpdateView();
    }

    Camera::~Camera() {
        std::visit([this](RenderTechniquePtr&& arg) {
            if (std::holds_alternative<RenderTechnique *>(arg)) {
                std::get<RenderTechnique*>(arg)->RemoveUsePoint();
            }
        }, m_renderTechnique);
    }

    void Camera::OnAttached() {
        Component::OnAttached();

        if (auto&& renderScene = GetRenderScene(); renderScene.RecursiveLockIfValid()) {
            renderScene->Register(this);
            renderScene.Unlock();
        }
        else {
            SRHalt("Render scene is invalid!");
        }

        /*auto&& cameraManager = Memory::CameraManager::Instance();

        /// Что-то пошло не так, возможно переподсоединили компонент во время уничтожения объекта.
        if (cameraManager.IsDestroyed(this)) {
            SRHalt("Camera is destroyed! Crash possible!");
            return;
        }

        /// Возможно компонент был переподсоиденен, стоит его перезарегистрировать
        if (cameraManager.IsRegistered(this)) {
            cameraManager.UnRegisterCamera(this);
        }

        cameraManager.RegisterCamera(this);*/
    }

    void Camera::OnDestroy() {
        if (auto&& renderScene = GetRenderScene(); renderScene.RecursiveLockIfValid()) {
            renderScene->Remove(this);
            renderScene.Unlock();
        }
        else {
            SRHalt("Render scene is invalid!");
        }

        //Memory::CameraManager::Instance().DestroyCamera(this);
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

        auto&& pCamera = new Camera(viewportSize.x, viewportSize.y);

        pCamera->SetFar(_far);
        pCamera->SetNear(_near);
        pCamera->SetFOV(FOV);

        pCamera->UpdateView();
        pCamera->UpdateProjection();

        return pCamera;
    }

    RenderTechnique *Camera::GetRenderTechnique() {
        return std::visit([this](RenderTechniquePtr&& arg) -> RenderTechnique* {
            if (std::holds_alternative<RenderTechnique*>(arg)) {
                return std::get<RenderTechnique*>(arg);
            }
            else {
                auto&& path = std::get<SR_UTILS_NS::Path>(arg);

                /// default technique
                if (path.Empty()) {
                    path = "Engine/MainRenderTechnique.xml";
                }

                if (auto&& pRenderTechnique = RenderTechnique::Load(path)) {
                    pRenderTechnique->SetCamera(this);
                    pRenderTechnique->SetRenderScene(GetRenderScene());
                    pRenderTechnique->AddUsePoint();

                    m_renderTechnique = pRenderTechnique;

                    return GetRenderTechnique();
                }

                return nullptr;
            }
        }, m_renderTechnique);
    }

    Camera::RenderScenePtr Camera::GetRenderScene() const {
        auto&& scene = GetScene();

        SR_HTYPES_NS::SafePtrRecursiveLockGuard m_lock(scene);

        if (scene.Valid()) {
            return scene->GetDataStorage().GetValue<RenderScenePtr>();
        }
        else {
            SRHalt("Scene is invalid!");
        }

        return RenderScenePtr();
    }

    void Camera::UpdateView() noexcept {
        glm::mat4 matrix(1.f);

        /// Vulkan implementation
        matrix = glm::rotate(matrix, -m_pitch + float_t(M_PI), { 1, 0, 0 });
        matrix = glm::rotate(matrix, -m_yaw,  { 0, 1, 0 });
        matrix = glm::rotate(matrix, -m_roll,  { 0, 0, 1 });

        m_viewTranslateMat = glm::translate(matrix, -m_position.ToGLM());

        m_viewMat = matrix;
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
        if (auto&& renderScene = GetRenderScene(); renderScene.RecursiveLockIfValid()) {
            renderScene->SetDirtyCameras();
            renderScene.Unlock();
        }

        //Environment::Get()->SetBuildState(false);
        Component::OnEnabled();
    }

    void Camera::OnDisabled() {
        if (auto&& renderScene = GetRenderScene(); renderScene.RecursiveLockIfValid()) {
            renderScene->SetDirtyCameras();
            renderScene.Unlock();
        }

        //Environment::Get()->SetBuildState(false);
        Component::OnDisabled();
    }
}