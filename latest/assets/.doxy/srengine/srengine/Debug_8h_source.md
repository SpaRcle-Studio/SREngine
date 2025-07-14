

# File Debug.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Debug.h**](Debug_8h.md)

[Go to the documentation of this file](Debug_8h.md)


```C++
//
// Created by Nikita on 16.11.2020.
//

#ifndef SR_ENGINE_UTILS_DEBUG_H
#define SR_ENGINE_UTILS_DEBUG_H

#include <Utils/FileSystem/Path.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Common/CastUtils.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(DebugLogType, uint8_t,
        Log, Info, Debug, Graph, Shader, Script, System, Warn,
        Error, ScriptError, ScriptLog, Vulkan, VulkanLog, VulkanError, Assert, Success, Test
    );

    static fmt::text_style GetTextStyleColorByLogType(DebugLogType type);

    class Debug : public Singleton<Debug> {
        SR_REGISTER_SINGLETON(Debug);
    public:
        enum class Level {
            None = 0, Low = 1, Medium = 2, High = 3, Full = 4
        };

        enum class Theme {
            Dark, Light
        };

    public:
        Debug();
        ~Debug() override;

    private:
        void InitColorTheme();

    public:
        void SetLevel(Level level);

        SR_NODISCARD Level GetLevel();
        SR_NODISCARD bool IsInitialized() const;

        void MakeCrash();
        void TestPrint();

        void Initialize(const std::string& log_path, bool ShowUsedMemory, Theme colorTheme = Theme::Light);
        void DeInitialize();

        bool IsSingletonCanBeDestroyed() const override { return false; }

    public:
        void Log(const std::string& msg);
        void Success(const std::string& msg);
        void VulkanLog(const std::string& msg);
        void Info(const std::string& msg);
        void Graph(const std::string& msg);
        void Vulkan(const std::string& msg);
        void Shader(const std::string& msg);
        void Script(const std::string& msg);
        void System(const std::string& msg);
        void Warn(const std::string& msg);
        void Error(const std::string& msg);
        void VulkanError(const std::string& msg);
        bool Assert(const std::string& msg);
        bool AssertOnceCheck(const std::string& msg);

        void ScriptLog(const std::string& msg);
        void ScriptError(const std::string& msg);

        void Print(std::string msg, DebugLogType type);

    private:
        bool m_showUseMemory = false;
        bool m_ColorThemeIsEnabled = false;

        Theme m_theme = Theme::Light;

        std::atomic<bool> m_isInit = false;
        Path m_logPath;
        std::ofstream m_file;
        std::atomic<Level> m_level = Level::Low;
        size_t m_countErrors = 0;
        size_t m_countWarnings = 0;

    };
}

#define SR_LOG_TEST(...) SR_UTILS_NS::Debug::Instance().Print(SR_FORMAT(__VA_ARGS__), SR_UTILS_NS::DebugLogType::Test)
#define SR_LOG(...) SR_UTILS_NS::Debug::Instance().Log(SR_FORMAT(__VA_ARGS__))
#define SR_INFO(...) SR_UTILS_NS::Debug::Instance().Info(SR_FORMAT(__VA_ARGS__))
#define SR_WARN(...) SR_UTILS_NS::Debug::Instance().Warn(SR_FORMAT(__VA_ARGS__))
#define SR_ERROR(...) SR_UTILS_NS::Debug::Instance().Error(SR_FORMAT(__VA_ARGS__))
#define SR_GRAPH(...) SR_UTILS_NS::Debug::Instance().Graph(SR_FORMAT(__VA_ARGS__))
#define SR_SUCCESS(...) SR_UTILS_NS::Debug::Instance().Success(SR_FORMAT(__VA_ARGS__))
#define SR_GRAPH_LOG(...) SR_GRAPH(SR_FORMAT(__VA_ARGS__))
#define SR_SHADER(...) SR_UTILS_NS::Debug::Instance().Shader(SR_FORMAT(__VA_ARGS__))
#define SR_SHADER_LOG(...) SR_UTILS_NS::Debug::Instance().Shader(SR_FORMAT(__VA_ARGS__))
#define SR_SYSTEM_LOG(...) SR_UTILS_NS::Debug::Instance().System(SR_FORMAT(__VA_ARGS__))
#define SR_VULKAN_MSG(...) SR_UTILS_NS::Debug::Instance().Vulkan(SR_FORMAT(__VA_ARGS__))
#define SR_VULKAN_LOG(...) SR_UTILS_NS::Debug::Instance().VulkanLog(SR_FORMAT(__VA_ARGS__))
#define SR_VULKAN_ERROR(...) SR_UTILS_NS::Debug::Instance().VulkanError(SR_FORMAT(__VA_ARGS__))
#define SR_DEBUG_LOG(...) SR_UTILS_NS::Debug::Instance().Print(SR_FORMAT(__VA_ARGS__), SR_UTILS_NS::DebugLogType::Debug)

#define SR_MAKE_ASSERT(msg) (msg).append("\nFile: ").append(__FILE__).append("\nLine: ").append(std::to_string(__LINE__))

#if defined(SR_DEBUG) || defined(SR_ANDROID)
    #define SR_ENABLE_ASSERTS
#endif

#ifdef SR_ENABLE_ASSERTS
    #define SR_CHECK_ERROR(fun, notEquals, errorMsg) \
        if (fun != notEquals) SR_UTILS_NS::Debug::Instance().Error(errorMsg)

    #define SRAssert2(expr, ...) (!!(expr) || SR_UTILS_NS::Debug::Instance().Assert(SR_MAKE_ASSERT(SR_FORMAT(__VA_ARGS__))))

    #define SRAssert1(expr) SRAssert2(expr, #expr)
    #define SRAssert(expr) SRAssert2(expr, "An exception has been occured.")

    #define SRVerifyFalse2(expr, ...) ((!(expr) || SR_UTILS_NS::Debug::Instance().Assert(SR_MAKE_ASSERT(SR_FORMAT(__VA_ARGS__)))))
    #define SRVerify2(expr, ...) ((expr) || SR_UTILS_NS::Debug::Instance().Assert(SR_MAKE_ASSERT(SR_FORMAT(__VA_ARGS__))))

    #define SR_SAFE_PTR_ASSERT(expr, msg) SRAssert2(expr, SR_FORMAT("[SafePtr] {} \n\tPtr: {}", msg, (void *) m_ptr));

    #define SRAssert2Once(expr, ...) ((!(expr) && SR_UTILS_NS::Debug::Instance().AssertOnceCheck(SR_MAKE_ASSERT(SR_FORMAT(__VA_ARGS__)))) || SRAssert2(expr, SR_FORMAT(__VA_ARGS__)))
#else
    #define SR_CHECK_ERROR(fun, notEquals, errorMsg) fun
    #define SRAssert2(expr, ...) (SR_NOOP)
    #define SRAssert(expr) (SR_NOOP)
    #define SRAssert1(expr) SRAssert(expr)
    #define SR_SAFE_PTR_ASSERT(expr, msg) (SR_NOOP)
    #define SRAssert2Once(expr, ...) (SR_NOOP)
    #define SRVerifyFalse2(expr, ...) ((!(expr)))
    #define SRVerify2(expr, ...) ((expr))
#endif

#define SRHalt(...) SR_UTILS_NS::Debug::Instance().Assert(SR_MAKE_ASSERT(SR_FORMAT(__VA_ARGS__)))
#define SRHaltOnce(...)  SR_UTILS_NS::Debug::Instance().AssertOnceCheck(SR_MAKE_ASSERT(SR_FORMAT(__VA_ARGS__))) || SRHalt(SR_FORMAT(__VA_ARGS__))
#define SRHalt0() SRHalt("An exception has been occured!")
#define SRHaltOnce0() SRHaltOnce("An exception has been occured!")

#define SRVerifyFalse(expr) SRVerifyFalse2(expr, "An exception has been occured!")
#define SRVerify(expr) SRVerify2(expr, "An exception has been occured!")

#define SRAssert1Once(expr) SRAssert2Once(expr, #expr)
#define SRAssertOnce(expr) SRAssert2Once(expr, "An exception has been occured!")

#endif //SR_ENGINE_UTILS_DEBUG_H
```


