

# File macros.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**macros.h**](Scripting_2inc_2Scripting_2macros_8h.md)

[Go to the documentation of this file](Scripting_2inc_2Scripting_2macros_8h.md)


```C++
//
// Created by Monika on 27.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_MACROS_H
#define SR_ENGINE_SCRIPTING_MACROS_H

#include <Utils/macros.h>

#ifdef SR_SCRIPTING_DLL_EXPORTS
    #define SR_SCRIPTING_DLL_API SR_DLL_API_EXPORT
#else
    #define SR_SCRIPTING_DLL_API SR_DLL_API_IMPORT
#endif

#endif //SR_ENGINE_SCRIPTING_MACROS_H
```


