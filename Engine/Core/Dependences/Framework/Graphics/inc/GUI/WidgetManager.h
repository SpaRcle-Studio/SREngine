//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_WIDGETMANAGER_H
#define SRENGINE_WIDGETMANAGER_H

#include <macros.h>
#include <Utils/NonCopyable.h>
#include <Utils/Singleton.h>
#include <mutex>
#include <Input/InputHandler.h>
#include <Input/InputSystem.h>
#include <string>
#include <unordered_map>

namespace SR_GRAPH_NS::GUI {
    class Widget;

    typedef std::unordered_map<std::string, Widget*> Widgets;

    class WidgetManager : public Helper::NonCopyable, public Helper::InputHandler {
    public:
        WidgetManager();
        ~WidgetManager() override;

        virtual void Draw();

        bool Register(Widget* widget);
        bool Remove(Widget* widget);

    public:
        Widgets& GetWidgets() { return m_widgets; }

        void OnKeyDown(const Helper::KeyDownEvent& event) override;
        void OnKeyUp(const Helper::KeyUpEvent& event) override;

    private:
        std::mutex m_mutex;
        Widgets m_widgets;
        bool m_ignoreNonFocused;

    };

    class GlobalWidgetManager : public WidgetManager, public Helper::Singleton<GlobalWidgetManager> {
        friend class Helper::Singleton<GlobalWidgetManager>;
    public:
        ~GlobalWidgetManager() override = default;
    };
}

#endif //SRENGINE_WIDGETMANAGER_H
