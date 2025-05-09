

# File macros.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**macros.h**](Physics_2inc_2Physics_2macros_8h.md)

[Go to the documentation of this file](Physics_2inc_2Physics_2macros_8h.md)


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


