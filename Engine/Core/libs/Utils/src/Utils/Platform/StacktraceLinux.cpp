//
// Created by Monika on 02.11.2021.
//

#include <Utils/Platform/Stacktrace.h>
#include <Utils/Platform/LinuxStacktraceImpl.h>

namespace SR_UTILS_NS {
    void StacktraceInit() {
        StacktraceInitImpl();
    }

    std::string GetStacktrace() {
        auto &&stacktrace = GetStacktraceImpl();
        std::string result = stacktrace;

        free(stacktrace);
        return result;
    }
}


