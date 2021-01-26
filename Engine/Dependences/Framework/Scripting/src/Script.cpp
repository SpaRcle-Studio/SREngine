//
// Created by Nikita on 29.12.2020.
//

#include "../inc/Script.h"
#include <Compiler.h>
#include <glm/glm.hpp>

namespace Framework::Scripting {
    Script::Script(const std::string &path, Compiler* compiler) : Helper::Component("Script"), m_name(path) {
        m_thisBridge.script = this;

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
        m_thisBridge.script = nullptr;
    }

    bool Script::Call(const std::string& funName) {
        if (m_isClose){
            Helper::Debug::Warn("Script::Call("+funName+") : script is close!\n\tPath: "+m_name);
            return false;
        }

        if (m_status == Status::RuntimeError)
            return false;

        if (m_status != Status::Compiled) {
            Helper::Debug::Error("Script::Call() : failed call \""+funName+"()\" method at \""+m_name+"\" script!\n\tReason: script is not compiled!");
            return false;
        }

        if (m_callingNow) {
            Helper::Debug::Warn("Script::Call() : script already calling! Wait...\n\tPath: "+m_name);
            ret:
            if (m_callingNow)
                goto ret;
        }
        m_callingNow = true;

        m_currentFunName = funName;

        if (this->IsNeedInit())
            this->Init();
        if (this->IsNeedStart())
            this->Start();

        r = lua_getglobal(L, funName.c_str());
        if (lua_pcall(L, 0, 0, 0)) {
            const char* stackTrace = lua_tostring(L, -1);

            Helper::Debug::Error("Script::Call() : failed call \""+funName+"()\" method at script!\n\tStack traceback: "+std::string(stackTrace));
            this->m_status = Status::RuntimeError;
            m_callingNow = false;
            return false;
        }
        m_callingNow = false;

        m_currentFunName = "Unnamed";

        return true;
    }

    /*
     =ЕСЛИ(D13<=$D$4;$E$4;
        ЕСЛИ($D$4<D13<=$D$5;$E$5;
            ЕСЛИ($D$5<D13<=$D$6;$E$6;
                ЕСЛИ($D$6<D13<=$D$7;$E$7;
                    ЕСЛИ($D$7<D13<=$D$8;$E$8;
                        ЕСЛИ($D$8<D13;$E$9;-1)
                    )
                )
            )
        )
    )

     =ЕСЛИ(D13<=$D$4;$E$4;ЕСЛИ($D$4<D13<=$D$5;$E$5;ЕСЛИ($D$5<D13<=$D$6;$E$6;ЕСЛИ($D$6<D13<=$D$7;$E$7;ЕСЛИ($D$7<D13<=$D$8;$E$8;ЕСЛИ($D$8<D13;$E$9;))))))

     =ЕСЛИ(D13<=$D$4;$E$4;
         ЕСЛИ(D13<=$D$5;$E$5;
             ЕСЛИ(D13<=$D$6;$E$6;
                 ЕСЛИ(D13<=$D$7;$E$7;
                     ЕСЛИ(D13<=$D$8;$E$8;
                         ЕСЛИ($D$8<D13;$E$9)
                     )
                 )
             )
         )
     )

     =ЕСЛИ(D13<=$D$4;$E$4;ЕСЛИ(D13<=$D$5;$E$5;ЕСЛИ(D13<=$D$6;$E$6;ЕСЛИ(D13<=$D$7;$E$7;ЕСЛИ(D13<=$D$8;$E$8;$E$9)))))

     intmain(){
     }

     if (a > 1);
          int i;
          std::cout<<*"i"*;
     else;
          ....


    */

    void Script::CheckExistsFunctions() {
        this->m_hasInit         = FunctionExists("Init");
        this->m_hasAwake        = FunctionExists("Awake");
        this->m_hasStart        = FunctionExists("Start");
        this->m_hasUpdate       = FunctionExists("Update");
        this->m_hasFixedUpdate  = FunctionExists("FixedUpdate");
        this->m_hasClose        = FunctionExists("Close");
    }

    bool Script::Compile() {
        if (m_status != Status::SuccessfullyLoad){
            Helper::Debug::Error("Script::Compile() : script was not loaded successfully!\n\tPath: " + m_name);
            return false;
        }else
            Helper::Debug::Log("Script::Compile() : compiling script...\n\tPath: "+m_name);

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

        this->RegisterBaseTypes();
        this->CheckExistsFunctions();

        this->m_status = Status::Compiled;
        return true;
    }

    bool Script::ReCompile() {
        return false; //TODO
    }

    void Script::OnDestroyGameObject() noexcept {

    }

    bool Script::Start() {
        if (m_status != Status::RuntimeError && m_hasInit && !m_isInit)
            return Init();

        if (m_status == Status::RuntimeError || !m_hasStart)
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
        if (m_status == Status::RuntimeError || !m_hasUpdate)
            return false;

        if (!m_isStart && m_hasStart)
            return Start();
        else if (!m_isInit && m_hasInit)
            return Init();

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
        if (m_status == Status::RuntimeError || !m_hasFixedUpdate)
            return false;

        if (!m_isStart && m_hasStart)
            return Start();
        else if (!m_isInit && m_hasInit)
            return Init();

        r = lua_getglobal(L, "FixedUpdate");
        if (lua_pcall(L, 0, 0, 0)) {
            const char* stackTrace = lua_tostring(L, -1);

            Helper::Debug::Error("Script::FixedUpdate() : failed call \"FixedUpdate()\" method at script!\n\tStack traceback: "+std::string(stackTrace));
            this->m_status = Status::RuntimeError;
            return false;
        }
        return true;
    }

