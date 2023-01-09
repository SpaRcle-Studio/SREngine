//
// Created by Monika on 08.01.2023.
//

#include <Graphics/Animations/AnimationClip.h>
#include <Graphics/Animations/AnimationChannel.h>

#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_ANIMATIONS_NS {
    AnimationClip::~AnimationClip() {
        for (auto&& pChannel : m_channels) {
            delete pChannel;
        }
        m_channels.clear();
    }

    AnimationClip* AnimationClip::Load(const Helper::Path &rawPath, uint32_t index) {
        Assimp::Importer importer;

        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        auto&& path = rawPath.SelfRemoveSubPath(resourceManager.GetResPathRef());
        path = resourceManager.GetResPath().Concat(rawPath);

        const aiScene* pScene = importer.ReadFile(path.ToString(), static_cast<aiPostProcessSteps>(0));
        if (!pScene) {
            SR_ERROR("AnimationClip::Load() : failed to load animation clips!\n\tPath: " + rawPath.ToString());
            return nullptr;
        }

        if (index >= pScene->mNumAnimations) {
            SR_ERROR("AnimationClip::Load() : out of range!\n\tPath: " + rawPath.ToString());
            return nullptr;
        }

        return Load(pScene->mAnimations[index]);
    }

    std::vector<AnimationClip*> AnimationClip::Load(const SR_UTILS_NS::Path &rawPath) {
        Assimp::Importer importer;

        std::vector<AnimationClip*> animations;

        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        auto&& path = rawPath.SelfRemoveSubPath(resourceManager.GetResPathRef());
        path = resourceManager.GetResPath().Concat(rawPath);

        const aiScene* pScene = importer.ReadFile(path.ToString(), static_cast<aiPostProcessSteps>(0));
        if (!pScene) {
            SR_ERROR("AnimationClip::Load() : failed to load animation clips!\n\tPath: " + rawPath.ToString());
            return std::move(animations);
        }

        animations.reserve(pScene->mNumAnimations);

        for (uint16_t animationIndex = 0; animationIndex < pScene->mNumAnimations; ++animationIndex) {
            animations.emplace_back(Load(pScene->mAnimations[animationIndex]));
        }

        return std::move(animations);
    }

    AnimationClip* AnimationClip::Load(aiAnimation* pAnimation) {
        auto&& pAnimationClip = new AnimationClip();

        for (uint16_t channelIndex = 0; channelIndex < pAnimation->mNumChannels; ++channelIndex) {
            auto&& pChannel = pAnimation->mChannels[channelIndex];

            auto&& pTranslationChannel = new AnimationChannel();
            auto&& pRotationChannel = new AnimationChannel();
            auto&& pScalingChannel = new AnimationChannel();

            pTranslationChannel->GetEntityRef().AddPathItem(SR_UTILS_NS::EntityRefUtils::Action::Action_Child, pChannel->mNodeName.C_Str());

            for (uint16_t positionKeyIndex = 0; positionKeyIndex < pChannel->mNumPositionKeys; ++positionKeyIndex) {
                auto&& pPositionKey = pChannel->mPositionKeys[positionKeyIndex];

                pTranslationChannel->AddKey(pPositionKey.mTime / pAnimation->mTicksPerSecond, new TranslationKey(pTranslationChannel, SR_MATH_NS::FVector3(
                    pPositionKey.mValue.z / 100.f,
                    pPositionKey.mValue.y / 100.f,
                    pPositionKey.mValue.x / 100.f
                )));
            }

            for (uint16_t rotationKeyIndex = 0; rotationKeyIndex < pChannel->mNumRotationKeys; ++rotationKeyIndex) {
                auto&& pRotationKey = pChannel->mRotationKeys[rotationKeyIndex];

                auto&& q = SR_MATH_NS::Quaternion(
                        pRotationKey.mValue.y,
                        pRotationKey.mValue.x,
                        pRotationKey.mValue.z,
                        pRotationKey.mValue.w
                );

                pRotationChannel->AddKey(pRotationKey.mTime / pAnimation->mTicksPerSecond, new RotationKey(pRotationChannel, q));
            }

            for (uint16_t scalingKeyIndex = 0; scalingKeyIndex < pChannel->mNumScalingKeys; ++scalingKeyIndex) {
                auto&& pScalingKey = pChannel->mScalingKeys[scalingKeyIndex];

                pScalingChannel->AddKey(pScalingKey.mTime / pAnimation->mTicksPerSecond, new ScalingKey(pScalingChannel, SR_MATH_NS::FVector3(
                        pScalingKey.mValue.z / 100.f,
                        pScalingKey.mValue.y / 100.f,
                        pScalingKey.mValue.x / 100.f
                )));
            }

            pAnimationClip->m_channels.emplace_back(pTranslationChannel);
            pAnimationClip->m_channels.emplace_back(pRotationChannel);
            pAnimationClip->m_channels.emplace_back(pScalingChannel);
        }

        return pAnimationClip;
    }
}