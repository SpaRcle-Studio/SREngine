//
// Created by Monika on 09.03.2023.
//

#ifndef SR_ENGINE_ENGINERESOURCES_H
#define SR_ENGINE_ENGINERESOURCES_H

#include <Utils/Types/SharedPtr.h>

namespace SR_CORE_NS {
    class Engine;
}

/**
 * Registers built-in engine resources into the provided Engine instance.
 *
 * @param pEngine Shared pointer to the Engine into which resources will be registered.
 * @returns `true` if resources were registered successfully, `false` otherwise.
 */
namespace SR_CORE_NS::Resources {
    bool RegisterResources(const SR_HTYPES_NS::SharedPtr<Engine>& pEngine);
}

#endif //SR_ENGINE_ENGINERESOURCES_H