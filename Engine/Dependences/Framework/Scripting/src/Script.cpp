//
// Created by Nikita on 29.12.2020.
//

#include "../inc/Script.h"
#include <Compiler.h>

namespace Framework::Scripting {
    Script::Script(const std::string &path, Compiler* compiler) : Helper::Component("Script") {
        this->m_compiler = compiler;

        L = luaL_newstate();

        switch (luaL_loadfile(L, path.c_str())) { //no bytecode allowed
            case LUA_OK:
                m_status = Status::SuccessfullyLoad;
                break;
            case LUA_ERRSYNTAX:
                m_status = Status::SyntaxError;
                return;
            case LUA_ERRFILE:
                m_status = Status::FileMissing;
                return;
            case LUA_ERRMEM:
                m_status = Status::MemoryExhausted;
                return;
            default:
                m_status = Status::UnexpectedError;
                return;
        }
    }

    Script::~Script() {
        //TODO!!!!
    }

    bool Script::Compile() {
        if (m_status != Status::SuccessfullyLoad){
            Helper::Debug::Error("Script::Compile() : script was not loaded successfully!");
            return false;
        }else
            Helper::Debug::Log("Script::Compile() : compiling script...");

        /* Незнамо зачем, но так надо (http://www.gamedev.ru/code/forum/?id=125829) */
        lua_pcall(L, 0, 0, 0);

        { //?================ INIT LUA ================
            static const luaL_Reg lualibs[] = {
                    {"base", luaopen_base},
                    {"io", luaopen_io},
                    {"math", luaopen_math },
                    {NULL, NULL}
            };

            for (const luaL_Reg* lib = lualibs; lib->func != NULL; lib++) {
                luaL_requiref(L, lib->name, lib->func, 1);
                lua_settop(L, 0);
            }
        } //?================ INIT LUA ================

        for (auto& fun : this->m_compiler->GetClasses("Base")){
            fun(L);
        }

        this->m_status = Status::Compiled;
        return true;
    }

    bool Script::ReCompile() {
        return false;
    }

    void Script::OnDestroyGameObject() noexcept {

    }

    bool Script::Start() {
        if (m_status == Status::RuntimeError)
            return false;


        r = lua_getglobal(L, "Start");
        if (lua_pcall(L, 0, 1, 0)) {
            const char* stackTrace = lua_tostring(L, -1);

            Helper::Debug::Error("Script::Start() : failed call \"Start()\" method at script! \n\tStack traceback: "+std::string(stackTrace));
            this->m_status = Status::RuntimeError;
            return false;
        }
        m_isStart = true;
        return true;
    }

    bool Script::Update() {
        if (m_status == Status::RuntimeError)
            return false;

        if (!m_isStart)
            return Start();

        r = lua_getglobal(L, "Update");
        if (lua_pcall(L, 0, 0, 0)) {
            const char* stackTrace = lua_tostring(L, -1);

            Helper::Debug::Error("Script::Update() : failed call \"Update()\" method at script!\n\tStack traceback: "+std::string(stackTrace));
            this->m_status = Status::RuntimeError;
            return false;
        }

        return true;
    }

    bool Script::FixedUpdate() {
        if (m_status == Status::RuntimeError)
            return false;

        if (!m_isStart)
            return Start();

        r = lua_getglobal(L, "FixedUpdate");
        if (lua_pcall(L, 0, 0, 0)) {
            const char* stackTrace = lua_tostring(L, -1);

            Helper::Debug::Error("Script::FixedUpdate() : failed call \"FixedUpdate()\" method at script!\n\tStack traceback: "+std::string(stackTrace));
            this->m_status = Status::RuntimeError;
            return false;
        }
        return true;
    }
}