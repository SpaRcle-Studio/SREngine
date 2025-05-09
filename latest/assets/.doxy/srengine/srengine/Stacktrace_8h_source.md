

# File Stacktrace.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Platform**](dir_dff07e13fcd57a959fed4d2a16791af6.md) **>** [**Stacktrace.h**](Stacktrace_8h.md)

[Go to the documentation of this file](Stacktrace_8h.md)


```C++
//
// Created by Monika on 02.11.2021.
//

#ifndef SR_ENGINE_UTILS_STACKTRACE_H
#define SR_ENGINE_UTILS_STACKTRACE_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS {
    extern SR_COMMON_DLL_API void DisableStacktrace();
    extern SR_COMMON_DLL_API std::string GetStacktrace();
    extern SR_COMMON_DLL_API void StacktraceInit();
}

#endif //SR_ENGINE_UTILS_STACKTRACE_H
```


