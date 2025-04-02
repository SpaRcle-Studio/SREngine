

# File PhysXVehicle4W3D.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysX**](dir_ff2872f47b85400c7459df934950f633.md) **>** [**PhysXVehicle4W3D.h**](PhysXVehicle4W3D_8h.md)

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


