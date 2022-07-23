//
// Created by Nikita on 21.03.2021.
//

#ifndef GAMEENGINE_MACROS_H
#define GAMEENGINE_MACROS_H

#pragma warning(disable: 4553)
#pragma warning(disable: 4552)

#define CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _HAS_AUTO_PTR_ETC 1

#define SR_USE_IMGUI

#ifdef _MSVC_LANG
    #define SR_MSVC
#endif

#ifdef __GNUC__
    #define SR_GCC
#endif

#if defined(__MINGW64__) || defined(__MINGW32__)
    #define SR_MINGW
#endif

/// если использовать только один из, то Debug будет определяться,
/// но может возникнуть ситуация, что в разных частях движка будут неправильно работать макросы.
/// Привет, Visual Studio
/// #if defined(NDEBUG) || defined(_DEBUG)

#if defined(SR_MSVC)
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
#endif

#define SR_SAFE_DELETE_PTR(ptr) \
    if (ptr) {                  \
        delete ptr;             \
        ptr = nullptr;          \
    }                           \

#define SR_COMBINE_HELPER(X, Y) X##Y
#define SR_COMBINE(X, Y) SR_COMBINE_HELPER(X, Y)
#define SR_FASTCALL_ATTRIBUTE __attribute__((fastcall))
#define SR_FASTCALL __fastcall
#define SR_CONSTEXPR constexpr
#define SR_FORCE_INLINE __forceinline
#define SR_NODISCARD [[nodiscard]]
#define SR_FALLTHROUGH [[fallthrough]]
#define SR_MAYBE_UNUSED [[maybe_unused]]
#define SR_DEPRECATED_EX(text) [[deprecated(text)]]
#define SR_DEPRECATED [[deprecated]]
#define SR_MAYBE_UNUSED_VAR [[maybe_unused]] auto&& SR_COMBINE(unused_var, __LINE__) =
#define SR_INLINE inline
#define SR_INLINE_STATIC SR_INLINE static
#define SR_NULL 0
#define SR_MARSHAL_USE_LIST 1
#define SR_MARSHAL_ENCODE_AND_DECODE 0
#define SR_INVALID_STR_POS -1
#define SR_ID_INVALID -1
#define SR_SHADER_PROGRAM int32_t
#define SR_NULL_SHADER -1
#define SR_VERTEX_DESCRIPTION size_t
#define GLM_ENABLE_EXPERIMENTAL
#define SR_NOOP (void)0

#define SR_FAST_CONSTRUCTOR SR_FORCE_INLINE SR_CONSTEXPR

#ifndef SR_USE_GLFW3
    #define SR_USE_GLFW3
#endif

#ifndef SR_USE_IMGUI
    #define SR_USE_IMGUI
    #define SR_USE_IMGUIZMO
#endif

#if defined(SR_USE_IMGUI) and not defined(SR_USE_IMGUIZMO)
    #define SR_USE_IMGUIZMO
#endif

#if defined(SR_USE_IMGUI) and not defined(SR_USE_IMGUI_NODE_EDITOR)
    #define SR_USE_IMGUI_NODE_EDITOR
#endif

#ifndef SR_USE_VULKAN
    #define SR_USE_VULKAN
    #define VK_PROTOTYPES
#endif

#ifndef SR_USE_OPENGL
    #define SR_USE_OPENGL
    #define IMGUI_IMPL_OPENGL_LOADER_GLFW
    //#define GL_GLEXT_PROTOTYPES
    //#define GL_VERSION_1_0
    //#define GL_VERSION_1_1
    //#define GL_VERSION_1_3
#endif

#ifdef WIN32
    #define SR_WIN32_BOOL true
    #define SR_WIN32
    #define WIN32_LEAN_AND_MEAN /// Исключите редко используемые компоненты из заголовков Windows
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
#else
    #define SR_WIN32_BOOL false
#endif

#define SR_XML_NS Framework::Helper::Xml
#define SR_UTILS_NS Framework::Helper
#define SR_PLATFORM_NS Framework::Helper::Platform
#define SR_MATH_NS Framework::Helper::Math
#define SR_GRAPH_NS Framework::Graphics
#define SR_HTYPES_NS SR_UTILS_NS::Types
#define SR_GTYPES_NS SR_GRAPH_NS::Types
#define SR_WORLD_NS Framework::Helper::World
#define SR_CORE_NS Framework::Core
#define SR_SCRIPTING_NS Framework::Scripting
#define SR_AUDIO_NS Framework::Audio

#define SR_GLOBAL_LOCK static std::mutex codegenGlobalMutex##__LINE__; std::lock_guard<std::mutex> codegenLock##__LINE__(codegenGlobalMutex##__LINE__);

//#define SR_STATIC_ASSERT2(expr, msg)

#if defined(SR_MINGW) || (_MSC_VER > 1929)
    #define SR_STATIC_ASSERT(msg) static_assert(msg);
#else
    #define SR_STATIC_ASSERT(msg) static_assert(false, msg);
#endif

#define SR_DLL_EXPORTS 1

#ifndef SR_LINUX
    #if defined(SR_DLL_EXPORTS)
        #define SR_DLL_EXPORT __declspec(dllexport)
    #else
        #define SR_DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define SR_DLL_EXPORT
#endif

#if defined(SR_MSVC)
    #define SR_STRCMPI _strcmpi
#else
    #define SR_STRCMPI strcasecmp
#endif

#endif //GAMEENGINE_MACROS_H
