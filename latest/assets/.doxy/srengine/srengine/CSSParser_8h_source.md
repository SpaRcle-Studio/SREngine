

# File CSSParser.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Web**](dir_70f8c8659136766207f9e88b26ae6fb0.md) **>** [**CSS**](dir_c67fdec84752b754610b5eee0005e4af.md) **>** [**CSSParser.h**](CSSParser_8h.md)

[Go to the documentation of this file](CSSParser_8h.md)


```C++
//
// Created by Monika on 20.08.2024.
//

#ifndef SR_COMMON_WEB_CSS_PARSER_H
#define SR_COMMON_WEB_CSS_PARSER_H

#include <Utils/Web/CSS/CSS.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS::Web {
    struct CSSParserContext {
        static CSSParserContext GetDefault() {
            static CSSParserContext context;
            return context;
        }

        CSSSizeValue maxWidth = 0;
        CSSSizeValue maxHeight = 0;
    };

    class CSSParser : public SR_UTILS_NS::Singleton<CSSParser> {
        SR_REGISTER_SINGLETON(CSSParser)
    public:
        SR_NODISCARD CSS::Ptr Parse(const Path& path, const CSSParserContext& context = CSSParserContext::GetDefault());
        SR_NODISCARD CSS::Ptr Parse(const std::string& data, const CSSParserContext& context = CSSParserContext::GetDefault());

    private:
        bool EvaluateMedia(const std::string& media, const CSSParserContext& context) const;

    private:
        CSS::Ptr m_pCSS = nullptr;

    };
}

#endif //SR_COMMON_WEB_CSS_PARSER_H
```


