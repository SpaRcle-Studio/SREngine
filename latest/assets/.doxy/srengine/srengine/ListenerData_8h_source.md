

# File ListenerData.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**ListenerData.h**](ListenerData_8h.md)

[Go to the documentation of this file](ListenerData_8h.md)


```C++
//
// Created by innerviewer on 10/17/2023.
//

#ifndef SR_ENGINE_LISTENERDATA_H
#define SR_ENGINE_LISTENERDATA_H

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
        SR_MATH_NS::FVector3 position;
        SR_MATH_NS::FVector6 orientation;
    };
}

#endif //SR_ENGINE_LISTENERDATA_H
```


