//
// Created by Monika on 25.11.2022.
//

#include <Physics/PhysX/PhysXRigidbody3D.h>
#include <Physics/PhysX/PhysXLibraryImpl.h>

namespace SR_PTYPES_NS {
    PhysXRigidbody3DImpl::~PhysXRigidbody3DImpl() {
        if (m_rigidActor) {
            m_rigidActor->release();
            m_rigidActor = nullptr;
        }
    }

    void* PhysXRigidbody3DImpl::GetHandle() const noexcept {
        return m_rigidActor;
    }

    void PhysXRigidbody3DImpl::UpdateInertia() {
        if (!m_rigidActor) {
            return;
        }

        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()) {
            physx::PxRigidBodyExt::updateMassAndInertia(*pRigidBody, m_rigidbody->GetMass());
        }
    }

    bool PhysXRigidbody3DImpl::InitBody() {
        if (!Super::InitBody()) {
            SRHalt("failed to init base body!");
            return false;
        }

        auto&& pPhysics = m_rigidbody->GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();
        if (!pPhysics) {
            SRHalt("pPhysics is nullptr!");
            return false;
        }

        m_rigidbodyTranslation = m_rigidbody->GetTranslation();
        m_rigidbodyRotation = m_rigidbody->GetRotation();

        if (m_rigidActor) {
            m_rigidActor->release();
            m_rigidActor = nullptr;
        }

        if (m_rigidbody->IsStatic()) {
            m_rigidActor = pPhysics->createRigidStatic(physx::PxTransform(physx::PxVec3(0.f, 0.f, 0.f)));
        }
        else {
            m_rigidActor = pPhysics->createRigidDynamic(physx::PxTransform(physx::PxVec3(0.f, 0.f, 0.f)));
        }

        if (!m_rigidActor) {
            SR_ERROR("PhysXRigidbody3D::InitBody() : failed to create rigid body!");
            return false;
        }

        UpdateLocks();

        m_rigidActor->userData = (void*)m_rigidbody;

        m_rigidbody->UpdateMatrix(true);
        m_rigidbody->SetShapeDirty(true);

        /// проверяем именно на Updated, так как остальные варианты тут недопустимы
        if (m_rigidbody->UpdateShape() != RBUpdShapeRes::Updated) {
            SR_ERROR("PhysXRigidbody3D::InitBody() : shape is not updated!");
            return false;
        }

        UpdateInertia();

        return true;
    }

    void PhysXRigidbody3DImpl::AddLinearVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (!m_rigidActor) {
            return;
        }

        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()) {
            pRigidBody->setLinearVelocity(pRigidBody->getLinearVelocity() + SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    void PhysXRigidbody3DImpl::AddAngularVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (!m_rigidActor) {
            return;
        }

        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()) {
            pRigidBody->setAngularVelocity(pRigidBody->getAngularVelocity() + SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    void PhysXRigidbody3DImpl::SetLinearVelocity(const SR_MATH_NS::FVector3 &velocity) {
        if (!m_rigidActor) {
            return;
        }

        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()) {
            pRigidBody->setLinearVelocity(SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    void PhysXRigidbody3DImpl::SetAngularVelocity(const SR_MATH_NS::FVector3 &velocity) {
        if (!m_rigidActor) {
            return;
        }

        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()) {
            pRigidBody->setAngularVelocity(SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    SR_MATH_NS::FVector3 PhysXRigidbody3DImpl::GetLinearVelocity() const {
        if (!m_rigidActor) {
            return SR_MATH_NS::FVector3();
        }

        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()) {
            return SR_PHYSICS_UTILS_NS::PxV3ToFV3(pRigidBody->getLinearVelocity());
        }

        return SR_MATH_NS::FVector3();
    }

    SR_MATH_NS::FVector3 PhysXRigidbody3DImpl::GetAngularVelocity() const {
        if (!m_rigidActor) {
            return SR_MATH_NS::FVector3();
        }

        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()) {
            return SR_PHYSICS_UTILS_NS::PxV3ToFV3(pRigidBody->getAngularVelocity());
        }

        return SR_MATH_NS::FVector3();
    }

    bool PhysXRigidbody3DImpl::UpdateMatrix(bool force) {
        if (!Super::UpdateMatrix(force)) {
            return false;
        }

        auto&& translation = m_rigidbody->GetTranslation() + m_rigidbody->GetCenterDirection();

        physx::PxTransform transform;

        SR_MATH_NS::Quaternion q;

        if (m_rigidbody->GetCollisionShape()->GetType() == ShapeType::Capsule3D) {
            q = m_rigidbody->GetRotation().RotateZ(90);
        }
        else {
            q = m_rigidbody->GetRotation();
        }

        transform.p = physx::PxVec3(translation.x, translation.y, translation.z);
        transform.q = physx::PxQuat(q.X(), q.Y(), q.Z(), q.W());

        m_rigidActor->setGlobalPose(transform);

        // TODO: воостановить для редактора ClearForces();

        return true;
    }

    bool PhysXRigidbody3DImpl::UpdateShapeInternal() {
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

        if (!m_rigidbody->GetCollisionShape()->GetHandle()) {
            SRHalt("Internal shape is nullptr!");
            return false;
        }

        if (!m_rigidActor->attachShape(*(physx::PxShape*)m_rigidbody->GetCollisionShape()->GetHandle())) {
            SRHalt("PhysXRigidbody3D::UpdateShapeInternal() : failed to attach shape!");
            return false;
        }

        return true;
    }

    void PhysXRigidbody3DImpl::SetLinearLock(const SR_MATH_NS::BVector3& lock) {
        Super::SetLinearLock(lock);
        UpdateLocks();
    }
    void PhysXRigidbody3DImpl::SetAngularLock(const SR_MATH_NS::BVector3& lock) {
        Super::SetAngularLock(lock);
        UpdateLocks();
    }

    void PhysXRigidbody3DImpl::UpdateLocks() {
        if (!m_rigidActor) {
            return;
        }

        if (auto&& pDynamic = m_rigidActor->is<physx::PxRigidDynamic>()) {
            auto&& flags = static_cast<physx::PxRigidDynamicLockFlags>(0);
            auto&& linearLock = GetRigidbody<Rigidbody3D>()->GetLinearLock();
            auto&& angularLock = GetRigidbody<Rigidbody3D>()->GetAngularLock();

            if (linearLock.X()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X; }
            if (linearLock.Y()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y; }
            if (linearLock.Z()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z; }

            if (angularLock.X()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X; }
            if (angularLock.Y()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y; }
            if (angularLock.Z()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z; }

            pDynamic->setRigidDynamicLockFlags(flags);
        }
    }

    void PhysXRigidbody3DImpl::ClearForces() {
        if (!m_rigidActor) {
            return;
        }

        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>(); pRigidBody && pRigidBody->getScene()) {
            pRigidBody->clearForce();
            pRigidBody->setLinearVelocity(physx::PxVec3(0, 0, 0));
            pRigidBody->setAngularVelocity(physx::PxVec3(0, 0, 0));
        }
        Super::ClearForces();
    }

    void PhysXRigidbody3DImpl::Synchronize() {
        if (!m_rigidActor) {
            return;
        }

        auto&& pTransform = m_rigidbody->GetTransform();
        if (!pTransform) {
            return;
        }

        auto&& globalPose = m_rigidActor->getGlobalPose();

        auto&& rigidbodyTranslation = SR_MATH_NS::FVector3(globalPose.p.x, globalPose.p.y, globalPose.p.z);
        auto&& rigidbodyRotation = SR_MATH_NS::Quaternion(globalPose.q.x, globalPose.q.y, globalPose.q.z, globalPose.q.w);

        if (m_rigidbody->GetType() == ShapeType::Capsule3D) {
            rigidbodyRotation = rigidbodyRotation.RotateZ(-90);
        }

        /// ------------------------------------------------------------------------------------------------------------

        SR_MATH_NS::FVector3 deltaTranslation(SR_MATH_NS::Unit(0));
        SR_MATH_NS::Quaternion deltaQuaternion(SR_MATH_NS::Quaternion::Identity());

        if (m_rigidbodyTranslation.IsFinite()) {
            deltaTranslation = (rigidbodyTranslation - m_rigidbody->GetCenterDirection()) - m_rigidbodyTranslation;
        }

        if (m_rigidbodyRotation.IsFinite()) {
            deltaQuaternion = rigidbodyRotation * m_rigidbodyRotation.Inverse();
        }

        if (!deltaTranslation.IsEquals(SR_MATH_NS::FVector3(SR_MATH_NS::Unit(0)), SR_MATH_NS::Unit(0.001))) {
            pTransform->GlobalTranslate(deltaTranslation);
        }

       if (!deltaQuaternion.IsEquals(SR_MATH_NS::FVector3(SR_MATH_NS::Unit(0)), SR_MATH_NS::Unit(0.0001))) {
           pTransform->SetRotation(rigidbodyRotation);
           // TODO: maybe use? pTransform->Rotate(deltaQuaternion);
       }

        m_rigidbody->UpdateMatrix(true);

        m_rigidbodyTranslation = m_rigidbody->GetTranslation();
        m_rigidbodyRotation = m_rigidbody->GetRotation();

        Super::Synchronize();
    }
}
