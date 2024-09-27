//
// Created by Monika on 24.11.2022.
//

#include <Physics/PhysX/PhysXPhysicsWorld.h>
#include <Physics/PhysX/PhysXLibraryImpl.h>
#include <Physics/PhysX/PhysXSimulationCallback.h>
#include <Physics/PhysX/PhysXRaycast3DImpl.h>

namespace SR_PHYSICS_NS {
    physx::PxFilterFlags contactReportFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
                                                   physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
                                                   physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
    {
        PX_UNUSED(attributes0);
        PX_UNUSED(attributes1);
        PX_UNUSED(filterData0);
        PX_UNUSED(filterData1);
        PX_UNUSED(constantBlockSize);
        PX_UNUSED(constantBlock);


        pairFlags = physx::PxPairFlag::eSOLVE_CONTACT | physx::PxPairFlag::eDETECT_DISCRETE_CONTACT
                    | physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
                    | physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS
                    | physx::PxPairFlag::eNOTIFY_CONTACT_POINTS
                    | physx::PxPairFlag::eNOTIFY_TOUCH_LOST;
        return physx::PxFilterFlag::eDEFAULT;
    }

    PhysXPhysicsWorld::PhysXPhysicsWorld(Super::LibraryPtr pLibrary, Space space)
        : Super(pLibrary, space)
    {
        m_contactCallback = new ContactReportCallback();
    }

    PhysXPhysicsWorld::~PhysXPhysicsWorld() {
        if (m_scene) {
            m_scene->release();
            m_scene = nullptr;
        }

        if (m_cpuDispatcher) {
            m_cpuDispatcher->release();
            m_cpuDispatcher = nullptr;
        }
        if (m_contactCallback) {
            delete m_contactCallback;
            m_contactCallback = nullptr;
        }
    }

    bool PhysXPhysicsWorld::Initialize() {
        SR_TRACY_ZONE;

        auto&& pPhysics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        m_raycast3dImpl = new PhysXRaycast3DImpl(this);

        physx::PxSceneDesc sceneDesc(pPhysics->getTolerancesScale());

        sceneDesc.kineKineFilteringMode = physx::PxPairFilteringMode::eKEEP;
        sceneDesc.staticKineFilteringMode = physx::PxPairFilteringMode::eKEEP;

        sceneDesc.filterShader	= contactReportFilterShader;
        sceneDesc.simulationEventCallback = m_contactCallback;

        if (!sceneDesc.cpuDispatcher) {
            m_cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(1);
            sceneDesc.cpuDispatcher = m_cpuDispatcher;
        }

        if(!sceneDesc.filterShader) {
            sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
        }

        m_scene = pPhysics->createScene(sceneDesc);

        m_scene->setSimulationEventCallback(m_contactCallback);

        if (!m_scene) {
            SR_ERROR("PhysXPhysicsWorld::Initialize() : failed to create scene!");
            return false;
        }

        m_scene->setGravity(physx::PxVec3(0.f, -SR_GRAV_CONST, 0.f));

        physx::PxPvdSceneClient* pPvdClient = m_scene->getScenePvdClient();
        
        if (pPvdClient) {
            pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
            pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
            pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
        }

        return true;
    }

    bool PhysXPhysicsWorld::ClearForces() {
        SR_TRACY_ZONE;
        return PhysicsWorld::ClearForces();
    }

    bool PhysXPhysicsWorld::Synchronize() {
        SR_TRACY_ZONE;
        return SynchronizeDynamic() && SynchronizeStatic();
    }

    bool PhysXPhysicsWorld::StepSimulation(float_t step) {
        SR_TRACY_ZONE;

        if (!m_scene) {
            return false;
        }

        m_scene->simulate(step);

        if (!m_scene->fetchResults(true)) {
            SR_ERROR("PhysXPhysicsWorld::StepSimulation() : failed to fetch results!");
            return false;
        }

        return true;
    }

    bool PhysXPhysicsWorld::AddRigidbody(PhysicsWorld::RigidbodyPtr pRigidbody) {
        if (!pRigidbody) {
            SRHalt("pRigidbody is nullptr!");
            return false;
        }

        if (pRigidbody->IsBodyDirty()) {
            pRigidbody->InitBody();
        }

        if (auto&& pActor = (physx::PxActor*)(pRigidbody->GetHandle())) {
            m_scene->addActor(*pActor);
        }

        return true;
    }

