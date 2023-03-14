//
// Created by innerviewer on 2/28/2023.
//

#ifndef SRENGINE_VEHICLE4W3D_H
#define SRENGINE_VEHICLE4W3D_H

#include <Physics/Vehicle.h>

namespace SR_PTYPES_NS {
    class Vehicle4W3D : public Vehicle {
        using Super = Vehicle;
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Vehicle4W3D);
    public:
        using WheelCenterActorOffsets = SR_MATH_NS::FVector3[4];

    public:
        explicit Vehicle4W3D(LibraryPtr pLibrary);
        ~Vehicle4W3D() override = default;

    public:
        SR_NODISCARD float_t GetWheelMass() const noexcept { return m_wheelMass; }
        SR_NODISCARD float_t GetWheelMOI() const noexcept { return m_wheelMOI; }
        SR_NODISCARD float_t GetWheelRadius() const noexcept { return m_wheelRadius; }
        SR_NODISCARD float_t GetWheelWidth() const noexcept { return m_wheelWidth; }
        SR_NODISCARD float_t GetChassisMass() const noexcept { return m_chassisMass; }
        SR_NODISCARD float_t GetMaxHandBrakeTorque() const noexcept { return m_maxHandBrakeTorque; }
        SR_NODISCARD float_t GetMaxSteer() const noexcept { return m_maxSteer; }
        SR_NODISCARD const WheelCenterActorOffsets& GetWheelCAOffsets() const noexcept { return m_wheelCAOffsets; }
        SR_NODISCARD const SR_MATH_NS::FVector3& GetChassisCMOffset() const noexcept { return m_chassisCMOffset; }

        SR_NODISCARD float_t GetPeakTorque() const noexcept { return m_peakTorque; }
        SR_NODISCARD float_t GetMaxOmega() const noexcept { return m_maxOmega; }
        SR_NODISCARD float_t GetSwitchTime() const noexcept { return m_switchTime; }
        SR_NODISCARD float_t GetStrength() const noexcept { return m_strength; }
        SR_NODISCARD float_t GetAccuracy() const noexcept { return m_accuracy; }

        void SetWheelMass(float_t wheelMass) { m_wheelMass = wheelMass; }
        void SetWheelMOI(float_t maxOmega) { m_wheelMOI = maxOmega; }
        void SetWheelRadius(float_t switchTime) { m_wheelRadius = switchTime; }
        void SetWheelWidth(float_t strength) { m_wheelWidth = strength; }
        void SetChassisMass(float_t accuracy) { m_chassisMass = accuracy; }
        void SetMaxHandBrakeTorque(float_t maxHandBrakeTorque) { m_maxHandBrakeTorque = maxHandBrakeTorque; }
        void SetMaxSteer(float_t maxSteer) { m_maxSteer = maxSteer; }
        void SetCAOffsets(WheelCenterActorOffsets offsets);
        void SetChassisCMOffset(SR_MATH_NS::FVector3 offset) { m_chassisCMOffset = offset; }

        void SetPeakTorque(float_t peakTorque) { m_peakTorque = peakTorque; }
        void SetMaxOmega(float_t maxOmega) { m_maxOmega = maxOmega; }
        void SetSwitchTime(float_t switchTime) { m_switchTime = switchTime; }
        void SetStrength(float_t strength) { m_strength = strength; }
        void SetAccuracy(float_t accuracy) { m_accuracy = accuracy; }

    private:
        ///Wheels data
        float_t m_wheelMass = 1.0f;
        float_t m_wheelMOI = 1.0f;
        float_t m_wheelRadius = 1.0f;
        float_t m_wheelWidth = 1.0f;
        float_t m_chassisMass = 1.0f;
        float_t m_maxHandBrakeTorque = 4000.0f;
        float_t m_maxSteer = 0.3333f;

        WheelCenterActorOffsets m_wheelCAOffsets;
        SR_MATH_NS::FVector3 m_chassisCMOffset;

        ///Drive data
        float_t m_peakTorque = 500.0f;
        float_t m_maxOmega = 600.0f; //approx 6000 rpm
        float_t m_switchTime = 0.5f;
        float_t m_strength = 10.0f;
        float_t m_accuracy = 1.0f;
    };
}

#endif //SRENGINE_VEHICLE4W3D_H
