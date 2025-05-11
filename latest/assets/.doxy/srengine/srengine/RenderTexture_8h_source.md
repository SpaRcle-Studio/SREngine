

# File RenderTexture.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**RenderTexture.h**](RenderTexture_8h.md)

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


