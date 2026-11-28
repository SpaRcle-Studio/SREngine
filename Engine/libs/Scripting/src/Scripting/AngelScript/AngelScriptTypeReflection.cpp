//
// Created by Codex on 20.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
#include <Scripting/AngelScript/AngelScriptTypeReflection.h>
#include <Scripting/AngelScript/AngelScriptBindingHelpers.h>
#include <Scripting/AngelScript/AngelScriptNativeStorage.h>

#include <Utils/Profile/TracyContext.h>

namespace SR_SCRIPTING_NS::AngelScriptTypeReflection {
    asITypeInfo* ScriptType(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        return static_cast<asITypeInfo*>(info.vtable.pRuntimeData);
    }

    uint32_t EnumCount(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        return ScriptType(info)->GetEnumValueCount();
    }

    SR_UTILS_NS::StringAtom EnumValue(const SR_UTILS_NS::Reflection::TypeInfo& info, uint32_t index, int64_t& value) {
        asINT64 number = 0;
        const char* pName = ScriptType(info)->GetEnumValueByIndex(index, &number);
        value = number;
        return pName ? SR_UTILS_NS::StringAtom(pName) : SR_UTILS_NS::StringAtom();
    }

    void Construct(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pDestination) {
        auto&& pType = ScriptType(info);
        *static_cast<void**>(pDestination) = info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle ? nullptr :
            pType->GetEngine()->CreateScriptObject(pType);
    }

