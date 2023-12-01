//
// Created by Nikita on 16.11.2020.
//

#include <Utils/Debug.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Platform/Stacktrace.h>
#include <Utils/Platform/Platform.h>

namespace SR_UTILS_NS {
    void Debug::Print(std::string msg, DebugLogType type) {
        SR_LOCK_GUARD;
        SR_TRACY_ZONE;
        SR_TRACY_TEXT_N("Text", msg);

        if (!m_isInit) {
            SR_PLATFORM_NS::WriteConsoleError("Debug::Print() : debugger isn't initialized!\n\tMessage: " + msg + "\n" + SR_UTILS_NS::GetStacktrace());
            SR_PLATFORM_NS::Terminate();
        }

        if (type == DebugLogType::Assert) {
            msg.append("\nStack trace:\n").append(GetStacktrace());
        }
        msg.append("\n");

        auto&& prefix = SR_FORMAT("[{}]", SR_UTILS_NS::EnumReflector::ToStringAtom(type).ToCStr());
        auto&& memoryUsage = m_showUseMemory ? SR_FORMAT("<{} KB> ", static_cast<uint32_t>(SR_PLATFORM_NS::GetProcessUsedMemory() / 1024)) : std::string();

        fmt::print(fmt::fg(fmt::color::dark_gray) | fmt::emphasis::faint, memoryUsage);
        fmt::print(GetTextStyleColorByLogType(type),prefix);
        fmt::print(fmt::emphasis::bold, " " + msg);

        std::cout << std::flush;

        if (m_file.is_open()) {
            m_file << (memoryUsage + prefix + " " + msg);
        }

        volatile static bool enableBreakPoints = true;
        if (type == DebugLogType::Assert && Platform::IsRunningUnderDebugger() && enableBreakPoints) {
            Breakpoint();
        }
    }

    void Debug::Init(const std::string& log_path, bool ShowUsedMemory, Theme colorTheme) {
        m_theme = colorTheme;

        InitColorTheme();

    #ifndef SR_ANDROID
        auto&& successfulPath = SR_PLATFORM_NS::GetApplicationPath().GetFolder().Concat("/successful");
        if (successfulPath.Exists(Path::Type::File))
            Platform::Delete(successfulPath);
    #endif

        m_logPath = Path(log_path + "/log.txt");
        if (m_logPath.Exists(Path::Type::File))
            Platform::Delete(m_logPath);

        m_file.open(m_logPath);
        if (!m_file.is_open()) {
            SR_PLATFORM_NS::WriteConsoleError("Debug::Init() : failed to open log file!\n\tLog path: " + m_logPath.ToString());
        }

        m_isInit = true;
        m_showUseMemory = ShowUsedMemory;

        Print("Debugger has been initialized. \n\tLog path: " + m_logPath.ToString(), DebugLogType::Debug);
    }

    void Debug::OnSingletonDestroy() {
        if (!m_countErrors && !m_countWarnings) {
            std::string msg = "Debugger has been stopped.";
            Print(msg, DebugLogType::Debug);
        }
        else {
            std::string msg = "Debugger has been stopped with errors!\n"
                              "\tErrors count: "+std::to_string(m_countErrors)+
                              "\n\tWarnings count: "+std::to_string(m_countWarnings);
            Print(msg, DebugLogType::Debug);
        }

        if (m_file.is_open()) {
            m_file.close();
        }

    #ifndef SR_ANDROID
        std::ofstream success(Platform::GetApplicationPath().GetFolder().Concat("/successful"));
        if (success.is_open()) {
            success.close();
        }
    #endif
    }

    void Debug::InitColorTheme() {
    #ifdef SR_WIN32
        if (!m_ColorThemeIsEnabled) {
            if (m_theme == Theme::Light)
                system("color 70");
        }
    #endif
        m_ColorThemeIsEnabled = true;
    }

    bool Debug::AssertOnceCheck(const std::string &msg) {
        SR_SCOPED_LOCK

        static std::unordered_set<std::string> asserts;

        if (asserts.count(msg) == 0) {
            asserts.insert(msg);
            return false;
        }

        return true;
    }

    void Debug::MakeCrash() {
        SR_SCOPED_LOCK

        Assert("[Stacktrace]");
        System("Function \"MakeCrash\" has been called... >_<");
        for (long long int i = 0; ++i; (&i)[i] = i);
        // https://codengineering.ru/q/what-is-the-easiest-way-to-make-a-c-program-crash-24928
    }

    void Debug::TestPrint() {
        for (auto&& logTypeName : SR_UTILS_NS::EnumReflector::GetNames<DebugLogType>()) {
            Print("The quick brown fox jumps over the lazy dog.", SR_UTILS_NS::EnumReflector::FromString<DebugLogType>(logTypeName));
        }
    }

    fmt::text_style GetTextStyleColorByLogType(DebugLogType type) {
        static auto errorWarnStyle = fmt::emphasis::blink | fmt::emphasis::bold;
        switch (type) {
            case DebugLogType::Log: return fmt::fg(fmt::color::dark_cyan);
            case DebugLogType::Info: return fmt::fg(fmt::color::dark_magenta);
            case DebugLogType::Debug: return fmt::fg(fmt::color::blue_violet);
            case DebugLogType::Graph: return fmt::fg(fmt::color::green);
            case DebugLogType::Shader: return fmt::fg(fmt::color::lawn_green);
            case DebugLogType::Script: return fmt::fg(fmt::color::brown);
            case DebugLogType::System: return fmt::fg(fmt::color::sky_blue);
            case DebugLogType::Warn: return fmt::fg(fmt::color::yellow) | errorWarnStyle;
            case DebugLogType::Error: return fmt::fg(fmt::color::red) | errorWarnStyle;
            case DebugLogType::ScriptError: return fmt::fg(fmt::color::red) | errorWarnStyle;
            case DebugLogType::ScriptLog: return fmt::fg(fmt::color::dark_cyan);
            case DebugLogType::Vulkan: return fmt::fg(fmt::color::deep_sky_blue);
            case DebugLogType::VulkanLog: return fmt::fg(fmt::color::deep_sky_blue);
            case DebugLogType::VulkanError: return fmt::fg(fmt::color::red) | errorWarnStyle;
            case DebugLogType::Assert: return fmt::fg(fmt::color::orange_red) | errorWarnStyle;
            default:
                return fmt::text_style(); /// NOLINT
        }
    }
}