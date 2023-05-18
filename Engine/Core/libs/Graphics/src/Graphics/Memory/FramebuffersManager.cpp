//
// Created by Monika on 16.05.2023.
//

#include <Graphics/Memory/FramebuffersManager.h>

namespace SR_GRAPH_NS {
    void FramebuffersManager::Register(const FramebufferPtr& pFramebuffer) {
        SR_LOCK_GUARD

        if (m_framebuffers.count(pFramebuffer) == 1) {
            SRHalt("Double registration!");
            return;
        }

        m_framebuffers.insert(pFramebuffer);
    }

    void FramebuffersManager::UnRegister(const FramebufferPtr& pFramebuffer) {
        SR_LOCK_GUARD

        if (m_framebuffers.count(pFramebuffer) == 0) {
            SRHalt("Framebuffer is not registered!");
            return;
        }

        m_framebuffers.erase(pFramebuffer);
    }

    void FramebuffersManager::SetDirty() {
        SR_LOCK_GUARD

        for (auto&& pFramebuffer : m_framebuffers) {
            pFramebuffer->SetDirty();
        }
    }
}