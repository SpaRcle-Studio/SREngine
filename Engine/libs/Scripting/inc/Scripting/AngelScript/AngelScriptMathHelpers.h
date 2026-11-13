//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_MATH_HELPERS_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_MATH_HELPERS_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/stdInclude.h>

#include <Utils/Reflection/Value.h>

namespace SR_SCRIPTING_NS::AngelScriptMathHelpers {
    struct Component {
        const char* pName = nullptr;
        const char* pScalar = nullptr;
        uint32_t offset = 0;
    };

    struct Layout {
        Component components[16] = {};
        uint32_t count = 0;
    };

    Layout Describe(const SR_UTILS_NS::Reflection::TypeInfo& info);
}

#endif

#endif
