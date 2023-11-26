//
// Created by Monika on 11.11.2023.
//

#include <Utils/Types/StringAtom.h>
#include <Utils/Common/HashManager.h>

namespace SR_UTILS_NS {
    StringHashInfo* StringAtom::DEFAULT_STRING_INFO = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo("");

    StringAtom::StringAtom(const char* str)
        : m_info(SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str))
    { }

    StringAtom::StringAtom(const std::string& str)
        : m_info(SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str))
    { }

    StringAtom::operator std::string() const noexcept { /// NOLINT
        return m_info ? m_info->data : DEFAULT;
    }

    bool StringAtom::operator==(const StringAtom& rhs) const noexcept {
        return m_info == rhs.m_info;
    }

    bool StringAtom::operator==(const std::string& rhs) const noexcept {
        return m_info != nullptr && m_info->data == rhs;
    }

    bool StringAtom::operator==(const char* rhs) const noexcept {
        return m_info != nullptr && m_info->data == rhs;
    }

    StringAtom& StringAtom::operator=(const std::string& str) {
        m_info = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str);
        return *this;
    }

    StringAtom& StringAtom::operator=(const char* str) {
        m_info = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str);
        return *this;
    }

    void StringAtom::operator()(const std::string& str) {
        m_info = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str);
    }

    void StringAtom::operator()(const char* str) {
        m_info = SR_UTILS_NS::HashManager::Instance().GetOrAddInfo(str);
    }

    SR_NODISCARD uint64_t StringAtom::Size() const {
        return m_info ? m_info->size : 0;
    };

    SR_NODISCARD uint64_t StringAtom::size() const {
        return Size();
    };

    SR_NODISCARD bool StringAtom::Empty() const {
        return m_info == nullptr || m_info->size == 0;
    };

    SR_NODISCARD bool StringAtom::empty() const {
        return Empty();
    };

    SR_NODISCARD uint64_t StringAtom::GetHash() const {
        return m_info ? m_info->hash : 0;
    };

    SR_NODISCARD std::string StringAtom::ToString() const {
        return m_info ? m_info->data : DEFAULT;
    };

    SR_NODISCARD const char* StringAtom::ToCStr() const {
        return m_info ? m_info->data.c_str() : "";
    };

    SR_NODISCARD const char* StringAtom::c_str() const {
        return ToCStr();
    };

    SR_NODISCARD const char* StringAtom::data() const {
        return ToCStr();
    };

    SR_NODISCARD const std::string& StringAtom::ToStringRef() const {
        return m_info ? m_info->data : DEFAULT;
    };

    SR_NODISCARD std::string_view StringAtom::ToStringView() const {
        return m_info ? m_info->data : DEFAULT;
    }

    StringAtom::operator std::string_view() const noexcept {
        return m_info ? m_info->data : DEFAULT;
    };
}
