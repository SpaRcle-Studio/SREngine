

# File EventManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Events**](dir_e74a527d3186554a7cccdddc0bf2b7af.md) **>** [**EventManager.h**](EventManager_8h.md)

[Go to the documentation of this file](EventManager_8h.md)


```C++
//
// Created by Nikita on 27.01.2021.
//

#ifndef SR_ENGINE_EVENTMANAGER_H
#define SR_ENGINE_EVENTMANAGER_H

#include <Utils/Debug.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/Thread.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class EventManager : public Singleton<EventManager> {
        SR_REGISTER_SINGLETON(EventManager)
    private:
        ~EventManager() override = default;

    public:
        enum class Event {
            Exit, FatalError
        };

        using Subscription = SR_HTYPES_NS::Function<void(const Event&)>;

    public:
        void Subscribe(Subscription&& subHandler) {
            SR_LOCK_GUARD;
            m_subscriptions.emplace_back(std::move(subHandler));
        }

        void Broadcast(const Event& event){
            SR_LOCK_GUARD;

            for (auto&& subscription : m_subscriptions) {
                subscription(event);
            }
        }

    private:
        std::list<Subscription> m_subscriptions;

    };
}

#endif //SR_ENGINE_EVENTMANAGER_H
```


