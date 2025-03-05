//
// Created by Monika on 03.02.2025.
//

#ifndef SR_ENGINE_GUI_POINTER_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_POINTER_PROPERTY_DRAWER_H

#include <Core/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class PointerPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

        virtual void OnObjectReplaced(SRClass* pOld, SRClass* pNew) { }

    private:
        SR_UTILS_NS::StringAtom m_lastTypeName;
        std::string m_default;
        std::string m_searchBuffer;
        bool m_comboOpened = false;
        bool m_isOpened = false;
        ObjectPropertyDrawer::Ptr m_objectDrawer;
        std::vector<std::string> m_typeNames;

    };
}

#endif //SR_ENGINE_GUI_POINTER_PROPERTY_DRAWER_H

