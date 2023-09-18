//
// Created by Monika on 08.01.2023.
//

#ifndef SRENGINE_ANIMATIONCLIP_H
#define SRENGINE_ANIMATIONCLIP_H

#include <Utils/ResourceManager/IResource.h>

class aiAnimation;

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_ANIMATIONS_NS {
    class AnimationChannel;

    class AnimationClip : public SR_UTILS_NS::IResource {
        using Super = SR_UTILS_NS::IResource;
    public:
        AnimationClip();
        ~AnimationClip() override;

    public:
        static std::vector<AnimationClip*> Load(const SR_UTILS_NS::Path& path);
        static AnimationClip* Load(const SR_UTILS_NS::Path& path, uint32_t id);

    public:
        SR_NODISCARD const std::vector<AnimationChannel*>& GetChannels() const { return m_channels; }
        SR_NODISCARD bool IsAllowedToRevive() const override { return true; }

        SR_NODISCARD SR_UTILS_NS::Path InitializeResourcePath() const override;

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        void LoadChannels(SR_HTYPES_NS::RawMesh* pRawMesh, uint32_t index);

    private:
        std::vector<AnimationChannel*> m_channels;

    };
}

#endif //SRENGINE_ANIMATIONCLIP_H
