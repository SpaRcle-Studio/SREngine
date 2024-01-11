//
// Created by innerviewer on 5/6/2023.
//

#ifndef SR_ENGINE_WHEELINTERNALDATA_H
#define SR_ENGINE_WHEELINTERNALDATA_H

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
