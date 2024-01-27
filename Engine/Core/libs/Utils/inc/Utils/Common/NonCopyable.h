//
// Created by Monika on 16.01.2022.
//

#ifndef SR_ENGINE_NONCOPYABLE_H
#define SR_ENGINE_NONCOPYABLE_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT NonCopyable {
    protected:
        constexpr NonCopyable() = default;
        virtual ~NonCopyable() = default;

        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

#endif //SR_ENGINE_NONCOPYABLE_H
