//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_SCRIPT_H
#define GAMEENGINE_SCRIPT_H

#include <Debug.h>
#include <Utils/NonCopyable.h>

namespace Framework::Scripting {
    typedef std::chrono::high_resolution_clock::time_point Time;

    enum class ScriptType {
        EvoScript, Lua
    };

    class Compiler;

    class Script {
    protected:
        Script(Compiler* compiler, const std::string& name, const std::string& path) {
            this->m_compiler = compiler;
            this->m_name     = name;
            this->m_path     = path;
        }
        virtual ~Script() = default;
    public:
        Script(const Script&) = delete;
    protected:
        Compiler*   m_compiler             = nullptr;
        std::string m_name                 = "None";
        std::string m_path                 = "None";
        Time        m_lastUpd              = {};

        bool        m_isStart              = false;
        bool        m_isDestroy            = false;
        bool        m_needFreeAfterDestroy = false;
    public:
        virtual void ForcedFree()            = 0;
        virtual bool AwaitDestroy()          = 0;
        virtual bool Compile()               = 0;
        virtual bool DelayedDestroyAndFree() = 0;
    public:
        void Free() {
            if (m_needFreeAfterDestroy) {
                Helper::Debug::Error("Script::Free() : script will be automatically free after destroy!");
                return;
            }

            this->ForcedFree();
        }

        [[nodiscard]] bool IsNeedFreeAfterDestroy() const {
            return m_needFreeAfterDestroy;
        }
    public:
        virtual void Awake()       = 0;
        virtual void Start()       = 0;
        virtual void Close()       = 0;
        virtual void Update()      = 0;
        virtual void FixedUpdate() = 0;
        virtual void OnGUI()       = 0;
    public:
        static Scripting::Script* Allocate(
                const std::string& name,
                Compiler* compiler,
                ScriptType type);
    };
}

#endif //GAMEENGINE_SCRIPT_H
