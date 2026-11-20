//
// Created by Codex on 14.11.2026.
//

#include <Scripting/AngelScript/AngelScriptDebugNativeValues.h>

#if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
#include <Utils/Common/EnumReflector.h>
#include <Utils/Reflection/Property.h>
#include <Utils/TypeTraits/SRClass.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Types/Optional.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Profile/TracyContext.h>
#include <Utils/Reflection/TypeInfoSerialization.h>

namespace SR_SCRIPTING_NS::AngelScriptDebugNativeValues {
    SR_UTILS_NS::String Summary(SR_UTILS_NS::Reflection::Value& value) {
        if (!value) {
            return "<unavailable>";
        }
        auto&& info = value.GetTypeInfo();
        if (info.vtable.pIsNull && info.vtable.pIsNull(info, value.Data())) {
            return "null";
        }
        if (value.IsSharedPtr() && !value.GetSharedPtrBase()->Valid()) {
            return "null";
        }
        if (info.IsArithmetic()) {
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Bool) {
                return *value.Cast<bool>() ? "true" : "false";
            }
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Float) {
                return "{}"_format(*value.Cast<float_t>());
            }
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Double) {
                return "{}"_format(*value.Cast<double_t>());
            }
            const auto size = value.SizeOf();
            if (size == 0 || size > sizeof(uint64_t)) {
                return "<unsupported scalar>";
            }
            uint64_t bits = 0;
            memcpy(&bits, value.Data(), size);
            if (value.IsSigned()) {
                if (size < sizeof(bits) && (bits & (uint64_t(1) << (size * 8 - 1)))) {
                    bits |= ~uint64_t(0) << (size * 8);
                }
                return "{}"_format(static_cast<int64_t>(bits));
            }
            return "{}"_format(bits);
        }
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Enum) {
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(info.name);
            if (pReflector) {
                const auto number = pReflector->ReadEnumValueFromPointerInternal(value.Data());
                return "{}"_format(number);
            }
        }
        switch (info.kind) {
            case SR_UTILS_NS::Reflection::TypeKind::String:
                return "\"" + *value.Cast<SR_UTILS_NS::String>() + "\"";
            case SR_UTILS_NS::Reflection::TypeKind::StringAtom:
                return "\"" + SR_UTILS_NS::String(*value.Cast<SR_UTILS_NS::StringAtom>()) + "\"";
            case SR_UTILS_NS::Reflection::TypeKind::StringView:
                return "\"" + SR_UTILS_NS::String(*value.Cast<SR_UTILS_NS::StringView>()) + "\"";
            case SR_UTILS_NS::Reflection::TypeKind::Path:
                return value.Cast<SR_UTILS_NS::Path>()->ToStringRef();
            default:
                break;
        }
        if (const auto array = value.AsArray()) {
            return "size = {}"_format(array.Size());
        }
        if (const auto map = value.AsMap()) {
            return "size = {}"_format(map.Size());
        }
        return HasChildren(value) ? "{...}" : "<native object: no reflected properties>";
    }

    bool HasChildren(SR_UTILS_NS::Reflection::Value& value) {
        if (!value || (value.IsSharedPtr() && !value.GetSharedPtrBase()->Valid())) {
            return false;
        }
        auto&& info = value.GetTypeInfo();
        if (value.AsRef().FieldCount() || info.kind == SR_UTILS_NS::Reflection::TypeKind::Value) {
            return true;
        }
        if (SR_UTILS_NS::Reflection::IsTypeKindContainer(info.kind)) {
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Optional || info.kind == SR_UTILS_NS::Reflection::TypeKind::Pair) {
                return true;
            }
            if (value.AsArray() || value.AsMap()) {
                return true;
            }
        }
        if (auto&& pObject = value.GetSRClass()) {
            bool hasProperties = false;
            pObject->GetMeta()->ForEachProperty([&](const SR_UTILS_NS::Reflection::Property&, uint64_t) {
                hasProperties = true;
            });
            return hasProperties;
        }
        return false;
    }

    SR_UTILS_NS::Vector<Child> Children(SR_UTILS_NS::Reflection::Value& value) {
        SR_TRACY_ZONE;
        SR_UTILS_NS::Vector<Child> result;
        if (!value || (value.IsSharedPtr() && !value.GetSharedPtrBase()->Valid())) {
            return result;
        }
        auto&& info = value.GetTypeInfo();
        for (uint32_t i = 0; i < value.AsRef().FieldCount(); ++i) {
            auto field = value.AsRef().Field(i);
            if (field) {
                result.emplace_back(Child{SR_UTILS_NS::String(value.AsRef().FieldName(i)), field.ToValue()});
            }
        }
        if (info.fieldsCount || info.vtable.pFieldCount) {
            return result;
        }
        if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Value) {
            auto&& payload = *value.Cast<SR_UTILS_NS::Reflection::Value>();
            result.emplace_back(Child{"value", payload.Ref()});
            return result;
        }
        if (auto&& pOptional = value.GetOptionalBase()) {
            result.emplace_back(Child{"hasValue", SR_UTILS_NS::Reflection::Value::Create(pOptional->HasValue())});
            if (pOptional->HasValue()) {
                result.emplace_back(Child{"value", pOptional->GetReflectionValue()});
            }
            return result;
        }
        constexpr uint32_t maxChildren = 256;
        if (const auto array = value.AsArray()) {
            const auto size = array.Size();
            result.emplace_back(Child{"size", SR_UTILS_NS::Reflection::Value::Create(uint64_t(size))});
            for (uint32_t i = 0; i < size && i < maxChildren; ++i) {
                result.emplace_back(Child{"[{}]"_format(i), array.At(i).ToValue()});
            }
            return result;
        }
        if (const auto map = value.AsMap()) {
            result.emplace_back(Child{"size", SR_UTILS_NS::Reflection::Value::Create(uint64_t(map.Size()))});
            uint32_t index = 0;
            map.ForEach([&](const SR_UTILS_NS::Reflection::ValueRef& key, const SR_UTILS_NS::Reflection::ValueRef& mapped) {
                result.emplace_back(Child{"[{}]"_format(index), key.ToValue()});
                if (mapped) {
                    result.emplace_back(Child{"[{}].value"_format(index), mapped.ToValue()});
                }
                return ++index < maxChildren;
            });
            return result;
        }
        if (auto&& pObject = value.GetSRClass()) {
            pObject->GetMeta()->ForEachProperty([&](const SR_UTILS_NS::Reflection::Property& property, uint64_t) {
                result.emplace_back(Child{SR_UTILS_NS::String(property.GetName()), property.Get(pObject)});
            });
        }
        return result;
    }
}
#endif
