

# File AnimationClip.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**AnimationClip.h**](AnimationClip_8h.md)

[Go to the documentation of this file](AnimationClip_8h.md)


```C++
//
// Created by Monika on 08.01.2023.
//

#ifndef SR_ENGINE_ANIMATIONCLIP_H
#define SR_ENGINE_ANIMATIONCLIP_H

#include <Graphics/macros.h>

#include <Utils/Resources/IResource.h>

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_ANIMATIONS_NS {
    class AnimationChannel;

    class AnimationClip : public SR_UTILS_NS::IResource {
        SR_CLASS()
        using Super = SR_UTILS_NS::IResource;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<AnimationClip>;

    public:
        AnimationClip();
        ~AnimationClip() override;

    public:
        static std::vector<AnimationClip::Ptr> Load(const SR_UTILS_NS::Path& path, const SR_UTILS_NS::Path& skeleton);
        static AnimationClip::Ptr Load(const SR_UTILS_NS::Path& path, const SR_UTILS_NS::Path& skeleton, SR_UTILS_NS::StringAtom name);

    public:
        SR_NODISCARD const std::vector<AnimationChannel*>& GetChannels() const { return m_channels; }
        SR_NODISCARD bool IsAllowedToRevive() const override { return true; }

        SR_NODISCARD bool IsAllowedMultiInstance() const override { return true; }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetClipName() const noexcept;

        SR_NODISCARD float_t GetDuration() const noexcept { return m_duration; }
        SR_NODISCARD uint32_t GetMaxKeyFrame() const noexcept { return m_maxKeyFrame; }

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        SR_NODISCARD bool LoadChannels(SR_HTYPES_NS::RawMesh* pRawMesh, SR_HTYPES_NS::RawMesh* pSkeleton, const std::string& name);

    private:
        SR_UTILS_NS::Path m_skeletonPath;
        std::vector<AnimationChannel*> m_channels;

        float_t m_duration = 0.f;
        uint32_t m_maxKeyFrame = 0;

    };
}

#endif //SR_ENGINE_ANIMATIONCLIP_H
```


