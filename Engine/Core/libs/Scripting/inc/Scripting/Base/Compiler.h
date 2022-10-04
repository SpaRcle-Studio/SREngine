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
        virtual bool Init() = 0;

    protected:
        Mutex m_mutex = Mutex();

    };
}

#endif //GAMEENGINE_COMPILER_H
