

# File WheelInternalData.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**WheelInternalData.h**](WheelInternalData_8h.md)

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


