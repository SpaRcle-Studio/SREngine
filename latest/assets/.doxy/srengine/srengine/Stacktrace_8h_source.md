

# File Stacktrace.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Platform**](dir_c017a2c280f4c252cdb104ea7a64a7b4.md) **>** [**Stacktrace.h**](Stacktrace_8h.md)

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


