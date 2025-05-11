

# File FreeTypeDrawContext.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Font**](dir_0f9fa5c8aefacabb9ad499652a4f09bc.md) **>** [**FreeTypeDrawContext.h**](FreeTypeDrawContext_8h.md)

[Go to the documentation of this file](FreeTypeDrawContext_8h.md)


```C++
//
// Created by Monika on 06.11.2022.
//

#ifndef SR_ENGINE_FREETYPEDRAWCONTEXT_H
#define SR_ENGINE_FREETYPEDRAWCONTEXT_H

#include <Graphics/Font/FreeType.h>
#include <Utils/Common/NonCopyable.h>

namespace SR_GRAPH_NS {
    class FreeTypeFace;

    class FreeTypeDrawContext : public SR_UTILS_NS::NonCopyable {
        friend class FreeTypeFace;
    public:
        FreeTypeDrawContext() = default;
        ~FreeTypeDrawContext() override = default;
        FreeTypeDrawContext(const FreeTypeDrawContext&) = delete;
        FreeTypeDrawContext& operator=(const FreeTypeDrawContext&) = delete;

    public:
        SR_NODISCARD uint8_t* Bitmap() noexcept {
            if (m_bitmap.empty() && m_width > 0 && m_height > 0) {
                m_bitmap.resize(m_width * m_height * 4);
            }

            if (m_bitmap.empty()) {
                return nullptr;
            }

            return &m_bitmap[0];
        }

        SR_NODISCARD uint32_t Width() const noexcept { return m_width; }
        SR_NODISCARD uint32_t Height() const noexcept { return m_height; }

        void Align(int align) {
            m_width += align;
        }

        void NextLine(int valign) {
            m_height += valign + m_maxGlyphHeight;
        }

    private:
        uint32_t m_tmpWidth = 0;
        uint32_t m_tmpHeight = 0;

        uint32_t m_maxGlyphHeight = 0;
        uint32_t m_topRow = 0;

        uint32_t m_width = 0;
        uint32_t m_height = 0;

        std::vector<uint8_t> m_bitmap;

    };
}

#endif //SR_ENGINE_FREETYPEDRAWCONTEXT_H
```


