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
        SR_UTILS_NS::Reflection::TypeInfo* DrawTypeInfo(uint32_t& index, const SR_UTILS_NS::Reflection::TypeInfo& typeInfo, const PropertyDrawerContext& context);

    private:
        SR_UTILS_NS::String m_default;
        SR_UTILS_NS::String m_searchBuffer;
        bool m_isOpened = false;
        bool m_openedByDefault = false;
        SR_UTILS_NS::SRHashType m_lastTypeInfoHash = 0;
        SR_HTYPES_NS::SharedPtr<PropertyDrawerBase> m_drawer;

        SR_UTILS_NS::Vector<SR_HTYPES_NS::SharedPtr<EnumPropertyDrawer>> m_enumDrawers;
        SR_UTILS_NS::Vector<bool> m_comboTypeOpenedStack;
        SR_UTILS_NS::Vector<bool> m_comboSizeOpenedStack;

        SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> m_typeNames;
        SR_UTILS_NS::Vector<uint8_t> m_detailedSizes;
        SR_UTILS_NS::Vector<SR_UTILS_NS::String> m_detailedSizesStr;

    };
}

#endif //SR_ENGINE_GUI_VALUE_PROPERTY_DRAWER_H

