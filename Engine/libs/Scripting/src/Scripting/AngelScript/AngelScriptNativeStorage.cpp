//
// Created by Codex on 21.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
#include <Scripting/AngelScript/AngelScriptNativeStorage.h>
#include <Scripting/AngelScript/AngelScriptBindingHelpers.h>

namespace SR_SCRIPTING_NS::AngelScriptNativeStorage {
    AngelScriptBindings* Bindings(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        return static_cast<AngelScriptBindings*>(const_cast<void*>(info.pOwnerModule));
    }

    SR_UTILS_NS::Pair<SR_UTILS_NS::SizeType, SR_UTILS_NS::SizeType> PointerSize(const SR_UTILS_NS::Reflection::TypeInfo&) {
        return { sizeof(AngelScriptNativeObject*), alignof(AngelScriptNativeObject*) };
    }

    SR_UTILS_NS::Pair<SR_UTILS_NS::SizeType, SR_UTILS_NS::SizeType> ScriptEnum32Size(const SR_UTILS_NS::Reflection::TypeInfo&) {
        return { sizeof(int32_t), alignof(int32_t) };
    }

    void Construct(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pData) {
        auto&& pSlot = static_cast<AngelScriptNativeObject**>(pData);
        *pSlot = nullptr;
        if (info.detailedSize == 0) {
            *pSlot = Bindings(info)->Wrap(SR_UTILS_NS::Reflection::Value::CreateDefault(info.pNext[0]));
        }
    }

    void Copy(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pData, const void* pSource) {
        auto&& pObject = *static_cast<AngelScriptNativeObject* const*>(pSource);
        if (info.detailedSize == 0 && pObject) {
            *static_cast<AngelScriptNativeObject**>(pData) = pObject->IsAlive() ? Bindings(info)->Wrap(Bindings(info)->CopyValue(pObject->value)) : nullptr;
        }
        else {
            *static_cast<AngelScriptNativeObject**>(pData) = pObject;
            if (pObject) {
                pObject->AddRef();
            }
        }
    }

    void Move(const SR_UTILS_NS::Reflection::TypeInfo&, void* pData, void* pSource) {
        *static_cast<AngelScriptNativeObject**>(pData) = *static_cast<AngelScriptNativeObject**>(pSource);
        *static_cast<AngelScriptNativeObject**>(pSource) = nullptr;
    }

    void Destroy(const SR_UTILS_NS::Reflection::TypeInfo&, void* pData) {
        auto&& pSlot = static_cast<AngelScriptNativeObject**>(pData);
        if (*pSlot) {
            (*pSlot)->Release();
            *pSlot = nullptr;
        }
    }

    void Assign(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pData, const void* pSource) {
        if (pData == pSource) {
            return;
        }
        auto&& pDestination = *static_cast<AngelScriptNativeObject**>(pData);
        auto&& pSourceObject = *static_cast<AngelScriptNativeObject* const*>(pSource);
        if (!info.detailedSize && pDestination && pSourceObject) {
            if (!pDestination->IsAlive() || !pSourceObject->IsAlive() || !Bindings(info)->CopyTo(pSourceObject->value, pDestination->value)) {
                AngelScriptBindingHelpers::Exception("Native vector element cannot be assigned");
            }
            return;
        }
        AngelScriptNativeObject* pReplacement = nullptr;
        Copy(info, &pReplacement, pSource);
        Destroy(info, pData);
        *static_cast<AngelScriptNativeObject**>(pData) = pReplacement;
    }

    void* Controller(SR_UTILS_NS::Reflection::ReflectedValue& value) {
        auto&& pObject = *static_cast<AngelScriptNativeObject**>(value.GetData());
        return pObject ? pObject->GetObject() : nullptr;
    }

    bool IsNull(const SR_UTILS_NS::Reflection::TypeInfo&, const void* pData) {
        return !*static_cast<AngelScriptNativeObject* const*>(pData);
    }

    void Create(const SR_UTILS_NS::Reflection::TypeInfo& info, void* pData) {
        auto payload = SR_UTILS_NS::Reflection::Value::CreateDefault(info.pNext[0]);
        if (payload) {
            auto&& pObject = Bindings(info)->Wrap(std::move(payload));
            Destroy(info, pData);
            *static_cast<AngelScriptNativeObject**>(pData) = pObject;
        }
    }

    uint32_t FieldCount(const SR_UTILS_NS::Reflection::TypeInfo&, const void* pData) {
        auto&& pObject = *static_cast<AngelScriptNativeObject* const*>(pData);
        return pObject && pObject->IsAlive() ? 1 : 0;
    }

    SR_UTILS_NS::StringAtom FieldName(const SR_UTILS_NS::Reflection::TypeInfo&, const void*, uint32_t) {
        return "value";
    }

