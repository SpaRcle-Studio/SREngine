//
// Created by Codex on 13.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptBindingHelpers.h>
#include <Scripting/AngelScript/AngelScriptBindings.h>
#include <Scripting/Base/ScriptSystem.h>

#include <Utils/TypeTraits/Factory.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Reflection/TypeInfoSerialization.h>
#include <Utils/Common/EnumReflector.h>
#include <Utils/Memory/Allocator.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Types/Optional.h>
#include <Utils/ECS/EntityRef.h>
#include <Utils/Resources/ResourceRef.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Localization/Grapheme.h>

namespace SR_SCRIPTING_NS {
    namespace AngelScriptBindingHelpers {
        void Exception(const char* pMessage) {
            if (auto&& pContext = asGetActiveContext()) {
                pContext->SetException(pMessage);
            }
        }

        void RejectTemplate(asIScriptGeneric* pCall) {
            pCall->SetReturnByte(false);
        }

        bool Primitive(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            return info.IsArithmetic() || info.kind == SR_UTILS_NS::Reflection::TypeKind::Enum;
        }

        SR_UTILS_NS::String PrimitiveName(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Int32) {
                return "int";
            }

            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::UInt32) {
                return "uint";
            }

            return SR_UTILS_NS::String(info.name.ToStringView());
        }

        SR_UTILS_NS::String StorageIdentifier(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            if (info.IsString() && info.kind != SR_UTILS_NS::Reflection::TypeKind::String) {
                return SR_UTILS_NS::String(info.name.ToStringView());
            }

            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::SharedPtr && info.pNext[0]) {
                return Identifier(*info.pNext[0]) + "@";
            }

            return Identifier(info);
        }

        bool HasBorrowedView(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::StringView) {
                return true;
            }

            return (info.pNext[0] && HasBorrowedView(*info.pNext[0])) || (info.pNext[1] && HasBorrowedView(*info.pNext[1]));
        }

        SR_UTILS_NS::String Identifier(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            SR_TRACY_ZONE;
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Value) {
                return "Value";
            }
            if (Primitive(info)) {
                return PrimitiveName(info);
            }

            if (info.IsString()) {
                return "String";
            }

            /// канонические имена математических типов совпадают с именами в скриптах: FVector3, IRect, FSize2, FColor
            if (info.IsMath() || info.kind == SR_UTILS_NS::Reflection::TypeKind::Object) {
                return SR_UTILS_NS::String(info.name.ToStringView());
            }

            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::SharedPtr && info.pNext[0]) {
                return Identifier(*info.pNext[0]);
            }

            if (info.IsContainer() && info.GetArgument(0)) {
                const SR_UTILS_NS::String templateName(SR_UTILS_NS::Reflection::GetTypeKindTemplateName(info.kind).ToStringView());

                if (info.IsMapLike() && info.GetArgument(1)) {
                    return templateName + "<" + StorageIdentifier(*info.GetArgument(0)) + ", " + StorageIdentifier(*info.GetArgument(1)) + ">";
                }

                return templateName + "<" + StorageIdentifier(*info.GetArgument(0)) + ">";
            }

            SR_UTILS_NS::String result;
            SR_UTILS_NS::Reflection::SaveTypeInfo(result, &info);

            for (auto&& ch : result) {
                if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))) {
                    ch = '_';
                }
            }

            return result;
        }

        const SR_UTILS_NS::Reflection::TypeInfo* GetPrimitiveTypeInfo(const int32_t typeId) {
            switch (typeId) {
                case asTYPEID_BOOL: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::Bool);
                case asTYPEID_INT8: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::Int8);
                case asTYPEID_INT16: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::Int16);
                case asTYPEID_INT32: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::Int32);
                case asTYPEID_INT64: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::Int64);
                case asTYPEID_UINT8: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::UInt8);
                case asTYPEID_UINT16: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::UInt16);
                case asTYPEID_UINT32: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::UInt32);
                case asTYPEID_UINT64: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::UInt64);
                case asTYPEID_FLOAT: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::Float);
                case asTYPEID_DOUBLE: return SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::Double);
                default: return nullptr;
            }
        }

        void AddRef(asIScriptGeneric* pCall) {
            static_cast<AngelScriptNativeObject*>(pCall->GetObject())->AddRef();
        }

        void Release(asIScriptGeneric* pCall) {
            static_cast<AngelScriptNativeObject*>(pCall->GetObject())->Release();
        }

        SR_UTILS_NS::Reflection::Value ShareObject(SR_UTILS_NS::SRClass* pObject) {
            auto&& pPointer = dynamic_cast<SR_HTYPES_NS::SharedPtrBase*>(pObject);

            if (!pPointer || !pPointer->Valid()) {
                return {};
            }

            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(pObject->GetMeta()->GetFactoryName());

            if (!pMeta) {
                return {};
            }

            SR_UTILS_NS::Reflection::TypeInfoKey objectKey;
            objectKey.kind = SR_UTILS_NS::Reflection::TypeKind::Object;
            objectKey.name = pMeta->GetFactoryName();

            auto&& pPointerType = SR_UTILS_NS::Reflection::ResolveTemplateTypeInfo(SR_UTILS_NS::Reflection::TypeKind::SharedPtr,
                SR_UTILS_NS::Reflection::ResolveTypeInfo(objectKey));
            if (!pPointerType->IsResolved()) {
                return {};
            }

            auto result = SR_UTILS_NS::Reflection::Value::CreateDefault(pPointerType);
            auto&& pDestination = result.GetSharedPtrBase();

            if (!pDestination) {
                return {};
            }

            pDestination->SetPointerFromBase(pPointer);

            return result;
        }

        void Construct(asIScriptGeneric* pCall) {
            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            SR_UTILS_NS::Reflection::Value value;
            SR_UTILS_NS::SRClass* pAllocation = nullptr;

            if (pBinding->pOwner->pMeta) {
                pAllocation = SR_UTILS_NS::Factory::Instance().CreateBase(pBinding->pOwner->pMeta->GetFactoryName());

                if (pAllocation) {
                    if (dynamic_cast<SR_HTYPES_NS::SharedPtrBase*>(pAllocation)) {
                        value = ShareObject(pAllocation);

                        if (value) {
                            pAllocation = nullptr;
                        }
                    }
                    else {
                        value = pBinding->pOwner->pMeta->Cast(SR_UTILS_NS::Reflection::Value::CreateRef(*pAllocation));
                    }
                }
            }
            else {
                value = SR_UTILS_NS::Reflection::Value::CreateDefault(pBinding->pOwner->pTypeInfo);
            }

            auto&& pObject = pBinding->pBindings->Wrap(std::move(value));

            if (pObject) {
                pObject->pAllocation = pAllocation;
            }
            else {
                if (auto&& pShared = dynamic_cast<SR_HTYPES_NS::SharedPtrBase*>(pAllocation)) {
                    pShared->DecrementPointer();
                }
                else {
                    delete pAllocation;
                }
            }

            pCall->SetReturnAddress(pObject);
        }

        void Assign(asIScriptGeneric* pCall) {
            auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());
            auto&& pOther = static_cast<AngelScriptNativeObject*>(pCall->GetArgObject(0));
            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());

            if (!pObject->IsAlive() || (pOther && !pOther->IsAlive())) {
                Exception("Engine object has been destroyed");
                return;
            }

            if (!pOther || !pBinding->pBindings->CopyTo(pOther->value, pObject->value)) {
                Exception("Native value cannot be assigned");
            }

            pCall->SetReturnAddress(pObject);
        }

        void Cast(asIScriptGeneric* pCall) {
            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());

            if (!pObject->GetObject()) {
                pCall->SetReturnAddress(nullptr);
                return;
            }

            auto value = pBinding->pOwner->pMeta->Cast(pObject->value);
            if (!value) {
                pCall->SetReturnAddress(nullptr);
                return;
            }
            pBinding->pBindings->Return(pCall, std::move(value), pObject);
        }

        void SingletonInstance(asIScriptGeneric* pCall) {
            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            auto&& name = pBinding->pOwner->pMeta->GetFactoryName();
            const auto hash = SR_UTILS_NS::SingletonManager::GetOrAddSingletonHashName(name.c_str());
            auto&& pSingleton = SR_UTILS_NS::GetSingletonManager()->GetSingletonMeta(hash);

            if (!pSingleton) {
                Exception("Singleton instance is unavailable");
                return;
            }

            auto value = pBinding->pOwner->pMeta->Cast(SR_UTILS_NS::Reflection::Value::CreateRef(*pSingleton));
            pBinding->pBindings->Return(pCall, std::move(value));
        }

        void MathComponent(asIScriptGeneric* pCall) {
            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());

            if (!pObject->IsAlive()) {
                Exception("Engine object has been destroyed");
                return;
            }

            auto&& pAddress = static_cast<char*>(pObject->value.Data()) + pBinding->component;
            auto field = SR_UTILS_NS::Reflection::ValueRef(pBinding->pPropertyType, pAddress, pObject->value.IsConst()).ToValue();

            if (pCall->GetArgCount() == 0) {
                pBinding->pBindings->Return(pCall, std::move(field), pObject);
            }
            else {
                if (pObject->value.IsConst()) {
                    Exception("Cannot change a const mathematical object");

                    return;
                }

                if (Primitive(*pBinding->pPropertyType)) {
                    const auto size = pBinding->pPropertyType->kind == SR_UTILS_NS::Reflection::TypeKind::Enum ?
                        field.SizeOf() : pBinding->pPropertyType->GetScalarSize();
                    memcpy(pAddress, pCall->GetAddressOfArg(0), size);
                }
                else {
                    auto&& pSource = static_cast<AngelScriptNativeObject*>(pCall->GetArgObject(0));
                    if (!pSource || !pSource->IsAlive() || !pBinding->pBindings->CopyTo(pSource->value, field)) {
                        Exception("Native field cannot be assigned");
                    }
                }
            }
        }

        void Invoke(asIScriptGeneric* pCall) {
            SR_TRACY_ZONE;

            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());
            auto&& pOwner = pObject->GetObject();

            if (!pOwner) {
                Exception("Engine object has been destroyed");
                return;
            }

            if (pObject->value.IsConst()) {
                Exception("Cannot invoke a mutable method on a const native view");
                return;
            }

            if (pBinding->activeFrames >= pBinding->frames.size()) {
                Exception("Prepared native call frames exhausted");
                return;
            }
            auto&& pFrame = pBinding->frames[pBinding->activeFrames];

            ++pBinding->activeFrames;

            struct FrameScope {
                AngelScriptBindings::Call* pBinding = nullptr;
                AngelScriptBindings::Call::Frame* pFrame = nullptr;

                ~FrameScope() {
                    for (auto&& argument : pFrame->arguments) {
                        if (argument && !Primitive(argument.GetTypeInfo())) {
                            argument = {};
                        }
                    }
                    --pBinding->activeFrames;
                }
            };

            FrameScope scope {
                pBinding, pFrame
            };
            auto&& arguments = pFrame->arguments;
            auto&& pointers = pFrame->pointers;

            for (uint32_t i = 0; i < pBinding->method.GetParamsCount(); ++i) {
                auto&& param = pBinding->method.GetParam(i);
                if (!pBinding->pBindings->ReadInto(pCall, i, *param.pTypeInfo, arguments[i])) {
                    Exception("Incompatible native argument");
                    return;
                }
                if (param.IsOutput() && arguments[i].IsConst()) {
                    Exception("Cannot pass a const native view as an output argument");
                    return;
                }
                if (param.isConst && param.pTypeInfo->kind == SR_UTILS_NS::Reflection::TypeKind::Value &&
                    arguments[i].GetType() == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
                    // Generated const Value& parameters receive the payload, without an extra reflection box.
                    auto payload = pBinding->pBindings->CopyValue(*arguments[i].Cast<SR_UTILS_NS::Reflection::Value>());
                    arguments[i] = std::move(payload);
                }
                pointers[i] = pBinding->method.GetArgumentData(arguments[i], i);
            }

            if (pBinding->method.HasReturn()) {
                if (!pBinding->method.ReturnsReference()) {
                    pFrame->result = pBinding->pResultPool->Acquire();
                    if (!pFrame->result) {
                        Exception("Prepared native result storage exhausted");
                        return;
                    }
                }
                pBinding->method.InvokeInto(*pOwner, pointers.data(), pFrame->result);
                auto result = Primitive(*pBinding->method.GetReturnType()) ? pFrame->result.Copy() : std::move(pFrame->result);
                if (pBinding->method.IsDontPack() && result && result.GetTypeInfo().kind == SR_UTILS_NS::Reflection::TypeKind::Value) {
                    auto payload = result.IsRef() ?
                        *result.Cast<SR_UTILS_NS::Reflection::Value>() : std::move(*result.Cast<SR_UTILS_NS::Reflection::Value>());
                    result = std::move(payload);
                }
                if (pBinding->method.GetReturnType()->kind == SR_UTILS_NS::Reflection::TypeKind::Value) {
                    if (result.GetType() == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
                        result = pBinding->pBindings->CopyValue(result);
                    }
                    else {
                        result = SR_UTILS_NS::Reflection::Value::Create(pBinding->pBindings->CopyValue(result));
                    }
                }
                pBinding->pBindings->Return(pCall, std::move(result), pObject);
            }
            else {
                pBinding->method.InvokeRaw(*pOwner, pointers.data(), nullptr);
            }

            for (uint32_t i = 0; i < arguments.size(); ++i) {
                if (pBinding->method.IsOutputParam(i) && !Primitive(arguments[i].GetTypeInfo())) {
                    auto&& pArgument = static_cast<AngelScriptNativeObject*>(pCall->GetArgObject(i));
                    if (!pArgument || pArgument->value.IsConst() || !pBinding->pBindings->CopyTo(arguments[i], pArgument->value)) {
                        Exception("Cannot write back a native output argument");
                        return;
                    }
                }
                else if (pBinding->method.IsOutputParam(i)) {
                    if (arguments[i].GetType() == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
                        auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(arguments[i].GetTypeInfo().name);
                        const auto number = static_cast<int32_t>(pReflector->ReadEnumValueFromPointerInternal(arguments[i].Data()));
                        memcpy(pCall->GetArgAddress(i), &number, sizeof(number));
                        continue;
                    }

                    memcpy(pCall->GetArgAddress(i), arguments[i].Data(), arguments[i].GetTypeInfo().GetScalarSize());
                }
            }
        }

        void GetProperty(asIScriptGeneric* pCall) {
            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());
            auto&& pOwner = pObject->GetObject();

            if (!pOwner) {
                Exception("Engine object has been destroyed");
                return;
            }

            pBinding->pBindings->Return(pCall, pBinding->property.Get(pOwner), pObject);
        }

        void SetProperty(asIScriptGeneric* pCall) {
            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());
            auto&& pOwner = pObject->GetObject();

            if (!pOwner) {
                Exception("Engine object has been destroyed");
                return;
            }

            if (pObject->value.IsConst()) {
                Exception("Cannot modify a const native view");
                return;
            }

            auto value = pBinding->pBindings->Read(pCall, 0, *pBinding->pPropertyType);

            if (!value) {
                Exception("Incompatible native property");
                return;
            }

            pBinding->property.Set(pOwner, value);
            pBinding->property.OnChanged(pOwner);
        }

        void Wrapper(asIScriptGeneric* pCall) {
            SR_TRACY_ZONE;
            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());
            const SR_UTILS_NS::StringView operation(pCall->GetFunction()->GetName());

            if (!pObject->IsAlive()) {
                Exception("Engine object has been destroyed");
                return;
            }

            auto&& value = pObject->value;
            const bool dynamic = value.GetType() == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value;
            if (value.IsConst() && operation != "get" && operation != "hasValue") {
                Exception("Cannot modify a const native view");
                return;
            }

            if (dynamic) {
                auto&& payload = *value.Cast<SR_UTILS_NS::Reflection::Value>();
                if (operation == "hasValue") {
                    pCall->SetReturnByte(static_cast<bool>(payload));
                    return;
                }
                if (operation == "reset") {
                    payload = {};
                    return;
                }

                const auto id = pCall->GetArgTypeId(0);
                auto&& pAddress = pCall->GetArgAddress(0);
                if (operation == "set") {
                    if (id & asTYPEID_SCRIPTOBJECT) {
                        Exception("Script objects cannot be stored in a native Value");
                        return;
                    }
                    if (id & asTYPEID_MASK_OBJECT) {
                        auto&& pNative = (id & asTYPEID_OBJHANDLE) ? *static_cast<AngelScriptNativeObject**>(pAddress) : static_cast<AngelScriptNativeObject*>(pAddress);
                        if (!pNative || !pNative->IsAlive()) {
                            payload = {};
                            return;
                        }
                        payload = pBinding->pBindings->CopyValue(pNative->value);
                        if (!payload) {
                            Exception("Native value cannot be copied");
                        }
                    }
                    else {
                        const SR_UTILS_NS::Reflection::TypeInfo* pInfo = nullptr;
                        if (auto&& pType = pBinding->pBindings->FindType(id)) {
                            pInfo = pType->pTypeInfo;
                        }
                        else {
                            pInfo = GetPrimitiveTypeInfo(id);
                        }
                        if (!pInfo || !pInfo->IsResolved()) {
                            Exception("Unsupported native Value type");
                            return;
                        }
                        payload = pBinding->pBindings->Read(pCall, 0, *pInfo);
                    }
                    return;
                }

                pCall->SetReturnByte(false);
                if (!payload || (id & asTYPEID_SCRIPTOBJECT)) {
                    return;
                }
                if (id & asTYPEID_MASK_OBJECT) {
                    auto&& pType = pBinding->pBindings->FindType(id);
                    if (!pType) {
                        return;
                    }
                    SR_UTILS_NS::Reflection::Value destination;
                    if (payload.IsSharedPtr() && pType->pMeta) {
                        destination = pType->pMeta->Cast(payload);
                    }
                    else {
                        destination = SR_UTILS_NS::Reflection::Value::CreateDefault(pType->pTypeInfo);
                        if (!pBinding->pBindings->CopyTo(payload, destination)) {
                            return;
                        }
                    }
                    if (!destination) {
                        return;
                    }
                    if (id & asTYPEID_OBJHANDLE) {
                        auto&& pTarget = static_cast<AngelScriptNativeObject**>(pAddress);
                        auto&& pReplacement = pBinding->pBindings->Wrap(std::move(destination));
                        if (*pTarget) {
                            (*pTarget)->Release();
                        }
                        *pTarget = pReplacement;
                    }
                    else if (!pBinding->pBindings->CopyTo(destination, static_cast<AngelScriptNativeObject*>(pAddress)->value)) {
                        return;
                    }
                }
                else {
                    const auto declaration = pBinding->pBindings->Declaration(payload.GetTypeInfo());
                    if (!Primitive(payload.GetTypeInfo()) || pCall->GetEngine()->GetTypeIdByDecl(declaration.c_str()) != id) {
                        return;
                    }
                    if (payload.GetType() == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
                        auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(payload.GetTypeInfo().name);
                        const auto number = static_cast<int32_t>(pReflector->ReadEnumValueFromPointerInternal(payload.Data()));
                        memcpy(pAddress, &number, sizeof(number));
                    }
                    else {
                        memcpy(pAddress, payload.Data(), payload.SizeOf());
                    }
                }
                pCall->SetReturnByte(true);
                return;
            }

            if (auto&& pOptional = value.GetOptionalBase()) {
                if (operation == "hasValue") {
                    pCall->SetReturnByte(pOptional->HasValue());
                }
                else if (operation == "reset") {
                    pOptional->Reset();
                }
                else if (operation == "get") {
                    if (!pOptional->HasValue()) {
                        Exception("Optional has no value");
                        return;
                    }
                    pBinding->pBindings->Return(pCall, pOptional->GetReflectionValue());
                }
                else {
                    auto source = pBinding->pBindings->Read(pCall, 0, *value.GetTypeInfo().pNext[0]);
                    if (!source) {
                        Exception("Invalid Optional value");
                        return;
                    }
                    pOptional->SetValue(source);
                }
                return;
            }

            auto&& pEntity = dynamic_cast<SR_UTILS_NS::EntityRefBase*>(value.GetSRClass());
            auto&& pResource = dynamic_cast<SR_UTILS_NS::ResourceRefBase*>(value.GetSRClass());
            if (operation == "hasValue") {
                pCall->SetReturnByte(pEntity ? pEntity->GetEntity().Valid() : pResource->IsValid());
            }
            else if (operation == "reset") {
                if (pEntity) {
                    pEntity->SetEntityId(SR_ID_INVALID);
                }
                else {
                    pResource->ResetResource();
                }
            }
            else if (operation == "setId") {
                if (pEntity) {
                    pEntity->SetEntityId(pCall->GetArgQWord(0));
                }
                else {
                    auto&& pText = static_cast<AngelScriptNativeObject*>(pCall->GetArgObject(0));
                    if (!pText || !pText->IsAlive()) {
                        Exception("Invalid resource identifier");
                        return;
                    }
                    pResource->SetResource(*pText->value.Cast<SR_UTILS_NS::String>());
                }
            }
            else {
                auto target = pEntity ? ShareObject(pEntity->GetEntity().Get()) : ShareObject(const_cast<SR_UTILS_NS::IResource*>(pResource->GetResourceBase().Get()));
                if (!target) {
                    pCall->SetReturnAddress(nullptr);
                    return;
                }
                auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(value.GetTypeInfo().pNext[0]->name);
                pBinding->pBindings->Return(pCall, pMeta->Cast(target));
            }
        }

        void Container(asIScriptGeneric* pCall) {
            SR_TRACY_ZONE;

            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());

            if (!pObject->IsAlive()) {
                Exception("Engine object has been destroyed");
                return;
            }

            auto&& value = pObject->value;
            const SR_UTILS_NS::StringView operation(pCall->GetFunction()->GetName());

            if (value.IsConst() && operation != "size" && operation != "contains" && operation != "at") {
                Exception("Cannot modify a const container");
                return;
            }

            if (const auto array = value.AsArray()) {
                if (operation == "size") {
                    pCall->SetReturnDWord(static_cast<asDWORD>(array.Size()));
                    return;
                }

                if (operation == "clear") {
                    array.Clear();
                    return;
                }

                if (operation == "resize") {
                    array.Resize(pCall->GetArgDWord(0));
                    return;
                }

                auto&& pElement = array.GetElementType();

                if (operation == "pushBack") {
                    auto source = pBinding->pBindings->Read(pCall, 0, *pElement);
                    if (!source) {
                        Exception("Invalid vector element");
                        return;
                    }

                    array.PushBack(source.AsRef());
                    return;
                }

                const auto index = pCall->GetArgDWord(0);

                if (index >= array.Size()) {
                    Exception("Vector index out of range");
                    return;
                }

                if (operation == "at") {
                    // Return a copy: no script handle may retain a reference invalidated by resize/erase.
                    pBinding->pBindings->Return(pCall, pBinding->pBindings->CopyValue(array.At(index).ToValue()));
                    return;
                }

                if (operation == "set") {
                    auto destination = array.At(index).ToValue();
                    auto source = pBinding->pBindings->Read(pCall, 1, *pElement);

                    if (!source || !pBinding->pBindings->CopyTo(source, destination)) {
                        Exception("Invalid vector element");
                    }
                }
                return;
            }

            const auto map = value.AsMap();
            if (!map) {
                Exception("Unsupported container");
                return;
            }

            if (operation == "size") {
                pCall->SetReturnDWord(static_cast<asDWORD>(map.Size()));
                return;
            }

            if (operation == "clear") {
                map.Clear();
                return;
            }

            auto key = pBinding->pBindings->Read(pCall, 0, *map.GetKeyType());

            if (!key) {
                Exception("Invalid container key");
                return;
            }

            if (operation == "contains") {
                pCall->SetReturnByte(map.Contains(key.AsRef()));
                return;
            }

            if (operation == "erase") {
                map.Erase(key.AsRef());
                return;
            }

            if (operation == "at") {
                const auto found = map.Find(key.AsRef());
                if (!found) {
                    Exception("Map key not found");
                    return;
                }

                pBinding->pBindings->Return(pCall, pBinding->pBindings->CopyValue(found.ToValue()));
                return;
            }

            if (map.IsSet()) {
                map.InsertOrAssign(key.AsRef(), SR_UTILS_NS::Reflection::ValueRef());
                return;
            }

            auto source = pBinding->pBindings->Read(pCall, 1, *map.GetValueType());
            if (!source) {
                Exception("Invalid map value");
                return;
            }

            const bool isNewKey = !map.Contains(key.AsRef());
            auto destination = map.FindOrAdd(key.AsRef()).ToValue();
            if (!pBinding->pBindings->CopyTo(source, destination)) {
                if (isNewKey) {
                    map.Erase(key.AsRef());
                }
                Exception("Map value is not assignable");
            }
        }

        void StringOperation(asIScriptGeneric* pCall) {
            auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());
            if (!pObject->IsAlive()) {
                Exception("Engine object has been destroyed");
                return;
            }

            auto&& pBinding = static_cast<AngelScriptBindings::Call*>(pCall->GetAuxiliary());
            auto&& pText = pObject->value.Cast<SR_UTILS_NS::String>();
            const SR_UTILS_NS::StringView operation(pCall->GetFunction()->GetName());

            if (operation == "length") {
                pCall->SetReturnDWord(static_cast<asDWORD>(pText->size()));
                return;
            }

            if (operation == "byteAt") {
                const auto index = pCall->GetArgDWord(0);
                if (index >= pText->size()) {
                    Exception("String byte index out of bounds");
                    return;
                }
                pCall->SetReturnDWord(static_cast<uint8_t>((*pText)[index]));
                return;
            }

            if (operation == "substring") {
                const auto begin = pCall->GetArgDWord(0);
                const auto count = pCall->GetArgDWord(1);
                if (begin > pText->size() || count > pText->size() - begin) {
                    Exception("String byte range out of bounds");
                    return;
                }
                pBinding->pBindings->Return(pCall, SR_UTILS_NS::Reflection::Value::Create(SR_UTILS_NS::String(pText->substr(begin, count))));
                return;
            }

            if (operation == "graphemeCount") {
                SR_UTILS_NS::Vector<SR_UTILS_NS::Localization::GraphemeCodepoint> codepoints;
                uint32_t count = 0;
                if (!SR_UTILS_NS::Localization::DecodeGraphemes(*pText, codepoints, count)) {
                    Exception("Invalid UTF-8 string");
                    return;
                }
                pCall->SetReturnDWord(count);
                return;
            }

            auto&& pOther = static_cast<AngelScriptNativeObject*>(pCall->GetArgObject(0));

            if (!pOther || !pOther->IsAlive()) {
                Exception("Null or invalid string");
                return;
            }

            auto&& pRhs = pOther->value.Cast<SR_UTILS_NS::String>();

            if (operation == "opEquals") {
                pCall->SetReturnByte(*pText == *pRhs);
            }
            else {
                pBinding->pBindings->Return(pCall, SR_UTILS_NS::Reflection::Value::Create(SR_UTILS_NS::String(*pText + *pRhs)));
            }
        }
    }
}

#endif
