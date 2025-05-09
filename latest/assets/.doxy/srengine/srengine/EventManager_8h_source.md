

# File EventManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Events**](dir_44d7275059ecd594487e039c74bc8965.md) **>** [**EventManager.h**](EventManager_8h.md)

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


