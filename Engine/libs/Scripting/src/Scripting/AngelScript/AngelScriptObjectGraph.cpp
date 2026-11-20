//
// Created by Codex on 20.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
#include <Scripting/AngelScript/AngelScriptObjectGraph.h>
#include <Scripting/AngelScript/AngelScriptTypeReflection.h>

#include <Utils/Profile/TracyContext.h>

namespace SR_SCRIPTING_NS {
    namespace AngelScriptGraphHelpers {
        struct State {
            uint32_t depth = 0;
            SR_HTYPES_NS::FlatHashMap<const void*, uint64_t> saved;
            SR_HTYPES_NS::FlatHashMap<uint64_t, asIScriptObject*> loaded;
        };

        State& Current() {
            static thread_local State state;
            return state;
        }
    }

    AngelScriptObjectGraph::AngelScriptObjectGraph(asIScriptObject* pRoot) {
        auto&& state = AngelScriptGraphHelpers::Current();
        if (state.depth++ == 0) {
            state.saved.clear();
            state.loaded.clear();
            if (pRoot) {
                state.saved[pRoot] = 1;
                state.loaded[1] = pRoot;
            }
        }
    }

    AngelScriptObjectGraph::~AngelScriptObjectGraph() {
        auto&& state = AngelScriptGraphHelpers::Current();
        if (--state.depth == 0) {
            state.saved.clear();
            state.loaded.clear();
        }
    }

    void SaveAngelScriptObject(const SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::ISerializer& serializer) {
        SR_TRACY_ZONE;
        auto&& state = AngelScriptGraphHelpers::Current();
        auto&& pObject = *static_cast<asIScriptObject* const*>(value.Data());
        const auto objectId = SR_UTILS_NS::SerializationId::Create("objectId");
        const auto definitionId = SR_UTILS_NS::SerializationId::Create("definition");
        if (!pObject) {
            serializer.WriteUInt(uint64_t(0), objectId);
            return;
        }
        if (const auto found = state.saved.find(pObject); found != state.saved.end()) {
            serializer.WriteUInt(found->second, objectId);
            serializer.WriteBool(false, definitionId);
            return;
        }
        const auto id = static_cast<uint64_t>(state.saved.size() + 1);
        state.saved[pObject] = id;
        serializer.WriteUInt(id, objectId);
        serializer.WriteBool(true, definitionId);
        serializer.WriteString(pObject->GetEngine()->GetTypeDeclaration(pObject->GetTypeId(), true), SR_UTILS_NS::SerializationId::Create("objectType"));
        auto&& pExpected = static_cast<asITypeInfo*>(value.GetTypeInfo().vtable.pRuntimeData);
        auto&& pBindings = static_cast<AngelScriptBindings*>(pExpected->GetUserData(AngelScriptTypeReflection::ScriptTypeUserData));
        AngelScriptTypeReflection::Resolve(pBindings, pObject->GetEngine(), pObject->GetTypeId());
        serializer.BeginArray(pObject->GetPropertyCount(), SR_UTILS_NS::SerializationId::Create("properties"));
        for (uint32_t i = 0; i < pObject->GetPropertyCount(); ++i) {
            serializer.BeginItem(SR_UTILS_NS::SerializationId::Create("property"));
            serializer.WriteString(pObject->GetPropertyName(i), SR_UTILS_NS::SerializationId::Create("name"));
            serializer.WriteString(pObject->GetEngine()->GetTypeDeclaration(pObject->GetPropertyTypeId(i), true), SR_UTILS_NS::SerializationId::Create("scriptType"));
            auto field = AngelScriptTypeReflection::Property(pBindings, pObject, i, true).ToValue();
            if (field && CanSerializeAngelScriptValue(field.GetTypeInfo())) {
                serializer.BeginObject(SR_UTILS_NS::SerializationId::Create("value"));
                SaveAngelScriptValue(field, serializer);
                serializer.EndObject();
            }
            serializer.EndItem();
        }
        serializer.EndArray();
    }

