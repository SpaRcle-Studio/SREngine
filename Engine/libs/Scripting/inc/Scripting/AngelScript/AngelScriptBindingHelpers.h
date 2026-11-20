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
    bool ContainsScriptType(const SR_UTILS_NS::Reflection::TypeInfo& info);
    asQWORD MathScalarFlags(const SR_UTILS_NS::Reflection::TypeInfo& info);
    SR_UTILS_NS::String PrimitiveName(const SR_UTILS_NS::Reflection::TypeInfo& info);
    SR_UTILS_NS::String StorageIdentifier(const SR_UTILS_NS::Reflection::TypeInfo& info);
    bool HasBorrowedView(const SR_UTILS_NS::Reflection::TypeInfo& info);
    SR_UTILS_NS::String Identifier(const SR_UTILS_NS::Reflection::TypeInfo& info);
    /// Встроенный скалярный тип для примитивного typeId AngelScript, nullptr для остальных
    const SR_UTILS_NS::Reflection::TypeInfo* GetPrimitiveTypeInfo(int32_t typeId);
    void AddRef(asIScriptGeneric* pCall);
    void Release(asIScriptGeneric* pCall);
    SR_UTILS_NS::Reflection::Value ShareObject(SR_UTILS_NS::SRClass* pObject);
    void Construct(asIScriptGeneric* pCall);
    void ConstructValue(asIScriptGeneric* pCall);
    void CopyConstructValue(asIScriptGeneric* pCall);
    void DestructValue(asIScriptGeneric* pCall);
    void AssignValue(asIScriptGeneric* pCall);
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
