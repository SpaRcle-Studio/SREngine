//
// Created by Monika on 15.04.2023.
//

#ifndef SR_ENGINE_DRAGNDROPHELPER_H
#define SR_ENGINE_DRAGNDROPHELPER_H

#include <Utils/ECS/EntityRefOld.h>

namespace SR_CORE_GUI_NS {
    class EditorGUI;
    SR_MAYBE_UNUSED bool DragDropTargetEntityRef(EditorGUI* pContext, SR_UTILS_NS::EntityRefOld& entityRef, const char* id, float_t width = 300.f);
}

#endif //SR_ENGINE_DRAGNDROPHELPER_H
