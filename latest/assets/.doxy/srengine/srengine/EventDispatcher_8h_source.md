

# File EventDispatcher.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Events**](dir_44d7275059ecd594487e039c74bc8965.md) **>** [**EventDispatcher.h**](EventDispatcher_8h.md)

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


