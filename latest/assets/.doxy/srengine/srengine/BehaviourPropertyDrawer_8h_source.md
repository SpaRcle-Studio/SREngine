

# File BehaviourPropertyDrawer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**PropertyDrawers**](dir_4cfb8686e051f64f158d683134748f22.md) **>** [**BehaviourPropertyDrawer.h**](BehaviourPropertyDrawer_8h.md)

[Go to the documentation of this file](BehaviourPropertyDrawer_8h.md)


```C++
//
// Created by Monika on 04.05.2025.
//

#ifndef SR_ENGINE_GUI_BEHAVIOUR_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_BEHAVIOUR_PROPERTY_DRAWER_H

#include <Core/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class BehaviourPropertyDrawer : public ObjectPropertyDrawer {
        SR_CLASS()
    public:
        BehaviourPropertyDrawer();

    public:
        PropertyDrawerFeedback DrawCustomProperties(const PropertyDrawerContext& context) override;

    private:
        SR_UTILS_NS::Subscription m_moduleReloadSubscription;
        std::string m_searchBuffer;
        bool m_comboOpened = false;
        ObjectPropertyDrawer::Ptr m_pObjectPropertyDrawer;

    };
}

#endif //SR_ENGINE_GUI_BEHAVIOUR_PROPERTY_DRAWER_H
```


