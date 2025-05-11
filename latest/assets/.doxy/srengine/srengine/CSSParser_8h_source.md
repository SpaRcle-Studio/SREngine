

# File CSSParser.h

[**File List**](files.md) **>** [**CSS**](dir_8392c415e30628e2ce7c2879273a6118.md) **>** [**CSSParser.h**](CSSParser_8h.md)

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


