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
        : Super()
        , m_viewportSize(SR_MATH_NS::UVector2(width, height))
    {
        if (width != 0 && height != 0) {
            UpdateProjection();
            UpdateView();
        }
    }

    Camera::~Camera() {
        if (m_renderTechnique.pTechnique) {
            if (auto&& pResource = dynamic_cast<SR_UTILS_NS::IResource*>( m_renderTechnique.pTechnique)) {
                pResource->RemoveUsePoint();
            }
            else {
                SRHalt0();
            }
            m_renderTechnique.pTechnique = nullptr;
        }
    }

    void Camera::OnAttached() {
        Component::OnAttached();

        if (auto&& pRenderScene = GetRenderScene(); pRenderScene.RecursiveLockIfValid()) {
            pRenderScene->Register(GetThis().DynamicCast<Camera>());
            pRenderScene.Unlock();
            m_isRegistered = true;
        }
        else {
            SRHalt("Render scene is invalid!");
        }
    }

    void Camera::OnDestroy() {
        RenderScene::Ptr pRenderScene = TryGetRenderScene();

        Super::OnDestroy();

        if (m_isRegistered && pRenderScene.RecursiveLockIfValid()) {
            pRenderScene->Remove(GetThis().DynamicCast<Camera>());
            pRenderScene.Unlock();
        }

        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    SR_HTYPES_NS::Marshal::Ptr Camera::Save(SR_UTILS_NS::SavableContext data) const {
        auto&& pMarshal = Component::Save(data);

        pMarshal->Write<std::string>(m_renderTechnique.path.ToStringRef());
        pMarshal->Write<float_t>(m_far);
        pMarshal->Write<float_t>(m_near);
        pMarshal->Write<float_t>(m_FOV);
        pMarshal->Write<int32_t>(m_priority);

        return pMarshal;
    }

    SR_UTILS_NS::Component* Camera::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        const auto&& renderTechniquePath = marshal.Read<std::string>();
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
        pCamera->SetRenderTechnique(renderTechniquePath);

        pCamera->UpdateView();
        pCamera->UpdateProjection();

        return pCamera;
    }

    IRenderTechnique* Camera::GetRenderTechnique() {
        if (m_renderTechnique.pTechnique || m_hasErrors) {
            return m_renderTechnique.pTechnique;
        }

        auto&& path = GetRenderTechniquePath();

        if (path.GetExtensionView() == "srlm") {
            m_renderTechnique.pTechnique = ScriptableRenderTechnique::Load(path);
        }
        else {
            m_renderTechnique.pTechnique = RenderTechnique::Load(path);
        }

        if (m_renderTechnique.pTechnique) {
            m_renderTechnique.pTechnique->SetCamera(this);
            m_renderTechnique.pTechnique->SetRenderScene(GetRenderScene());
        }

        if (auto&& pResourceRenderTechnique = dynamic_cast<SR_UTILS_NS::IResource*>(m_renderTechnique.pTechnique)) {
            pResourceRenderTechnique->AddUsePoint();
        }

        return m_renderTechnique.pTechnique;
    }

    const SR_UTILS_NS::Path& Camera::GetRenderTechniquePath() {
        /// default technique
        if (m_renderTechnique.path.Empty()) {
            m_renderTechnique.path = RenderTechnique::DEFAULT_RENDER_TECHNIQUE;
        }

        return m_renderTechnique.path;
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
        m_viewMat = m_rotation.RotateX(SR_DEG(SR_PI)).Inverse().ToMat4x4();
        m_viewTranslateMat = m_viewMat.Translate(m_position.Inverse());
        m_viewDirection = m_rotation * SR_MATH_NS::FVector3(0, 0, 1);
    }

    void Camera::UpdateProjection() {
        if (m_viewportSize.HasZero()) {
            SRHalt("Camera::UpdateProjection() : viewport size has zero!");
            m_aspect = 0.f;
        }
        else {
            m_aspect = static_cast<float_t>(m_viewportSize.x) / static_cast<float_t>(m_viewportSize.y);
        }

        m_projection = SR_MATH_NS::Matrix4x4::Perspective(SR_RAD(m_FOV), m_aspect, m_near, m_far);

        //////////////////////////////////////////////////////////////////////////////////////////////

        m_orthogonal = SR_MATH_NS::Matrix4x4::Identity();

        m_orthogonal[0][0] = 1.f / m_aspect;
        m_orthogonal[1][1] = -1.f;
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

    SR_MATH_NS::Matrix4x4 Camera::GetImGuizmoView() const noexcept {
        /// TODO: optimize

        SR_MATH_NS::Matrix4x4 matrix = SR_MATH_NS::Matrix4x4::Identity();

        SR_MATH_NS::FVector3 eulerAngles = m_rotation.EulerAngle();

        matrix = matrix.RotateAxis(SR_MATH_NS::FVector3(1, 0, 0), eulerAngles.x);
        matrix = matrix.RotateAxis(SR_MATH_NS::FVector3(0, 1, 0), eulerAngles.y + 180);
        matrix = matrix.RotateAxis(SR_MATH_NS::FVector3(0, 0, 1), eulerAngles.z);

        matrix = matrix.Translate(m_position.InverseAxis(SR_MATH_NS::AXIS_YZ));

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

        pTransform->GetMatrix().Decompose(m_position, m_rotation);

        UpdateView();

        Component::OnMatrixDirty();
    }

    void Camera::SetRenderTechnique(const SR_UTILS_NS::Path& path) {
        if (m_renderTechnique.pTechnique) {
            if (auto&& pResource = dynamic_cast<SR_UTILS_NS::IResource*>(m_renderTechnique.pTechnique)) {
                pResource->RemoveUsePoint();
            }
            else {
                SRHalt("Render technique is not a resource! Memory leak possible.");
            }
            m_renderTechnique.pTechnique = nullptr;
        }

        m_hasErrors = false;
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

    const SR_MATH_NS::FVector3& Camera::GetViewDirection() const {
        return m_viewDirection;
    }

    SR_MATH_NS::FVector3 Camera::GetViewDirection(const SR_MATH_NS::FVector3& pos) const noexcept {
        auto&& dir = m_position.Direction(pos);
        return m_rotation * SR_MATH_NS::FVector3(dir);
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

    SR_MATH_NS::FVector3 Camera::GetViewPosition() const {
        return m_position;
    }

    void Camera::Update(float_t dt) {
        if (auto&& pScriptable = dynamic_cast<SR_GRAPH_NS::ScriptableRenderTechnique*>(m_renderTechnique.pTechnique)) {
            pScriptable->UpdateMachine(dt);
        }

        Super::Update(dt);
    }

    void Camera::Start() {
        Super::Start();
    }
}