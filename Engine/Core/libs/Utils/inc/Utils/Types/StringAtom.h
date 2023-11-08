//
// Created by Monika on 29.09.2021.
//

#ifndef SR_ENGINE_STRING_ATOM_H
#define SR_ENGINE_STRING_ATOM_H

#include <Utils/Common/HashManager.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT StringAtom {
        SR_INLINE_STATIC std::string DEFAULT = std::string();
        SR_INLINE_STATIC auto DEFAULT_STRING_INFO = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo("");
    public:
        StringAtom() {
            m_info = DEFAULT_STRING_INFO;
        }

        StringAtom(const StringAtom& str) = default;

        StringAtom(const char* str) /// NOLINT
            : m_info(SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str))
        { }

        StringAtom(const std::string& str) /// NOLINT
            : m_info(SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str))
        { }

    public:
        operator std::string() const noexcept { /// NOLINT
            return m_info ? m_info->data : DEFAULT;
        }

        bool operator==(const StringAtom& rhs) const noexcept {
            return m_info == rhs.m_info;
        }

        bool operator==(const std::string& rhs) const noexcept {
            return m_info != nullptr && m_info->data == rhs;
        }

        bool operator==(const char* rhs) const noexcept {
            return m_info != nullptr && m_info->data == rhs;
        }

        StringAtom& operator=(const std::string& str) {
            m_info = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str);
            return *this;
        }

        StringAtom& operator=(const char* str) {
            m_info = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str);
            return *this;
        }

        void operator()(const std::string& str) {
            m_info = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str);
        }

        void operator()(const char* str) {
            m_info = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str);
        }

    public:
        SR_NODISCARD uint64_t Size() const {
            return m_info ? m_info->size : 0;
        };

        SR_NODISCARD uint64_t size() const {
            return Size();
        };

        SR_NODISCARD bool Empty() const {
            return m_info == nullptr || m_info->size == 0;
        };

        SR_NODISCARD bool empty() const {
            return Empty();
        };

        SR_NODISCARD uint64_t GetHash() const {
            return m_info ? m_info->hash : 0;
        };

        SR_NODISCARD std::string ToString() const {
            return m_info ? m_info->data : DEFAULT;
        };

        SR_NODISCARD const char* ToCStr() const {
            return m_info ? m_info->data.c_str() : "";
        };

        SR_NODISCARD const char* c_str() const {
            return ToCStr();
        };

        SR_NODISCARD const char* data() const {
            return ToCStr();
        };

        SR_NODISCARD const std::string& ToStringRef() const {
            return m_info ? m_info->data : DEFAULT;
        };

        SR_NODISCARD std::string_view ToStringView() const {
            return m_info ? m_info->data : DEFAULT;
        };

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
