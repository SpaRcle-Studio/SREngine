//
// Created by Monika on 16.04.2023.
//

#include <Utils/ECS/EntityRefUtils.h>
#include <Utils/World/Scene.h>
#include <Utils/ECS/Entity.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>

namespace SR_UTILS_NS::EntityRefUtils {
    EntityRefUtils::OwnerRef::OwnerRef(const SR_HTYPES_NS::SharedPtr<Entity>& ptr)
        : pEntity(ptr)
    { }

    EntityRefUtils::OwnerRef::OwnerRef(const SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>& ptr)
        : pScene(ptr)
    { }

    Entity::Ptr GetEntity(const OwnerRef& owner, const RefPath& path) {
        Entity::Ptr pEntity;

        for (const PathItem& item : path) {
            switch (item.action) {
                case Action::Action_Parent: {
                    GameObject::Ptr pGameObject = pEntity.DynamicCast<GameObject>();

                    if (!pGameObject && owner.pEntity) {
                        if (auto&& pComponent = owner.pEntity.DynamicCast<Component>()) {
                            if (!pComponent->IsComponentValid()) {
                                return nullptr;
                            }
                            pGameObject = pComponent->GetGameObject();
                        }
                        else if (auto&& pOwnerGameObject = owner.pEntity.DynamicCast<GameObject>()) {
                            pGameObject = pOwnerGameObject->GetParent();
                        }
                    }

                    if (pGameObject) {
                        pEntity = pGameObject->GetParent().DynamicCast<Entity>();
                    }

                    break;
                }
                case Action::Action_Child: {
                    const std::vector<SR_UTILS_NS::GameObject::Ptr>* tree = nullptr;

                    if (!pEntity) {
                        if (owner.pEntity) {
                            if (auto&& gm = owner.pEntity.DynamicCast<GameObject>()) {
                                tree = &gm->GetChildrenRef();
                            }
                            else if (auto&& pComponent = owner.pEntity.DynamicCast<Component>()) {
                                tree = &pComponent->GetScene()->GetRootGameObjects();
                            }
                        }
                        else if (owner.pScene) {
                            tree = &owner.pScene->GetRootGameObjects();
                        }
                    }
                    else if (auto&& pGameObject = pEntity.DynamicCast<GameObject>()) {
                        tree = &pGameObject->GetChildrenRef();
                    }

                    if (!tree) {
                        SRHaltOnce0();
                        return nullptr;
                    }

                    uint16_t index = item.index;
                    bool found = false;
                    for (auto&& pChild : *tree) {
                        if (pChild->GetHashName() != item.hashName) {
                            continue;
                        }
                        if (index > 0) {
                            --index;
                            continue;
                        }
                        pEntity = pChild.DynamicCast<Entity>();
                        found = true;
                    }

                    if (found) {
                        break;
                    }

                    return nullptr;
                }
                case Action::Action_Component: {
                    const std::vector<Component*>& components = pEntity ? pEntity.DynamicCast<GameObject>()->GetComponents() : GetSceneFromOwner(owner)->GetComponents();

                    if (components.empty()) {
                        return nullptr;
                    }

                    uint16_t index = item.index;
                    for (auto&& pComponent : components) {
                        SRAssert1Once(pComponent->Valid());

                        if (pComponent->GetComponentHashName() != item.hashName) {
                            continue;
                        }
                        if (index > 0) {
                            --index;
                            continue;
                        }
                        pEntity = pComponent->DynamicCast<Entity>();
                        break;
                    }

                    break;
                }
                default:
                    SRHaltOnce0();
                    break;
            }
        }

        return pEntity;
    }

