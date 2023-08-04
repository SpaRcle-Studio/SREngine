//
// Created by Monika on 08.05.2023.
//

#include <Graphics/Animations/AnimationState.h>

namespace SR_ANIMATIONS_NS {
    AnimationState::~AnimationState() {
        for (auto&& pTransition : m_transitions) {
            delete pTransition;
        }
    }

    void AnimationClipState::Update(const UpdateContext& context) {
        SR_TRACY_ZONE;

        if (!m_clip) {
            Super::Update(context);
            return;
        }

        uint32_t currentKeyFrame = 0;

        for (auto&& pChannel : m_clip->GetChannels()) {
            const uint32_t keyFrame = pChannel->UpdateChannel(
                m_playState[pChannel],
                m_time,
                context
            );
            currentKeyFrame = SR_MAX(currentKeyFrame, keyFrame);
        }

        m_time += context.dt;

        if (currentKeyFrame == m_maxKeyFrame) {
            m_time = 0.f;
            m_playState.clear();
        }

        Super::Update(context);
    }

    IAnimationClipState::~IAnimationClipState() {
        SetClip(nullptr);
    }

    IAnimationClipState::IAnimationClipState(AnimationStateMachine *pMachine, AnimationClip* pClip)
        : Super(pMachine)
    {
        SetClip(pClip);
    }

    void IAnimationClipState::SetClip(AnimationClip* pClip) {
        SR_TRACY_ZONE;

        if (m_clip == pClip) {
            return;
        }

        if (m_clip) {
            m_clip->RemoveUsePoint();
        }

        if (pClip) {
            pClip->AddUsePoint();
        }

        if ((m_clip = pClip)) {
            for (auto&& pChannel : m_clip->GetChannels()) {
                m_maxKeyFrame = SR_MAX(m_maxKeyFrame, pChannel->GetKeys().size());
            }
        }
    }

    void AnimationSetPoseState::OnTransitionBegin(const UpdateContext& context) {
        if (m_clip && context.pStaticPose) {
            context.pStaticPose->SetPose(m_clip);
        }
        Super::OnTransitionBegin(context);
    }
}