//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_SCRIPT_H
#define GAMEENGINE_SCRIPT_H

#include <string>
#include <ctime>
#include <ratio>
#include <chrono>

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
        Compiler*   m_compiler = nullptr;
        std::string m_name     = "None";
        std::string m_path     = "None";
        Time        m_lastUpd  = {};

        bool        m_isStart  = false;
    public:
        virtual void Free()    = 0;
        virtual bool Destroy() = 0;
        virtual bool Compile() = 0;
    public:
        virtual void Awake()       = 0;
        virtual void Start()       = 0;
        virtual void Close()       = 0;
        virtual void Update()      = 0;
        virtual void FixedUpdate() = 0;
    public:
        static Scripting::Script* Allocate(
                const std::string& name,
                const std::string& path,
                Compiler* compiler,
                ScriptType type);
    };
}

#endif //GAMEENGINE_SCRIPT_H
