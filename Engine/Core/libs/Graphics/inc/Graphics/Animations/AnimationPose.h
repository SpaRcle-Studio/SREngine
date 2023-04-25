//
// Created by Monika on 25.04.2023.
//

#ifndef SRENGINE_ANIMATIONPOSE_H
#define SRENGINE_ANIMATIONPOSE_H

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

#include <Graphics/Animations/AnimationData.h>
#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Animations/Bone.h>

namespace SR_ANIMATIONS_NS {
    class Skeleton;

    class AnimationPose : public SR_UTILS_NS::NonCopyable {
        using BoneHashName = uint64_t;
        using Index = uint32_t;
    public:
        ~AnimationPose() override {
            for (auto&& [boneHashName, pData] : m_data) {
                delete pData;
            }
            m_indices.clear();
            m_data.clear();
        }

    public:
        SR_NODISCARD AnimationData* GetData(BoneHashName boneHashName) const noexcept {
            if (auto&& pIt = m_indices.find(boneHashName); pIt != m_indices.end()) {
                return pIt->second;
            }

            return nullptr;
        }

        void Reset() {
            for (auto&& [boneHashName, pData] : m_data) {
                pData->Reset();
            }
        }

        void Initialize(Skeleton* pSkeleton) {
            auto&& bones = pSkeleton->GetBones();

            m_indices.reserve(bones.size());
            m_data.reserve(bones.size());

            for (auto&& pBone : bones) {
                auto&& pair = std::make_pair(
                    pBone->hashName,
                    new AnimationData()
                );

                m_indices.insert(pair);
                m_data.emplace_back(pair);
            }

            m_isInitialized = true;
        }

        void Apply(Skeleton* pSkeleton, AnimationPose* pSourcePose) {
            if (!m_isInitialized) {
                Initialize(pSkeleton);
            }

            for (auto&& [boneHashName, pData] : m_data) {
                auto&& pBone = pSkeleton->TryGetBone(boneHashName);
                if (!pBone || !pBone->gameObject) {
                    continue;
                }

                if (pSourcePose) {
                    Apply(pData, pBone->gameObject, pSourcePose);
                }
                else {
                    Apply(pData, pBone->gameObject);
                }
            }
        }

    private:
        static void Apply(const AnimationData* pData, const SR_UTILS_NS::GameObject::Ptr& pGameObject) {
            auto&& pTransform = pGameObject->GetTransform();

            if (pData->translation.has_value()) {
                pTransform->SetTranslation(pData->translation.value());
            }

            if (pData->rotation.has_value()) {
                pTransform->SetRotation(pData->rotation.value());
            }

            if (pData->scale.has_value()) {
                pTransform->SetScale(pData->scale.value());
            }
        }

        void Apply(const AnimationData* pData, const SR_UTILS_NS::GameObject::Ptr& pGameObject, AnimationPose* pSourcePose) {
            auto&& pTransform = pGameObject->GetTransform();

            /*if (translation.has_value()) {
                if (states.count(pTarget) == 0) {
                    auto&& pAnimatedData = new AnimationData();
                    auto&& pOriginData = new AnimationData();
                    pOriginData->translation = pAnimatedData->translation = pTransform->GetTranslation();
                    pTransform->SetTranslation(translation.value());
                    states.insert(std::make_pair(pGameObject, std::make_pair(pOriginData, pAnimatedData)));
                }
                else {
                    auto&& [pOrigin, pAnimated] = states.at(pTarget);

                    auto&& offset = pTransform->GetTranslation() - pAnimated->translation.value();

                    if (pOrigin->translation.has_value()) {
                        offset = pAnimated->translation.value() - pTransform->GetTranslation();

                        pAnimated->translation = translation;
                        pTransform->SetTranslation(pOrigin->translation.value());

                        pOrigin->translation = std::nullopt;
                    }
                    else {
                        pAnimated->translation = translation;

                        pTransform->SetTranslation(translation.value() + offset);
                    }
                }
            }

            if (rotation.has_value()) {
                pTransform->SetRotation(rotation.value());
            }

            if (scale.has_value()) {
                pTransform->SetScale(scale.value());
            }*/
        }

    private:
        bool m_isInitialized = false;

        ska::flat_hash_map<BoneHashName, AnimationData*> m_indices;
        std::vector<std::pair<BoneHashName, AnimationData*>> m_data;

    };
}

#endif //SRENGINE_ANIMATIONPOSE_H
