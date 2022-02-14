//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_WIDGETMANAGER_H
#define SRENGINE_WIDGETMANAGER_H

#include <macros.h>
#include <Utils/NonCopyable.h>
#include <Utils/Singleton.h>
#include <mutex>
#include <string>
#include <unordered_map>

namespace Framework::Graphics::GUI {
    class Widget;

    typedef std::unordered_map<std::string, Widget*> Widgets;

    class WidgetManager : public Helper::NonCopyable {
    public:
        ~WidgetManager() override;

        virtual void Draw();

        bool Register(Widget* widget);
        bool Remove(Widget* widget);

    public:
        Widgets& GetWidgets() { return m_widgets; }

    private:
        std::mutex m_mutex;
        Widgets m_widgets;

    };

    class GlobalWidgetManager : public WidgetManager, public Helper::Singleton<GlobalWidgetManager> {
        friend class Helper::Singleton<GlobalWidgetManager>;
    public:
        ~GlobalWidgetManager() override = default;
    };
}

#endif //SRENGINE_WIDGETMANAGER_H
