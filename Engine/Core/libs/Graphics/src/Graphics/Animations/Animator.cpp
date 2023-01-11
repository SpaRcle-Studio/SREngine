//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/Animator.h>
#include <Graphics/Animations/AnimationClip.h>
#include <Graphics/Animations/AnimationChannel.h>

#include <Utils/ECS/ComponentManager.h>

namespace SR_ANIMATIONS_NS {
    SR_REGISTER_COMPONENT(Animator);

    Animator::~Animator() {
        delete m_animationClip;
    }

    SR_UTILS_NS::Component* Animator::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pController = new Animator();
        return pController;
    }

    SR_UTILS_NS::Component* Animator::CopyComponent() const {
        auto&& pController = new Animator();
        return pController;
    }

    SR_HTYPES_NS::Marshal::Ptr Animator::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        return Super::Save(pMarshal, flags);
    }

    void Animator::OnDestroy() {
        Super::OnDestroy();
        delete this;
    }

    void Animator::FixedUpdate() {
        if (m_sync) {
            UpdateInternal(1.f / 60.f);
        }

        Super::FixedUpdate();
    }

    void Animator::Update(float_t dt) {
        if (!m_sync) {
            UpdateInternal(dt / 1000.f);
        }

        Super::Update(dt);
    }

    void Animator::UpdateInternal(float_t dt) {
        auto&& pParent = dynamic_cast<SR_UTILS_NS::GameObject*>(GetParent());
        if (!pParent) {
            return;
        }

        uint32_t maxKeyFrame = 0;

        for (auto&& pChannel : m_animationClip->GetChannels()) {
            const uint32_t keyFrame = UpdateChannel(pChannel, pParent);
            maxKeyFrame = SR_MAX(maxKeyFrame, keyFrame);
        }

        m_time += dt;

        if (maxKeyFrame == m_maxKeyFrame) {
            m_time = 0.f;
            m_playState.clear();
        }
    }

    void Animator::OnAttached() {
        m_animationClip = AnimationClip::Load("Samples/Liza/Standing Idle.fbx", 0);

        for (auto&& pChannel : m_animationClip->GetChannels()) {
            m_maxKeyFrame = SR_MAX(m_maxKeyFrame, pChannel->GetKeys().size());
        }

        Super::OnAttached();
    }

    uint32_t Animator::UpdateChannel(AnimationChannel* pChannel, SR_UTILS_NS::GameObject* pRoot) {
        auto&& keys = pChannel->GetKeys();
        auto&& keyIndex = m_playState[pChannel];

    skipKey:
        if (keyIndex == keys.size()) {
            return keyIndex;
        }

        auto&& [time, pKey] = keys.at(keyIndex);

        if (m_time > time) {
            if (keyIndex == 0) {
                pKey->Update(0.f, nullptr, pRoot);
            }
            else {
                pKey->Update(1.f, keys.at(keyIndex - 1).second, pRoot);
            }

            ++keyIndex;

            goto skipKey;
        }

        if (keyIndex == 0) {
            pKey->Update(0.f, nullptr, pRoot);
        }
        else {
            auto&& [prevTime, prevKey] = keys.at(keyIndex - 1);

            const double_t currentTime = m_time - prevTime;
            const double_t keyTime = time - prevTime;
            const double_t progress = currentTime / keyTime;

            pKey->Update(progress, prevKey, pRoot);
        }

        return keyIndex;
    }
}