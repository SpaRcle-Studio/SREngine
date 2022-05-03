//
// Created by Monika on 18.03.2022.
//

#include <Types/Thread.h>
#include <Platform/Platform.h>

namespace SR_HTYPES_NS {
    void Thread::Sleep(uint64_t milliseconds) {
        Platform::Sleep(milliseconds);
    }
}

