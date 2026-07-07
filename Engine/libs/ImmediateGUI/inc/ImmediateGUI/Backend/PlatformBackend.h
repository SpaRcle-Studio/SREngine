//
// Created by Monika on 07.07.2026.
//

#ifndef SR_ENGINE_IMMEDIATE_GUI_PLATFORM_BACKEND_H
#define SR_ENGINE_IMMEDIATE_GUI_PLATFORM_BACKEND_H

#include <ImmediateGUI/stdInclude.h>

#include <Utils/Math/Vector2.h>

namespace SR_GRAPH_GUI_NS::Immediate {
    enum class PlatformBackend : uint8_t {
        None = 0,
        Win32,
        GLFW,
        Android,
        WaylandCustom
    };

    struct SR_IMMEDIATE_GUI_DLL_API PlatformInitInfo {
        PlatformBackend backend = PlatformBackend::None;

        /// For Win32: HWND
        /// For GLFW: GLFWwindow*
        /// For Android: ANativeWindow*
        void* window = nullptr;
    };

    struct SR_IMMEDIATE_GUI_DLL_API PlatformNewFrameInfo {
        /// Used by custom Wayland backend. Other backends ignore it.
        SR_MATH_NS::FVector2 displaySize = SR_MATH_NS::FVector2(0.f, 0.f);
        SR_MATH_NS::FVector2 framebufferScale = SR_MATH_NS::FVector2(1.f, 1.f);
        float_t deltaTime = 1.0f / 60.0f;
    };

    SR_IMMEDIATE_GUI_DLL_API extern bool PlatformInit(const PlatformInitInfo& info);
    SR_IMMEDIATE_GUI_DLL_API extern void PlatformShutdown(PlatformBackend backend);
    SR_IMMEDIATE_GUI_DLL_API extern void PlatformNewFrame(PlatformBackend backend, const PlatformNewFrameInfo& info = PlatformNewFrameInfo());
}

#endif // SR_ENGINE_IMMEDIATE_GUI_PLATFORM_BACKEND_H
