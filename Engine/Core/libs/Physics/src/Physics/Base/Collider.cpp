//
// Created by Monika on 16.08.2022.
//

#include <Physics/Base/Collider.h>
#include <Physics/PhysicsScene.h>
#include <Utils/World/Scene.h>

namespace SR_PHYSICS_NS::Types {
    Collider::~Collider() {
        SR_SAFE_DELETE_PTR(m_shape);
        SR_SAFE_DELETE_PTR(m_motionState);
        SR_SAFE_DELETE_PTR(m_rigidbody);
    }

    void Collider::OnAttached() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            auto &&matrix = GetTransform()->GetMatrix();

            auto &&translation = matrix.GetTranslate();
            auto &&rotation = matrix.GetQuat();

            /// init transformation

            /*

            /// init rigidbody

            m_shape = new btBoxShape(btVector3(5, 1, 5));
            m_collider = new btCollisionObject();

            //m_collider->setWorldTransform(startTransform);
            m_collider->setCollisionShape(m_shape);
            ///m_collider->setUserPointer(this);*/

            m_shape = new btBoxShape(btVector3(btScalar(100.), btScalar(1.), btScalar(100.)));

            m_motionState = new btDefaultMotionState(btTransform::getIdentity());
            btRigidBody::btRigidBodyConstructionInfo rbInfo(0.f, m_motionState, m_shape, btVector3(0, 0, 0));
            m_rigidbody = new btRigidBody(rbInfo);

            m_rigidbody->setActivationState(DISABLE_DEACTIVATION);

            physicsScene->Register(this);
        }

        Component::OnAttached();
    }

    void Collider::OnMatrixDirty() {
        auto &&matrix = GetTransform()->GetMatrix();

        auto &&translation = matrix.GetTranslate();
        auto &&rotation = matrix.GetQuat();

        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(translation.x, translation.y, translation.z));
        startTransform.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

        m_rigidbody->setWorldTransform(startTransform);

        if (m_rigidbody->getMotionState()) {
            m_rigidbody->getMotionState()->setWorldTransform(startTransform);
        }

        m_rigidbody->clearForces();
        m_rigidbody->setAngularVelocity(btVector3(0, 0, 0));
        m_rigidbody->setLinearVelocity(btVector3(0, 0, 0));

        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->ClearForces();
        }

        Component::OnMatrixDirty();
    }

    Collider::PhysicsScenePtr Collider::GetPhysicsScene() {
        if (!m_physicsScene.Valid()) {
            m_physicsScene = GetScene().Do<PhysicsScenePtr>([](SR_WORLD_NS::Scene* ptr) {
                return ptr->GetDataStorage().GetValue<PhysicsScenePtr>();
            }, PhysicsScenePtr());
        }

        return m_physicsScene;
    }

    void Collider::OnDestroy() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->Remove(this);
        }

        Component::OnDestroy();
    }
}