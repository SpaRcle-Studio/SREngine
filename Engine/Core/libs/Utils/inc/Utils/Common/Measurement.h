//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_MEASUREMENT_H
#define SR_ENGINE_MEASUREMENT_H

#include <Utils/Common/Enumerations.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(Measurement, int32_t,
        Unknown = -2,
        Holder = -1,
        SpaceZero = 0,
        Space1D = 1,
        Space2D = 2,
        Space3D = 3,
        Space4D = 4
    );
}

#endif //SR_ENGINE_MEASUREMENT_H
