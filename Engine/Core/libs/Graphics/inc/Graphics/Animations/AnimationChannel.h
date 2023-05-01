//
// Created by Monika on 08.01.2023.
//

#ifndef SRENGINE_ANIMATIONCHANNEL_H
#define SRENGINE_ANIMATIONCHANNEL_H

#include <Utils/ECS/EntityRef.h>

#include <Graphics/Animations/AnimationKey.h>

namespace SR_ANIMATIONS_NS {
    class AnimationKey;
    class AnimationPose;

    class AnimationChannel final : public SR_UTILS_NS::NonCopyable {
        using Keys = std::vector<std::pair<double_t, AnimationKey*>>;
    public:
        ~AnimationChannel() override {
            for (auto&& [time, pKey] : m_keys) {
                delete pKey;
            }
        }

    public:
        SR_NODISCARD AnimationChannel* Copy() const noexcept {
            auto&& pChannel = new AnimationChannel();

            for (auto&& [time, pKey] : GetKeys()) {
                pChannel->AddKey(time, pKey->Copy(pChannel));
            }

            pChannel->m_hashName = m_hashName;

            return pChannel;
        }

        void SetName(const std::string_view& name) {
            m_hashName = SR_HASH_STR_VIEW(name);
            if (m_hashName == 0) {
                SRHalt0();
            }
        }

        void AddKey(double_t timePoint, AnimationKey* pKey) {
            m_keys.emplace_back(std::make_pair(timePoint, pKey));
        }

        uint32_t UpdateChannel(uint32_t keyIndex,
                float_t time,
                float_t weight,
                const AnimationPose* pStaticPose,
                AnimationPose* pWorkingPose) const;

    public:
        SR_NODISCARD const Keys& GetKeys() const { return m_keys; }
        SR_NODISCARD SR_FORCE_INLINE uint64_t GetGameObjectHashName() const noexcept { return m_hashName; }

    private:
        uint64_t m_hashName = 0;
        Keys m_keys;

    };
}

#endif //SRENGINE_ANIMATIONCHANNEL_H
