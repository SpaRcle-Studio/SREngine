//
// Created by Monika on 21.07.2023.
//

#ifndef SRENGINE_PASSQUEUE_H
#define SRENGINE_PASSQUEUE_H

#include <Utils/Common/NonCopyable.h>

namespace SR_GRAPH_NS {
    class BasePass;

    using PassQueue = std::vector<BasePass*>;
    using PassQueues = std::vector<PassQueue>;
}

#endif //SRENGINE_PASSQUEUE_H
