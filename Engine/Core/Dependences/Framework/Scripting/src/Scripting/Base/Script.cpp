//
// Created by Nikita on 11.07.2021.
//

#include <Scripting/Base/Script.h>
#include <Scripting/Impl/EvoScriptImpl.h>
#include <ResourceManager/ResourceManager.h>

namespace SR_SCRIPTING_NS {
    Script *Framework::Scripting::Script::Allocate(const std::string &name, Compiler *compiler, ScriptType type) {
        auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Scripts").Concat(name);
        switch (type) {
            case ScriptType::EvoScript:
                return new EvoScriptImpl(compiler, name, path);
            case ScriptType::Lua:
                break;
        }
        return nullptr;
    }

    bool Script::IsAutoFree() const {
        return m_autoFree;
    }
}