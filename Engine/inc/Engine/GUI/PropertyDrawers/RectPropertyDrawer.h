//
// Created by Monika on 18.05.2025.
//

#ifndef SR_ENGINE_GUI_RECT_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_RECT_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class RectPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<RectPropertyDrawer>;

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        uint64_t m_numberTempData = 0;

    };
}

#endif //SR_ENGINE_GUI_RECT_PROPERTY_DRAWER_H
