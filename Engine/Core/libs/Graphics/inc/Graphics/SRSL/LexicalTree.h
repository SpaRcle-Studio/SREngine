//
// Created by Monika on 22.01.2023.
//

#ifndef SRENGINE_SRSL_LEXICALTREE_H
#define SRENGINE_SRSL_LEXICALTREE_H

#include <Graphics/SRSL/LexerUtils.h>

#include <utility>

namespace SR_SRSL_NS {
    /// минимальная лексическая единица
    struct SRSLLexicalUnit : public SR_UTILS_NS::NonCopyable {
        SR_NODISCARD virtual std::string ToString() const { return std::string(); }
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLExpr : public SRSLLexicalUnit {
        SRSLExpr() = default;

        explicit SRSLExpr(std::string&& token)
            : token(SR_UTILS_NS::Exchange(token, { }))
        {
            SRAssert(this->token != ")" && this->token != "(");
            SRAssert(this->token != "[" && this->token != "]");
        }

        explicit SRSLExpr(std::string&& token, SRSLExpr* pAExpr)
            : token(SR_UTILS_NS::Exchange(token, { }))
        {
            SRAssert(pAExpr);
            SRAssert(this->token != ")" && this->token != "(");
            SRAssert(this->token != "[" && this->token != "]");
            args.emplace_back(pAExpr);
        }

        explicit SRSLExpr(std::string&& token, SRSLExpr* pAExpr, SRSLExpr* pBExpr)
            : token(SR_UTILS_NS::Exchange(token, { }))
        {
            SRAssert(pAExpr && pBExpr);
            SRAssert(this->token != ")" && this->token != "(");
            SRAssert(this->token != "]");

            if (this->token == "[") {
                isArray = true;
            }

            args.emplace_back(pAExpr);
            args.emplace_back(pBExpr);
        }

        explicit SRSLExpr(SRSLExpr* pAExpr, SRSLExpr* pBExpr) {
            SRAssert(pAExpr && pBExpr);
            args.emplace_back(pAExpr);
            args.emplace_back(pBExpr);
        }

        ~SRSLExpr() override {
            for (auto&& pExpr : args) {
                delete pExpr;
            }
        }

        SRSLExpr(SRSLExpr&& other) noexcept
            : token(SR_UTILS_NS::Exchange(other.token, { }))
            , args(SR_UTILS_NS::Exchange(other.args, { }))
            , isCall(SR_UTILS_NS::Exchange(other.isCall, { }))
            , isAccess(SR_UTILS_NS::Exchange(other.isAccess, { }))
            , isArray(SR_UTILS_NS::Exchange(other.isArray, { }))
        { }

        SR_NODISCARD std::string ToString() const override;

        std::string token;
        std::vector<SRSLExpr*> args;

        bool isCall = false;       /// function(arg1, arg2, arg3)
        bool isAccess = false;     /// variable.field
        bool isArray = false;      /// variable[expression]
        bool isAssignment = false; /// variable = expression

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
        SRSLVariable() = default;

        SRSLVariable(SRSLVariable&& other) noexcept
            : pDecorators(SR_UTILS_NS::Exchange(other.pDecorators, { }))
            , pType(SR_UTILS_NS::Exchange(other.pType, { }))
            , pName(SR_UTILS_NS::Exchange(other.pName, { }))
            , pExpr(SR_UTILS_NS::Exchange(other.pExpr, { }))
        { }

        SRSLVariable& operator=(SRSLVariable&& other) noexcept {
            pDecorators = SR_UTILS_NS::Exchange(other.pDecorators, { });
            pType = SR_UTILS_NS::Exchange(other.pType, { });
            pName = SR_UTILS_NS::Exchange(other.pName, { });
            pExpr = SR_UTILS_NS::Exchange(other.pExpr, { });
            return *this;
        }

        ~SRSLVariable() override {
            SR_SAFE_DELETE_PTR(pDecorators);
            SR_SAFE_DELETE_PTR(pExpr);
            SR_SAFE_DELETE_PTR(pType);
            SR_SAFE_DELETE_PTR(pName);
        }

        SR_NODISCARD std::string ToString() const override;

        SRSLDecorators* pDecorators = nullptr;
        SRSLExpr* pType = nullptr;
        SRSLExpr* pName = nullptr;
        SRSLExpr* pExpr = nullptr;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLReturn : public SRSLLexicalUnit {
        explicit SRSLReturn(SRSLExpr* pExpr)
            : pExpr(pExpr)
        { }

        ~SRSLReturn() override {
            delete pExpr;
        }

        SRSLReturn(SRSLReturn&& other) noexcept
            : pExpr(SR_UTILS_NS::Exchange(other.pExpr, { }))
        { }

        SRSLReturn& operator=(SRSLReturn&& other) noexcept {
            pExpr = SR_UTILS_NS::Exchange(other.pExpr, { });
            return *this;
        }

        SRSLExpr* pExpr;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    struct SRSLFunction : public SRSLLexicalUnit {
        ~SRSLFunction() override {
            SR_SAFE_DELETE_PTR(pDecorators);
            SR_SAFE_DELETE_PTR(pType);
            SR_SAFE_DELETE_PTR(pName);

            for (auto&& pArg : args) {
                delete pArg;
            }

            for (auto&& pUnit : lexicalTree) {
                delete pUnit;
            }
        }

        SR_NODISCARD std::string ToString() const override;

        SRSLDecorators* pDecorators = nullptr;
        SRSLExpr* pType = nullptr;
        SRSLExpr* pName = nullptr;

        std::vector<SRSLVariable*> args;

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
