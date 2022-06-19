//
// Created by Monika on 10.05.2022.
//

#ifndef SRENGINE_THREADUTILS_H
#define SRENGINE_THREADUTILS_H

#include <Utils/Common/Enumerations.h>

namespace SR_UTILS_NS {
    SR_ENUM_CLASS(ThreadPriority,
          SR_THREAD_PRIORITY_ABOVE_NORMAL,
          SR_THREAD_PRIORITY_BELOW_NORMAL,
          SR_THREAD_PRIORITY_HIGHEST,
          SR_THREAD_PRIORITY_IDLE,
          SR_THREAD_PRIORITY_LOWEST,
          SR_THREAD_PRIORITY_NORMAL,
          SR_THREAD_PRIORITY_TIME_CRITICAL,
    );

    SR_INLINE std::string GetThreadId(const std::thread& thread) {
        std::stringstream stream;
        stream << thread.get_id();
        return stream.str();
    }

    SR_INLINE std::string GetThisThreadId() {
        std::stringstream stream;
        stream << std::this_thread::get_id();
        return stream.str();
    }
}

#endif //SRENGINE_THREADUTILS_H
