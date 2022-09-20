//
// Created by Nikita on 16.11.2020.
//

#include <Utils/Debug.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/Stacktrace.h>
#include <Utils/Platform/Platform.h>

namespace SR_UTILS_NS {
    void Debug::Print(std::string msg, Debug::Type type) {
        SR_LOCK_GUARD

        if (!m_isInit) {
            std::cerr << "Debug::Print() : Debugger isn't initialized!\n";
            Platform::Terminate();
        }

        std::string pref;
        ConsoleColor color;

        switch (type) {
            case Debug::Type::Log:		    pref = "[Log] ";	        color = ConsoleColor::Cyan;		      break;
            case Debug::Type::VulkanLog:	pref = "[VulkanLog] ";	    color = ConsoleColor::DarkGray;       break;
            case Debug::Type::Info: 	    pref = "[Info] ";	        color = ConsoleColor::Magenta;	      break;
            case Debug::Type::Debug:	    pref = "[Debug] ";	        color = ConsoleColor::Blue;		      break;
            case Debug::Type::Graph:	    pref = "[Graph] ";	        color = ConsoleColor::Green;	      break;
            case Debug::Type::Vulkan:	    pref = "[Vulkan] ";	        color = ConsoleColor::DarkGray;       break;
            case Debug::Type::Shader:	    pref = "[Shader] ";	        color = ConsoleColor::LightCyan;      break;
            case Debug::Type::Script:	    pref = "[Script] ";	        color = ConsoleColor::Brown;	      break;
            case Debug::Type::System:	    pref = "[System] ";	        color = ConsoleColor::LightBlue;      break;
            case Debug::Type::Warn:	        pref = "[Warn] ";	        color = ConsoleColor::Yellow;	      break;
            case Debug::Type::Error:	    pref = "[Error] ";	        color = ConsoleColor::LightRed;	      break;
            case Debug::Type::Assert:	    pref = "[Assert] ";	        color = ConsoleColor::LightRed;	      break;
            case Debug::Type::ScriptError:	pref = "[ScriptError] ";	color = ConsoleColor::LightRed;	      break;
            case Debug::Type::VulkanError:	pref = "[VulkanError] ";	color = ConsoleColor::LightRed;	      break;
            case Debug::Type::ScriptLog:	pref = "[ScriptLog] ";	    color = ConsoleColor::LightCyan;      break;
            default:					    pref = "[Unk] ";	        color = ConsoleColor::Black;	      break;
        }

        if (m_showUseMemory) {
            std::cout << '<' << static_cast<uint32_t>(SR_PLATFORM_NS::GetProcessUsedMemory() / 1024) << " KB> ";
            if (m_file.is_open()) {
                m_file << '<' << static_cast<uint32_t>(SR_PLATFORM_NS::GetProcessUsedMemory() / 1024) << " KB> ";
            }
        }

        /// TODO: to refactoring

        DWORD bg_color = m_theme == Theme::Light ? (WORD)(((int)ConsoleColor::LightGray << 4)) : (WORD)(((int)ConsoleColor::Black << 4));

        SetConsoleTextAttribute(Debug::m_console, (bg_color | (int)color));
        std::cout << pref;
        if (m_file.is_open())
            m_file << pref;

        int text_color = m_theme == Theme::Light ? (int)ConsoleColor::Black : (int)ConsoleColor::White;
        SetConsoleTextAttribute(Debug::m_console, (bg_color | text_color));

        if (type == Debug::Type::Assert)
            msg.append("\nStack trace:\n").append(GetStacktrace());

        std::cout << msg << std::endl;
        if (m_file.is_open())
            m_file << msg << std::endl;

        volatile static bool enableBreakPoints = true;
        if (type == Debug::Type::Assert && IsRunningUnderDebugger() && enableBreakPoints) {
            Breakpoint();
        }
    }

    void Debug::Init(const std::string& log_path, bool ShowUsedMemory, Theme colorTheme) {
        m_theme = colorTheme;

        InitColorTheme();

        auto&& successfulPath = SR_PLATFORM_NS::GetApplicationPath().GetFolder().Concat("/successful");
        if (successfulPath.Exists(Path::Type::File))
            Platform::Delete(successfulPath);

        m_logPath = Path(log_path + "/log.txt");
        if (m_logPath.Exists(Path::Type::File))
            Platform::Delete(m_logPath);
        m_file.open(m_logPath);

        m_console = GetStdHandle(STD_OUTPUT_HANDLE);

        m_isInit = true;
        m_showUseMemory = ShowUsedMemory;

        std::string msg = "Debugger has been initialized. \n\tLog path: " + m_logPath.ToString();
        Print(msg, Type::Debug);
    }

    void Debug::OnSingletonDestroy() {
        if (!m_countErrors && !m_countWarnings) {
            std::string msg = "Debugger has been stopped.";
            Print(msg, Type::Debug);
        }
        else {
            std::string msg = "Debugger has been stopped with errors!\n"
                              "\tErrors count: "+std::to_string(m_countErrors)+
                              "\n\tWarnings count: "+std::to_string(m_countWarnings);
            Print(msg, Type::Debug);
        }
        m_file.close();

        std::ofstream o(Platform::GetApplicationPath().GetFolder().Concat("/successful"));
        o.close();
    }

    void Debug::InitColorTheme() {
        if (!m_ColorThemeIsEnabled)
            if (m_theme == Theme::Light)
                system("color 70");
        m_ColorThemeIsEnabled = true;
    }

    bool Debug::IsRunningUnderDebugger() {
#if defined(SR_WIN32) and defined(SR_MSVC)
        return ::IsDebuggerPresent() == TRUE;
#else
        return false;
#endif
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

    void Debug::Terminate() {
        SR_SCOPED_LOCK

        Assert("[Stacktrace]");
        System("Function \"Terminate\" has been called... >_<");
        Platform::Terminate();
    }

    void Debug::MakeCrash() {
        SR_SCOPED_LOCK

        Assert("[Stacktrace]");
        System("Function \"MakeCrash\" has been called... >_<");
        for (long long int i = 0; ++i; (&i)[i] = i);
        // https://codengineering.ru/q/what-is-the-easiest-way-to-make-a-c-program-crash-24928
    }
}