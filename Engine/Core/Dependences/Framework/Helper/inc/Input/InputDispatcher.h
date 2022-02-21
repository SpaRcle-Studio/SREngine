//
// Created by Monika on 17.02.2022.
//

#ifndef SRENGINE_INPUTDISPATCHER_H
#define SRENGINE_INPUTDISPATCHER_H

#include <Events/EventDispatcher.h>

namespace Framework::Helper {
    class InputDispatcher : public EventDispatcher {
    public:
        ~InputDispatcher() override = default;

    public:
        void Check();

    };
}

#endif //SRENGINE_INPUTDISPATCHER_H
