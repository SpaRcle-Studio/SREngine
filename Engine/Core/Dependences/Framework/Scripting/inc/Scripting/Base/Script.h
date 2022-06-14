//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_SCRIPT_H
#define GAMEENGINE_SCRIPT_H

#include <Utils/Debug.h>

namespace SR_SCRIPTING_NS {
    typedef std::chrono::high_resolution_clock::time_point Time;

    enum class ScriptType {
        EvoScript, Lua
    };

    class Compiler;

    class Script : private SR_UTILS_NS::NonCopyable {
    protected:
        Script(Compiler* compiler, const std::string& name, const std::string& path) {
            m_compiler = compiler;
            m_name     = name;
            m_path     = path;
        }

    public:
        ~Script() override = default;

    public:
        SR_NODISCARD bool IsAutoFree() const;

        virtual bool AwaitDestroy()          = 0;
        virtual bool Compile()               = 0;
        virtual bool DelayedDestroyAndFree() = 0;

        virtual void Awake()       = 0;
        virtual void Start()       = 0;
        virtual void Close()       = 0;
        virtual void Update()      = 0;
        virtual void FixedUpdate() = 0;
        virtual void OnGUI()       = 0;

    protected:
        Compiler*   m_compiler  = nullptr;
        std::string m_name      = "None";
        std::string m_path      = "None";
        Time        m_lastUpd   = {};

        bool        m_isStart   = false;
        bool        m_isDestroy = false;
        bool        m_autoFree  = false;

    };
}

#endif //GAMEENGINE_SCRIPT_H
