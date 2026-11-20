//
// Created by Codex on 19.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptVectorBindings.h>
#include <Scripting/AngelScript/AngelScriptBindingHelpers.h>
#include <Scripting/AngelScript/AngelScriptTypeReflection.h>

#include <Utils/Common/EnumReflector.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_SCRIPTING_NS::AngelScriptVectorBindings {
    void Validate(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = static_cast<asITypeInfo*>(pCall->GetArgAddress(0));
        auto&& pElement = pType->GetSubType();
        if ((pType->GetSubTypeId() & asTYPEID_SCRIPTOBJECT) && !(pType->GetSubTypeId() & asTYPEID_OBJHANDLE)) {
            bool hasDefaultFactory = false;
            for (uint32_t i = 0; i < pElement->GetFactoryCount(); ++i) {
                hasDefaultFactory |= pElement->GetFactoryByIndex(i)->GetParamCount() == 0;
            }
            if (!hasDefaultFactory) {
                pCall->SetReturnByte(false);
                return;
            }
        }
        *static_cast<bool*>(pCall->GetArgAddress(1)) = !pElement || !(pElement->GetFlags() & (asOBJ_GC | asOBJ_SCRIPT_OBJECT));
        pCall->SetReturnByte(pBindings->ResolveVectorType(pType) != nullptr);
    }

    void Construct(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = pBindings->ResolveVectorType(static_cast<asITypeInfo*>(pCall->GetArgAddress(0)));
        if (!pType) {
            AngelScriptBindingHelpers::Exception("Unsupported Vector element type");
            return;
        }
        pType->pTypeInfo->ConstructAt(pCall->GetObject());
    }

    void CopyConstruct(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = pBindings->ResolveVectorType(static_cast<asITypeInfo*>(pCall->GetArgAddress(0)));
        if (!pType) {
            AngelScriptBindingHelpers::Exception("Unsupported Vector element type");
            return;
        }
        pType->pTypeInfo->CopyConstructAt(pCall->GetObject(), pCall->GetArgObject(1));
    }

    void Destruct(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = pBindings->FindType(pCall->GetObjectTypeId());
        pBindings->ClearVectorElements(pCall->GetObject());
        if (pType) {
            pType->pTypeInfo->DestructAt(pCall->GetObject());
        }
    }

    void Assign(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = pBindings->FindType(pCall->GetObjectTypeId());
        if (!pType || !pCall->GetArgObject(0)) {
            AngelScriptBindingHelpers::Exception("Vector cannot be assigned");
            return;
        }
        pBindings->ClearVectorElements(pCall->GetObject());
        pType->pTypeInfo->CopyAssign(pCall->GetObject(), pCall->GetArgObject(0));
        pCall->SetReturnAddress(pCall->GetObject());
    }

    void Operation(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = pBindings->FindType(pCall->GetObjectTypeId());
        if (!pType) {
            AngelScriptBindingHelpers::Exception("Unregistered Vector type");
            return;
        }
        const auto array = SR_UTILS_NS::Reflection::ValueRef(pType->pTypeInfo, pCall->GetObject(), pCall->GetFunction()->IsReadOnly()).AsArray();
        if (!array || !pType->pTypeInfo->CanConstruct()) {
            AngelScriptBindingHelpers::Exception("Vector element type is unresolved");
            return;
        }
        const SR_UTILS_NS::StringView operation(pCall->GetFunction()->GetName());
        if (operation == "size") {
            pCall->SetReturnDWord(static_cast<asDWORD>(array.Size()));
            return;
        }
        auto&& pElement = array.GetElementType();
        if (operation == "at" || operation == "opIndex") {
            const auto index = pCall->GetArgDWord(0);
            if (index >= array.Size()) {
                AngelScriptBindingHelpers::Exception("Vector index out of range");
                return;
            }
            if (pElement->IsArithmetic()) {
                pCall->SetReturnAddress(array.At(index).Data());
                return;
            }
            if (pElement->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject || pElement->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
                auto&& pSlot = array.At(index).Data();
                pCall->SetReturnAddress(pElement->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle ? pSlot : *static_cast<void**>(pSlot));
                return;
            }
            if (auto&& pType = pBindings->FindType(*pElement); pType && pType->IsValue()) {
                pCall->SetReturnAddress(array.At(index).Data());
                return;
            }
            // Reference-returning template methods need a stable script representation.
            // Keep independent copies so script handles survive subsequent vector mutations.
            auto&& elements = pBindings->VectorElements(pCall->GetObject());
            if (elements.size() != array.Size()) {
                for (auto&& pElementObject : elements) {
                    if (pElementObject) {
                        pElementObject->Release();
                    }
                }
                elements.clear();
                elements.resize(array.Size());
            }
            auto&& pCached = elements[index];
            if (pElement->kind == SR_UTILS_NS::Reflection::TypeKind::Enum) {
                auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(pElement->name);
                if (!pReflector) {
                    AngelScriptBindingHelpers::Exception("Unregistered engine enum");
                    return;
                }
                const auto number = static_cast<int32_t>(pReflector->ReadEnumValueFromPointerInternal(array.At(index).Data()));
                if (!pCached) {
                    pCached = pBindings->Wrap(SR_UTILS_NS::Reflection::Value::Create(int32_t()));
                }
                *pCached->value.Cast<int32_t>() = number;
                pCall->SetReturnAddress(pCached->value.Data());
                return;
            }
            auto value = pBindings->CopyValue(array.At(index).ToValue());
            const bool handle = (pCall->GetReturnTypeId() & asTYPEID_OBJHANDLE) != 0;
            if (pCached && !handle && pBindings->CopyTo(value, pCached->value)) {
                pCall->SetReturnAddress(pCached);
                return;
            }
            auto&& pReplacement = pBindings->Wrap(std::move(value));
            if (pCached) {
                pCached->Release();
            }
            pCached = pReplacement;
            if (!pCached && !handle) {
                AngelScriptBindingHelpers::Exception("Invalid Vector element");
                return;
            }
            pCall->SetReturnAddress(handle ? static_cast<void*>(&pCached) : static_cast<void*>(pCached));
            return;
        }
        if (array.IsConst()) {
            AngelScriptBindingHelpers::Exception("Cannot modify a const vector");
            return;
        }
        if (operation == "clear" || operation == "resize" || operation == "reserve") {
            pBindings->ClearVectorElements(pCall->GetObject());
            if (operation == "clear") {
                array.Clear();
            }
            else if (operation == "resize") {
                array.Resize(pCall->GetArgDWord(0));
            }
            else {
                array.Reserve(pCall->GetArgDWord(0));
            }
            return;
        }
        const auto index = operation == "pushBack" ? array.Size() : pCall->GetArgDWord(0);
        if (operation != "pushBack" && index >= array.Size()) {
            AngelScriptBindingHelpers::Exception("Vector index out of range");
            return;
        }
        if (operation == "erase") {
            pBindings->ClearVectorElements(pCall->GetObject());
            array.Erase(index);
            return;
        }
        auto source = pBindings->CopyValue(pBindings->Read(pCall, operation == "pushBack" ? 0 : 1, *pElement));
        if (!source) {
            AngelScriptBindingHelpers::Exception("Invalid Vector element");
            return;
        }
        pBindings->ClearVectorElements(pCall->GetObject());
        if (operation == "pushBack") {
            if (!array.PushBack(source.AsRef())) {
                AngelScriptBindingHelpers::Exception("Vector element cannot be inserted");
            }
        }
        else if (operation == "set" && !array.At(index).Assign(source.AsRef())) {
            AngelScriptBindingHelpers::Exception("Vector element cannot be assigned");
        }
    }

    void ForgetType(asITypeInfo* pScriptType) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pScriptType->GetUserData(AngelScriptBindings::NativeTypeUserData));
        if (!pBindings) {
            return;
        }
        if (auto&& pType = pBindings->FindType(pScriptType->GetTypeId()); pType && pType->isGeneratedVector) {
            pBindings->ForgetType(pScriptType->GetTypeId());
        }
    }

    void EnumReferences(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = pBindings->FindType(pCall->GetObjectTypeId());
        if (!pType) {
            return;
        }
        const auto array = SR_UTILS_NS::Reflection::ValueRef(pType->pTypeInfo, pCall->GetObject(), true).AsArray();
        auto&& pElement = array.GetElementType();
        for (SR_UTILS_NS::SizeType i = 0; i < array.Size(); ++i) {
            if (pElement->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle || pElement->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject) {
                if (auto&& pObject = *static_cast<void**>(array.At(i).Data())) {
                    pCall->GetEngine()->GCEnumCallback(pObject);
                }
            }
            else if (pElement->kind == SR_UTILS_NS::Reflection::TypeKind::Vector) {
                if (auto&& pNested = pBindings->FindType(*pElement)) {
                    pCall->GetEngine()->ForwardGCEnumReferences(array.At(i).Data(), pCall->GetEngine()->GetTypeInfoById(pNested->scriptTypeId));
                }
            }
        }
    }

    void ReleaseReferences(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        if (auto&& pType = pBindings->FindType(pCall->GetObjectTypeId())) {
            pBindings->ClearVectorElements(pCall->GetObject());
            SR_UTILS_NS::Reflection::ValueRef(pType->pTypeInfo, pCall->GetObject(), false).AsArray().Clear();
        }
    }

    bool Register(asIScriptEngine* pEngine, AngelScriptBindings* pBindings) {
        SR_TRACY_ZONE;
        pEngine->SetTypeInfoUserDataCleanupCallback(&ForgetType, AngelScriptBindings::NativeTypeUserData);
        pEngine->SetTypeInfoUserDataCleanupCallback(&AngelScriptTypeReflection::Forget, AngelScriptTypeReflection::ScriptTypeUserData);
        if (pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_TEMPLATE_CALLBACK, "bool f(int&in, bool&out)",
                asFUNCTION(Validate), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_CONSTRUCT, "void f(int&in)",
                asFUNCTION(Construct), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_CONSTRUCT, "void f(int&in, const Vector<T>&in)",
                asFUNCTION(CopyConstruct), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_DESTRUCT, "void f()",
                asFUNCTION(Destruct), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_ENUMREFS, "void f(int&in)",
                asFUNCTION(EnumReferences), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_RELEASEREFS, "void f(int&in)",
                asFUNCTION(ReleaseReferences), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectMethod("Vector<T>", "Vector<T>& opAssign(const Vector<T>&in)",
                asFUNCTION(Assign), asCALL_GENERIC, pBindings) < 0) {
            SR_ERROR("AngelScriptVectorBindings::Register() : failed to register Vector behaviours!");
            return false;
        }
        const char* pDeclarations[] = {
            "uint size() const", "void clear()", "void resize(uint)", "void reserve(uint)", "void erase(uint)",
            "const T& at(uint) const", "const T& opIndex(uint) const", "T& at(uint)", "T& opIndex(uint)",
            "void set(uint, const T&in)", "void pushBack(const T&in)"
        };
        for (auto&& pDeclaration : pDeclarations) {
            if (pEngine->RegisterObjectMethod("Vector<T>", pDeclaration, asFUNCTION(Operation), asCALL_GENERIC, pBindings) < 0) {
                SR_ERROR("AngelScriptVectorBindings::Register() : failed to register {}!", pDeclaration);
                return false;
            }
        }
        return true;
    }
}

#endif //SR_ENGINE_ANGELSCRIPT_SUPPORT
