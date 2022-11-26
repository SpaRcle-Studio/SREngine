//
// Created by Monika on 22.11.2022.
//

#include <Physics/Bullet3/Bullet3Rigidbody3D.h>
#include <Physics/Bullet3/Bullet3PhysicsLib.h>

namespace SR_PTYPES_NS {
    Bullet3Rigidbody3D::Bullet3Rigidbody3D(Rigidbody::LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    Bullet3Rigidbody3D::~Bullet3Rigidbody3D() {
        SRAssert2(!m_motionState && !m_rigidbody, "Not all data deleted!");
    }

    void Bullet3Rigidbody3D::UpdateInertia() {
        if (m_rigidbody) {
            auto&& inertia = m_shape ? m_shape->CalculateLocalInertia(m_mass) : SR_MATH_NS::FVector3(0, 0, 0);
            m_rigidbody->setMassProps(m_mass, SR_PHYSICS_UTILS_NS::FV3ToBtV3(inertia));
        }
    }

    bool Bullet3Rigidbody3D::InitBody() {
        if (!Super::InitBody()) {
            SR_ERROR("Bullet3Rigidbody3D::InitBody() : failed to init base body!");
            return false;
        }

        btTransform startTransform;
        startTransform.setIdentity();

        SRAssert2(!m_motionState && !m_rigidbody, "Rigidbody is already initialized!");

        m_motionState = new btDefaultMotionState(startTransform);

        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                m_mass,        /// mass, in kg. 0 -> Static object, will never move.
                m_motionState,
                (btCollisionShape*)m_shape->GetHandle(), /// collision shape of body
                btVector3()   /// local inertia
        );
        m_rigidbody = new btRigidBody(rigidBodyCI);

        m_rigidbody->setActivationState(DISABLE_DEACTIVATION);

        m_rigidbody->setUserPointer(this);

        return true;
    }

    void Bullet3Rigidbody3D::AddLocalVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (m_rigidbody) {
            m_rigidbody->setLinearVelocity(m_rigidbody->getLinearVelocity() + SR_PHYSICS_UTILS_NS::FV3ToBtV3(m_rotation * velocity));
        }
        else {
            SRHalt("m_rigidbody is nullptr!");
        }
    }

    void Bullet3Rigidbody3D::AddGlobalVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (m_rigidbody) {
            m_rigidbody->setLinearVelocity(m_rigidbody->getLinearVelocity() + SR_PHYSICS_UTILS_NS::FV3ToBtV3(velocity));
        }
        else {
            SRHalt("m_rigidbody is nullptr!");
        }
    }

    void Bullet3Rigidbody3D::SetVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (m_rigidbody) {
            m_rigidbody->setLinearVelocity(SR_PHYSICS_UTILS_NS::FV3ToBtV3(velocity));
        }
        else {
            SRHalt("m_rigidbody is nullptr!");
        }
    }

    void Bullet3Rigidbody3D::DeInitBody() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            if (m_rigidbody) {
                physicsScene->Remove(this);
            }
        }
        else {
            SRHalt("Failed to get physics scene!");
        }

        SR_SAFE_DELETE_PTR(m_motionState);
        SR_SAFE_DELETE_PTR(m_rigidbody);

        Super::DeInitBody();
    }

    bool Bullet3Rigidbody3D::UpdateMatrix() {
        if (!Super::UpdateMatrix()) {
            return false;
        }

        auto&& translation = m_translation + GetCenterDirection();

        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(translation.x, translation.y, translation.z));
        startTransform.setRotation(btQuaternion(m_rotation.X(), m_rotation.Y(), m_rotation.Z(), m_rotation.W()));

        m_rigidbody->setWorldTransform(startTransform);

        if (m_rigidbody->getMotionState()) {
            m_rigidbody->getMotionState()->setWorldTransform(startTransform);
        }

        m_rigidbody->clearForces();
        m_rigidbody->setAngularVelocity(btVector3(0, 0, 0));
        m_rigidbody->setLinearVelocity(btVector3(0, 0, 0));

        return true;
    }

    bool Bullet3Rigidbody3D::UpdateShapeInternal() {
        if (!m_rigidbody) {
            SR_ERROR("Bullet3Rigidbody3D::UpdateShapeInternal() : rigidbody is nullptr!");
            return false;
        }

        m_rigidbody->setCollisionShape(static_cast<btCollisionShape*>(m_shape->GetHandle()));

        return true;
    }

    void* Bullet3Rigidbody3D::GetHandle() const noexcept {
        return (void*)m_rigidbody;
    }
}