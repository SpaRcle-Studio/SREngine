//
// Created by Monika on 08.01.2023.
//

#ifndef SRENGINE_ANIMATIONCHANNEL_H
#define SRENGINE_ANIMATIONCHANNEL_H

#include <Utils/ECS/EntityRef.h>

#include <Graphics/Animations/AnimationKey.h>

struct aiNodeAnim;

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_ANIMATIONS_NS {
    class AnimationKey;
    class AnimationPose;

    class AnimationChannel final : public SR_UTILS_NS::NonCopyable {
        using Keys = std::vector<std::pair<float_t, AnimationKey*>>;
    public:
        ~AnimationChannel() override;

    public:
        static void Load(SR_HTYPES_NS::RawMesh* pRawMesh, aiNodeAnim* pChannel, float_t ticksPerSecond, std::vector<AnimationChannel*>& channels);

        SR_NODISCARD AnimationChannel* Copy() const noexcept {
            auto&& pChannel = new AnimationChannel();

            for (auto&& [time, pKey] : GetKeys()) {
                pChannel->AddKey(time, pKey->Copy(pChannel));
            }

            pChannel->m_hashName = m_hashName;
            pChannel->m_boneIndex = m_boneIndex;

            return pChannel;
        }

        void SetName(const std::string_view& name);
        void SetBoneIndex(uint16_t index) { m_boneIndex = index; }

        void AddKey(float_t timePoint, AnimationKey* pKey);

        uint32_t UpdateChannel(uint32_t keyIndex, float_t time, const UpdateContext& context) const;

    public:
        SR_NODISCARD const Keys& GetKeys() const { return m_keys; }

        SR_NODISCARD SR_FORCE_INLINE uint64_t GetGameObjectHashName() const noexcept { return m_hashName; }
        SR_NODISCARD SR_FORCE_INLINE uint16_t GetBoneIndex() const noexcept { return m_boneIndex; }

    private:
        uint16_t m_boneIndex = SR_UINT16_MAX;
        uint64_t m_hashName = 0;
        Keys m_keys;

    };
}

#endif //SRENGINE_ANIMATIONCHANNEL_H
