//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_DEBUG_H
#define HELPER_DEBUG_H

#include <fstream>
#include <ostream>
#include <mutex>
#include <macros.h>
#include <cassert>

#ifdef SR_WIN32
    #include <Windows.h>
#endif

namespace Framework::Helper {
    class Debug {
    public:
        enum class Level {
            None = 0, Low = 1, Medium = 2, High = 3, Full = 4
        };

        enum class Theme {
            Dark, Light
        };

        enum class ConsoleColor {
            Black = 0,
            Blue = 1,
            Green = 2,
            Cyan = 3,
            Red = 4,
            Magenta = 5,
            Brown = 6,
            LightGray = 7,
            DarkGray = 8,
            LightBlue = 9,
            LightGreen = 10,
            LightCyan = 11,
            LightRed = 12,
            LightMagenta = 13,
            Yellow = 14,
            White = 15
        };

        enum class Type {
            Log, Info, Debug, Graph, Shader, Script, System, Warn,
            Error, ScriptError, ScriptLog, Vulkan, VulkanLog, VulkanError, Assert
        };
    public:
        Debug() = delete;
        ~Debug() = delete;
        Debug(Debug &) = delete;
    private:
        inline static Theme             g_theme                     = Theme::Light;
        inline static std::mutex        g_mutex                     = std::mutex();
#ifdef SR_WIN32
        inline static HANDLE            g_console                   = nullptr;
#endif
        inline static bool              g_showUseMemory             = false;
        inline static bool              g_ColorThemeIsEnabled       = false;
        inline static volatile bool     g_isInit                    = false;
        inline static std::string       g_log_path                  = "";
        inline static std::ofstream     g_file                      = std::ofstream();
        static inline Level             g_level                     = Level::Low;
        static inline bool              g_profile                   = false;
        static inline size_t            g_countErrors               = 0;
        static inline size_t            g_countWarnings             = 0;
    private:
        static void InitColorTheme();

        static void Print(std::string msg, Type type);
    public:
        [[nodiscard]] static bool Profile() { return g_profile; }

        static Level GetLevel() { return g_level; }
        static void SetLevel(Level level) { g_level = level; }

        static void MakeCrash() {
            System("Function \"MakeCrash\" has been called... >_<");
            for (long long int i = 0; ++i; (&i)[i] = i);
            // https://codengineering.ru/q/what-is-the-easiest-way-to-make-a-c-program-crash-24928
        }

        static void Init(const std::string& log_path, bool ShowUsedMemory, Theme colorTheme = Theme::Light);
        static int Stop();
    public:
        static void Log(const std::string& msg)         { Print(msg, Type::Log);                            }
        static void VulkanLog(const std::string& msg)   { Print(msg, Type::VulkanLog);                      }
        static void Info(const std::string& msg)        { Print(msg, Type::Info);                           }
        static void Graph(const std::string& msg)       { Print(msg, Type::Graph);                          }
        static void Vulkan(const std::string& msg)      { Print(msg, Type::Vulkan);                         }
        static void Shader(const std::string& msg)      { Print(msg, Type::Shader);                         }
        static void Script(const std::string& msg)      { Print(msg, Type::Script);                         }
        static void System(const std::string& msg)      { Print(msg, Type::System);                         }
        static void Warn(const std::string& msg)        { Print(msg, Type::Warn);        g_countWarnings++; }
        static void Error(const std::string& msg)       { Print(msg, Type::Error);       g_countErrors++;   }
        static void VulkanError(const std::string& msg) { Print(msg, Type::VulkanError); g_countErrors++;   }
        static void Assert(const std::string& msg)      { Print(msg, Type::Assert);      g_countErrors++;   }

        static void ScriptLog(const std::string& msg)   { Print(msg, Type::ScriptLog);  }
        static void ScriptError(const std::string& msg) { Print(msg, Type::ScriptError);  }
    };
}

#ifdef SR_RELEASE
    #define SR_CHECK_ERROR(fun, notEquals, errorMsg) fun
    #define SRAssert2(expr, msg) { expr; }
    #define SRAssert(expr) { expr; }
#else
    #define SR_CHECK_ERROR(fun, notEquals, errorMsg) \
        if (fun != notEquals) Framework::Helper::Debug::Error(errorMsg)

    #define SR_MAKE_ASSERT(msg) std::string(msg).append("\nFile: ") \
        .append(__FILE__).append("\nLine: ").append(std::to_string(__LINE__)) \

    #define SRAssert2(expr, msg) { if (!(expr)) Helper::Debug::Assert(SR_MAKE_ASSERT(msg)); }
    #define SRAssert(expr) SRAssert2(expr, "An exception has been occured.");
#endif

#endif //HELPER_DEBUG_H
