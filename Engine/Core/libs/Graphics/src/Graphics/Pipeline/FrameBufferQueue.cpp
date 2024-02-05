//
// Created by Monika on 20.07.2023.
//

#include <Graphics/Pipeline/FrameBufferQueue.h>
#include <Graphics/Types/Framebuffer.h>

namespace SR_GRAPH_NS {
    void FrameBufferQueue::AddFrameBuffer(FrameBufferQueue::FrameBuffer pFrameBuffer, uint32_t layer) {
        auto&& pIt = m_used.find(pFrameBuffer);
        if (pIt == m_used.end()) {
            m_used.insert(std::make_pair(pFrameBuffer, std::set { layer }));
        }
        else {
            pIt->second.insert(layer);
        }
    }

    const std::vector<std::vector<FrameBufferQueue::FrameBuffer>>& FrameBufferQueue::GetQueues() {
        return m_levels;
    }

    bool FrameBufferQueue::Contains(FrameBufferQueue::FrameBuffer pFrameBuffer, uint32_t layer) {
        if (IsAllowMultiFrameBuffers()) {
            return false;
        }

        if (auto&& pIt = m_used.find(pFrameBuffer); pIt != m_used.end()) {
            return pIt->second.count(layer) == 1;
        }

        return false;
    }

    bool FrameBufferQueue::Contains(FrameBufferQueue::FrameBuffer pFrameBuffer) {
        if (IsAllowMultiFrameBuffers()) {
            return false;
        }
        return m_used.find(pFrameBuffer) != m_used.end();
    }

    void FrameBufferQueue::Clear() {
        m_used.clear();
        m_levels.clear();
    }

    void FrameBufferQueue::AddQueue(FrameBufferQueue::FrameBuffer pFrameBuffer, uint32_t queueIndex) {
        if (m_levels.size() <= queueIndex) {
            m_levels.resize(queueIndex + 1);
        }
        m_levels[queueIndex].emplace_back(pFrameBuffer);
    }

    bool FrameBufferQueue::IsAllowMultiFrameBuffers() const {
        return true;
    }
}
