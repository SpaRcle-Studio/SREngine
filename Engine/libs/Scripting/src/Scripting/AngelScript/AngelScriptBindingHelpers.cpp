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

namespace SR_SCRIPTING_NS {
    namespace AngelScriptBindingHelpers {
        void Exception(const char* pMessage) {
            if (auto&& pContext = asGetActiveContext()) {
                pContext->SetException(pMessage);
            }
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
                return "SharedPtr_" + StorageIdentifier(*info.pNext[0]);
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
            if (Primitive(info)) {
                return PrimitiveName(info);
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String) {
                return "string";
            }

            if (info.detailedType == "SharedPtr" && info.pNext[0]) {
                return Identifier(*info.pNext[0]);
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Object) {
                return SR_UTILS_NS::String(info.detailedType);
            }

            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container && info.pNext[0]) {
                if ((info.detailedType == "Map" || info.detailedType == "FlatHashMap") && info.pNext[0]->pNext[0] && info.pNext[0]->pNext[1]) {
                    return SR_UTILS_NS::String(info.detailedType) + "_" + StorageIdentifier(*info.pNext[0]->pNext[0]) + "_" + StorageIdentifier(*info.pNext[0]->pNext[1]);
                }

                return SR_UTILS_NS::String(info.detailedType) + "_" + StorageIdentifier(*info.pNext[0]);
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
                delete pAllocation;
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
            }

            std::span<SR_UTILS_NS::Reflection::Value*> params(pointers.data(), pointers.size());

            if (pBinding->method.HasReturn()) {
                auto result = pointers.empty() ? pBinding->method.Invoke(*pOwner) : pBinding->method.Invoke(*pOwner, params);
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
                if (pBinding->method.IsOutputParam(i) && Primitive(arguments[i].GetTypeInfo())) {
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