    bool LoadAngelScriptObject(SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::IDeserializer& deserializer) {
        SR_TRACY_ZONE;
        auto&& state = AngelScriptGraphHelpers::Current();
        auto&& info = value.GetTypeInfo();
        auto&& pExpected = static_cast<asITypeInfo*>(info.vtable.pRuntimeData);
        auto&& pEngine = pExpected->GetEngine();
        auto&& pSlot = static_cast<asIScriptObject**>(value.Data());
        uint64_t id = 0;
        deserializer.ReadUInt(id, SR_UTILS_NS::SerializationId::Create("objectId"));
        if (id == 0) {
            if (info.kind != SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
                return false;
            }
            info.DestructAt(pSlot);
            *pSlot = nullptr;
            return true;
        }
        bool definition = false;
        deserializer.ReadBool(definition, SR_UTILS_NS::SerializationId::Create("definition"));
        asIScriptObject* pObject = nullptr;
        if (definition) {
            SR_UTILS_NS::String declaration;
            deserializer.ReadString(declaration, SR_UTILS_NS::SerializationId::Create("objectType"));
            auto&& pActual = pExpected->GetModule()->GetTypeInfoByDecl(declaration.c_str());
            if (!pActual || (pActual != pExpected && !pActual->DerivesFrom(pExpected) && !pActual->Implements(pExpected))) {
                return false;
            }
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject && *pSlot) {
                pObject = *pSlot;
            }
            else {
                pObject = static_cast<asIScriptObject*>(pEngine->CreateScriptObject(pActual));
                if (!pObject) {
                    return false;
                }
                info.DestructAt(pSlot);
                *pSlot = pObject;
            }
            state.loaded[id] = pObject;
        }
        else {
            const auto found = state.loaded.find(id);
            if (found == state.loaded.end()) {
                return false;
            }
            pObject = found->second;
            auto&& pActual = pObject->GetObjectType();
            if (pActual != pExpected && !pActual->DerivesFrom(pExpected) && !pActual->Implements(pExpected)) {
                return false;
            }
            if (pObject != *pSlot) {
                if (info.kind != SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
                    return false;
                }
                pObject->AddRef();
                info.DestructAt(pSlot);
                *pSlot = pObject;
            }
            return true;
        }
        auto&& pBindings = static_cast<AngelScriptBindings*>(pExpected->GetUserData(AngelScriptTypeReflection::ScriptTypeUserData));
        const auto count = deserializer.BeginArray(SR_UTILS_NS::SerializationId::Create("properties"));
        bool success = true;
        for (uint32_t i = 0; i < count; ++i) {
            if (!deserializer.BeginItem(SR_UTILS_NS::SerializationId::Create("property"), i)) {
                success = false;
                break;
            }
            SR_UTILS_NS::String name, declaration;
            deserializer.ReadString(name, SR_UTILS_NS::SerializationId::Create("name"));
            deserializer.ReadString(declaration, SR_UTILS_NS::SerializationId::Create("scriptType"));
            for (uint32_t fieldIndex = 0; fieldIndex < pObject->GetPropertyCount(); ++fieldIndex) {
                if (name != pObject->GetPropertyName(fieldIndex) || declaration != pEngine->GetTypeDeclaration(pObject->GetPropertyTypeId(fieldIndex), true)) {
                    continue;
                }
                auto field = AngelScriptTypeReflection::Property(pBindings, pObject, fieldIndex, false).ToValue();
                if (field && !field.IsConst() && CanSerializeAngelScriptValue(field.GetTypeInfo()) && deserializer.BeginObject(SR_UTILS_NS::SerializationId::Create("value"))) {
                    success &= LoadAngelScriptValue(field, deserializer);
                    deserializer.EndObject();
                }
                break;
            }
            deserializer.EndItem();
        }
        deserializer.EndArray();
        return success;
    }
}
#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
