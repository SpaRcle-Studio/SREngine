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
    public:
        enum class Status {
            Unknown, FileMissing, SuccessfullyLoad, RuntimeError, MemoryExhausted, SyntaxError, UnexpectedError, Compiled
        };
    private:
        ~Script();
        Script(const std::string &path, Compiler* compiler);
    private:
        const std::string m_name = "Unknown";

        This            m_thisBridge       = This();

        Status          m_status           = Status::Unknown;
        Compiler*       m_compiler         = nullptr;

        lua_State *     L                  = nullptr;
        int             r	               = -1;

        bool            m_hasInit          = false;
        bool            m_hasAwake         = false;
        bool            m_hasStart         = false;
        bool            m_hasUpdate        = false;
        bool            m_hasFixedUpdate   = false;
        bool            m_hasClose         = false;

        bool            m_isDestroy        = false;

        bool            m_isInit           = false;
        bool            m_isAwake          = false;
        bool            m_isStart          = false;
        bool            m_isClose          = false;

        unsigned int    m_countUsePoints   = 0;
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

        [[nodiscard]] bool FunctionExists(const std::string& funName) noexcept;

        [[nodiscard]] inline bool IsNeedInit() const noexcept {
            return (m_hasInit && !m_isInit);
        }

        [[nodiscard]] inline bool IsNeedStart() const noexcept {
            return (m_hasStart && !m_isStart);
        }

        [[nodiscard]] inline bool IsDestroy() const noexcept { return m_isDestroy; }
        [[nodiscard]] inline Status GetStatus() const noexcept { return m_status; }

        [[nodiscard]] inline unsigned int GetCountUses() const noexcept { return m_countUsePoints; }
        inline bool AddUsePoint() noexcept {
            if (m_isDestroy) {
                Helper::Debug::Error("Script::AddUsePoint() : script is destroyed! Some thing went wrong...\n\tPath: "+m_name);
                return false;
            } else {
                this->m_countUsePoints++;
                return true;
            }
        }
        inline bool RemoveUsePoint() noexcept {
            if (m_countUsePoints == 0){
                Helper::Debug::Error("Script::RemoveUsePoint() : count uses point is equal zero! Some thing went wrong...\n\tPath: "+m_name);
                return false;
            } else {
                this->m_countUsePoints--;
                return true;
            }
        }

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
