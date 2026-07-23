//
// Created by Monika on 15.07.2026.
//

#include <ImmediateGUI/Backend/WebGPURenderer.h>
#include <ImmediateGUI/Impl/ImGUI.h>

#if defined(SR_USE_IMGUI) && defined(SR_EMSCRIPTEN)

namespace SR_GRAPH_GUI_NS::Immediate {
    namespace {
        struct WebGPURenderer {
            WebGPURendererCreateInfo info;
            bool initialized = false;
        };
    }

    WebGPURendererHandle WebGPUCreateRenderer(const WebGPURendererCreateInfo& info) {
        if (!info.device || info.renderTargetFormat == WGPUTextureFormat_Undefined) {
            return nullptr;
        }

        auto* pRenderer = new WebGPURenderer();
        pRenderer->info = info;

        ImGui_ImplWGPU_InitInfo initInfo;
        initInfo.Device = info.device;
        initInfo.NumFramesInFlight = info.numFramesInFlight;
        initInfo.RenderTargetFormat = info.renderTargetFormat;
        initInfo.DepthStencilFormat = info.depthStencilFormat;

        if (!ImGui_ImplWGPU_Init(&initInfo)) {
            delete pRenderer;
            return nullptr;
        }

        pRenderer->initialized = true;
        return pRenderer;
    }

    void WebGPUDestroyRenderer(WebGPURendererHandle renderer) {
        if (!renderer) {
            return;
        }

        auto* pRenderer = static_cast<WebGPURenderer*>(renderer);

        if (pRenderer->initialized) {
            ImGui_ImplWGPU_Shutdown();
        }

        delete pRenderer;
    }

    void WebGPUNewFrame(WebGPURendererHandle renderer) {
        if (!renderer) {
            return;
        }

        ImGui_ImplWGPU_NewFrame();
    }

    void WebGPURenderDrawData(WebGPURendererHandle renderer, WGPURenderPassEncoder pass) {
        if (!renderer || !pass) {
            return;
        }

        ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), pass);
    }

    void WebGPUReloadFonts(WebGPURendererHandle renderer) {
        if (!renderer) {
            return;
        }

        // On ImGui 1.92+ with RendererHasTextures, the WGPU backend will honor this request
        // during ImGui_ImplWGPU_RenderDrawData() (via draw_data->Textures updates).
        ImGuiIO& io = ImGui::GetIO();
        if (io.Fonts && io.Fonts->TexData) {
            io.Fonts->TexData->SetStatus(ImTextureStatus_WantCreate);
        }
    }
}

#endif // SR_USE_IMGUI && SR_EMSCRIPTEN
