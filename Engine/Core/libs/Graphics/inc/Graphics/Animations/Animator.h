//
// Created by Monika on 07.01.2023.
//

#ifndef SRENGINE_ANIMATOR_H
#define SRENGINE_ANIMATOR_H

#include <Utils/ECS/Component.h>
#include <Graphics/Animations/AnimationKey.h>
#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Animations/AnimationGraph.h>
#include <Graphics/Animations/AnimationStateMachine.h>

namespace SR_ANIMATIONS_NS {
    class AnimationClip;
    class AnimationChannel;

    class Animator : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Animator);
        using Super = SR_UTILS_NS::Component;
    protected:
        ~Animator() override;

    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        SR_NODISCARD Component* CopyComponent() const override;
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        void FixedUpdate() override;
        void Update(float_t dt) override;

        void OnAttached() override;
        void OnDestroy() override;

        void Start() override;

    private:
        void UpdateInternal(float_t dt);
        uint32_t UpdateChannel(AnimationChannel* pChannel);

    public:
        float_t m_weight = 1.f;

    private:
        bool m_sync = false;

        AnimationPose* m_workingPose = nullptr;
        AnimationPose* m_staticPose = nullptr;

        std::map<AnimationChannel*, uint32_t> m_playState;

        SR_UTILS_NS::GameObject* m_gameObject = nullptr;
        Skeleton* m_skeleton = nullptr;

        uint32_t m_maxKeyFrame = 0;
        float_t m_time = 0.f;

        AnimationClip* m_animationClip = nullptr;

    };
}

#endif //SRENGINE_ANIMATOR_H
