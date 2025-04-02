

# File PhysXUtils.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysX**](dir_ff2872f47b85400c7459df934950f633.md) **>** [**PhysXUtils.h**](PhysXUtils_8h.md)

[Go to the documentation of this file](PhysXUtils_8h.md)


```C++
//
// Created by Monika on 24.11.2022.
//

#ifndef SR_ENGINE_PHYSXUTILS_H
#define SR_ENGINE_PHYSXUTILS_H

#include <Utils/stdInclude.h>
#include <Utils/Math/Vector3.h>

#include <PxPhysicsAPI.h>
#include <PxFoundation.h>
#include <PxSimulationEventCallback.h>

SR_CONSTEXPR auto SR_PHYSX_FOUNDATION_VERSION = PX_PHYSICS_VERSION;
SR_CONSTEXPR auto SR_PHYSX_PHYSICS_VERSION = PX_PHYSICS_VERSION;

namespace SR_PHYSICS_NS {
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
    typedef debugger::comm::PvdConnection PhysXPvdConnection;
#else
    typedef physx::PxPvd PhysXPvdConnection;
#endif
}

namespace SR_PHYSICS_UTILS_NS {
    SR_MAYBE_UNUSED static physx::PxVec3 FV3ToPxV3(const SR_MATH_NS::FVector3 &vector3) {
        return physx::PxVec3(vector3.x, vector3.y, vector3.z);
    }

    SR_MAYBE_UNUSED static SR_MATH_NS::FVector3 PxV3ToFV3(const physx::PxVec3 &vector3) {
        return SR_MATH_NS::FVector3(vector3.x, vector3.y, vector3.z);
    }

    static physx::PxCombineMode::Enum CombineToPxCombine(const Combine mode){
        switch (mode) {
            case Combine::Minimum:
                return physx::PxCombineMode::Enum::eMIN;
            case Combine::Average:
                return physx::PxCombineMode::Enum::eAVERAGE;
            case Combine::Maximum:
                return physx::PxCombineMode::Enum::eMAX;
            case Combine::Multiply:
                return physx::PxCombineMode::Enum::eMULTIPLY;
            default:
                SRHalt("CombineToPxCombine() : unsolved situation.");
                return physx::PxCombineMode::Enum::eAVERAGE;
        }
    }

    PhysXPvdConnection* CreatePvdConnection(physx::PxFoundation* pFoundation, const std::string& ip, uint16_t port, uint32_t timeout) {
        auto&& pPvd = PxCreatePvd(*pFoundation);
        auto&& pTransport = physx::PxDefaultPvdSocketTransportCreate(ip.c_str(), port, timeout);

        if (pPvd->connect(*pTransport, physx::PxPvdInstrumentationFlag::eALL)) {
            return pPvd;
        }

        pPvd->release();

        return nullptr;
    }
}

#endif //SR_ENGINE_PHYSXUTILS_H
```


