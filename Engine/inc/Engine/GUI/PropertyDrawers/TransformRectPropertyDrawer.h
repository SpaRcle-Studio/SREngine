//
// Created by Monika on 18.12.2025.
//

#ifndef SR_ENGINE_GUI_TRANSFORM_RECT_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_TRANSFORM_RECT_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

#include <Utils/ECS/TransformRect.h>

namespace SR_CORE_GUI_NS {
    class TransformRectPropertyDrawer : public ObjectPropertyDrawer {
        SR_CLASS()
        using Super = ObjectPropertyDrawer;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TransformRectPropertyDrawer>;

    public:
        TransformRectPropertyDrawer();

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        SR_UTILS_NS::RectAnchors m_lastAnchors;
        ObjectPropertyDrawer::Ptr m_anchorsDrawer;

    };
}

#endif //SR_ENGINE_GUI_TRANSFORM_RECT_PROPERTY_DRAWER_H
