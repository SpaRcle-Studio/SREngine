

# File macros.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**macros.h**](libs_2Physics_2inc_2Physics_2macros_8h.md)

[Go to the documentation of this file](libs_2Physics_2inc_2Physics_2macros_8h.md)


```C++
#ifndef SR_ENGINE_PHYSICS_MACROS_H
#define SR_ENGINE_PHYSICS_MACROS_H

#include <Utils/macros.h>

#ifdef SR_PHYSICS_DLL_EXPORTS
    #define SR_PHYSICS_DLL_API SR_DLL_API_EXPORT
#else
    #define SR_PHYSICS_DLL_API SR_DLL_API_IMPORT
#endif

#endif //SR_ENGINE_PHYSICS_MACROS_H
```


