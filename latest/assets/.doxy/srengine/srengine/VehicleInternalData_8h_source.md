

# File VehicleInternalData.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**VehicleInternalData.h**](VehicleInternalData_8h.md)

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


