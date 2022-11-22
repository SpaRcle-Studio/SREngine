//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_MEASUREMENT_H
#define SRENGINE_MEASUREMENT_H

#include <Utils/Common/Enumerations.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(Measurement, int32_t,
            SpaceZero = 0,
            Space1D = 1,
            Space2D = 2,
            Space3D = 3,
            Space4D = 4,
            Unknown = SR_INT32_MAX
    );
}

#endif //SRENGINE_MEASUREMENT_H
