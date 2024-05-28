//
// Created by Monika on 09.08.2022.
//

#ifndef SR_ENGINE_ALLOCATOR_H
#define SR_ENGINE_ALLOCATOR_H

#include <Libraries/MemoryAllocator.h>

#pragma warning(disable: 4530)

void* operator new(size_t sz) {
    return ESMemoryAlloc(sz);
}

void operator delete(void* ptr) noexcept {
    ESMemoryFree(ptr);
}

void* operator new[](size_t sz) {
    return ESMemoryAlloc(sz);
}

void operator delete[](void* ptr) noexcept {
    ESMemoryFree(ptr);
}

#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <atomic>
#include <unordered_set>
#include <math.h>
#include <unordered_map>
#include <any>
#include <functional>
#include <utility>
#include <cmath>
#include <memory>
#include <ctype.h>

#define SR_INLINE inline

#if defined(SR_ANDROID)
    #define SR_FASTCALL
    #define SR_FORCE_INLINE SR_INLINE
#elif defined(SR_LINUX)
    #define SR_FASTCALL
    #define SR_FORCE_INLINE SR_INLINE
#else
    #define SR_FASTCALL __fastcall
    #define SR_FORCE_INLINE __forceinline
#endif

#define SR_SAFE_PTR_ASSERT(expr, msg)                                                                                  \
    if (!(expr)) {                                                                                                     \
        fprintf(stderr, "[SafePtr<%s>] %s\n\tLine: %i\n\tPtr: %p\n", typeid(T).name(), msg, __LINE__, (void *) m_ptr); \
    }                                                                                                                  \

#define SR_DLL_EXPORT
#define SR_NODISCARD [[nodiscard]]

#define SR_NEW_SAFE_PTR() { }
#define SR_DEL_SAFE_PTR() { }

#ifdef DEBUG
    #define EVK_DEBUG
#endif

#define SR_INF INFINITY
#define SR_NAN NAN
#define SR_INT16_MAX INT16_MAX
#define SR_UINT16_MAX UINT16_MAX
#define SR_UINT8_MAX UINT8_MAX
#define SR_INT8_MAX INT8_MAX
#define SR_INT32_MAX INT32_MAX
#define SR_INT32_MIN INT32_MIN
#define SR_UINT32_MAX UINT32_MAX
#define SR_INT64_MAX INT64_MAX
#define SR_UINT64_MAX UINT64_MAX
#define SR_UINTPTR_MAX UINTPTR_MAX
#define SR_DOUBLE_MAX DBL_MAX
#define SR_FLOAT_MAX FLT_MAX

namespace SR_UTILS_NS {
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


#endif //SR_ENGINE_ALLOCATOR_H
