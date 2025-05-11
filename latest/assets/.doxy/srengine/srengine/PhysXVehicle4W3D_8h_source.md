

# File PhysXVehicle4W3D.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysX**](dir_3ad88c97ba0c5fb710f861c6ad44644a.md) **>** [**PhysXVehicle4W3D.h**](PhysXVehicle4W3D_8h.md)

[Go to the documentation of this file](PhysXVehicle4W3D_8h.md)


```C++
//
// Created by innerviewer on 2/28/2023.
//

#ifndef SR_ENGINE_PHYSXVEHICLE4W3D_H
#define SR_ENGINE_PHYSXVEHICLE4W3D_H

#include <Physics/3D/Vehicle4W3D.h>

namespace SR_PTYPES_NS {
    /*class PhysXVehicle4W3D : public Vehicle4W3D {
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
    };*/
}

#endif //SR_ENGINE_PHYSXVEHICLE4W3D_H
```