    bool PhysXPhysicsWorld::RemoveRigidbody(PhysicsWorld::RigidbodyPtr pRigidbody) {
        if (!pRigidbody) {
            SRHalt("pRigidbody is nullptr!");
            return false;
        }

        if (auto&& pActor = (physx::PxActor*)(pRigidbody->GetHandle())) {
            m_scene->removeActor(*pActor);
        }

        return true;
    }

    void PhysXPhysicsWorld::Flush() {
        SR_TRACY_ZONE;

        m_scene->flushSimulation();
        PhysicsWorld::Flush();
    }

    bool PhysXPhysicsWorld::SynchronizeStatic() {
        SR_TRACY_ZONE;

        const uint32_t count = m_scene->getNbActors(physx::PxActorTypeFlag::Enum::eRIGID_STATIC);
        if (count == 0) {
            return true;
        }

        if (m_staticActors.size() < count) {
            m_staticActors.resize(count);
        }

        auto&& pActors = m_staticActors.data();
        m_scene->getActors(physx::PxActorTypeFlag::Enum::eRIGID_STATIC, pActors, count);

        for (uint32_t i = 0; i < count; ++i) {
            auto&& pRigidActor = pActors[i]->is<physx::PxRigidActor>();
            if (!SRVerifyFalse(!pRigidActor)) {
                continue;
            }

            auto&& pRigidbody = (SR_PTYPES_NS::Rigidbody*)pRigidActor->userData;
            if (!SRVerifyFalse(!pRigidbody)) {
                continue;
            }

            if (pRigidbody->IsBodyDirty()) {
                SRVerifyFalse(!ReAddRigidbody(pRigidbody));
                continue;
            }

            if (pRigidbody->UpdateShape() == RBUpdShapeRes::Error) {
                SR_ERROR("PhysXPhysicsWorld::Synchronize() : failed to update shape!");
                continue;
            }

            if (pRigidbody->IsMatrixDirty()) {
                pRigidbody->UpdateMatrix();
            }
        }

        return true;
    }

    bool PhysXPhysicsWorld::SynchronizeDynamic() {
        SR_TRACY_ZONE;

        const uint32_t count = m_scene->getNbActors(physx::PxActorTypeFlag::Enum::eRIGID_DYNAMIC);
        if (count == 0) {
            return true;
        }

        if (m_dynamicActors.size() < count) {
            m_dynamicActors.resize(count);
        }

        auto&& pActors = m_dynamicActors.data();
        m_scene->getActors(physx::PxActorTypeFlag::Enum::eRIGID_DYNAMIC, pActors, count);

        for (uint32_t i = 0; i < count; ++i) {
            auto&& pRigidActor = pActors[i]->is<physx::PxRigidActor>();
            if (!SRVerifyFalse(!pRigidActor)) {
                continue;
            }

            auto&& pRigidbody = (SR_PTYPES_NS::Rigidbody*)pRigidActor->userData;
            if (!SRVerifyFalse(!pRigidbody)) {
                continue;
            }

            if (pRigidbody->IsBodyDirty()) {
                SRVerifyFalse(!ReAddRigidbody(pRigidbody));
                continue;
            }

            if (pRigidbody->UpdateShape() == RBUpdShapeRes::Error) {
                SR_ERROR("PhysXPhysicsWorld::Synchronize() : failed to update shape!");
                continue;
            }

            pRigidbody->Synchronize();
        }

        return true;
    }

    void PhysXPhysicsWorld::ForEachRigidbody3D(const SR_HTYPES_NS::Function<void(SR_PTYPES_NS::Rigidbody3D *)> &fun) {
        static const physx::PxActorTypeFlags flags =
                physx::PxActorTypeFlag::Enum::eRIGID_DYNAMIC |
                physx::PxActorTypeFlag::Enum::eRIGID_STATIC;

        const uint32_t count = m_scene->getNbActors(flags);
        if (count == 0) {
            return;
        }

        if (m_actors.size() < count) {
            m_actors.resize(count);
        }

        auto&& pActors = m_actors.data();
        m_scene->getActors(flags, pActors, count);

        for (uint32_t i = 0; i < count; ++i) {
            auto&& pRigidActor = pActors[i]->is<physx::PxRigidActor>();
            if (!SRVerifyFalse(!pRigidActor)) {
                continue;
            }

            auto&& pRigidbody = dynamic_cast<SR_PTYPES_NS::Rigidbody3D*>((SR_PTYPES_NS::Rigidbody*)pRigidActor->userData);
            fun(pRigidbody);
        }
    }
}
