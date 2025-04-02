

# File StringAtomLiterals.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**StringAtomLiterals.h**](StringAtomLiterals_8h.md)

[Go to the documentation of this file](StringAtomLiterals_8h.md)


```C++
//
// Created by Monika on 20.08.2024.
//

#ifndef SR_COMMON_STRING_ATOM_LITERALS_H
#define SR_COMMON_STRING_ATOM_LITERALS_H

#include <Utils/Common/HashManager.h>

SR_INLINE SR_UTILS_NS::StringAtom operator"" _atom(const char* str, size_t) {
    return SR_UTILS_NS::StringAtom(str);
}

SR_INLINE uint64_t operator"" _atom_hash(const char* str, size_t) {
    return SR_HASH_STR_REGISTER(str);
}

namespace SR_UTILS_NS::Details {
    class Formatter {
    public:
        explicit Formatter(const char* format) noexcept
            : m_format(format)
        { }

        template <class... Args> SR_NODISCARD std::string operator()(Args... args) const noexcept {
            return SR_FORMAT(m_format, args...);
        }
    private:
        const char* m_format = nullptr;
    };

    class AtomFormatter {
    public:
        explicit AtomFormatter(const char* format) noexcept
            : m_format(format)
        { }

        template <class... Args> SR_NODISCARD SR_UTILS_NS::StringAtom operator()(Args... args) const noexcept {
            return SR_UTILS_NS::StringAtom(SR_FORMAT(m_format, args...));
        }
    private:
        const char* m_format = nullptr;
    };
}

SR_INLINE SR_UTILS_NS::Details::Formatter operator"" _format(const char* str, size_t) {
    return SR_UTILS_NS::Details::Formatter(str);
}

SR_INLINE SR_UTILS_NS::Details::AtomFormatter operator"" _format_atom(const char* str, size_t) {
    return SR_UTILS_NS::Details::AtomFormatter(str);
}


/*constexpr uint64_t operator"" _atom_hash(const char* str, size_t size) {
    const auto strView = std::string_view(str, size);
    return SR_HASH_CONSTEXPR_STR_VIEW_REGISTER(strView);
}*/

#endif //SR_COMMON_STRING_ATOM_LITERALS_H
```


