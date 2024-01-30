//
// Created by Monika on 22.01.2023.
//

#ifndef SR_ENGINE_REGEX_H
#define SR_ENGINE_REGEX_H

#include <Utils/stdInclude.h>

namespace SR_HTYPES_NS {
    class Regex {
    public:
        Regex() = default;
        Regex(const std::string& regex); /** NOLINT */
        Regex(Regex&& other) noexcept;

        Regex& operator=(Regex&& other) noexcept;

    public:
        bool Search(const std::string& input);

        SR_NODISCARD uint64_t Size() const noexcept;
        SR_NODISCARD std::string Prefix() const noexcept;
        SR_NODISCARD std::string Suffix() const noexcept;

        SR_NODISCARD std::string operator[](int64_t index) const noexcept;

    private:
        std::regex m_regex;
        std::smatch m_match;

    };
}

#endif //SR_ENGINE_REGEX_H
