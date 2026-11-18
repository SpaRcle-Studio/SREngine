//
// Created by Codex on 15.11.2026.
//

#include <Engine/UI/UIControl.h>
#include <Engine/UI/UIButton.h>
#include <Engine/UI/UIScrollBar.h>
#include <Engine/UI/UIScrollRect.h>
#include <Engine/UI/UISlider.h>
#include <Engine/UI/UIToggle.h>
#include <Utils/ECS/TransformRect.h>
#include <Utils/Reflection/Method.h>
#include <Scripting/Base/Behaviour.h>
#include <Utils/World/Scene.h>
#include <Utils/World/SceneUpdater.h>
#include <Codegen/UIControl.generated.hpp>

namespace SR_CORE_UI_NS {
    void UIControl::OnMatrixDirty() {
        m_hitMatrixDirty = true;
        SR_UTILS_NS::UIComponent::OnMatrixDirty();
    }

    void UIControl::OnPostLoad() {
        m_hitMatrixDirty = true;
        SR_UTILS_NS::UIComponent::OnPostLoad();
    }

    bool UIControl::RequiresInputPolling() const {
        // Opt in only audited implementations; an unknown subclass may have time-dependent input.
        auto&& pMeta = GetMeta();
        return pMeta != UIControl::GetMetaStatic() && pMeta != UIButton::GetMetaStatic()
            && pMeta != UIScrollBar::GetMetaStatic() && pMeta != UIScrollRect::GetMetaStatic()
            && pMeta != UISlider::GetMetaStatic() && pMeta != UIToggle::GetMetaStatic();
    }

    void UIControl::Focus() {
        if (auto&& pScene = TryGetScene()) {
            if (auto&& pUpdater = pScene->GetSceneUpdater()) {
                pUpdater->RequestUIFocus(*this);
            }
        }
    }

    bool UIButtonEvent::Invoke() const {
        auto pObject = object.Get();
        if (!pObject || !pObject->IsComponentValid()) {
            SR_ERROR("UIButtonEvent::Invoke() : unavailable target {} for {}", object.GetEntityId(), method);
            return false;
        }
        if (pObject->GetMeta()->IsSameOrInherited(SR_SCRIPTING_NS::Behaviour::GetClassStaticName())) {
            return static_cast<SR_SCRIPTING_NS::Behaviour*>(pObject.Get())->InvokeEvent(method);
        }

        auto&& pMethod = pObject->GetMeta()->FindMethod(method);
        if (!pMethod || pMethod->HasReturn() || pMethod->GetParamsCount() != 0 || !pMethod->IsActive(*pObject)) {
            SR_ERROR("UIButtonEvent::Invoke() : expected active void {}() on {}", method, pObject->GetMeta()->GetFactoryName());
            return false;
        }
        pMethod->InvokeVoid(*pObject);
        return true;
    }

    void UIControl::InvokeEvents(const SR_UTILS_NS::Vector<UIButtonEvent>& events) {
        SR_TRACY_ZONE;
        const auto snapshot = events;
        for (auto&& event : snapshot) {
            event.Invoke();
        }
    }

    bool UIControl::HitTest(const SR_UTILS_NS::PointerEvent& event) {
        if (!m_raycastTarget) {
            return false;
        }
        auto&& pRect = GetTransformAs<SR_UTILS_NS::TransformRect>();
        auto&& pCanvas = FindCanvas(GetSceneObject().Get());
        if (!pRect || !pCanvas || !pCanvas->IsActive() || !pCanvas->ContainsPointerViewport(event) || pRect->GetGlobalScale().HasZero()) {
            return false;
        }
        if (m_hitMatrixDirty || m_pHitRect != pRect || RequiresInputPolling()) {
            m_hitInverse = pRect->GetMatrix().Inverse();
            m_pHitRect = pRect;
            m_hitMatrixDirty = false;
        }
        const auto canvasPoint = pCanvas->PointerToCanvasSpace(event);
        const auto layoutPoint = canvasPoint * pCanvas->GetScaleFactor() + pCanvas->GetSize().CastToFloat() / 2.f;
        const auto localPoint = m_hitInverse.TransformPoint({ layoutPoint.x, layoutPoint.y, 0.f });
        if (!pRect->GetLayoutRect().Contains(SR_MATH_NS::FVector2(localPoint.x, localPoint.y))) {
            return false;
        }
        const auto mask = pRect->GetMaskInfo();
        if (mask.hasMask && mask.scissor) {
            auto point = layoutPoint;
            point.y = static_cast<float_t>(mask.referenceSize.y) - point.y;
            if (!mask.rect.Contains(point.CastToInt())) {
                return false;
            }
        }
        return true;
    }

    int32_t UIControl::GetInputPriority() const {
        auto&& pRect = GetTransformAs<SR_UTILS_NS::TransformRect>();
        return pRect ? pRect->GetPriority() : 0;
    }

    void UIControl::SetInteractable(bool value) {
        m_interactable = value;
        InvalidateUIInput();
        SetInputState(false, false, false);
    }

    void UIControl::SetInputState(bool hovered, bool pressed, bool focused) {
        m_state = !m_interactable ? UIControlState::Disabled : pressed ? UIControlState::Pressed : hovered ? UIControlState::Hovered : focused ? UIControlState::Selected : UIControlState::Idle;
        if (auto pObject = m_idle.Get()) {
            pObject->SetEnabled(m_state == UIControlState::Idle);
        }
        if (auto pObject = m_hovered.Get()) {
            pObject->SetEnabled(m_state == UIControlState::Hovered);
        }
        if (auto pObject = m_pressed.Get()) {
            pObject->SetEnabled(m_state == UIControlState::Pressed);
        }
        if (auto pObject = m_selected.Get()) {
            pObject->SetEnabled(m_state == UIControlState::Selected);
        }
        if (auto pObject = m_disabled.Get()) {
            pObject->SetEnabled(m_state == UIControlState::Disabled);
        }
    }

    void UIControl::Cancel() {
        InvokeEvents(m_onCancelEvents);
    }
}
