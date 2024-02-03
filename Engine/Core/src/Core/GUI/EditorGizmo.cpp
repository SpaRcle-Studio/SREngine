//
// Created by Monika on 03.02.2024.
//

#include <Core/GUI/EditorGizmo.h>

namespace SR_CORE_GUI_NS {
    EditorGizmo::EditorGizmo(Hierarchy* pHierarchy)
        : Super()
        , m_hierarchy(pHierarchy)
    {
        SetDontSave(true);
    }
}