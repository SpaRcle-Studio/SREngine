//
// Created by Codex on 21.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptMapBindings.h>
#include <Scripting/AngelScript/AngelScriptBindingHelpers.h>
#include <Scripting/AngelScript/AngelScriptVectorBindings.h>

#include <Utils/Profile/TracyContext.h>

namespace SR_SCRIPTING_NS::AngelScriptMapBindings {
    void Validate(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = static_cast<asITypeInfo*>(pCall->GetArgAddress(0));
        bool noGC = true;
        for (uint32_t i = 0; i < pType->GetSubTypeCount(); ++i) {
            auto&& pSubtype = pType->GetSubType(i);
            if ((pType->GetSubTypeId(i) & asTYPEID_SCRIPTOBJECT) && !(pType->GetSubTypeId(i) & asTYPEID_OBJHANDLE)) {
                bool hasDefaultFactory = false;
                for (uint32_t factory = 0; factory < pSubtype->GetFactoryCount(); ++factory) {
                    hasDefaultFactory |= pSubtype->GetFactoryByIndex(factory)->GetParamCount() == 0;
                }
                if (!hasDefaultFactory) {
                    pCall->SetReturnByte(false);
                    return;
                }
            }
            noGC &= !pSubtype || !(pSubtype->GetFlags() & (asOBJ_GC | asOBJ_SCRIPT_OBJECT));
        }
        *static_cast<bool*>(pCall->GetArgAddress(1)) = noGC;
        pCall->SetReturnByte(pBindings->ResolveContainerType(pType) != nullptr);
    }

    void ReturnElement(asIScriptGeneric* pCall, const SR_UTILS_NS::Reflection::ValueRef& value) {
        auto&& type = value.GetTypeInfo();
        auto&& pAddress = value.Data();
        if (type.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject ||
            (type.kind == SR_UTILS_NS::Reflection::TypeKind::NativeHandle && !type.detailedSize)) {
            pAddress = *static_cast<void**>(pAddress);
        }
        pCall->SetReturnAddress(pAddress);
    }

    void Operation(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = pBindings->FindType(pCall->GetObjectTypeId());
        if (!pType || !pType->pTypeInfo->CanConstruct()) {
            AngelScriptBindingHelpers::Exception("Unregistered or unresolved associative container type");
            return;
        }
        const auto map = SR_UTILS_NS::Reflection::ValueRef(pType->pTypeInfo, pCall->GetObject(), pCall->GetFunction()->IsReadOnly()).AsMap();
        const SR_UTILS_NS::StringView operation(pCall->GetFunction()->GetName());
        if (operation == "size") {
            pCall->SetReturnDWord(static_cast<asDWORD>(map.Size()));
            return;
        }
        if (operation == "clear") {
            map.Clear();
            return;
        }
        auto key = pBindings->Read(pCall, 0, *map.GetKeyType());
        if (!key) {
            AngelScriptBindingHelpers::Exception("Invalid associative container key");
            return;
        }
        if (operation == "contains") {
            pCall->SetReturnByte(map.Contains(key.AsRef()));
        }
        else if (operation == "erase") {
            pCall->SetReturnByte(map.Erase(key.AsRef()));
        }
        else if (operation == "set" || operation == "insert") {
            if (map.IsSet()) {
                pCall->SetReturnByte(map.InsertOrAssign(key.AsRef(), {}));
                return;
            }
            auto value = pBindings->CopyValue(pBindings->Read(pCall, 1, *map.GetValueType()));
            if (!value) {
                AngelScriptBindingHelpers::Exception("Invalid Map value");
                return;
            }
            map.InsertOrAssign(key.AsRef(), value.AsRef());
        }
        else {
            const auto value = operation == "opIndex" && !map.IsConst() ? map.FindOrAdd(key.AsRef()) : map.Find(key.AsRef());
            if (!value) {
                AngelScriptBindingHelpers::Exception("Map key not found");
                return;
            }
            ReturnElement(pCall, value);
        }
    }

