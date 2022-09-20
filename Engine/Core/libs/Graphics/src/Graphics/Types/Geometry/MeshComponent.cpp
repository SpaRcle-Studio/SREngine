//
// Created by Monika on 19.09.2022.
//

#include <Graphics/Types/Geometry/MeshComponent.h>

namespace SR_GTYPES_NS {
    void MeshComponent::OnAttached() {
        AddUsePoint();

        GetRenderScene().Do([this](SR_GRAPH_NS::RenderScene *ptr) {
            ptr->Register(this);
        });

        Component::OnAttached();
    }

    void MeshComponent::OnDestroy() {
        Component::OnDestroy();

        auto&& renderScene = GetRenderScene();

        /// после вызова данная сущность может быть уничтожена
        RemoveUsePoint();

        renderScene->SetDirty();
    }

    void MeshComponent::OnEnable() {
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
        Component::OnEnable();
    }

    void MeshComponent::OnDisable() {
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
        Component::OnDisable();
    }

    bool MeshComponent::ExecuteInEditMode() const {
        return true;
    }

    Mesh::RenderScenePtr MeshComponent::GetRenderScene() {
        if (!m_renderScene.Valid()) {
            m_renderScene = TryGetScene().Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) {
                return ptr->GetDataStorage().GetValue<RenderScenePtr>();
            }, RenderScenePtr());
        }

        return m_renderScene;
    }

    SR_MATH_NS::FVector3 MeshComponent::GetBarycenter() const {
        return Component::GetBarycenter();
    }

    void MeshComponent::OnMatrixDirty() {
        if (auto&& pTransform = GetTransform()) {
            m_modelMatrix = pTransform->GetMatrix();
            m_translation = pTransform->GetTranslation();
        }
        else {
            SRHalt("Component have not transform, but OnMatrixDirty was called!");
        }

        Component::OnMatrixDirty();
    }
}