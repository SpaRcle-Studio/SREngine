#ifndef SR_ENGINE_AUDIO_MACROS_H
#define SR_ENGINE_AUDIO_MACROS_H

#include <Utils/macros.h>

#ifdef SR_AUDIO_DLL_EXPORTS
    #define SR_AUDIO_DLL_API SR_DLL_API_EXPORT
#else
    #define SR_AUDIO_DLL_API SR_DLL_API_IMPORT
#endif

#endif //SR_ENGINE_AUDIO_MACROS_H
