

# File AndroidEvent.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Platform**](dir_c017a2c280f4c252cdb104ea7a64a7b4.md) **>** [**AndroidEvent.h**](AndroidEvent_8h.md)

[Go to the documentation of this file](AndroidEvent_8h.md)


```C++
//
// Created by Monika on 19.09.2025.
//

#ifndef SR_ENGINE_COMMON_ANDROID_EVENT_H
#define SR_ENGINE_COMMON_ANDROID_EVENT_H

#include <Utils/Common/Singleton.h>

#include <android/sensor.h>

namespace SR_UTILS_NS {
    struct AndroidEvent {
        enum Type {
            Motion,
            Key,
            Lifecycle,
            Window,
            Sensor
        } type;

        union {
            struct { int32_t action; float x, y; int32_t pointerId; } motion;
            struct { int32_t keyCode; int32_t action; } key;
            struct { int32_t command; } lifecycle;
            struct { ANativeWindow* window; } windowEvent;
            struct { ASensorEvent sensor; } sensorEvent;
        };
    };

    class AndroidEventQueue : public Singleton<AndroidEventQueue> {
        SR_REGISTER_SINGLETON(AndroidEventQueue);
    public:
        void PushEvent(const AndroidEvent &event);
        bool PopEvent(AndroidEvent &event);

    private:
        std::list<AndroidEvent> m_events;

    };
}

#endif //SR_ENGINE_COMMON_ANDROID_EVENT_H
```


