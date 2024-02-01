//
// Created by Monika on 23.11.2023.
//

#include <Graphics/UI/Gizmo.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/GUI/ImGUI.h>

#include <Utils/ECS/ComponentManager.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/DebugDraw.h>

namespace SR_GRAPH_UI_NS {
    SR_REGISTER_COMPONENT(Gizmo);

    SR_UTILS_NS::Component* Gizmo::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        return SR_UTILS_NS::ComponentManager::Instance().CreateComponent<Gizmo>();
    }

    void Gizmo::OnAttached() {
        GetGameObject()->SetLayer("Gizmo");
        GetGameObject()->GetOrAddChild("Selection")->SetLayer("GizmoSelection");
        Super::OnAttached();
    }

    void Gizmo::OnDestroy() {
        ReleaseGizmo();

        Super::OnDestroy();

        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void Gizmo::LoadMesh(GizmoOperationFlag operation, SR_UTILS_NS::StringAtom path, SR_UTILS_NS::StringAtom name, GizmoMeshLoadMode mode) { /// NOLINT
        if (mode == GizmoMeshLoadMode::All) {
            LoadMesh(operation, path, name, GizmoMeshLoadMode::Visual);
            LoadMesh(operation, path, name, GizmoMeshLoadMode::Selection);
            return;
        }

        if (!GetGameObject()) {
            return;
        }

        auto&& pMesh = SR_GTYPES_NS::Mesh::Load(path, MeshType::Static, name);
        if (!pMesh) {
            SR_ERROR("Gizmo::LoadMesh() : failed to load mesh!\n\tPath: {}\n\tName: {}", path.ToStringRef(), name.ToStringRef());
            return;
        }

        auto&& pMeshComponent = dynamic_cast<SR_GTYPES_NS::MeshComponent*>(pMesh);
        if (!pMeshComponent) {
            SRHalt("Failed to cast!");
            return;
        }

        pMeshComponent->SetDontSave(true);

        if (operation & GizmoOperation::X) {
            pMeshComponent->SetMaterial("Engine/Materials/Colors/gizmo-x.mat");
        }
        else if (operation & GizmoOperation::Y) {
            pMeshComponent->SetMaterial("Engine/Materials/Colors/gizmo-y.mat");
        }
        else if (operation & GizmoOperation::Z) {
            pMeshComponent->SetMaterial("Engine/Materials/Colors/gizmo-z.mat");
        }
        else if (operation & GizmoOperation::Center) {
            pMeshComponent->SetMaterial("Engine/Materials/Colors/gizmo-center.mat");
        }

        if (mode == GizmoMeshLoadMode::Visual) {
            GetGameObject()->AddComponent(pMeshComponent);
            m_meshes[operation].pVisual = pMeshComponent;
        }
        else if (mode == GizmoMeshLoadMode::Selection) {
            GetGameObject()->GetOrAddChild("Selection")->AddComponent(pMeshComponent);
            m_meshes[operation].pSelection = pMeshComponent;
        }
        else {
            SRHalt("Unresolved situation!");
        }
    }

    void Gizmo::OnEnable() {
        LoadGizmo();
        Super::OnEnable();
    }

    void Gizmo::LoadGizmo() {
        SRAssert(m_meshes.empty());

        static const SR_UTILS_NS::StringAtom gizmoFile = "Engine/Models/gizmo-translation.fbx";

        LoadMesh(GizmoOperation::Center, gizmoFile, "Center", GizmoMeshLoadMode::Visual);
        LoadMesh(GizmoOperation::Center, gizmoFile, "CenterSelection", GizmoMeshLoadMode::Selection);

        LoadMesh(GizmoOperation::TranslateAltX, gizmoFile, "PlaneX", GizmoMeshLoadMode::All);
        LoadMesh(GizmoOperation::TranslateAltY, gizmoFile, "PlaneY", GizmoMeshLoadMode::All);
        LoadMesh(GizmoOperation::TranslateAltZ, gizmoFile, "PlaneZ", GizmoMeshLoadMode::All);

        LoadMesh(GizmoOperation::TranslateX, gizmoFile, "ArrowX", GizmoMeshLoadMode::Visual);
        LoadMesh(GizmoOperation::TranslateY, gizmoFile, "ArrowY", GizmoMeshLoadMode::Visual);
        LoadMesh(GizmoOperation::TranslateZ, gizmoFile, "ArrowZ", GizmoMeshLoadMode::Visual);

        LoadMesh(GizmoOperation::TranslateX, gizmoFile, "ArrowXSelection", GizmoMeshLoadMode::Selection);
        LoadMesh(GizmoOperation::TranslateY, gizmoFile, "ArrowYSelection", GizmoMeshLoadMode::Selection);
        LoadMesh(GizmoOperation::TranslateZ, gizmoFile, "ArrowZSelection", GizmoMeshLoadMode::Selection);

        m_lastMousePos = SR_MATH_NS::FPoint(SR_FLOAT_MAX);
    }

    void Gizmo::ReleaseGizmo() {
        for (auto&& [operation, info] : m_meshes) {
            if (info.pSelection) {
                info.pSelection->Detach();
            }
            if (info.pVisual) {
                info.pVisual->Detach();
            }
        }
        m_meshes.clear();
    }

    void Gizmo::OnDisable() {
        ReleaseGizmo();
        Super::OnDisable();
    }

    void Gizmo::FixedUpdate() {
        SR_TRACY_ZONE;

        auto&& pCamera = GetCamera();
        if (!pCamera) {
            return;
        }

        /*if (SR_UTILS_NS::Input::Instance().GetMouseDown(Utils::MouseCode::MouseLeft)) {
            auto&& worldPos = GetCamera()->ScreenToWorldPoint(GetCamera()->GetMousePos(), 10.f);
            GetTransform()->SetTranslation(worldPos);

            auto&& forward = GetCamera()->GetRotation() * SR_UTILS_NS::Transform3D::FORWARD;

            auto&& ray = GetCamera()->GetScreenRay(GetCamera()->GetMousePos());
            SR_UTILS_NS::DebugDraw::Instance().DrawLine(forward + GetCamera()->GetPosition(), worldPos, SR_MATH_NS::FColor(255, 0, 0, 255), 10.f);
            SR_UTILS_NS::DebugDraw::Instance().DrawLine(forward + ray.origin, ray.origin + ray.direction, SR_MATH_NS::FColor(0, 255, 0, 255), 10.f);
        }*/

        auto&& pTechnique = pCamera->GetRenderTechnique();
        if (!pTechnique) {
            return;
        }

        if (m_zoomFactor > 0.f) {
            auto&& modelMatrix = SR_MATH_NS::Matrix4x4::FromTranslate(GetTransform()->GetTranslation());
            const float_t screenFactor = GetCamera()->CalculateScreenFactor(modelMatrix, m_zoomFactor);
            GetTransform()->SetScale(screenFactor);
        }

        if (!SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseLeft)) {
            m_activeOperation = GizmoOperation::None;
        }

        m_modelMatrix = SR_MATH_NS::Matrix4x4::FromTranslate(GetTransform()->GetTranslation());

        if (m_activeOperation == GizmoOperation::None) {
            auto&& pMesh = pTechnique->PickMeshAt(pCamera->GetMousePos());
            for (auto&& [flag, info] : m_meshes) {
                if (pMesh == info.pSelection.Get()) {
                    info.pVisual->OverrideUniform("color")
                        .SetData(SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f))
                        .SetShaderVarType(ShaderVarType::Vec4);

                    if (SR_UTILS_NS::Input::Instance().GetMouseDown(SR_UTILS_NS::MouseCode::MouseLeft)) {
                        m_activeOperation = flag;

                        const float_t screenFactor = GetCamera()->CalculateScreenFactor(m_modelMatrix, m_moveFactor);

                        m_translationPlan = m_modelMatrix.BuildTranslationPlan(SR_MATH_NS::AXIS_Z, GetCamera()->GetViewTranslate());
                        auto&& screenRay = GetCamera()->GetScreenRay(pCamera->GetMousePos());
                        const float len = m_translationPlan.IntersectRayPlane(screenRay.origin, screenRay.direction);
                        auto&& translationPlanOrigin = screenRay.origin + screenRay.direction * len;

                        m_relativeOrigin = (translationPlanOrigin - m_modelMatrix.v.position.XYZ()) * (1.f / screenFactor);

                        SR_UTILS_NS::DebugDraw::Instance().DrawLine(m_translationPlan.x, m_translationPlan.y, SR_MATH_NS::FColor(0, 0, 255, 255), 20.f);
                        SR_UTILS_NS::DebugDraw::Instance().DrawLine(m_translationPlan.y, m_translationPlan.z, SR_MATH_NS::FColor(0, 0, 255, 255), 20.f);
                        SR_UTILS_NS::DebugDraw::Instance().DrawLine(m_translationPlan.z, m_translationPlan.w, SR_MATH_NS::FColor(0, 0, 255, 255), 20.f);
                        SR_UTILS_NS::DebugDraw::Instance().DrawLine(m_translationPlan.w, m_translationPlan.x, SR_MATH_NS::FColor(0, 0, 255, 255), 20.f);

                        SR_LOG("Gizmo selected!");
                    }
                }
                else {
                    info.pVisual->RemoveUniformOverride("color");
                }
            }
        }

        ProcessGizmo();

        Super::FixedUpdate();
    }

    bool Gizmo::InitializeEntity() noexcept {
        GetComponentProperties()
            .AddStandardProperty("Zoom factor", &m_zoomFactor)
            .SetResetValue(0.1f)
            .SetDrag(0.05f)
            .SetWidth(60.f);
        GetComponentProperties()

            .AddStandardProperty("Move factor", &m_moveFactor)
            .SetResetValue(0.1f)
            .SetDrag(0.05f)
            .SetWidth(60.f);

        return Super::InitializeEntity();
    }

    void Gizmo::ProcessGizmo() {
        auto&& mousePos = GetCamera()->GetMousePos();
        if (m_lastMousePos == SR_MATH_NS::InfinityFV2) {
            m_lastMousePos = mousePos;
            return;
        }

        if (SR_UTILS_NS::Input::Instance().GetMouse(Utils::MouseCode::MouseLeft)) {

        }

        if (SR_UTILS_NS::Input::Instance().GetMouse(Utils::MouseCode::MouseLeft)) {
            const float_t cameraDistance = GetCamera()->GetPosition().Distance(GetTransform()->GetTranslation());

            //auto&& forward = GetCamera()->GetRotation() * SR_UTILS_NS::Transform3D::FORWARD * 10.f;

            auto&& modelMatrix = SR_MATH_NS::Matrix4x4::FromTranslate(GetTransform()->GetTranslation());
            auto&& viewMatrix = GetCamera()->GetView();
            const float_t screenFactor = GetCamera()->CalculateScreenFactor(modelMatrix, viewMatrix, m_moveFactor);

            auto&& worldDirection = GetCamera()->ScreenToWorldPoint(GetCamera()->GetMousePos(), screenFactor);
            auto&& lastPos = GetCamera()->ScreenToWorldPoint(m_lastMousePos, screenFactor);

            //SR_UTILS_NS::DebugDraw::Instance().DrawLine(lastPos, worldDirection, SR_MATH_NS::FColor(255, 0, 0, 255), 10.f);

            //GetTransform()->SetTranslation(worldDirection);
        }

        if (m_activeOperation == GizmoOperation::None) {
            m_relativeOrigin = SR_MATH_NS::InfinityFV3;
            return;
        }

        if (m_activeOperation & GizmoOperation::TranslateZ) {
            auto&& screenRay = GetCamera()->GetScreenRay(mousePos);

            const float_t screenFactor = GetCamera()->CalculateScreenFactor(m_modelMatrix, m_moveFactor);

            const float_t signedLength = m_translationPlan.IntersectRayPlane(screenRay.origin, screenRay.direction);
            const float_t len = fabsf(signedLength); /// near plan
            auto&& newPos = screenRay.origin + screenRay.direction * len;

            auto&& newOrigin = newPos - m_relativeOrigin * screenFactor;
            auto&& delta = newOrigin - m_modelMatrix.v.position.XYZ();

            auto&& axisValue = m_modelMatrix.value[2 /** z */].XYZ();
            const float lengthOnAxis = axisValue.Dot(delta);
            delta = axisValue * lengthOnAxis;

            //SR_UTILS_NS::DebugDraw::Instance().DrawLine(screenRay.origin, newPos, SR_MATH_NS::FColor(0, 255, 0, 255), 10.f);

            GetTransform()->Translate(0, 0, delta.z);
            //GetTransform()->SetTranslation(0, 0, newPos.z);
        }

        if (m_activeOperation & GizmoOperation::TranslateZ && false) {
            const float_t cameraDistance = GetCamera()->GetPosition().Distance(GetTransform()->GetTranslation());

            //auto&& modelMatrix = SR_MATH_NS::Matrix4x4::FromTranslate(GetTransform()->GetTranslation());
            auto&& modelMatrix = SR_MATH_NS::Matrix4x4::Identity();
            auto&& viewMatrix = GetCamera()->GetView();
            const float_t screenFactor = GetCamera()->CalculateScreenFactor(modelMatrix, viewMatrix, m_moveFactor * cameraDistance);

            //auto&& worldDirection = GetCamera()->ScreenToWorldPoint(mousePos, cameraDistance);
            //GetTransform()->SetTranslation(0, 0, worldDirection.z);

            //SR_UTILS_NS::DebugDraw::Instance().DrawLine(worldDirection, worldDirection + SR_MATH_NS::FVector3(SR_EPSILON), SR_MATH_NS::FColor(255, 0, 0, 255), 10.f);

            auto&& lastPos = GetCamera()->ScreenToWorldPoint(m_lastMousePos, screenFactor);
            auto&& currentPos = GetCamera()->ScreenToWorldPoint(GetCamera()->GetMousePos(), screenFactor);

            const float_t distance = lastPos.Distance(currentPos);

            auto&& forwardMouse = (currentPos - lastPos).Normalize();
            auto&& forwardGizmo = (GetTransform()->GetQuaternion() * SR_UTILS_NS::Transform3D::FORWARD).Normalize();

            const float_t angle = forwardGizmo.AngleCoefficient(forwardMouse);

            if (angle < 0.f) {
                GetTransform()->Translate(0, 0, -distance);
            }
            else {
                GetTransform()->Translate(0, 0, distance);
            }

            SR_UTILS_NS::DebugDraw::Instance().DrawLine(lastPos, currentPos, SR_MATH_NS::FColor(255, 0, 0, 255), 10.f);
            //SR_UTILS_NS::DebugDraw::Instance().DrawLine(lastPos, lastPos + forwardGizmo, SR_MATH_NS::FColor(0, 255, 0, 255), 10.f);

            //auto&& forward = GetCamera()->GetRotation() * SR_UTILS_NS::Transform3D::FORWARD;

            //SR_UTILS_NS::DebugDraw::Instance().DrawLine(forward + GetCamera()->GetPosition(), worldPos, SR_MATH_NS::FColor(255, 0, 0, 255), 10.f);

            //GetTransform()->SetTranslation(worldPos);

            //float_t deltaX = m_lastMousePos.x - mousePos.x;
            //GetTransform()->Translate(deltaX, 0, 0);

            //auto&& worldPos = GetCamera()->ScreenToWorldPoint(mousePos, 0.f);

            //GetTransform()->SetTranslation(worldPos);
        }

        m_lastMousePos = mousePos;
    }
}