//
// Created by Monika on 08.01.2023.
//

#ifndef SRENGINE_ANIMATIONCHANNEL_H
#define SRENGINE_ANIMATIONCHANNEL_H

#include <Utils/ECS/EntityRef.h>

#include <Graphics/Animations/AnimationKey.h>

namespace SR_ANIMATIONS_NS {
    class AnimationKey;

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
        }

        void AddKey(double_t timePoint, AnimationKey* pKey) {
            m_keys.emplace_back(std::make_pair(timePoint, pKey));
        }

    public:
        SR_NODISCARD const Keys& GetKeys() const { return m_keys; }

    private:
        uint64_t m_hashName = 0;
        Keys m_keys;

    };
}

#endif //SRENGINE_ANIMATIONCHANNEL_H
