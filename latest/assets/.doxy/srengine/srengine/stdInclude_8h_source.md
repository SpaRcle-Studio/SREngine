

# File stdInclude.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**stdInclude.h**](stdInclude_8h.md)

[Go to the documentation of this file](stdInclude_8h.md)


```C++
//
// Created by Monika on 07.04.2022.
//

#ifndef SR_ENGINE_STDINCLUDE_H
#define SR_ENGINE_STDINCLUDE_H

#include <Utils/macros.h>

#include <string>
#include <array>
#include <map>
#include <vector>
#include <cstdint>
#include <set>
#include <optional>

#ifndef SR_ENGINE_CODEGEN_CLANG_PARSE_MODE
    #include <cfloat>
    #include <span>
    #include <limits>
    #include <type_traits>
    #include <cstdio>
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
    #include <memory>
    #include <fstream>
    #include <ostream>
    #include <queue>
    #include <mutex>
    #include <cassert>
    #include <cmath>
    #include <ranges>
    #include <atomic>
    #include <utility>
    #include <functional>
    #include <exception>
    #include <unordered_map>
    #include <algorithm>
    #include <any>
    #include <thread>
    #include <sstream>
    #include <list>
    #include <ctime>
    #include <iostream>
    #include <ratio>
    #include <chrono>
    #include <random>
    #include <iomanip>
    #include <concepts>
    #include <condition_variable>
    #include <numeric>
    #include <numbers>
    #include <execution>

    #ifndef SR_ENGINE_SCRIPT_API_MODE
        #include <zlib.h>
    #endif

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

    #include <fmt/format.h>
    #include <fmt/printf.h>
    #include <fmt/color.h>
#endif

#undef min
#undef max


inline std::string_view SRGetClassName(std::string_view func_signature) {
    // Для GCC/Clang
#ifdef __GNUC__
    auto start = func_signature.find("] ") + 2;
    auto end = func_signature.find_last_of(";");
#else  // Для MSVC
    auto start = func_signature.find("SRGetClassName<") + 15;
    auto end = func_signature.find_last_of('>');
#endif
    return func_signature.substr(start, end - start);
}

#ifdef _MSC_VER
    #define SR_GET_CLASS_NAME() SRGetClassName(__FUNCSIG__)
#else
    #define SR_GET_CLASS_NAME() SRGetClassName(__PRETTY_FUNCTION__)
#endif

#define SR_GET_COMPILE_TIME_CLASS_NAME(T) SR_UTILS_NS::GetCompileTimeTypeName<T>()

#define SR_IGNORE_UNUSED(...) SR_UTILS_NS::IgnoreUnused(__VA_ARGS__)

constexpr uint32_t SR_INVALID_VBO = SR_ID_INVALID;
constexpr uint32_t SR_INVALID_IBO = SR_ID_INVALID;
constexpr uint32_t SR_INVALID_UBO = SR_ID_INVALID;
constexpr uint32_t SR_INVALID_SSBO = SR_ID_INVALID;
constexpr uint32_t SR_INVALID_DESCRIPTOR_SET = SR_ID_INVALID;
constexpr uint32_t SR_INVALID_FBO = SR_ID_INVALID;

namespace SR_UTILS_NS {
    template <typename T> constexpr bool HasPublicDestructor() {
        if constexpr (!std::is_destructible_v<T>) {
            return false;
        }
        else if constexpr (std::is_final_v<T>) {
            return true;
        }
        else {
            struct Test : T { ~Test() = default; };
            return std::is_destructible_v<Test>;
        }
    }

    template<typename T> struct InputIteratorPointer final {
        using ValueType = T;
        using Pointer = T*;
        using Reference = T&;

        constexpr InputIteratorPointer(ValueType&& value) noexcept(std::is_nothrow_move_constructible_v<ValueType>) 
            : m_value { std::move(value) }
        { }

        SR_NODISCARD constexpr Pointer operator->() noexcept { return std::addressof(m_value); }
        SR_NODISCARD constexpr Reference operator*() noexcept { return m_value; }

    private:
        T m_value;
    };

    using namespace std::literals::string_literals;
    using namespace std::literals::string_view_literals;

    template<size_t N1, size_t N2> constexpr auto CompileTimeConcatStrings(const char(&s1)[N1], const char(&s2)[N2]) {
        char result[N1 + N2 - 1] = {};
        for (size_t i = 0; i < N1 - 1; ++i) {
            result[i] = s1[i];
        }
        for (size_t i = 0; i < N2; ++i) {
            result[N1 - 1 + i] = s2[i];
        }
        return result;
    }

    template<typename T> constexpr const char* GetCompileTimeTypeName() {
    #ifdef _MSC_VER
        return __FUNCSIG__;
    #else
        return __PRETTY_FUNCTION__;
    #endif
    }

    template <typename... T> SR_CONSTEXPR void IgnoreUnused(const T&...) { }

    template <class T> using RemoveQualifiersT = std::remove_const_t<std::remove_reference_t<std::remove_const_t<std::remove_volatile_t<T>>>>;

    template <class Alloc, class ValueType>
    using RebindAllocT = typename std::allocator_traits<Alloc>::template rebind_alloc<ValueType>;

    using SRHashType = uint64_t;

    #if defined(SR_LINUX) && !defined(SR_ANDROID)
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

    /*template <class Iterator, class = void>
    constexpr bool UnwrappableV = false;

    template <class Iterator> SR_NODISCARD SR_CONSTEXPR decltype(auto) GetUnwrapped(Iterator&& pIt) noexcept {
        if constexpr (std::is_pointer_v<std::decay_t<Iterator>>) { // special-case pointers and arrays
            return pIt + 0;
        }
        else {
            return static_cast<Iterator&&>(pIt);
        }
    }*/

    template <class InIt> SR_NODISCARD SR_CONSTEXPR uint64_t Distance(InIt pFirst, InIt pLast) {
        /*if constexpr (_Is_ranges_random_iter_v<_InIt>) {
            return pFirst - pLast;
        }
        else {
            auto pUFirst = GetUnwrapped(pFirst);
            const auto&& pULast = GetUnwrapped(pLast);

            uint64_t offset = 0;

            for (; pUFirst != pULast; ++pUFirst) {
                ++offset;
            }

            return offset;
        }*/

        
        uint64_t offset = 0;

        for (; pFirst != pLast; ++pFirst) {
            ++offset;
        }

        return offset;
    }

    template<template<class> class T, class U>
    struct IsDerivedFrom {
    private:
        template<class V> static decltype(static_cast<const T<V>&>(std::declval<U>()), std::true_type{}) test(const T<V>&); 
        static std::false_type test(...);                                                                                   

    public:
        static constexpr bool value = decltype(IsDerivedFrom::test(std::declval<U>()))::value;

    };

    template <class BaseT, class DerivedT>
    constexpr bool IsBaseOfV = std::is_base_of_v<BaseT, DerivedT>;

    template<typename T> constexpr bool IsVolatile() {
        return std::is_volatile<T>::value;
    }

    template<typename T> constexpr bool IsLogical() {
        if (!IsVolatile<T>()) {
            return IsLogical<volatile T>();
        }

        return std::is_same_v<T, volatile bool>;
    }
}

namespace SR_UTILS_NS {
    enum class EnumVariant : uint8_t {
        Undefined, List, Flags
    };
}

namespace Codegen {
    template <typename EnumType> struct EnumSelector {};

    template<typename T>
    constexpr SR_UTILS_NS::EnumVariant GetEnumVariant(T) noexcept {
        return SR_UTILS_NS::EnumVariant::Undefined;
    }

    template<typename T> constexpr size_t GetEnumItemsCount(T) noexcept {
        return 0;
    }
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

#endif //SR_ENGINE_STDINCLUDE_H
```


