//
// Created by Codex on 13.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptValueSerialization.h>
#include <Scripting/AngelScript/AngelScriptMathHelpers.h>

#include <Utils/Reflection/TypeInfoSerialization.h>
#include <Utils/Common/EnumReflector.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Serialization/Serializable.h>
#include <Utils/Types/Optional.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_SCRIPTING_NS {
    namespace AngelScriptSerializationHelpers {
        const auto valueId = SR_UTILS_NS::SerializationId::Create("value");
        const auto itemsId = SR_UTILS_NS::SerializationId::Create("items");
        const auto itemId = SR_UTILS_NS::SerializationId::Create("item");
        const auto keyId = SR_UTILS_NS::SerializationId::Create("key");
        const auto mappedId = SR_UTILS_NS::SerializationId::Create("mapped");

        bool IsMap(const SR_UTILS_NS::Reflection::TypeInfo& info) {
            return info.detailedType == "Map" || info.detailedType == "FlatHashMap";
        }
    }

    bool CanSerializeAngelScriptValue(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        switch (info.category) {
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::Arithmetic:
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum:
                return true;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::MathVector:
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::MathRect:
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::MathSize:
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::MathObject:
                return AngelScriptMathHelpers::Describe(info).count > 0;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::String:
                return info.detailedType == "String" || info.detailedType == "StringAtom" || info.detailedType == "Path";
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::Container: {
                if (info.detailedType == "EntityRef" || info.detailedType == "ResourceRef") {
                    return true;
                }
                if (info.detailedType == "Optional") {
                    return info.pNext[0] && CanSerializeAngelScriptValue(*info.pNext[0]);
                }
                if (AngelScriptSerializationHelpers::IsMap(info)) {
                    return info.pNext[0] && info.pNext[0]->pNext[0] && info.pNext[0]->pNext[1] &&
                        CanSerializeAngelScriptValue(*info.pNext[0]->pNext[0]) && CanSerializeAngelScriptValue(*info.pNext[0]->pNext[1]);
                }

                return (info.detailedType == "Vector" || info.detailedType == "Set" || info.detailedType == "FlatHashSet") &&
                    info.pNext[0] && CanSerializeAngelScriptValue(*info.pNext[0]);
            }
            default:
                return false;
        }
    }

    void SaveAngelScriptValue(const SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::ISerializer& serializer) {
        SR_TRACY_ZONE;

        auto&& info = value.GetTypeInfo();

        if (info.detailedType == "EntityRef" || info.detailedType == "ResourceRef") {
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

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container) {
            auto container = SR_UTILS_NS::Reflection::BaseContainerValueRef(const_cast<SR_UTILS_NS::Reflection::Value*>(&value));
            serializer.BeginArray(container.Size(), AngelScriptSerializationHelpers::itemsId);

            for (auto it = container.Begin(); it != container.End(); ++it) {
                serializer.BeginItem(AngelScriptSerializationHelpers::itemId);
                serializer.BeginObject(AngelScriptSerializationHelpers::keyId);
                SaveAngelScriptValue(it.First(), serializer);
                serializer.EndObject();

                if (AngelScriptSerializationHelpers::IsMap(info)) {
                    serializer.BeginObject(AngelScriptSerializationHelpers::mappedId);
                    SaveAngelScriptValue(it.Second(), serializer);
                    serializer.EndObject();
                }

                serializer.EndItem();
            }

            serializer.EndArray();
            return;
        }

        const auto layout = AngelScriptMathHelpers::Describe(info);

        if (layout.count > 0) {
            serializer.BeginArray(layout.count, AngelScriptSerializationHelpers::itemsId);

            for (uint32_t i = 0; i < layout.count; ++i) {
                auto&& descriptor = layout.components[i];
                auto&& pScalar = SR_UTILS_NS::Reflection::LoadTypeInfo("Arithmetic." + SR_UTILS_NS::String(descriptor.pScalar));
                SR_UTILS_NS::Reflection::FindVTable(*pScalar);
                auto component = SR_UTILS_NS::Reflection::Value::CreateDefault(pScalar);
                SR_UTILS_NS::Reflection::FreeTypeInfo(pScalar);

                const auto size = SR_UTILS_NS::Reflection::GetReflectedTypeSize(descriptor.pScalar);
                memcpy(component.Data(), static_cast<const char*>(value.Data()) + descriptor.offset, size);
                serializer.BeginItem(AngelScriptSerializationHelpers::itemId);
                SaveAngelScriptValue(component, serializer);
                serializer.EndItem();
            }

            serializer.EndArray();
            return;
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String) {
            if (info.detailedType == "StringAtom") {
                serializer.WriteString(value.Cast<SR_UTILS_NS::StringAtom>()->ToStringView(), AngelScriptSerializationHelpers::valueId);
            }
            else if (info.detailedType == "Path") {
                serializer.WriteString(value.Cast<SR_UTILS_NS::Path>()->ToStringView(), AngelScriptSerializationHelpers::valueId);
            }
            else {
                serializer.WriteString(*value.Cast<SR_UTILS_NS::String>(), AngelScriptSerializationHelpers::valueId);
            }
            return;
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(info.detailedType);
            serializer.WriteInt(pReflector->ReadEnumValueFromPointerInternal(value.Data()), AngelScriptSerializationHelpers::valueId);
            return;
        }

        if (info.detailedType == "bool") {
            serializer.WriteBool(*value.Cast<bool>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (info.detailedType == "float") {
            serializer.WriteFloat(*value.Cast<float_t>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (info.detailedType == "double") {
            serializer.WriteDouble(*value.Cast<double_t>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (value.IsSigned()) {
            const auto size = SR_UTILS_NS::Reflection::GetReflectedTypeSize(info.detailedType);
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
            memcpy(&number, value.Data(), SR_UTILS_NS::Reflection::GetReflectedTypeSize(info.detailedType));
            serializer.WriteUInt(number, AngelScriptSerializationHelpers::valueId);
        }
    }

    bool LoadAngelScriptValue(SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::IDeserializer& deserializer) {
        SR_TRACY_ZONE;

        auto&& info = value.GetTypeInfo();

        if (info.detailedType == "EntityRef" || info.detailedType == "ResourceRef") {
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

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container) {
            auto container = SR_UTILS_NS::Reflection::BaseContainerValueRef(&value);
            const auto count = deserializer.BeginArray(AngelScriptSerializationHelpers::itemsId);
            container.Clear();
            bool success = true;
            auto&& pKeyType = AngelScriptSerializationHelpers::IsMap(info) ? info.pNext[0]->pNext[0] : info.pNext[0];

            for (uint32_t i = 0; i < count; ++i) {
                if (!deserializer.BeginItem(AngelScriptSerializationHelpers::itemId, i)) {
                    success = false;
                    break;
                }

                auto key = SR_UTILS_NS::Reflection::Value::CreateDefault(const_cast<SR_UTILS_NS::Reflection::TypeInfo*>(pKeyType));

                if (deserializer.BeginObject(AngelScriptSerializationHelpers::keyId)) {
                    success &= LoadAngelScriptValue(key, deserializer);
                    deserializer.EndObject();
                }
                else {
                    success = false;
                }

                SR_UTILS_NS::Reflection::Value mapped;

                if (AngelScriptSerializationHelpers::IsMap(info)) {
                    mapped = SR_UTILS_NS::Reflection::Value::CreateDefault(info.pNext[0]->pNext[1]);

                    if (deserializer.BeginObject(AngelScriptSerializationHelpers::mappedId)) {
                        success &= LoadAngelScriptValue(mapped, deserializer);
                        deserializer.EndObject();
                    }
                    else {
                        success = false;
                    }
                }

                if (success) {
                    auto&& table = info.vtable.containerVTable;
                    auto it = table.pEnd(value.GetStorage());
                    table.pInsert(value.GetStorage(), it, key.GetStorage(), mapped.GetStorage());
                }

                deserializer.EndItem();
            }

            deserializer.EndArray();

            return success;
        }

        const auto layout = AngelScriptMathHelpers::Describe(info);

        if (layout.count > 0) {
            const auto count = deserializer.BeginArray(AngelScriptSerializationHelpers::itemsId);
            bool success = count == layout.count;

            for (uint32_t i = 0; i < count; ++i) {
                if (!deserializer.BeginItem(AngelScriptSerializationHelpers::itemId, i)) {
                    success = false;
                    break;
                }

                if (i < layout.count) {
                    auto&& descriptor = layout.components[i];
                    auto&& pScalar = SR_UTILS_NS::Reflection::LoadTypeInfo("Arithmetic." + SR_UTILS_NS::String(descriptor.pScalar));
                    SR_UTILS_NS::Reflection::FindVTable(*pScalar);
                    auto component = SR_UTILS_NS::Reflection::Value::CreateDefault(pScalar);
                    SR_UTILS_NS::Reflection::FreeTypeInfo(pScalar);

                    success &= LoadAngelScriptValue(component, deserializer);
                    const auto size = SR_UTILS_NS::Reflection::GetReflectedTypeSize(descriptor.pScalar);
                    memcpy(static_cast<char*>(value.Data()) + descriptor.offset, component.Data(), size);
                }

                deserializer.EndItem();
            }

            deserializer.EndArray();

            return success;
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String) {
            if (info.detailedType == "StringAtom") {
                deserializer.ReadString(*value.Cast<SR_UTILS_NS::StringAtom>(), AngelScriptSerializationHelpers::valueId);
            }
            else if (info.detailedType == "Path") {
                deserializer.ReadString(*value.Cast<SR_UTILS_NS::Path>(), AngelScriptSerializationHelpers::valueId);
            }
            else {
                deserializer.ReadString(*value.Cast<SR_UTILS_NS::String>(), AngelScriptSerializationHelpers::valueId);
            }

            return true;
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
            int64_t number = 0;
            deserializer.ReadInt(number, AngelScriptSerializationHelpers::valueId);
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(info.detailedType);
            pReflector->WriteEnumValueToPointerInternal(value.Data(), number);

            return true;
        }

        if (info.detailedType == "bool") {
            deserializer.ReadBool(*value.Cast<bool>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (info.detailedType == "float") {
            deserializer.ReadFloat(*value.Cast<float_t>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (info.detailedType == "double") {
            deserializer.ReadDouble(*value.Cast<double_t>(), AngelScriptSerializationHelpers::valueId);
        }
        else if (value.IsSigned()) {
            int64_t number = 0;
            deserializer.ReadInt(number, AngelScriptSerializationHelpers::valueId);
            memcpy(value.Data(), &number, SR_UTILS_NS::Reflection::GetReflectedTypeSize(info.detailedType));
        }
        else {
            uint64_t number = 0;
            deserializer.ReadUInt(number, AngelScriptSerializationHelpers::valueId);
            memcpy(value.Data(), &number, SR_UTILS_NS::Reflection::GetReflectedTypeSize(info.detailedType));
        }

        return true;
    }
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
