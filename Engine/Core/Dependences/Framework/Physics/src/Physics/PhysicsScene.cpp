//
// Created by Monika on 28.07.2022.
//

#include <Physics/PhysicsScene.h>
#include <Utils/Math/Mathematics.h>
#include <Utils/World/Scene.h>

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

        return true;
    }

    void PhysicsScene::Update(float_t dt) {
        //m_dynamicsWorld->stepSimulation(dt);

        uint32_t numCollisionObjects = m_dynamicsWorld->getNumCollisionObjects();
        for (uint32_t i = 0; i < numCollisionObjects; ++i) {
            btCollisionObject* colObj = m_dynamicsWorld->getCollisionObjectArray()[i];
            btCollisionShape* collisionShape = colObj->getCollisionShape();

            btVector3 pos = colObj->getWorldTransform().getOrigin();
            btQuaternion orn = colObj->getWorldTransform().getRotation();
            btVector3 euler;
            orn.getEulerZYX(euler[0], euler[1], euler[2]);

            auto&& pRigidbody = (RigidbodyPtr)colObj->getUserPointer();

            if (!pRigidbody) {
                continue;
            }

            auto&& pTransform = pRigidbody->GetTransform();

            if (!pTransform) {
                continue;
            }

            pRigidbody->UpdateMatrix();

            pTransform->SetTranslation(pos.x(), pos.y(), pos.z());
            pTransform->SetRotation(SR_MATH_NS::FVector3(euler.x(), euler.y(), euler.z()).Degrees());

            pRigidbody->m_dirty = false;
        }
    }

    void PhysicsScene::Register(PhysicsScene::RigidbodyPtr pRigidbody) {
        m_dynamicsWorld->addRigidBody(pRigidbody->m_rigidbody);

        auto&& shape = new btBoxShape(btVector3(5, 1, 5));
        auto&& collider = new btCollisionObject();
        collider->setCollisionShape(shape);

        m_dynamicsWorld->addCollisionObject(collider);
    }
}