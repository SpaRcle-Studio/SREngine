//
// Created by Codex on 14.11.2026.
//

#include <Scripting/AngelScript/AngelScriptDebugNativeValues.h>

#if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
#include <Scripting/AngelScript/AngelScriptMathHelpers.h>
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
        if (value.IsSharedPtr() && !value.GetSharedPtrBase()->Valid()) {
            return "null";
        }
        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Arithmetic) {
            if (info.detailedType == "bool") {
                return *value.Cast<bool>() ? "true" : "false";
            }
            if (info.detailedType == "float") {
                return "{}"_format(*value.Cast<float_t>());
            }
            if (info.detailedType == "double") {
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
        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(info.detailedType);
            if (pReflector) {
                const auto number = pReflector->ReadEnumValueFromPointerInternal(value.Data());
                return "{}"_format(number);
            }
        }
        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String) {
            if (info.detailedType == "String") {
                return "\"" + *value.Cast<SR_UTILS_NS::String>() + "\"";
            }
            if (info.detailedType == "StringAtom") {
                return "\"" + SR_UTILS_NS::String(*value.Cast<SR_UTILS_NS::StringAtom>()) + "\"";
            }
            if (info.detailedType == "StringView") {
                return "\"" + SR_UTILS_NS::String(*value.Cast<SR_UTILS_NS::StringView>()) + "\"";
            }
            if (info.detailedType == "Path") {
                return value.Cast<SR_UTILS_NS::Path>()->ToStringRef();
            }
        }
        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container && info.vtable.containerVTable.pSize) {
            return "size = {}"_format(info.vtable.containerVTable.pSize(value.GetStorage()));
        }
        return HasChildren(value) ? "{...}" : "<native object: no reflected properties>";
    }

    bool HasChildren(SR_UTILS_NS::Reflection::Value& value) {
        if (!value || (value.IsSharedPtr() && !value.GetSharedPtrBase()->Valid())) {
            return false;
        }
        auto&& info = value.GetTypeInfo();
        if (AngelScriptMathHelpers::Describe(info).count || info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
            return true;
        }
        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container) {
            if (info.detailedType == "Optional" || info.detailedType == "Pair") {
                return true;
            }
            if (info.vtable.containerVTable.pSize && info.vtable.containerVTable.pBegin && info.vtable.containerVTable.pEnd &&
                info.vtable.iteratorVTable.pGetValue && info.vtable.iteratorVTable.pOffset) {
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
        const auto layout = AngelScriptMathHelpers::Describe(info);
        for (uint32_t i = 0; i < layout.count; ++i) {
            auto&& component = layout.components[i];
            auto&& pInfo = SR_UTILS_NS::Reflection::LoadTypeInfo("Arithmetic." + SR_UTILS_NS::String(component.pScalar));
            if (!pInfo || !SR_UTILS_NS::Reflection::FindVTable(*pInfo)) {
                SR_UTILS_NS::Reflection::FreeTypeInfo(pInfo);
                continue;
            }
            auto scalar = SR_UTILS_NS::Reflection::Value::CreateDefault(pInfo);
            SR_UTILS_NS::Reflection::FreeTypeInfo(pInfo);
            if (scalar && component.offset + scalar.SizeOf() <= value.SizeOf()) {
                memcpy(scalar.Data(), static_cast<const char*>(value.Data()) + component.offset, scalar.SizeOf());
                result.emplace_back(Child{component.pName, std::move(scalar)});
            }
        }
        if (layout.count) {
            return result;
        }
        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
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
        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container && info.detailedType == "Pair" && info.vtable.pairVTable.pGetPairValue) {
            for (uint32_t i = 0; i < 2; ++i) {
                auto storage = info.vtable.pairVTable.pGetPairValue(value.GetStorage(), i == 0);
                if (storage.GetData() && info.pNext[i]) {
                    auto child = SR_UTILS_NS::Reflection::Value::CreateRef(*static_cast<char*>(storage.GetData()),
                        SR_UTILS_NS::Reflection::CopyTypeInfo(info.pNext[i]));
                    child.GetStorage() = storage;
                    result.emplace_back(Child{i == 0 ? "first" : "second", std::move(child)});
                }
            }
            return result;
        }
        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container && info.vtable.containerVTable.pSize &&
            info.vtable.containerVTable.pBegin && info.vtable.containerVTable.pEnd && info.vtable.iteratorVTable.pGetValue && info.vtable.iteratorVTable.pOffset) {
            auto container = value.AsSequenceContainer();
            result.emplace_back(Child{"size", SR_UTILS_NS::Reflection::Value::Create(uint64_t(container.Size()))});
            auto iterator = container.Begin();
            const auto end = container.End();
            for (uint32_t i = 0; iterator != end && i < 256; ++i, ++iterator) {
                result.emplace_back(Child{"[{}]"_format(i), *iterator});
            }
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
