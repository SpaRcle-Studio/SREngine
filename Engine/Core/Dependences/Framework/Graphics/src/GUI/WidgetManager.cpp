//
// Created by Monika on 10.02.2022.
//

#include <GUI/WidgetManager.h>
#include <Debug.h>

void WidgetManager::Draw() {
    std::lock_guard<std::mutex> lock(m_mutex);

    for (auto&& [name, widget] : m_widgets)
        if (widget->IsOpen())
            widget->DrawWindow();
}

bool WidgetManager::Register(Widget *widget) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_widgets.count(widget->GetName()) == 1) {
        SRAssert(false);
        return false;
    }

    m_widgets.insert(std::make_pair(widget->GetName(), widget));

    return true;
}

bool WidgetManager::Remove(Widget *widget) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_widgets.count(widget->GetName()) == 0) {
        SRAssert(false);
        return false;
    }

    m_widgets.erase(widget->GetName());

    return true;
}

WidgetManager::~WidgetManager() {
    m_widgets.clear();
}

void WidgetManager::OnKeyDown(const KeyDownEvent &event) {
    std::lock_guard<std::mutex> lock(m_mutex);

    for (auto&& [name, pWidget] : m_widgets)
        pWidget->OnKeyDown(event);
}

void WidgetManager::OnKeyUp(const KeyUpEvent &event) {
    std::lock_guard<std::mutex> lock(m_mutex);

    for (auto&& [name, pWidget] : m_widgets)
        pWidget->OnKeyUp(event);
}
