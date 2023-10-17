//
// Created by innerviewer on 10/17/2023.
//

#ifndef SRENGINE_LISTENERDATA_H
#define SRENGINE_LISTENERDATA_H

namespace SR_AUDIO_NS {
    SR_ENUM_NS_CLASS_T(ListenerDistanceModel, uint8_t,
       None,
       InverseDistance,
       InverseDistanceClamped,
       LinearDistance,
       LinearDistanceClamped,
       ExponentDistance,
       ExponentDistanceClamped
    );

    struct ListenerData : public SR_UTILS_NS::NonCopyable {
        ListenerDistanceModel distanceModel = ListenerDistanceModel::InverseDistanceClamped;
        float_t rolloffFactor = 1.0f;
        float_t referenceDistance = 1.0f;
        float_t maxDistance = SR_FLOAT_MAX;
        SR_MATH_NS::FVector3 velocity = SR_MATH_NS::FVector3(0.f, 0.f, 0.f);
        float_t dopplerFactor = 1.0f;
        float_t gain = 1.0f;
        float_t outerConeGain = 0.0f;
    };
}

#endif //SRENGINE_LISTENERDATA_H
