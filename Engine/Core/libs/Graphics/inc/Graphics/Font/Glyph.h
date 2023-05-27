//
// Created by Monika on 24.05.2023.
//

#ifndef SRENGINE_GLYPH_H
#define SRENGINE_GLYPH_H

#include <Utils/Common/NonCopyable.h>
#include <Graphics/Font/FreeType.h>

namespace SR_GRAPH_NS {
    struct GlyphMetrics {
        /// Позиция по горизонтали
        int32_t posX = 0;
        /// Позиция по вертикали (от базовой линии)
        int32_t posY = 0;
        /// Ширина глифа
        int32_t width = 0;
        /// Высота глифа
        int32_t height = 0;

        int32_t left = 0;
        int32_t top = 0;

        int32_t advanceX = 0;
        int32_t advanceY = 0;
    };

    class Glyph : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;
        using Ptr = std::shared_ptr<Glyph>;

    public:
        Glyph(FT_Glyph pGlyph, FT_Render_Mode renderMode);
        ~Glyph() override;

    public:
        SR_NODISCARD int32_t GetPosX() const noexcept;
        SR_NODISCARD int32_t GetPosY() const noexcept;
        SR_NODISCARD uint32_t GetSize() const noexcept;
        SR_NODISCARD uint32_t GetWidth() const noexcept;
        SR_NODISCARD uint32_t GetHeight() const noexcept;
        SR_NODISCARD uint32_t GetPixelSize() const noexcept;
        SR_NODISCARD FT_Glyph GetGlyph() const noexcept;
        SR_NODISCARD GlyphMetrics& GetMetrics() noexcept;

    private:
        FT_Render_Mode m_renderMode;
        GlyphMetrics m_metrics = { };
        FT_Glyph m_glyph = nullptr;

    };

    class GlyphImage : public SR_UTILS_NS::NonCopyable {
    public:
        using Ptr = std::shared_ptr<GlyphImage>;

    private:
        GlyphImage() = default;

    public:
        SR_NODISCARD static GlyphImage::Ptr Create(const Glyph::Ptr& pGlyph);
        SR_NODISCARD uint8_t* GetData() const { return m_data.get(); }

        void InsertTo(uint8_t* pTarget, int32_t top, uint32_t sizeX, bool debug);

    private:
        SR_NODISCARD bool Init();

    private:
        std::shared_ptr<uint8_t[]> m_data;
        Glyph::Ptr m_glyph;

    };
}

#endif //SRENGINE_GLYPH_H
