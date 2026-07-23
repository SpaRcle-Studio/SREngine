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
        PX_UNUSED(filterData0);
        PX_UNUSED(filterData1);
        PX_UNUSED(constantBlock);
        PX_UNUSED(constantBlockSize);

        const bool isTrigger0 = physx::PxFilterObjectIsTrigger(attributes0);
        const bool isTrigger1 = physx::PxFilterObjectIsTrigger(attributes1);

        if (isTrigger0 || isTrigger1) {
            pairFlags =
                physx::PxPairFlag::eTRIGGER_DEFAULT
                | physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
                | physx::PxPairFlag::eNOTIFY_TOUCH_LOST;

            return physx::PxFilterFlag::eDEFAULT;
        }

        pairFlags =
            physx::PxPairFlag::eSOLVE_CONTACT
            | physx::PxPairFlag::eDETECT_DISCRETE_CONTACT
            | physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
            | physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS
            | physx::PxPairFlag::eNOTIFY_TOUCH_LOST
            | physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;

        return physx::PxFilterFlag::eDEFAULT;
    }

    PhysXPhysicsWorld::PhysXPhysicsWorld(Super::LibraryPtr pLibrary, Space space)
        : Super(pLibrary, space)
    {
        m_contactCallback = new ContactReportCallback();
    }

    PhysXPhysicsWorld::~PhysXPhysicsWorld() {
        if (m_controllerManager) {
            m_controllerManager->release();
            m_controllerManager = nullptr;
        }

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

        sceneDesc.filterShader = contactReportFilterShader;
        sceneDesc.simulationEventCallback = m_contactCallback;

        if (!sceneDesc.cpuDispatcher) {
            m_cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(1);
            sceneDesc.cpuDispatcher = m_cpuDispatcher;
        }

        if (!sceneDesc.filterShader) {
            sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
        }

        m_scene = pPhysics->createScene(sceneDesc);

        m_scene->setSimulationEventCallback(m_contactCallback);

        if (!m_scene) {
            SR_ERROR("PhysXPhysicsWorld::Initialize() : failed to create scene!");
            return false;
        }

        m_scene->setGravity(physx::PxVec3(0.f, -SR_EARTH_GRAVITY_CONST, 0.f));

        m_controllerManager = PxCreateControllerManager(*m_scene);

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

    bool PhysXPhysicsWorld::AddCharacterController(PhysicsWorld::CharacterControllerPtr pController) {
        SR_TRACY_ZONE;

        if (!pController) {
            SRHalt("pController is nullptr!");
            return false;
        }

        if (!pController->InitController()) {
            SR_ERROR("PhysXPhysicsWorld::AddCharacterController() : failed to initialize character controller!");
            return false;
        }

        auto&& pMaterialData = pController->GetMaterialData();
        if (!pMaterialData) {
            SR_ERROR("PhysXPhysicsWorld::AddCharacterController() : character controller has no material data!");
            return false;
        }

        physx::PxCapsuleControllerDesc desc;
        desc.height = pController->GetConfig().height;
        desc.radius = pController->GetConfig().radius;
        desc.position = SR_PHYSICS_UTILS_NS::FV3ToPxV3Extended(pController->GetTransform()->GetTranslation() + pController->GetConfig().offset);
        desc.upDirection = physx::PxVec3(0, 1, 0);
        desc.material = static_cast<physx::PxMaterial*>(pMaterialData->GetMaterialImpl(LibraryType::PhysX)->GetHandle());
        desc.stepOffset = pController->GetConfig().stepOffset;
        desc.slopeLimit = SR_COS(pController->GetConfig().slopeLimit * SR_PI / 180.0f);
        desc.contactOffset = pController->GetConfig().contactOffset;
        desc.invisibleWallHeight = pController->GetConfig().invisibleWallHeight;
        desc.maxJumpHeight = pController->GetConfig().maxJumpHeight;

        auto&& pControllerImpl = m_controllerManager->createController(desc);
        if (!pControllerImpl) {
            SR_ERROR("PhysXPhysicsWorld::AddCharacterController() : failed to create character controller!");
            return false;
        }

        pController->GetImpl()->SetHandle(pControllerImpl);

        return true;
    }

    bool PhysXPhysicsWorld::RemoveCharacterController(PhysicsWorld::CharacterControllerPtr pController) {
        SR_TRACY_ZONE;

        if (!pController) {
            SRHalt("pController is nullptr!");
            return false;
        }

        CharacterControllerImpl* pImpl = pController->GetImpl();
        if (!pImpl) {
            SR_ERROR("PhysXPhysicsWorld::RemoveCharacterController() : character controller has no implementation!");
            return false;
        }

        if (auto&& pControllerImpl = (physx::PxController*)pImpl->GetHandle()) {
            pControllerImpl->release();
            pController->ReleaseController();
            return true;
        }

        pController->ReleaseController();
        SR_ERROR("PhysXPhysicsWorld::RemoveCharacterController() : failed to get character controller handle!");
        return false;
    }

    bool PhysXPhysicsWorld::AddRigidbody(PhysicsWorld::RigidbodyPtr pRigidbody) {
        SR_TRACY_ZONE;

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
        SR_TRACY_ZONE;

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

        uint32_t cookedCount = 0;
        constexpr uint32_t maxCookPerFrame = 1;

        auto&& pActors = m_staticActors.data();
        m_scene->getActors(physx::PxActorTypeFlag::Enum::eRIGID_STATIC, pActors, count);

        for (uint32_t i = 0; i < count; ++i) {
            auto&& pRigidActor = pActors[i]->is<physx::PxRigidActor>();
            if (!SRVerifyFalse(!pRigidActor)) {
                continue;
            }

            auto&& pUserData = static_cast<RigidActorUserData*>(pRigidActor->userData);
            if (!SRVerifyFalse(!pUserData || !pUserData->pUserData)) {
                continue;
            }

            switch (pUserData->type) {
                case RigidActorUserData::Type::Rigidbody: {
                auto&& pRigidbody = (SR_PTYPES_NS::Rigidbody*)pUserData->pUserData;
                if (pRigidbody->IsBodyDirty()) {
                    SRVerifyFalse(!ReAddRigidbody(pRigidbody));
                    continue;
                }

                const RBUpdShapeRes result = pRigidbody->UpdateShape();
                if (result == RBUpdShapeRes::Error) {
                    SR_ERROR("PhysXPhysicsWorld::Synchronize() : failed to update shape!");
                    continue;
                }

                if (result == RBUpdShapeRes::Updated) {
                    for (auto&& pShape : pRigidbody->GetShapes()) {
                        if (pShape->GetType() == ShapeType::TriangleMesh3D) {
                            cookedCount++;
                        }
                    }
                }

                if (cookedCount > maxCookPerFrame) {
                    return true;
                }

                if (pRigidbody->IsMatrixDirty()) {
                    pRigidbody->UpdateMatrix();
                }
                break;
            }
                case RigidActorUserData::Type::CharacterController: {
                SRHalt("Character controllers should not be static actors!");
                break;
            }
                default: {
                SRHalt("Unknown rigid actor user data type!");
                break;
            }
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

            auto&& pUserData = static_cast<RigidActorUserData*>(pRigidActor->userData);
            if (!SRVerifyFalse(!pUserData || !pUserData->pUserData)) {
                continue;
            }

            switch (pUserData->type) {
                case RigidActorUserData::Type::Rigidbody: {
                auto&& pRigidbody = (SR_PTYPES_NS::Rigidbody*)pUserData->pUserData;
                if (pRigidbody->IsBodyDirty()) {
                    SRVerifyFalse(!ReAddRigidbody(pRigidbody));
                    continue;
                }

                if (pRigidbody->UpdateShape() == RBUpdShapeRes::Error) {
                    SR_ERROR("PhysXPhysicsWorld::Synchronize() : failed to update shape!");
                    continue;
                }
                pRigidbody->Synchronize();
                break;
            }
                case RigidActorUserData::Type::CharacterController: {
                auto&& pController = (CharacterController*)pUserData->pUserData;
                pController->GetImpl()->Synchronize();
                break;
            }
                default: {
                SRHalt("Unknown rigid actor user data type!");
                break;
            }
            }
        }

        return true;
    }

    void PhysXPhysicsWorld::ForEachRigidbody3D(const SR_HTYPES_NS::Function<void(SR_PTYPES_NS::Rigidbody3D*)>& fun) {
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

            auto&& pUserData = static_cast<RigidActorUserData*>(pRigidActor->userData);
            if (!SRVerifyFalse(!pUserData || !pUserData->pUserData)) {
                continue;
            }

            if (pUserData->type != RigidActorUserData::Type::Rigidbody) {
                continue;
            }

            auto&& pRigidbody = dynamic_cast<SR_PTYPES_NS::Rigidbody3D*>((SR_PTYPES_NS::Rigidbody*)pRigidActor->userData);
            fun(pRigidbody);
        }
    }
}
