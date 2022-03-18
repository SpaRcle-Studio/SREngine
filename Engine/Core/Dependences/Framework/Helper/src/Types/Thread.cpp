//
// Created by Monika on 18.03.2022.
//

#include <Types/Thread.h>

#ifdef SR_WIN32
    #include <Windows.h>
#endif

void Types::Thread::Sleep(uint64_t milliseconds) {
#ifdef SR_WIN32
    ::Sleep(static_cast<DWORD>(milliseconds));
#endif
}

