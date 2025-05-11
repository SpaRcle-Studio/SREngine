

# File ThreadUtils.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**ThreadUtils.h**](ThreadUtils_8h.md)

[Go to the documentation of this file](ThreadUtils_8h.md)


```C++
//
// Created by Monika on 10.05.2022.
//

#ifndef SR_ENGINE_THREADUTILS_H
#define SR_ENGINE_THREADUTILS_H

#include <Utils/Common/Enumerations.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_T(ThreadPriority, int8_t,
          SR_THREAD_PRIORITY_ABOVE_NORMAL,
          SR_THREAD_PRIORITY_BELOW_NORMAL,
          SR_THREAD_PRIORITY_HIGHEST,
          SR_THREAD_PRIORITY_IDLE,
          SR_THREAD_PRIORITY_LOWEST,
          SR_THREAD_PRIORITY_NORMAL,
          SR_THREAD_PRIORITY_TIME_CRITICAL
    );

    SR_INLINE std::string GetThreadId(const std::thread& thread) {
        std::stringstream stream;
        stream << thread.get_id();

        if (stream.str() == "thread::id of a non-executing thread") {
            return std::string();
        }

        return stream.str();
    }

    SR_INLINE SR_UTILS_NS::StringAtom GetThisThreadId() {
        std::stringstream stream;
        stream << std::this_thread::get_id();
        return stream.str();
    }
}

#endif //SR_ENGINE_THREADUTILS_H
```


