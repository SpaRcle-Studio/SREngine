//
// Created by Monika on 30.11.2022.
//

#ifndef SRENGINE_ENTITYREFUTILS_H
#define SRENGINE_ENTITYREFUTILS_H

#include <Utils/Common/Enumerations.h>

namespace SR_UTILS_NS::EntityRefUtils {
    SR_ENUM_NS_CLASS_T(Action, uint8_t,
        Action_Parent, Action_Child, Action_Component, Action_GameObject
    );

    struct PathItem {
        uint64_t hashName;
        uint32_t index;
        Action action;
    };
}

#endif //SRENGINE_ENTITYREFUTILS_H
