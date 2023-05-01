//
// Created by Monika on 01.05.2023.
//

#include <Graphics/Animations/AnimationChannel.h>

namespace SR_ANIMATIONS_NS {
    uint32_t AnimationChannel::UpdateChannel(uint32_t keyIndex,
            float_t time,
            float_t weight,
            const AnimationPose* pStaticPose,
            AnimationPose* pWorkingPose
    ) const {
        auto&& pWorkingData = pWorkingPose->GetData(GetGameObjectHashName());
        auto&& pStaticData = pStaticPose->GetData(GetGameObjectHashName());

        if (!pWorkingData || !pStaticData) {
            return keyIndex;
        }

    skipKey:
        if (keyIndex == m_keys.size()) {
            return keyIndex;
        }

        auto&& [keyTime, pKey] = m_keys.at(keyIndex);

        if (time > keyTime) {
            if (keyIndex == 0) {
                pKey->Update(0.f, weight, nullptr, pWorkingData, pStaticData);
            }
            else {
                pKey->Update(1.f, weight, m_keys.at(keyIndex - 1).second, pWorkingData, pStaticData);
            }

            ++keyIndex;

            goto skipKey;
        }

        if (keyIndex == 0) {
            pKey->Update(0.f, weight, nullptr, pWorkingData, pStaticData);
        }
        else {
            auto&& [prevTime, prevKey] = m_keys.at(keyIndex - 1);

            const double_t currentTime = time - prevTime;
            const double_t keyCurrTime = keyTime - prevTime;
            const double_t progress = currentTime / keyCurrTime;

            pKey->Update(progress, weight, prevKey, pWorkingData, pStaticData);
        }

        return keyIndex;
    }
}