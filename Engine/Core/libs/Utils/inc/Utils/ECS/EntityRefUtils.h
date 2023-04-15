//
// Created by Monika on 30.11.2022.
//

#ifndef SRENGINE_ENTITYREFUTILS_H
#define SRENGINE_ENTITYREFUTILS_H

#include <Utils/Common/Enumerations.h>
#include <Utils/World/Scene.h>
#include <Utils/ECS/Entity.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>

namespace SR_UTILS_NS::EntityRefUtils {
    using OwnerRef = std::variant<Entity::Ptr, SR_WORLD_NS::Scene::Ptr>;

    SR_ENUM_NS_CLASS_T(Action, uint8_t,
        Action_Parent, Action_Child, Action_Component, Action_GameObject
    );

    struct PathItem {
        uint64_t hashName;
        uint16_t index;
        Action action;

        bool operator==(const PathItem& other) const noexcept {
            return
                hashName == other.hashName &&
                index == other.index &&
                action == other.action;
        }
    };

    typedef std::vector<PathItem> RefPath;

    SR_MAYBE_UNUSED static SR_WORLD_NS::Scene::Ptr GetSceneFromOwner(const OwnerRef& owner);

    SR_MAYBE_UNUSED static Entity::Ptr GetEntity(const OwnerRef& owner, const RefPath& path);

    SR_MAYBE_UNUSED static RefPath CalculatePath(const OwnerRef& from);
    SR_MAYBE_UNUSED static RefPath CalculateRelativePath(const OwnerRef& from, const Entity::Ptr& target);

    SR_MAYBE_UNUSED static bool IsOwnerValid(const OwnerRef& owner);

    /// ================================================================================================================

    Entity::Ptr GetEntity(const OwnerRef& owner, const RefPath& path) {
        Entity::Ptr pEntity;

        for (const PathItem& item : path) {
            switch (item.action) {
                case Action::Action_Parent: {
                    GameObject::Ptr pGameObject = pEntity.DynamicCast<GameObject>();

                    if (!pGameObject) {
                        pGameObject = std::visit([](OwnerRef&& arg) -> GameObject::Ptr {
                            if (std::holds_alternative<SR_UTILS_NS::Entity::Ptr>(arg)) {
                                auto&& pEntity = std::get<SR_UTILS_NS::Entity::Ptr>(arg);

                                if (auto&& pComponent = pEntity.DynamicCast<Component>()) {
                                    return pComponent->GetGameObject();
                                }

                                return pEntity.DynamicCast<GameObject>();
                            }
                            SRHaltOnce0();
                            return GameObject::Ptr();
                        }, owner);
                    }

                    if (pGameObject) {
                        pEntity = pGameObject->GetParent().DynamicCast<Entity>();
                        break;
                    }
                    SRHaltOnce0();
                    return nullptr;
                }
                case Action::Action_GameObject: {
                    if (auto&& pComponent = pEntity.DynamicCast<Component>()) {
                        pEntity = pComponent->GetGameObject().DynamicCast<Entity>();
                        break;
                    }
                    SRHaltOnce0();
                    return nullptr;
                }
                case Action::Action_Child: {
                    const std::vector<SR_UTILS_NS::GameObject::Ptr>* tree = nullptr;

                    if (!pEntity) {
                        tree = std::visit([](OwnerRef&& arg) -> std::vector<SR_UTILS_NS::GameObject::Ptr>* {
                            if (std::holds_alternative<SR_UTILS_NS::Entity::Ptr>(arg)) {
                                if (auto&& gm = std::get<SR_UTILS_NS::Entity::Ptr>(arg).DynamicCast<GameObject>()) {
                                    return &gm->GetChildrenRef();
                                }
                                else if (auto&& pComponent = std::get<SR_UTILS_NS::Entity::Ptr>(arg).DynamicCast<Component>()) {
                                    return &pComponent->GetGameObject()->GetChildrenRef();
                                }
                                SRHaltOnce0();
                                return { };
                            }
                            else if (std::holds_alternative<SR_WORLD_NS::Scene::Ptr>(arg)) {
                                return &std::get<SR_WORLD_NS::Scene::Ptr>(arg)->GetRootGameObjects();
                            }
                            else {
                                SRHaltOnce0();
                                return { };
                            }
                        }, owner);
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
                    if (auto&& pGameObject = pEntity.DynamicCast<GameObject>()) {
                        uint16_t index = item.index;
                        for (auto&& pComponent : pGameObject->GetComponents()) {
                            if (pComponent->GetComponentHashName() != item.hashName) {
                                continue;
                            }
                            if (index > 0) {
                                --index;
                                continue;
                            }
                            pEntity = pComponent->GetThis().DynamicCast<Entity>();
                        }
                        break;
                    }
                    return nullptr;
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

        if (from.index() == 1) {
            return std::move(refPath);
        }

        Entity::Ptr pFromEntity = from._Storage()._Get();

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

    RefPath CalculateRelativePath(const OwnerRef& from, const Entity::Ptr& target) {
        RefPath refPath;

        auto&& fromPath = CalculatePath(from);
        auto&& targetPath = CalculatePath(target);

        /**
         * File-System example:
         *      from: C:/A/B/C/file.txt
         *      to:   C:/A/G/C/file.txt
         *      path: ../../../G/C/file.txt
        */

        int32_t minSize = SR_MIN(fromPath.size(), targetPath.size());
        int32_t offset = 0;

        for (int32_t i = 0; i < minSize; ++i) {
            if (fromPath[i] != targetPath[i]) {
                break;
            }
            ++offset;
        }

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
        return std::visit([](OwnerRef&& arg) -> bool{
            if (std::holds_alternative<SR_UTILS_NS::Entity::Ptr>(arg)) {
                return std::get<SR_UTILS_NS::Entity::Ptr>(arg);
            }
            else if (std::holds_alternative<SR_WORLD_NS::Scene::Ptr>(arg)) {
                return std::get<SR_WORLD_NS::Scene::Ptr>(arg);
            }
            else {
                SRHalt0();
                return false;
            }
        }, owner);
    }

    SR_WORLD_NS::Scene::Ptr GetSceneFromOwner(const OwnerRef& owner) {
        return std::visit([](OwnerRef&& arg) -> SR_WORLD_NS::Scene::Ptr {
            if (std::holds_alternative<SR_UTILS_NS::Entity::Ptr>(arg)) {
                SR_UTILS_NS::Entity::Ptr pEntity = std::get<SR_UTILS_NS::Entity::Ptr>(arg);

                if (auto&& pComponent = pEntity.DynamicCast<Component>()) {
                    return pComponent->GetGameObject()->GetScene()->GetThis();
                }
                else if (auto&& pGameObject = pEntity.DynamicCast<GameObject>()) {
                    return pGameObject->GetScene()->GetThis();
                }
            }
            else if (std::holds_alternative<SR_WORLD_NS::Scene::Ptr>(arg)) {
                return std::get<SR_WORLD_NS::Scene::Ptr>(arg);
            }

            SRHalt0();

            return SR_WORLD_NS::Scene::Ptr();
        }, owner);
    }
}

#endif //SRENGINE_ENTITYREFUTILS_H
