

# File macros.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**macros.h**](inc_2Engine_2macros_8h.md)

[Go to the documentation of this file](inc_2Engine_2macros_8h.md)


```C++
//
// Created by Monika on 12.05.2025.
//

#ifndef SR_ENGINE_CORE_MACROS_H
#define SR_ENGINE_CORE_MACROS_H

#include <Utils/macros.h>

#ifdef SR_ENGINE_DLL_EXPORTS
    #define SR_ENGINE_DLL_API SR_DLL_API_EXPORT
#else
    #define SR_ENGINE_DLL_API SR_DLL_API_IMPORT
#endif

#endif //SR_ENGINE_CORE_MACROS_H
```


