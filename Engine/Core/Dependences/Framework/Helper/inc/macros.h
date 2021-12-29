//
// Created by Nikita on 21.03.2021.
//

#ifndef GAMEENGINE_MACROS_H
#define GAMEENGINE_MACROS_H

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

#if (!defined(NDEBUG) && defined(SR_MSVC)) || (!defined(NDEBUG) && defined(SR_MINGW))
    #define SR_DEBUG
#else
    #define SR_RELEASE
#endif

#define SR_FORCE_INLINE __forceinline
#define SR_NULL 0

#ifndef SR_USE_GLFW3
    #define SR_USE_GLFW3
#endif

#ifndef SR_USE_IMGUI
    #define SR_USE_IMGUI
    #define SR_USE_IMGUIZMO
#endif

#if defined(SR_USE_IMGUI) and not (SR_USE_IMGUIZMO)
    #define SR_USE_IMGUIZMO
#endif

#ifndef SR_USE_VULKAN
    #define SR_USE_VULKAN
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
#else
    #define SR_WIN32_BOOL false
#endif

#endif //GAMEENGINE_MACROS_H