    SR_UTILS_NS::Reflection::ValueRef Field(const SR_UTILS_NS::Reflection::TypeInfo&, void* pData, uint32_t, bool isConst) {
        auto&& pObject = *static_cast<AngelScriptNativeObject**>(pData);
        return pObject && pObject->IsAlive() ? SR_UTILS_NS::Reflection::ValueRef(&pObject->value.GetTypeInfo(), pObject->value.Data(), isConst || pObject->value.IsConst()) :
            SR_UTILS_NS::Reflection::ValueRef();
    }

    bool IsPackedEnum(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        return info.kind == SR_UTILS_NS::Reflection::TypeKind::Int32 && info.pNext[0] && info.pNext[0]->kind == SR_UTILS_NS::Reflection::TypeKind::Enum;
    }

    const SR_UTILS_NS::Reflection::TypeInfo* NativeType(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::NativeHandle) {
            return info.detailedSize ? SR_UTILS_NS::Reflection::ResolveTemplateTypeInfo(SR_UTILS_NS::Reflection::TypeKind::SharedPtr, info.pNext[0]) : info.pNext[0];
        }
        if (IsPackedEnum(info)) {
            return info.pNext[0];
        }
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Vector) {
            return SR_UTILS_NS::Reflection::ResolveTemplateTypeInfo(info.kind, NativeType(*info.pNext[0]));
        }
        return &info;
    }

    const SR_UTILS_NS::Reflection::TypeInfo* Resolve(AngelScriptBindings* pBindings, const SR_UTILS_NS::Reflection::TypeInfo& info) {
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Vector) {
            return SR_UTILS_NS::Reflection::ResolveTemplateTypeInfo(info.kind, Resolve(pBindings, *info.pNext[0]));
        }
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Enum && info.vtable.lifecycle.size < sizeof(int32_t)) {
            SR_UTILS_NS::Reflection::TypeInfoKey key;
            key.kind = SR_UTILS_NS::Reflection::TypeKind::Int32;
            key.pNext[0] = &info;
            SR_UTILS_NS::Reflection::TypeInfoVTable vtable;
            SR_UTILS_NS::Reflection::FillLifecycle<int32_t>(vtable);
            vtable.pSizeOfAlign = &ScriptEnum32Size;
            return SR_UTILS_NS::Reflection::InternTypeInfo(key, vtable, pBindings);
        }
        if (info.IsArithmetic() || info.IsMath() || info.IsString() || info.kind == SR_UTILS_NS::Reflection::TypeKind::Enum ||
            info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject || info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle ||
            info.kind == SR_UTILS_NS::Reflection::TypeKind::NativeHandle) {
            return &info;
        }
        auto&& pObjectType = info.kind == SR_UTILS_NS::Reflection::TypeKind::SharedPtr ? info.pNext[0] : &info;
        SR_UTILS_NS::Reflection::TypeInfoKey key;
        key.kind = SR_UTILS_NS::Reflection::TypeKind::NativeHandle;
        key.detailedSize = info.kind == SR_UTILS_NS::Reflection::TypeKind::SharedPtr ? 1 : 0;
        key.pNext[0] = pObjectType;
        SR_UTILS_NS::String name;
        SR_UTILS_NS::FormatTo(name, "ASNative_{}_{}{}", pBindings->GetStorageId(), pObjectType->name.view(), key.detailedSize ? "Handle" : "Value");
        key.name = name;
        SR_UTILS_NS::Reflection::TypeInfoVTable vtable;
        vtable.lifecycle.size = sizeof(AngelScriptNativeObject*);
        vtable.displayName = pObjectType->name;
        vtable.lifecycle.alignment = alignof(AngelScriptNativeObject*);
        vtable.lifecycle.isNothrowMoveConstructible = true;
        vtable.lifecycle.pMoveConstructAt = &Move;
        if (key.detailedSize || pObjectType->CanConstruct()) {
            vtable.lifecycle.pConstructAt = &Construct;
        }
        if (key.detailedSize || pObjectType->CanCopy()) {
            vtable.lifecycle.pCopyConstructAt = &Copy;
        }
        if (key.detailedSize || pObjectType->CanAssign()) {
            vtable.lifecycle.pCopyAssign = &Assign;
        }
        vtable.lifecycle.pDestructAt = &Destroy;
        vtable.pSizeOfAlign = &PointerSize;
        vtable.pGetTypeController = &Controller;
        vtable.pFieldCount = &FieldCount;
        vtable.pFieldName = &FieldName;
        vtable.pField = &Field;
        if (key.detailedSize) {
            vtable.pIsNull = &IsNull;
            vtable.pCreate = &Create;
        }
        return SR_UTILS_NS::Reflection::InternTypeInfo(key, vtable, pBindings);
    }
}
#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
