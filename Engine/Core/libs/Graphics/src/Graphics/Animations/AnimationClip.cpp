//
// Created by Monika on 08.01.2023.
//

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <Graphics/Animations/AnimationClip.h>
#include <Graphics/Animations/AnimationChannel.h>

#include <Utils/Types/RawMesh.h>

namespace SR_ANIMATIONS_NS {
    AnimationClip::AnimationClip()
        : Super(SR_COMPILE_TIME_CRC32_TYPE_NAME(AnimationClip), true /** auto remove */)
    { }

    AnimationClip::~AnimationClip() {
        for (auto&& pChannel : m_channels) {
            delete pChannel;
        }
        m_channels.clear();
    }

    AnimationClip* AnimationClip::Load(const SR_UTILS_NS::Path &rawPath, uint32_t index) {
        SR_GLOBAL_LOCK

        AnimationClip* pAnimationClip = nullptr;

        SR_UTILS_NS::ResourceManager::Instance().Execute([&]() {
            auto&& path = rawPath.SelfRemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPathRef());
            auto&& resourceId = path.GetExtensionView() == "animation" ? path.ToString() : std::to_string(index) + "|" + path.ToString();

            if (auto&& pResource = SR_UTILS_NS::ResourceManager::Instance().Find<AnimationClip>(path)) {
                pAnimationClip = pResource;
                return;
            }

            pAnimationClip = new AnimationClip();
            pAnimationClip->SetId(resourceId, false /** auto register */);

            if (!pAnimationClip->Reload()) {
                SR_ERROR("AnimationClip::Load() : failed to load animation clip! \n\tPath: " + path.ToString());
                delete pAnimationClip;
                pAnimationClip = nullptr;
                return;
            }

            /// отложенная ручная регистрация
            SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pAnimationClip);
        });

        return pAnimationClip;
    }

    std::vector<AnimationClip*> AnimationClip::Load(const SR_UTILS_NS::Path& rawPath) {
        std::vector<AnimationClip*> animations;

        auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(rawPath, true);
        if (!pRawMesh) {
            return animations;
        }

        for (uint32_t i = 0; i < pRawMesh->GetAnimationsCount(); ++i) {
            auto&& pAnimationClip = Load(rawPath, i);
            animations.emplace_back(pAnimationClip);
        }

        if (animations.empty()) {
            SR_ERROR("AnimationClip::Load() : failed to load animation clips! Path: " + rawPath.ToString());
        }

        return animations;
    }

    void AnimationClip::LoadChannels(aiAnimation *pAnimation) {
        for (uint16_t channelIndex = 0; channelIndex < pAnimation->mNumChannels; ++channelIndex) {
            auto&& pChannel = pAnimation->mChannels[channelIndex];

            /// --------------------------------------------------------------------------------------------------------

            if (pChannel->mNumPositionKeys > 0) {
                auto&& pTranslationChannel = new AnimationChannel();

                pTranslationChannel->SetName(pChannel->mNodeName.C_Str());

                for (uint16_t positionKeyIndex = 0; positionKeyIndex < pChannel->mNumPositionKeys; ++positionKeyIndex) {
                    auto&& pPositionKey = pChannel->mPositionKeys[positionKeyIndex];

                    pTranslationChannel->AddKey(pPositionKey.mTime / pAnimation->mTicksPerSecond, new TranslationKey(pTranslationChannel, SR_MATH_NS::FVector3(
                            pPositionKey.mValue.x / 100.f,
                            pPositionKey.mValue.y / 100.f,
                            pPositionKey.mValue.z / 100.f
                    )));
                }

                m_channels.emplace_back(pTranslationChannel);
            }

            /// --------------------------------------------------------------------------------------------------------

            if (pChannel->mNumRotationKeys > 0) {
                auto&& pRotationChannel = new AnimationChannel();

                pRotationChannel->SetName(pChannel->mNodeName.C_Str());

                for (uint16_t rotationKeyIndex = 0; rotationKeyIndex < pChannel->mNumRotationKeys; ++rotationKeyIndex) {
                    auto&& pRotationKey = pChannel->mRotationKeys[rotationKeyIndex];

                    auto&& q = SR_MATH_NS::Quaternion(
                            pRotationKey.mValue.x,
                            pRotationKey.mValue.y,
                            pRotationKey.mValue.z,
                            pRotationKey.mValue.w
                    );

                   pRotationChannel->AddKey(pRotationKey.mTime / pAnimation->mTicksPerSecond, new RotationKey(pRotationChannel, q));
                }

                m_channels.emplace_back(pRotationChannel);
            }

            /// --------------------------------------------------------------------------------------------------------

            if (pChannel->mNumScalingKeys > 0) {
                auto&& pScalingChannel = new AnimationChannel();

                pScalingChannel->SetName(pChannel->mNodeName.C_Str());

                for (uint16_t scalingKeyIndex = 0; scalingKeyIndex < pChannel->mNumScalingKeys; ++scalingKeyIndex) {
                    auto&& pScalingKey = pChannel->mScalingKeys[scalingKeyIndex];

                    pScalingChannel->AddKey(pScalingKey.mTime / pAnimation->mTicksPerSecond, new ScalingKey(pScalingChannel, SR_MATH_NS::FVector3(
                            pScalingKey.mValue.x / 1.f,
                            pScalingKey.mValue.y / 1.f,
                            pScalingKey.mValue.z / 1.f
                    )));
                }

                m_channels.emplace_back(pScalingChannel);
            }
        }
    }

    bool AnimationClip::Unload() {
        for (auto&& pChannel : m_channels) {
            delete pChannel;
        }
        m_channels.clear();

        return Super::Unload();
    }

    bool AnimationClip::Load() {
        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        auto&& resourceId = GetResourceId();

        if (SR_UTILS_NS::StringUtils::GetExtensionFromFilePath(resourceId) == "animation") {

        }
        else {
            auto&& [strIndex, rawPath] = SR_UTILS_NS::StringUtils::SplitTwo(resourceId, "|");
            uint32_t index = SR_UTILS_NS::LexicalCast<uint32_t>(strIndex);

            auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(rawPath, true);
            if (!pRawMesh) {
                return false;
            }

            LoadChannels(pRawMesh->GetAssimpScene()->mAnimations[index]);
        }

        return Super::Load();
    }

    SR_UTILS_NS::Path AnimationClip::InitializeResourcePath() const {
        return SR_UTILS_NS::Path(
                std::move(SR_UTILS_NS::StringUtils::SubstringView(GetResourceId(), '|', 1)),
                true /** fast */
        );
    }
}