

# File Event.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Events**](dir_e74a527d3186554a7cccdddc0bf2b7af.md) **>** [**Event.h**](Event_8h.md)

[Go to the documentation of this file](Event_8h.md)


```C++
//
// Created by Monika on 17.02.2022.
//

#ifndef SR_ENGINE_EVENT_H
#define SR_ENGINE_EVENT_H

#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API IEvent {
    protected:
        IEvent();
        virtual ~IEvent();

    public:
        SR_NODISCARD virtual const std::string& GetEventName() const = 0;

    };

    template <typename ..._args> class SR_COMMON_DLL_API Event : public IEvent {
        using CallBack = std::function<void(_args...)>;
    public:
        explicit Event(std::string name)
            : m_name(std::move(name))
        { }

        ~Event() override = default;

    public:
        virtual void Trigger(_args... a) { }

    private:
        SR_NODISCARD const std::string& GetEventName() const override;

    private:
        std::string m_name;

    };

#ifdef SR_COMMON_DLL_EXPORTS
    template<typename... _args> const std::string &Event<_args...>::GetEventName() const {
        return m_name;
    }
#endif
}

#endif //SR_ENGINE_EVENT_H
```


