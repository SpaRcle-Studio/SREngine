//
// Created by Monika on 09.09.2022.
//

#include <Utils/Common/EnumReflector.h>

namespace SR_UTILS_NS {
    EnumReflector::~EnumReflector() {
        SR_SAFE_DELETE_PTR(m_data)
    }

    bool EnumReflector::IsIdentChar(char c) {
        return (c >= 'A' && c <= 'Z') ||
               (c >= 'a' && c <= 'z') ||
               (c >= '0' && c <= '9') ||
               (c == '_');
    }

    std::optional<std::string> EnumReflector::ToStringInternal(int64_t value) const {
        for (auto&& enumerator : m_data->values) {
            if (enumerator.value == value) {
                return enumerator.name;
            }
        }

        return std::optional<std::string>();
    }

    std::optional<int64_t> EnumReflector::FromStringInternal(const std::string &name) const {
        const int64_t hash = SR_UTILS_NS::HashCombine(name);

        for (auto&& enumerator : m_data->values) {
            if (enumerator.hashName == hash) {
                return enumerator.value;
            }
        }

        return std::optional<int64_t>();
    }

    std::optional<int64_t> EnumReflector::GetIndexInternal(int64_t value) const {
        int64_t index = 0;

        for (auto&& enumerator : m_data->values) {
            if (enumerator.value == value) {
                return index;
            }
            ++index;
        }

        return std::optional<int64_t>();
    }

    std::optional<int64_t> EnumReflector::AtInternal(int64_t index) const {
        if (static_cast<uint64_t>(index) < Count()) {
            return m_data->values[index].value;
        }

        return std::optional<int64_t>();
    }

    uint64_t EnumReflector::Count() const noexcept {
        return m_data->values.size();
    }
}

