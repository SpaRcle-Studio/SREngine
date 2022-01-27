//
// Created by Nikita on 11.07.2021.
//

#include "Base/Script.h"

#include <Impl/EvoScriptImpl.h>

Framework::Scripting::Script* Framework::Scripting::Script::Allocate(
        const std::string &name,
        Compiler *compiler,
        ScriptType type)
{
    const auto path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Scripts").Concat(name);
    switch (type) {
        case ScriptType::EvoScript:
            return new EvoScriptImpl(compiler, name, path);
        case ScriptType::Lua:
            break;
    }
    return nullptr;
}
