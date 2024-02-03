//
// Created by Monika on 03.02.2024.
//

#ifndef SR_ENGINE_UTILS_AXIS_H
#define SR_ENGINE_UTILS_AXIS_H

#include <Utils/Common/Enumerations.h>

namespace SR_MATH_NS {
    SR_ENUM_NS_STRUCT_T(Axis, uint64_t,
        None = 0,
        X    = 1 << 0,
        Y    = 1 << 1,
        Z    = 1 << 2,

        XY   = X | Y,
        XZ   = X | Z,
        YZ   = Y | Z,
        XYZ  = X | Y | Z
    );
}

#endif //SR_ENGINE_UTILS_AXIS_H
