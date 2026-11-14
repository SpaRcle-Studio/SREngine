//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGELSCRIPTBINDINGHELPERS_H
#define SR_ENGINE_SCRIPTING_ANGELSCRIPTBINDINGHELPERS_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptBindings.h>

namespace SR_SCRIPTING_NS::AngelScriptBindingHelpers {
    void Exception(const char* pMessage);
    void RejectTemplate(asIScriptGeneric* pCall);
    bool Primitive(const SR_UTILS_NS::Reflection::TypeInfo& info);
    SR_UTILS_NS::String PrimitiveName(const SR_UTILS_NS::Reflection::TypeInfo& info);
    SR_UTILS_NS::String StorageIdentifier(const SR_UTILS_NS::Reflection::TypeInfo& info);
    bool HasBorrowedView(const SR_UTILS_NS::Reflection::TypeInfo& info);
    SR_UTILS_NS::String Identifier(const SR_UTILS_NS::Reflection::TypeInfo& info);
    void AddRef(asIScriptGeneric* pCall);
    void Release(asIScriptGeneric* pCall);
    SR_UTILS_NS::Reflection::Value ShareObject(SR_UTILS_NS::SRClass* pObject);
    void Construct(asIScriptGeneric* pCall);
    void Assign(asIScriptGeneric* pCall);
    void Cast(asIScriptGeneric* pCall);
    void MathComponent(asIScriptGeneric* pCall);
    void Invoke(asIScriptGeneric* pCall);
    void GetProperty(asIScriptGeneric* pCall);
    void SetProperty(asIScriptGeneric* pCall);
    void Container(asIScriptGeneric* pCall);
    void Wrapper(asIScriptGeneric* pCall);
    void StringOperation(asIScriptGeneric* pCall);
    void SingletonInstance(asIScriptGeneric* pCall);
}

#endif

#endif
