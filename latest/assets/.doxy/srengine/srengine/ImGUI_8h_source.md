

# File ImGUI.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**ImGUI.h**](ImGUI_8h.md)

[Go to the documentation of this file](ImGUI_8h.md)


```C++
//
// Created by Nikita on 15.03.2021.
//

#ifndef SR_ENGINE_UTILS_GUI_H
#define SR_ENGINE_UTILS_GUI_H

#ifndef SR_IMGUI_INCLUDE_CHECK
    #error "ImGui included in another code module! Please include ImGui only in Grpahics module!"
#endif

#include <Graphics/macros.h>

#include <Utils/Debug.h>
#include <Utils/Math/Vector2.h>

#ifdef SR_USE_IMGUI
    #define IMGUI_UNLIMITED_FRAME_RATE
    #define IMGUI_DEFINE_MATH_OPERATORS
    #define IMGUI_USE_WCHAR32

    #ifndef IM_ASSERT
        #define IM_ASSERT(_EXP) SRAssert1Once(_EXP)
    #endif

    #ifndef IM_ASSERT_USER_ERROR
        #define IM_ASSERT_USER_ERROR(_EXP, _MSG) SRAssert2Once(_EXP, _MSG)
    #endif

    #include <imgui.h>
    #include <misc/cpp/imgui_stdlib.h>
    #include <imgui_internal.h>

    #ifdef SR_WIN32
        #include <backends/imgui_impl_win32.h>
    #endif

    #ifdef SR_LINUX
        #include <backends/imgui_impl_glfw.h>
    #endif

    #ifdef SR_USE_VULKAN
        #include <backends/imgui_impl_vulkan.h>

        #ifdef min
            #undef min
        #endif

        #ifdef max
            #undef max
        #endif
    #endif

    #ifdef SR_USE_OPENGL
        #define GL_GLEXT_PROTOTYPES
        //#include <GL/glew.h>
        //#include <GL/wglew.h>
        #include <backends/imgui_impl_opengl3.h>
        #include <backends/imgui_impl_opengl3_loader.h>

        //#include <GL/gl3w.h>
    #endif

    #ifdef SR_USE_GLFW3
        #include <backends/imgui_impl_glfw.h>
    #endif
#endif

namespace SR_GRAPH_NS {
    enum class PipelineType : uint8_t;
    class Pipeline;
}


#endif //SR_ENGINE_UTILS_GUI_H
```


