

# File ScriptModuleInfo.h

[**File List**](files.md) **>** [**Cpp**](dir_b8cef419041e294130040bdf7c4c8d81.md) **>** [**ScriptModuleInfo.h**](ScriptModuleInfo_8h.md)

[Go to the documentation of this file](ScriptModuleInfo_8h.md)


```C++
//
// Created by Monika on 04.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_SCRIPT_MODULE_INFO_H
#define SR_ENGINE_SCRIPTING_CPP_SCRIPT_MODULE_INFO_H

#include <Scripting/macros.h>

#include <Utils/Serialization/Serializable.h>

namespace SR_SCRIPTING_NS {
    SR_ENUM_NS_CLASS_T(ScriptLinkMode, uint8_t,
        Unknown, Dynamic, Static, Mixed
    );

    struct CppScriptModuleInfo : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        
        SR_UTILS_NS::StringAtom moduleName;
        ScriptLinkMode linkMode = ScriptLinkMode::Unknown;
        std::set<SR_UTILS_NS::StringAtom> dependencies;
        bool enabled = true;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_SCRIPT_MODULE_INFO_H
```


