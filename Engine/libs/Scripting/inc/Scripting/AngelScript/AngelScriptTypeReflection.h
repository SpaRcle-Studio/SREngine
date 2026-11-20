//
// Created by Codex on 20.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_TYPE_REFLECTION_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_TYPE_REFLECTION_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
#include <Scripting/AngelScript/AngelScriptBindings.h>

namespace SR_SCRIPTING_NS::AngelScriptTypeReflection {
    constexpr asPWORD ScriptTypeUserData = 0x53525459;
    const SR_UTILS_NS::Reflection::TypeInfo* Resolve(AngelScriptBindings* pBindings, asIScriptEngine* pEngine, int32_t typeId);
    SR_UTILS_NS::Reflection::ValueRef Property(AngelScriptBindings* pBindings, asIScriptObject* pObject, uint32_t index, bool isConst);
    void Forget(asITypeInfo* pType);
}
#endif

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_TYPE_REFLECTION_H
