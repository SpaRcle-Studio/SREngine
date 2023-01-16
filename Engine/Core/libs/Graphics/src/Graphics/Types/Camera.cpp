//
// Created by Nikita on 18.11.2020.
//

#include <Utils/Types/DataStorage.h>
#include <Utils/Types/SafePtrLockGuard.h>

#include <Graphics/Types/Camera.h>
#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Render/RenderTechnique.h>

#include <Graphics/Window/Window.h>

namespace SR_GTYPES_NS {
    SR_REGISTER_COMPONENT(Camera);

    Camera::Camera(uint32_t width, uint32_t height)
        : m_viewportSize(SR_MATH_NS::UVector2(width, height))
    {
        if (width != 0 && height != 0) {
            UpdateProjection();
            UpdateView();
        }
    }

    Camera::~Camera() {
        if (m_renderTechnique.pTechnique) {
            m_renderTechnique.pTechnique->RemoveUsePoint();
            m_renderTechnique.pTechnique = nullptr;
        }
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
    }

    void Camera::OnDestroy() {
        Component::OnDestroy();

        if (auto&& renderScene = TryGetRenderScene(); renderScene.RecursiveLockIfValid()) {
            renderScene->Remove(this);
            renderScene.Unlock();
        }
        else {
            delete this;
        }
    }

    SR_HTYPES_NS::Marshal::Ptr Camera::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Component::Save(pMarshal, flags);

        pMarshal->Write(m_far);
        pMarshal->Write(m_near);
        pMarshal->Write(m_FOV);
        pMarshal->Write(m_priority);

