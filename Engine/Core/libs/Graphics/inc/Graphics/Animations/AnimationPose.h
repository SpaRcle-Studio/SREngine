//
// Created by Monika on 25.04.2023.
//

#ifndef SRENGINE_ANIMATIONPOSE_H
#define SRENGINE_ANIMATIONPOSE_H

#include <Utils/ECS/GameObject.h>

#include <Graphics/Animations/AnimationCommon.h>

namespace SR_ANIMATIONS_NS {
    class Skeleton;
    class AnimationData;
    class AnimationClip;

    class AnimationPose : public SR_UTILS_NS::NonCopyable {
        using BoneHashName = uint64_t;
        using Index = uint32_t;
    public:
        ~AnimationPose() override;

    public:
        SR_NODISCARD AnimationData* GetData(BoneHashName boneHashName) const noexcept;

        void Reset();
        void Initialize(Skeleton* pSkeleton);
        void Apply(Skeleton* pSkeleton);
        void Update(Skeleton* pSkeleton, AnimationPose* pWorkingPose);
        void SetPose(AnimationClip* pClip);

    private:
        static void Apply(const AnimationData* pWorkingData, const SR_UTILS_NS::GameObject::Ptr& pGameObject);
        static void Update(AnimationData* pStaticData, const AnimationData* pWorkingData, const SR_UTILS_NS::GameObject::Ptr& pGameObject);

    private:
        bool m_isInitialized = false;

        ska::flat_hash_map<BoneHashName, AnimationData*> m_indices;
        std::vector<std::pair<BoneHashName, AnimationData*>> m_data;

    };
}

#endif //SRENGINE_ANIMATIONPOSE_H
