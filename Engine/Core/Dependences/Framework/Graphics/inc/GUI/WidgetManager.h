//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_WIDGETMANAGER_H
#define SRENGINE_WIDGETMANAGER_H

#include <Utils/Types/Thread.h>
#include <Utils/Input/InputHandler.h>
#include <Utils/Input/InputSystem.h>

namespace SR_GRAPH_NS::GUI {
    class Widget;

    typedef std::unordered_map<std::string, Widget*> Widgets;

    class WidgetManager : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::InputHandler {
    public:
        WidgetManager();
        ~WidgetManager() override;

        virtual void Draw();

        bool Register(Widget* widget);
        bool Remove(Widget* widget);

    public:
        Widgets& GetWidgets() { return m_widgets; }

        void OnMouseDrag(const SR_UTILS_NS::MouseInputData* data) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;

    private:
        std::recursive_mutex m_mutex;
        Widgets m_widgets;
        bool m_ignoreNonFocused;

    };

    class GlobalWidgetManager : public WidgetManager, public SR_UTILS_NS::Singleton<GlobalWidgetManager> {
        friend class SR_UTILS_NS::Singleton<GlobalWidgetManager>;
    public:
        ~GlobalWidgetManager() override = default;
    };
}

#endif //SRENGINE_WIDGETMANAGER_H
