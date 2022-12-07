//
// Created by Monika on 07.12.2022.
//

#include <Graphics/Window/BasicWindowImpl.h>

#if defined(SR_WIN32)
    #include <Graphics/Window/Win32Window.h>
#endif

namespace SR_GRAPH_NS {
    void BasicWindowImpl::SetResizeCallback(const ResizeCallback& callback) {
        m_resizeCallback = callback;
    }

    void BasicWindowImpl::SetMoveCallback(const MoveCallback& callback) {
        m_moveCallback = callback;
    }

    void BasicWindowImpl::SetScrollCallback(const ScrollCallback& callback) {
        m_scrollCallback = callback;
    }

    void BasicWindowImpl::SetFocusCallback(const FocusCallback& callback) {
        m_focusCallback = callback;
    }

    void BasicWindowImpl::SetCloseCallback(const CloseCallback& callback) {
        m_closeCallback = callback;
    }

    BasicWindowImpl* BasicWindowImpl::CreatePlatformWindow(PipelineType pipelineType, BasicWindowImpl::WindowType type) {
    #if defined(SR_WIN32)
        switch (type) {
            case WindowType::Auto:
            case WindowType::Win32:
                return new Win32Window(pipelineType);
            default:
                break;
        }

        SR_ERROR("BasicWindowImpl::CreatePlatformWindow() : OS Windows not support \"" +
            SR_UTILS_NS::EnumReflector::ToString(type) + "\" window!"
        );
    #else
        SR_ERROR("BasicWindowImpl::CreatePlatformWindow() : unsupported OS!");
    #endif

        return nullptr;
    }
}
