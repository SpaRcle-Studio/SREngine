//
// Created by Codex on 14.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_DEBUG_NATIVE_VALUES_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_DEBUG_NATIVE_VALUES_H

#include <Scripting/stdInclude.h>
#include <Utils/Reflection/Value.h>

namespace SR_SCRIPTING_NS::AngelScriptDebugNativeValues {
    struct Child {
        SR_UTILS_NS::String name;
        SR_UTILS_NS::Reflection::Value value;
    };

    SR_UTILS_NS::String Summary(SR_UTILS_NS::Reflection::Value& value);
    bool HasChildren(SR_UTILS_NS::Reflection::Value& value);
    SR_UTILS_NS::Vector<Child> Children(SR_UTILS_NS::Reflection::Value& value);
}

#endif
