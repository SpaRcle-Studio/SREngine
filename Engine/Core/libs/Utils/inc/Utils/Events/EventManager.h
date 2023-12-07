//
// Created by Nikita on 27.01.2021.
//

#ifndef GAMEENGINE_EVENTMANAGER_H
#define GAMEENGINE_EVENTMANAGER_H

#include <Utils/Debug.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/Thread.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT EventManager : public Singleton<EventManager> {
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

#endif //GAMEENGINE_EVENTMANAGER_H
