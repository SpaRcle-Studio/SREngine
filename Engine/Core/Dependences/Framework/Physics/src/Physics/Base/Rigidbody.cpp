//
// Created by Monika on 28.07.2022.
//

#include <Physics/Base/Rigidbody.h>
#include <Physics/PhysicsScene.h>
#include <Utils/ECS/Transform.h>
#include <Utils/World/Scene.h>

namespace SR_PHYSICS_NS::Types {
    Rigidbody::Rigidbody()
        : SR_UTILS_NS::Component()
    { }

    Rigidbody::~Rigidbody() {
        SR_SAFE_DELETE_PTR(m_motionState);
        SR_SAFE_DELETE_PTR(m_rigidbody);
        SR_SAFE_DELETE_PTR(m_shape);
    }

    void Rigidbody::OnDestroy() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            physicsScene->Remove(this);
        }

        Component::OnDestroy();
    }

    void Rigidbody::OnAttached() {
        if (auto&& physicsScene = GetPhysicsScene()) {
            InitShape();
            InitBody();

            physicsScene->Register(this);
        }

        Component::OnAttached();
    }

    bool Rigidbody::InitShape() {
        m_shape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
        return true;
    }

    bool Rigidbody::InitBody() {
        auto&& pTransform = GetTransform();

        if (!pTransform) {
            return false;
        }

        auto &&matrix = GetTransform()->GetMatrix();

        auto &&rotation = matrix.GetQuat();
        auto &&translation = matrix.GetTranslate();

        btScalar mass(1.f);

        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            m_shape->calculateLocalInertia(mass, localInertia);

        btTransform startTransform;
        startTransform.setIdentity();

        m_motionState = new btDefaultMotionState(startTransform);

        m_dirty = true;

        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                mass,               // mass, in kg. 0 -> Static object, will never move.
                m_motionState,
                m_shape,            // collision shape of body
                localInertia        // local inertia
        );
        m_rigidbody = new btRigidBody(rigidBodyCI);

        m_rigidbody->setActivationState(DISABLE_DEACTIVATION);

        m_rigidbody->setUserPointer(this);

        return true;
    }

    Rigidbody::PhysicsScenePtr Rigidbody::GetPhysicsScene() {
        if (!m_physicsScene.Valid()) {
            m_physicsScene = GetScene().Do<PhysicsScenePtr>([](SR_WORLD_NS::Scene* ptr) {
                return ptr->GetDataStorage().GetValue<PhysicsScenePtr>();
            }, PhysicsScenePtr());
        }

        return m_physicsScene;
    }

    void Rigidbody::OnMatrixDirty() {
        m_matrix = GetTransform()->GetMatrix();
        m_dirty = true;
        Component::OnMatrixDirty();
    }

    void Rigidbody::UpdateMatrix() {
        if (!m_rigidbody || !m_dirty) {
            return;
        }

        m_dirty = false;

        auto &&translation = m_matrix.GetTranslate();
        auto &&rotation = m_matrix.GetQuat();

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
    }
}
