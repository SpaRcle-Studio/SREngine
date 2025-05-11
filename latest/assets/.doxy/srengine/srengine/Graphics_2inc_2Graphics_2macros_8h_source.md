

# File macros.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**macros.h**](Graphics_2inc_2Graphics_2macros_8h.md)

[Go to the documentation of this file](Graphics_2inc_2Graphics_2macros_8h.md)


```C++
#ifndef SR_ENGINE_GRAPHICS_MACROS_H
#define SR_ENGINE_GRAPHICS_MACROS_H

#include <Utils/macros.h>

#ifdef SR_GRAPHICS_DLL_EXPORTS
    #define SR_GRAPHICS_DLL_API SR_DLL_API_EXPORT
#else
    #define SR_GRAPHICS_DLL_API SR_DLL_API_IMPORT
#endif

#endif //SR_ENGINE_GRAPHICS_MACROS_H
```


