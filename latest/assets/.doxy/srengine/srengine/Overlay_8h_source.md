

# File Overlay.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Overlay**](dir_32af8277f8900af675cc0c06167c7d00.md) **>** [**Overlay.h**](Overlay_8h.md)

[Go to the documentation of this file](Overlay_8h.md)


```C++
//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_OVERLAY_H
#define SR_ENGINE_GRAPHICS_OVERLAY_H

#include <Graphics/macros.h>

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


