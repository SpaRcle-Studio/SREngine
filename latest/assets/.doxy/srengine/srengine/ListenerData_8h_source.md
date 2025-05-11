

# File ListenerData.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**ListenerData.h**](ListenerData_8h.md)

[Go to the documentation of this file](ListenerData_8h.md)


```C++
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
        SR_MATH_NS::FVector3 position;
        SR_MATH_NS::FVector6 orientation;
    };
}

#endif //SR_ENGINE_LISTENERDATA_H
```


