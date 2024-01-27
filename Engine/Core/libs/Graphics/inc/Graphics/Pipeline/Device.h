//
// Created by Monika on 08.02.2023.
//

#ifndef SR_ENGINE_GRAPHICS_DEVICE_H
#define SR_ENGINE_GRAPHICS_DEVICE_H

#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(DeviceType, uint8_t,
        Nvidia, AMD, Intel
    );
}

#endif //SR_ENGINE_GRAPHICS_DEVICE_H
