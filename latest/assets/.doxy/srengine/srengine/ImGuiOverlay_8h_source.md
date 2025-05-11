

# File ImGuiOverlay.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Overlay**](dir_4a8795eb8ad690bf07364b6c276aac2d.md) **>** [**ImGuiOverlay.h**](ImGuiOverlay_8h.md)

[Go to the documentation of this file](ImGuiOverlay_8h.md)


```C++
//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_IMGUI_OVERLAY_H
#define SR_ENGINE_GRAPHICS_IMGUI_OVERLAY_H

#include <Graphics/macros.h>

#include <Graphics/Overlay/Overlay.h>

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
        SR_NODISCARD bool IsViewportsEnabled() const;

        SR_NODISCARD void* GetIconFont() const { return m_iconFont; }
        SR_NODISCARD void* GetMainFont() const { return m_mainFont; }

        void Prepare() override;
        void Destroy() override;

    protected:
        virtual void ReloadFonts();

    protected:
        void* m_context = nullptr;
        void* m_mainFont = nullptr;
        void* m_iconFont = nullptr;

        float_t m_fontSize = 12.0f;
        float_t m_iconFontSize = 40.0f;

        SR_UTILS_NS::Path m_iniPathEditor;
        SR_UTILS_NS::Path m_iniPathWidgets;

    };
}

#endif //SR_ENGINE_GRAPHICS_IMGUI_OVERLAY_H
```


