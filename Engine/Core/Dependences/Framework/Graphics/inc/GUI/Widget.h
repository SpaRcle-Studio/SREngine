//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_WIDGET_H
#define SRENGINE_WIDGET_H

#include <Utils/GUI.h>

#include <Utils/Common/NonCopyable.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/Input/InputHandler.h>

namespace SR_GRAPH_NS::GUI {
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
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
    public:
        explicit Widget(std::string name, SR_MATH_NS::IVector2 size = SR_MATH_NS::IVector2MAX)
            : m_name(std::move(name))
            , m_open(false)
            , m_center(false)
            , m_internalFlags(WIDGET_FLAG_NONE)
            , m_windowFlags(ImGuiWindowFlags_::ImGuiWindowFlags_None)
            , m_size(size)
            , m_widgetFlags(WIDGET_FLAG_NONE)
            , m_manager(nullptr)
        { }

        ~Widget() override = default;

    public:
        SR_NODISCARD bool IsOpen() const { return m_open; }
        SR_NODISCARD bool IsFocused() const { return m_internalFlags & WIDGET_FLAG_FOCUSED; }
        SR_NODISCARD bool IsHovered() const { return m_internalFlags & WIDGET_FLAG_HOVERED; }
        SR_NODISCARD WidgetManager* GetManager() const { return m_manager; }
        SR_NODISCARD std::string GetName() const { return m_name; }
        SR_NODISCARD RenderScenePtr GetRenderScene() const;

        virtual void Open();
        virtual void Close();

        void DrawSubWindow();

    protected:
        virtual void Draw() = 0;
        virtual void OnClose() { }
        virtual void OnOpen() { }

        void SetCenter(bool value) { m_center = value; }
        void SetName(const std::string& name) { m_name = name; }
        void SetFlags(WindowFlags flags) { m_windowFlags = flags; }

        void TextCenter(const std::string& text) const;

        void CheckFocused();
        void CheckHovered();

    private:
        void SetManager(WidgetManager* manager);

        void InternalCheckFocused();
        void InternalCheckHovered();
        void DrawWindow();

    private:
        std::string m_name;
        std::atomic<bool> m_open;
        std::atomic<bool> m_center;
        std::atomic<WidgetFlagBits> m_internalFlags;
        WindowFlags m_windowFlags;
        SR_MATH_NS::IVector2 m_size;
        WidgetManager* m_manager;

    protected:
        mutable std::recursive_mutex m_mutex;
        WidgetFlagBits m_widgetFlags;

    };
}

#endif //SRENGINE_WIDGET_H
