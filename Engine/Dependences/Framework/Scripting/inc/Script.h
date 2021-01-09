//
// Created by Nikita on 29.12.2020.
//

#ifndef GAMEENGINE_SCRIPT_H
#define GAMEENGINE_SCRIPT_H

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lapi.h>
    #include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

#include <functional>
#include <string>
#include <Debug.h>
#include <EntityComponentSystem/Component.h>

namespace Framework::Scripting {
    class Compiler;

    class Script : public Helper::Component {
        class This {
        public:
            Script* script = nullptr;
            inline bool ImportLib(const std::string& name) {
                return this->script->ImportLibrary(name);
            }
            Script* LoadScript(const std::string& name, bool fromEngine) const;
        };

        friend class Compiler;

        enum class Status {
            Unknown, FileMissing, SuccessfullyLoad, RuntimeError, MemoryExhausted, SyntaxError, UnexpectedError, Compiled
        };
    private:
        ~Script();
        Script(const std::string &path, Compiler* compiler);
    private:
        const std::string m_name = "Unknown";

        This        m_thisBridge       = This();

        Status      m_status           = Status::Unknown;
        Compiler*   m_compiler         = nullptr;

        lua_State * L                  = nullptr;
        int         r	               = -1;

        bool        m_hasInit          = false;
        bool        m_hasAwake         = false;
        bool        m_hasStart         = false;
        bool        m_hasUpdate        = false;
        bool        m_hasFixedUpdate   = false;
        bool        m_hasClose         = false;

        bool        m_isDestroy        = false;
        bool        m_isInit           = false;
        bool        m_isAwake          = false;
        bool        m_isStart          = false;
    private:
        void CheckExistsFunctions();
    public:
        // call only from lua
        bool ImportLibrary(const std::string& name);
    public:
        bool Init();        // вызывается самым первым
        bool Awake();       // вызывается только при старте движка
        bool Start();       // вызывается после Awake/Init
        bool Update();
        bool FixedUpdate();
        bool Close();

        bool Call(const std::string& funName);
        bool CallArgs(...);
        //void* CallRet();
        //void* CallRetArgs(...);

        // After call script pointer will be free
        bool Destroy();

        bool Compile();
        bool ReCompile();
    protected:
        void OnDestroyGameObject() noexcept override;
    };
}

#endif //GAMEENGINE_SCRIPT_H
