//
// Created by Nikita on 21.03.2021.
//

#ifndef GAMEENGINE_MACROS_H
#define GAMEENGINE_MACROS_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#if defined(_MSVC_LANG)
    static_assert(sizeof(size_t) == 8, "The engine supports only 64-bit systems!");

    /// TODO: убрать подавления и перенести туда где они нужны
    #pragma warning(disable: 4553)
    #pragma warning(disable: 4552)
    #pragma warning(disable: 5033)
    #pragma warning(disable: 4067)
    #pragma warning(disable: 4828)
#endif

#ifdef ANDROID
    #define SR_ANDROID
#endif

#ifdef __linux__
    #define SR_LINUX
#endif

#ifdef __clang__
    #define SR_CLANG
#endif

#ifdef SR_ANDROID
    #pragma clang diagnostic ignored "-Wunused-private-field"
    #pragma clang diagnostic ignored "-Wdeprecated-volatile"
    #pragma clang diagnostic ignored "-Wdefaulted-function-deleted"
    #pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif

#define CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _HAS_AUTO_PTR_ETC 1

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

#ifdef __GNUC__
    #define SR_LIKELY(x) __builtin_expect((x), 1)
    #define SR_UNLIKELY(x) __builtin_expect((x), 0)
#else
    #define SR_LIKELY(x) (x)
    #define SR_UNLIKELY(x) (x)
#endif

/// если использовать только один из, то Debug будет определяться,
/// но может возникнуть ситуация, что в разных частях движка будут неправильно работать макросы.
/// Привет, Visual Studio
/// #if defined(NDEBUG) || defined(_DEBUG)

#if defined(SR_MSVC)
    #define SR_MSC_VERSION _MSC_VER
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

#ifdef SR_ANDROID
    #define SR_FASTCALL
    #define SR_FORCE_INLINE SR_INLINE
#elifdef SR_GCC
    #define SR_FASTCALL
    #define SR_FORCE_INLINE SR_INLINE
#else
    #define SR_FASTCALL __fastcall
    #define SR_FORCE_INLINE __forceinline
#endif

#define SR_CLOCKS_PER_SEC CLOCKS_PER_SEC
#define SR_NODISCARD [[nodiscard]]
#define SR_FALLTHROUGH [[fallthrough]]
#define SR_MAYBE_UNUSED [[maybe_unused]]
#define SR_DEPRECATED_EX(text) [[deprecated(text)]]
#define SR_DEPRECATED [[deprecated]]
#define SR_MAYBE_UNUSED_VAR [[maybe_unused]] auto&& SR_COMBINE(unused_var, __LINE__) =
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

#define SR_MAX_BONES_ON_VERTEX 8
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
    #define WIN32_LEAN_AND_MEAN /// Исключите редко используемые компоненты из заголовков Windows
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
#else
    #define SR_WIN32_BOOL false
#endif

#define SR_MACRO_CONCAT_UTIL(a, b) a ## b
#define SR_MACRO_CONCAT(a, b) SR_MACRO_CONCAT_UTIL(a, b)

#define SR_LINE __LINE__

#define SR_XML_NS SpaRcle::Utils::Xml
#define SR_PHYSICS_NS SpaRcle::Physics
#define SR_PTYPES_NS SR_PHYSICS_NS::Types
#define SR_PHYSICS_UTILS_NS SR_PHYSICS_NS::Utils
#define SR_UTILS_NS SpaRcle::Utils
#define SR_SRLM_NS SR_UTILS_NS::SRLM
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

#define SR_GLOBAL_LOCK static std::mutex codegenGlobalMutex##__LINE__; std::lock_guard<std::mutex> codegenLock##__LINE__(codegenGlobalMutex##__LINE__);

#define SR_STATIC_ASSERT2(expr, msg) static_assert(expr, msg);

#if defined(SR_MINGW) || (SR_MSC_VERSION > 1929) || defined(SR_ANDROID)
    #define SR_STATIC_ASSERT(msg) static_assert(msg);
#else
    #define SR_STATIC_ASSERT(msg) static_assert(false, msg);
#endif

#ifdef SR_LINUX
    #define SR_DLL_EXPORT
#else
    #if defined(SR_DLL_EXPORTS)
        #ifdef SR_ANDROID
            #define SR_DLL_EXPORT
        #else
            #define SR_DLL_EXPORT __declspec(dllexport)
        #endif
    #else
        #ifdef SR_ANDROID
            #define SR_DLL_EXPORT
        #else
            #define SR_DLL_EXPORT __declspec(dllimport)
        #endif
    #endif
#endif

#if defined(SR_MSVC)
    #define SR_STRCMPI _strcmpi
#else
    #define SR_STRCMPI strcasecmp
#endif

#ifdef SR_MSVC
    #define SR_FUNCTION_SIGNATURE __FUNCSIG__
#else
#define SR_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif

#define SR_OFFSETOF(s,m) ((::size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))

#endif //GAMEENGINE_MACROS_H
