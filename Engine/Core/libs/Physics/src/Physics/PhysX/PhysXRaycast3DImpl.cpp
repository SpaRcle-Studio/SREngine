//
// Created by innerviewer on 2/16/2023.
//

#include <Physics/PhysX/PhysXRaycast3DImpl.h>

#include <Utils/ECS/GameObject.h>

namespace SR_PHYSICS_NS {
    PhysXRaycast3DImpl::RaycastHits PhysXRaycast3DImpl::Cast(const SR_MATH_NS::FVector3 &origin, const SR_MATH_NS::FVector3 &direction, float_t maxDistance, uint32_t maxHits) {
        RaycastHits hits;
        hits.reserve(maxHits);

        m_world->ForEachRigidbody3D([&](SR_PTYPES_NS::Rigidbody3D* pRigidbody){
            if (hits.size() == maxHits){
                return;
            }

            physx::PxTransform pose = ((physx::PxRigidActor*)pRigidbody->GetHandle())->getGlobalPose();

            if (pose.p == SR_PHYSICS_UTILS_NS::FV3ToPxV3(origin)){
                return;
            }

            physx::PxShape* pShape = ((physx::PxShape*)pRigidbody->GetCollisionShape()->GetHandle());

            if (!pShape) {
                if (auto&& gameObject = pRigidbody->GetGameObject()) {
                    SRHaltOnce("PhysXRaycast3DImpl::Cast() : " + gameObject->GetName() + " does not have a collision shape!");
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

            if (hitCount == 0){
                return;
            }

            SR_UTILS_NS::RaycastHit hit;
            hit.pHandler = dynamic_cast<SR_PTYPES_NS::Rigidbody*>(pRigidbody);
            hit.distance = pxHit.distance;
            hit.normal = SR_PHYSICS_UTILS_NS::PxV3ToFV3(pxHit.normal);
            hit.position = SR_PHYSICS_UTILS_NS::PxV3ToFV3(pxHit.position);

            hits.emplace_back(hit);
        });

        return hits;
    }
}