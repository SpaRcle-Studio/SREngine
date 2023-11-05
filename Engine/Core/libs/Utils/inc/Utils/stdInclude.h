//
// Created by Monika on 07.04.2022.
//

#ifndef SRENGINE_STDINCLUDE_H
#define SRENGINE_STDINCLUDE_H

#include <Utils/macros.h>

#include <type_traits>
#include <stdio.h>
#include <iosfwd>
#include <regex>
#include <stdexcept>
#include <string_view>
#include <shared_mutex>
#include <cstdarg>
#include <initializer_list>
#include <codecvt>
#include <cstddef>
#include <unordered_set>
#include <stack>
#include <cctype>
#include <locale>
#include <cstring>
#include <variant>
#include <optional>
#include <memory>
#include <fstream>
#include <vector>
#include <ostream>
#include <queue>
#include <mutex>
#include <string>
#include <cassert>
#include <cmath>
#include <atomic>
#include <utility>
#include <array>
#include <map>
#include <functional>
#include <set>
#include <exception>
#include <unordered_map>
#include <algorithm>
#include <any>
#include <thread>
#include <cstdlib>
#include <sstream>
#include <list>
#include <ctime>
#include <iostream>
#include <ratio>
#include <chrono>
#include <random>
#include <cstdint>
#include <iomanip>
#include <condition_variable>

#ifdef SR_SUPPORT_PARALLEL
    #include <omp.h>
#endif

#if !defined(SR_ANDROID) && defined(SR_CXX_20)
    #include <forward_list>
#endif

#ifdef SR_MINGW
    #include <iomanip>
#endif

#ifdef SR_LINUX
    #include <cstdarg>
    #include <sys/stat.h>
    #include <signal.h>
#endif

#if defined(SR_WIN32)
    #include <direct.h>
#endif

/// C++17 - 201703L
/// C++14 - 201402L
/// C++11 - 201103L
/// C++98 - 199711L

namespace SR_UTILS_NS {
    #ifdef SR_LINUX
        using TimePointType = std::chrono::time_point<std::chrono::system_clock>;
    #else
        #ifdef SR_MINGW
            using TimePointType = std::chrono::high_resolution_clock::time_point;
        #else
            using TimePointType = std::chrono::time_point<std::chrono::steady_clock>;
        #endif
    #endif

    template<class T, class U = T> SR_NODISCARD static SR_FORCE_INLINE T SR_FASTCALL Exchange(T& obj, U&& new_value) noexcept {
        T old_value = std::move(obj);
        obj = std::forward<U>(new_value);
        return old_value;
    }

    template<template<class> class T, class U>
    struct IsDerivedFrom {
    private:
        template<class V> static decltype(static_cast<const T<V>&>(std::declval<U>()), std::true_type{}) test(const T<V>&); /// NOLINT
        static std::false_type test(...);                                                                                   /// NOLINT

    public:
        static constexpr bool value = decltype(IsDerivedFrom::test(std::declval<U>()))::value;

    };
}

#define SR_EXCHANGE(x, y) SR_UTILS_NS::Exchange(x, y)

#if 0
    namespace std {
        template<class T, class U = T>
        T exchange(T &obj, U &&new_value) {
            T old_value = std::move(obj);
            obj = std::forward<U>(new_value);
            return old_value;
        }
    }
#endif

#endif //SRENGINE_STDINCLUDE_H
