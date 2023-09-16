//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_OVERLAY_H
#define SR_ENGINE_GRAPHICS_OVERLAY_H

#include <Graphics/Overlay/OverlayType.h>

namespace SR_GRAPH_NS {
    class Pipeline;

    /**
     *  --------------------------------------------------------
     *  | Base overlay | Type of overlay | Overlay renderer    |
     *  | Overlay     -> TypeOverlay    -> RendererTypeOverlay |
     *  | Overlay     -> ImGuiOverlay   -> VulkanImGuiOverlay  |
     *  --------------------------------------------------------
     */

    class Overlay : public SR_HTYPES_NS::SharedPtr<Overlay> {
    public:
        using Super = SR_HTYPES_NS::SharedPtr<Overlay>;
        using Ptr = SR_HTYPES_NS::SharedPtr<Overlay>;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;

    public:
        explicit Overlay(PipelinePtr pPipeline);
        virtual ~Overlay() = default;

    public:
        SR_NODISCARD virtual bool Init() = 0;
        SR_NODISCARD virtual bool IsUndockingActive() const = 0;
        SR_NODISCARD virtual bool ReCreate() = 0;
        SR_NODISCARD bool IsSurfaceDirty() const noexcept { return m_surfaceDirty; }

        SR_NODISCARD virtual std::string GetName() const = 0;

        virtual void Destroy() = 0;

        virtual bool BeginDraw() = 0;
        virtual void EndDraw() = 0;

        void SetSurfaceDirty() { m_surfaceDirty = true; }

    protected:
        PipelinePtr m_pipeline;

        bool m_initialized = false;
        bool m_surfaceDirty = true;
        bool m_tracyEnabled = false;

    };
}

#endif //SR_ENGINE_GRAPHICS_OVERLAY_H
