//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_SCRIPT_COLLISION_DATA_H
#define SR_ENGINE_SCRIPTING_SCRIPT_COLLISION_DATA_H

#include <Scripting/stdInclude.h>
#include <Utils/Serialization/Serializable.h>
#include <Utils/Math/Vector3.h>

namespace SR_SCRIPTING_NS {
    class SR_SCRIPTING_DLL_API ScriptCollisionData : public SR_UTILS_NS::Serializable {
        SR_CLASS()
    public:
        /// @property
        SR_MATH_NS::FVector3 point;
        /// @property
        SR_MATH_NS::FVector3 impulse;
    };
}

#endif // SR_ENGINE_SCRIPTING_SCRIPT_COLLISION_DATA_H
