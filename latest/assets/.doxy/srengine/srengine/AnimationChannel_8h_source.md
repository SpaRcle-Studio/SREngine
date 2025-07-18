

# File AnimationChannel.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**AnimationChannel.h**](AnimationChannel_8h.md)

[Go to the documentation of this file](AnimationChannel_8h.md)


```C++
//
// Created by Monika on 08.01.2023.
//

#ifndef SR_ENGINE_ANIMATIONCHANNEL_H
#define SR_ENGINE_ANIMATIONCHANNEL_H

#include <Utils/ECS/EntityRefOld.h>

#include <Graphics/Animations/AnimationKey.h>
#include <Graphics/Animations/AnimationContext.h>

struct aiNodeAnim;

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_ANIMATIONS_NS {
    class AnimationKey;
    class AnimationPose;

    class AnimationChannel final : public SR_UTILS_NS::NonCopyable {
        using Keys = std::vector<UnionAnimationKey>;
    public:
        ~AnimationChannel() override;

    public:
        static void Load(SR_HTYPES_NS::RawMesh* pRawMesh, aiNodeAnim* pChannel, float_t ticksPerSecond, std::vector<AnimationChannel*>& channels);

        SR_NODISCARD AnimationChannel* Copy() const noexcept {
            auto&& pChannel = new AnimationChannel();

            for (auto&& key : m_keys) {
                pChannel->m_keys.emplace_back(key);
            }

            pChannel->m_name = m_name;
            pChannel->m_boneIndex = m_boneIndex;

            return pChannel;
        }

        void SetName(SR_UTILS_NS::StringAtom name);
        void SetBoneIndex(uint16_t index) { m_boneIndex = index; }

        template<class T> void AddKey(double_t timePoint, T key) {
            auto&& newKey = m_keys.emplace_back();
            newKey.time = static_cast<float_t>(timePoint);
            newKey.SetData(key);
        }

        SR_NODISCARD uint32_t UpdateChannel(uint32_t keyIndex, float_t time, UpdateContext& context, ChannelUpdateContext& channelContext) const;
        SR_NODISCARD uint32_t UpdateChannelWithWeight(uint32_t keyIndex, float_t time, UpdateContext& context, ChannelUpdateContext& channelContext) const;

    public:
        SR_NODISCARD const Keys& GetKeys() const { return m_keys; }

        SR_NODISCARD SR_FORCE_INLINE SR_UTILS_NS::StringAtom GetGameObjectName() const noexcept { return m_name; }
        SR_NODISCARD SR_FORCE_INLINE uint16_t GetBoneIndex() const noexcept { return m_boneIndex.value_or(SR_UINT16_MAX); }
        SR_NODISCARD SR_FORCE_INLINE bool HasBoneIndex() const noexcept { return m_boneIndex.has_value(); }

    private:
        std::optional<uint16_t> m_boneIndex;
        SR_UTILS_NS::StringAtom m_name;
        Keys m_keys;

    };
}

#endif //SR_ENGINE_ANIMATIONCHANNEL_H
```


