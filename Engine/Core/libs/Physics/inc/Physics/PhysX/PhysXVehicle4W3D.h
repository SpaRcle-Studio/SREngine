//
// Created by innerviewer on 2/28/2023.
//

#ifndef SRENGINE_PHYSXVEHICLE4W3D_H
#define SRENGINE_PHYSXVEHICLE4W3D_H

#include <Physics/3D/Vehicle4W3D.h>

namespace SR_PTYPES_NS {
    class PhysXVehicle4W3D : public Vehicle4W3D {
        using Super = Vehicle4W3D;
    public:
        explicit PhysXVehicle4W3D(LibraryPtr pLibrary);
        ~PhysXVehicle4W3D() override;

    public:
        SR_NODISCARD void* GetHandle() const noexcept override;

    public:
        bool InitVehicle() override;

        SR_NODISCARD physx::PxVehicleWheelsSimData* SetupWheelsSimulationData();

        SR_NODISCARD physx::PxVehicleDriveSimData4W* SetupDriveSimData4W();

        SR_NODISCARD physx::PxRigidDynamic* SetupVehicleActor(
                const physx::PxVehicleChassisData& chassisData,
                physx::PxMaterial** wheelMaterials,
                physx::PxConvexMesh** wheelConvexMeshes,
                const physx::PxFilterData& wheelSimFilterData,
                physx::PxMaterial** chassisMaterials,
                physx::PxConvexMesh** chassisConvexMeshes,
                uint32_t numChassisMeshes,
                const physx::PxFilterData& chassisSimFilterData,
                physx::PxPhysics& physics);

    private:
        physx::PxVehicleWheelsSimData* m_wheelsSimData = nullptr;
        physx::PxRigidDynamic* m_vehActor = nullptr;
    };
}

#endif //SRENGINE_PHYSXVEHICLE4W3D_H
