

# File PointerPropertyDrawer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**PropertyDrawers**](dir_30dc1e095f689d337a3714af764d731f.md) **>** [**PointerPropertyDrawer.h**](PointerPropertyDrawer_8h.md)

[Go to the documentation of this file](PointerPropertyDrawer_8h.md)


```C++
//
// Created by Monika on 03.02.2025.
//

#ifndef SR_ENGINE_GUI_POINTER_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_POINTER_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

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


