//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_DEBUG_H
#define HELPER_DEBUG_H

#include <Utils/Common/Singleton.h>
#include <Utils/FileSystem/Path.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT Debug : public Singleton<Debug> {
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
        ~Debug() override = default;

    private:
        void InitColorTheme();

        void Print(std::string msg, Type type);

    public:
        Level GetLevel() { return m_level; }
        void SetLevel(Level level) { m_level = level; }

        bool IsRunningUnderDebugger();

        void Terminate();
        void MakeCrash();

        void Init(const std::string& log_path, bool ShowUsedMemory, Theme colorTheme = Theme::Light);
        void OnSingletonDestroy() override;

    public:
        void Log(const std::string& msg) { Print(msg, Type::Log); }
        void VulkanLog(const std::string& msg) { Print(msg, Type::VulkanLog); }
        void Info(const std::string& msg) { Print(msg, Type::Info); }
        void Graph(const std::string& msg) { Print(msg, Type::Graph); }
        void Vulkan(const std::string& msg) { Print(msg, Type::Vulkan); }
        void Shader(const std::string& msg) { Print(msg, Type::Shader); }
        void Script(const std::string& msg) { Print(msg, Type::Script); }
        void System(const std::string& msg) { Print(msg, Type::System); }
        void Warn(const std::string& msg) { Print(msg, Type::Warn); m_countWarnings++; }
        void Error(const std::string& msg) { Print(msg, Type::Error); m_countErrors++; }
        void VulkanError(const std::string& msg) { Print(msg, Type::VulkanError); m_countErrors++; }
        bool Assert(const std::string& msg) { Print(msg, Type::Assert); m_countErrors++; return false; }
        bool AssertOnceCheck(const std::string& msg);

        void ScriptLog(const std::string& msg) { Print(msg, Type::ScriptLog); }
        void ScriptError(const std::string& msg) { Print(msg, Type::ScriptError); }

    private:
        bool               m_showUseMemory             = false;
        bool               m_ColorThemeIsEnabled       = false;
        bool               m_profile                   = false;

        Theme              m_theme                     = Theme::Light;

        std::atomic<bool>  m_isInit                    = false;
        Path               m_logPath                   = Path();
        std::ofstream      m_file                      = std::ofstream();
        std::atomic<Level> m_level                     = Level::Low;
        size_t             m_countErrors               = 0;
        size_t             m_countWarnings             = 0;

#ifdef SR_WIN32
        void*              m_console                   = nullptr;
#endif

    };
}

#define SR_LOG(msg) SR_UTILS_NS::Debug::Instance().Log(msg);
#define SR_INFO(msg) SR_UTILS_NS::Debug::Instance().Info(msg);
#define SR_WARN(msg) SR_UTILS_NS::Debug::Instance().Warn(msg);
#define SR_ERROR(msg) SR_UTILS_NS::Debug::Instance().Error(msg);
#define SR_GRAPH(msg) SR_UTILS_NS::Debug::Instance().Graph(msg);
#define SR_GRAPH_LOG(msg) SR_GRAPH(msg);
#define SR_SHADER(msg) SR_UTILS_NS::Debug::Instance().Shader(msg);
#define SR_SHADER_LOG(msg) SR_UTILS_NS::Debug::Instance().Shader(msg);
#define SR_SYSTEM_LOG(msg) SR_UTILS_NS::Debug::Instance().System(msg);
#define SR_VULKAN_MSG(msg) SR_UTILS_NS::Debug::Instance().Vulkan(msg);
#define SR_VULKAN_LOG(msg) SR_UTILS_NS::Debug::Instance().VulkanLog(msg);
#define SR_VULKAN_ERROR(msg) SR_UTILS_NS::Debug::Instance().VulkanError(msg);

#define SR_MAKE_ASSERT(msg) std::string(msg).append("\nFile: ")           \
            .append(__FILE__).append("\nLine: ").append(std::to_string(__LINE__)) \

#ifdef SR_RELEASE
    #define SR_CHECK_ERROR(fun, notEquals, errorMsg) fun
    #define SRAssert2(expr, msg) (SR_NOOP)
    #define SRAssert(expr) (SR_NOOP)
    #define SRAssert1(expr) SRAssert(expr)
    #define SR_SAFE_PTR_ASSERT(expr, msg) (SR_NOOP)
    #define SRAssert2Once(expr, msg) (SR_NOOP)
    #define SRVerifyFalse2(expr, msg) ((!(expr)))
#endif

#ifdef SR_DEBUG
    #define SR_CHECK_ERROR(fun, notEquals, errorMsg) \
            if (fun != notEquals) SR_UTILS_NS::Debug::Instance().Error(errorMsg)

    #define SRAssert2(expr, msg) (!!(expr) || SR_UTILS_NS::Debug::Instance().Assert (SR_MAKE_ASSERT(msg)))

    #define SRAssert1(expr) SRAssert2(expr, #expr)
    #define SRAssert(expr) SRAssert2(expr, "An exception has been occured.")

    #define SRVerifyFalse2(expr, msg) ((!(expr) || SR_UTILS_NS::Debug::Instance().Assert(SR_MAKE_ASSERT(msg))))

    #define SR_SAFE_PTR_ASSERT(expr, msg) SRAssert2(expr, SR_UTILS_NS::Format("[SafePtr] %s \n\tPtr: %p", msg, (void *) m_ptr));

    #define SRAssert2Once(expr, msg) ((!(expr) && SR_UTILS_NS::Debug::Instance().AssertOnceCheck(SR_MAKE_ASSERT(msg))) || SRAssert2(expr, msg))
#endif

#define SRVerifyFalse(expr) SRVerifyFalse2(expr, "An exception has been occured.")

#define SRAssert1Once(expr) SRAssert2Once(expr, #expr)
#define SRAssertOnce(expr) SRAssert2Once(expr, "An exception has been occured.")
#define SRHalt(msg) SRAssert2(false, msg)
#define SRHalt0() SRAssert(false)

#endif //HELPER_DEBUG_H
