//
// Created by Monika on 25.11.2022.
//

#include <Physics/PhysX/PhysXRigidbody3D.h>

namespace SR_PTYPES_NS {
    PhysXRigidbody3D::PhysXRigidbody3D(Super::LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    PhysXRigidbody3D::~PhysXRigidbody3D() {
        if (m_rigidActor) {
            m_rigidActor->release();
            m_rigidActor = nullptr;
        }
    }

    void* PhysXRigidbody3D::GetHandle() const noexcept {
        return m_rigidActor;
    }

    void PhysXRigidbody3D::UpdateInertia() {
        if (m_rigidActor) {
            if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()) {
                physx::PxRigidBodyExt::updateMassAndInertia(*pRigidBody, m_mass);
            }
        }
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

        if (m_rigidActor) {
            m_rigidActor->release();
            m_rigidActor = nullptr;
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

        m_rigidActor->userData = (void*)dynamic_cast<Rigidbody*>(this);

        UpdateMatrix(true);
        UpdateShape();
        UpdateInertia();

        return true;
    }

    void PhysXRigidbody3D::AddLocalVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()){
            pRigidBody->setLinearVelocity(pRigidBody->getLinearVelocity() + SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    void PhysXRigidbody3D::AddGlobalVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()){
            pRigidBody->setAngularVelocity(pRigidBody->getAngularVelocity() + SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    bool PhysXRigidbody3D::UpdateMatrix(bool force) {
        if (!Super::UpdateMatrix(force)) {
            return false;
        }

        auto&& translation = m_translation + GetCenterDirection();

        physx::PxTransform transform;

        transform.p = physx::PxVec3(translation.x, translation.y, translation.z);
        transform.q = physx::PxQuat(m_rotation.X(), m_rotation.Y(), m_rotation.Z(), m_rotation.W());

        m_rigidActor->setGlobalPose(transform);

        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>(); pRigidBody && pRigidBody->getScene()) {
            pRigidBody->clearForce();
            pRigidBody->setLinearVelocity(physx::PxVec3(0, 0, 0));
            pRigidBody->setAngularVelocity(physx::PxVec3(0, 0, 0));
        }

        return true;
    }

    bool PhysXRigidbody3D::UpdateShapeInternal() {
        if (!m_rigidActor) {
            SRHalt("m_rigidActor is nullptr!");
            return false;
        }

        const uint32_t shapesCount = m_rigidActor->getNbShapes();
        if (shapesCount > 0) {
            std::vector<physx::PxShape*> shapes;
            shapes.resize(shapesCount);
            m_rigidActor->getShapes(shapes.data(), shapesCount);
            for (auto&& pShape : shapes) {
                m_rigidActor->detachShape(*pShape);
            }
        }

        if (!m_rigidActor->attachShape(*(physx::PxShape*)m_shape->GetHandle())) {
            SRHalt("PhysXRigidbody3D::UpdateShapeInternal() : failed to attach shape!");
            return false;
        }

        return true;
    }
}
