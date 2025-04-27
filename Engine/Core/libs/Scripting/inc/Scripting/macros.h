//
// Created by Monika on 27.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_MACROS_H
#define SR_ENGINE_SCRIPTING_MACROS_H

#include <Utils/macros.h>

#if defined(SR_ANDROID)
    #define SR_SCRIPTING_DLL_API
#elif defined(SR_LINUX)
    #define SR_SCRIPTING_DLL_API __attribute__((visibility("default")))
#else
    #ifdef SR_SCRIPTING_DLL_EXPORTS
        #define SR_SCRIPTING_DLL_API __declspec(dllexport)
    #else
        #define SR_SCRIPTING_DLL_API __declspec(dllimport)
    #endif
#endif

#endif //SR_ENGINE_SCRIPTING_MACROS_H
