//
// Created by Monika on 01.08.2022.
//

#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/ComponentManager.h>

#include <Graphics/UI/Canvas.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderScene.h>

namespace SR_GRAPH_NS::UI {
    SR_REGISTER_COMPONENT(Canvas);

    Canvas::Canvas()
        : Super()
    { }

    void Canvas::OnAttached() {
        m_renderScene = GetScene()->Do<RenderScenePtr>([](SR_WORLD_NS::Scene* pScene) {
            return pScene->GetDataStorage().GetValue<RenderScenePtr>();
        }, RenderScenePtr());

        m_context = m_renderScene->GetContext();

        Super::OnAttached();
    }

    SR_UTILS_NS::Component* Canvas::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* pDataStorage) {
        return new Canvas();
    }

    void Canvas::OnDestroy() {
        Super::OnDestroy();

        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void Canvas::Update(float_t dt) {
        if (m_renderScene.RecursiveLockIfValid()) {
            SR_MATH_NS::UVector2 windowSize;

            if (auto&& pCamera = m_renderScene->GetMainCamera()) {
                windowSize = pCamera->GetSize();
            }
            else {
                windowSize = m_renderScene->GetSurfaceSize();
            }

            auto&& pTransform = dynamic_cast<SR_UTILS_NS::Transform2D *>(GetTransform());

            if (windowSize != m_size && pTransform) {
                m_size = windowSize;

                auto&& aspect = m_size.Aspect();

                pTransform->SetTranslation(SR_MATH_NS::FVector3(0.f));
                pTransform->SetScale(SR_MATH_NS::FVector3(aspect, 1.f, 1.f));

                /// if (aspect > 1.f) {
                ///     pTransform->SetScale(SR_MATH_NS::FVector3(1.f, 1.f, 1.f));
                /// }
                /// else {
                ///     pTransform->SetScale(SR_MATH_NS::FVector3(aspect, aspect, 1.f));
                /// }
            }

            m_renderScene.Unlock();
        }

        Super::Update(dt);
    }

    bool Canvas::ExecuteInEditMode() const {
        return true;
    }
}