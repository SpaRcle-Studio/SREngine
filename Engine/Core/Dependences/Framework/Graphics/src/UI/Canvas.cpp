//
// Created by Monika on 01.08.2022.
//

#include <UI/Canvas.h>
#include <Utils/ECS/Transform3D.h>
#include <Render/RenderContext.h>
#include <Render/RenderScene.h>

namespace SR_GRAPH_NS::UI {
    Canvas::Canvas()
        : SR_UTILS_NS::Component()
    {
        Component::InitComponent<Canvas>();
    }

    SR_MATH_NS::IVector2 Canvas::GetWindowSize() const {
        return m_context->GetWindowSize();
    }

    void Canvas::TransformUI() {
        auto&& size = GetWindowSize();

        if (size.HasZero()) {
            return;
        }

        if (auto&& pTransform = GetTransform()) {
            pTransform->SetTranslation(0, 0, 0);
            pTransform->SetScale(size.Aspect(), 1.f, 1.f);
        }
    }

    void Canvas::OnAttached() {
        m_renderScene = GetScene().Do<RenderScenePtr>([](SR_WORLD_NS::Scene* pScene) {
            return pScene->GetDataStorage().GetValue<RenderScenePtr>();
        }, RenderScenePtr());

        m_context = m_renderScene->GetContext();

        TransformUI();
        Component::OnAttached();
    }

    void Canvas::OnWindowResized(const SR_MATH_NS::IVector2 &size) {
        TransformUI();
        Component::OnWindowResized(size);
    }

    SR_UTILS_NS::Component* Canvas::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        return new Canvas();
    }

    void Canvas::OnDestroy() {
        Component::OnDestroy();
        delete this;
    }
}