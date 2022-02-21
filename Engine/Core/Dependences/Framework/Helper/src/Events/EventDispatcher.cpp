//
// Created by Monika on 17.02.2022.
//

#include "Events/EventDispatcher.h"

namespace Framework::Helper {
    EventDispatcher::~EventDispatcher() {
        SRAssert(m_events.size() == 0);
    }

    void EventDispatcher::Register(IEvent *event) {
        if (event) {
            m_events[event->GetEventName()].insert(event);
        }
    }

    void EventDispatcher::Unregister(IEvent *event) {
        if (event) {
            auto&& groupIt = m_events.find(event->GetEventName());

            if (groupIt == m_events.end()) {
                SRAssert(false);
                return;
            }
            auto&& group = groupIt->second;

            if (auto&& pIt = group.find(event); pIt != group.end())
                group.erase(pIt);
            else
                SRAssert(false);

            if (group.size() == 0)
                m_events.erase(groupIt);
        }
    }

    void EventDispatcher::UnregisterAll() {
        m_events.clear();
    }
}