

# File EventDispatcher.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Events**](dir_e74a527d3186554a7cccdddc0bf2b7af.md) **>** [**EventDispatcher.h**](EventDispatcher_8h.md)

[Go to the documentation of this file](EventDispatcher_8h.md)


```C++
//
// Created by Monika on 17.02.2022.
//

#ifndef SR_ENGINE_EVENTDISPATCHER_H
#define SR_ENGINE_EVENTDISPATCHER_H

#include <Utils/Events/Event.h>

namespace SR_UTILS_NS {
    class IEvent;

    class SR_COMMON_DLL_API EventDispatcher {
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

#endif //SR_ENGINE_EVENTDISPATCHER_H
```


