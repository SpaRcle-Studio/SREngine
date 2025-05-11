

# File Typedefs.h

[**File List**](files.md) **>** [**Compilation**](dir_f4efc9bee95c06127bdf4e6c5eda8bf7.md) **>** [**Typedefs.h**](Typedefs_8h.md)

[Go to the documentation of this file](Typedefs_8h.md)


```C++
//
// Created by Nikita on 09.07.2021.
//

#ifndef EVOSCRIPT_TYPEDEFS_H
#define EVOSCRIPT_TYPEDEFS_H

#include <any>
#include <vector>
#include <string>

namespace EvoScript::Typedefs {

    typedef void(*InitFnPtr)(void**);

    typedef void*(*InitBehaviourFnPtr)();
    typedef void(*ReleaseBehaviourFnPtr)();
    typedef void(*SetPropertyFnPtr)(const std::string& id, const std::any& val);
    typedef void(*SwitchContextFnPtr)(void* pContext);
    typedef std::any(*GetPropertyFnPtr)(const std::string& id);
    typedef std::vector<std::string>(*GetPropertiesFnPtr)();

    typedef void*(*AllocateMemoryFnPtr)(size_t sz);
    typedef void(*FreeMemoryFnPtr)(void* ptr);

    typedef void(*SetAllocateMemoryFnPtr)(AllocateMemoryFnPtr);
    typedef void(*SetFreeMemoryFnPtr)(FreeMemoryFnPtr);

    typedef void(*VoidFnPtr)();
    typedef void(*AwakeFnPtr)();
    typedef void(*OnEnableFnPtr)();
    typedef void(*OnDisableFnPtr)();
    typedef void(*StartFnPtr)();
    typedef void(*CloseFnPtr)();
    typedef void(*UpdateFnPtr)(float dt);
    typedef void(*FixedUpdateFnPtr)();
    typedef void(*OnGUIFnPtr)();
}

#endif //EVOSCRIPT_TYPEDEFS_H
```


