//
// Created by Monika on 02.11.2021.
//

#include <Utils/Platform/Stacktrace.h>
#include <Utils/Platform/LinuxStacktraceImpl.h>

namespace SR_UTILS_NS {
    void StacktraceInit() {
        StacktraceInitImpl();
    }

    static bool g_stackStraceEnabled = true;

    void DisableStacktrace() {
        g_stackStraceEnabled = false;
    }

    std::string GetStacktrace() {
        if (!g_stackStraceEnabled) {
            return std::string("Stacktrace is disabled by Features.xml!");
        }

        static bool stackStaceLoaded = false;
        if (stackStaceLoaded) {
            SR_PLATFORM_NS::WriteConsoleError("GetStacktrace() : loading stacktrace...\n");
            stackStaceLoaded = true;
        }

        auto&& stacktrace = GetStacktraceImpl();
        std::string result = stacktrace;

        free(stacktrace);
        return result;
    }
}


