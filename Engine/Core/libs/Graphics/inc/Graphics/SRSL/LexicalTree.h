//
// Created by Monika on 22.01.2023.
//

#ifndef SRENGINE_SRSL_LEXICALTREE_H
#define SRENGINE_SRSL_LEXICALTREE_H

#include <Graphics/SRSL/LexerUtils.h>

namespace SR_SRSL_NS {
    /// минимальная лексическая единица
    struct SRSLLexicalUnit : public SR_UTILS_NS::NonCopyable {
        SR_NODISCARD virtual std::string ToString() const { return std::string(); }
    };

    /// ----------------------------------------------------------------------------------------------------------------

    enum class SRSLExprType {
        Unknown, Value, Operation, Call, Array
    };

    /// выражение может быть:
    ///     значнием, тогда args будет пуст а в token будет лежать значние
    ///     операцией, тогда в args будет 2 значения или выражения а в token операция
    ///     вызовом функции, тогда в args будут ее аргументы, а в token имя функции
    ///     массивом, token будет пуст, а в args будут лежать значения-выражения
    struct SRSLExpr : public SRSLLexicalUnit {
        SRSLExpr() = default;

        ~SRSLExpr() override {
            for (auto&& pExpr : args) {
                delete pExpr;
            }
        }

        SRSLExpr(SRSLExpr&& other) noexcept
            : token(SR_UTILS_NS::Exchange(other.token, { }))
            , args(SR_UTILS_NS::Exchange(other.args, { }))
            , type(SR_UTILS_NS::Exchange(other.type, { }))
        { }

        SR_NODISCARD std::string ToString() const override;

        std::string token;
        std::vector<SRSLExpr*> args;
        SRSLExprType type = SRSLExprType::Unknown;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLInclude : public SRSLLexicalUnit {
        std::string path;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLDecorator : public SRSLLexicalUnit {
        SRSLDecorator() = default;

        ~SRSLDecorator() override {
            for (auto&& pExpr : args) {
                delete pExpr;
            }
        }

        SRSLDecorator(SRSLDecorator&& other) noexcept
            : name(SR_UTILS_NS::Exchange(other.name, { }))
            , args(SR_UTILS_NS::Exchange(other.args, { }))
        { }

        SR_NODISCARD std::string ToString() const override;

        std::string name;
        std::vector<SRSLExpr*> args;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLDecorators : public SRSLLexicalUnit {
        SRSLDecorators() = default;

        SRSLDecorators(SRSLDecorators&& other) noexcept
            : decorators(SR_UTILS_NS::Exchange(other.decorators, { }))
        { }

        SRSLDecorators& operator=(SRSLDecorators&& other) noexcept {
            decorators = SR_UTILS_NS::Exchange(other.decorators, { });
            return *this;
        }

        SR_NODISCARD std::string ToString() const override;

        std::vector<SRSLDecorator> decorators;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLVariable : public SRSLLexicalUnit {
        SRSLDecorators decorators;
        std::string type;
        std::string name;
        std::optional<SRSLExpr> value;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLFunction : public SRSLLexicalUnit {
        ~SRSLFunction() override {
            for (auto&& pUnit : lexicalTree) {
                delete pUnit;
            }
        }

        SRSLDecorators decorators;

        std::string type;
        std::string name;
        std::vector<SRSLVariable> args;

        std::vector<SRSLLexicalUnit*> lexicalTree;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLIfStatement : public SRSLLexicalUnit {
        ~SRSLIfStatement() override {
            for (auto&& pUnit : lexicalTree) {
                delete pUnit;
            }
            if (elseStatement.has_value()) {
                delete elseStatement.value();
            }
        }

        std::optional<SRSLExpr> expr;
        std::vector<SRSLLexicalUnit*> lexicalTree;
        std::optional<SRSLIfStatement*> elseStatement;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLLexicalTree : public SR_UTILS_NS::NonCopyable {
        SRSLLexicalTree() = default;

        ~SRSLLexicalTree() override {
            for (auto&& pUnit : lexicalTree) {
                delete pUnit;
            }
        }

        SRSLLexicalTree(SRSLLexicalTree&& other) noexcept
            : lexicalTree(SR_UTILS_NS::Exchange(other.lexicalTree, { }))
        { }

        SRSLLexicalTree& operator=(SRSLLexicalTree&& other) noexcept {
            lexicalTree = SR_UTILS_NS::Exchange(other.lexicalTree, { });
            return *this;
        }

        SR_NODISCARD std::string ToString() const;

        std::vector<SRSLLexicalUnit*> lexicalTree;
    };

}

#endif //SRENGINE_SRSL_LEXICALTREE_H
