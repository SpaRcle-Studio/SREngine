//
// Created by Nikita on 16.11.2020.
//

#include <Utils/Debug.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/Stacktrace.h>
#include <Utils/Platform/Platform.h>

namespace SR_UTILS_NS {
    void Debug::Print(std::string msg, DebugLogType type) {
        SR_LOCK_GUARD;
        SR_TRACY_ZONE;
        SR_TRACY_TEXT_N("Text", msg);

        if (!m_isInit) {
            SR_PLATFORM_NS::WriteConsoleError("Debug::Print() : Debugger isn't initialized!\n\tMessage: " + msg + "\n" + SR_UTILS_NS::GetStacktrace());
            SR_PLATFORM_NS::Terminate();
        }

        std::string pref;
        ConsoleColor color;

        switch (type) {
            case DebugLogType::Log:		    pref = "[Log] ";	     color = ConsoleColor::Cyan;      break;
            case DebugLogType::VulkanLog:	pref = "[VulkanLog] ";   color = ConsoleColor::DarkGray;  break;
            case DebugLogType::Info:        pref = "[Info] ";        color = ConsoleColor::Magenta;   break;
            case DebugLogType::Debug:       pref = "[Debug] ";       color = ConsoleColor::Blue;      break;
            case DebugLogType::Graph:       pref = "[Graph] ";       color = ConsoleColor::Green;     break;
            case DebugLogType::Vulkan:      pref = "[Vulkan] ";	     color = ConsoleColor::DarkGray;  break;
            case DebugLogType::Shader:      pref = "[Shader] ";	     color = ConsoleColor::LightCyan; break;
            case DebugLogType::Script:      pref = "[Script] ";	     color = ConsoleColor::Brown;     break;
            case DebugLogType::System:      pref = "[System] ";	     color = ConsoleColor::LightBlue; break;
            case DebugLogType::Warn:        pref = "[Warn] ";        color = ConsoleColor::Yellow;    break;
            case DebugLogType::Error:       pref = "[Error] ";       color = ConsoleColor::LightRed;  break;
            case DebugLogType::Assert:      pref = "[Assert] ";      color = ConsoleColor::LightRed;  break;
            case DebugLogType::ScriptError:	pref = "[ScriptError] "; color = ConsoleColor::LightRed;  break;
            case DebugLogType::VulkanError:	pref = "[VulkanError] "; color = ConsoleColor::LightRed;  break;
            case DebugLogType::ScriptLog:	pref = "[ScriptLog] ";	 color = ConsoleColor::LightCyan; break;
            default:                        pref = "[Unk] ";         color = ConsoleColor::Black;     break;
        }

    #ifdef SR_WIN32
        if (m_showUseMemory) {
            SR_PLATFORM_NS::WriteConsoleLog(SR_UTILS_NS::Format("<%i KB> ", static_cast<uint32_t>(SR_PLATFORM_NS::GetProcessUsedMemory() / 1024)));
            if (m_file.is_open()) {
                m_file << '<' << static_cast<uint32_t>(SR_PLATFORM_NS::GetProcessUsedMemory() / 1024) << " KB> ";
            }
        }

        DWORD bg_color = m_theme == Theme::Light ? (WORD)(((int)ConsoleColor::LightGray << 4)) : (WORD)(((int)ConsoleColor::Black << 4));

        SetConsoleTextAttribute(Debug::m_console, (bg_color | (int)color));
        SR_PLATFORM_NS::WriteConsoleLog(pref);
        if (m_file.is_open())
            m_file << pref;

        int text_color = m_theme == Theme::Light ? (int)ConsoleColor::Black : (int)ConsoleColor::White;
        SetConsoleTextAttribute(Debug::m_console, (bg_color | text_color));
    #endif

    #ifdef SR_ANDROID
        msg = pref + msg;
    #endif

        if (type == DebugLogType::Assert) {
            msg.append("\nStack trace:\n").append(GetStacktrace());
        }

        msg.append("\n");

    #ifdef SR_ANDROID
        switch (type) {
            case DebugLogType::Warn:
                SR_PLATFORM_NS::WriteConsoleWarn(msg);
            case DebugLogType::Error:
            case DebugLogType::VulkanError:
            case DebugLogType::Assert:
                SR_PLATFORM_NS::WriteConsoleLog(msg);
                break;
            default:
                SR_PLATFORM_NS::WriteConsoleLog(msg);
                break;
        }
    #else
        SR_PLATFORM_NS::WriteConsoleLog(msg);
        std::cout << std::flush;
    #endif

        if (m_file.is_open()) {
            m_file << msg << std::endl;
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

    #ifdef SR_WIN32
        m_console = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif

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
}