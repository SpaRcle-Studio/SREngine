

# File TracyContext.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Profile**](dir_2c7cc58991649fbffe436a1b7c6e8155.md) **>** [**TracyContext.h**](TracyContext_8h.md)

[Go to the documentation of this file](TracyContext_8h.md)


```C++
//
// Created by Monika on 13.05.2023.
//

#ifndef SR_ENGINE_UTILS_TRACY_CONTEXT_H
#define SR_ENGINE_UTILS_TRACY_CONTEXT_H

#ifdef SR_TRACY_ENABLE

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Types/Map.h>

#ifndef SR_ENGINE_CODEGEN_CLANG_PARSE_MODE
    #include <Tracy.hpp>
#endif

namespace SR_UTILS_NS {
    SR_ENUM_NS_STRUCT_T(TracyType, uint8_t,
        Common,
        Vulkan,

        All
    );

    extern SR_COMMON_DLL_API void StartupEngineProfiler();
    extern SR_COMMON_DLL_API void ShutdownEngineProfiler();

    class TracyContextManager : public SR_UTILS_NS::Singleton<TracyContextManager> {
        SR_REGISTER_SINGLETON(TracyContextManager)
        using TracyContextPtr = void*;
        using IdentifierPtr = void*;
        using ContextMap = std::map<IdentifierPtr, TracyContextPtr>;
    public:
        TracyContextPtr& GetContext(TracyType type, IdentifierPtr pIdentifier) {
            if (type >= TracyType::TracyTypeMAX - 1) {
                SR_PLATFORM_NS::WriteConsoleError("TracyContextManager::GetContext() : Invalid TracyType!");
                SR_UTILS_NS::Breakpoint();
                static TracyContextPtr pNull = nullptr;
                return pNull;
            }

            return m_contexts[type][pIdentifier];
        }

        void Destroy(TracyType type);

    #ifdef SR_USE_VULKAN
        std::function<void(void*)> VulkanDestroy;
    #endif

    private:
        void Destroy(TracyContextPtr pContext, TracyType type);

    private:
        std::array<ContextMap, TracyType::TracyTypeMAX - 1> m_contexts;

    };
}
#endif

#ifdef SR_TRACY_ENABLE
    #define SR_TRACY_IS_PROFILER_CONNECTED (tracy::GetProfiler().IsConnected())
    #define SR_TRACY_TEXT_N(name, text) ZoneText(text.c_str(), text.size())
    #define SR_TRACY_ZONE ZoneScoped 
    #define SR_TRACY_ZONE_VALUE(value) ZoneValue(value)
    #define SR_TRACY_ZONE_TEXT(value) ZoneText(value.c_str(), value.size())
    #define SR_TRACY_ZONE_TEXT_C(value) ZoneText(value, strlen(value))
    #define SR_TRACY_ZONE_N(name) ZoneScopedN(name)
    #define SR_TRACY_ZONE_S(name) ZoneTransientN(TracyConcat(__tracy_source_location, TracyLine), name, true)
    #define SR_TRACY_PLOT(name, val) TracyPlot(name, val)
    #define SR_TRACY_ZONE_COLOR(color) ZoneColor(color)

    #define SR_TRACY_GET_CONTEXT(tracyType, pIdentifier) \
        SR_UTILS_NS::TracyContextManager::Instance().GetContext(tracyType, pIdentifier)

    #define SR_TRACY_DESTROY(tracyType) SR_UTILS_NS::TracyContextManager::Instance().Destroy(tracyType);
    #define SR_TRACY_THREAD_NAME(name) tracy::SetThreadName(name)
#else
    #define SR_TRACY_IS_PROFILER_CONNECTED (false)
    #define SR_TRACY_TEXT_N(name, text)
    #define SR_TRACY_ZONE SR_NOOP
    #define SR_TRACY_ZONE_VALUE(value) SR_NOOP
    #define SR_TRACY_ZONE_TEXT(value) SR_NOOP
    #define SR_TRACY_ZONE_TEXT_C(value) SR_NOOP
    #define SR_TRACY_ZONE_N(name) SR_NOOP
    #define SR_TRACY_ZONE_S(name) SR_NOOP
    #define SR_TRACY_PLOT(name, val) SR_NOOP
    #define SR_TRACY_ZONE_COLOR(color)

    #define SR_TRACY_GET_CONTEXT(tracyType, pIdentifier)
    #define SR_TRACY_DESTROY(tracyType)
    #define SR_TRACY_THREAD_NAME(name)
#endif


#endif //SR_ENGINE_UTILS_TRACY_CONTEXT_H
```


