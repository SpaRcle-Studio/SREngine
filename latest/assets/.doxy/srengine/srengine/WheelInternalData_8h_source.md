

# File WheelInternalData.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**WheelInternalData.h**](WheelInternalData_8h.md)

[Go to the documentation of this file](WheelInternalData_8h.md)


```C++
//
// Created by innerviewer on 5/6/2023.
//

#ifndef SR_ENGINE_WHEELINTERNALDATA_H
#define SR_ENGINE_WHEELINTERNALDATA_H

#include <Physics/macros.h>

#include <Utils/Common/Enumerations.h>

namespace SR_PTYPES_NS {
    class PhysicsMaterial;

    SR_ENUM_NS_STRUCT_T(Vehicle4WWheelOrder, uint8_t,
        FrontLeft,
        FrontRight,
        RearLeft,
        RearRight,
        Size
    );

    struct WheelInternalData {
        float_t m_wheelMass = 1.0f;
        float_t m_wheelMOI = 1.0f;
        float_t m_wheelRadius = 1.0f;
        float_t m_wheelWidth = 1.0f;
        float_t m_maxHandBrakeTorque = 4000.0f;
        float_t m_maxSteer = 0.3333f;

        SR_MATH_NS::FVector3 m_wheelCenterActorOffset;

        PhysicsMaterial* m_wheelMaterial = nullptr;

    };
}

#endif //SR_ENGINE_WHEELINTERNALDATA_H
```


