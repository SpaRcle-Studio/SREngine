

# File GLFWWindow.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Window**](dir_387552b0934ce9512c4f7c4e31a03e0f.md) **>** [**GLFWWindow.h**](GLFWWindow_8h.md)

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


