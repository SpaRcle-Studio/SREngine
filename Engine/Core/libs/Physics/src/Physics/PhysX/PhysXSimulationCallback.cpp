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
        for (physx::PxU32 i = 0; i < nbPairs; i++)
        {
            const physx::PxContactPair& cp = pairs[i];

            SR_PTYPES_NS::CollisionShape* shape1 = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(cp.shapes[0]->userData);
            SR_PTYPES_NS::CollisionShape* shape2 = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(cp.shapes[1]->userData);

            SR_PTYPES_NS::Rigidbody* rigidbody1 = shape1->GetRigidbody();
            SR_PTYPES_NS::Rigidbody* rigidbody2 = shape2->GetRigidbody();

            SR_UTILS_NS::CollisionData data = { };

            auto&& gameObject1 = rigidbody1->GetGameObject();
            auto&& gameObject2 = rigidbody2->GetGameObject();

            if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
            {
                for (auto&& pComponent : gameObject1->GetComponents()){
                    if (pComponent == rigidbody1){
                        continue;
                    }
                    else {
                        data.pHandler = rigidbody1;
#ifdef SR_DEBUG
                        std::cout << "Detected collision ENTER for : " << rigidbody1->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << rigidbody2->GetGameObject()->GetName() << std::endl;
#endif
                        pComponent->OnCollisionEnter(data);
                    }
                }
                for (auto&& pComponent : gameObject2->GetComponents()){
                    if (pComponent == rigidbody2){
                        continue;
                    }
                    else {
                        data.pHandler = rigidbody2;
#ifdef SR_DEBUG
                        std::cout << "Detected collision ENTER for : " << rigidbody2->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << rigidbody1->GetGameObject()->GetName() << std::endl;
#endif
                        pComponent->OnCollisionEnter(data);
                    }
                }
            }
            if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
            {
                for (auto&& pComponent : gameObject1->GetComponents()){
                    if (pComponent == rigidbody1){
                        continue;
                    }
                    else {
                        data.pHandler = rigidbody1;
#ifdef SR_DEBUG
                        std::cout << "Detected collision STAY for : " << rigidbody1->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << rigidbody2->GetGameObject()->GetName() << std::endl;
#endif
                        pComponent->OnCollisionStay(data);
                    }
                }
                for (auto&& pComponent : gameObject2->GetComponents()){
                    if (pComponent == rigidbody2){
                        continue;
                    }
                    else {
                        data.pHandler = rigidbody2;
#ifdef SR_DEBUG
                        std::cout << "Detected collision STAY for : " << rigidbody2->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << rigidbody1->GetGameObject()->GetName() << std::endl;
#endif
                        pComponent->OnCollisionStay(data);
                    }
                }
            }
            if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
            {
                for (auto&& pComponent : gameObject1->GetComponents()){
                    if (pComponent == rigidbody1){
                        continue;
                    }
                    else {
                        data.pHandler = rigidbody1;
#ifdef SR_DEBUG
                        std::cout << "Detected collision EXIT for : " << rigidbody1->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << rigidbody2->GetGameObject()->GetName() << std::endl;
#endif
                        pComponent->OnCollisionExit(data);
                    }
                }
                for (auto&& pComponent : gameObject2->GetComponents()){
                    if (pComponent == rigidbody2){
                        continue;
                    }
                    else {
                        data.pHandler = rigidbody2;
#ifdef SR_DEBUG
                        std::cout << "Detected collision EXIT for : " << rigidbody2->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << rigidbody1->GetGameObject()->GetName() << std::endl;
#endif
                        pComponent->OnCollisionExit(data);
                    }
                }
            }
        }
    }
    /**
    This method handles only RigidBody-Trigger collisions and calls the OnTriggerEnter/OnTriggerStay/OnTriggerExit method as appropriate.
     */
    void ContactReportCallback::onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count)
    {
        for(physx::PxU32 i=0; i < count; i++)
        {
            // ignore pairs when shapes have been deleted
            if (pairs[i].flags & (physx::PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER |
                                  physx::PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
                continue;

            const physx::PxTriggerPair& tp = pairs[i];

            SR_PTYPES_NS::CollisionShape* triggerShape = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(tp.triggerShape[0].userData);
            SR_PTYPES_NS::CollisionShape* otherShape = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(tp.otherShape[0].userData);

            SR_PTYPES_NS::Rigidbody* triggerRigidBody = triggerShape->GetRigidbody();
            SR_PTYPES_NS::Rigidbody* rigidbody = otherShape->GetRigidbody();

            SR_UTILS_NS::CollisionData data = { };

            auto&& triggerGameObject = triggerRigidBody->GetGameObject();
            auto&& gameObject = rigidbody->GetGameObject();

            if (tp.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
            {
                for (auto&& pComponent : gameObject->GetComponents()){
                    if (pComponent == rigidbody){
                        continue;
                    }
                    else {
                        data.pHandler = rigidbody;
#ifdef SR_DEBUG
                        std::cout << "Detected trigger ENTER for : " << rigidbody->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << triggerGameObject->GetName() << std::endl;
#endif
                        pComponent->OnTriggerEnter(data);
                    }
                }

                for (auto&& pComponent : triggerGameObject->GetComponents()){
                    if (pComponent == triggerRigidBody){
                        continue;
                    }
                    else {
                        data.pHandler = triggerRigidBody;
#ifdef SR_DEBUG
                        std::cout << "Detected trigger ENTER for : " << triggerRigidBody->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << gameObject->GetName() << std::endl;
#endif
                        pComponent->OnTriggerEnter(data);
                    }
                }
            }
            if (tp.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
            {
                for (auto&& pComponent : gameObject->GetComponents()){
                    if (pComponent == rigidbody){
                        continue;
                    }
                    else {
                        data.pHandler = rigidbody;
#ifdef SR_DEBUG
                        std::cout << "Detected trigger EXIT for : " << rigidbody->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << triggerGameObject->GetName() << std::endl;
#endif
                        pComponent->OnTriggerExit(data);
                    }
                }
                for (auto&& pComponent : triggerGameObject->GetComponents()){
                    if (pComponent == triggerRigidBody){
                        continue;
                    }
                    else {
                        data.pHandler = triggerRigidBody;
#ifdef SR_DEBUG
                        std::cout << "Detected trigger EXIT for : " << triggerRigidBody->GetGameObject()->GetName() << "(" << pComponent->GetComponentName()<<  ")"<< "\twith\t" << gameObject->GetName() << std::endl;
#endif
                        pComponent->OnTriggerExit(data);
                    }
                }
            }
        }
    }
}