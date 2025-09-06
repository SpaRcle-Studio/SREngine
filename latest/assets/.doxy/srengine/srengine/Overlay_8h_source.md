

# File Overlay.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Overlay**](dir_4a8795eb8ad690bf07364b6c276aac2d.md) **>** [**Overlay.h**](Overlay_8h.md)

[Go to the documentation of this file](Overlay_8h.md)


```C++
//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_OVERLAY_H
#define SR_ENGINE_GRAPHICS_OVERLAY_H

#include <Graphics/Overlay/OverlayType.h>

namespace SR_GRAPH_NS {
    class Pipeline;

    class Overlay : public SR_HTYPES_NS::SharedPtr<Overlay> {
    public:
        using Super = SR_HTYPES_NS::SharedPtr<Overlay>;
        using Ptr = SR_HTYPES_NS::SharedPtr<Overlay>;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;

    public:
        explicit Overlay(PipelinePtr pPipeline);

    public:
        SR_NODISCARD virtual bool Init() = 0;
        SR_NODISCARD virtual bool IsUndockingActive() const = 0;
        SR_NODISCARD virtual bool IsDynamicRenderingEnabled() const = 0;
        SR_NODISCARD virtual bool ReCreate() = 0;
        SR_NODISCARD bool IsSurfaceDirty() const noexcept { return m_surfaceDirty; }
        SR_NODISCARD bool IsEnabled() const noexcept { return m_enabled; }
        SR_NODISCARD const PipelinePtr& GetPipeline() const noexcept { return m_pipeline; }

        SR_NODISCARD virtual void* GetTextureDescriptorSet(uint32_t textureId) { return nullptr; }
        SR_NODISCARD virtual std::string GetName() const = 0;

        virtual void Destroy() = 0;

        virtual void Prepare() { }
        virtual bool BeginDraw() = 0;
        virtual void EndDraw() = 0;

        void SetEnabled(bool enabled) { m_enabled = enabled; }
        void SetSurfaceDirty() { m_surfaceDirty = true; }

    protected:
        PipelinePtr m_pipeline;

        bool m_enabled = true;
        bool m_initialized = false;
        bool m_surfaceDirty = true;
        bool m_tracyEnabled = false;

    };
}

#endif //SR_ENGINE_GRAPHICS_OVERLAY_H
```


