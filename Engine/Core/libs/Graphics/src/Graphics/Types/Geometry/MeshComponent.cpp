//
// Created by Monika on 19.09.2022.
//

#include <Graphics/Types/Geometry/MeshComponent.h>
#include <Graphics/Utils/MeshUtils.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform2D.h>

namespace SR_GTYPES_NS {
    MeshComponent::MeshComponent(MeshType type)
        : IndexedMesh(type)
        , SR_GTYPES_NS::IRenderComponent()
    {
        m_entityMessages.AddCustomProperty<SR_UTILS_NS::LabelProperty>("MeshInv")
            .SetLabel("Invalid mesh!")
            .SetColor(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f))
            .SetActiveCondition([this] { return !IsCalculatable(); })
            .SetDontSave();

        m_entityMessages.AddCustomProperty<SR_UTILS_NS::LabelProperty>("MeshNotCalc")
            .SetLabel("Mesh isn't calculated!")
            .SetColor(SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f))
            .SetActiveCondition([this] { return !IsCalculated(); })
            .SetDontSave();

        m_entityMessages.AddCustomProperty<SR_UTILS_NS::LabelProperty>("MeshNotReg")
            .SetLabel("Mesh isn't registered!")
            .SetColor(SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f))
            .SetActiveCondition([this] { return !IsGraphicsResourceRegistered(); })
            .SetDontSave();
    }

    void MeshComponent::OnLoaded() {
        Component::OnLoaded();
    }

    void MeshComponent::OnAttached() {
        GetRenderScene().Do([this](SR_GRAPH_NS::RenderScene* ptr) {
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

    bool MeshComponent::InitializeEntity() noexcept {
        m_properties.AddEnumProperty("Mesh type", &m_meshType).SetReadOnly();

        auto&& materialContainer = m_properties.AddContainer("Material");

        materialContainer.AddCustomProperty<SR_UTILS_NS::PathProperty>("Path")
            .AddFileFilter("Material", "mat")
            .SetGetter([this]()-> SR_UTILS_NS::Path {
                return m_material ? m_material->GetResourcePath() : SR_UTILS_NS::Path();
            })
            .SetSetter([this](const SR_UTILS_NS::Path& path) {
                SetMaterial(path);
            });

        materialContainer.AddCustomProperty<SR_UTILS_NS::ExternalProperty>("Material")
            .SetPropertyGetter([this]() -> SR_UTILS_NS::Property* { return m_material ? &m_material->GetProperties() : nullptr; })
            .SetActiveCondition([this]() -> bool { return m_material; })
            .SetReadOnly()
            .SetDontSave();

        //m_customMaterialProperties = &materialContainer.AddArray<MaterialProperty>("Custom properties");

        return Entity::InitializeEntity();
    }

    void MeshComponent::OnBeforeLayerChanged() {
        Component::OnBeforeLayerChanged();
    }

    void MeshComponent::OnLayerChanged() {
        Component::OnLayerChanged();
    }

    bool MeshComponent::HasSortingPriority() const {
        if (!m_gameObject) {
            return false;
        }

        return m_gameObject->GetTransform()->GetMeasurement() == SR_UTILS_NS::Measurement::Space2D;
    }

    SR_UTILS_NS::StringAtom MeshComponent::GetMeshLayer() const {
        if (!m_gameObject) {
            return SR_UTILS_NS::StringAtom();
        }

        return m_gameObject->GetLayer();
    }
}