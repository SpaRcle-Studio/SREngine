//
// Created by Monika on 18.06.2022.
//

#ifndef SRENGINE_BREAKPOINT_H
#define SRENGINE_BREAKPOINT_H

#include <Utils/macros.h>

namespace SR_UTILS_NS {
    static void Breakpoint() {
#if defined(SR_WIN32) and defined(SR_MSVC)
        __debugbreak();
#endif
    }
}

#endif //SRENGINE_BREAKPOINT_H
