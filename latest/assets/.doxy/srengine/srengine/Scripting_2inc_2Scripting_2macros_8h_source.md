

# File macros.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**macros.h**](Scripting_2inc_2Scripting_2macros_8h.md)

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


