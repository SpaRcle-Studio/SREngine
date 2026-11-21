//
// Created by Codex on 20.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
#include <Scripting/AngelScript/AngelScriptObjectGraph.h>
#include <Scripting/AngelScript/AngelScriptTypeReflection.h>
#include <Scripting/AngelScript/AngelScriptBindingHelpers.h>

#include <Utils/Profile/TracyContext.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Types/Optional.h>

namespace SR_SCRIPTING_NS {
    namespace AngelScriptSnapshotHelpers {
        template<typename Visitor> bool VisitChildren(const SR_UTILS_NS::Reflection::ValueRef& value, Visitor&& visitor) {
            auto&& info = value.GetTypeInfo();
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::NativeHandle) {
                auto&& pObject = *value.Cast<AngelScriptNativeObject*>();
                if (!pObject || !pObject->IsAlive()) {
                    return true;
                }
                visitor(pObject->value.AsRef());
                return true;
            }
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject || info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
                auto&& pObject = *value.Cast<asIScriptObject*>();
                auto&& pExpected = static_cast<asITypeInfo*>(info.vtable.pRuntimeData);
                auto&& pBindings = static_cast<AngelScriptBindings*>(pExpected->GetUserData(AngelScriptTypeReflection::ScriptTypeUserData));
                for (uint32_t i = 0; i < pObject->GetPropertyCount(); ++i) {
                    bool isConst = false;
                    pObject->GetObjectType()->GetProperty(i, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &isConst);
                    if (isConst) {
                        continue;
                    }
                    auto field = AngelScriptTypeReflection::Property(pBindings, pObject, i, true, true);
                    if (field && CanSerializeAngelScriptValue(field.GetTypeInfo())) {
                        visitor(field);
                    }
                }
                return true;
            }
            if (auto&& pOptional = value.GetOptionalBase()) {
                if (pOptional->HasValue()) {
                    visitor(pOptional->GetReflectionValue().AsRef());
                }
                return true;
            }
            if (const auto array = value.AsArray()) {
                for (SR_UTILS_NS::SizeType i = 0; i < array.Size(); ++i) {
                    visitor(array.At(i));
                }
                return true;
            }
            if (const auto map = value.AsMap()) {
                map.ForEach([&visitor, &map](const SR_UTILS_NS::Reflection::ValueRef& key, const SR_UTILS_NS::Reflection::ValueRef& mapped) {
                    visitor(key);
                    if (!map.IsSet()) {
                        visitor(mapped);
                    }
                });
                return true;
            }
            if (info.fieldsCount > 0) {
                for (uint32_t i = 0; i < value.FieldCount(); ++i) {
                    visitor(value.Field(i));
                }
                return true;
            }
            return false;
        }

        bool IsScalar(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            return info.IsArithmetic() || info.kind == SR_UTILS_NS::Reflection::TypeKind::Enum || info.IsString();
        }

        bool EqualScalar(const SR_UTILS_NS::Reflection::ValueRef& value, const SR_UTILS_NS::Reflection::Value& initial) {
            auto&& info = value.GetTypeInfo();
            switch (info.kind) {
                case SR_UTILS_NS::Reflection::TypeKind::Float:
                    return SR_EQUALS(*value.Cast<float_t>(), *initial.Cast<float_t>());
                case SR_UTILS_NS::Reflection::TypeKind::Double:
                    return SR_EQUALS(*value.Cast<double_t>(), *initial.Cast<double_t>());
                case SR_UTILS_NS::Reflection::TypeKind::String:
                    return *value.Cast<SR_UTILS_NS::String>() == *initial.Cast<SR_UTILS_NS::String>();
                case SR_UTILS_NS::Reflection::TypeKind::StringAtom:
                    return *value.Cast<SR_UTILS_NS::StringAtom>() == *initial.Cast<SR_UTILS_NS::StringAtom>();
                case SR_UTILS_NS::Reflection::TypeKind::Path:
                    return *value.Cast<SR_UTILS_NS::Path>() == *initial.Cast<SR_UTILS_NS::Path>();
                default:
                    return (info.IsArithmetic() || info.kind == SR_UTILS_NS::Reflection::TypeKind::Enum) &&
                        memcmp(value.Data(), initial.Data(), value.SizeOf()) == 0;
            }
        }
    }

    void AngelScriptValueSnapshot::Capture(const SR_UTILS_NS::Reflection::ValueRef& value,
        SR_HTYPES_NS::FlatHashMap<const void*, uint64_t>& objects)
    {
        pType = &value.GetTypeInfo();
        if (pType->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject || pType->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
            auto&& pObject = *value.Cast<asIScriptObject*>();
            if (!pObject) {
                return;
            }
            pObjectType = pObject->GetObjectType();
            if (const auto found = objects.find(pObject); found != objects.end()) {
                objectId = found->second;
                return;
            }
            objectId = objects.size() + 1;
            objects[pObject] = objectId;
        }
        if (AngelScriptSnapshotHelpers::IsScalar(*pType)) {
            scalar = value.Copy();
            comparable = static_cast<bool>(scalar);
            return;
        }
        comparable = AngelScriptSnapshotHelpers::VisitChildren(value, [this, &objects](const SR_UTILS_NS::Reflection::ValueRef& child) {
            children.emplace_back();
            children.back().Capture(child, objects);
        });
    }

    bool AngelScriptValueSnapshot::Matches(const SR_UTILS_NS::Reflection::ValueRef& value,
        SR_HTYPES_NS::FlatHashMap<const void*, uint64_t>& objects) const
    {
        if (!comparable || !value || pType != &value.GetTypeInfo()) {
            return false;
        }
        if (pType->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject || pType->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
            auto&& pObject = *value.Cast<asIScriptObject*>();
            if (!pObject) {
                return objectId == 0;
            }
            if (pObjectType != pObject->GetObjectType()) {
                return false;
            }
            if (const auto found = objects.find(pObject); found != objects.end()) {
                return objectId == found->second;
            }
            const auto id = objects.size() + 1;
            objects[pObject] = id;
            if (objectId != id) {
                return false;
            }
        }
        if (scalar) {
            return AngelScriptSnapshotHelpers::EqualScalar(value, scalar);
        }
        SR_UTILS_NS::SizeType index = 0;
        bool matches = true;
        const bool supported = AngelScriptSnapshotHelpers::VisitChildren(value, [this, &objects, &index, &matches](const SR_UTILS_NS::Reflection::ValueRef& child) {
            if (index >= children.size() || !children[index].Matches(child, objects)) {
                matches = false;
            }
            ++index;
        });
        return supported && matches && index == children.size();
    }

    namespace AngelScriptGraphHelpers {
        struct State {
            uint32_t depth = 0;
            uint32_t preloading = 0;
            uint64_t nextId = 1;
            SR_HTYPES_NS::FlatHashMap<const void*, uint64_t> saved;
            SR_HTYPES_NS::FlatHashMap<uint64_t, asIScriptObject*> loaded;
            SR_UTILS_NS::Vector<asIScriptObject*> retained;
        };

        State& Current() {
            static thread_local State state;
            return state;
        }

        void Retain(asIScriptObject* pObject) {
            pObject->AddRef();
            Current().retained.emplace_back(pObject);
        }

        struct PreloadScope {
            PreloadScope() {
                ++Current().preloading;
            }
            ~PreloadScope() {
                --Current().preloading;
            }
        };
    }

    AngelScriptObjectGraph::AngelScriptObjectGraph(asIScriptObject* pRoot) {
        auto&& state = AngelScriptGraphHelpers::Current();
        if (state.depth++ == 0) {
            state.saved.clear();
            state.loaded.clear();
            state.nextId = 1;
            if (pRoot) {
                state.saved[pRoot] = 1;
                state.loaded[1] = pRoot;
                state.nextId = 2;
            }
        }
    }

    AngelScriptObjectGraph::~AngelScriptObjectGraph() {
        auto&& state = AngelScriptGraphHelpers::Current();
        if (--state.depth == 0) {
            state.saved.clear();
            state.loaded.clear();
            auto retained = std::move(state.retained);
            for (auto&& pObject : retained) {
                pObject->Release();
            }
        }
    }

    void AngelScriptObjectGraph::RegisterRoot(asIScriptObject* pSaved, asIScriptObject* pLoaded, uint64_t id) {
        auto&& state = AngelScriptGraphHelpers::Current();
        state.nextId = SR_MAX(state.nextId, id + 1);
        if (pSaved) {
            state.saved[pSaved] = id;
        }
        if (pLoaded) {
            state.loaded[id] = pLoaded;
            AngelScriptGraphHelpers::Retain(pLoaded);
        }
        else if (pSaved) {
            state.loaded[id] = nullptr;
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
        const auto id = state.nextId++;
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
            bool isReadOnly = false;
            pObject->GetObjectType()->GetProperty(i, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &isReadOnly);
            auto field = AngelScriptTypeReflection::Property(pBindings, pObject, i, true, true).ToValue();
            if (field && !isReadOnly && CanSerializeAngelScriptValue(field.GetTypeInfo())) {
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
            const auto existing = state.loaded.find(id);
            if (existing != state.loaded.end()) {
                pObject = existing->second;
                if (!pObject || pObject->GetObjectType() != pActual) {
                    return false;
                }
                if (*pSlot != pObject) {
                    pObject->AddRef();
                    info.DestructAt(pSlot);
                    *pSlot = pObject;
                }
            }
            else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject && *pSlot) {
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
            if (existing == state.loaded.end()) {
                state.loaded[id] = pObject;
                AngelScriptGraphHelpers::Retain(pObject);
            }
        }
        else {
            const auto found = state.loaded.find(id);
            if (found == state.loaded.end()) {
                return state.preloading != 0;
            }
            pObject = found->second;
            if (!pObject) {
                if (info.kind != SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
                    return false;
                }
                info.DestructAt(pSlot);
                *pSlot = nullptr;
                return true;
            }
            auto&& pActual = pObject->GetObjectType();
            if (pActual != pExpected && !pActual->DerivesFrom(pExpected) && !pActual->Implements(pExpected)) {
                return false;
            }
            if (pObject != *pSlot) {
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
            bool restored = false;
            for (uint32_t fieldIndex = 0; fieldIndex < pObject->GetPropertyCount(); ++fieldIndex) {
                if (name != pObject->GetPropertyName(fieldIndex) || declaration != pEngine->GetTypeDeclaration(pObject->GetPropertyTypeId(fieldIndex), true)) {
                    continue;
                }
                auto field = AngelScriptTypeReflection::Property(pBindings, pObject, fieldIndex, false, true).ToValue();
                if (field && !field.IsConst() && CanSerializeAngelScriptValue(field.GetTypeInfo()) && deserializer.BeginObject(SR_UTILS_NS::SerializationId::Create("value"))) {
                    success &= LoadAngelScriptValue(field, deserializer);
                    deserializer.EndObject();
                    restored = true;
                }
                break;
            }
            if (!restored && deserializer.BeginObject(SR_UTILS_NS::SerializationId::Create("value"))) {
                success &= PreloadAngelScriptValue(pBindings, pExpected->GetModule(), declaration, deserializer);
                deserializer.EndObject();
            }
            deserializer.EndItem();
        }
        if (count > 0) {
            deserializer.EndArray();
        }
        return success;
    }

    bool PreloadAngelScriptValue(AngelScriptBindings* pBindings, asIScriptModule* pModule,
        const SR_UTILS_NS::String& declaration, SR_UTILS_NS::IDeserializer& deserializer)
    {
        const auto typeId = pModule->GetTypeIdByDecl(declaration.c_str());
        if (typeId < 0) {
            return true;
        }
        auto&& pInfo = AngelScriptTypeReflection::Resolve(pBindings, pModule->GetEngine(), typeId);
        if (!pInfo || !AngelScriptBindingHelpers::ContainsScriptType(*pInfo)) {
            return true;
        }
        AngelScriptGraphHelpers::PreloadScope scope;
        if (pInfo->kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject) {
            void* pObject = nullptr;
            auto value = SR_UTILS_NS::Reflection::ValueRef(pInfo, &pObject, false).ToValue();
            const bool success = LoadAngelScriptValue(value, deserializer);
            pInfo->DestructAt(&pObject);
            return success;
        }
        auto value = SR_UTILS_NS::Reflection::Value::CreateDefault(pInfo);
        return value && LoadAngelScriptValue(value, deserializer);
    }
}
#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
