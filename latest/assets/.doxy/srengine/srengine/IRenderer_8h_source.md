

# File IRenderer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**IRenderer.h**](IRenderer_8h.md)

[Go to the documentation of this file](IRenderer_8h.md)


```C++
//
// Created by Monika on 05.01.2025.
//

#ifndef SR_GRAPHICS_RENDER_I_RENDERER_H
#define SR_GRAPHICS_RENDER_I_RENDERER_H

#include <Graphics/macros.h>

#include <Utils/Types/SharedPtr.h>
#include <Utils/TypeTraits/SRClass.h>

namespace SR_GRAPH_NS {
    class RenderScene;

    class IRenderer : public SR_UTILS_NS::SRClass, public SR_HTYPES_NS::SharedPtr<IRenderer> {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<IRenderer>;

        explicit IRenderer()
            : SR_UTILS_NS::SRClass()
            , SR_HTYPES_NS::SharedPtr<IRenderer>(this, SR_UTILS_NS::SharedPtrPolicy::Manually)
        { }

    public:
        SR_NODISCARD RenderScene* GetRenderScene() const noexcept { return m_renderScene; }

        void SetRenderScene(RenderScene* pRenderScene) noexcept { m_renderScene = pRenderScene; }

        virtual void Clear() { }
        virtual void Init() { }
        virtual void DeInit() { }
        virtual void Prepare() { }
        virtual void PostUpdate() { }
        virtual bool IsEmpty() const noexcept { return true; }

    protected:
        mutable std::recursive_mutex m_mutex;

    private:
        RenderScene* m_renderScene = nullptr;

    };
}

#endif //SR_GRAPHICS_RENDER_I_RENDERER_H
```


