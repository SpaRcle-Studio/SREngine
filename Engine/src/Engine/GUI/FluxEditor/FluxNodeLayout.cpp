//
// Created by Monika on 22.08.2026.
//

#include <Engine/GUI/FluxEditor/FluxNodeLayout.h>

#include <Utils/Common/EnumReflector.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Reflection/Method.h>
#include <Utils/Reflection/Value.h>
#include <Utils/TypeTraits/SRClassMeta.h>

namespace SR_CORE_GUI_NS {
    namespace {
        FluxPinLayout& AddPin(SR_UTILS_NS::Vector<FluxPinLayout>& pins, SR_UTILS_NS::String name, const bool isFlow = false) {
            auto&& pin = pins.emplace_back();
            pin.name = std::move(name);
            pin.isFlow = isFlow;
            return pin;
        }

        /// Количество пинов аргументов вызова. Если метод не найден, то показываем занятые пины плюс
        /// один свободный, чтобы можно было подключить следующий аргумент
        SR_NODISCARD uint32_t GetArgumentsCount(const SR_FLUX_NS::FluxGraph& graph, const uint32_t nodeIndex, const uint32_t firstArgumentPin) {
            const auto& node = *graph.GetNode(nodeIndex);

            if (auto&& pMethod = node.GetCallable().FindMethodMeta()) {
                return pMethod->GetParamsCount();
            }

            const uint32_t maxPin = graph.GetMaxInputPin(nodeIndex);
            return maxPin >= firstArgumentPin ? (maxPin - firstArgumentPin) + 2 : 1;
        }

        void AddArgumentPins(SR_UTILS_NS::Vector<FluxPinLayout>& pins, const uint32_t count) {
            for (uint32_t i = 0; i < count; ++i) {
                AddPin(pins, SR_FORMAT("Arg {}", i));
            }
        }
    }

