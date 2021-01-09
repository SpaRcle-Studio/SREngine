//
// Created by Nikita on 29.12.2020.
//

#include "Compiler.h"
#include <ResourceManager/ResourceManager.h>

Framework::Scripting::Script *Framework::Scripting::Compiler::Load(const std::string& name, bool fromEngine) {
    this->m_mutex_load.lock();

    std::string folder = fromEngine ? "Engine/" : "Game/";
    std::string path = Framework::Helper::ResourceManager::GetResourcesFolder() + "/Scripts/" + folder + name + ".lua";

    Helper::Debug::Log("Compiler::Load() : loading "+path + " script...");

    Script* script = new Script(path, this);

    if (Framework::Scripting::Compiler::Compile(script)) {
        this->m_scripts.push_back(script);
        m_countScripts++;
    }

    this->m_mutex_load.unlock();

    return script;
}

void Framework::Scripting::Compiler::RegisterScriptClass(const std::string& libName, std::function<void(lua_State *)> fun) {
    this->m_mutex_register.lock();
    this->m_libs[libName].push_back(fun);
    this->m_mutex_register.unlock();
}

std::vector<std::function<void(lua_State *L)>> Framework::Scripting::Compiler::GetClasses(const std::string& libName) noexcept {
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

void Framework::Scripting::Compiler::DestroyScript(Framework::Scripting::Script *script) {
    m_mutex_load.lock();

    this->m_scriptsToDestroy.push_back(script);
    this->m_countScriptsToDestroy++;

    m_mutex_load.unlock();
}

void Framework::Scripting::Compiler::PoolEvents() {
    m_mutex_load.lock();
    this->m_mutex_delayed.lock();

    if (m_countScriptsToDestroy) {
        for (size_t t = 0; t < m_countScriptsToDestroy; t++){
            this->Remove(m_scriptsToDestroy[t]);
            if(Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                Helper::Debug::Log("Compiler::PoolEvents() : free script pointer...");
            delete m_scriptsToDestroy[t];
        }
        m_countScriptsToDestroy = 0;
        this->m_scriptsToDestroy.clear();
    }

    if (m_countDelayedLoadingScripts) {
        for (size_t t = 0; t < m_countDelayedLoadingScripts; t++) {
            if (Framework::Scripting::Compiler::Compile(m_delayedLoadingScripts[t])){
                this->m_scripts.push_back(m_delayedLoadingScripts[t]);
                m_countScripts++;
            }else
                Helper::Debug::Error("Compiler::PoolEvents() : failed delayed-compiling script!\n\tPath: "+ m_delayedLoadingScripts[t]->m_name);
        }

        m_delayedLoadingScripts.clear();
        m_countDelayedLoadingScripts = 0;
    }

    this->m_mutex_delayed.unlock();
    m_mutex_load.unlock();
}

bool Framework::Scripting::Compiler::Remove(Framework::Scripting::Script *script) {
    for(size_t t = 0; t < m_countScripts; t++)
        if (m_scripts[t] == script) {
            m_scripts.erase(m_scripts.begin() + t);
            return true;
        }

    return false;
}

Framework::Scripting::Script *Framework::Scripting::Compiler::DelayedLoad(const std::string &name, bool fromEngine) {
    this->m_mutex_delayed.lock();

    std::string folder = fromEngine ? "Engine/" : "Game/";
    std::string path = Framework::Helper::ResourceManager::GetResourcesFolder() + "/Scripts/" + folder + name + ".lua";

    Helper::Debug::Log("Compiler::DelayedLoad() : delayed loading "+path + " script...");

    Script* delayed = new Script(path, this);

    this->m_delayedLoadingScripts.push_back(delayed);
    m_countDelayedLoadingScripts++;

    this->m_mutex_delayed.unlock();

    return delayed;
}

bool Framework::Scripting::Compiler::Compile(Framework::Scripting::Script *script) {
    if (!script->Compile()) {
        switch (script->m_status) {
            //case Script::Status::Unknown:
            //    break;
            case Script::Status::FileMissing:
                Helper::Debug::Error("Compiler::Compile() : file "+script->m_name + " is not exists!");
                break;
            //case Script::Status::SuccessfullyLoad:
            //    break;
            //case Script::Status::RuntimeError:
            //    break;
            case Script::Status::MemoryExhausted:
                Helper::Debug::Error("Compiler::Compile() : memory exhausted at "+script->m_name + " script!");
                break;
            case Script::Status::SyntaxError:
                Helper::Debug::Error("Compiler::Compile() : file "+script->m_name + " has syntax errors!");
                break;
            case Script::Status::UnexpectedError:
                Helper::Debug::Error("Compiler::Compile() : unexpected error at "+script->m_name + " script!");
                break;
            default:
                Helper::Debug::Error("Compiler::Compile() : unknown error at "+script->m_name + " script!");
                break;
            //case Script::Status::Compiled:
            //    break;
        }
        return false;
    }
    else
        return true;
}
