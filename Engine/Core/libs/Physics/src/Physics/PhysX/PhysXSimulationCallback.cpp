//
// Created by innerviewer on 21.01.2023.
//

#include <Physics/PhysX/PhysXSimulationCallback.h>
#include <Utils/ECS/GameObject.h>
#include <Physics/Rigidbody.h>
#include <Utils/Common/CollisionData.h>

namespace SR_PHYSICS_NS {
    /**
    This method handles only RigidBody-RigidBody collisions and calls the OnCollisionEnter/OnCollisionStay/OnCollisionExit method as appropriate.
     */
    void ContactReportCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
    {
        const physx::PxU32 bufferSize = 64;
        physx::PxContactPairPoint contacts[bufferSize];

        auto point = physx::PxVec3(0);
        auto impulse  = physx::PxVec3(0);

        for (physx::PxU32 i = 0; i < nbPairs; i++)
        {
            physx::PxU32 nbContacts = pairs[i].extractContacts(contacts, bufferSize);

            for(physx::PxU32 j=0; j < nbContacts; j++)
            {
                point += contacts[j].position;
                impulse += contacts[j].impulse;
            }

            point /= nbContacts > 0 ? nbContacts : 1.f;
            impulse /= nbContacts > 0 ? nbContacts : 1.f;

            const physx::PxContactPair& cp = pairs[i];

            auto shape1 = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(cp.shapes[0]->userData);
            auto shape2 = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(cp.shapes[1]->userData);

            SR_PTYPES_NS::Rigidbody* rigidbody1 = shape1->GetRigidbody();
            SR_PTYPES_NS::Rigidbody* rigidbody2 = shape2->GetRigidbody();

            SR_UTILS_NS::CollisionData data = { };

            auto&& gameObject1 = rigidbody1->GetGameObject();
            auto&& gameObject2 = rigidbody2->GetGameObject();

            if (!gameObject1 || !gameObject2) {
                SRHalt0();
                continue;
            }

            data.point = SR_PHYSICS_UTILS_NS::PxV3ToFV3(point);
            data.impulse = SR_PHYSICS_UTILS_NS::PxV3ToFV3(impulse);
            data.pHandler = rigidbody2;

            for (auto&& pComponent : gameObject1->GetComponents()){
                if (pComponent == rigidbody1){
                    continue;
                }
                else {
                    if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
                    {
                        pComponent->OnCollisionEnter(data);
                    }
                    if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
                    {
                        pComponent->OnCollisionStay(data);
                    }
                    if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
                    {
                        pComponent->OnCollisionExit(data);
                    }
                }
            }

            data.pHandler = rigidbody1;

            for (auto&& pComponent : gameObject2->GetComponents()){
                if (pComponent == rigidbody2){
                    continue;
                }
                else {
                    if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
                    {
                        pComponent->OnCollisionEnter(data);
                    }
                    if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
                    {
                        pComponent->OnCollisionStay(data);
                    }
                    if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
                    {
                        pComponent->OnCollisionExit(data);
                    }
                }
            }
        }
    }
    /**
    This method handles only RigidBody-Trigger collisions and calls the OnTriggerEnter/OnTriggerExit method as appropriate.
     */
    void ContactReportCallback::onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count)
    {
        for(physx::PxU32 i=0; i < count; i++)
        {
            // ignore pairs when shapes have been deleted
            if (pairs[i].flags & (physx::PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER |
                                  physx::PxTriggerPairFlag::eREMOVED_SHAPE_OTHER)) {
                continue;
            }

            const physx::PxTriggerPair& tp = pairs[i];

            auto triggerShape = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(tp.triggerShape[0].userData);
            auto otherShape = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(tp.otherShape[0].userData);

            SR_PTYPES_NS::Rigidbody* triggerRigidBody = triggerShape->GetRigidbody();
            SR_PTYPES_NS::Rigidbody* rigidbody = otherShape->GetRigidbody();

            SR_UTILS_NS::CollisionData data = { };

            auto&& triggerGameObject = triggerRigidBody->GetGameObject();
            auto&& gameObject = rigidbody->GetGameObject();

            if (!triggerGameObject || !gameObject) {
                SRHalt0();
                continue;
            }

            data.pHandler = rigidbody;

            for (auto&& pComponent : triggerGameObject->GetComponents()){
                if (pComponent == triggerRigidBody){
                    continue;
                }
                else {
                    if (tp.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
                    {
                        pComponent->OnCollisionEnter(data);
                    }
                    if (tp.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
                    {
                        pComponent->OnCollisionExit(data);
                    }
                }
            }

            data.pHandler = triggerRigidBody;

            for (auto&& pComponent : gameObject->GetComponents()){
                if (pComponent == rigidbody){
                    continue;
                }
                else {
                    if (tp.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
                    {
                        pComponent->OnTriggerEnter(data);
                    }
                    if (tp.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
                    {
                        pComponent->OnTriggerExit(data);
                    }
                }
            }
        }
    }
}