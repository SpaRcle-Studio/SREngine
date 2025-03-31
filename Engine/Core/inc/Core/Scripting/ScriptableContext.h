//
// Created by Monika on 31.03.2025.
//

#ifndef SR_ENGINE_CORE_SCRIPTABLE_CONTEXT_H
#define SR_ENGINE_CORE_SCRIPTABLE_CONTEXT_H

#include <Core/Engine.h>

namespace SR_CORE_NS {
    /// @scriptableClass
    struct ScriptableContext {
        /// @method
        SR_CORE_NS::Engine& GetEngine() {
            return *pEngine;
        }
        SR_CORE_NS::Engine* pEngine = nullptr;
    };
}

#endif //SR_ENGINE_CORE_SCRIPTABLE_CONTEXT_H