    void EnumReferences(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        auto&& pType = pBindings->FindType(pCall->GetObjectTypeId());
        if (!pType) {
            SRHalt("AngelScriptMapBindings::EnumReferences() : missing associative container type during garbage collection!");
            return;
        }
        const auto map = SR_UTILS_NS::Reflection::ValueRef(pType->pTypeInfo, pCall->GetObject(), true).AsMap();
        map.ForEach([&](const SR_UTILS_NS::Reflection::ValueRef& key, const SR_UTILS_NS::Reflection::ValueRef& value) {
            const SR_UTILS_NS::Reflection::ValueRef elements[] = { key, value };
            for (const auto element : elements) {
                if (!element) {
                    continue;
                }
                auto&& type = element.GetTypeInfo();
                if (type.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject || type.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
                    if (auto&& pObject = *static_cast<void**>(element.Data())) {
                        pCall->GetEngine()->GCEnumCallback(pObject);
                    }
                }
                else if (type.kind == SR_UTILS_NS::Reflection::TypeKind::Vector || type.kind == SR_UTILS_NS::Reflection::TypeKind::Map || type.kind == SR_UTILS_NS::Reflection::TypeKind::Set) {
                    if (auto&& pNested = pBindings->FindType(type)) {
                        pCall->GetEngine()->ForwardGCEnumReferences(element.Data(), pCall->GetEngine()->GetTypeInfoById(pNested->scriptTypeId));
                    }
                }
            }
        });
    }

    void ReleaseReferences(asIScriptGeneric* pCall) {
        auto&& pBindings = static_cast<AngelScriptBindings*>(pCall->GetAuxiliary());
        if (auto&& pType = pBindings->FindType(pCall->GetObjectTypeId())) {
            SR_UTILS_NS::Reflection::ValueRef(pType->pTypeInfo, pCall->GetObject(), false).AsMap().Clear();
        }
    }

    bool RegisterContainer(asIScriptEngine* pEngine, AngelScriptBindings* pBindings, bool set) {
        SR_TRACY_ZONE;
        const char* pInstance = set ? "Set<T>" : "Map<K, V>";
        const SR_UTILS_NS::String instance(pInstance);
        const auto copyConstructor = "void f(int&in, const " + instance + "&in)";
        const auto assignment = instance + "& opAssign(const " + instance + "&in)";
        if (pEngine->RegisterObjectBehaviour(pInstance, asBEHAVE_TEMPLATE_CALLBACK, "bool f(int&in, bool&out)",
                asFUNCTION(Validate), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour(pInstance, asBEHAVE_CONSTRUCT, "void f(int&in)",
                asFUNCTION(AngelScriptVectorBindings::Construct), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour(pInstance, asBEHAVE_CONSTRUCT, copyConstructor.c_str(),
                asFUNCTION(AngelScriptVectorBindings::CopyConstruct), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour(pInstance, asBEHAVE_DESTRUCT, "void f()",
                asFUNCTION(AngelScriptVectorBindings::Destruct), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour(pInstance, asBEHAVE_ENUMREFS, "void f(int&in)",
                asFUNCTION(EnumReferences), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectBehaviour(pInstance, asBEHAVE_RELEASEREFS, "void f(int&in)",
                asFUNCTION(ReleaseReferences), asCALL_GENERIC, pBindings) < 0 ||
            pEngine->RegisterObjectMethod(pInstance, assignment.c_str(),
                asFUNCTION(AngelScriptVectorBindings::Assign), asCALL_GENERIC, pBindings) < 0) {
            SR_ERROR("AngelScriptMapBindings::Register() : failed to register {} behaviours!", instance);
            return false;
        }
        const char* pMapDeclarations[] = {
            "uint size() const", "void clear()", "bool contains(const K&in) const", "bool erase(const K&in)",
            "void set(const K&in, const V&in)", "void insert(const K&in, const V&in)",
            "V& at(const K&in)", "const V& at(const K&in) const",
            "V& opIndex(const K&in)", "const V& opIndex(const K&in) const"
        };
        const char* pSetDeclarations[] = {
            "uint size() const", "void clear()", "bool contains(const T&in) const",
            "bool insert(const T&in)", "bool erase(const T&in)"
        };
        const char* const* pDeclarations = set ? pSetDeclarations : pMapDeclarations;
        const auto count = set ? sizeof(pSetDeclarations) / sizeof(*pSetDeclarations) : sizeof(pMapDeclarations) / sizeof(*pMapDeclarations);
        for (SR_UTILS_NS::SizeType i = 0; i < count; ++i) {
            auto&& pDeclaration = pDeclarations[i];
            if (pEngine->RegisterObjectMethod(pInstance, pDeclaration, asFUNCTION(Operation), asCALL_GENERIC, pBindings) < 0) {
                SR_ERROR("AngelScriptMapBindings::Register() : failed to register {}!", pDeclaration);
                return false;
            }
        }
        return true;
    }

    bool Register(asIScriptEngine* pEngine, AngelScriptBindings* pBindings) {
        return RegisterContainer(pEngine, pBindings, false) && RegisterContainer(pEngine, pBindings, true);
    }
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
