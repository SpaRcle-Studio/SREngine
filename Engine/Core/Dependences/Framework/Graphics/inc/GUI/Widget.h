//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_WIDGET_H
#define SRENGINE_WIDGET_H

#include <GUI.h>
#include <atomic>
#include <utility>
#include <optional>
#include <Utils/NonCopyable.h>
#include <Input/InputSystem.h>
#include <Input/InputHandler.h>

namespace Framework::Graphics::GUI {
    class WidgetManager;
    typedef ImGuiWindowFlags WindowFlags;

    class Widget : public Helper::NonCopyable, public Helper::InputHandler {
        friend class WidgetManager;
    public:
        explicit Widget(std::string name, Helper::Math::IVector2 size = Helper::Math::IVector2MAX)
            : m_name(std::move(name))
            , m_open(false)
            , m_focused(false)
            , m_center(false)
            , m_flags(ImGuiWindowFlags_::ImGuiWindowFlags_None)
            , m_size(size)
        { }

        ~Widget() override = default;

    public:
        SR_NODISCARD bool IsOpen() const { return m_open; }
        SR_NODISCARD bool IsFocused() const { return m_focused; }

        virtual void Open();
        virtual void Close();

    protected:
        virtual void Draw() = 0;
        virtual void OnClose() { }
        virtual void OnOpen() { }

        void SetCenter(bool value) { m_center = value; }
        void SetName(const std::string& name) { m_name = name; }
        void SetFlags(WindowFlags flags) { m_flags = flags; }

        void TextCenter(const std::string& text) const;

        SR_NODISCARD std::string GetName() const { return m_name; }

    private:
        void DrawWindow();

    private:
        std::string m_name;
        std::atomic<bool> m_open;
        std::atomic<bool> m_focused;
        std::atomic<bool> m_center;
        WindowFlags m_flags;
        Helper::Math::IVector2 m_size;

    };
}

#endif //SRENGINE_WIDGET_H
