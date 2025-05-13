//
// Created by Monika on 12.05.2025.
//

#ifndef SR_ENGINE_CORE_MACROS_H
#define SR_ENGINE_CORE_MACROS_H

#include <Utils/macros.h>

#ifdef SR_ENGINE_DLL_EXPORTS
    #define SR_ENGINE_DLL_API SR_DLL_API_EXPORT
#else
    #define SR_ENGINE_DLL_API SR_DLL_API_IMPORT
#endif

#endif //SR_ENGINE_CORE_MACROS_H
