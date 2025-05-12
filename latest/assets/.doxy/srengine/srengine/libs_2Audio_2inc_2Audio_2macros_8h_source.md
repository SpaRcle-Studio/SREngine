

# File macros.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**macros.h**](libs_2Audio_2inc_2Audio_2macros_8h.md)

[Go to the documentation of this file](libs_2Audio_2inc_2Audio_2macros_8h.md)


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


