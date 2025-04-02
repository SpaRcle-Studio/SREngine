

# File IRenderer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Render**](dir_5ea2fe9b8fa53724ec2c57fac60d8202.md) **>** [**IRenderer.h**](IRenderer_8h.md)

[Go to the documentation of this file](IRenderer_8h.md)


```C++
//
// Created by Monika on 05.01.2025.
//

#ifndef SR_GRAPHICS_RENDER_I_RENDERER_H
#define SR_GRAPHICS_RENDER_I_RENDERER_H

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


