//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_COMPILER_H
#define GAMEENGINE_COMPILER_H

#include <Base/Script.h>

namespace Framework::Scripting {
    class Compiler : SR_UTILS_NS::NonCopyable {
    protected:
        Compiler() = default;
        ~Compiler() override = default;

    public:
        void StartAll();
        void UpdateAll();
        void FixedUpdateAll();

    public:
        void RegisterScript(Script* script);
        void RemoveScript(Script* script);
        void PollEvents();
        bool Contains(Script* script);

    public:
        virtual bool Init()    = 0;
        virtual bool Destroy() = 0;
        virtual void Free()    = 0;

    protected:
        std::recursive_mutex m_mutex          = std::recursive_mutex();

        std::set<Script*>    m_scripts        = {};
        std::set<Script*>    m_scriptsToAdd   = {};
        std::set<Script*>    m_scriptsToDel   = {};

    };
}

#endif //GAMEENGINE_COMPILER_H
