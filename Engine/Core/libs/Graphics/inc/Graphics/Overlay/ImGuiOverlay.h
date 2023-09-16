//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_IMGUI_OVERLAY_H
#define SR_ENGINE_GRAPHICS_IMGUI_OVERLAY_H

#include <Graphics/Overlay/Overlay.h>

class ImFont;
class ImGuiContext;

namespace SR_GRAPH_NS {
    class ImGuiOverlay : public Overlay {
        using Super = Overlay;
    public:
        explicit ImGuiOverlay(PipelinePtr pPipeline)
            : Super(std::move(pPipeline))
        { }

    public:
        SR_NODISCARD bool Init() override;
        SR_NODISCARD bool IsUndockingActive() const override;

        SR_NODISCARD ImFont* GetIconFont() const { return m_iconFont; }
        SR_NODISCARD ImFont* GetMainFont() const { return m_mainFont; }

        void Destroy() override;

    protected:
        ImGuiContext* m_context = nullptr;
        ImFont* m_mainFont = nullptr;
        ImFont* m_iconFont = nullptr;

        SR_UTILS_NS::Path m_iniPathEditor;
        SR_UTILS_NS::Path m_iniPathWidgets;

    };
}

#endif //SR_ENGINE_GRAPHICS_IMGUI_OVERLAY_H
