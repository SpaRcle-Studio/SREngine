//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_SCRIPT_SYSTEM_STATE_H
#define SR_ENGINE_SCRIPTING_SCRIPT_SYSTEM_STATE_H

#include <Scripting/stdInclude.h>

namespace SR_SCRIPTING_NS {
    SR_ENUM_NS_CLASS_T(ScriptSystemState, uint8_t,
        InitialAnalyse, Idle, CheckModules, Codegen, Compiling, Reloading
    );
}

#endif // SR_ENGINE_SCRIPTING_SCRIPT_SYSTEM_STATE_H