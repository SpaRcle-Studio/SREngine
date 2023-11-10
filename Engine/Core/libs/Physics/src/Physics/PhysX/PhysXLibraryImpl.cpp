//
// Created by Monika on 24.11.2022.
//

#include <Utils/Common/Features.h>

#include <Physics/PhysX/PhysXLibraryImpl.h>

#include <Physics/PhysX/PhysXPhysicsWorld.h>
#include <Physics/PhysX/PhysXCollisionShape.h>
#include <Physics/PhysX/PhysXRigidbody3D.h>
#include <Physics/PhysX/PhysXMaterialImpl.h>
#include <Physics/PhysX/PhysXVehicle4W3D.h>

namespace SR_PHYSICS_NS {
    bool PhysXLibraryImpl::Initialize() {
        SR_TRACY_ZONE;

        if (!Super::Initialize()){
            SR_ERROR("PhysXLibraryImpl::Initialize() : failed to initialize basic library!");
        }

        m_allocatorCallback = new physx::PxDefaultAllocator();
        m_errorCallback = new physx::PxDefaultErrorCallback();

        m_foundation = PxCreateFoundation(SR_PHYSX_FOUNDATION_VERSION, *m_allocatorCallback, *m_errorCallback);
        if (!m_foundation) {
            SR_ERROR("PhysXLibraryImpl::Initialize() : failed to create foundation!");
            return false;
        }

        m_pvd = PxCreatePvd(*m_foundation);

        m_physics = PxCreatePhysics(SR_PHYSX_FOUNDATION_VERSION, *m_foundation, physx::PxTolerancesScale(), true, m_pvd);
        if (!m_physics) {
            SR_ERROR("PhysXLibraryImpl::Initialize() : failed to create physics!");
            return false;
        }

        if (IsVehicleSupported()) {
            SR_TRACY_ZONE_N("Init vechicle");

            if (!physx::PxInitVehicleSDK(*m_physics)){
                SR_ERROR("PhysXLibraryImpl::Initialize() : failed to initialize Vehicle SDK!");
                return false;
            }
            physx::PxVehicleSetBasisVectors(physx::PxVec3(0,1,0), physx::PxVec3(0,0,1));
            physx::PxVehicleSetUpdateMode(physx::PxVehicleUpdateMode::eACCELERATION);
        }

        return true;
    }

    PhysXLibraryImpl::~PhysXLibraryImpl() {
        if (IsVehicleSupported()){
            physx::PxCloseVehicleSDK();
        }

        if (m_physics) {
            m_physics->release();
            m_physics = nullptr;
        }

        if (m_pvd) {
            m_pvd->release();
            m_pvd = nullptr;
        }

        if (m_pvdTransport) {
            m_pvdTransport->release();
            m_pvdTransport = nullptr;
        }

        if (m_foundation) {
            m_foundation->release();
            m_foundation = nullptr;
        }

        SR_SAFE_DELETE_PTR(m_allocatorCallback);
        SR_SAFE_DELETE_PTR(m_errorCallback);
    }

    bool PhysXLibraryImpl::IsShapeSupported(ShapeType type) const {
        switch (type) {
            case ShapeType::Plane3D:
            case ShapeType::Box3D:
            case ShapeType::Capsule3D:
            case ShapeType::Sphere3D:
            case ShapeType::Convex3D:
                return true;
            default:
                return false;
        }
    }

    SR_PTYPES_NS::CollisionShape* PhysXLibraryImpl::CreateCollisionShape() {
        return new SR_PTYPES_NS::PhysXCollisionShape(this);
    }

    SR_PTYPES_NS::Rigidbody3DImpl* PhysXLibraryImpl::CreateRigidbody3DImpl() {
        return new SR_PTYPES_NS::PhysXRigidbody3DImpl();
    }

    SR_PHYSICS_NS::PhysicsWorld* PhysXLibraryImpl::CreatePhysicsWorld(Space space) {
        return new PhysXPhysicsWorld(this, space);
    }

    SR_PTYPES_NS::PhysicsMaterialImpl* PhysXLibraryImpl::CreatePhysicsMaterial() {
        return new SR_PTYPES_NS::PhysXMaterialImpl(this);
    }

    SR_PTYPES_NS::Vehicle4W3D *PhysXLibraryImpl::CreateVehicle4W3D() {
        return new SR_PTYPES_NS::PhysXVehicle4W3D(this);
    }

    void PhysXLibraryImpl::ConnectPVD() {
        SR_TRACY_ZONE_N("Create PVD");

        if (m_pvd->isConnected()) {
            m_pvd->disconnect();
            SR_LOG("PhysXLibraryImpl::ConnectPVD() : previous connection aborted.")
        }

        if (m_pvdTransport) {
            m_pvdTransport->release();
            m_pvdTransport = nullptr;
        }

        SR_LOG("PhysXLibraryImpl::ConnectPVD() : trying to connect.")

        m_pvdTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 1000);
        m_pvd->connect(*m_pvdTransport, physx::PxPvdInstrumentationFlag::eALL);
    }
}