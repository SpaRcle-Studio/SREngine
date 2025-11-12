#include <Physics/PhysX/PhysXUtils.h>

namespace SR_PHYSICS_UTILS_NS {
    PhysXPvdConnection* CreatePvdConnection(physx::PxFoundation* pFoundation, const std::string& ip, uint16_t port, uint32_t timeout){
        auto&& pPvd = PxCreatePvd(*pFoundation);
        auto&& pTransport = physx::PxDefaultPvdSocketTransportCreate(ip.c_str(), port, timeout);

        if (pPvd->connect(*pTransport, physx::PxPvdInstrumentationFlag::eALL)) {
            return pPvd;
        }

        pPvd->release();

        return nullptr;
    }
}
