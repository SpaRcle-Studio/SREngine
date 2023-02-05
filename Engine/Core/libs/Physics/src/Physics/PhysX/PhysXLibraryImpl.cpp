//
// Created by Monika on 24.11.2022.
//

#include <Physics/PhysX/PhysXLibraryImpl.h>

#include <Physics/PhysX/PhysXPhysicsWorld.h>
#include <Physics/PhysX/PhysXCollisionShape.h>
#include <Physics/PhysX/PhysXRigidbody3D.h>

namespace SR_PHYSICS_NS {
    bool PhysXLibraryImpl::Initialize() {
        m_allocatorCallback = new physx::PxDefaultAllocator();
        m_errorCallback = new physx::PxDefaultErrorCallback();

        m_foundation = PxCreateFoundation(SR_PHYSX_FOUNDATION_VERSION, *m_allocatorCallback, *m_errorCallback);
        if (!m_foundation) {
            SR_ERROR("PhysXLibraryImpl::Initialize() : failed to create foundation!");
            return false;
        }

        m_pvd = PxCreatePvd(*m_foundation);
        m_pvdTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
        m_pvd->connect(*m_pvdTransport, physx::PxPvdInstrumentationFlag::eALL);

        m_physics = PxCreatePhysics(SR_PHYSX_FOUNDATION_VERSION, *m_foundation, physx::PxTolerancesScale(), true, m_pvd);
        if (!m_physics) {
            SR_ERROR("PhysXLibraryImpl::Initialize() : failed to create physics!");
            return false;
        }

        return true;
    }

    PhysXLibraryImpl::~PhysXLibraryImpl() {
        if (m_physics) {
            m_physics->release();
            m_physics = nullptr;
        }

        if(m_pvd) {
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
                return true;
            default:
                return false;
        }
    }

    SR_PTYPES_NS::CollisionShape* PhysXLibraryImpl::CreateCollisionShape() {
        return new SR_PTYPES_NS::PhysXCollisionShape(this);
    }

    SR_PTYPES_NS::Rigidbody3D* PhysXLibraryImpl::CreateRigidbody3D() {
        return new SR_PTYPES_NS::PhysXRigidbody3D(this);
    }

    SR_PHYSICS_NS::PhysicsWorld* PhysXLibraryImpl::CreatePhysicsWorld(Space space) {
        return new PhysXPhysicsWorld(this, space);
    }
}