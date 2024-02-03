//
// Created by Monika on 23.11.2023.
//

#include <Graphics/UI/Gizmo.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Render/RenderTechnique.h>

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

        if (operation & GizmoOperation::Center) {
            pMeshComponent->SetMaterial("Engine/Materials/Colors/gizmo-center.mat");
        }
        else if ((operation & GizmoOperation::X && !(operation & GizmoOperation::Alternative)) || (operation == GizmoOperation::TranslateAltX)) {
            pMeshComponent->SetMaterial("Engine/Materials/Colors/gizmo-x.mat");
        }
        else if ((operation & GizmoOperation::Y && !(operation & GizmoOperation::Alternative)) || (operation == GizmoOperation::TranslateAltY)) {
            pMeshComponent->SetMaterial("Engine/Materials/Colors/gizmo-y.mat");
        }
        else if ((operation & GizmoOperation::Z && !(operation & GizmoOperation::Alternative)) || (operation == GizmoOperation::TranslateAltZ)) {
            pMeshComponent->SetMaterial("Engine/Materials/Colors/gizmo-z.mat");
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

        LoadMesh(GizmoOperation::TranslateCenter, gizmoFile, "Center", GizmoMeshLoadMode::Visual);
        LoadMesh(GizmoOperation::TranslateCenter, gizmoFile, "CenterSelection", GizmoMeshLoadMode::Selection);

        LoadMesh(GizmoOperation::TranslateAltX, gizmoFile, "PlaneX", GizmoMeshLoadMode::All);
        LoadMesh(GizmoOperation::TranslateAltY, gizmoFile, "PlaneY", GizmoMeshLoadMode::All);
        LoadMesh(GizmoOperation::TranslateAltZ, gizmoFile, "PlaneZ", GizmoMeshLoadMode::All);

        LoadMesh(GizmoOperation::TranslateX, gizmoFile, "ArrowX", GizmoMeshLoadMode::Visual);
        LoadMesh(GizmoOperation::TranslateY, gizmoFile, "ArrowY", GizmoMeshLoadMode::Visual);
        LoadMesh(GizmoOperation::TranslateZ, gizmoFile, "ArrowZ", GizmoMeshLoadMode::Visual);

        LoadMesh(GizmoOperation::TranslateX, gizmoFile, "ArrowXSelection", GizmoMeshLoadMode::Selection);
        LoadMesh(GizmoOperation::TranslateY, gizmoFile, "ArrowYSelection", GizmoMeshLoadMode::Selection);
        LoadMesh(GizmoOperation::TranslateZ, gizmoFile, "ArrowZSelection", GizmoMeshLoadMode::Selection);
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

        auto&& mousePos = GetCamera()->GetMousePos();

        m_modelMatrix = SR_MATH_NS::Matrix4x4(
            GetTransform()->GetTranslation(),
            GetTransform()->GetQuaternion()
        );

        /// normalized for local scape
        m_modelMatrix = m_modelMatrix.OrthogonalNormalize();

        if (m_activeOperation == GizmoOperation::None) {
            auto&& pMesh = pTechnique->PickMeshAt(pCamera->GetMousePos());
            for (auto&& [flag, info] : m_meshes) {
                if (pMesh == info.pSelection.Get()) {
                    info.pVisual->OverrideUniform("color")
                        .SetData(SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f))
                        .SetShaderVarType(ShaderVarType::Vec4);

                    if (SR_UTILS_NS::Input::Instance().GetMouseDown(SR_UTILS_NS::MouseCode::MouseLeft)) {
                        m_activeOperation = flag;

                        auto&& normal = SR_MATH_NS::CalcPlanNormal(
                            m_modelMatrix,
                            GetCamera()->GetCameraEye(),
                            GetCamera()->GetCameraDir(),
                            GetAxis()
                        );

                        auto&& screenRay = GetCamera()->GetScreenRay(mousePos);
                        const float_t screenFactor = GetCamera()->CalculateScreenFactor(m_modelMatrix, m_moveFactor);

                        m_translationPlan = SR_MATH_NS::BuildPlan(m_modelMatrix.v.position, normal);
                        m_translationPlanOrigin = screenRay.IntersectPlane(m_translationPlan);
                        m_relativeOrigin = (m_translationPlanOrigin - m_modelMatrix.v.position.XYZ()) * (1.f / screenFactor);
                    }
                }
                else {
                    info.pVisual->RemoveUniformOverride("color");
                }
            }
        }

        ProcessGizmo(mousePos);

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

    void Gizmo::ProcessGizmo(const SR_MATH_NS::FPoint& mousePos) {
        if (m_activeOperation == GizmoOperation::None) {
            return;
        }

        auto&& screenRay = GetCamera()->GetScreenRay(mousePos);
        const float_t screenFactor = GetCamera()->CalculateScreenFactor(m_modelMatrix, m_moveFactor);

        if (m_activeOperation & GizmoOperation::Translate) {
            auto&& newPos = screenRay.IntersectPlane(m_translationPlan);
            auto&& newOrigin = newPos - m_relativeOrigin * screenFactor;
            auto&& delta = newOrigin - m_modelMatrix.v.position.XYZ();

            if (!(m_activeOperation & GizmoOperation::Alternative) && !(m_activeOperation & GizmoOperation::Center)) {
                auto&& axisValue = m_modelMatrix.GetAxis(GetAxis()).XYZ();
                const float lengthOnAxis = axisValue.Dot(delta);
                delta = axisValue * lengthOnAxis;
            }

            SR_UTILS_NS::DebugDraw::Instance().DrawLine(GetCamera()->GetPosition(), newPos, SR_MATH_NS::FColor(255, 0, 255, 255), 10.f);
            SR_UTILS_NS::DebugDraw::Instance().DrawLine(GetCamera()->GetPosition(), newOrigin, SR_MATH_NS::FColor(255, 0, 0, 255), 10.f);
            SR_UTILS_NS::DebugDraw::Instance().DrawLine(GetTransform()->GetTranslation(), GetTransform()->GetTranslation() + delta, SR_MATH_NS::FColor(255, 255, 0, 255), 10.f);

            GetTransform()->Translate(m_modelMatrix.GetQuat().Inverse() * delta);
        }
    }

    SR_MATH_NS::AxisFlag Gizmo::GetAxis() const {
        SR_MATH_NS::AxisFlag axis = SR_MATH_NS::Axis::None;
        axis |= (m_activeOperation & GizmoOperation::X) ? SR_MATH_NS::Axis::X : SR_MATH_NS::Axis::None;
        axis |= (m_activeOperation & GizmoOperation::Y) ? SR_MATH_NS::Axis::Y : SR_MATH_NS::Axis::None;
        axis |= (m_activeOperation & GizmoOperation::Z) ? SR_MATH_NS::Axis::Z : SR_MATH_NS::Axis::None;
        axis |= (m_activeOperation & GizmoOperation::Center) ? SR_MATH_NS::Axis::XYZ : SR_MATH_NS::Axis::None;
        return axis;
    }
}