//
// Created by Codex on 21.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_NATIVE_STORAGE_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_NATIVE_STORAGE_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
#include <Scripting/AngelScript/AngelScriptBindings.h>

namespace SR_SCRIPTING_NS::AngelScriptNativeStorage {
    const SR_UTILS_NS::Reflection::TypeInfo* Resolve(AngelScriptBindings* pBindings, const SR_UTILS_NS::Reflection::TypeInfo& info);
    bool IsPackedEnum(const SR_UTILS_NS::Reflection::TypeInfo& info);
    const SR_UTILS_NS::Reflection::TypeInfo* NativeType(const SR_UTILS_NS::Reflection::TypeInfo& info);
}
#endif

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_NATIVE_STORAGE_H
