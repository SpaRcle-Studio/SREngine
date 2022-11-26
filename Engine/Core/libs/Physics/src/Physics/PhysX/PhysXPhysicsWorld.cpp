//
// Created by Monika on 24.11.2022.
//

#include <Physics/PhysX/PhysXPhysicsWorld.h>
#include <Physics/PhysX/PhysXLibraryImpl.h>

namespace SR_PHYSICS_NS {
    PhysXPhysicsWorld::PhysXPhysicsWorld(Super::LibraryPtr pLibrary, Space space)
        : Super(pLibrary, space)
    { }

    PhysXPhysicsWorld::~PhysXPhysicsWorld() {
        if (m_scene) {
            m_scene->release();
            m_scene = nullptr;
        }

        if (m_cpuDispatcher) {
            m_cpuDispatcher->release();
            m_cpuDispatcher = nullptr;
        }
    }

    bool PhysXPhysicsWorld::Initialize() {
        auto&& pPhysics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        physx::PxSceneDesc sceneDesc(pPhysics->getTolerancesScale());

        if (!sceneDesc.cpuDispatcher) {
            m_cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(1);
            sceneDesc.cpuDispatcher = m_cpuDispatcher;
        }

        if(!sceneDesc.filterShader) {
            sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
        }

        m_scene = pPhysics->createScene(sceneDesc);

        if (!m_scene) {
            SR_ERROR("PhysXPhysicsWorld::Initialize() : failed to create scene!");
            return false;
        }

        m_scene->setGravity(physx::PxVec3(0.f, -SR_EARTH_GRAVITY, 0.f));

        return true;
    }

    bool PhysXPhysicsWorld::ClearForces() {
        return PhysicsWorld::ClearForces();
    }

    bool PhysXPhysicsWorld::Synchronize() {
        return SynchronizeDynamic() && SynchronizeStatic();
    }

    bool PhysXPhysicsWorld::StepSimulation(float_t step) {
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

    bool PhysXPhysicsWorld::SynchronizeStatic() {
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

            if (pRigidbody->IsShapeDirty() && pRigidbody->UpdateShape() == RBUpdShapeRes::Error) {
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

            if (pRigidbody->IsShapeDirty() && pRigidbody->UpdateShape() == RBUpdShapeRes::Error) {
                SR_ERROR("PhysXPhysicsWorld::Synchronize() : failed to update shape!");
                continue;
            }

            if (pRigidbody->IsMatrixDirty()) {
                pRigidbody->UpdateMatrix();
            }
            else if (auto&& pTransform = pRigidbody->GetTransform()) {
                auto&& globalPose = pRigidActor->getGlobalPose();

                pTransform->SetTranslation(globalPose.p.x, globalPose.p.y, globalPose.p.z);

                pTransform->SetRotation(SR_MATH_NS::Quaternion(
                        globalPose.q.x,
                        globalPose.q.y,
                        globalPose.q.z,
                        globalPose.q.w)
                );

                pRigidbody->SetMatrixDirty(false);
            }
        }

        return true;
    }
}
