//
// Created by Monika on 22.11.2022.
//

#include <Physics/Bullet3/Bullet3PhysicsWorld.h>

namespace SR_PHYSICS_NS {
    Bullet3PhysicsWorld::Bullet3PhysicsWorld(PhysicsWorld::LibraryPtr pLibrary, Space space)
        : Super(pLibrary, space)
    { }

    Bullet3PhysicsWorld::~Bullet3PhysicsWorld() {
        SR_SAFE_DELETE_PTR(m_dynamicsWorld);
        SR_SAFE_DELETE_PTR(m_solver);
        SR_SAFE_DELETE_PTR(m_broadPhase);
        SR_SAFE_DELETE_PTR(m_dispatcher);
        SR_SAFE_DELETE_PTR(m_collisionConfiguration);
    }

    bool Bullet3PhysicsWorld::Initialize() {
        ///collision configuration contains default setup for memory, collision setup
        m_collisionConfiguration = new btDefaultCollisionConfiguration();

        //m_collisionConfiguration->setConvexConvexMultipointIterations();

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

        m_broadPhase = new btDbvtBroadphase();

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        m_solver = new btSequentialImpulseConstraintSolver();

        m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadPhase, m_solver, m_collisionConfiguration);

        m_dynamicsWorld->setGravity(btVector3(0, -SR_EARTH_GRAVITY, 0));

        m_dynamicsWorld->getSolverInfo().m_deformable_erp = 0.1;
        m_dynamicsWorld->getSolverInfo().m_deformable_maxErrorReduction = btScalar(20);
        m_dynamicsWorld->getSolverInfo().m_leastSquaresResidualThreshold = 1e-3;
        m_dynamicsWorld->getSolverInfo().m_splitImpulse = true;
        m_dynamicsWorld->getSolverInfo().m_numIterations = 100;

        // m_dynamicsWorld->getDispatchInfo().m_enableSPU = true;

        m_dynamicsWorld->setInternalTickCallback([](btDynamicsWorld *pWorld, btScalar timeStep) {
            //std::cout << pWorld->getDispatcher()->getNumManifolds() << std::endl;
        });

        return true;
    }

    bool Bullet3PhysicsWorld::ClearForces() {
        m_dynamicsWorld->clearForces();
        return true;
    }

    bool Bullet3PhysicsWorld::Synchronize() {
        const int32_t numManifolds = m_dispatcher->getNumManifolds();
        for (int32_t i = 0; i < numManifolds; ++i) {
            const btPersistentManifold* contactManifold = m_dispatcher->getManifoldByIndexInternal(i);

            if (contactManifold->getNumContacts() > 0)
            {
                /// Activate triggers here
            }
            else
            {
                /// Deactivate trigger here
            }
        }

        uint32_t numCollisionObjects = m_dynamicsWorld->getNumCollisionObjects();
        for (uint32_t i = 0; i < numCollisionObjects; ++i) {
            btCollisionObject* colObj = m_dynamicsWorld->getCollisionObjectArray()[i];
            /// btCollisionShape* collisionShape = colObj->getCollisionShape();

            btRigidBody* body = btRigidBody::upcast(colObj);
            btTransform trans;
            if (body && body->getMotionState()) {
                body->getMotionState()->getWorldTransform(trans);
            }
            else {
                trans = colObj->getWorldTransform();
            }

            auto&& pRigidbody = (RigidbodyPtr)colObj->getUserPointer();

            if (!pRigidbody) {
                continue;
            }

            if (pRigidbody->UpdateShape() == RBUpdShapeRes::Error) {
                SR_ERROR("Bullet3PhysicsWorld::Synchronize() : failed to update shape!");
                continue;
            }

            if (pRigidbody->IsMatrixDirty()) {
                pRigidbody->UpdateMatrix();
            }
            else if (auto&& pTransform = pRigidbody->GetTransform()) {
                btVector3 pos = trans.getOrigin();
                btQuaternion orn = trans.getRotation();

                pTransform->SetTranslation(SR_MATH_NS::FVector3(pos.x(), pos.y(), pos.z()) - pRigidbody->GetCenterDirection());
                pTransform->SetRotation(SR_MATH_NS::Quaternion(orn.x(), orn.y(), orn.z(), orn.w()));

                pRigidbody->SetMatrixDirty(false);
            }
        }

        return true;
    }

    bool Bullet3PhysicsWorld::AddRigidbody(PhysicsWorld::RigidbodyPtr pRigidbody) {
        if (auto&& pHandle = pRigidbody->GetHandle()) {
            m_dynamicsWorld->addRigidBody((btRigidBody*)pHandle);
            return true;
        }

        SRHalt("pHandle is nullptr!");
        return false;
    }

    bool Bullet3PhysicsWorld::RemoveRigidbody(PhysicsWorld::RigidbodyPtr pRigidbody) {
        if (auto&& pHandle = pRigidbody->GetHandle()) {
            m_dynamicsWorld->removeRigidBody((btRigidBody *)pHandle);
            return true;
        }

        SRHalt("pHandle is nullptr!");
        return false;
    }

    bool Bullet3PhysicsWorld::StepSimulation(float_t step) {
        m_dynamicsWorld->stepSimulation(step);
        return true;
    }
}