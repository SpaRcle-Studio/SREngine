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

#include <string>
#include <Debug.h>
#include <EntityComponentSystem/Component.h>

namespace Framework::Scripting {
    class Compiler;

    class Script : public Helper::Component {
        friend class Compiler;

        enum class Status {
            Unknown, FileMissing, SuccessfullyLoad, RuntimeError, MemoryExhausted, SyntaxError, UnexpectedError, Compiled
        };
    private:
        ~Script();
        Script(const std::string &path, Compiler* compiler);
    private:
        const std::string m_name = "Unknown";

        Status m_status = Status::Unknown;
        Compiler* m_compiler = nullptr;

        lua_State * L   = nullptr;
        int         r	= -1;

        bool m_isDestoy = false;
        bool m_isStart  = false;
    public:
        bool Start();
        bool Update();
        bool FixedUpdate();
        bool Close();

        // After call script pointer will be free
        bool Destroy();

        bool Compile();
        bool ReCompile();
    protected:
        void OnDestroyGameObject() noexcept override;
    };
}

#endif //GAMEENGINE_SCRIPT_H
