//
// Created by Monika on 06.02.2023.
//

#include <Graphics/SRSL/Evaluator.h>
#include <Graphics/SRSL/Lexer.h>
#include <Graphics/SRSL/LexicalAnalyzer.h>
#include <Graphics/SRSL/MathExpression.h>

namespace SR_SRSL_NS {
    double_t SRSLEvaluator::Evaluate(const std::string& code) {
        SR_GLOBAL_LOCK

        auto&& lexems = SRSLLexer::Instance().ParseString(code, 0);
        auto&& [pTree, result] = SRSLLexicalAnalyzer::Instance().Analyze(std::move(lexems));

        if (result.HasErrors()) {
            SR_ERROR("SSRSLEvaluator::Evaluate() : failed to parse expression!");
            return 0;
        }

        if (pTree->pLexicalTree->lexicalTree.empty()) {
            SR_ERROR("SRSLEvaluator::Evaluate() : expression not found!");
            return 0;
        }

        auto&& pExpr = dynamic_cast<SRSLExpr*>(pTree->pLexicalTree->lexicalTree.back());
        if (!pExpr) {
            SR_ERROR("SRSLEvaluator::Evaluate() : expression not found!");
            return 0;
        }

        return Evaluate(pExpr);
    }

    double_t SRSLEvaluator::Evaluate(const SRSLExpr* pExpr) {
        SR_GLOBAL_LOCK

        if (pExpr->args.empty()) {
            if (SR_MATH_NS::IsNumber(pExpr->token)) {
                return SR_UTILS_NS::LexicalCast<double_t>(pExpr->token);
            }
            else {
                SRHalt("It is not a number!");
                return 0.f;
            }
        }
        else if (pExpr->args.size() == 2) {
            return ApplyOperator(pExpr->token, Evaluate(pExpr->args[0]), Evaluate(pExpr->args[1]));
        }

        SRHalt("Invalid expression!");

        return 0.0;
    }

    double_t SRSLEvaluator::ApplyOperator(const std::string& op, double_t left, double_t right) const {
        if (op == "+") {
            return left + right;
        }
        else if (op == "-") {
            return left - right;
        }
        else if (op == "*") {
            return left * right;
        }
        else if (op == "/") {
            return left / right;
        }

        SRHalt("Invalid operator!");

        return 0.f;
    }
}