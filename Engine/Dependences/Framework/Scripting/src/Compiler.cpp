//
// Created by Nikita on 29.12.2020.
//

#include "Compiler.h"
#include <ResourceManager/ResourceManager.h>

Framework::Scripting::Script *Framework::Scripting::Compiler::Load(std::string name, bool fromEngine) {
    this->m_mutex_load.lock();

    std::string folder = fromEngine ? "Engine/" : "Game/";
    std::string path = Framework::Helper::ResourceManager::GetResourcesFolder() + "/Scripts/" + folder + name + ".lua";

    Helper::Debug::Log("Compiler::Load() : loading "+path + " script...");

    Script* script = new Script(path, this);

    if (!script->Compile()) {
        switch (script->m_status) {
            case Script::Status::Unknown:
                break;
            case Script::Status::FileMissing:
                Helper::Debug::Error("Compiler::Load() : file "+path + " is not exists!");
                break;
            case Script::Status::SuccessfullyLoad:
                break;
            case Script::Status::RuntimeError:
                break;
            case Script::Status::MemoryExhausted:
                Helper::Debug::Error("Compiler::Load() : memory exhausted at "+path + " script!");
                break;
            case Script::Status::SyntaxError:
                Helper::Debug::Error("Compiler::Load() : file "+path + " has syntax errors!");
                break;
            case Script::Status::UnexpectedError:
                Helper::Debug::Error("Compiler::Load() : unexpected error at "+path + " script!");
                break;
            case Script::Status::Compiled:
                break;
        }
    }
    else {
        this->m_scripts.push_back(script);
    }

    this->m_mutex_load.unlock();

    return script;
}

void Framework::Scripting::Compiler::RegisterScriptClass(std::string libName, std::function<void(lua_State *)> fun) {
    this->m_mutex_register.lock();
    this->m_libs[libName].push_back(fun);
    this->m_mutex_register.unlock();
}

std::vector<std::function<void(lua_State *L)>> Framework::Scripting::Compiler::GetClasses(std::string libName) noexcept {
    this->m_mutex_register.lock();

    auto copy = this->m_libs.find(libName);
    if (copy == m_libs.end())
    {
        Helper::Debug::Error("Compiler::GetClasses() : \""+libName+"\" not exists in compiler!");
        this->m_mutex_register.unlock();
        return std::vector<std::function<void(lua_State *L)>>();
    }

    this->m_mutex_register.unlock();

    return copy->second;
}

void Framework::Scripting::Compiler::AwakeAll() {

}

void Framework::Scripting::Compiler::FixedUpdateAll() {
    m_mutex_load.lock();

    for (Script* script : m_scripts)
        script->FixedUpdate();

    m_mutex_load.unlock();
}

void Framework::Scripting::Compiler::UpdateAll() {
    m_mutex_load.lock();

    for (Script* script : m_scripts)
        script->Update();

    m_mutex_load.unlock();
}
