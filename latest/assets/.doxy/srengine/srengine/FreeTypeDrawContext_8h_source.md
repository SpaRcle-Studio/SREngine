

# File FreeTypeDrawContext.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Font**](dir_193e1c173bb6bd0681658b8507d31117.md) **>** [**FreeTypeDrawContext.h**](FreeTypeDrawContext_8h.md)

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


