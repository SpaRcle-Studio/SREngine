//
// Created by Codex on 13.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptValueSerialization.h>
#include <Scripting/AngelScript/AngelScriptObjectGraph.h>

#include <Utils/Reflection/TypeInfoSerialization.h>
#include <Utils/Common/EnumReflector.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Serialization/Serializable.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Types/Optional.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_SCRIPTING_NS {
    namespace AngelScriptSerializationHelpers {
        const auto valueId = SR_UTILS_NS::SerializationId::Create("value");
        const auto itemsId = SR_UTILS_NS::SerializationId::Create("items");
        const auto itemId = SR_UTILS_NS::SerializationId::Create("item");
        const auto keyId = SR_UTILS_NS::SerializationId::Create("key");
        const auto mappedId = SR_UTILS_NS::SerializationId::Create("mapped");

        bool IsSerializableReference(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            return info.kind == SR_UTILS_NS::Reflection::TypeKind::Object ||
                info.kind == SR_UTILS_NS::Reflection::TypeKind::EntityRef ||
                info.kind == SR_UTILS_NS::Reflection::TypeKind::ResourceRef;
        }

        void CollectLegacyComponents(const SR_UTILS_NS::Reflection::ValueRef& value,
            SR_UTILS_NS::Vector<SR_UTILS_NS::Reflection::ValueRef>& components) { /// NOLINT(misc-no-recursion)
            auto&& info = value.GetTypeInfo();
            if (info.fieldsCount == 0) {
                if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Enum) {
                    components.emplace_back(SR_UTILS_NS::Reflection::TypeOf<uint8_t>(), value.Data(), value.IsConst());
                }
                else {
                    components.emplace_back(value);
                }
                return;
            }
            for (uint32_t i = 0; i < info.fieldsCount; ++i) {
                auto&& field = info.pFields[i];
                CollectLegacyComponents(SR_UTILS_NS::Reflection::ValueRef(field.pType,
                    static_cast<uint8_t*>(value.Data()) + field.offset, value.IsConst()), components);
            }
        }
    }

    bool CanSerializeAngelScriptValue(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        if (info.IsArithmetic()) {
            return true;
        }

        if (info.fieldsCount > 0) {
            for (uint32_t i = 0; i < info.fieldsCount; ++i) {
                if (!CanSerializeAngelScriptValue(*info.pFields[i].pType)) {
                    return false;
                }
            }
            return true;
        }

        switch (info.kind) {
            case SR_UTILS_NS::Reflection::TypeKind::ScriptObject:
            case SR_UTILS_NS::Reflection::TypeKind::ScriptHandle:
                return true;
            case SR_UTILS_NS::Reflection::TypeKind::Enum:
            case SR_UTILS_NS::Reflection::TypeKind::EntityRef:
            case SR_UTILS_NS::Reflection::TypeKind::ResourceRef:
            case SR_UTILS_NS::Reflection::TypeKind::String:
            case SR_UTILS_NS::Reflection::TypeKind::StringAtom:
            case SR_UTILS_NS::Reflection::TypeKind::Path:
                return true;
            case SR_UTILS_NS::Reflection::TypeKind::Object: {
                auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(info.name);
                return pMeta && pMeta->IsSameOrInherited("Serializable");
            }
            case SR_UTILS_NS::Reflection::TypeKind::Optional:
            case SR_UTILS_NS::Reflection::TypeKind::Vector:
            case SR_UTILS_NS::Reflection::TypeKind::Set:
            case SR_UTILS_NS::Reflection::TypeKind::FlatHashSet:
                return info.pNext[0] && CanSerializeAngelScriptValue(*info.pNext[0]);
            case SR_UTILS_NS::Reflection::TypeKind::Map:
            case SR_UTILS_NS::Reflection::TypeKind::FlatHashMap:
                return info.GetArgument(0) && info.GetArgument(1) &&
                    CanSerializeAngelScriptValue(*info.GetArgument(0)) && CanSerializeAngelScriptValue(*info.GetArgument(1));
            default:
                return false;
        }
    }

    void SaveAngelScriptValue(const SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::ISerializer& serializer) {
        SR_TRACY_ZONE;
        AngelScriptObjectGraph graph;

        auto&& info = value.GetTypeInfo();
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject || info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
            SaveAngelScriptObject(value, serializer);
            return;
        }

        if (AngelScriptSerializationHelpers::IsSerializableReference(info)) {
            auto&& pSerializable = dynamic_cast<SR_UTILS_NS::Serializable*>(value.GetSRClass());
            if (pSerializable) {
                pSerializable->Save(serializer);
            }
            return;
        }

        if (auto&& pOptional = value.GetOptionalBase()) {
            serializer.WriteBool(pOptional->HasValue(), SR_UTILS_NS::SerializationId::Create("hasValue"));
            if (pOptional->HasValue()) {
                SaveAngelScriptValue(pOptional->GetReflectionValue(), serializer);
            }
            return;
        }

        if (info.IsContainer()) {
            if (const auto array = value.AsArray()) {
                const auto size = array.Size();
                serializer.BeginArray(size, AngelScriptSerializationHelpers::itemsId);

                for (SR_UTILS_NS::SizeType i = 0; i < size; ++i) {
                    serializer.BeginItem(AngelScriptSerializationHelpers::itemId);
                    serializer.BeginObject(AngelScriptSerializationHelpers::keyId);
                    SaveAngelScriptValue(array.At(i).ToValue(), serializer);
                    serializer.EndObject();
                    serializer.EndItem();
                }

                serializer.EndArray();
                return;
            }

            const auto map = value.AsMap();
            serializer.BeginArray(map.Size(), AngelScriptSerializationHelpers::itemsId);

            map.ForEach([&serializer, &map](const SR_UTILS_NS::Reflection::ValueRef& key, const SR_UTILS_NS::Reflection::ValueRef& mapped) {
                serializer.BeginItem(AngelScriptSerializationHelpers::itemId);
                serializer.BeginObject(AngelScriptSerializationHelpers::keyId);
                SaveAngelScriptValue(key.ToValue(), serializer);
                serializer.EndObject();

                if (!map.IsSet()) {
                    serializer.BeginObject(AngelScriptSerializationHelpers::mappedId);
                    SaveAngelScriptValue(mapped.ToValue(), serializer);
                    serializer.EndObject();
                }

                serializer.EndItem();
            });

            serializer.EndArray();
            return;
        }

        if (info.fieldsCount > 0) {
            SR_UTILS_NS::Reflection::SerializeValue(value, serializer);
            return;
        }

        if (info.IsString()) {
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::StringAtom) {
                serializer.WriteString(value.Cast<SR_UTILS_NS::StringAtom>()->ToStringView(), AngelScriptSerializationHelpers::valueId);
            }
            else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Path) {
                serializer.WriteString(value.Cast<SR_UTILS_NS::Path>()->ToStringView(), AngelScriptSerializationHelpers::valueId);
            }
            else {
                serializer.WriteString(*value.Cast<SR_UTILS_NS::String>(), AngelScriptSerializationHelpers::valueId);
            }
            return;
        }

        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Enum) {
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(info.name);
            serializer.WriteInt(pReflector->ReadEnumValueFromPointerInternal(value.Data()), AngelScriptSerializationHelpers::valueId);
            return;
        }

        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Bool) {
            serializer.WriteBool(*value.Cast<bool>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Float) {
            serializer.WriteFloat(*value.Cast<float_t>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Double) {
            serializer.WriteDouble(*value.Cast<double_t>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (value.IsSigned()) {
            const auto size = info.GetScalarSize();
            int64_t number = 0;

            if (size == 1) {
                number = *value.Cast<int8_t>();
            }
            else if (size == 2) {
                number = *value.Cast<int16_t>();
            }
            else if (size == 4) {
                number = *value.Cast<int32_t>();
            }
            else {
                number = *value.Cast<int64_t>();
            }

            serializer.WriteInt(number, AngelScriptSerializationHelpers::valueId);
        }
        else {
            uint64_t number = 0;
            memcpy(&number, value.Data(), info.GetScalarSize());
            serializer.WriteUInt(number, AngelScriptSerializationHelpers::valueId);
        }
    }

    bool LoadAngelScriptValue(SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::IDeserializer& deserializer) {
        SR_TRACY_ZONE;
        AngelScriptObjectGraph graph;

        auto&& info = value.GetTypeInfo();
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject || info.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle) {
            return LoadAngelScriptObject(value, deserializer);
        }

        if (AngelScriptSerializationHelpers::IsSerializableReference(info)) {
            auto&& pSerializable = dynamic_cast<SR_UTILS_NS::Serializable*>(value.GetSRClass());
            return pSerializable && pSerializable->Load(deserializer);
        }

        if (auto&& pOptional = value.GetOptionalBase()) {
            bool hasValue = false;
            deserializer.ReadBool(hasValue, SR_UTILS_NS::SerializationId::Create("hasValue"));
            pOptional->Reset();
            if (!hasValue) {
                return true;
            }
            auto element = SR_UTILS_NS::Reflection::Value::CreateDefault(info.pNext[0]);
            if (!element || !LoadAngelScriptValue(element, deserializer)) {
                return false;
            }
            pOptional->SetValue(element);
            return true;
        }

        if (info.IsContainer()) {
            const auto array = value.AsArray();
            const auto map = value.AsMap();
            const auto count = deserializer.BeginArray(AngelScriptSerializationHelpers::itemsId);
            array.Clear();
            map.Clear();
            array.Reserve(count);
            if (array) {
                array.Resize(count);
            }
            bool success = true;
            auto&& pKeyType = info.GetArgument(0);

            for (uint32_t i = 0; i < count; ++i) {
                if (!deserializer.BeginItem(AngelScriptSerializationHelpers::itemId, i)) {
                    success = false;
                    break;
                }

                auto key = array ? array.At(i).ToValue() : SR_UTILS_NS::Reflection::Value::CreateDefault(pKeyType);

                if (deserializer.BeginObject(AngelScriptSerializationHelpers::keyId)) {
                    success &= LoadAngelScriptValue(key, deserializer);
                    deserializer.EndObject();
                }
                else {
                    success = false;
                }

                SR_UTILS_NS::Reflection::Value mapped;

                if (info.IsMapLike()) {
                    mapped = SR_UTILS_NS::Reflection::Value::CreateDefault(info.GetArgument(1));

                    if (deserializer.BeginObject(AngelScriptSerializationHelpers::mappedId)) {
                        success &= LoadAngelScriptValue(mapped, deserializer);
                        deserializer.EndObject();
                    }
                    else {
                        success = false;
                    }
                }

                if (success) {
                    if (!array) {
                        map.InsertOrAssign(key.AsRef(), mapped.AsRef());
                    }
                }

                deserializer.EndItem();
            }

            deserializer.EndArray();

            return success;
        }

        if (info.fieldsCount > 0) {
            if (deserializer.HasKey(SR_UTILS_NS::SerializationId::Create("fields"))) {
                return SR_UTILS_NS::Reflection::DeserializeValue(value, deserializer);
            }
            SR_UTILS_NS::Vector<SR_UTILS_NS::Reflection::ValueRef> components;
            AngelScriptSerializationHelpers::CollectLegacyComponents(value.AsRef(), components);
            const auto count = deserializer.BeginArray(AngelScriptSerializationHelpers::itemsId);
            bool success = count == components.size();

            for (uint32_t i = 0; i < count; ++i) {
                if (!deserializer.BeginItem(AngelScriptSerializationHelpers::itemId, i)) {
                    success = false;
                    break;
                }

                if (i < components.size()) {
                    auto component = components[i].ToValue();

                    success &= LoadAngelScriptValue(component, deserializer);
                }

                deserializer.EndItem();
            }

            deserializer.EndArray();

            return success;
        }

        if (info.IsString()) {
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::StringAtom) {
                deserializer.ReadString(*value.Cast<SR_UTILS_NS::StringAtom>(), AngelScriptSerializationHelpers::valueId);
            }
            else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Path) {
                deserializer.ReadString(*value.Cast<SR_UTILS_NS::Path>(), AngelScriptSerializationHelpers::valueId);
            }
            else {
                deserializer.ReadString(*value.Cast<SR_UTILS_NS::String>(), AngelScriptSerializationHelpers::valueId);
            }

            return true;
        }

        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Enum) {
            int64_t number = 0;
            deserializer.ReadInt(number, AngelScriptSerializationHelpers::valueId);
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(info.name);
            pReflector->WriteEnumValueToPointerInternal(value.Data(), number);

            return true;
        }

        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Bool) {
            deserializer.ReadBool(*value.Cast<bool>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Float) {
            deserializer.ReadFloat(*value.Cast<float_t>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Double) {
            deserializer.ReadDouble(*value.Cast<double_t>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (value.IsSigned()) {
            int64_t number = 0;
            deserializer.ReadInt(number, AngelScriptSerializationHelpers::valueId);
            memcpy(value.Data(), &number, info.GetScalarSize());
        }
        else {
            uint64_t number = 0;
            deserializer.ReadUInt(number, AngelScriptSerializationHelpers::valueId);
            memcpy(value.Data(), &number, info.GetScalarSize());
        }

        return true;
    }
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
