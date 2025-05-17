

# File macros.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**macros.h**](libs_2Utils_2inc_2Utils_2macros_8h.md)

[Go to the documentation of this file](libs_2Utils_2inc_2Utils_2macros_8h.md)


```C++
//
// Created by Nikita on 21.03.2021.
//

#ifndef SR_COMMON_MACROS_H
#define SR_COMMON_MACROS_H

#ifdef _WINDOWS_
    #error "Windows.h was included before macros.h"
#endif

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#if defined(_MSVC_LANG)
    static_assert(sizeof(size_t) == 8, "The engine supports only 64-bit systems!");

    #pragma warning(disable: 4553)
    #pragma warning(disable: 4552)
    #pragma warning(disable: 5033)
    #pragma warning(disable: 4067)
    #pragma warning(disable: 4828)
#endif

#ifdef ANDROID
    #pragma clang diagnostic ignored "-Wunused-private-field"
    #pragma clang diagnostic ignored "-Wdeprecated-volatile"
    #pragma clang diagnostic ignored "-Wdefaulted-function-deleted"
    #pragma clang diagnostic ignored "-Winconsistent-missing-override"
    #pragma clang diagnostic ignored "-Wunused-variable"
    #pragma clang diagnostic ignored "-Wlogical-op-parentheses"
    #pragma clang diagnostic ignored "-Wreorder-ctor"
    #pragma clang diagnostic ignored "-Wunused-function"
    #pragma clang diagnostic ignored "-Wmismatched-tags"
    #pragma clang diagnostic ignored "-Woverloaded-virtual"
    #pragma clang diagnostic ignored "-Wunused-label"
    #pragma clang diagnostic ignored "-Wformat-security"
    #pragma clang diagnostic ignored "-Wreturn-type"
    #pragma clang diagnostic ignored "-Wdelete-incomplete"
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
    #pragma clang diagnostic ignored "-Wignored-attributes"
    #pragma clang diagnostic ignored "-Wunused-command-line-argument"
    #pragma clang diagnostic ignored "-Wc++20-attribute-extensions"
    #define SR_ANDROID
#else
    #ifdef __linux__
        #define SR_LINUX
    #endif
#endif

#ifdef __clang__
    #define SR_CLANG
#endif

#define CRT_SECURE_NO_WARNINGS

#ifndef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
    #define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif

#ifndef _HAS_AUTO_PTR_ETC
    #define _HAS_AUTO_PTR_ETC 1
#endif

#define TRUE 1
#define FALSE 0

#ifdef _MSVC_LANG
    #define SR_MSVC
#endif

#ifdef __clang__
    #define SR_CLANG
#endif


#ifdef __GNUC__
    #define SR_GCC
#endif

#if defined(__MINGW64__) || defined(__MINGW32__)
    #define SR_MINGW
#endif

#ifdef __has_cpp_attribute
    #define SR_HAS_ATTRIBUTE __has_cpp_attribute
#else
    #define SR_HAS_ATTRIBUTE(x) (0)
#endif

#if SR_HAS_ATTRIBUTE(likely) || defined(SR_MSVC)
    #define SR_LIKELY_ATTRIBUTE [[likely]]
    #define SR_UNLIKELY_ATTRIBUTE [[unlikely]]
#else
    #define SR_LIKELY_ATTRIBUTE
    #define SR_UNLIKELY_ATTRIBUTE
#endif

#ifdef __GNUC__
    #define SR_LIKELY(x) __builtin_expect((x), 1)
    #define SR_UNLIKELY(x) __builtin_expect((x), 0)
#else
    #define SR_LIKELY(x) (x)
    #define SR_UNLIKELY(x) (x)
#endif


#if defined(SR_MSVC)
    #define SR_MSC_VERSION _MSC_VER
    #if defined(_DEBUG)
        #define SR_DEBUG
    #elif defined(NDEBUG)
        #define SR_RELEASE
    #else
        #define SR_DEBUG
    #endif
#elif defined(SR_LINUX)
    #if defined(NDEBUG)
        #define SR_RELEASE
    #else
        #define SR_DEBUG
    #endif
#elif defined(SR_MINGW)
    #if defined(NDEBUG)
        #define SR_RELEASE
    #else
        #define SR_DEBUG
    #endif
#else
    #ifdef SR_ANDROID
        #define SR_RELEASE 
    #endif
#endif

#define SR_SAFE_DELETE_PTR(ptr) \
    if (ptr) {                  \
        delete ptr;             \
        ptr = nullptr;          \
    }                           \

#define SR_SAFE_DELETE_ARRAY_PTR(ptr) \
    if (ptr) {                        \
        delete[] ptr;                 \
        ptr = nullptr;                \
    }                                 \

#define SR_COMBINE_Utils(X, Y) X##Y
#define SR_COMBINE(X, Y) SR_COMBINE_Utils(X, Y)
#define SR_FASTCALL_ATTRIBUTE __attribute__((fastcall))
#define SR_CONSTEXPR constexpr
#define SR_INLINE inline

#if defined(SR_ANDROID)
    #define SR_FASTCALL
    #define SR_FORCE_INLINE SR_INLINE
#elif defined(SR_GCC)
    #define SR_FASTCALL
    #define SR_FORCE_INLINE __attribute__((always_inline))
#else
    #define SR_FASTCALL __fastcall
    #define SR_FORCE_INLINE __forceinline
#endif

#define SR_CLOCKS_PER_SEC 1000

#ifdef SR_GCC
    #define SR_NODISCARD __attribute__ ((__warn_unused_result__))
#else
    #define SR_NODISCARD [[nodiscard]]
#endif

#define SR_FALLTHROUGH [[fallthrough]]

#ifndef SR_ANDROID
    #define SR_DEPRECATED [[deprecated]]
    #define SR_DEPRECATED_EX(text) [[deprecated(text)]]
    #define SR_MAYBE_UNUSED [[maybe_unused]]
#else
    typedef int int32_t;
    #define SR_DEPRECATED
    #define SR_DEPRECATED_EX(text)
    #define SR_MAYBE_UNUSED
#endif

#define SR_MAYBE_UNUSED_VAR SR_MAYBE_UNUSED auto&& SR_COMBINE(unused_var, __LINE__) =
#define SR_INLINE_STATIC SR_INLINE static
#define SR_NULL 0
#define SR_MARSHAL_USE_LIST 1
#define SR_MARSHAL_ENCODE_AND_DECODE 0
#define SR_INVALID_STR_POS (-1)
#define SR_ID_INVALID (-1)
#define SR_SHADER_PROGRAM int32_t
#define SR_NULL_SHADER (-1)
#define SR_VERTEX_DESCRIPTION size_t
#define GLM_ENABLE_EXPERIMENTAL
#define SR_NOOP (void)0
#define SR_FLT_EPSILON FLT_EPSILON
#define SR_NORETURN [[noreturn]]

#define SR_MAX_BONES_ON_VERTEX 16
#define SR_HUMANOID_MAX_BONES 128

#define SR_FAST_CONSTRUCTOR SR_FORCE_INLINE SR_CONSTEXPR

#ifdef SR_USE_VULKAN
    #define VK_PROTOTYPES
#endif

#ifdef SR_USE_OPENGL
    #define IMGUI_IMPL_OPENGL_LOADER_GLFW
    //#define GL_GLEXT_PROTOTYPES
    //#define GL_VERSION_1_0
    //#define GL_VERSION_1_1
    //#define GL_VERSION_1_3
#endif

#define SR_UNUSED_VARIABLE(x) do { (void)(x); } while (0)

#ifdef WIN32
    #define SR_WIN32_BOOL true
    #define SR_WIN32
    #define WIN32_WINNT 0x0A00
    #define WIN32_LEAN_AND_MEAN 
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
#else
    #define SR_WIN32_BOOL false
#endif

#ifdef WIN32
    #define SR_SIMD_SUPPORT 1
#else
    #define SR_SIMD_SUPPORT 0
#endif

#define SR_MACRO_CONCAT_UTIL(a, b) a ## b
#define SR_MACRO_CONCAT(a, b) SR_MACRO_CONCAT_UTIL(a, b)
#define SR_STRINGIFY(x) #x
#define SR_EXPAND_AND_STRINGIFY(x) SR_STRINGIFY(x)
#define SR_PROTECT(...) __VA_ARGS__
#define SR_EXPAND(x) x

#define SR_LINE __LINE__

#define SR_AF_INET 2 
#define SR_SOCK_STREAM 1 
#define SR_INADDR_ANY (ULONG)0x00000000

#define SR_XML_NS SpaRcle::Utils::Xml
#define SR_YAML_NS SpaRcle::Utils::Yaml
#define SR_PHYSICS_NS SpaRcle::Physics
#define SR_PTYPES_NS SR_PHYSICS_NS::Types
#define SR_PHYSICS_UTILS_NS SR_PHYSICS_NS::Utils
#define SR_UTILS_NS SpaRcle::Utils
#define SR_SRLM_NS SR_UTILS_NS::SRLM
#define SR_NETWORK_NS SR_UTILS_NS::Network
#define SR_PLATFORM_NS SpaRcle::Utils::Platform
#define SR_MATH_NS SpaRcle::Utils::Math
#define SR_GRAPH_NS SpaRcle::Graphics
#define SR_SRSL_NS SpaRcle::Graphics::SRSL2
#define SR_GRAPH_UI_NS SpaRcle::Graphics::UI
#define SR_GRAPH_GUI_NS SpaRcle::Graphics::GUI
#define SR_ANIMATIONS_NS SpaRcle::Graphics::Animations
#define SR_HTYPES_NS SR_UTILS_NS::Types
#define SR_GTYPES_NS SR_GRAPH_NS::Types
#define SR_WORLD_NS SpaRcle::Utils::World
#define SR_CORE_NS SpaRcle::Core
#define SR_CORE_UI_NS SpaRcle::Core::UI
#define SR_CORE_GUI_NS SpaRcle::Core::GUI
#define SR_SCRIPTING_NS SpaRcle::Scripting
#define SR_AUDIO_NS SpaRcle::Audio
#define SR_UTILS_GUI_NS SR_UTILS_NS::GUI

#define SR_COUNT_ARGS_IMPL2(                                                                                            \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,                                                                            \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,                                                                   \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,                                                                   \
    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,                                                                   \
    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,                                                                   \
    _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,                                                                   \
    _61, _62, _63, _64, _65, _66, _67, _68, _69, _70,                                                                   \
    _71, _72, _73, _74, _75, _76, _77, _78, _79, _80,                                                                   \
    _81, _82, _83, _84, _85, _86, _87, _88, _89, _90,                                                                   \
    _91, _92, _93, _94, _95, _96, _97, _98, _99, _100,                                                                  \
    _101, _102, _103, _104, _105, _106, _107, _108, _109, _110,                                                         \
    _111, _112, _113, _114, _115, _116, _117, _118, _119, _120,                                                         \
    _121, _122, _123, _124, _125, N, ...) N

#define SR_COUNT_ARGS_IMPL(...) SR_EXPAND(SR_COUNT_ARGS_IMPL2(__VA_ARGS__))

#define SR_COUNT_ARGS(...) SR_COUNT_ARGS_IMPL(SR_PROTECT(__VA_ARGS__),                                                  \
    125, 124, 123, 122, 121, 120, 119, 118, 117,                                                                        \
    116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103,                                               \
    102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89,                                                          \
    88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75,                                                             \
    74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61,                                                             \
    60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47,                                                             \
    46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33,                                                             \
    32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,                                                             \
    18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5,                                                                  \
    4, 3, 2, 1, 0)

#define SR_GLOBAL_LOCK static std::mutex codegenGlobalMutex##__LINE__; std::lock_guard<std::mutex> codegenLock##__LINE__(codegenGlobalMutex##__LINE__);

#define SR_STATIC_ASSERT2(expr, msg) static_assert(expr, msg)

#if defined(SR_MINGW) || (SR_MSC_VERSION > 1929) || defined(SR_ANDROID) || defined(SR_LINUX)
    #define SR_STATIC_ASSERT(msg) static_assert(msg)
#else
    #define SR_STATIC_ASSERT(msg) static_assert(false, msg)
#endif

#define SR_RENDERER_DLL_API
#define SR_CORE_DLL_API

#if defined(SR_ANDROID)
    #define SR_DLL_API_IMPORT
    #define SR_DLL_API_EXPORT
#elif defined(SR_LINUX)
    #define SR_DLL_API_IMPORT __attribute__((visibility("default")))
    #define SR_DLL_API_EXPORT __attribute__((visibility("default")))
#else
    #define SR_DLL_API_IMPORT __declspec(dllimport)
    #define SR_DLL_API_EXPORT __declspec(dllexport)
#endif

#ifdef SR_ENGINE_SCRIPT_API_MODE
    #define SR_CODEGEN_DLL_API_IMPORT
    #define SR_CODEGEN_DLL_API_EXPORT
#else
    #define SR_CODEGEN_DLL_API_IMPORT SR_DLL_API_IMPORT
    #define SR_CODEGEN_DLL_API_EXPORT SR_DLL_API_EXPORT
#endif

#ifdef SR_COMMON_DLL_EXPORTS
    #define SR_COMMON_DLL_API SR_DLL_API_EXPORT
#else
    #define SR_COMMON_DLL_API SR_DLL_API_IMPORT
#endif

#if defined(SR_MSVC)
    #define SR_STRCMPI _strcmpi
    #define SR_STRNCPY strncpy_s
#else
    #define SR_STRCMPI strcasecmp
    #define SR_STRNCPY strncpy
#endif

#ifdef SR_MSVC
    #define SR_FUNCTION_SIGNATURE __FUNCSIG__
#else
#define SR_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define SR_GCC_CLANG_REMOVE_PADDING_ATTRIB __attribute__((packed)); // GCC/Clang: Убирает паддинг
#else
    #define SR_GCC_CLANG_REMOVE_PADDING_ATTRIB
#endif

#define SR_CODEGEN_HEADER_COMMENT "This file is generated by SpaRcle Studio code-generator ^_^"

#define SR_OFFSETOF(s,m) ((::size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))

namespace SR_UTILS_NS {
#if defined(SR_ANDROID) || defined(SR_EMSCRIPTEN)
    using SizeType = unsigned long;
#elif defined(SR_LINUX)
    using SizeType = long unsigned int;
#else
    using SizeType = unsigned long long int;
#endif

    template<typename T> struct RemoveReference      { using Type = T; };
    template<typename T> struct RemoveReference<T&>  { using Type = T; };
    template<typename T> struct RemoveReference<T&&> { using Type = T; };

    template<typename T>
    using RemoveReferenceT = typename RemoveReference<T>::Type;

    template<typename T> constexpr T&& Forward(RemoveReferenceT <T>& t) noexcept {
        return static_cast<T &&>(t);
    }

    template<typename T> constexpr T&& Forward(RemoveReferenceT <T>&& t) noexcept {
        return static_cast<T &&>(t);
    }
}

#include <cstdlib>

#include <Utils/Memory/Allocator.h>

#endif //SR_COMMON_MACROS_H
```


