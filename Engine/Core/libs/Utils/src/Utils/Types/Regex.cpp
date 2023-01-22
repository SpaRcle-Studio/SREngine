//
// Created by Monika on 22.01.2023.
//

#include <Utils/Types/Regex.h>

namespace SR_HTYPES_NS {
    Regex::Regex(const std::string& regex)
        : m_regex(std::regex(regex))
    { }

    Regex::Regex(Regex&& other) noexcept
        : m_regex(SR_UTILS_NS::Exchange(other.m_regex, { }))
        , m_match(SR_UTILS_NS::Exchange(other.m_match, { }))
    { }

    Regex &Regex::operator=(Regex&& other) noexcept {
        m_regex = SR_UTILS_NS::Exchange(other.m_regex, { });
        m_match = SR_UTILS_NS::Exchange(other.m_match, { });
        return *this;
    }

    bool Regex::Search(const std::string& input) {
        return std::regex_search(input, m_match, m_regex);
    }

    uint64_t Regex::Size() const noexcept {
        return m_match.size();
    }

    std::string Regex::Suffix() const noexcept {
        return m_match.suffix();
    }

    std::string Regex::Prefix() const noexcept {
        return m_match.prefix();
    }

    std::string Regex::operator[](int64_t index) const noexcept {
        if (index < Size()) {
            return m_match[index];
        }

        SRHalt("Out of range!");

        return std::string();
    }
}
