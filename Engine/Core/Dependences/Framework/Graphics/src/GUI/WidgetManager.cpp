//
// Created by Monika on 10.02.2022.
//

#include <GUI/WidgetManager.h>

#include <Utils/Debug.h>
#include <Utils/Common/Features.h>

namespace SR_GRAPH_NS::GUI {
    WidgetManager::WidgetManager()
        : SR_UTILS_NS::NonCopyable()
        , SR_UTILS_NS::InputHandler()
    {
        m_ignoreNonFocused = SR_UTILS_NS::Features::Instance().Enabled("InputIgnoreNonFocusedWidgets", true);
    }

    void WidgetManager::Draw() {
        SR_SCOPED_LOCK

        for (auto&&[name, widget] : m_widgets) {
            if (widget->IsOpen())
                widget->DrawWindow();
        }
    }

    bool WidgetManager::Register(Widget *widget) {
        SR_SCOPED_LOCK

        if (m_widgets.count(widget->GetName()) == 1) {
            SRHalt("Widget are already registered!");
            return false;
        }

        m_widgets.insert(std::make_pair(widget->GetName(), widget));

        widget->SetManager(this);

        return true;
    }

    bool WidgetManager::Remove(Widget *widget) {
        SR_SCOPED_LOCK

        if (m_widgets.count(widget->GetName()) == 0) {
            SRHalt("Widget are not registered!");
            return false;
        }

        m_widgets.erase(widget->GetName());

        widget->SetManager(nullptr);

        return true;
    }

    WidgetManager::~WidgetManager() {
        SRAssert2(m_widgets.empty(), "Memory leak possible!");
        m_widgets.clear();
    }

    void WidgetManager::OnKeyDown(const SR_UTILS_NS::KeyDownEvent &event) {
        SR_SCOPED_LOCK

        for (auto&&[name, pWidget] : m_widgets) {
            if (pWidget->IsFocused() || !m_ignoreNonFocused)
                pWidget->OnKeyDown(event);
        }
    }

    void WidgetManager::OnKeyUp(const SR_UTILS_NS::KeyUpEvent &event) {
        SR_SCOPED_LOCK

        for (auto&&[name, pWidget] : m_widgets) {
            if (pWidget->IsFocused() || !m_ignoreNonFocused)
                pWidget->OnKeyUp(event);
        }
    }
}