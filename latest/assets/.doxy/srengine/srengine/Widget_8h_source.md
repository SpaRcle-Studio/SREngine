

# File Widget.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**Widget.h**](Widget_8h.md)

[Go to the documentation of this file](Widget_8h.md)


```C++
//
// Created by Monika on 10.02.2022.
//

#ifndef SR_ENGINE_GRAPHICS_WIDGET_H
#define SR_ENGINE_GRAPHICS_WIDGET_H

#include <Graphics/macros.h>

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/Function.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/Input/InputHandler.h>

#include <Graphics/GUI/ImmediateGUI.h>

#include <Enum/WindowFlags.hpp>

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderContext;
}

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_GRAPH_GUI_NS {
    class WidgetManager;

    enum WidgetFlags : uint32_t {
        WIDGET_FLAG_NONE         = 1 << 0, 
        WIDGET_FLAG_HOVERED      = 1 << 1, 
        WIDGET_FLAG_FOCUSED      = 1 << 2, 
    };
    typedef uint32_t WidgetFlagBits;

    class Widget : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::InputHandler {
        friend class WidgetManager;
        using Super = SR_UTILS_NS::InputHandler;
    public:
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;
        using ContextPtr = RenderContext*;
        using ScenePtr = SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;

    public:
        Widget() = default;

        explicit Widget(std::string name, SR_MATH_NS::IVector2 size = SR_MATH_NS::IVector2MAX)
            : m_name(std::move(name))
            , m_size(size)
        { }

        ~Widget() override;

    public:
        SR_NODISCARD bool IsOpen() const { return m_open; }
        SR_NODISCARD bool IsFocused() const { return m_internalFlags & WIDGET_FLAG_FOCUSED; }
        SR_NODISCARD bool IsHovered() const { return m_internalFlags & WIDGET_FLAG_HOVERED; }
        SR_NODISCARD WidgetManager* GetManager() const { return m_manager; }
        SR_NODISCARD const std::string& GetName() const { return m_name; }
        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD ContextPtr GetContext() const;
        SR_NODISCARD SR_HTYPES_NS::DataStorage& GetWeakStorage() const { return m_weakStorage; }
        SR_NODISCARD SR_HTYPES_NS::DataStorage& GetStrongStorage() const { return m_strongStorage; }

        void SetDefaultSize(const SR_MATH_NS::IVector2& size) { m_defaultSize = size; }

        virtual void Init() { }

        virtual void SetSize(const SR_MATH_NS::IVector2& size) { m_size = size; }

        virtual bool OpenFile(const SR_UTILS_NS::Path& path) { return false; }

        virtual void Focus();
        virtual void Open();
        virtual void Close();

        virtual void Update(float_t dt) { }
        virtual void FixedUpdate() { }

        virtual void SetScene(const ScenePtr& scene) { }

        void DrawAsSubWindow();

        void SetManager(WidgetManager* pManager);

        void AddSubWidget(Widget* pWidget);

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* pData) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* pData) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* pData) override;

    protected:
        virtual void Draw() = 0;
        virtual void OnClose() { }
        virtual void OnOpen() { }

        void SetCenter(bool value) { m_center = value; }
        void SetName(const std::string& name) { m_name = name; }
        void SetFlags(WindowFlags flags) { m_windowFlags = flags; }
        void AddFlags(WindowFlags flags) { m_windowFlags |= flags; }

        void TextCenter(const std::string& text) const;

        void ResetWeakStorage();
        void ResetStrongStorage();

        void CheckFocused();
        void CheckHovered();

    private:
        void InternalCheckFocused();
        void InternalCheckHovered();
        void DrawWindow();

    protected:
        std::vector<Widget*> m_subWidgets;

    private:
        std::string m_name;
        std::atomic<bool> m_open = false;
        std::atomic<bool> m_center = false;
        std::atomic<WidgetFlagBits> m_internalFlags = WIDGET_FLAG_NONE;
        WindowFlags m_windowFlags = WindowFlags::None;
        SR_MATH_NS::IVector2 m_size;
        SR_MATH_NS::IVector2 m_defaultSize;
        WidgetManager* m_manager = nullptr;

        mutable SR_HTYPES_NS::DataStorage m_weakStorage;
        mutable SR_HTYPES_NS::DataStorage m_strongStorage;

    protected:
        mutable std::recursive_mutex m_mutex;
        WidgetFlagBits m_widgetFlags = WIDGET_FLAG_NONE;

    };
}

#endif //SR_ENGINE_GRAPHICS_WIDGET_H
```


