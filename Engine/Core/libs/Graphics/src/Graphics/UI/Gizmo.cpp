//
// Created by Monika on 23.11.2023.
//

#include <Graphics/UI/Gizmo.h>
#include <Utils/ECS/ComponentManager.h>

namespace SR_GRAPH_UI_NS {
    SR_REGISTER_COMPONENT(Gizmo);

    SR_UTILS_NS::Component* Gizmo::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        return SR_UTILS_NS::ComponentManager::Instance().CreateComponent<Gizmo>();
    }

    void Gizmo::OnAttached() {
        Super::OnAttached();
    }

    void Gizmo::OnDestroy() {
        ReleaseGizmo();

        Super::OnDestroy();

        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void Gizmo::LoadMesh(GizmoOperationFlag operation, SR_UTILS_NS::StringAtom path, SR_UTILS_NS::StringAtom name) {
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

        //MaterialProperty& materialProperty = pMeshComponent->GetOverrideUniforms().emplace_back();
        //materialProperty.SetData(SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f));
        //materialProperty.SetName("color");
        //materialProperty.SetShaderVarType(ShaderVarType::Vec4);

        GetParent()->AddComponent(pMeshComponent);

        m_meshes[operation] = pMeshComponent;
    }

    void Gizmo::OnEnable() {
        LoadGizmo();
        Super::OnEnable();
    }

    void Gizmo::LoadGizmo() {
        SRAssert(m_meshes.empty());

        LoadMesh(GizmoOperation::Center, "Engine/Models/gizmo-translation.fbx", "Center");
        LoadMesh(GizmoOperation::TranslateX, "Engine/Models/gizmo-translation.fbx", "ArrowX");
        LoadMesh(GizmoOperation::TranslateY, "Engine/Models/gizmo-translation.fbx", "ArrowY");
        LoadMesh(GizmoOperation::TranslateZ, "Engine/Models/gizmo-translation.fbx", "ArrowZ");
        LoadMesh(GizmoOperation::TranslateAltX, "Engine/Models/gizmo-translation.fbx", "PlaneX");
        LoadMesh(GizmoOperation::TranslateAltY, "Engine/Models/gizmo-translation.fbx", "PlaneY");
        LoadMesh(GizmoOperation::TranslateAltZ, "Engine/Models/gizmo-translation.fbx", "PlaneZ");
    }

    void Gizmo::ReleaseGizmo() {
        for (auto&& [operation, pMesh] : m_meshes) {
            if (pMesh) {
                pMesh->Detach();
            }
        }
        m_meshes.clear();
    }

    void Gizmo::OnDisable() {
        ReleaseGizmo();
        Super::OnDisable();
    }
}