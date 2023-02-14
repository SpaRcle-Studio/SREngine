//
// Created by Monika on 25.11.2022.
//

#include <Physics/PhysX/PhysXRigidbody3D.h>
#include <Physics/PhysX/PhysXLibraryImpl.h>

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

        UpdateLocks();

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

    void PhysXRigidbody3D::AddLinearVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()){
            pRigidBody->setLinearVelocity(pRigidBody->getLinearVelocity() + SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    void PhysXRigidbody3D::AddAngularVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()){
            pRigidBody->setAngularVelocity(pRigidBody->getAngularVelocity() + SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    void PhysXRigidbody3D::SetLinearVelocity(const SR_MATH_NS::FVector3 &velocity) {
        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()){
            pRigidBody->setLinearVelocity(SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    void PhysXRigidbody3D::SetAngularVelocity(const SR_MATH_NS::FVector3 &velocity) {
        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()){
            pRigidBody->setAngularVelocity(SR_PHYSICS_UTILS_NS::FV3ToPxV3(velocity));
        }
    }

    SR_MATH_NS::FVector3 PhysXRigidbody3D::GetLinearVelocity() const {
        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()){
            return SR_PHYSICS_UTILS_NS::PxV3ToFV3(pRigidBody->getLinearVelocity());
        }

        return Super::GetLinearVelocity();
    }

    SR_MATH_NS::FVector3 PhysXRigidbody3D::GetAngularVelocity() const {
        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>()){
            return SR_PHYSICS_UTILS_NS::PxV3ToFV3(pRigidBody->getAngularVelocity());
        }

        return Super::GetAngularVelocity();
    }

    bool PhysXRigidbody3D::UpdateMatrix(bool force) {
        if (!Super::UpdateMatrix(force)) {
            return false;
        }

        auto&& translation = m_translation + GetCenterDirection();

        physx::PxTransform transform;

        SR_MATH_NS::Quaternion q;

        if (m_shape->GetType() == ShapeType::Capsule3D) {
            q = m_rotation.RotateZ(90);
        }
        else {
            q = m_rotation;
        }

        transform.p = physx::PxVec3(translation.x, translation.y, translation.z);
        transform.q = physx::PxQuat(q.X(), q.Y(), q.Z(), q.W());

        m_rigidActor->setGlobalPose(transform);

        // TODO: воостановить для редактора ClearForces();

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

    void PhysXRigidbody3D::SetLinearLock(const SR_MATH_NS::BVector3& lock) {
        Super::SetLinearLock(lock);
        UpdateLocks();
    }
    void PhysXRigidbody3D::SetAngularLock(const SR_MATH_NS::BVector3& lock) {
        Super::SetAngularLock(lock);
        UpdateLocks();
    }

    void PhysXRigidbody3D::UpdateLocks() {
        if (!m_rigidActor) {
            return;
        }

        if (auto&& pDynamic = m_rigidActor->is<physx::PxRigidDynamic>()) {
            physx::PxRigidDynamicLockFlags flags = static_cast<physx::PxRigidDynamicLockFlags>(0);

            if (m_linearLock.X()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X; }
            if (m_linearLock.Y()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y; }
            if (m_linearLock.Z()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z; }

            if (m_angularLock.X()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X; }
            if (m_angularLock.Y()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y; }
            if (m_angularLock.Z()) { flags |= physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z; }

            pDynamic->setRigidDynamicLockFlags(flags);
        }
    }

    void PhysXRigidbody3D::ClearForces() {
        if (auto&& pRigidBody = m_rigidActor->is<physx::PxRigidBody>(); pRigidBody && pRigidBody->getScene()) {
            pRigidBody->clearForce();
            pRigidBody->setLinearVelocity(physx::PxVec3(0, 0, 0));
            pRigidBody->setAngularVelocity(physx::PxVec3(0, 0, 0));
        }
        Rigidbody::ClearForces();
    }

    void PhysXRigidbody3D::Synchronize() {
        auto&& pTransform = GetTransform();
        if (!pTransform) {
            return;
        }

        auto&& globalPose = m_rigidActor->getGlobalPose();

        auto&& rigidbodyTranslation = SR_MATH_NS::FVector3(globalPose.p.x, globalPose.p.y, globalPose.p.z);
        auto&& rigidbodyRotation = SR_MATH_NS::Quaternion(globalPose.q.x, globalPose.q.y, globalPose.q.z, globalPose.q.w);

        if (GetType() == ShapeType::Capsule3D) {
            rigidbodyRotation = rigidbodyRotation.RotateZ(-90);
        }

        /// ------------------------------------------------------------------------------------------------------------

        SR_MATH_NS::FVector3 deltaTranslation(SR_MATH_NS::Unit(0));
        SR_MATH_NS::Quaternion deltaQuaternion(SR_MATH_NS::Quaternion::Identity());

        if (m_rigidbodyTranslation.IsFinite()) {
            deltaTranslation = (rigidbodyTranslation - GetCenterDirection()) - m_rigidbodyTranslation;
        }

        if (m_rigidbodyRotation.IsFinite()) {
            deltaQuaternion = rigidbodyRotation * m_rigidbodyRotation.Inverse();
        }

        if (!deltaTranslation.IsEquals(SR_MATH_NS::FVector3(SR_MATH_NS::Unit(0)), SR_MATH_NS::Unit(0.001))) {
            pTransform->GlobalTranslate(deltaTranslation);
        }

       if (deltaQuaternion != SR_MATH_NS::Quaternion::Identity()) {
           pTransform->SetRotation(rigidbodyRotation);
           // TODO: maybe use? pTransform->Rotate(deltaQuaternion);
       }

        UpdateMatrix(true);

        SetMatrixDirty(false);

        m_rigidbodyTranslation = m_translation;
        m_rigidbodyRotation = m_rotation;

        Rigidbody::Synchronize();
    }
}
