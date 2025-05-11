

# File Tag.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Web**](dir_1edd94f8cff42d6094453f2baf1e13fd.md) **>** [**HTML**](dir_cb6460e35697e7553b43ae6c998f1fd7.md) **>** [**Tag.h**](Tag_8h.md)

[Go to the documentation of this file](Tag_8h.md)


```C++
//
// Created by Monika on 16.08.2024.
//

#ifndef SR_COMMON_WEB_HTML_TAG_H
#define SR_COMMON_WEB_HTML_TAG_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Common/StringAtomLiterals.h>

namespace SR_UTILS_NS::Web {
    enum class HTMLTag {
        Undefined,
        Div, Span,
        P, H1, H2, H3, H4, H5, H6, A,
        Img, Input, Button, Form, Label, Select, Option, Textarea, Table,
        Tr, Td, Th, Thead, Tbody, Tfoot, Ul, Ol, Li, Dl, Dt, Dd,
        Br, Hr, Meta, Link, Style, Script, Title, Head, Body, Html, Text, Header,
        MAX_SIZE
    };

    SR_INLINE_STATIC SR_UTILS_NS::StringAtom UndefinedTag = "undef"_atom;

    SR_NODISCARD HTMLTag MyHTMLTagToHTMLTag(size_t tag);

    SR_NODISCARD static HTMLTag StringAtomToHTMLTag(const SR_UTILS_NS::StringAtom& tag) {
        static const std::unordered_map<SR_UTILS_NS::StringAtom, HTMLTag> HTMLTags = {
            {"div"_atom, HTMLTag::Div}, {"span"_atom, HTMLTag::Span}, {"p"_atom, HTMLTag::P},
            {"h1"_atom, HTMLTag::H1}, {"h2"_atom, HTMLTag::H2}, {"h3"_atom, HTMLTag::H3}, {"h4"_atom, HTMLTag::H4}, {"h5"_atom, HTMLTag::H5}, {"h6"_atom, HTMLTag::H6},
            {"a"_atom, HTMLTag::A},{"img"_atom, HTMLTag::Img}, {"input"_atom, HTMLTag::Input}, {"button"_atom, HTMLTag::Button}, {"form"_atom, HTMLTag::Form},
            {"label"_atom, HTMLTag::Label}, {"select"_atom, HTMLTag::Select}, {"option"_atom, HTMLTag::Option}, {"textarea"_atom, HTMLTag::Textarea}, {"table"_atom, HTMLTag::Table},
            {"tr"_atom, HTMLTag::Tr}, {"td"_atom, HTMLTag::Td}, {"th"_atom, HTMLTag::Th}, {"thead"_atom, HTMLTag::Thead}, {"tbody"_atom, HTMLTag::Tbody},
            {"tfoot"_atom, HTMLTag::Tfoot}, {"ul"_atom, HTMLTag::Ul}, {"ol"_atom, HTMLTag::Ol}, {"li"_atom, HTMLTag::Li}, {"dl"_atom, HTMLTag::Dl},
            {"dt"_atom, HTMLTag::Dt}, {"dd"_atom, HTMLTag::Dd},{"br"_atom, HTMLTag::Br}, {"hr"_atom, HTMLTag::Hr}, {"meta"_atom, HTMLTag::Meta}, {"link"_atom, HTMLTag::Link},
            {"style"_atom, HTMLTag::Style}, {"script"_atom, HTMLTag::Script}, {"title"_atom, HTMLTag::Title}, {"head"_atom, HTMLTag::Head}, {"body"_atom, HTMLTag::Body}, {"html"_atom, HTMLTag::Html},
            {"text"_atom, HTMLTag::Text}, {"header"_atom, HTMLTag::Header}
        };

        if (const auto it = HTMLTags.find(tag); it != HTMLTags.end()) {
            return it->second;
        }
        return HTMLTag::Undefined;
    };

    SR_NODISCARD static SR_UTILS_NS::StringAtom HTMLTagToStringAtom(HTMLTag tag) {
        static const std::array<SR_UTILS_NS::StringAtom, static_cast<uint32_t>(HTMLTag::MAX_SIZE) - 1> HTMLTags = {
            "div"_atom, "span"_atom, "p"_atom, "h1"_atom, "h2"_atom, "h3"_atom, "h4"_atom, "h5"_atom, "h6"_atom, "a"_atom,
            "img"_atom, "input"_atom, "button"_atom, "form"_atom, "label"_atom, "select"_atom, "option"_atom, "textarea"_atom, "table"_atom,
            "tr"_atom, "td"_atom, "th"_atom, "thead"_atom, "tbody"_atom, "tfoot"_atom, "ul"_atom, "ol"_atom, "li"_atom, "dl"_atom, "dt"_atom, "dd"_atom,
            "br"_atom, "hr"_atom, "meta"_atom, "link"_atom, "style"_atom, "script"_atom, "title"_atom, "head"_atom, "body"_atom, "html"_atom, "text"_atom,
            "header"_atom,
        };

        if ((static_cast<uint32_t>(tag) - 1) < HTMLTags.size()) {
            return HTMLTags[static_cast<uint32_t>(tag) - 1];
        }
        return UndefinedTag;
    }
}

#endif //SR_COMMON_WEB_HTML_TAG_H
```


