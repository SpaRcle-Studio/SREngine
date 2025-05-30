//
// Created by Monika on 17.02.2025.
//

#ifndef SR_ENGINE_GUI_MATERIAL_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_MATERIAL_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawers/PointerPropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class MaterialPropertyDrawer final : public PointerPropertyDrawer {
        using Super = PointerPropertyDrawer;
        SR_CLASS()
    public:
        void OnObjectReplaced(SRClass* pOld, SRClass* pNew) override;
    };
} // namespace SR_CORE_GUI_NS

#endif // SR_ENGINE_GUI_MATERIAL_PROPERTY_DRAWER_H
