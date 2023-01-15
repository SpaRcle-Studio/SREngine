//
// Created by Igor on 07/12/2022.
//

#ifndef SRENGINE_SKELETONANIMATIONCLIP_H
#define SRENGINE_SKELETONANIMATIONCLIP_H

#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Animations/AnimationPose.h>

namespace SR_ANIMATIONS_NS {
    class SkeletonAnimationClip {
    public:
        SkeletonAnimationClip(
                const AssimpSkeleton* skeleton,
                float duration,
                float rate,
                std::vector<BoneAnimationChannel> bonesAnimationChannels)
                : m_skeleton(),
                  m_bonesAnimationChannels(std::move(bonesAnimationChannels)),
                  m_currentPose(skeleton, std::vector<BonePose>(skeleton->bones.size())),
                  m_duration(duration),
                  m_rate(rate)
        {
        }

        SR_NODISCARD const AnimationPose& GetCurrentPose() const;

        void Load(SR_UTILS_NS::Path path);
        void IncreaseCurrentTime(float delta);

    private:
        SR_NODISCARD BonePose GetBoneLocalPose(uint8_t boneIndex, float time) const;

        template<class T, class S>
        SR_NODISCARD T GetMixedAdjacentFrames(const std::vector<S>& frames, float time) const;

        template<class T>
        T GetIdentity() const { assert(false); }

        template<class T, class S>
        T GetKeyframeValue(const S& frame) const { assert(false); }

        template<class T>
        T GetInterpolatedValue(const T& first, const T& second, float delta) const { assert(false); }

    private:
        const Skeleton* m_skeleton;
        std::vector<BoneAnimationChannel> m_bonesAnimationChannels;

        mutable AnimationPose m_currentPose;

        double m_currentTime = 0.0f;
        double m_duration = 0.0f;
        double m_rate = 0.0f;
    };

}

#endif //SRENGINE_SKELETONANIMATIONCLIP_H