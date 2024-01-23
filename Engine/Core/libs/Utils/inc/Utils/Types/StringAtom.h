//
// Created by Monika on 29.09.2021.
//

#ifndef SR_ENGINE_STRING_ATOM_H
#define SR_ENGINE_STRING_ATOM_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS {
    class StringHashInfo;

    class SR_DLL_EXPORT StringAtom {
        SR_INLINE_STATIC std::string DEFAULT = std::string();
        static StringHashInfo* DEFAULT_STRING_INFO;
    public:
        StringAtom() {
            m_info = DEFAULT_STRING_INFO;
        }

        StringAtom(const StringAtom& str) = default;

        StringAtom(StringHashInfo* pInfo); /// NOLINT
        StringAtom(const char* str); /// NOLINT
        StringAtom(const std::string& str); /// NOLINT
        StringAtom(const std::string_view& str); /// NOLINT

    public:
        operator std::string() const noexcept; /// NOLINT
        operator std::string_view() const noexcept; /// NOLINT
        bool operator==(const StringAtom& rhs) const noexcept;
        bool operator==(const std::string& rhs) const noexcept;
        bool operator==(const char* rhs) const noexcept;
        StringAtom& operator=(const std::string& str);
        StringAtom& operator=(const char* str);
        void operator()(const std::string& str);
        void operator()(const char* str);

    public:
        SR_NODISCARD uint64_t Size() const;
        SR_NODISCARD uint64_t size() const;
        SR_NODISCARD bool Contains(const char* str) const;
        SR_NODISCARD bool Empty() const;
        SR_NODISCARD bool empty() const;
        SR_NODISCARD uint64_t GetHash() const;
        SR_NODISCARD std::string ToString() const;
        SR_NODISCARD const char* ToCStr() const;
        SR_NODISCARD const char* c_str() const;
        SR_NODISCARD const char* data() const;
        SR_NODISCARD const std::string& ToStringRef() const;
        SR_NODISCARD std::string_view ToStringView() const;

        void clear() {
            Clear();
        }

        void Clear() {
            if (!m_info) {
                return;
            }

            m_info = DEFAULT_STRING_INFO;
        }

    private:
        StringHashInfo* m_info = nullptr;

    };

    template<typename T> constexpr bool IsString() {
        if (!IsVolatile<T>()) {
            return IsString<volatile T>();
        }

        return
            std::is_same_v<T, volatile std::string> ||
            std::is_same_v<T, volatile std::string_view> ||
            std::is_same_v<T, volatile StringAtom>;
    }
}

namespace std {
    template<> struct hash<SR_UTILS_NS::StringAtom> {
        size_t operator()(SR_UTILS_NS::StringAtom const& object) const {
            return object.GetHash();
        }
    };

    template<> struct less<SR_UTILS_NS::StringAtom> {
        bool operator()(const SR_UTILS_NS::StringAtom& lhs, const SR_UTILS_NS::StringAtom& rhs) const {
            return lhs.GetHash() < rhs.GetHash();
        }
    };
}

#endif //SR_ENGINE_STRING_ATOM_H
