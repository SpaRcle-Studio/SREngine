//
// Created by Monika on 21.03.2021.
//

#include "Core/PhysEngine.h"
#include <Debug.h>

bool Framework::Physics::PhysEngine::Create() {
    Helper::Debug::Info("PhysEngine::Create() : create physics engine...");

    this->m_collisionConf = new btDefaultCollisionConfiguration();
    this->m_dispatcher = new btCollisionDispatcher(m_collisionConf);

    this->m_overlappingPairCache = new btDbvtBroadphase();

    this->m_solver = new btSequentialImpulseConstraintSolver;

    this->m_dynamicWorld = new btDiscreteDynamicsWorld(
            m_dispatcher,
            m_overlappingPairCache,
            m_solver,
            m_collisionConf
        );

    // default gravity
    this->m_dynamicWorld->setGravity(btVector3(0, -10, 0));

    /*
    btMotionState* state = new btDefaultMotionState(btTransform(
            btQuaternion(), // rotation
            btVector3()     // position
        ));

    btCollisionShape* shape = new btBoxShape(btVector3(1,1,1));

    btRigidBody* rigidbody = new btRigidBody(1.f, state, shape);*/

    return true;
}

bool Framework::Physics::PhysEngine::SetGravity(float x, float y, float z) {
    if (!m_isCreate || !m_dynamicWorld)
        return false;

    this->m_dynamicWorld->setGravity(btVector3(x, y, z));

    return true;
}
