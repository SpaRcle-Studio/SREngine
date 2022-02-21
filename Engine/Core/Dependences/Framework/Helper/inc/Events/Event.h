//
// Created by Monika on 17.02.2022.
//

#ifndef SRENGINE_EVENT_H
#define SRENGINE_EVENT_H

#include <macros.h>

namespace Framework::Helper {
    class IEvent {
    protected:
        IEvent() = default;
        virtual ~IEvent() = default;

    public:
        SR_NODISCARD virtual const std::string& GetEventName() const = 0;

    };

    template <typename ..._args> class Event : public IEvent {
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

#endif //SRENGINE_EVENT_H
