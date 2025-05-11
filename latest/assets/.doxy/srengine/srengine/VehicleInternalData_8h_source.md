

# File VehicleInternalData.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**VehicleInternalData.h**](VehicleInternalData_8h.md)

[Go to the documentation of this file](VehicleInternalData_8h.md)


```C++
//
// Created by innerviewer on 5/6/2023.
//

#ifndef SR_ENGINE_VEHICLEINTERNALDATA_H
#define SR_ENGINE_VEHICLEINTERNALDATA_H

#include <Physics/macros.h>

namespace SR_PTYPES_NS {
    struct VehicleInternalData {
        float_t m_peakTorque = 500.0f;
        float_t m_maxOmega = 600.0f; //approx 6000 rpm
        float_t m_switchTime = 0.5f;
        float_t m_strength = 10.0f;
        float_t m_accuracy = 1.0f;
        float_t m_chassisMass = 1.0f;

        SR_MATH_NS::FVector3 m_chassisCMOffset;
    };
}

#endif //SR_ENGINE_VEHICLEINTERNALDATA_H
```


