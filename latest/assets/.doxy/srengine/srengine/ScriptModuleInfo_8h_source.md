

# File ScriptModuleInfo.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Cpp**](dir_5b4c9295b84b252e440361db0d67cd77.md) **>** [**ScriptModuleInfo.h**](ScriptModuleInfo_8h.md)

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


