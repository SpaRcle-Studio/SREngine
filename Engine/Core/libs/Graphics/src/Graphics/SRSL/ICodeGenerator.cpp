//
// Created by Monika on 30.01.2023.
//

#include <Graphics/SRSL/ICodeGenerator.h>

namespace SR_SRSL_NS {
    std::pair<std::string, SRSLResult> ISRSLCodeGenerator::ToString(SRSLAnalyzedTree::Ptr&& analyzedTree) {
        SR_GLOBAL_LOCK

        Clear();

        m_analyzedTree = std::move(analyzedTree);

        auto&& stages = GenerateStages();

        std::string code;

        for (auto&& stage : stages) {
            code += "Stage[" + SR_UTILS_NS::EnumReflector::ToString(stage.stage) + "] {\n" + stage.code + "\n}";
        }

        return std::make_pair(std::move(code), SR_UTILS_NS::Exchange(m_result, { }));
    }

    void ISRSLCodeGenerator::Clear() {
        m_result = SRSLResult();
    }
}