    bool Script::Close() {
        if (!m_hasClose)
            return false;

        if (m_isClose){
            Helper::Debug::Error("Script::Close() : script already destroyed!\n\tPath: \""+m_name+"\"");
            return false;
        }

        r = lua_getglobal(L, "Close");
        if (lua_pcall(L, 0, 0, 0)) {
            const char* stackTrace = lua_tostring(L, -1);

            Helper::Debug::Error("Script::Close() : failed call \"Close()\" method at script!\n\tStack traceback: "+std::string(stackTrace));
            this->m_status = Status::RuntimeError;
            return false;
        }

        this->m_status = Status::Closed;
        this->m_isClose = true;
        return true;
    }

    bool Script::Destroy() {
        if (!m_isClose)
            Helper::Debug::Warn("Script::Destroy() : script is not closed!\n\tPath: \""+m_name+"\"");

        this->m_status = Status::Destroyed;

        if (!m_stack.empty())
            Helper::Debug::Warn("Script::Destroy() : stack is not empty!\n\tPath: "+m_name+"\n\tCount elements: "+std::to_string(m_stack.size()));

        if (m_callingNow) {
            Helper::Debug::Error("Script::Destroy() : Script calling \""+m_currentFunName+"\" function now! Unresolved situation! Wait...\n\tPath: "+m_name);
            ret:
            if (m_callingNow)
                goto ret;
        }

        if (m_isDestroy) {
            Helper::Debug::Error("Script::Destroy() : script already destroyed!\n\tPath: \""+m_name+"\"");
            return false;
        } else
            Helper::Debug::Log("Script::Destroy() : destroying script...\n\tPath: \""+m_name+"\"");

        if (L) {
            Helper::Debug::Log("Script::Destroy() : close lua state...");
            lua_close(L);
        }

        this->m_compiler->DestroyScript(this);

        this->m_isDestroy = true;

        return true;
    }

    bool Script::Init() {
        if (m_status == Status::RuntimeError || !m_hasInit)
            return false;

        r = lua_getglobal(L, "Init");
        if (lua_pcall(L, 0, 1, 0)) {
            const char* stackTrace = lua_tostring(L, -1);

            Helper::Debug::Error("Script::Init() : failed call \"Init()\" method at script! \n\tStack traceback: "+std::string(stackTrace));
            this->m_status = Status::RuntimeError;
            return false;
        }
        m_isInit = true;
        return true;
    }

    bool Script::Awake() {
        return false; //TODO
    }

    bool Script::ImportLibrary(const std::string &name) {
        auto a = m_compiler->GetClasses(name);
        if (a.empty())
            return false;
        else
        {
            Helper::Debug::Script("Script::ImportLibrary(InternalCall) : importing \""+name+"\" library...");
            for (const auto& b : a)
                b(L);

            return true;
        }
    }

    bool Script::FunctionExists(const std::string &funName) noexcept {
        lua_Debug ar;
        lua_getglobal(L, funName.c_str());
        lua_getinfo(L, ">S", &ar);
        return ar.linedefined != -1;
    }

    bool Script::RegisterBaseTypes() {
        luabridge::getGlobalNamespace(L)
                .beginClass<lua_State>("LuaState")
                        //.addStaticProperty("L", L, false)
                .endClass()

                .beginClass<Scripting::Script::This>("ScriptThisBridge")
                .addFunction("ImportLib", (bool (Scripting::Script::This::*)(
                        const std::string &)) &Scripting::Script::This::ImportLib)
                .addFunction("LoadScript", (Script *(Scripting::Script::This::*)(const std::string &,
                                                                                 bool)) &Scripting::Script::This::LoadScript)
                        // .addFunction("GetPointer", (Script* (Scripting::Script::This::*)(void))&Scripting::Script::This::GetPointer)
                .endClass()

                .beginClass<Scripting::Script>("Script")
                    .addStaticProperty("this", &m_thisBridge, false)
                    .addFunction("Call", (bool (Scripting::Script::*)(const std::string &)) &Scripting::Script::Call)
                    .addFunction("Close", (bool (Scripting::Script::*)(void)) &Scripting::Script::Close)
                    .addFunction("Destroy", (bool (Scripting::Script::*)(void)) &Scripting::Script::Destroy)
                            //.addFunction("CallArgs",    (bool (Scripting::Script::*)(const std::string&
                            //       ))&Scripting::Script::CallArgs)
                .endClass();

        Framework::Scripting::Script::RegisterCasting<bool>("Bool", L);
        //Framework::Scripting::Script::RegisterCasting<int>("Int", L);

        return true;
    }

    Script*  Script::This::LoadScript(const std::string &name, bool fromEngine) const {
        return this->script->m_compiler->DelayedLoad(name, fromEngine);
    }
}