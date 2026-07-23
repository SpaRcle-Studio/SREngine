//
// Created by innerviewer on 10/17/2023.
//

#ifndef SR_ENGINE_LISTENERDATA_H
#define SR_ENGINE_LISTENERDATA_H

#include <Audio/macros.h>

#include <Utils/Common/Enumerations.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector6.h>

namespace SR_AUDIO_NS {
    SR_ENUM_NS_CLASS_T(ListenerDistanceModel, uint8_t,
                       None,
                       Inverse,
                       InverseClamped,
                       Linear,
                       LinearClamped,
                       Exponent,
                       ExponentClamped
    );

    struct ListenerData {
        ListenerDistanceModel distanceModel = ListenerDistanceModel::InverseClamped;
        SR_MATH_NS::FVector3 velocity;
        float_t gain = 1.0f;
        float_t globalGain = 1.0f;
        SR_MATH_NS::FVector3 position;
        SR_MATH_NS::FVector6 orientation;
    };
}

#endif //SR_ENGINE_LISTENERDATA_H
