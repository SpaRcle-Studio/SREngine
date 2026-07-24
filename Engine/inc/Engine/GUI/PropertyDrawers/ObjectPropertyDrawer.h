//
// Created by Monika on 03.02.2025.
//

#ifndef SR_ENGINE_GUI_OBJECT_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_OBJECT_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class ObjectPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ObjectPropertyDrawer>;

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

        virtual PropertyDrawerFeedback DrawCustomProperties(const PropertyDrawerContext& context) { return PropertyDrawerFeedback(); }

    private:
        void DrawPropertyGroup(
            SR_UTILS_NS::StringAtom group,
            SR_UTILS_NS::SRClass* pClassValue,
            uint64_t index,
            const SR_UTILS_NS::Reflection::Property& property,
            const PropertyDrawerContext& context,
            PropertyDrawerContext& propertyContext,
            PropertyDrawerFeedback& feedback
        );

        void DrawMethod(
            SR_UTILS_NS::SRClass* pClassValue,
            uint64_t index,
            const SR_UTILS_NS::Reflection::Method& method,
            const PropertyDrawerContext& context,
            PropertyDrawerContext& propertyContext,
            PropertyDrawerFeedback& feedback
        );

    private:
        bool m_openedByDefault = false;
        bool m_isOpened = false;
        SR_UTILS_NS::Set<SR_UTILS_NS::StringAtom> m_openedGroups;
        SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> m_groups;
        SR_UTILS_NS::Vector<PropertyDrawerBase::Ptr> m_drawers;

    };
}

#endif //SR_ENGINE_GUI_OBJECT_PROPERTY_DRAWER_H

