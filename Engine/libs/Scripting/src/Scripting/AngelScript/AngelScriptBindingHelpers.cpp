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
            return info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Arithmetic || info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum;
        }

        SR_UTILS_NS::String PrimitiveName(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
                return SR_UTILS_NS::String(info.detailedType);
            }

            if (info.detailedType == "int32") {
                return "int";
            }

            if (info.detailedType == "uint32") {
                return "uint";
            }

            return SR_UTILS_NS::String(info.detailedType);
        }

        SR_UTILS_NS::String StorageIdentifier(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String && info.detailedType != "String") {
                return SR_UTILS_NS::String(info.detailedType);
            }

            if (info.detailedType == "SharedPtr" && info.pNext[0]) {
                return Identifier(*info.pNext[0]) + "@";
            }

            return Identifier(info);
        }

        bool HasBorrowedView(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String && info.detailedType == "StringView") {
                return true;
            }

            return (info.pNext[0] && HasBorrowedView(*info.pNext[0])) || (info.pNext[1] && HasBorrowedView(*info.pNext[1]));
        }

        SR_UTILS_NS::String Identifier(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            SR_TRACY_ZONE;
            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
                return "Value";
            }
            if (Primitive(info)) {
                return PrimitiveName(info);
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String) {
                return "string";
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::MathVector) {
                SR_UTILS_NS::String prefix;
                if (info.detailedType == "float") prefix = "F";
                else if (info.detailedType == "int32") prefix = "I";
                else if (info.detailedType == "uint32") prefix = "U";
                else if (info.detailedType == "bool") prefix = "B";

                prefix += "Vector";
                if (info.detailedSize == 2) return prefix + "2";
                if (info.detailedSize == 3) return prefix + "3";
                if (info.detailedSize == 4) return prefix + "4";
                if (info.detailedSize == 6) return prefix + "6";
                return {};
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::MathRect) {
                if (info.detailedType == "float") return "FRect";
                if (info.detailedType == "int32") return "IRect";
                if (info.detailedType == "uint32") return "URect";
                if (info.detailedType == "uint16") return "USRect";
                return {};
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::MathSize) {
                const SR_UTILS_NS::String suffix = info.detailedSize == 2 ? "Size2" : "Size";
                if (info.detailedSize != 1 && info.detailedSize != 2) return {};
                if (info.detailedType == "float") return "F" + suffix;
                if (info.detailedType == "int32") return "I" + suffix;
                if (info.detailedType == "uint32") return "U" + suffix;
                return {};
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::MathObject) {
                if (info.detailedType == "Color") return "FColor";
                return SR_UTILS_NS::String(info.detailedType);
            }

            if (info.detailedType == "SharedPtr" && info.pNext[0]) {
                return Identifier(*info.pNext[0]);
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Object) {
                return SR_UTILS_NS::String(info.detailedType);
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container && info.pNext[0]) {
                if ((info.detailedType == "Map" || info.detailedType == "FlatHashMap") && info.pNext[0]->pNext[0] && info.pNext[0]->pNext[1]) {
                    return SR_UTILS_NS::String(info.detailedType) + "<" + StorageIdentifier(*info.pNext[0]->pNext[0]) + ", " + StorageIdentifier(*info.pNext[0]->pNext[1]) + ">";
                }

                return SR_UTILS_NS::String(info.detailedType) + "<" + StorageIdentifier(*info.pNext[0]) + ">";
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

            SR_UTILS_NS::Reflection::TypeInfo objectType;
            objectType.category = SR_UTILS_NS::Reflection::ReflectedCategoryType::Object;
            objectType.detailedType = pMeta->GetFactoryName();
            objectType.vtable = pMeta->GetVTable();
            SR_UTILS_NS::Reflection::TypeInfo pointerType;
            pointerType.category = SR_UTILS_NS::Reflection::ReflectedCategoryType::Container;
            pointerType.detailedType = "SharedPtr";
            pointerType.pNext[0] = &objectType;

            if (!SR_UTILS_NS::Reflection::FindVTable(pointerType)) {
                return {};
            }

            auto result = SR_UTILS_NS::Reflection::Value::CreateDefault(&pointerType);
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

            const auto size = SR_UTILS_NS::Reflection::GetReflectedTypeSize(pBinding->pPropertyType->detailedType);
            auto&& pAddress = static_cast<char*>(pObject->value.Data()) + pBinding->component;

            if (pCall->GetArgCount() == 0) {
                memcpy(pCall->GetAddressOfReturnLocation(), pAddress, size);
            }
            else {
                if (pObject->value.IsConst()) {
                    Exception("Cannot change a const mathematical object");

                    return;
                }

                memcpy(pAddress, pCall->GetAddressOfArg(0), size);
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

            auto&& pFrame = pBinding->activeFrames < pBinding->frames.size() ?
                pBinding->frames[pBinding->activeFrames] :
                pBinding->AddFrame();

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
                if (param.isConst && param.pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value &&
                    arguments[i].GetType() == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
                    // Generated const Value& parameters receive the payload, without an extra reflection box.
                    auto payload = pBinding->pBindings->CopyValue(*arguments[i].Cast<SR_UTILS_NS::Reflection::Value>());
                    arguments[i] = std::move(payload);
                }
            }

            std::span<SR_UTILS_NS::Reflection::Value*> params(pointers.data(), pointers.size());

            if (pBinding->method.HasReturn()) {
                auto result = pointers.empty() ? pBinding->method.Invoke(*pOwner) : pBinding->method.Invoke(*pOwner, params);
                if (pBinding->method.GetReturnType()->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
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
                if (pointers.empty()) {
                    pBinding->method.InvokeVoid(*pOwner);
                }
                else {
                    pBinding->method.InvokeVoid(*pOwner, params);
                }
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
                        auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(arguments[i].GetTypeInfo().detailedType);
                        const auto number = static_cast<int32_t>(pReflector->ReadEnumValueFromPointerInternal(arguments[i].Data()));
                        memcpy(pCall->GetArgAddress(i), &number, sizeof(number));
                        continue;
                    }

                    const auto size = arguments[i].GetType() == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum ? sizeof(int32_t) : SR_UTILS_NS::Reflection::GetReflectedTypeSize(arguments[i].GetTypeInfo().detailedType);
                    memcpy(pCall->GetArgAddress(i), arguments[i].Data(), size);
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
                        auto&& pType = pBinding->pBindings->FindType(id);
                        SR_UTILS_NS::String serialized = "Arithmetic.";
                        if (id == asTYPEID_INT32) {
                            serialized += "int32";
                        }
                        else if (id == asTYPEID_UINT32) {
                            serialized += "uint32";
                        }
                        else {
                            serialized += pCall->GetEngine()->GetTypeDeclaration(id);
                        }
                        auto&& pInfo = pType ? SR_UTILS_NS::Reflection::CopyTypeInfo(pType->pTypeInfo) : SR_UTILS_NS::Reflection::LoadTypeInfo(serialized);
                        if (!pInfo || !SR_UTILS_NS::Reflection::FindVTable(*pInfo)) {
                            SR_UTILS_NS::Reflection::FreeTypeInfo(pInfo);
                            Exception("Unsupported native Value type");
                            return;
                        }
                        auto source = pBinding->pBindings->Read(pCall, 0, *pInfo);
                        payload = std::move(source);
                        SR_UTILS_NS::Reflection::FreeTypeInfo(pInfo);
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
                        auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(payload.GetTypeInfo().detailedType);
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
                auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(value.GetTypeInfo().pNext[0]->detailedType);
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
            auto&& table = value.GetTypeInfo().vtable.containerVTable;
            const SR_UTILS_NS::StringView operation(pCall->GetFunction()->GetName());

            if (value.IsConst() && operation != "size" && operation != "contains" && operation != "at") {
                Exception("Cannot modify a const container");
                return;
            }

            const bool map = value.GetTypeInfo().detailedType == "Map" || value.GetTypeInfo().detailedType == "FlatHashMap";
            const bool sequence = value.GetTypeInfo().detailedType == "Vector";

            if (operation == "size") {
                pCall->SetReturnDWord(static_cast<asDWORD>(table.pSize(value.GetStorage())));
                return;
            }

            if (operation == "clear") {
                table.pClear(value.GetStorage());
                return;
            }

            if (operation == "resize") {
                table.pResize(value.GetStorage(), pCall->GetArgDWord(0), false);
                return;
            }

            auto&& pElement = value.GetTypeInfo().pNext[0];
            auto&& pKeyType = map ? pElement->pNext[0] : pElement;
            auto&& pMappedType = map ? pElement->pNext[1] : pElement;
            auto container = SR_UTILS_NS::Reflection::BaseContainerValueRef(&value);
            auto iterator = container.End();
            SR_UTILS_NS::Reflection::Value key;

            if (sequence && operation != "pushBack") {
                const auto index = pCall->GetArgDWord(0);

                if (index >= container.Size()) {
                    Exception("Vector index out of range");
                    return;
                }

                iterator = container.Begin() + index;
            }
            else if (!sequence) {
                key = pBinding->pBindings->Read(pCall, 0, *pKeyType);

                if (!key) {
                    Exception("Invalid container key");
                    return;
                }

                iterator = table.pFind(value.GetStorage(), key.GetStorage());
                iterator.pContainer = &value;
            }

            if (operation == "contains") {
                pCall->SetReturnByte(iterator != container.End());
                return;
            }

            if (operation == "erase") {
                if (iterator != container.End()) {
                    container.Erase(iterator);
                }
                return;
            }

            if (operation == "at") {
                if (iterator == container.End()) {
                    Exception("Map key not found");
                    return;
                }

                auto result = map ? iterator.Second() : *iterator;
                // Return a copy: no script handle may retain an iterator invalidated by resize/erase.
                pBinding->pBindings->Return(pCall, pBinding->pBindings->CopyValue(result));
                return;
            }

            if (operation == "set") {
                auto result = *iterator;
                auto source = pBinding->pBindings->Read(pCall, 1, *pElement);

                if (!source || !pBinding->pBindings->CopyTo(source, result)) {
                    Exception("Invalid vector element");
                }
                return;
            }

            if (sequence) {
                auto source = pBinding->pBindings->Read(pCall, 0, *pElement);
                if (!source) {
                    Exception("Invalid vector element");
                    return;
                }

                value.AsSequenceContainer().PushBack(source);
            }
            else if (map) {
                auto source = pBinding->pBindings->Read(pCall, 1, *pMappedType);
                if (!source) {
                    Exception("Invalid map value");
                    return;
                }

                if (iterator != container.End()) {
                    auto destination = iterator.Second();
                    if (!pBinding->pBindings->CopyTo(source, destination)) {
                        Exception("Map value is not assignable");
                    }
                }
                else {
                    value.AsAssociativeContainer().Insert(key, source);
                }
            }
            else {
                SR_UTILS_NS::Reflection::ReflectedValue unused { };
                table.pInsert(value.GetStorage(), {}, key.GetStorage(), unused);
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
