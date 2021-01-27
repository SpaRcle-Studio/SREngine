//
// Created by Nikita on 27.01.2021.
//

#ifndef GAMEENGINE_EVENTMANAGER_H
#define GAMEENGINE_EVENTMANAGER_H

#include <functional>
#include <mutex>
#include <utility>
#include <vector>

namespace Framework::Helper {
    // Global event manager

    class EventManager {
    public:
        enum class Event {
            Exit, Fatal
        };
    public:
        EventManager() = delete;
        EventManager(EventManager&) = delete;
        ~EventManager() = delete;
    public:
        inline static void Subscribe(std::function<void(Event)> handler) {
            g_mutex.lock();

            EventManager::g_handler = std::move(handler);

            g_mutex.unlock();
        }
        inline static void Push(EventManager::Event event){
            g_mutex.lock();

            EventManager::g_events.push_back(event);
            EventManager::g_countEvents++;

            g_mutex.unlock();
        }
        inline static void PoolEvents() {
            if (!g_countEvents)
                return;

            g_mutex.lock();

            for (auto& event : g_events)
                g_handler(event);

            g_countEvents = 0;
            g_events.clear();

            g_mutex.unlock();
        }
    private:
        inline static std::function<void(Event)> g_handler = std::function<void(Event)>();
        inline static size_t g_countEvents = 0;
        inline static std::vector<Event> g_events = std::vector<Event>();
        inline static std::mutex g_mutex = std::mutex();
    };
}

#endif //GAMEENGINE_EVENTMANAGER_H
