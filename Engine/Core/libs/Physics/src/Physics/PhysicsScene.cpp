//
// Created by Monika on 28.07.2022.
//

#include <Utils/Math/Mathematics.h>
#include <Utils/World/Scene.h>

#include <Physics/PhysicsScene.h>

namespace SR_PHYSICS_NS {
    PhysicsScene::PhysicsScene(const ScenePtr& scene)
        : Super(this)
        , m_scene(scene)
    {
        Init();
    }

    PhysicsScene::~PhysicsScene() {
        SR_SAFE_DELETE_PTR(m_dynamicsWorld);
        SR_SAFE_DELETE_PTR(m_solver);
        SR_SAFE_DELETE_PTR(m_broadphase);
        SR_SAFE_DELETE_PTR(m_dispatcher);
        SR_SAFE_DELETE_PTR(m_collisionConfiguration);
    }

    bool PhysicsScene::Init() {
        SR_INFO("PhysicsScene::Init() : initializing the physics scene...");

        if (m_scene.RecursiveLockIfValid()) {
            auto&& dataStorage = m_scene->GetDataStorage();

            if (dataStorage.GetValueDef<Ptr>(Ptr())) {
                SR_ERROR("PhysicsScene::Init() : render scene is already exists!");
                m_scene.Unlock();
                return false;
            }

            dataStorage.SetValue<Ptr>(GetThis());

            m_scene.Unlock();
        }
        else {
            SR_ERROR("PhysicsScene::Init() : scene is invalid!");
        }

        if (!CreateDynamicWorld()) {
            SR_ERROR("PhysicsScene::Init() : failed to create dynamic world!");
            return false;
        }

        m_dynamicsWorld->stepSimulation(1.f / 60.f);

        return true;
    }

    bool PhysicsScene::CreateDynamicWorld() {
        ///collision configuration contains default setup for memory, collision setup
        m_collisionConfiguration = new btDefaultCollisionConfiguration();

        //m_collisionConfiguration->setConvexConvexMultipointIterations();

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

        m_broadphase = new btDbvtBroadphase();

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        m_solver = new btSequentialImpulseConstraintSolver();

        m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

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

    void PhysicsScene::FixedUpdate() {
        if (m_needClearForces) {
            m_dynamicsWorld->clearForces();
            m_needClearForces = false;
        }

        m_dynamicsWorld->stepSimulation(1.f / 60.f);

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

            if (pRigidbody->m_dirty) {
                pRigidbody->UpdateShape();
                pRigidbody->UpdateMatrix();
            }
            else if (auto&& pTransform = pRigidbody->GetTransform()) {
                btVector3 pos = trans.getOrigin();
                btQuaternion orn = trans.getRotation();

                pTransform->SetTranslation(SR_MATH_NS::FVector3(pos.x(), pos.y(), pos.z()) - pRigidbody->GetCenterDirection());
                pTransform->SetRotation(SR_MATH_NS::Quaternion(orn.x(), orn.y(), orn.z(), orn.w()));

                pRigidbody->m_dirty = false;
            }
        }
    }

    void PhysicsScene::Register(PhysicsScene::RigidbodyPtr pRigidbody) {
        m_dynamicsWorld->addRigidBody(pRigidbody->m_rigidbody);
    }

    void PhysicsScene::Remove(PhysicsScene::RigidbodyPtr pRigidbody) {
        m_dynamicsWorld->removeRigidBody(pRigidbody->m_rigidbody);
        delete pRigidbody;
    }

    void PhysicsScene::ClearForces() {
        m_needClearForces = true;
    }
}