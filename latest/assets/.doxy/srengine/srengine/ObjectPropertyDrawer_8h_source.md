

# File ObjectPropertyDrawer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**PropertyDrawers**](dir_4cfb8686e051f64f158d683134748f22.md) **>** [**ObjectPropertyDrawer.h**](ObjectPropertyDrawer_8h.md)

[Go to the documentation of this file](ObjectPropertyDrawer_8h.md)


```C++
//
// Created by Monika on 03.02.2025.
//

#ifndef SR_ENGINE_GUI_OBJECT_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_OBJECT_PROPERTY_DRAWER_H

#include <Core/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class ObjectPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ObjectPropertyDrawer>;

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

        virtual PropertyDrawerFeedback DrawCustomProperties(const PropertyDrawerContext& context) { return PropertyDrawerFeedback(); }

    private:
        bool m_isOpened = false;
        std::vector<PropertyDrawerBase::Ptr> m_drawers;

    };
}

#endif //SR_ENGINE_GUI_OBJECT_PROPERTY_DRAWER_H

```


