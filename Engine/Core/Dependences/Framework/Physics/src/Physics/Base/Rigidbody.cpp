//
// Created by Monika on 28.07.2022.
//

#include <Physics/Base/Rigidbody.h>

namespace SR_PHYSICS_NS::Types {
    Rigidbody::Rigidbody()
        : SR_UTILS_NS::Component()
    { }

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

        Component::OnAttached();
    }

    void Rigidbody::OnDestroy() {
        Component::OnDestroy();
    }

    void Rigidbody::OnDisabled() {
        Component::OnDisabled();
    }

    void Rigidbody::OnEnabled() {
        Component::OnEnabled();
    }
}
