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
        return true;
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

        auto&& pActor = (physx::PxActor*)(pRigidbody->GetHandle());
        m_scene->addActor(*pActor);

        return true;
    }

    bool PhysXPhysicsWorld::RemoveRigidbody(PhysicsWorld::RigidbodyPtr pRigidbody) {
        if (!pRigidbody) {
            SRHalt("pRigidbody is nullptr!");
            return false;
        }

        auto&& pActor = (physx::PxActor*)(pRigidbody->GetHandle());
        m_scene->removeActor(*pActor);

        return true;
    }
}
