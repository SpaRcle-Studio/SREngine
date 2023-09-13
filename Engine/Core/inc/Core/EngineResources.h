//
// Created by Monika on 09.03.2023.
//

#ifndef SRENGINE_ENGINERESOURCES_H
#define SRENGINE_ENGINERESOURCES_H

#include <Utils/Types/SharedPtr.h>

namespace SR_CORE_NS {
    class Engine;
}

namespace SR_CORE_NS::Resources {
    bool RegisterResources(const SR_HTYPES_NS::SharedPtr<Engine>& pEngin);
}

#endif //SRENGINE_ENGINERESOURCES_H