        return pMarshal;
    }

    SR_UTILS_NS::Component * Camera::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        const auto&& _far = marshal.Read<float_t>();
        const auto&& _near = marshal.Read<float_t>();
        const auto&& FOV = marshal.Read<float_t>();
        const auto&& priority = marshal.Read<int32_t>();

        auto&& pWindow = dataStorage->GetValue<Window::Ptr>();

        if (!SRVerifyFalse(!pWindow)) {
            return nullptr;
        }

        auto&& viewportSize = pWindow->GetSize();

        auto&& pCamera = new Camera(viewportSize.x, viewportSize.y);

        pCamera->SetFar(_far);
        pCamera->SetNear(_near);
        pCamera->SetFOV(FOV);
        pCamera->SetPriority(priority);

        pCamera->UpdateView();
        pCamera->UpdateProjection();

        return pCamera;
    }

    RenderTechnique *Camera::GetRenderTechnique() {
        if (m_renderTechnique.pTechnique) {
            return m_renderTechnique.pTechnique;
        }

        /// default technique
        if (m_renderTechnique.path.Empty()) {
            m_renderTechnique.path = "Engine/Configs/MainRenderTechnique.xml";
        }

        if (auto&& pRenderTechnique = RenderTechnique::Load( m_renderTechnique.path)) {
            pRenderTechnique->SetCamera(this);
            pRenderTechnique->AddUsePoint();
            pRenderTechnique->SetRenderScene(GetRenderScene());

            return (m_renderTechnique.pTechnique = pRenderTechnique);
        }

        return nullptr;
    }

    Camera::RenderScenePtr Camera::TryGetRenderScene() const {
        auto&& scene = TryGetScene();
        if (!scene) {
            return RenderScenePtr();
        }

        SR_HTYPES_NS::SafePtrRecursiveLockGuard m_lock(scene);

        if (scene->Valid()) {
            return scene->GetDataStorage().GetValue<RenderScenePtr>();
        }

        return RenderScenePtr();
    }

    Camera::RenderScenePtr Camera::GetRenderScene() const {
        auto&& renderScene = TryGetRenderScene();

        if (!renderScene) {
            SRHalt("Render scene is nullptr!");
        }

        return renderScene;
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

    void Camera::UpdateProjection() {
        if (m_viewportSize.HasZero()) {
            SRHalt("Camera::UpdateProjection() : viewport size has zero!");
            m_aspect = 0.f;
        }
        else {
            m_aspect = static_cast<float_t>(m_viewportSize.x) / static_cast<float_t>(m_viewportSize.y);
        }

        m_projection = glm::perspective(glm::radians(m_FOV), m_aspect, m_near, m_far);

        //////////////////////////////////////////////////////////////////////////////////////////////

        m_orthogonal = glm::mat4(1);

        m_orthogonal[0][0] = 1.f / m_aspect;
        m_orthogonal[1][1] = 1.f;
        m_orthogonal[2][2] = 1.f / (m_far - m_near);
        m_orthogonal[3][2] = m_near / (m_far - m_near);

        //////////////////////////////////////////////////////////////////////////////////////////////

        if (m_renderTechnique.pTechnique) {
            m_renderTechnique.pTechnique->OnResize(m_viewportSize);
        }
    }

    void Camera::UpdateProjection(uint32_t w, uint32_t h) {
        if (m_viewportSize.x == w && m_viewportSize.y == h) {
            return;
        }

        m_viewportSize = SR_MATH_NS::UVector2(w, h);

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

    glm::mat4 Camera::GetImGuizmo2DView() const noexcept {
        auto matrix = glm::rotate(glm::mat4(1), m_pitch, { 1, 0, 0 });
        matrix = glm::rotate(matrix, m_yaw + (float)Deg180InRad, { 0, 1, 0 });
        matrix = glm::rotate(matrix, m_roll, { 0, 0, 1 });

        return matrix;
    }

    void Camera::SetFar(float_t value) {
        m_far = value;

        if (!m_viewportSize.HasZero()) {
            UpdateProjection();
        }
    }

    void Camera::SetNear(float_t value) {
        m_near = value;

        if (!m_viewportSize.HasZero()) {
            UpdateProjection();
        }
    }

    void Camera::SetFOV(float_t value) {
        m_FOV = value;

        if (!m_viewportSize.HasZero()) {
            UpdateProjection();
        }
    }

    void Camera::OnEnable() {
        if (auto&& renderScene = TryGetRenderScene(); renderScene.RecursiveLockIfValid()) {
            renderScene->SetDirtyCameras();
            renderScene.Unlock();
        }

        Component::OnEnable();
    }

    void Camera::OnDisable() {
        if (auto&& renderScene = GetRenderScene(); renderScene.RecursiveLockIfValid()) {
            renderScene->SetDirtyCameras();
            renderScene.Unlock();
        }

        Component::OnDisable();
    }

    void Camera::OnMatrixDirty() {
        auto&& pTransform = GetTransform();
        if (!pTransform) {
            return;
        }

        auto&& matrix = pTransform->GetMatrix();
        auto&& rotate = matrix.GetQuat().EulerAngle();
        auto&& translation = matrix.GetTranslate();

        m_yaw   = float_t(rotate.y * SR_PI / 45.f / 4.f);
        m_pitch = float_t(rotate.x * SR_PI / 45.f / 4.f);
        m_roll  = float_t(rotate.z * SR_PI / 45.f / 4.f);

        m_position = translation;

        UpdateView();

        Component::OnMatrixDirty();
    }

    void Camera::SetRenderTechnique(const SR_UTILS_NS::Path& path) {
        if (m_renderTechnique.pTechnique) {
            m_renderTechnique.pTechnique->RemoveUsePoint();
            m_renderTechnique.pTechnique = nullptr;
        }

        m_renderTechnique.path = path;
    }

    void Camera::SetPriority(int32_t priority) {
        m_priority = priority;

        if (!m_parent) {
            return;
        }

        GetRenderScene().Do([](auto&& pRenderScene) {
            pRenderScene->SetDirtyCameras();
        });
    }

    glm::vec3 Camera::GetViewDirection() const {
        return (SR_MATH_NS::Quaternion(SR_MATH_NS::FVector3(m_pitch, m_yaw, m_roll)) * SR_MATH_NS::FVector3(1, 0, 0)).ToGLM();
    }

    glm::vec3 Camera::GetViewDirection(const SR_MATH_NS::FVector3 &pos) const noexcept {
        return (SR_MATH_NS::Quaternion(SR_MATH_NS::FVector3(m_pitch, m_yaw, m_roll)) * m_position.Direction(pos)).ToGLM();
    }

    SR_UTILS_NS::Component *Camera::CopyComponent() const {
        auto&& pCamera = new Camera(m_viewportSize.x, m_viewportSize.y);

        pCamera->m_priority = m_priority;

        pCamera->m_far = m_far;
        pCamera->m_near = m_near;
        pCamera->m_aspect = m_aspect;
        pCamera->m_FOV = m_FOV;
        pCamera->m_renderTechnique.path = m_renderTechnique.path;

        return dynamic_cast<Component*>(pCamera);
    }
}