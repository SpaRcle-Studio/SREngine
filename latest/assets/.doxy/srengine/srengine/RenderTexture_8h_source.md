

# File RenderTexture.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**RenderTexture.h**](RenderTexture_8h.md)

[Go to the documentation of this file](RenderTexture_8h.md)


```C++
//
// Created by Monika on 18.07.2022.
//

#ifndef SR_ENGINE_RENDERTEXTURE_H
#define SR_ENGINE_RENDERTEXTURE_H

#include <Utils/Settings.h>
#include <Graphics/Pipeline/TextureHelper.h>

namespace SR_GTYPES_NS {
    class Framebuffer;

    class RenderTexture : public SR_UTILS_NS::Settings {
    private:
        RenderTexture();
        ~RenderTexture() override;

    public:
        static RenderTexture* Load(const SR_UTILS_NS::Path& path);

    protected:
        void ClearSettings() override;
        bool LoadSettings(const SR_XML_NS::Node& node) override;

    private:
        Framebuffer* m_fbo = nullptr;

    };
}

#endif //SR_ENGINE_RENDERTEXTURE_H
```


