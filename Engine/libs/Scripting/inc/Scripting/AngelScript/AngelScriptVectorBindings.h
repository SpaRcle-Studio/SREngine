//
// Created by Codex on 19.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_VECTOR_BINDINGS_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_VECTOR_BINDINGS_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptBindings.h>

namespace SR_SCRIPTING_NS::AngelScriptVectorBindings {
    void Construct(asIScriptGeneric* pCall);
    void CopyConstruct(asIScriptGeneric* pCall);
    void Destruct(asIScriptGeneric* pCall);
    void Assign(asIScriptGeneric* pCall);
    bool Register(asIScriptEngine* pEngine, AngelScriptBindings* pBindings);
}

#endif

#endif //SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_VECTOR_BINDINGS_H