    void Copy(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pDestination, const void* pSource) {
        auto&& pType = ScriptType(info);
        auto&& pObject = *static_cast<void* const*>(pSource);
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject) {
            *static_cast<void**>(pDestination) = pObject ? pType->GetEngine()->CreateScriptObjectCopy(pObject, pType) : nullptr;
        }
        else {
            *static_cast<void**>(pDestination) = pObject;
            if (pObject) {
                pType->GetEngine()->AddRefScriptObject(pObject, pType);
            }
        }
    }

    void Move(const SR_UTILS_NS::Reflection::TypeInfo&, void* pDestination, void* pSource) {
        *static_cast<void**>(pDestination) = *static_cast<void**>(pSource);
        *static_cast<void**>(pSource) = nullptr;
    }

    void Destroy(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pData) {
        auto&& pType = ScriptType(info);
        if (auto&& pObject = *static_cast<void**>(pData)) {
            pType->GetEngine()->ReleaseScriptObject(pObject, pType);
            *static_cast<void**>(pData) = nullptr;
        }
    }

    void Assign(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pDestination, const void* pSource) {
        if (pDestination == pSource) {
            return;
        }
        auto&& pType = ScriptType(info);
        auto&& pSourceObject = *static_cast<void* const*>(pSource);
        auto&& pDestinationObject = *static_cast<void**>(pDestination);
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject && pDestinationObject && pSourceObject) {
            if (pType->GetEngine()->AssignScriptObject(pDestinationObject, pSourceObject, pType) < 0) {
                AngelScriptBindingHelpers::Exception("Script object cannot be assigned");
            }
            return;
        }
        void* pReplacement = nullptr;
        Copy(info, &pReplacement, pSource);
        Destroy(info, pDestination);
        pDestinationObject = pReplacement;
    }

    SR_UTILS_NS::Pair<SR_UTILS_NS::SizeType, SR_UTILS_NS::SizeType> Size(const SR_UTILS_NS::Reflection::TypeInfo&) {
        return { sizeof(void*), alignof(void*) };
    }

    SR_UTILS_NS::Pair<SR_UTILS_NS::SizeType, SR_UTILS_NS::SizeType> ScriptEnumSize(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        return { info.pNext[0]->vtable.lifecycle.size, info.pNext[0]->vtable.lifecycle.alignment };
    }

    uint32_t FieldCount(const SR_UTILS_NS::Reflection::TypeInfo&, const void* pData) {
        auto&& pObject = *static_cast<asIScriptObject* const*>(pData);
        return pObject ? pObject->GetPropertyCount() : 0;
    }

    bool IsNull(const SR_UTILS_NS::Reflection::TypeInfo&, const void* pData) {
        return !*static_cast<void* const*>(pData);
    }

    void Create(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pData) {
        auto&& pType = ScriptType(info);
        void* pObject = pType->GetEngine()->CreateScriptObject(pType);
        if (pObject) {
            Destroy(info, pData);
            *static_cast<void**>(pData) = pObject;
        }
    }

    SR_UTILS_NS::StringAtom FieldName(const SR_UTILS_NS::Reflection::TypeInfo&, const void* pData, uint32_t index) {
        auto&& pObject = *static_cast<asIScriptObject* const*>(pData);
        const char* pName = pObject ? pObject->GetPropertyName(index) : nullptr;
        return pName ? SR_UTILS_NS::StringAtom(pName) : SR_UTILS_NS::StringAtom();
    }

    SR_UTILS_NS::Reflection::ValueRef Field(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pData, uint32_t index, bool isConst) {
        auto&& pType = ScriptType(info);
        auto&& pBindings = static_cast<AngelScriptBindings*>(pType->GetUserData(ScriptTypeUserData));
        return Property(pBindings, *static_cast<asIScriptObject**>(pData), index, isConst || info.detailedSize != 0);
    }

    SR_UTILS_NS::Reflection::ValueRef Property(AngelScriptBindings* pBindings, asIScriptObject* pObject, uint32_t index, bool isConst, bool includePrivate) {
        if (!pObject || index >= pObject->GetPropertyCount()) {
            return {};
        }
        bool isPrivate = false, isProtected = false, isReadOnly = false;
        int32_t offset = 0;
        pObject->GetObjectType()->GetProperty(index, nullptr, nullptr, &isPrivate, &isProtected, &offset, nullptr, nullptr, nullptr, nullptr, &isReadOnly);
        if (!includePrivate && (isPrivate || isProtected)) {
            return {};
        }
        isConst |= isReadOnly;
        const auto typeId = pObject->GetPropertyTypeId(index);
        auto&& pAddress = pObject->GetAddressOfProperty(index);
        if (typeId & asTYPEID_SCRIPTOBJECT) {
            auto&& pInfo = Resolve(pBindings, pObject->GetEngine(), typeId);
            return SR_UTILS_NS::Reflection::ValueRef(pInfo, static_cast<char*>(static_cast<void*>(pObject)) + offset, isConst);
        }
        if (auto&& pInfo = AngelScriptBindingHelpers::GetPrimitiveTypeInfo(typeId)) {
            return SR_UTILS_NS::Reflection::ValueRef(pInfo, pAddress, isConst);
        }
        if (!(typeId & asTYPEID_MASK_OBJECT)) {
            auto&& pInfo = Resolve(pBindings, pObject->GetEngine(), typeId);
            return pInfo ? SR_UTILS_NS::Reflection::ValueRef(AngelScriptNativeStorage::Resolve(pBindings, *pInfo), pAddress, isConst) :
                SR_UTILS_NS::Reflection::ValueRef();
        }
        auto&& pNativeType = pBindings->FindType(typeId);
        if (!pNativeType) {
            return {};
        }
        if (pNativeType->IsValue()) {
            return SR_UTILS_NS::Reflection::ValueRef(pNativeType->pTypeInfo, pAddress, isConst);
        }
        auto&& pNative = (typeId & asTYPEID_OBJHANDLE) ? *static_cast<AngelScriptNativeObject**>(pAddress) : static_cast<AngelScriptNativeObject*>(pAddress);
        return pNative && pNative->IsAlive() ? SR_UTILS_NS::Reflection::ValueRef(&pNative->value.GetTypeInfo(), pNative->value.Data(),
            isConst || (typeId & asTYPEID_HANDLETOCONST) != 0 || pNative->value.IsConst()) :
            SR_UTILS_NS::Reflection::ValueRef();
    }

    const SR_UTILS_NS::Reflection::TypeInfo* Resolve(AngelScriptBindings* pBindings, asIScriptEngine* pEngine, int32_t typeId) {
        if (auto&& pPrimitive = AngelScriptBindingHelpers::GetPrimitiveTypeInfo(typeId)) {
            return pPrimitive;
        }
        if (!(typeId & asTYPEID_SCRIPTOBJECT)) {
            auto&& pType = pBindings->FindType(typeId);
            if (pType) {
                return pType->pTypeInfo;
            }
            auto&& pEnum = pEngine->GetTypeInfoById(typeId);
            if (!pEnum || !pEnum->GetModule() || !(pEnum->GetFlags() & asOBJ_ENUM)) {
                return nullptr;
            }
            SR_UTILS_NS::Reflection::TypeInfoKey key;
            key.kind = SR_UTILS_NS::Reflection::TypeKind::ScriptEnum;
            key.pNext[0] = AngelScriptBindingHelpers::GetPrimitiveTypeInfo(pEnum->GetUnderlyingTypeId());
            if (!key.pNext[0]) {
                return nullptr;
            }
            key.name = SR_UTILS_NS::String("AS_") + pEnum->GetModule()->GetName() + "::" + pEngine->GetTypeDeclaration(typeId, true);
            SR_UTILS_NS::Reflection::TypeInfoVTable vtable;
            vtable.lifecycle = key.pNext[0]->vtable.lifecycle;
            vtable.pLess = key.pNext[0]->vtable.pLess;
            vtable.pSizeOfAlign = &ScriptEnumSize;
            vtable.pRuntimeData = pEnum;
            vtable.displayName = pEngine->GetTypeDeclaration(typeId, true);
            vtable.pEnumCount = &EnumCount;
            vtable.pEnumValue = &EnumValue;
            pEnum->SetUserData(pBindings, ScriptTypeUserData);
            auto&& pInfo = SR_UTILS_NS::Reflection::InternTypeInfo(key, vtable, pEnum);
            /// asCEnumType не вызывает очистку user data при удалении, поэтому Forget для enum не срабатывает
            /// и после пересборки модуля в реестре остаётся TypeInfo с указателем на удалённый тип.
            if (pInfo->vtable.pRuntimeData != pEnum) {
                SR_UTILS_NS::Reflection::UnregisterModuleTypes(pInfo->pOwnerModule);
                pInfo = SR_UTILS_NS::Reflection::InternTypeInfo(key, vtable, pEnum);
            }
            return pInfo;
        }
        auto&& pType = pEngine->GetTypeInfoById(typeId);
        if (!pType || !(pType->GetFlags() & asOBJ_SCRIPT_OBJECT)) {
            return nullptr;
        }
        SR_UTILS_NS::Reflection::TypeInfoKey key;
        key.kind = (typeId & asTYPEID_OBJHANDLE) ? SR_UTILS_NS::Reflection::TypeKind::ScriptHandle : SR_UTILS_NS::Reflection::TypeKind::ScriptObject;
        key.detailedSize = (typeId & asTYPEID_HANDLETOCONST) ? 1 : 0;
        const auto name = SR_UTILS_NS::String("AS_") + pType->GetModule()->GetName() + "::" + pEngine->GetTypeDeclaration(typeId, true);
        key.name = name;
        SR_UTILS_NS::Reflection::TypeInfoVTable vtable;
        vtable.lifecycle.size = sizeof(void*);
        vtable.lifecycle.alignment = alignof(void*);
        vtable.lifecycle.isNothrowMoveConstructible = true;
        vtable.lifecycle.pConstructAt = &Construct;
        vtable.lifecycle.pCopyConstructAt = &Copy;
        vtable.lifecycle.pMoveConstructAt = &Move;
        vtable.lifecycle.pCopyAssign = &Assign;
        vtable.lifecycle.pDestructAt = &Destroy;
        vtable.pSizeOfAlign = &Size;
        vtable.pRuntimeData = pType;
        vtable.displayName = pEngine->GetTypeDeclaration(pType->GetTypeId(), true);
        vtable.pFieldCount = &FieldCount;
        vtable.pFieldName = &FieldName;
        vtable.pField = &Field;
        if (key.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
            vtable.pIsNull = &IsNull;
            vtable.pCreate = &Create;
        }
        pType->SetUserData(pBindings, ScriptTypeUserData);
        return SR_UTILS_NS::Reflection::InternTypeInfo(key, vtable, pType);
    }

    void Forget(asITypeInfo* pType) {
        SR_UTILS_NS::Reflection::UnregisterModuleTypes(pType);
    }
}
#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
