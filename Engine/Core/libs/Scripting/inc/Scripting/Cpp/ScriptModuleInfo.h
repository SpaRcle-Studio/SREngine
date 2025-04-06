//
// Created by Monika on 04.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_SCRIPT_MODULE_INFO_H
#define SR_ENGINE_SCRIPTING_CPP_SCRIPT_MODULE_INFO_H

#include <Utils/Serialization/Serializable.h>

namespace SR_SCRIPTING_NS {
    SR_ENUM_NS_CLASS_T(ScriptLinkMode, uint8_t,
        Unknown, Dynamic, Static, Mixed
    );

    struct CppScriptModuleInfo : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        /// @property
        SR_UTILS_NS::StringAtom moduleName;
        /// @property
        ScriptLinkMode linkMode = ScriptLinkMode::Unknown;
        /// @property
        std::set<SR_UTILS_NS::StringAtom> dependencies;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_SCRIPT_MODULE_INFO_H