    RefPath CalculatePath(const OwnerRef& from) {
        RefPath refPath;

        if (from.pScene) {
            return std::move(refPath);
        }

        Entity::Ptr pFromEntity = from.pEntity;

        while (pFromEntity) {
            /// ---------------------- [ Component ] ----------------------
            if (auto&& pComponent = pFromEntity.DynamicCast<Component>()) {
                if (auto&& pParent = pComponent->GetParent()) {
                    uint16_t componentIndex = 0;

                    for (auto&& pComponentIteration : pParent->GetComponents()) {
                        if (pComponent == pComponentIteration) {
                            break;
                        }
                        if (pComponentIteration->GetComponentHashName() == pComponent->GetComponentHashName()) {
                            ++componentIndex;
                        }
                    }

                    PathItem item = {
                            .hashName = pComponent->GetComponentHashName(),
                            .index = componentIndex,
                            .action = Action::Action_Component
                    };

                    refPath.emplace_back(item);

                    if (auto&& pGameObject = dynamic_cast<GameObject*>(pParent)) {
                        pFromEntity = pGameObject;
                    }
                    else {
                        pFromEntity = nullptr;
                    }
                }
                else {
                    SRHalt0();
                }
            }
                /// --------------------- [ Game Object ] ---------------------
            else if (auto&& pGameObject = pFromEntity.DynamicCast<GameObject>()) {
                auto&& pParent = pGameObject->GetParent();

                auto&& tree = pParent ? pParent->GetChildrenRef() : pGameObject->GetScene()->GetRootGameObjects();

                uint16_t objectIndex = 0;

                for (auto&& pChild : tree) {
                    if (pChild == pGameObject) {
                        break;
                    }
                    if (pChild->GetHashName() == pGameObject->GetHashName()) {
                        ++objectIndex;
                    }
                }

                PathItem item = {
                    .hashName = pGameObject->GetHashName(),
                    .index = objectIndex,
                    .action = Action::Action_Child
                };

                refPath.emplace_back(item);
                pFromEntity = pParent.DynamicCast<Entity>();
            }
        }

        std::reverse(refPath.begin(), refPath.end());

        return std::move(refPath);
    }

    RefPath CalculateRelativePath(const OwnerRef& from, const OwnerRef& target) {
        RefPath refPath;

        auto&& fromPath = CalculatePath(from);
        auto&& targetPath = CalculatePath(target);

        /**
         * File-System example:
         *      from: C:/A/B/C/file.txt
         *      to:   C:/A/G/C/file.txt
         *      path: ../../../G/C/file.txt
        */

        const int32_t minSize = SR_MIN(fromPath.size(), targetPath.size());
        int32_t offset = 0;

        for (int32_t i = 0; i < minSize; ++i) {
            if (fromPath[i] != targetPath[i]) {
                break;
            }
            ++offset;
        }

        /// Вычитаем 2, так как один это конец массива, а второй это компонент
        for (int32_t i = fromPath.size() - 2; i >= offset; --i) {
            PathItem item = {
                .action = Action::Action_Parent
            };
            refPath.emplace_back(item);
        }

        for (int32_t i = offset; i < targetPath.size(); ++i) {
            refPath.emplace_back(targetPath[i]);
        }

        return refPath;
    }

    bool IsOwnerValid(const OwnerRef& owner) {
        return owner.pScene || owner.pEntity;
    }

    bool IsTargetInitialized(const OwnerRef& owner) {
        if (owner.pScene) {
            return true;
        }

        if (auto&& pComponent = owner.pEntity.DynamicCast<Component>()) {
            return pComponent->HasParent();
        }

        if (auto&& pGameObject = owner.pEntity.DynamicCast<GameObject>()) {
            return pGameObject->GetScene();
        }

        return false;
    }

    SR_WORLD_NS::Scene::Ptr GetSceneFromOwner(const OwnerRef& owner) {
        if (owner.pEntity) {
            SR_UTILS_NS::Entity::Ptr pEntity = owner.pEntity;

            if (auto&& pComponent = pEntity.DynamicCast<Component>()) {
                if (!pComponent->IsComponentValid()) {
                    return SR_WORLD_NS::Scene::Ptr();
                }
                return pComponent->GetGameObject()->GetScene()->GetThis();
            }
            else if (auto&& pGameObject = pEntity.DynamicCast<GameObject>()) {
                return pGameObject->GetScene()->GetThis();
            }
        }

        return owner.pScene;
    }
}
