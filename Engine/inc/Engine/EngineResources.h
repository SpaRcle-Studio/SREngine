//
// Created by Monika on 09.03.2023.
//

#ifndef SR_ENGINE_ENGINERESOURCES_H
#define SR_ENGINE_ENGINERESOURCES_H

#include <Utils/Types/SharedPtr.h>

namespace SR_CORE_NS {
    class Engine;
}

namespace SR_CORE_NS::Resources {
    bool RegisterResources(const SR_HTYPES_NS::SharedPtr<Engine>& pEngin);
}

#endif //SR_ENGINE_ENGINERESOURCES_H
