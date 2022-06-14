//
// Created by Monika on 17.02.2022.
//

#ifndef SRENGINE_INPUTDISPATCHER_H
#define SRENGINE_INPUTDISPATCHER_H

#include <Utils/Events/EventDispatcher.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT InputDispatcher : public EventDispatcher {
    public:
        ~InputDispatcher() override = default;

    public:
        void Check();

    };
}

#endif //SRENGINE_INPUTDISPATCHER_H
