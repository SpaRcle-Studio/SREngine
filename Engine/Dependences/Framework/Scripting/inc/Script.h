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

#include <stack>

#include <functional>
#include <string>
#include <Debug.h>
#include <EntityComponentSystem/Component.h>

#include <Types/List.h>

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
            //inline Script* GetPointer() const noexcept{
            //    return script;
            //}
        };

        friend class Compiler;
    public:
        enum class Status {
            Unknown, FileMissing, SuccessfullyLoad, RuntimeError, MemoryExhausted, SyntaxError, UnexpectedError, Compiled, Closed, Destroyed
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

        //bool            m_callingNow       = false;
        std::mutex      m_mutex            = std::mutex();
        std::string     m_currentFunName   = "Unidentified";

        std::stack<void*> m_stack = std::stack<void*>();
    private:
        void CheckExistsFunctions();
        bool RegisterBaseTypes();
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

        template<typename T> static inline void RegisterList(const std::string& className, lua_State*L){
            luabridge::getGlobalNamespace(L)
                .beginClass<Types::List<T>>((className + "List").c_str())
                        .addFunction("Get", (T (Framework::Helper::Types::List<T>::*)(unsigned int))&Framework::Helper::Types::List<T>::Get)
                .endClass();
        }
        template<typename T> static inline void RegisterCasting(const std::string& className, lua_State*L){
            luabridge::getGlobalNamespace(L)
                    .beginNamespace("Stack")
                    //.beginClass<Script>("Script")
                        .addFunction(("Push"+className).c_str(), static_cast<void(*)(Script*, T)>([](Script*script, T type) {
                            script->Push((void*)type);
                        }))
                        .addFunction(("Pop"+className).c_str(), static_cast<T(*)(Script::This*)>([](Script::This* aThis) -> T {
                            return reinterpret_cast<T>(aThis->script->Pop());
                        }))
                    //.endClass();
                    .endNamespace();
        }

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
                Helper::Debug::Error("Script::AddUsePoint() : script is destroyed! Something went wrong...\n\tPath: "+m_name);
                return false;
            } else {
                this->m_countUsePoints++;
                return true;
            }
        }
        inline bool RemoveUsePoint() noexcept {
            if (m_countUsePoints == 0){
                Helper::Debug::Error("Script::RemoveUsePoint() : count uses point is equal zero! Something went wrong...\n\tPath: "+m_name);
                return false;
            } else {
                this->m_countUsePoints--;
                if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High && m_countUsePoints == 0)
                    Helper::Debug::Log("Script::RemoveUsePoint() : now counts uses equal zero.");
                return true;
            }
        }

        bool Call(const std::string& funName);
        inline void Push(void* data) {
            //std::cout << data << std::endl;
            m_stack.push(data);
        }
        void* Pop(){
            void* value = m_stack.top();
            m_stack.pop();
            return value;
        }
        //inline bool CallArgs(const std::string& funName){
        //    std::cout << "Call: " + funName + "\n";

            //if (data1) std::cout << type1 << std::endl;
           // if (data2) std::cout << type2 << std::endl;
        //}
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
