

# File Widget.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**Widget.h**](Widget_8h.md)

[Go to the documentation of this file](Widget_8h.md)


```C++
//
// Created by Monika on 10.02.2022.
//

#ifndef SR_ENGINE_GRAPHICS_WIDGET_H
#define SR_ENGINE_GRAPHICS_WIDGET_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/Function.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/Input/InputHandler.h>

#include <Graphics/GUI/ImGUI.h>

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderContext;
}

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_GRAPH_GUI_NS {
    class WidgetManager;
    typedef ImGuiWindowFlags WindowFlags;

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

        virtual void Init() { }

        virtual void SetSize(const SR_MATH_NS::IVector2& size) { m_size = size; }

        virtual bool OpenFile(const SR_UTILS_NS::Path& path) { return false; }

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
        WindowFlags m_windowFlags = ImGuiWindowFlags_None;
        SR_MATH_NS::IVector2 m_size;
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


