//
// Created by Monika on 18.06.2022.
//

#ifndef SR_ENGINE_BREAKPOINT_H
#define SR_ENGINE_BREAKPOINT_H

#include <Utils/macros.h>

namespace SR_UTILS_NS {
    static inline void Breakpoint() {
#if defined(SR_WIN32) and defined(SR_MSVC)
        __debugbreak();
#endif
#ifdef SR_LINUX
    raise(SIGTRAP);
#endif
    }
}

#define SR_MAKE_BREAKPOINT SR_UTILS_NS::Breakpoint()

#endif //SR_ENGINE_BREAKPOINT_H
