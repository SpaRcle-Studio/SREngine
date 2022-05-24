//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_COMPILER_H
#define GAMEENGINE_COMPILER_H

#include <Scripting/Base/Script.h>

namespace SR_SCRIPTING_NS {
    class Compiler : SR_UTILS_NS::NonCopyable {
        using Mutex = std::recursive_mutex;
    protected:
        Compiler() = default;

    public:
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

    protected:
        Mutex m_mutex = Mutex();

        std::set<Script*> m_scripts        = {};
        std::set<Script*> m_scriptsToAdd   = {};
        std::set<Script*> m_scriptsToDel   = {};

    };
}

#endif //GAMEENGINE_COMPILER_H
