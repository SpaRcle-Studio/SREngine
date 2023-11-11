//
// Created by Monika on 06.02.2023.
//

#ifndef SRENGINE_SRSL_EVALUATOR_H
#define SRENGINE_SRSL_EVALUATOR_H

#include <Graphics/SRSL/LexicalTree.h>
#include <Graphics/SRSL/ShaderType.h>

namespace SR_SRSL_NS {
    class SRSLEvaluator : public SR_UTILS_NS::Singleton<SRSLEvaluator> {
        SR_REGISTER_SINGLETON(SRSLEvaluator)
    public:
        SR_NODISCARD double_t Evaluate(const std::string& code);
        SR_NODISCARD double_t Evaluate(const SRSLExpr* pExpr);

    private:
        SR_NODISCARD double_t ApplyOperator(const std::string& op, double_t left, double_t right) const;

    };
}

#endif //SRENGINE_SRSL_EVALUATOR_H
