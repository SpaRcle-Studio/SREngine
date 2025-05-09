

# File macros.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**macros.h**](Graphics_2inc_2Graphics_2macros_8h.md)

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


