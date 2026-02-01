//
// Created by Monika on 01.02.2026.
//

#include <Graphics/UI/Utils.h>

namespace SR_GRAPH_NS::UI {
    SR_MATH_NS::Ray ScreenPointToRay(SR_GTYPES_NS::Camera* pCamera, SR_MATH_NS::FVector2 screenPos) {
        if (pCamera) {
            return pCamera->GetScreenRay(screenPos, true);
        }

        SR_MATH_NS::FVector3 origin = SR_MATH_NS::FVector3(screenPos.x, screenPos.y, -100.f);
        return SR_MATH_NS::Ray(origin, SR_MATH_NS::FVector3::Forward());
    }

    bool ScreenPointToWorldPointInRectangle(SR_UTILS_NS::TransformRect& rect, SR_MATH_NS::FVector2 screenPoint, SR_GTYPES_NS::Camera* pCamera, SR_MATH_NS::FVector3& outWorldPoint) {
        outWorldPoint = SR_MATH_NS::FVector3();
        SR_MATH_NS::Ray ray = ScreenPointToRay(pCamera, screenPoint);
        float enter = 0.f;
        if (!SR_MATH_NS::Plane(rect.GetGlobalRotation() * SR_MATH_NS::FVector3::Back(), rect.GetTranslation()).Raycast(ray, enter)) {
            return false;
        }

        outWorldPoint = ray.GetPoint(enter);
        return true;
    }

    bool ScreenPointToLocalPointInRectangle(SR_UTILS_NS::TransformRect& rect, SR_MATH_NS::FVector2 screenPoint, SR_GTYPES_NS::Camera* pCamera, SR_MATH_NS::FVector2& outLocalPoint) {
        outLocalPoint = SR_MATH_NS::FVector2();
        SR_MATH_NS::FVector3 worldPoint;

        if (!ScreenPointToWorldPointInRectangle(rect, screenPoint, pCamera, worldPoint)) {
            return false;
        }

        outLocalPoint = rect.InverseTransformPoint(worldPoint).XY();
        return true;
    }

    bool RectangleContainsScreenPoint(SR_UTILS_NS::TransformRect& rect, SR_MATH_NS::FVector2 screenPoint, SR_GTYPES_NS::Camera* pCamera) {
        SR_MATH_NS::FVector2 localPoint;
        if (!ScreenPointToLocalPointInRectangle(rect, screenPoint, pCamera, localPoint)) {
            return false;
        }

        SR_MATH_NS::FRect layoutRect = rect.GetLayoutRect();
        return layoutRect.Contains(localPoint);
    }

    bool RectangleContainsScreenPoint(SR_UTILS_NS::TransformRect& rect, SR_MATH_NS::FVector2 screenPoint) {
        return RectangleContainsScreenPoint(rect, screenPoint, nullptr);
    }
}