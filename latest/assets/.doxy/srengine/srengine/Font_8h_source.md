

# File Font.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Font**](dir_0f9fa5c8aefacabb9ad499652a4f09bc.md) **>** [**Font.h**](Font_8h.md)

[Go to the documentation of this file](Font_8h.md)


```C++
//
// Created by Monika on 14.02.2022.
//

#ifndef SR_ENGINE_FONT_H
#define SR_ENGINE_FONT_H

#include <Graphics/macros.h>

#include <Utils/Resources/IResource.h>
#include <Graphics/Font/FreeType.h>

namespace SR_GTYPES_NS {
    class SR_RENDERER_DLL_API Font : public SR_UTILS_NS::IResource {
        SR_CLASS()
        using Super = SR_UTILS_NS::IResource;
        using FontLibrary = FT_Library;
        using FontFace = FT_Face;
        using StringType = std::u32string;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Font>;

    public:
        Font();
        ~Font() override = default;

    public:
        static Font::Ptr Load(const SR_UTILS_NS::Path& rawPath);

        SR_NODISCARD bool HasColor() const noexcept { return m_hasColor; }
        SR_NODISCARD bool IsColorEmoji() const noexcept { return m_isColorEmoji; }

        SR_NODISCARD FT_Glyph GetGlyph(char32_t code, FT_Render_Mode renderMode, FT_Int32 charLoad, FT_Int32 glyphLoad) const;
        SR_NODISCARD FT_Glyph GetGlyph(char32_t code, FT_Render_Mode renderMode) const;

        SR_NODISCARD FT_Pos GetKerning(uint32_t leftCharCode, uint32_t rightCharCode) const;

        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;

        bool SetPixelSizes(uint32_t w, uint32_t h);
        bool SetCharSize(uint32_t w, uint32_t h, uint32_t wRes, uint32_t hRes);

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        FontLibrary m_library = nullptr;
        FontFace m_face = nullptr;

        bool m_hasColor = false;
        bool m_isColorEmoji = false;

    };
}

#endif //SR_ENGINE_FONT_H
```


