//
// Created by Monika on 08.01.2023.
//

#ifndef SRENGINE_ANIMATIONCLIP_H
#define SRENGINE_ANIMATIONCLIP_H

#include <Utils/ResourceManager/IResource.h>

class aiAnimation;

namespace SR_ANIMATIONS_NS {
    class AnimationChannel;

    class AnimationClip : public SR_UTILS_NS::NonCopyable {
    public:
        ~AnimationClip() override;

    public:
        static AnimationClip* Load(const SR_UTILS_NS::Path& rawPath, uint32_t index);
        static std::vector<AnimationClip*> Load(const SR_UTILS_NS::Path& rawPath);
        static AnimationClip* Load(aiAnimation* pAnimation);

    public:
        SR_NODISCARD const std::vector<AnimationChannel*>& GetChannels() const { return m_channels; }

    private:
        std::vector<AnimationChannel*> m_channels;

    };
}

#endif //SRENGINE_ANIMATIONCLIP_H
