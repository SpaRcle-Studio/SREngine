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

#endif // SR_ENGINE_SCRIPTING_MACROS_H
