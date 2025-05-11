

# File GLFWWindow.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Window**](dir_eceba3be4a9ee281baac1dc94ed42c6c.md) **>** [**GLFWWindow.h**](GLFWWindow_8h.md)

[Go to the documentation of this file](GLFWWindow_8h.md)


```C++
//
// Created by innerviewer on 2024-05-06.
//

#ifndef SR_ENGINE_GLFW_WINDOW_H
#define SR_ENGINE_GLFW_WINDOW_H

#include <Graphics/Window/BasicWindowImpl.h>
#include <GLFW/glfw3.h>

namespace SR_GRAPH_NS {
    class GLFWWindow : public BasicWindowImpl {
        using Super = BasicWindowImpl;
    public:
        explicit GLFWWindow()
                : Super()
        { }

    public:
        bool Initialize(const std::string& name,
                        const SR_MATH_NS::IVector2& position,
                        const SR_MATH_NS::UVector2& size,
                        bool fullScreen, bool resizable) override;

        void PollEvents() override;
    public:
        void OnSizeChangedCallback(GLFWwindow* pWindow, SR_MATH_NS::IVector2 size);
        void OnFramebufferSizeChangedCallback(GLFWwindow* pWindow, SR_MATH_NS::IVector2 size);
        void OnFocusChangedCallback(GLFWwindow* pWindow, bool isFocused);
        void OnWindowRefreshCallback(GLFWwindow* pWindow);
        void OnScrollCallback(GLFWwindow* pWindow, double xoffset, double yoffset);


    public:
        SR_NODISCARD WindowType GetType() const override { return WindowType::GLFW; };
        SR_NODISCARD void* GetHandle() const override { return static_cast<void*>(m_window); };
        SR_NODISCARD GLFWwindow* GetWindow() const { return m_window; }

        void SetIcon(const std::string& path) override;

    private:
        GLFWwindow* m_window = nullptr;
    };
}

#endif //SR_ENGINE_GLFW_WINDOW_H
```


