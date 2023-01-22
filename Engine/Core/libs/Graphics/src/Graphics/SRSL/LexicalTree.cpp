//
// Created by Monika on 22.01.2023.
//

#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    std::string SRSLExpr::ToString() const {
        switch (type) {
            case SRSLExprType::Value:
                return token;
            case SRSLExprType::Operation: {
                if (args.size() == 1) {
                    return token + args[0]->ToString();
                }
                else if (args.size() == 2) {
                    return args[0]->ToString() + token + args[1]->ToString();
                }
                return std::string();
            }
            case SRSLExprType::Call:
                break;
            case SRSLExprType::Array:
                break;
            default:
                break;
        }
        return std::string();
    }

    std::string SRSLDecorator::ToString() const {
        std::string code = "[" + name;

        if (!args.empty()) {
            code += "(";

            for (uint32_t i = 0; i < args.size(); ++i) {
                code += args[i]->ToString();
                if (i + 1 < args.size()) {
                    code += ", ";
                }
            }

            code += ")";
        }

        return code + "]";
    }

    std::string SRSLDecorators::ToString() const {
        std::string code = "[";

        for (uint32_t i = 0; i < decorators.size(); ++i) {
            code += decorators[i].ToString();

            if (i + 1 < decorators.size()) {
                code += ", ";
            }
        }

        return code + "]";
    }

    std::string SRSLLexicalTree::ToString() const {
        std::string code;

        for (auto&& pUnit : lexicalTree) {
            code += pUnit->ToString() + "\n";
        }

        return code;
    }
}