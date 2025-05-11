

# File FrameBufferQueue.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pipeline**](dir_b95270d167403b29f5d572cffd5b214a.md) **>** [**FrameBufferQueue.h**](FrameBufferQueue_8h.md)

[Go to the documentation of this file](FrameBufferQueue_8h.md)


```C++
//
// Created by Monika on 20.07.2023.
//

#ifndef SR_ENGINE_FRAMEBUFFERQUEUE_H
#define SR_ENGINE_FRAMEBUFFERQUEUE_H

#include <Graphics/macros.h>

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

        SR_NODISCARD bool IsAllowMultiFrameBuffers() const;

        SR_NODISCARD bool Contains(FrameBuffer pFrameBuffer);
        SR_NODISCARD bool Contains(FrameBuffer pFrameBuffer, uint32_t layer);
        SR_NODISCARD const std::vector<std::vector<FrameBuffer>>& GetQueues() const;

    private:
        std::map<FrameBuffer, std::set<Layer>> m_used;
        std::vector<std::vector<FrameBuffer>> m_levels;

    };
}

#endif //SR_ENGINE_FRAMEBUFFERQUEUE_H
```


