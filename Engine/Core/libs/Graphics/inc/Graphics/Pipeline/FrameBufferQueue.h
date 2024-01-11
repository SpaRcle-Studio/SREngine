//
// Created by Monika on 20.07.2023.
//

#ifndef SR_ENGINE_FRAMEBUFFERQUEUE_H
#define SR_ENGINE_FRAMEBUFFERQUEUE_H

#include <Utils/Debug.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class FrameBufferQueue {
        using FrameBuffer = SR_GTYPES_NS::Framebuffer*;
        using Layer = uint32_t;

    public:
        void AddFrameBuffer(FrameBuffer pFrameBuffer, uint32_t layer);
        void AddQueue(FrameBuffer pFrameBuffer, uint32_t queueIndex);

        void Clear();

        SR_NODISCARD bool Contains(FrameBuffer pFrameBuffer);
        SR_NODISCARD bool Contains(FrameBuffer pFrameBuffer, uint32_t layer);
        SR_NODISCARD const std::vector<std::vector<FrameBuffer>>& GetQueues();

    private:
        std::map<FrameBuffer, std::set<Layer>> m_used;
        std::vector<std::vector<FrameBuffer>> m_levels;

    };
}

#endif //SR_ENGINE_FRAMEBUFFERQUEUE_H
