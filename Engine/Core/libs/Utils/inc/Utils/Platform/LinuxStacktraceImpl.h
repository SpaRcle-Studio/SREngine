#ifndef SR_ENGINE_LINUXSTACKTRACEIMPL_H
#define SR_ENGINE_LINUXSTACKTRACEIMPL_H

#include <Utils/macros.h>

namespace SR_UTILS_NS {
    extern char* GetStacktraceImpl();
    extern void StacktraceInitImpl();
}

#endif // SR_ENGINE_LINUXSTACKTRACEIMPL_H