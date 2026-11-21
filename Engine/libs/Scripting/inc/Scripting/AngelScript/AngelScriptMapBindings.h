//
// Created by Codex on 21.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_MAP_BINDINGS_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_MAP_BINDINGS_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
#include <Scripting/AngelScript/AngelScriptBindings.h>

namespace SR_SCRIPTING_NS::AngelScriptMapBindings {
    bool Register(asIScriptEngine* pEngine, AngelScriptBindings* pBindings);
}
#endif

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_MAP_BINDINGS_H
