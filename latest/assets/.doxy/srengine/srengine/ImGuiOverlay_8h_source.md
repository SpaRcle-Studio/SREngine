

# File ImGuiOverlay.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Overlay**](dir_32af8277f8900af675cc0c06167c7d00.md) **>** [**ImGuiOverlay.h**](ImGuiOverlay_8h.md)

[Go to the documentation of this file](ImGuiOverlay_8h.md)


```C++
//
// Created by Monika on 15.09.2023.
//

#ifndef SR_ENGINE_GRAPHICS_IMGUI_OVERLAY_H
#define SR_ENGINE_GRAPHICS_IMGUI_OVERLAY_H

#include <Graphics/Overlay/Overlay.h>

struct ImFont;
struct ImGuiContext;

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

        SR_NODISCARD ImFont* GetIconFont() const { return m_iconFont; }
        SR_NODISCARD ImFont* GetMainFont() const { return m_mainFont; }

        void Prepare() override;
        void Destroy() override;

    protected:
        virtual void ReloadFonts();

    protected:
        ImGuiContext* m_context = nullptr;
        ImFont* m_mainFont = nullptr;
        ImFont* m_iconFont = nullptr;

        float_t m_fontSize = 12.0f;
        float_t m_iconFontSize = 40.0f;

        SR_UTILS_NS::Path m_iniPathEditor;
        SR_UTILS_NS::Path m_iniPathWidgets;

    };
}

#endif //SR_ENGINE_GRAPHICS_IMGUI_OVERLAY_H
```


