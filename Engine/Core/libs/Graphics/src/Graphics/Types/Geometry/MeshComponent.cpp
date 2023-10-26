//
// Created by Monika on 19.09.2022.
//

#include <Graphics/Types/Geometry/MeshComponent.h>
#include <Graphics/Utils/MeshUtils.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform2D.h>

namespace SR_GTYPES_NS {
    SR_HTYPES_NS::Marshal::Ptr MeshComponent::Save(SR_UTILS_NS::SavableSaveData data) const {
        auto&& pMarshal = Component::Save(data);

        pMarshal->Write(static_cast<int32_t>(GetMeshType()));

        return pMarshal;
    }

    void MeshComponent::OnLoaded() {
        Component::OnLoaded();
    }

    void MeshComponent::OnAttached() {
        GetRenderScene().Do([this](SR_GRAPH_NS::RenderScene *ptr) {
            ptr->Register(this);
        });

        Component::OnAttached();
    }

    void MeshComponent::OnDestroy() {
        RenderScene::Ptr renderScene = TryGetRenderScene();

        Component::OnDestroy();

        /// если ресурс уничтожится сразу, то обрабатывать это нужно в контексте SharedPtr
        if (!IsGraphicsResourceRegistered()) {
            GetThis().DynamicCast<MeshComponent>().AutoFree([](auto&& pData) {
                pData->MarkMeshDestroyed();
            });
        }
        else {
            MarkMeshDestroyed();
        }

        if (renderScene) {
            renderScene->SetDirty();
        }
    }

    bool MeshComponent::ExecuteInEditMode() const {
        return true;
    }

    SR_MATH_NS::FVector3 MeshComponent::GetBarycenter() const {
        return m_barycenter;
    }

    void MeshComponent::OnMatrixDirty() {
        if (auto&& pTransform = GetTransform()) {
            m_modelMatrix = pTransform->GetMatrix();
            m_translation = pTransform->GetTranslation();
        }
        else {
            m_modelMatrix = SR_MATH_NS::Matrix4x4::Identity();
            m_translation = SR_MATH_NS::FVector3::Zero();
        }

        Component::OnMatrixDirty();
    }

    SR_UTILS_NS::Component* MeshComponent::CopyComponent() const {
        auto&& pMesh = SR_GRAPH_NS::CreateMeshByType(GetMeshType());
        if (!pMesh) {
            return nullptr;
        }

        if (auto&& pMeshComponent = dynamic_cast<MeshComponent*>(pMesh)) {
            pMeshComponent->SetMaterial(GetMaterial());
            return pMeshComponent;
        }

        SRHalt("Mesh is not a component! Memory leak...");

        return nullptr;
    }

    void MeshComponent::FreeMesh() {
        AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    int64_t MeshComponent::GetSortingPriority() const {
        if (!m_gameObject) {
            return -1;
        }

        if (auto&& pTransform = dynamic_cast<SR_UTILS_NS::Transform2D*>(m_gameObject->GetTransform())) {
            return pTransform->GetPriority();
        }

        return -1;
    }
}