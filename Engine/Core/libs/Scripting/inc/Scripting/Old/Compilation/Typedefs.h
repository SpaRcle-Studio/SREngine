//
// Created by Nikita on 09.07.2021.
//

#ifndef EVOSCRIPT_TYPEDEFS_H
#define EVOSCRIPT_TYPEDEFS_H

#include <any>
#include <vector>
#include <string>

namespace EvoScript::Typedefs {
    /// сборник разных типов методов на все случаи жизни

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
