//
// Created by Monika on 17.02.2022.
//

#ifndef SRENGINE_EVENTDISPATCHER_H
#define SRENGINE_EVENTDISPATCHER_H

#include <unordered_map>
#include <unordered_set>
#include <Debug.h>

namespace Framework::Helper {
    class IEvent;

    class EventDispatcher {
    public:
        EventDispatcher() = default;
        virtual ~EventDispatcher();

    public:
        void UnregisterAll();
        void Register(IEvent* event);
        void Unregister(IEvent* event);

        template <typename T, typename ..._args> void Dispatch(_args...a) {
            Dispatch(typeid(T).name(), a...);
        }

        template <typename ..._args> void Dispatch(const std::string& eventName, _args...a) {
            auto&& eventList = m_events.find(eventName);

            if (eventList == m_events.end())
                return;

            for (auto&& iEvent : eventList->second) {
                if (Event<_args...> * pEvent = dynamic_cast<Event<_args...>*>(iEvent))
                    pEvent->Trigger(a...);
                else {
                    SRAssert(false);
                }
            }
        }

    private:
        std::unordered_map<std::string, std::unordered_set<IEvent*>> m_events;

    };
}

#endif //SRENGINE_EVENTDISPATCHER_H
