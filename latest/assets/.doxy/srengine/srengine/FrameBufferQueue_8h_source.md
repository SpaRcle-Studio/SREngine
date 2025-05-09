

# File FrameBufferQueue.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pipeline**](dir_5b8a811d805f0a9bb3b25de386a42645.md) **>** [**FrameBufferQueue.h**](FrameBufferQueue_8h.md)

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


