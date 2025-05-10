

# File ImGUI.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**ImGUI.h**](ImGUI_8h.md)

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


