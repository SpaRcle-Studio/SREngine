//
// Created by Monika on 18.07.2022.
//

#ifndef SRENGINE_RENDERTEXTURE_H
#define SRENGINE_RENDERTEXTURE_H

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

#endif //SRENGINE_RENDERTEXTURE_H
