//
// Created by Monika on 15.07.2026.
//

#ifndef SR_ENGINE_IMMEDIATE_GUI_WEBGPU_RENDERER_H
#define SR_ENGINE_IMMEDIATE_GUI_WEBGPU_RENDERER_H

#include <ImmediateGUI/stdInclude.h>

#if defined(SR_USE_IMGUI) && defined(SR_EMSCRIPTEN)

#include <webgpu/webgpu.h>

namespace SR_GRAPH_GUI_NS::Immediate {
    struct SR_IMMEDIATE_GUI_DLL_API WebGPURendererCreateInfo {
        WGPUDevice device = nullptr;

        int32_t numFramesInFlight = 3;

        WGPUTextureFormat renderTargetFormat = WGPUTextureFormat_Undefined;
        WGPUTextureFormat depthStencilFormat = WGPUTextureFormat_Undefined;
    };

    using WebGPURendererHandle = void*;

    SR_IMMEDIATE_GUI_DLL_API extern WebGPURendererHandle WebGPUCreateRenderer(const WebGPURendererCreateInfo& info);
    SR_IMMEDIATE_GUI_DLL_API extern void WebGPUDestroyRenderer(WebGPURendererHandle renderer);

    /// Call once per ImGui frame before ImGui::NewFrame().
    SR_IMMEDIATE_GUI_DLL_API extern void WebGPUNewFrame(WebGPURendererHandle renderer);

    /// Records draw data into provided pass.
    SR_IMMEDIATE_GUI_DLL_API extern void WebGPURenderDrawData(WebGPURendererHandle renderer, WGPURenderPassEncoder pass);

    SR_IMMEDIATE_GUI_DLL_API extern void WebGPUReloadFonts(WebGPURendererHandle renderer);
}

#endif // SR_USE_IMGUI && SR_EMSCRIPTEN

#endif // SR_ENGINE_IMMEDIATE_GUI_WEBGPU_RENDERER_H
