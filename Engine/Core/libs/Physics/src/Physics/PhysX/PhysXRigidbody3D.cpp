//
// Created by Monika on 25.11.2022.
//

#include <Physics/PhysX/PhysXRigidbody3D.h>

namespace SR_PTYPES_NS {
    PhysXRigidbody3D::PhysXRigidbody3D(Super::LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    PhysXRigidbody3D::~PhysXRigidbody3D() {
        SRAssert(!m_rigidActor);
    }

    void* PhysXRigidbody3D::GetHandle() const noexcept {
        return m_rigidActor;
    }

    void PhysXRigidbody3D::SetMass(float_t mass) {
        if (auto&& pRigidBody = dynamic_cast<physx::PxRigidBody*>(m_rigidActor)) {
            pRigidBody->setMass(mass);
        }
        Super::SetMass(mass);
    }

    bool PhysXRigidbody3D::InitBody() {
        if (!Super::InitBody()) {
            SRHalt("failed to init base body!");
            return false;
        }

        auto&& pPhysics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();
        if (!pPhysics) {
            SRHalt("pPhysics is nullptr!");
            return false;
        }

        if (m_isStatic) {
            m_rigidActor = pPhysics->createRigidStatic(physx::PxTransform(physx::PxVec3(0.f, 0.f, 0.f)));
        }
        else {
            m_rigidActor = pPhysics->createRigidDynamic(physx::PxTransform(physx::PxVec3(0.f, 0.f, 0.f)));
        }

        if (!m_rigidActor) {
            SR_ERROR("PhysXRigidbody3D::InitBody() : failed to create rigid body!");
            return false;
        }

        return true;
    }

    bool PhysXRigidbody3D::UpdateMatrix() {
        return Super::UpdateMatrix();
    }

    void PhysXRigidbody3D::DeInitBody() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            if (m_rigidActor) {
                physicsScene->Remove(this);
            }
        }
        else {
            SRHalt("Failed to get physics scene!");
        }

        Super::DeInitBody();
    }

    bool PhysXRigidbody3D::UpdateShapeInternal() {
        if (!m_rigidActor) {
            SRHalt("m_rigidActor is nullptr!");
            return false;
        }

        physx::PxShape* shapes[1];
        m_rigidActor->getShapes(shapes, 1);
        if (shapes[0]) {
            m_rigidActor->detachShape(*shapes[0]);
        }

        if (!m_rigidActor->attachShape(*(physx::PxShape*)m_shape->GetHandle())) {
            SRHalt("PhysXRigidbody3D::UpdateShapeInternal() : failed to attach shape!");
            return false;
        }

        return true;
    }
}
