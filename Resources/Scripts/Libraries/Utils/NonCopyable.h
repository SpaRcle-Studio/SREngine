//
// Created by Monika on 23.05.2022.
//

#ifndef EVOSCRIPTLIB_NONCOPYABLE_H
#define EVOSCRIPTLIB_NONCOPYABLE_H

#include <math.h>
#include <iostream>
#include <unordered_map>
#include <any>
#include <functional>

class NonCopyable {
protected:
    constexpr NonCopyable() = default;
    virtual ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

};

#endif //EVOSCRIPTLIB_NONCOPYABLE_H
