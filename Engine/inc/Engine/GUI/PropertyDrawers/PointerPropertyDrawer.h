//
// Created by Monika on 03.02.2025.
//

#ifndef SR_ENGINE_GUI_POINTER_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_POINTER_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

/**
 * Render and manage the editor UI for a pointer property in the property inspector.
 *
 * @param context Context information and state used to draw the property UI.
 * @returns `PropertyDrawerFeedback` value describing the outcome of the draw operation (for example whether the property value changed or other follow-up is required).
 */
/**
 * Handle a replacement of the referenced object's class.
 *
 * @param pOld Pointer to the previous class of the referenced object (may be nullptr).
 * @param pNew Pointer to the new class of the referenced object (may be nullptr).
 */
namespace SR_CORE_GUI_NS {
    class ObjectPropertyDrawer;

    class PointerPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<PointerPropertyDrawer>;

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

        virtual void OnObjectReplaced(SRClass* pOld, SRClass* pNew) { }

    private:
        SR_UTILS_NS::StringAtom m_lastTypeName;
        std::string m_default;
        std::string m_searchBuffer;
        bool m_comboOpened = false;
        bool m_isOpened = false;
        bool m_openedByDefault = false;
        SR_HTYPES_NS::SharedPtr<ObjectPropertyDrawer> m_objectDrawer;
        std::vector<SR_UTILS_NS::StringAtom> m_typeNames;

    };
}

#endif //SR_ENGINE_GUI_POINTER_PROPERTY_DRAWER_H
