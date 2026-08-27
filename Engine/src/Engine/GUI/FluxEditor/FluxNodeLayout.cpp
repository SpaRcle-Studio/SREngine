//
// Created by Monika on 22.08.2026.
//

#include <Engine/GUI/FluxEditor/FluxNodeLayout.h>

#include <Utils/Common/EnumReflector.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Reflection/Method.h>
#include <Utils/Reflection/Value.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/TypeTraits/Factory.h>

namespace SR_CORE_GUI_NS {
    namespace {
        FluxPinLayout& AddPin(SR_UTILS_NS::Vector<FluxPinLayout>& pins, SR_UTILS_NS::StringView name, const bool isFlow = false) {
            auto&& pin = pins.emplace_back();
            pin.name = name;
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

        /// Временная информация о типе класса, зарегистрированного в фабрике. Нужна редактору,
        /// чтобы подсветить совместимость пинов
        SR_NODISCARD SR_UTILS_NS::Reflection::TypeInfo* MakeClassTypeInfo(const SR_UTILS_NS::StringAtom className, SR_UTILS_NS::Vector<SR_UTILS_NS::Reflection::TypeInfo*>& tmpTypeInfos) {
            auto&& pType = SR_UTILS_NS::Factory::Instance().GetType(className);
            if (!pType) {
                return nullptr;
            }
            auto&& pTypeInfo = tmpTypeInfos.emplace_back(SR_UTILS_NS::Reflection::AllocateTypeInfo());
            pTypeInfo->category = SR_UTILS_NS::Reflection::ReflectedCategoryType::Object;
            pTypeInfo->detailedType = className;
            pTypeInfo->vtable = pType->GetVTable();
            return pTypeInfo;
        }

        void AddArgumentPins(SR_UTILS_NS::Vector<FluxPinLayout>& pins, const SR_UTILS_NS::Reflection::Method* pMethod) {
            if (!pMethod) {
                return;
            }
            for (uint32_t i = 0; i < pMethod->GetParamsCount(); ++i) {
                AddPin(pins, pMethod->GetParam(i).name.ToStringView()).pTypeInfo = pMethod->GetParam(i).pTypeInfo;
            }
        }
    }

