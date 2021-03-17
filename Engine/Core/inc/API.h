//
// Created by Monika on 14.02.2021.
//

#ifndef GAMEENGINE_API_H
#define GAMEENGINE_API_H

#include <Compiler.h>
#include <Editor.h>

namespace Framework {
    class API{
    public:
        API() = delete;
        API(API&) = delete;
        API(const API&) = delete;
        ~API() = delete;
    public:
        static void Register(Framework::Scripting::Compiler* compiler);
    };
}

#endif //GAMEENGINE_API_H
