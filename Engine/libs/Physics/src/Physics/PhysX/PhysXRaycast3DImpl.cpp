//
// Created by innerviewer on 2/16/2023.
//

#include <Physics/PhysX/PhysXRaycast3DImpl.h>

#include <Utils/ECS/GameObject.h>

namespace SR_PHYSICS_NS {
    class RaycastTagFilterCallback : public physx::PxQueryFilterCallback {
    public:
        const SR_UTILS_NS::LayerMask& layerMask;
        SR_UTILS_NS::TagManager& tagManager;

        RaycastTagFilterCallback(const SR_UTILS_NS::LayerMask& mask)
            : layerMask(mask)
            , tagManager(SR_UTILS_NS::TagManager::Instance())
        { }

        // Вызывается для каждого shape, чтобы решить — тестировать или нет.
        physx::PxQueryHitType::Enum preFilter(const physx::PxFilterData& filterData, const physx::PxShape* pShape, const physx::PxRigidActor* pActor, physx::PxHitFlags& queryFlags) override {
            SR_TRACY_ZONE;

            if (!pActor) {
                return physx::PxQueryHitType::eNONE;
            }

            auto&& pUserData = static_cast<RigidActorUserData*>(pActor->userData);
            if (!pUserData || pUserData->type != RigidActorUserData::Type::Rigidbody) {
                return physx::PxQueryHitType::eNONE;
            }

            auto&& pRigidbody = reinterpret_cast<SR_PTYPES_NS::Rigidbody3D*>(pUserData->pUserData);
            if (!pRigidbody) {
                return physx::PxQueryHitType::eNONE;
            }

            auto&& pSo = pRigidbody->GetSceneObject();
            if (!pSo) {
                return physx::PxQueryHitType::eNONE;
            }

            uint64_t tagMask = tagManager.TagToMask(pSo->GetTag());

            // если тег не подходит — этот shape пропускаем
            if (!SR_MATH_NS::IsMaskIncludedSubMask(layerMask.mask, tagMask))
                return physx::PxQueryHitType::eNONE;

            return physx::PxQueryHitType::eBLOCK; // тестируем
        }

        // postFilter не нужен
        physx::PxQueryHitType::Enum postFilter(const physx::PxFilterData&, const physx::PxQueryHit& hit) override {
            return physx::PxQueryHitType::eBLOCK;
        }
    };

    PhysXRaycast3DImpl::RaycastHits PhysXRaycast3DImpl::Cast(const SR_MATH_NS::FVector3& origin, const SR_MATH_NS::FVector3& direction, float_t maxDistance, uint32_t maxHits, const SR_UTILS_NS::LayerMask& layerMask) {
        SR_TRACY_ZONE;

        RaycastHits hits;

        auto&& pPxScene = static_cast<PhysXPhysicsWorld*>(m_world)->GetPxScene();
        if (!pPxScene) {
            SRHalt("PhysXRaycast3DImpl::Cast() : PxScene is null!");
            return hits;
        }

        physx::PxRaycastHit hitsRaw[64];
        physx::PxRaycastBuffer hitBuffer(hitsRaw, 64);

        RaycastTagFilterCallback filter(layerMask);

        physx::PxQueryFilterData filterData;
        filterData.flags = physx::PxQueryFlag::eSTATIC | physx::PxQueryFlag::eDYNAMIC | physx::PxQueryFlag::ePREFILTER;

        physx::PxVec3 pxOrigin = SR_PHYSICS_UTILS_NS::FV3ToPxV3(origin);
        physx::PxVec3 pxDir = SR_PHYSICS_UTILS_NS::FV3ToPxV3(direction);

        const bool hasHit = pPxScene->raycast(
            pxOrigin,
            pxDir,
            maxDistance,
            hitBuffer,
            physx::PxHitFlag::eDEFAULT,
            filterData,
            &filter
        );

        if (!hasHit || hitBuffer.getNbAnyHits() == 0) {
            return hits;
        }

        uint32_t count = std::min<uint32_t>(hitBuffer.getNbAnyHits(), maxHits);
        hits.reserve(count);

        for (uint32_t i = 0; i < count; i++) {
            auto& pxHit = hitBuffer.getAnyHit(i);

            const auto* pActor = pxHit.actor;
            if (!pActor) {
                continue;
            }

            auto&& pUserData = static_cast<RigidActorUserData*>(pActor->userData);
            if (!pUserData || pUserData->type != RigidActorUserData::Type::Rigidbody) {
                continue;
            }

            auto* pRigidbody = reinterpret_cast<SR_PTYPES_NS::Rigidbody3D*>(pUserData->pUserData);
            if (!pRigidbody) {
                continue;
            }

            SR_UTILS_NS::RaycastHit outHit;
            outHit.pHandler = static_cast<SR_PTYPES_NS::Rigidbody*>(pRigidbody);
            outHit.distance = pxHit.distance;
            outHit.normal = SR_PHYSICS_UTILS_NS::PxV3ToFV3(pxHit.normal);
            outHit.position = SR_PHYSICS_UTILS_NS::PxV3ToFV3(pxHit.position);

            hits.emplace_back(outHit);
        }

        return hits;

        /*
           auto&& tagManager = SR_UTILS_NS::TagManager::Instance();
           m_world->ForEachRigidbody3D([&](SR_PTYPES_NS::Rigidbody3D* pRigidbody){
            if (hits.size() == maxHits) {
                return;
            }

            physx::PxTransform pose = ((physx::PxRigidActor*)pRigidbody->GetHandle())->getGlobalPose();

            if (pose.p == SR_PHYSICS_UTILS_NS::FV3ToPxV3(origin)){
                return;
            }

            auto&& pSO = pRigidbody->GetSceneObject();
            if (!pSO) {
                return;
            }

            uint64_t tag = tagManager.TagToMask(pSO->GetTag());
            if (!SR_MATH_NS::IsMaskIncludedSubMask(layerMask.mask, tag)) {
                return;
            }

            for (auto&& pPhysShape : pRigidbody->GetShapes()) {
                physx::PxShape* pShape = ((physx::PxShape*)pPhysShape->GetHandle());

                if (!pShape) {
                    if (auto&& gameObject = pRigidbody->GetGameObject()) {
                        SRHaltOnce("PhysXRaycast3DImpl::Cast() : " + gameObject->GetName().ToStringRef() + " does not have a collision shape!");
                    }
                    else {
                        SRHaltOnce("PhysXRaycast3DImpl::Cast() : rigidbody does not have a collision shape!");
                    }
                    return;
                }

                physx::PxRaycastHit pxHit;
                physx::PxU32 hitCount = physx::PxGeometryQuery::raycast(
                        SR_PHYSICS_UTILS_NS::FV3ToPxV3(origin),
                        SR_PHYSICS_UTILS_NS::FV3ToPxV3(direction),
                        pShape->getGeometry().any(),
                        pose,
                        maxDistance,
                        physx::PxHitFlag::eDEFAULT,
                        1,
                        &pxHit
                );

                if (hitCount == 0) {
                    continue;
                }

                SR_UTILS_NS::RaycastHit hit;
                hit.pHandler = dynamic_cast<SR_PTYPES_NS::Rigidbody*>(pRigidbody);
                hit.distance = pxHit.distance;
                hit.normal = SR_PHYSICS_UTILS_NS::PxV3ToFV3(pxHit.normal);
                hit.position = SR_PHYSICS_UTILS_NS::PxV3ToFV3(pxHit.position);

                hits.emplace_back(hit);
            }
           });*/

        return hits;
    }
}