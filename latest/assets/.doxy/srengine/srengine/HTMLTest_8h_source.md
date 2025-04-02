

# File HTMLTest.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**Tests**](dir_a438f77ea296cf9ed84cc5f25e2e6a4d.md) **>** [**HTMLTest.h**](HTMLTest_8h.md)

[Go to the documentation of this file](HTMLTest_8h.md)


```C++
//
// Created by Monika on 15.08.2024.
//

#ifndef SR_ENGINE_CORE_HTML_TEST_H
#define SR_ENGINE_CORE_HTML_TEST_H

#include <Utils/Resources/ResourceManager.h>
#include <Utils/Web/HTML/HTMLParser.h>
#include <Utils/Web/CSS/CSSParser.h>

namespace SR_CORE_NS::Tests {
    class HTMLTest {
    public:
        static bool Run() {
            const SR_UTILS_NS::Path path = "Tests/editor.html";
            //auto&& pPage = SR_UTILS_NS::Web::HTMLParser::Instance().Parse(path);
            //const std::string text = SR_UTILS_NS::Web::HTMLParser::Instance().DebugPageTostring(pPage);
            //SR_DEBUG_LOG("{}", text);
            return true;
        }
    };

    class CSSTest {
    public:
        static bool Run() {
            const SR_UTILS_NS::Path path = "Tests/editor.css";
            //auto&& pCSS = SR_UTILS_NS::Web::CSSParser::Instance().Parse(path);
            //const std::string text = pCSS->ToString();
            //SR_DEBUG_LOG("{}", text);
            return true;
        }
    };
}

#endif //SR_ENGINE_CORE_HTML_TEST_H
```


