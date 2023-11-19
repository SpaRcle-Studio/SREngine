//
// Created by Monika on 02.11.2021.
//

#ifndef SR_ENGINE_UTILS_STACKTRACE_H
#define SR_ENGINE_UTILS_STACKTRACE_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS {
    extern SR_DLL_EXPORT std::string GetStacktrace();
    extern SR_DLL_EXPORT void StacktraceInit();
}

#endif //SR_ENGINE_UTILS_STACKTRACE_H
