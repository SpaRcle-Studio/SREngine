//
// Created by innerviewer on 21.01.2023.
//

#include <Physics/PhysX/PhysXSimulationCallback.h>
#include <Utils/ECS/GameObject.h>
#include <Physics/Rigidbody.h>
#include <Utils/Common/CollisionData.h>

namespace SR_PHYSICS_NS {
    void ContactReportCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
    {
        for (physx::PxU32 i = 0; i < nbPairs; i++)
        {
            const physx::PxContactPair& cp = pairs[i];

            if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
            {
                SR_PTYPES_NS::CollisionShape* shape1 = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(cp.shapes[0]->userData);
                SR_PTYPES_NS::CollisionShape* shape2 = reinterpret_cast<SR_PTYPES_NS::CollisionShape*>(cp.shapes[1]->userData);

                SR_PTYPES_NS::Rigidbody* rigidbody1 = shape1->GetRigidbody();
                SR_PTYPES_NS::Rigidbody* rigidbody2 = shape2->GetRigidbody();

                SR_UTILS_NS::CollisionData data;

                /// Оба - триггеры
                if (rigidbody1->IsTrigger() && rigidbody2->IsTrigger()){
                    continue;
                }
                /// Только первый - триггер
                else if (rigidbody1->IsTrigger() && !rigidbody2->IsTrigger()) {
                    auto&& gameObject2 = rigidbody2->GetGameObject();
                    for (auto&& pComponent : gameObject2->GetComponents()){
                        if (pComponent == rigidbody2){
                            continue;
                        }
                        else {
                            pComponent->OnCollisionEnter(data);
                        }
                    }
                }
                /// Только второй - триггер
                else if (!rigidbody1->IsTrigger() && rigidbody2->IsTrigger()){
                    auto&& gameObject1 = rigidbody1->GetGameObject();
                    for (auto&& pComponent : gameObject1->GetComponents()){
                        if (pComponent == rigidbody1){
                            continue;
                        }
                        else {
                            pComponent->OnCollisionEnter(data);
                        }
                    }
                }
                /// Оба не триггеры
                else if (!rigidbody1->IsTrigger() && !rigidbody2->IsTrigger()) {
                    auto&& gameObject1 = rigidbody1->GetGameObject();
                    auto&& gameObject2 = rigidbody2->GetGameObject();
                    for (auto&& pComponent : gameObject1->GetComponents()){
                        if (pComponent == rigidbody1){
                            continue;
                        }
                        else {
                            pComponent->OnCollisionEnter(data);
                        }
                    }
                    for (auto&& pComponent : gameObject2->GetComponents()){
                        if (pComponent == rigidbody2){
                            continue;
                        }
                        else {
                            pComponent->OnCollisionEnter(data);
                        }
                    }
                }
            }
        }
    }
}
