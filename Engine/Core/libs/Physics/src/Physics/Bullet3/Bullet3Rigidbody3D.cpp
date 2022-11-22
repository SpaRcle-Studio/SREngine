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

    void Bullet3Rigidbody3D::SetMass(float_t mass) {
        Super::SetMass(mass);

        if (m_rigidbody) {
            auto&& inertia = m_shape ? m_shape->CalculateLocalInertia(m_mass) : SR_MATH_NS::FVector3(0, 0, 0);
            m_rigidbody->setMassProps(m_mass, SR_PHYSICS_UTILS_NS::FV3ToBtV3(inertia));
        }
    }

    bool Bullet3Rigidbody3D::InitBody() {
        if (!Super::InitBody()) {
            return false;
        }

        auto&& localInertia = m_shape->CalculateLocalInertia(m_mass);

        btTransform startTransform;
        startTransform.setIdentity();

        SRAssert2(!m_motionState && !m_rigidbody, "Rigidbody is already initialized!");

        m_motionState = new btDefaultMotionState(startTransform);

        m_dirty = true;

        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                m_mass,        /// mass, in kg. 0 -> Static object, will never move.
                m_motionState,
                (btCollisionShape*)m_shape->GetHandle(), /// collision shape of body
                SR_PHYSICS_UTILS_NS::FV3ToBtV3(localInertia)   /// local inertia
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
    }

    void Bullet3Rigidbody3D::AddGlobalVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (m_rigidbody) {
            m_rigidbody->setLinearVelocity(m_rigidbody->getLinearVelocity() + SR_PHYSICS_UTILS_NS::FV3ToBtV3(velocity));
        }
    }

    void Bullet3Rigidbody3D::SetVelocity(const SR_MATH_NS::FVector3& velocity) {
        if (m_rigidbody) {
            m_rigidbody->setLinearVelocity(SR_PHYSICS_UTILS_NS::FV3ToBtV3(velocity));
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

    bool Bullet3Rigidbody3D::UpdateShape() {
        if (!m_shape || m_shape->GetType() != m_type) {
            SR_SAFE_DELETE_PTR(m_shape)

            if (!m_library->IsShapeSupported(m_type)) {
                m_type = m_library->GetDefaultShape();
            }

            m_shape = m_library->CreateCollisionShape(m_type);

            if (!m_shape || !m_shape->Update()) {
                SRHalt("Failed to update shape or shape is nullptr!");
                return false;
            }

            if (m_rigidbody) {
                m_rigidbody->setCollisionShape(static_cast<btCollisionShape*>(m_shape->GetHandle()));
            }
        }

        UpdateDebugShape();

        return true;
    }

    void* Bullet3Rigidbody3D::GetHandle() const noexcept {
        return (void*)m_rigidbody;
    }
}