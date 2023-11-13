#ifndef SRENGINE_LINUXSTACKTRACEIMPL_H
#define SRENGINE_LINUXSTACKTRACEIMPL_H

#include <Utils/macros.h>

namespace SR_UTILS_NS {
    extern char* GetStacktraceImpl();
    extern void StacktraceInitImpl();
}

#endif // SRENGINE_LINUXSTACKTRACEIMPL_H