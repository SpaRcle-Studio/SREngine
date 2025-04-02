

# File Breakpoint.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**Breakpoint.h**](Breakpoint_8h.md)

[Go to the documentation of this file](Breakpoint_8h.md)


```C++
//
// Created by Monika on 18.06.2022.
//

#ifndef SR_ENGINE_BREAKPOINT_H
#define SR_ENGINE_BREAKPOINT_H

#include <Utils/macros.h>

namespace SR_UTILS_NS {
    SR_INLINE_STATIC void Breakpoint() {
    #if defined(SR_WIN32) and defined(SR_MSVC)
        __debugbreak();
    #elif defined(SR_LINUX) || defined(SR_ANDROID)
        raise(SIGTRAP);
    #else
        #error "Breakpoint not implemented for this platform"
    #endif
    }
}

#define SR_MAKE_BREAKPOINT SR_UTILS_NS::Breakpoint()

#endif //SR_ENGINE_BREAKPOINT_H
```


