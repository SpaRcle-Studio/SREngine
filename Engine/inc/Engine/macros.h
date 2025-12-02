//
// Created by Monika on 12.05.2025.
//

#ifndef SR_ENGINE_CORE_MACROS_H
#define SR_ENGINE_CORE_MACROS_H

#ifndef SR_USE_PCH
    #include <Utils/macros.h>
#endif

#ifdef SR_ENGINE_DLL_EXPORTS
    #define SR_ENGINE_DLL_API SR_DLL_API_EXPORT
#else
    #define SR_ENGINE_DLL_API SR_DLL_API_IMPORT
#endif

#define SR_CODEGEN_DLL_API_EXPORT_ENGINE_MODULE
#define SR_CODEGEN_DLL_API_IMPORT_ENGINE_MODULE

#endif //SR_ENGINE_CORE_MACROS_H
