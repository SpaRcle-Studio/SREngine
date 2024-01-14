//
// Created by innerviewer on 2024-01-12.
//

#include <Core/UI/IButton.h>


namespace SR_CORE_UI_NS {
    IButton::IButton()
        : Super()
    { }

    SR_GRAPH_NS::IColorBufferPass* IButton::GetIColorBufferPass() {
        if (!m_renderScene) {
            m_mesh = GetParent()->GetComponent<SR_GTYPES_NS::Mesh3D>();
            m_renderScene = m_mesh->GetRenderScene();
        }

        return m_renderScene->GetMainCamera()->GetRenderTechnique()->FindPass<SR_GRAPH_NS::IColorBufferPass>();
    }

    SR_NODISCARD bool IButton::IsHovered() {
        auto&& pIColorBufferPass = GetIColorBufferPass();

        //auto&& windowSize = m_renderScene->GetWindow()->GetSize();

        auto&& mousePosition = SR_PLATFORM_NS::GetMousePos();
        auto&& surfaceSize = m_renderScene->GetSurfaceSize();
        SR_MATH_NS::FVector2 positionRatio  = { mousePosition.x / surfaceSize.x, mousePosition.y / surfaceSize.y }; /* NOLINT */

        auto&& pHoveredMesh = pIColorBufferPass->GetMesh(positionRatio);

        return pHoveredMesh == m_mesh;
    }
}