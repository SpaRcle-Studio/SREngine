//
// Created by Monika on 30.11.2022.
//

#ifndef SRENGINE_ENTITYREFUTILS_H
#define SRENGINE_ENTITYREFUTILS_H

#include <Utils/Common/Enumerations.h>
#include <Utils/World/Scene.h>
#include <Utils/ECS/Entity.h>

namespace SR_UTILS_NS::EntityRefUtils {
    using OwnerRef = std::variant<Entity::Ptr, SR_WORLD_NS::Scene::Ptr>;

    SR_ENUM_NS_CLASS_T(Action, uint8_t,
        Action_SceneRoot, Action_Parent, Action_Child, Action_Component, Action_GameObject
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

    SR_MAYBE_UNUSED static Entity::Ptr GetEntity(const OwnerRef& owner, const RefPath& path);

    SR_MAYBE_UNUSED static RefPath CalculatePath(const OwnerRef& from);
    SR_MAYBE_UNUSED static RefPath CalculateRelativePath(const OwnerRef& from, const Entity::Ptr& target);

    SR_MAYBE_UNUSED static bool IsOwnerValid(const OwnerRef& owner);

    /// ================================================================================================================

    Entity::Ptr GetEntity(const OwnerRef& owner, const RefPath& path) {
        Entity::Ptr pEntity;

        for (const PathItem& item : path) {
            switch (item.action) {
                case Action::Action_SceneRoot: {
                    pEntity = nullptr;
                    break;
                }
                case Action::Action_Parent: {
                    if (auto&& pGameObject = pEntity.DynamicCast<GameObject>()) {
                        pEntity = pGameObject->GetParent().DynamicCast<Entity>();
                        break;
                    }
                    SRHalt0();
                    return nullptr;
                }
                case Action::Action_GameObject: {
                    if (auto&& pComponent = pEntity.DynamicCast<Component>()) {
                        pEntity = pComponent->GetGameObject().DynamicCast<Entity>();
                        break;
                    }
                    SRHalt0();
                    return nullptr;
                }
                case Action::Action_Child: {
                    if (auto&& pGameObject = pEntity.DynamicCast<GameObject>()) {
                        uint16_t index = item.index;
                        for (auto&& pChild : pGameObject->GetChildrenRef()) {
                            if (pChild->GetHashName() != item.hashName) {
                                continue;
                            }
                            if (index > 0) {
                                --index;
                                continue;
                            }
                            pEntity = pChild.DynamicCast<Entity>();
                        }
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
                    SRHalt0();
                    break;
            }
        }

        return pEntity;
    }

    RefPath CalculatePath(const OwnerRef& from) {
        RefPath refPath;

        if (from.index() == 1) {
            PathItem item = {
                .action = Action::Action_SceneRoot
            };
            refPath.emplace_back(item);
            return std::move(refPath);
        }

        Entity::Ptr pFromEntity = from._Storage()._Get();

        while (pFromEntity) {
            /// ---------------------- [ Component ] ----------------------
            if (auto&& pComponent = pFromEntity.DynamicCast<Component>()) {
                auto&& pParent = pComponent->GetParent();

                if (dynamic_cast<SR_WORLD_NS::Scene*>(pParent)) {
                    PathItem item = {
                        .action = Action::Action_SceneRoot
                    };
                    refPath.emplace_back(item);
                    break;
                }
                else if (auto&& pGameObject = dynamic_cast<GameObject*>(pParent)) {
                    uint16_t componentIndex = 0;

                    for (auto&& pComponentIteration : pGameObject->GetComponents()) {
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
                    pFromEntity = pGameObject;
                }
                else {
                    SRHalt0();
                }
            }
            /// --------------------- [ Game Object ] ---------------------
            else if (auto&& pGameObject = pFromEntity.DynamicCast<GameObject>()) {
                auto&& pParent = pGameObject->GetParent();

                if (!pParent) {
                    PathItem item = {
                        .action = Action::Action_SceneRoot
                    };
                    refPath.emplace_back(item);
                    break;
                }

                uint16_t objectIndex = 0;

                for (auto&& pChild : pParent->GetChildrenRef()) {
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

        for (int32_t i = fromPath.size() - 1; i >= offset; --i) {
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
}

#endif //SRENGINE_ENTITYREFUTILS_H
