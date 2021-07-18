//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_COMPILER_H
#define GAMEENGINE_COMPILER_H

#include <Base/Script.h>

#include <vector>
#include <set>
#include <mutex>

namespace Framework::Scripting {
    class Compiler {
    protected:
        Compiler() = default;
        virtual ~Compiler() = default;
    public:
        Compiler(const Compiler&) = delete;
    protected:
        std::set<Script*> m_scripts = {};
        std::mutex        m_mutex   = std::mutex();
    public:
        void UpdateAll();
        void FixedUpdateAll();
    public:
        void RegisterScript(Script* script);
        void RemoveScript(Script* script);
    public:
        virtual bool Init()    = 0;
        virtual bool Destroy() = 0;
        virtual void Free()    = 0;
    };
}

#endif //GAMEENGINE_COMPILER_H
