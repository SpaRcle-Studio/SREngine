//
// Created by Monika on 16.05.2023.
//

#ifndef SRENGINE_FRAMEBUFFERSMANAGER_H
#define SRENGINE_FRAMEBUFFERSMANAGER_H

#include <Utils/Common/Singleton.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class FramebuffersManager : public SR_UTILS_NS::Singleton<FramebuffersManager> {
        friend class SR_UTILS_NS::Singleton<FramebuffersManager>;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
    public:
        void Register(const FramebufferPtr& pFramebuffer);
        void UnRegister(const FramebufferPtr& pFramebuffer);

        void SetDirty();

    private:
        std::unordered_set<FramebufferPtr> m_framebuffers;

    };
}

#endif //SRENGINE_FRAMEBUFFERSMANAGER_H
