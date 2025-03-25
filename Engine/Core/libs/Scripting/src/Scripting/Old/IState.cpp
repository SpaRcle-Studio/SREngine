//
// Created by Nikita on 08.07.2021.
//

#include <EvoScript/IState.h>

#ifdef ES_WIN32
    #include <EvoScript/Win32State.hpp>
#endif

#ifdef ES_GCC
    #include <EvoScript/LinuxState.hpp>
#endif

EvoScript::IState *EvoScript::IState::Allocate(const std::string &path) {
    #ifdef ES_WIN32
        return new Win32State(path);
    #elif defined(ES_GCC)
        return new LinuxState(path);
    #else
        ES_ERROR("IState::Allocate() : unsupported platform!");
        return nullptr;
    #endif
}
