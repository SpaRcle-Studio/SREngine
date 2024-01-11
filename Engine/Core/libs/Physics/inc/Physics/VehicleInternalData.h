//
// Created by innerviewer on 5/6/2023.
//

#ifndef SR_ENGINE_VEHICLEINTERNALDATA_H
#define SR_ENGINE_VEHICLEINTERNALDATA_H

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
