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

    float_t Gizmo::GetSegmentLengthClipSpace(const SR_MATH_NS::FVector4& start, const SR_MATH_NS::FVector4& end, const SR_MATH_NS::Matrix4x4& mvp)
    {
        SR_MATH_NS::FVector4 startOfSegment = start;
        startOfSegment = mvp * startOfSegment;
        if (fabsf(startOfSegment.w) > FLT_EPSILON) // check for axis aligned with camera direction
        {
            startOfSegment *= 1.f / startOfSegment.w;
        }

        SR_MATH_NS::FVector4 endOfSegment = end;
        endOfSegment = mvp * endOfSegment;
        if (fabsf(endOfSegment.w) > FLT_EPSILON) // check for axis aligned with camera direction
        {
            endOfSegment *= 1.f / endOfSegment.w;
        }

        //auto imgSize = GetCamera()->GetActiveViewportSize();
        //const float_t displayRatio = imgSize.x / imgSize.y;

        SR_MATH_NS::FVector4 clipSpaceAxis = endOfSegment - startOfSegment;

        //if (displayRatio < 1.0) {
        //    clipSpaceAxis.x *= displayRatio;
        //}
        //else {
        //    clipSpaceAxis.y /= displayRatio;
        //}

        float segmentLengthInClipSpace = sqrtf(clipSpaceAxis.x * clipSpaceAxis.x + clipSpaceAxis.y * clipSpaceAxis.y);
        return segmentLengthInClipSpace;
    }

    float getScreenSpaceSize(const SR_MATH_NS::Matrix4x4& projectionMatrix, const SR_MATH_NS::Matrix4x4& viewMatrix, float objectSize, float distanceFromCamera) {
        // Преобразование точки объекта в экранные координаты
        SR_MATH_NS::FVector4 objectPoint(0.0f, 0.0f, -distanceFromCamera, 1.0f);

        SR_MATH_NS::Matrix4x4 modelViewMatrix = viewMatrix.Inverse() * SR_MATH_NS::Matrix4x4(1.0f);  // Если у вас есть матрица модели, умножьте ее здесь
        SR_MATH_NS::FVector4 transformedObjectPoint = modelViewMatrix * objectPoint;

        // Преобразование точки в экранные координаты
        SR_MATH_NS::FVector4 screenPoint = projectionMatrix * transformedObjectPoint;

        // Получение глубины экранной точки
        float depth = screenPoint.z / screenPoint.w;

        // Размер в экранных координатах (подразумевается, что distanceFromCamera > 0)
        float screenSize = objectSize * projectionMatrix[1][1] / depth;

        return screenSize;
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
            auto&& mvp = GetCamera()->GetProjection() * GetCamera()->GetViewTranslate();

            const float_t gizmoSizeClipSpace = 0.1f;

            SR_MATH_NS::FVector4 rightViewInverse = GetCamera()->GetViewTranslate().Inverse().v.right;
            rightViewInverse = SR_MATH_NS::Matrix4x4::Identity().TransformVector(rightViewInverse.XYZ());
            float rightLength = mvp.GetSegmentLengthClipSpace(SR_MATH_NS::FVector3(), rightViewInverse.XYZ(), GetCamera()->GetAspect());

            const float_t screenFactor = gizmoSizeClipSpace / rightLength;
            GetTransform()->SetScale(screenFactor * m_zoomFactor);
        }

        if (!SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseLeft)) {
            m_activeOperation = GizmoOperation::None;
        }

        if (m_activeOperation == GizmoOperation::None) {
            auto&& pMesh = pTechnique->PickMeshAt(pCamera->GetMousePos());
            for (auto&& [flag, info] : m_meshes) {
                if (pMesh == info.pSelection.Get()) {
                    info.pVisual->OverrideUniform("color")
                        .SetData(SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f))
                        .SetShaderVarType(ShaderVarType::Vec4);

                    if (SR_UTILS_NS::Input::Instance().GetMouseDown(SR_UTILS_NS::MouseCode::MouseLeft)) {
                        m_activeOperation = flag;
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

        return Super::InitializeEntity();
    }

    void Gizmo::ProcessGizmo() {
        if (m_activeOperation == GizmoOperation::None) {
            m_lastMousePos = SR_MATH_NS::InfinityFV2;
            return;
        }

        auto&& mousePos = GetCamera()->GetMousePos();
        if (m_lastMousePos == SR_MATH_NS::InfinityFV2) {
            m_lastMousePos = mousePos;
            return;
        }

        if (m_activeOperation & GizmoOperation::TranslateZ) {
            const float_t cameraDistance = GetCamera()->GetPosition().Distance(GetTransform()->GetTranslation());

            auto&& lastPos = GetCamera()->ScreenToWorldPoint(m_lastMousePos, cameraDistance);
            auto&& currentPos = GetCamera()->ScreenToWorldPoint(GetCamera()->GetMousePos(), cameraDistance);

            const float_t distance = lastPos.Distance(currentPos);

            auto&& forwardMouse = (currentPos - lastPos).Normalize();
            auto&& forwardGizmo = (GetTransform()->GetQuaternion() * SR_UTILS_NS::Transform3D::FORWARD).Normalize();

            SR_UTILS_NS::DebugDraw::Instance().DrawLine(lastPos, currentPos, SR_MATH_NS::FColor(255, 0, 0, 255), 10.f);
            SR_UTILS_NS::DebugDraw::Instance().DrawLine(lastPos, lastPos + forwardGizmo, SR_MATH_NS::FColor(0, 255, 0, 255), 10.f);

            const float_t angle = forwardGizmo.AngleCoefficient(forwardMouse);

            GetTransform()->Translate(0, 0, angle * distance);

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