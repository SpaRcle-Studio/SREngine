//
// Created by Monika on 24.11.2022.
//

#ifndef SRENGINE_PHYSXUTILS_H
#define SRENGINE_PHYSXUTILS_H

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

#endif //SRENGINE_PHYSXUTILS_H