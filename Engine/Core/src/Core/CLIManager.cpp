// 
// Created by innerviewer on 2025-04-16.
//

#include <Core/CLIManager.h>

#include <Enum/CLIFlags.hpp>
#include <Enum/CLIOptions.hpp>

namespace SR_CORE_NS {
    void CLIManager::Init(int argc, char** argv) {
        auto&& rawOptions = SR_UTILS_NS::EnumReflector::GetNames<CLIOptions>();
        auto&& rawFlags = SR_UTILS_NS::EnumReflector::GetNames<CLIFlags>();

        std::map<std::string, CLIOptions> options;
        std::map<std::string, CLIFlags> flags;

        for (auto&& option : rawOptions) {
            options[std::string("--" + SR_UTILS_NS::StringUtils::ToKebabCase(option))] = SR_UTILS_NS::EnumReflector::FromString<CLIOptions>(option);
        }

        for (auto&& flag : rawFlags) {
            flags[std::string("--" + SR_UTILS_NS::StringUtils::ToKebabCase(flag))] = SR_UTILS_NS::EnumReflector::FromString<CLIFlags>(flag);
        }

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];

            if (flags.count(arg) > 0) {
                // Check if a value follows the flag
                if (i + 1 < argc && std::string(argv[i + 1]).rfind("--", 0) != 0) {
                    SR_PLATFORM_NS::WriteConsoleWarn(SR_FORMAT("CLIManager::Init() : unexpected value for flag '{}': '{}'"
                        "\n\tFlags do not take values!\n", arg, argv[i + 1])
                    );

                    ++i; // Skip the unexpected value
                } else {
                    m_flags |= flags.find(arg)->second;
                }
            }
            else if (options.count(arg) > 0) {
                if (i + 1 < argc && std::string(argv[i + 1]).rfind("--", 0) != 0) {
                    m_options[options.find(arg)->second] = argv[i + 1];
                    ++i; // Skip the value
                } else {
                    SR_PLATFORM_NS::WriteConsoleWarn(SR_FORMAT("CLIManager::Init() : missing value for option "
                        "'{}': '{}'\n", arg, argv[i + 1])
                    );
                }
            }
            else if (arg.rfind("-", 0) == 0) {
                SR_PLATFORM_NS::WriteConsoleWarn(SR_FORMAT("CLIManager::Init() : unknown argument: '{}'\n", arg));
            }
            else {
                SR_PLATFORM_NS::WriteConsoleWarn(SR_FORMAT("CLIManager::Init() : unexpected argument: '{}'\n", arg));
            }
        }
    }

    std::optional<std::string> CLIManager::GetOptionValue(CLIOptions option) {
        auto&& it = m_options.find(option);
        if (it != m_options.end()) {
            return it->second;
        }

        return std::nullopt;
    }
}
