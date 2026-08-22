//
// Created by Monika on 22.08.2026.
//

#ifndef SR_ENGINE_CORE_GUI_FLUX_NODE_LAYOUT_H
#define SR_ENGINE_CORE_GUI_FLUX_NODE_LAYOUT_H

#include <Engine/stdInclude.h>

#include <Utils/Flux/Graph/FluxGraph.h>

namespace SR_UTILS_NS::Reflection {
    class Method;
}

namespace SR_CORE_GUI_NS {
    struct FluxPinLayout {
        SR_UTILS_NS::String name;
        bool isFlow = false;
    };

    /// Раскладка узла для редактора. Порядок пинов обязан совпадать с описанием в FluxGraph.h,
    /// так как компилятор графа адресует пины по индексам
    struct FluxNodeLayout {
        SR_UTILS_NS::String title;
        SR_UTILS_NS::Vector<FluxPinLayout> inputs;
        SR_UTILS_NS::Vector<FluxPinLayout> outputs;

        SR_NODISCARD bool IsFlowInput(uint32_t pinIndex) const {
            return pinIndex < inputs.size() && inputs[pinIndex].isFlow;
        }
        SR_NODISCARD bool IsFlowOutput(uint32_t pinIndex) const {
            return pinIndex < outputs.size() && outputs[pinIndex].isFlow;
        }
    };

    SR_NODISCARD FluxNodeLayout BuildFluxNodeLayout(const SR_FLUX_NS::FluxGraph& graph, uint32_t nodeIndex);

    /// Ищет метод вызываемого объекта. Объект разрешается как зарегистрированный в фабрике класс
    SR_NODISCARD const SR_UTILS_NS::Reflection::Method* FindFluxMethod(const SR_FLUX_NS::FluxCallable& callable);

    /// Короткое представление значения для заголовка узла и списка переменных
    SR_NODISCARD SR_UTILS_NS::String GetFluxValuePreview(const SR_UTILS_NS::Reflection::Value& value);

    SR_NODISCARD SR_UTILS_NS::StringAtom GetFluxValueTypeName(const SR_UTILS_NS::Reflection::Value& value);

    /// Список типов значений, доступных для констант и переменных графа
    SR_NODISCARD const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& GetFluxValueTypeNames();

    SR_NODISCARD SR_UTILS_NS::Reflection::Value CreateFluxValue(SR_UTILS_NS::StringAtom typeName);
}

#endif //SR_ENGINE_CORE_GUI_FLUX_NODE_LAYOUT_H
