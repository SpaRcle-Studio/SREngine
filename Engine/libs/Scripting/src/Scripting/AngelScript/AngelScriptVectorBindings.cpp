//
// Created by Codex on 19.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptVectorBindings.h>
#include <Scripting/AngelScript/AngelScriptBindingHelpers.h>

#include <Utils/Common/EnumReflector.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_SCRIPTING_NS::AngelScriptVectorBindings {
    void Validate(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = static_cast<asITypeInfo*>(pCall->GetArgAddress(0));
        *static_cast<bool*>(pCall->GetArgAddress(1)) = true;
        pCall->SetReturnByte(pBindings->ResolveVectorType(pType) != nullptr);
    }

    void Construct(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = pBindings->ResolveVectorType(static_cast<asITypeInfo*>(pCall->GetArgAddress(0)));
        if (!pType) {
            AngelScriptBindingHelpers::Exception("Unsupported Vector element type");
            pCall->SetReturnAddress(nullptr);
            return;
        }
        pCall->SetReturnAddress(pBindings->Wrap(SR_UTILS_NS::Reflection::Value::CreateDefault(pType->pTypeInfo)));
    }

    void Assign(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());
        auto&& pOther = static_cast<AngelScriptNativeObject*>(pCall->GetArgObject(0));
        if (!pObject->IsAlive() || !pOther || !pOther->IsAlive() ||
            !pBindings->CopyTo(pOther->value, pObject->value)) {
            AngelScriptBindingHelpers::Exception("Vector cannot be assigned");
            return;
        }
        pObject->ClearVectorElements();
        pCall->SetReturnAddress(pObject);
    }

    void Operation(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetObject());
        if (!pObject->IsAlive()) {
            AngelScriptBindingHelpers::Exception("Engine object has been destroyed");
            return;
        }
        const auto array = pObject->value.AsArray();
        if (!array || !pObject->value.GetTypeInfo().CanConstruct()) {
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
            // Reference-returning template methods need a stable script representation.
            // Keep independent copies so script handles survive subsequent vector mutations.
            if (pObject->vectorElements.size() != array.Size()) {
                pObject->ClearVectorElements();
                pObject->vectorElements.resize(array.Size());
            }
            auto&& pCached = pObject->vectorElements[index];
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
        if (pObject->value.IsConst()) {
            AngelScriptBindingHelpers::Exception("Cannot modify a const vector");
            return;
        }
        if (operation == "clear" || operation == "resize" || operation == "reserve") {
            pObject->ClearVectorElements();
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
            pObject->ClearVectorElements();
            array.Erase(index);
            return;
        }
        auto source = pBindings->CopyValue(pBindings->Read(pCall, operation == "pushBack" ? 0 : 1, *pElement));
        if (!source) {
            AngelScriptBindingHelpers::Exception("Invalid Vector element");
            return;
        }
        pObject->ClearVectorElements();
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
        for (auto&& pType : pBindings->GetTypes()) {
            if (pType->isGeneratedVector && pType->scriptTypeId == pScriptType->GetTypeId()) {
                pType->scriptTypeId = 0;
            }
        }
    }

    bool Register(asIScriptEngine* pEngine, AngelScriptBindings* pBindings) {
        SR_TRACY_ZONE;
        pEngine->SetTypeInfoUserDataCleanupCallback(&ForgetType, AngelScriptBindings::NativeTypeUserData);
        if (pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_TEMPLATE_CALLBACK, "bool f(int&in, bool&out)",
                asFUNCTION(Validate), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_FACTORY, "Vector<T>@ f(int&in)",
                asFUNCTION(Construct), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_ADDREF, "void f()",
                asFUNCTION(AngelScriptBindingHelpers::AddRef), asCALL_GENERIC) < 0 ||
            pEngine->RegisterObjectBehaviour("Vector<T>", asBEHAVE_RELEASE, "void f()",
                asFUNCTION(AngelScriptBindingHelpers::Release), asCALL_GENERIC) < 0 ||
            pEngine->RegisterObjectMethod("Vector<T>", "Vector<T>& opAssign(const Vector<T>&in)",
                asFUNCTION(Assign), asCALL_GENERIC, pBindings) < 0) {
            SR_ERROR("AngelScriptVectorBindings::Register() : failed to register Vector behaviours!");
            return false;
        }
        const char* pDeclarations[] = {
            "uint size() const", "void clear()", "void resize(uint)", "void reserve(uint)", "void erase(uint)",
            "const T& at(uint) const", "const T& opIndex(uint) const", "void set(uint, const T&in)", "void pushBack(const T&in)"
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