    FluxNodeLayout BuildFluxNodeLayout(const SR_FLUX_NS::FluxGraph& graph, const uint32_t nodeIndex) {
        FluxNodeLayout layout;

        auto&& pNode = graph.GetNode(nodeIndex);
        if (!pNode) {
            SRHalt("BuildFluxNodeLayout() : node index {} is out of range!", nodeIndex);
            return layout;
        }

        const auto callable = pNode->GetCallable();
        const SR_UTILS_NS::StringAtom name = pNode->GetName();

        switch (pNode->GetType()) {
            case SR_FLUX_NS::FluxGraphNodeType::Event: {
                layout.title = name.empty() ? "Event" : SR_FORMAT("Event: {}", name.ToStringView());
                AddPin(layout.outputs, "Exec", true);
                /// сигнатура события неизвестна, поэтому показываем занятые пины плюс один свободный
                const uint32_t maxPin = graph.GetMaxOutputPin(nodeIndex);
                for (uint32_t i = 1; i <= maxPin + 1; ++i) {
                    AddPin(layout.outputs, SR_FORMAT("Arg {}", i - 1));
                }
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::Invoke: {
                layout.title = SR_FORMAT("{}.{}", callable.object.ToStringView(), callable.function.ToStringView());
                AddPin(layout.inputs, "Exec", true);
                if (!SR_UTILS_NS::GetSingletonManager()->GetSingletonMeta(callable.object.GetHash())) {
                    AddPin(layout.inputs, "Object");
                }
                auto&& pMethod = callable.FindMethodMeta();
                AddArgumentPins(layout.inputs, GetArgumentsCount(graph, nodeIndex, 2));
                AddPin(layout.outputs, "Exec", true);
                if (pMethod && pMethod->HasReturn()) {
                    AddPin(layout.outputs, "Return");
                }
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::Evaluate: {
                layout.title = SR_FORMAT("= {}.{}", callable.object.ToStringView(), callable.function.ToStringView());
                AddPin(layout.inputs, "Object");
                AddArgumentPins(layout.inputs, GetArgumentsCount(graph, nodeIndex, 1));
                AddPin(layout.outputs, "Result");
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::Constant: {
                layout.title = SR_FORMAT("Const: {}", GetFluxValuePreview(pNode->GetConstant()));
                AddPin(layout.outputs, "Value");
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::ReadVariable: {
                layout.title = SR_FORMAT("Get: {}", name.ToStringView());
                AddPin(layout.outputs, "Value");
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::WriteVariable: {
                layout.title = SR_FORMAT("Set: {}", name.ToStringView());
                AddPin(layout.inputs, "Exec", true);
                AddPin(layout.inputs, "Value");
                AddPin(layout.outputs, "Exec", true);
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::Branch: {
                layout.title = "Branch";
                AddPin(layout.inputs, "Exec", true);
                AddPin(layout.inputs, "Condition");
                AddPin(layout.outputs, "True", true);
                AddPin(layout.outputs, "False", true);
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::While: {
                layout.title = "While";
                AddPin(layout.inputs, "Exec", true);
                AddPin(layout.inputs, "Condition");
                AddPin(layout.outputs, "Body", true);
                AddPin(layout.outputs, "Completed", true);
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::For: {
                layout.title = "For";
                AddPin(layout.inputs, "Exec", true);
                AddPin(layout.inputs, "First");
                AddPin(layout.inputs, "Last");
                AddPin(layout.inputs, "Step");
                AddPin(layout.outputs, "Body", true);
                AddPin(layout.outputs, "Completed", true);
                AddPin(layout.outputs, "Index");
                break;
            }
            default:
                layout.title = "Unknown";
                break;
        }

        return layout;
    }

    SR_UTILS_NS::String GetFluxValuePreview(const SR_UTILS_NS::Reflection::Value& value) {
        if (!value.IsValid()) {
            return "none";
        }

        auto&& typeInfo = value.GetTypeInfo();

        switch (typeInfo.category) {
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::String: {
                if (typeInfo.detailedType == "String") {
                    return SR_FORMAT("\"{}\"", *value.Cast<SR_UTILS_NS::String>());
                }
                if (typeInfo.detailedType == "StringAtom") {
                    return SR_FORMAT("\"{}\"", value.Cast<SR_UTILS_NS::StringAtom>()->ToStringView());
                }
                if (typeInfo.detailedType == "Path") {
                    return SR_FORMAT("\"{}\"", value.Cast<SR_UTILS_NS::Path>()->View());
                }
                break;
            }
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::Arithmetic: {
                if (typeInfo.detailedType == "bool") {
                    return *value.Cast<bool>() ? "true" : "false";
                }
                if (typeInfo.detailedType == "float") {
                    return SR_FORMAT("{}", *value.Cast<float_t>());
                }
                if (typeInfo.detailedType == "double") {
                    return SR_FORMAT("{}", *value.Cast<double_t>());
                }
                if (typeInfo.detailedType == "int32_t") {
                    return SR_FORMAT("{}", *value.Cast<int32_t>());
                }
                if (typeInfo.detailedType == "int64_t") {
                    return SR_FORMAT("{}", *value.Cast<int64_t>());
                }
                if (typeInfo.detailedType == "uint32_t") {
                    return SR_FORMAT("{}", *value.Cast<uint32_t>());
                }
                if (typeInfo.detailedType == "uint64_t") {
                    return SR_FORMAT("{}", *value.Cast<uint64_t>());
                }
                break;
            }
            default:
                break;
        }

        return SR_UTILS_NS::String(typeInfo.detailedType.ToStringView());
    }

    SR_UTILS_NS::StringAtom GetFluxValueTypeName(const SR_UTILS_NS::Reflection::Value& value) {
        return value.IsValid() ? value.GetTypeInfo().detailedType : SR_UTILS_NS::StringAtom();
    }

    const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& GetFluxValueTypeNames() {
        static const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> types = {
            SR_UTILS_NS::StringAtom("bool"),
            SR_UTILS_NS::StringAtom("int32_t"),
            SR_UTILS_NS::StringAtom("int64_t"),
            SR_UTILS_NS::StringAtom("uint32_t"),
            SR_UTILS_NS::StringAtom("uint64_t"),
            SR_UTILS_NS::StringAtom("float"),
            SR_UTILS_NS::StringAtom("double"),
            SR_UTILS_NS::StringAtom("String")
        };
        return types;
    }

    SR_UTILS_NS::Reflection::Value CreateFluxValue(const SR_UTILS_NS::StringAtom typeName) {
        if (typeName == "bool") { return SR_UTILS_NS::Reflection::Value::Create<bool>(false); }
        if (typeName == "int32_t") { return SR_UTILS_NS::Reflection::Value::Create<int32_t>(0); }
        if (typeName == "int64_t") { return SR_UTILS_NS::Reflection::Value::Create<int64_t>(0); }
        if (typeName == "uint32_t") { return SR_UTILS_NS::Reflection::Value::Create<uint32_t>(0); }
        if (typeName == "uint64_t") { return SR_UTILS_NS::Reflection::Value::Create<uint64_t>(0); }
        if (typeName == "float") { return SR_UTILS_NS::Reflection::Value::Create<float_t>(0.f); }
        if (typeName == "double") { return SR_UTILS_NS::Reflection::Value::Create<double_t>(0.0); }
        if (typeName == "String") { return SR_UTILS_NS::Reflection::Value::Create(SR_UTILS_NS::String()); }

        SRHalt("CreateFluxValue() : unsupported value type \"{}\"!", typeName);
        return {};
    }
}
