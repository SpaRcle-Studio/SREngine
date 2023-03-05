//
// Created by innerviewer on 2/28/2023.
//

#ifndef SRENGINE_PHYSXVEHICLE4W3D_H
#define SRENGINE_PHYSXVEHICLE4W3D_H

#include <Physics/3D/Vehicle4W3D.h>

namespace SR_PTYPES_NS {
    class PhysXVehicle4W3D : public Vehicle4W3D{
        using Super = Vehicle4W3D;
        using WheelCenterActorOffsets = SR_MATH_NS::FVector3[4];
    public:
        explicit PhysXVehicle4W3D(LibraryPtr pLibrary);
        ~PhysXVehicle4W3D() override;

    public:
        SR_NODISCARD void* GetHandle() const noexcept override;

    public:
        bool InitVehicle() override;

        physx::PxVehicleWheelsSimData* SetupWheelsSimulationData(
                float_t wheelMass,
                float_t wheelMOI,
                float_t wheelRadius,
                float_t wheelWidth,
                const WheelCenterActorOffsets& wheelCenterActorOffsets,
                const SR_MATH_NS::FVector3& chassisCMOffset,
                float_t chassisMass);

        physx::PxVehicleDriveSimData4W* SetupDriveSimData4W(
                float_t peakTorque,
                float_t maxOmega,
                float_t switchTime,
                float_t strength,
                float_t accuracy);

        physx::PxRigidDynamic* SetupVehicleActor(
                const physx::PxVehicleChassisData& chassisData,
                physx::PxMaterial** wheelMaterials,
                physx::PxConvexMesh** wheelConvexMeshes,
                const physx::PxFilterData& wheelSimFilterData,
                physx::PxMaterial** chassisMaterials,
                physx::PxConvexMesh** chassisConvexMeshes,
                uint32_t numChassisMeshes,
                const physx::PxFilterData& chassisSimFilterData,
                physx::PxPhysics& physics);

    public:
        SR_NODISCARD float_t GetWheelMass() const noexcept { return m_wheelMass; }
        SR_NODISCARD float_t GetWheelMOI() const noexcept { return m_wheelMOI; }
        SR_NODISCARD float_t GetWheelRadius() const noexcept { return m_wheelRadius; }
        SR_NODISCARD float_t GetWheelWidth() const noexcept { return m_wheelWidth; }
        SR_NODISCARD float_t GetChassisMass() const noexcept { return m_chassisMass; }

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

        void SetPeakTorque(float_t peakTorque) { m_peakTorque = peakTorque; }
        void SetMaxOmega(float_t maxOmega) { m_maxOmega = maxOmega; }
        void SetSwitchTime(float_t switchTime) { m_switchTime = switchTime; }
        void SetStrength(float_t strength) { m_strength = strength; }
        void SetAccuracy(float_t accuracy) { m_accuracy = accuracy; }

    private:
        physx::PxVehicleWheelsSimData* m_wheelsSimData = nullptr;
        physx::PxRigidDynamic* m_vehActor = nullptr;

        ///Wheels data
        float_t m_wheelMass = 1.0f;
        float_t m_wheelMOI = 1.0f;
        float_t m_wheelRadius = 1.0f;
        float_t m_wheelWidth = 1.0f;
        float_t m_chassisMass = 1.0f;

        ///Drive data
        float_t m_peakTorque = 500.0f;
        float_t m_maxOmega = 600.0f; //approx 6000 rpm
        float_t m_switchTime = 0.5f;
        float_t m_strength = 10.0f;
        float_t m_accuracy = 1.0f;
    };
}

#endif //SRENGINE_PHYSXVEHICLE4W3D_H
