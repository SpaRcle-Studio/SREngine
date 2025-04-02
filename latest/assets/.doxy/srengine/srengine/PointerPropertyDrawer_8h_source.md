

# File PointerPropertyDrawer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**PropertyDrawers**](dir_4cfb8686e051f64f158d683134748f22.md) **>** [**PointerPropertyDrawer.h**](PointerPropertyDrawer_8h.md)

[Go to the documentation of this file](PointerPropertyDrawer_8h.md)


```C++
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
        ObjectPropertyDrawer::Ptr m_objectDrawer;
        std::vector<std::string> m_typeNames;

    };
}

#endif //SR_ENGINE_GUI_POINTER_PROPERTY_DRAWER_H

```


