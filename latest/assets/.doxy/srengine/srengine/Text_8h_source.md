

# File Text.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Font**](dir_193e1c173bb6bd0681658b8507d31117.md) **>** [**Text.h**](Text_8h.md)

[Go to the documentation of this file](Text_8h.md)


```C++
//
// Created by Monika on 20.06.2024.
//

#ifndef SR_ENGINE_TEXT_H
#define SR_ENGINE_TEXT_H

#include <Graphics/Types/Vertices.h>
#include <Graphics/Types/Mesh.h>
#include <Utils/Types/UnicodeString.h>

namespace SR_GTYPES_NS {
    class Font;

    class Text : public Mesh {
        SR_CLASS()
        using Super = Mesh;
    public:
        Text();
        ~Text() override;

    public:
        void UseMaterial() override;
        void UseModelMatrix() override;

        void UseSamplers() override;

        SR_NODISCARD MeshType GetMeshType() const noexcept override { return MeshType::Text; }

        SR_NODISCARD bool IsFlatMesh() const noexcept override;

        SR_NODISCARD uint32_t GetIndicesCount() const override { return 6; }

        SR_NODISCARD bool IsCalculatable() const override;
        SR_NODISCARD SR_FORCE_INLINE bool GetKerning() const noexcept { return m_kerning; }
        SR_NODISCARD SR_FORCE_INLINE bool IsDebugEnabled() const noexcept { return m_debug; }
        SR_NODISCARD SR_FORCE_INLINE bool IsPreprocessorEnabled() const noexcept { return m_preprocessor; }
        SR_NODISCARD SR_FORCE_INLINE bool IsLocalizationEnabled() const noexcept { return m_localization; }
        SR_NODISCARD SR_FORCE_INLINE Font* GetFont() const noexcept { return m_font; }
        SR_NODISCARD SR_FORCE_INLINE uint16_t GetFontSize() const noexcept { return m_fontSize; }

        SR_NODISCARD bool IsSupportVBO() const override { return false; }

        SR_NODISCARD SR_UTILS_NS::Path GetFontPath() const noexcept;
        SR_NODISCARD uint32_t GetAtlasWidth() const noexcept { return m_atlasSize.x; }
        SR_NODISCARD uint32_t GetAtlasHeight() const noexcept { return m_atlasSize.y; }

        SR_NODISCARD const SR_HTYPES_NS::UnicodeString& GetText() const { return m_text; }

        void SetText(const std::string& text);
        void SetText(const std::u16string& text);
        void SetText(const std::u32string& text);
        void SetKerning(bool enabled);
        void SetDebug(bool enabled);
        void SetFont(Font* pFont);
        void SetFont(const SR_UTILS_NS::Path& path);
        void SetFontSize(const uint16_t& size);
        void SetUseLocalization(bool enabled);
        void SetUsePreprocessor(bool enabled);

        bool Calculate() override;
        void FreeVideoMemory() override;

    protected:
        void OnTextDirty();
        SR_NODISCARD bool BuildAtlas();

    protected:
        SR_HTYPES_NS::UnicodeString m_text;
        SR_VIRTUAL_PROPERTY
        SR_MATH_NS::UVector2 m_atlasSize;
        uint16_t m_fontSize = 16;
        bool m_is3D = false;
        bool m_kerning = true;
        bool m_debug = false;
        bool m_preprocessor = false;
        bool m_localization = false;

    private:
        int32_t m_id = SR_ID_INVALID;
        Font* m_font = nullptr;

    };
}

#endif //SR_ENGINE_TEXT_H
```


