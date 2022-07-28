//
// Created by Monika on 28.07.2022.
//

#include <Physics/PhysicsScene.h>
#include <Utils/Math/Mathematics.h>

namespace SR_PHYSICS_NS {
    PhysicsScene::PhysicsScene()
        : Super(this)
    { }

    PhysicsScene::~PhysicsScene() {

    }

    bool PhysicsScene::Init() {
        SR_INFO("PhysicsScene::Init() : initializing the physics scene...");

        if (!CreateDynamicWorld()) {
            SR_ERROR("PhysicsScene::Init() : failed to create dynamic world!");
            return false;
        }

        m_dynamicsWorld->stepSimulation(1.f / 60.f);

        return true;
    }

    void PhysicsScene::Close() {
        SR_SAFE_DELETE_PTR(m_dynamicsWorld);
        SR_SAFE_DELETE_PTR(m_solver);
        SR_SAFE_DELETE_PTR(m_broadphase);
        SR_SAFE_DELETE_PTR(m_dispatcher);
        SR_SAFE_DELETE_PTR(m_collisionConfiguration);
    }

    bool PhysicsScene::CreateDynamicWorld() {
        ///collision configuration contains default setup for memory, collision setup
        m_collisionConfiguration = new btDefaultCollisionConfiguration();
        //m_collisionConfiguration->setConvexConvexMultipointIterations();

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

        m_broadphase = new btDbvtBroadphase();

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
        m_solver = sol;

        m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

        m_dynamicsWorld->setGravity(btVector3(0, SR_EARTH_GRAVITY, 0));

        return true;
    }
}