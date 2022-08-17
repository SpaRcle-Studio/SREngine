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

    void Rigidbody::OnAttached() {
        //btTransform startTransform;
        //startTransform.setIdentity();
        //startTransform.setOrigin(btVector3(0, h, -(s + 3.5)));
//
        //bool isDynamic = (mass != 0.f);
//
        //btVector3 localInertia(0, 0, 0);
        //if (isDynamic)
        //    shape->calculateLocalInertia(mass, localInertia);
//
        //btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//
        //btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);
//
        //btRigidBody* body = new btRigidBody(cInfo);
//
        //body->setUserIndex(-1);
        //m_dynamicsWorld->addRigidBody(body);
        //
        //btRigidBody* body = createRigidBody(1, startTransform, new btBoxShape(btVector3(s, 1, 3)));

        if (auto&& physicsScene = GetPhysicsScene()) {
            InitShape();
            InitBody();

            physicsScene->Register(this);
        }

        Component::OnAttached();
    }

    bool Rigidbody::InitShape() {
        //m_shape = new btBoxShape(btVector3(1, 1, 1));
        m_shape = new btSphereShape(1.f);
        return true;
    }

    bool Rigidbody::InitBody() {
        auto&& pTransform = GetTransform();

        if (!pTransform || !m_shape) {
            return false;
        }


        auto &&matrix = GetTransform()->GetMatrix();

        auto &&rotation = matrix.GetQuat().EulerAngle();
        auto &&translation = matrix.GetTranslate();

        btQuaternion quaternion;
        quaternion.setEulerZYX(rotation.x, rotation.y, rotation.z);

        btVector3 position = btVector3(translation.x, translation.y, translation.z);

        m_motionState = new btDefaultMotionState(btTransform(quaternion, position));

        btVector3 bodyInertia;
        m_shape->calculateLocalInertia((btScalar)m_mass, bodyInertia);

        auto&& bodyCI = btRigidBody::btRigidBodyConstructionInfo((btScalar)m_mass, m_motionState, m_shape, bodyInertia);

        bodyCI.m_restitution = 1.0f;
        bodyCI.m_friction = 0.5f;

        m_rigidbody = new btRigidBody(bodyCI);
        m_rigidbody->setUserPointer((void*)this);
        m_rigidbody->setLinearFactor(btVector3(1,1,0));

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
        m_dirty = true;
        Component::OnMatrixDirty();
    }

    void Rigidbody::UpdateMatrix() {
        if (!m_rigidbody || !m_dirty) {
            return;
        }

        m_dirty = false;

        //auto &&matrix = GetTransform()->GetMatrix();

        //auto &&rotation = matrix.GetQuat().EulerAngle();
        //rotation = rotation.Radians();

        //auto &&translation = matrix.GetTranslate();

        //btQuaternion quaternion;
        //quaternion.setEulerZYX(rotation.x, rotation.y, rotation.z);

        //btTransform initialTransform;

        //initialTransform.setOrigin(btVector3(translation.x, translation.y, translation.z));
        //initialTransform.setRotation(quaternion);

        //m_rigidbody->setWorldTransform(initialTransform);
        //m_motionState->setWorldTransform(initialTransform);

        //m_rigidbody->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
        //m_rigidbody->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
        //m_rigidbody->clearForces();
    }
}
