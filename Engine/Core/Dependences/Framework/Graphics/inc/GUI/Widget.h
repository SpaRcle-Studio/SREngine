//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_WIDGET_H
#define SRENGINE_WIDGET_H

#include <GUI.h>
#include <atomic>
#include <utility>
#include <Utils/NonCopyable.h>

namespace Framework::Graphics::GUI {
    class WidgetManager;
    typedef ImGuiWindowFlags WindowFlags;

    class Widget : public Helper::NonCopyable {
        friend class WidgetManager;
    public:
        explicit Widget(std::string name)
            : m_name(std::move(name))
            , m_flags(ImGuiWindowFlags_::ImGuiWindowFlags_None)
            , m_open(false)
            , m_focused(false)
            , m_center(false)
        { }

        ~Widget() override = default;

    public:
        SR_NODISCARD bool IsOpen() const { return m_open; }
        SR_NODISCARD bool IsFocused() const { return m_focused; }

        virtual void Open() {
            if (!m_open)
                OnOpen();

            m_open = true;
        }
        virtual void Close() {
            if (m_open)
                OnClose();

            m_open = false;
        }

    protected:
        virtual void Draw() = 0;
        virtual void OnClose() { }
        virtual void OnOpen() { }

        void SetCenter(bool value) { m_center = value; }
        void SetName(const std::string& name) { m_name = name; }
        void SetFlags(WindowFlags flags) { m_flags = flags; }

        void TextCenter(const std::string& text);

        SR_NODISCARD std::string GetName() const { return m_name; }

    private:
        void DrawWindow();

    private:
        std::string m_name;
        std::atomic<bool> m_open;
        std::atomic<bool> m_focused;
        std::atomic<bool> m_center;
        WindowFlags m_flags;

    };
}

#endif //SRENGINE_WIDGET_H
