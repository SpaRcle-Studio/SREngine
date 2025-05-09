

# File macros.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**macros.h**](Audio_2inc_2Audio_2macros_8h.md)

[Go to the documentation of this file](Audio_2inc_2Audio_2macros_8h.md)


```C++
#ifndef SR_ENGINE_AUDIO_MACROS_H
#define SR_ENGINE_AUDIO_MACROS_H

#include <Utils/macros.h>

#ifdef SR_AUDIO_DLL_EXPORTS
    #define SR_AUDIO_DLL_API SR_DLL_API_EXPORT
#else
    #define SR_AUDIO_DLL_API SR_DLL_API_IMPORT
#endif

#endif //SR_ENGINE_AUDIO_MACROS_H
```


