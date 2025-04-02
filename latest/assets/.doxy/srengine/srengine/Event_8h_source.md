

# File Event.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Events**](dir_44d7275059ecd594487e039c74bc8965.md) **>** [**Event.h**](Event_8h.md)

[Go to the documentation of this file](Event_8h.md)


```C++
//
// Created by Monika on 17.02.2022.
//

#ifndef SR_ENGINE_EVENT_H
#define SR_ENGINE_EVENT_H

#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT IEvent {
    protected:
        IEvent() = default;
        virtual ~IEvent() = default;

    public:
        SR_NODISCARD virtual const std::string& GetEventName() const = 0;

    };

    template <typename ..._args> class SR_DLL_EXPORT Event : public IEvent {
        using CallBack = std::function<void(_args...)>;
    public:
        explicit Event(std::string name)
            : m_name(std::move(name))
        { }

        ~Event() override = default;

    public:
        virtual void Trigger(_args... a) { }

    private:
        SR_NODISCARD const std::string& GetEventName() const override { return m_name; }

    private:
        std::string m_name;

    };
}

#endif //SR_ENGINE_EVENT_H
```


