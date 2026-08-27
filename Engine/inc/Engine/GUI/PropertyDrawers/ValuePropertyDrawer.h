//
// Created by Monika on 03.02.2025.
//

#ifndef SR_ENGINE_GUI_VALUE_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_VALUE_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

#include <Utils/Reflection/ReflectedType.h>

namespace SR_CORE_GUI_NS {
    class ObjectPropertyDrawer;
    class EnumPropertyDrawer;

    class ValuePropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ValuePropertyDrawer>;

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

        virtual void OnObjectReplaced(SRClass* pOld, SRClass* pNew) { }
        virtual void CustomContextMenu(const PropertyDrawerContext& context, SRClass* pClass) { }

    private:
        SR_UTILS_NS::String m_default;
        std::string m_searchBuffer;
        bool m_comboTypeOpened = false;
        bool m_comboSizeOpened = false;
        bool m_isOpened = false;
        bool m_openedByDefault = false;
        SR_HTYPES_NS::SharedPtr<EnumPropertyDrawer> m_enumDrawer;
        SR_HTYPES_NS::SharedPtr<PropertyDrawerBase> m_drawer;
        SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> m_typeNames;
        SR_UTILS_NS::Vector<uint8_t> m_detailedSizes;
        SR_UTILS_NS::Vector<SR_UTILS_NS::String> m_detailedSizesStr;
        SR_UTILS_NS::Reflection::ReflectedCategoryType m_lastCategoryType = SR_UTILS_NS::Reflection::ReflectedCategoryType::Unknown;
        SR_UTILS_NS::StringAtom m_lastDetailedType;

    };
}

#endif //SR_ENGINE_GUI_VALUE_PROPERTY_DRAWER_H