    void BuildFluxNodeLayout(SR_FLUX_NS::FluxGraph& graph, const uint32_t nodeIndex, FluxNodeLayout& layout, SR_UTILS_NS::Vector<SR_UTILS_NS::Reflection::TypeInfo*>& tmpTypeInfos) {
        SR_TRACY_ZONE;

        layout.title.clear();
        layout.inputs.clear();
        layout.outputs.clear();

        auto&& pNode = graph.GetNode(nodeIndex);
        if (!pNode) {
            SRHalt("BuildFluxNodeLayout() : node index {} is out of range!", nodeIndex);
            return;
        }

        const auto callable = pNode->GetCallable();
        const SR_UTILS_NS::StringAtom name = pNode->GetName();

        switch (pNode->GetType()) {
            case SR_FLUX_NS::FluxGraphNodeType::Event: {
                if (name.empty()) {
                    layout.title = "Event (no name)";
                }
                else {
                    SR_UTILS_NS::FormatTo(layout.title, "Event: {}", name);
                }
                AddPin(layout.outputs, "Exec", true);
                /// сигнатура события неизвестна, поэтому показываем занятые пины плюс один свободный
                const uint32_t maxPin = graph.GetMaxOutputPin(nodeIndex);
                for (uint32_t i = 1; i <= maxPin + 1; ++i) {
                    AddPin(layout.outputs, SR_FORMAT("Arg {}", i - 1));
                }
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::Invoke:
            case SR_FLUX_NS::FluxGraphNodeType::Evaluate: {
                auto&& pMethod = callable.FindMethodMeta();
                pNode->SetType(pMethod ? (pMethod->IsEvaluate() ? SR_FLUX_NS::FluxGraphNodeType::Evaluate : SR_FLUX_NS::FluxGraphNodeType::Invoke) : pNode->GetType());

                if (pNode->GetType() == SR_FLUX_NS::FluxGraphNodeType::Invoke) {
                    AddPin(layout.inputs, "Exec", true);
                    SR_UTILS_NS::FormatTo(layout.title, "{}.{}", callable.object, callable.function);
                }
                else {
                    SR_UTILS_NS::FormatTo(layout.title, "= {}.{}", callable.object, callable.function);
                }
                if (!SR_UTILS_NS::GetSingletonManager()->GetSingletonMeta(callable.object.GetHash())) {
                    AddPin(layout.inputs, "Object").pTypeInfo = MakeClassTypeInfo(callable.object, tmpTypeInfos);
                }
                AddArgumentPins(layout.inputs, pMethod);

                if (pNode->GetType() == SR_FLUX_NS::FluxGraphNodeType::Invoke) {
                    AddPin(layout.outputs, "Exec", true);
                    if (pMethod && pMethod->HasReturn()) {
                        AddPin(layout.outputs, "Return").pTypeInfo = pMethod->GetReturnType();
                    }
                }
                else if (pMethod && pMethod->HasReturn()) {
                    AddPin(layout.outputs, "Result").pTypeInfo = pMethod->GetReturnType();
                }
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::Constant: {
                SR_UTILS_NS::FormatTo(layout.title, "Const: {} ({})", GetFluxValueTypeName(pNode->GetConstant()), GetFluxValuePreview(pNode->GetConstant()));
                AddPin(layout.outputs, "Value").pTypeInfo = &pNode->GetConstant().GetTypeInfo();
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::ReadVariable: {
                SR_UTILS_NS::FormatTo(layout.title, "Get: {}", name);
                AddPin(layout.outputs, "Value").pTypeInfo = &pNode->GetConstant().GetTypeInfo();
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::WriteVariable: {
                SR_UTILS_NS::FormatTo(layout.title, "Set: {}", name);
                AddPin(layout.inputs, "Exec", true);
                AddPin(layout.inputs, "Value").pTypeInfo = &pNode->GetConstant().GetTypeInfo();
                AddPin(layout.outputs, "Exec", true);
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::Branch: {
                layout.title = "Branch";
                AddPin(layout.inputs, "Exec", true);
                AddPin(layout.inputs, "Condition").pTypeInfo = tmpTypeInfos.emplace_back(SR_UTILS_NS::Reflection::DetermineTypeInfoAlloc<bool>());
                AddPin(layout.outputs, "True", true);
                AddPin(layout.outputs, "False", true);
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::While: {
                layout.title = "While";
                AddPin(layout.inputs, "Exec", true);
                AddPin(layout.inputs, "Condition").pTypeInfo = tmpTypeInfos.emplace_back(SR_UTILS_NS::Reflection::DetermineTypeInfoAlloc<bool>());
                AddPin(layout.outputs, "Body", true);
                AddPin(layout.outputs, "Completed", true);
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::For: {
                layout.title = "For";
                auto&& pIntTypeInfo = tmpTypeInfos.emplace_back(SR_UTILS_NS::Reflection::DetermineTypeInfoAlloc<int32_t>());
                AddPin(layout.inputs, "Exec", true);
                AddPin(layout.inputs, "First").pTypeInfo = pIntTypeInfo;
                AddPin(layout.inputs, "Last").pTypeInfo = pIntTypeInfo;
                AddPin(layout.inputs, "Step").pTypeInfo = pIntTypeInfo;
                AddPin(layout.outputs, "Body", true);
                AddPin(layout.outputs, "Completed", true);
                AddPin(layout.outputs, "Index").pTypeInfo = pIntTypeInfo;
                break;
            }
            case SR_FLUX_NS::FluxGraphNodeType::Cast: {
                if (name.empty()) {
                    layout.title = "Cast To (no type)";
                }
                else {
                    SR_UTILS_NS::FormatTo(layout.title, "Cast To {}", name);
                }
                AddPin(layout.inputs, "Exec", true);
                /// исходный объект может быть любого типа, поэтому пин не типизирован
                AddPin(layout.inputs, "Object");
                AddPin(layout.outputs, "Exec", true);
                AddPin(layout.outputs, "Cast Failed", true);
                const std::string resultPinName = name.empty() ? std::string("As Object") : SR_FORMAT("As {}", name);
                AddPin(layout.outputs, resultPinName).pTypeInfo = MakeClassTypeInfo(name, tmpTypeInfos);
                break;
            }
            default:
                layout.title = "Unknown";
                break;
        }
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
}
