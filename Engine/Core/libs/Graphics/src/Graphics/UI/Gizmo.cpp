//
// Created by Monika on 23.11.2023.
//

#include <Graphics/UI/Gizmo.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/ECS/GameObject.h>

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

    void Gizmo::Update(float_t dt) {
        SR_TRACY_ZONE;

        auto&& pRenderScene = TryGetRenderScene();
        if (!pRenderScene) {
            return;
        }

        auto&& pCamera = pRenderScene->GetMainCamera();
        if (!pCamera) {
            return;
        }

        auto&& pTechnique = pCamera->GetRenderTechnique();
        if (!pTechnique) {
            return;
        }

        const float_t distance = GetTransform()->GetTranslation().Distance(pCamera->GetPosition());

        GetTransform()->SetScale(distance / 10.f);

        if (auto&& pMesh = pTechnique->PickMeshAt(pCamera->GetMousePos())) {
            for (auto&& [flag, info] : m_meshes) {
                if (pMesh == info.pSelection.Get()) {
                    info.pVisual->OverrideUniform("color")
                        .SetData(SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f))
                        .SetShaderVarType(ShaderVarType::Vec4);
                }
                else {
                    info.pVisual->RemoveUniformOverride("color");
                }
            }
        }

        Super::Update(dt);
    }
}