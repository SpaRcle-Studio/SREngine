//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/Animator.h>

#include <Utils/ECS/ComponentManager.h>

namespace SR_ANIMATIONS_NS {
    SR_REGISTER_COMPONENT(Animator);

    Animator::~Animator() {
        if (m_animationClip) {
            m_animationClip->RemoveUsePoint();
            m_animationClip = nullptr;
        }
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
        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void Animator::FixedUpdate() {
        if (m_sync) {
            UpdateInternal(1.f / 60.f);
        }

        Super::FixedUpdate();
    }

    void Animator::Update(float_t dt) {
        m_skeleton = GetParent()->GetComponent<Skeleton>();

        if (!m_sync) {
            UpdateInternal(dt / 1000.f);
        }

        Super::Update(dt);
    }

    void Animator::UpdateInternal(float_t dt) {
        if (!m_gameObject || !m_animationClip) {
            return;
        }

        uint32_t maxKeyFrame = 0;

        for (auto&& pChannel : m_animationClip->GetChannels()) {
            const uint32_t keyFrame = UpdateChannel(pChannel);
            maxKeyFrame = SR_MAX(maxKeyFrame, keyFrame);
        }

        m_time += dt;

        if (maxKeyFrame == m_maxKeyFrame) {
            m_time = 0.f;
            m_playState.clear();
        }
    }

    void Animator::OnAttached() {
        //m_animationClip = AnimationClip::Load("Samples/Liza/Walking.fbx", 0);

        //m_animationClip = AnimationClip::Load("Samples/Liza/Standing Idle.fbx", 0);
        //m_animationClip = AnimationClip::Load("Samples/Liza/Dancing Twerk.fbx", 0);
        //m_animationClip = AnimationClip::Load("Samples/Liza/Jump.fbx", 0);
        m_animationClip = AnimationClip::Load("Samples/Tsumugi/Tsumugi.fbx", 0);

        if (!m_animationClip) {
            return;
        }

        m_animationClip->AddUsePoint();

        for (auto&& pChannel : m_animationClip->GetChannels()) {
            m_maxKeyFrame = SR_MAX(m_maxKeyFrame, pChannel->GetKeys().size());
        }

        Super::OnAttached();
    }

    void Animator::Start() {
        m_gameObject = GetGameObject().Get();
        Super::Start();
    }

    uint32_t Animator::UpdateChannel(AnimationChannel* pChannel) {
        auto&& keys = pChannel->GetKeys();
        auto&& keyIndex = m_playState[pChannel];

        SR_UTILS_NS::GameObject* pTarget = m_gameObject;

        if (m_skeleton) {
            auto&& pBone = m_skeleton->GetBone(pChannel->GetGameObjectHashName());
            if (pBone && pBone->gameObject) {
                pTarget = pBone->gameObject.Get();
            }
        }

        if (!pTarget) {
            return keyIndex;
        }

    skipKey:
        if (keyIndex == keys.size()) {
            return keyIndex;
        }

        auto&& [time, pKey] = keys.at(keyIndex);

        if (m_time > time) {
            if (keyIndex == 0) {
                pKey->Update(0.f, nullptr, pTarget);
            }
            else {
                pKey->Update(1.f, keys.at(keyIndex - 1).second, pTarget);
            }

            ++keyIndex;

            goto skipKey;
        }

        if (keyIndex == 0) {
            pKey->Update(0.f, nullptr, pTarget);
        }
        else {
            auto&& [prevTime, prevKey] = keys.at(keyIndex - 1);

            const double_t currentTime = m_time - prevTime;
            const double_t keyTime = time - prevTime;
            const double_t progress = currentTime / keyTime;

            pKey->Update(progress, prevKey, pTarget);
        }

        return keyIndex;
    }
}