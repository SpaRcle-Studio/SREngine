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
        : Super(SR_COMPILE_TIME_CRC32_TYPE_NAME(AnimationClip))
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
                pAnimationClip->StopWatch();
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

        SR_HTYPES_NS::RawMeshParams params;
        params.animation = true;

        auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(rawPath, params);
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

    void AnimationClip::LoadChannels(SR_HTYPES_NS::RawMesh* pRawMesh, uint32_t index) {
        auto&& pAnimation = pRawMesh->GetAssimpScene()->mAnimations[index];

        for (uint16_t channelIndex = 0; channelIndex < pAnimation->mNumChannels; ++channelIndex) {
            AnimationChannel::Load(
                pRawMesh,
                pAnimation->mChannels[channelIndex],
                pAnimation->mTicksPerSecond,
                m_channels
            );
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
        auto&& resourceId = GetResourceId();

        if (SR_UTILS_NS::StringUtils::GetExtensionFromFilePath(resourceId) == "animation") {
            SRHalt("TODO!");
        }
        else {
            auto&& [strIndex, rawPath] = SR_UTILS_NS::StringUtils::SplitTwo(resourceId, "|");
            uint32_t index = SR_UTILS_NS::LexicalCast<uint32_t>(strIndex);

            SR_HTYPES_NS::RawMeshParams params;
            params.animation = true;

            auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(rawPath, params);
            if (!pRawMesh) {
                return false;
            }

            if (index >= pRawMesh->GetAssimpScene()->mNumAnimations) {
                SR_ERROR("AnimationClip::Load() : wrong animation index!\n\tTotal animations: {}", pRawMesh->GetAssimpScene()->mNumAnimations);
                return false;
            }

            LoadChannels(pRawMesh, index);
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