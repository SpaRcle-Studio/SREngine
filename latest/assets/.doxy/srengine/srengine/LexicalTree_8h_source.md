

# File LexicalTree.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**LexicalTree.h**](LexicalTree_8h.md)

[Go to the documentation of this file](LexicalTree_8h.md)


```C++
//
// Created by Monika on 22.01.2023.
//

#ifndef SR_ENGINE_SRSL_LEXICALTREE_H
#define SR_ENGINE_SRSL_LEXICALTREE_H

#include <Graphics/SRSL/LexerUtils.h>

namespace SR_SRSL_NS {
    class SRSLLexicalUnit : public SR_UTILS_NS::NonCopyable {
    public:
        SR_NODISCARD virtual std::string ToString(uint32_t deep) const { return std::string(); }

    };

    class SRSLLexicalTree;


    class SRSLExpr : public SRSLLexicalUnit {
    public:
        SRSLExpr() = default;

        static SRSLExpr* CreateStringExpression(std::string token) {
            auto&& pExpr = new SRSLExpr(std::move(token));
            pExpr->isString = true;
            return pExpr;
        }

        explicit SRSLExpr(std::string&& token)
            : token(SR_UTILS_NS::Exchange(token, { }))
        {
            SRAssert(this->token != "(" && this->token != ")");
            SRAssert(this->token != "[" && this->token != "]");
            SRAssert(this->token != "}");

            if (this->token == "{") {
                isList = true;
            }
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
            SRAssert(pAExpr);
            SRAssert(this->token != ")" && this->token != "(");
            SRAssert(this->token != "]");

            if (this->token == "[") {
                isArray = true;
            }

            args.emplace_back(pAExpr);

            if (pBExpr) {
                args.emplace_back(pBExpr);
            }
            else {
                SRAssert(isArray);
                SR_NOOP;
            }
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
            , isArray(SR_UTILS_NS::Exchange(other.isArray, { }))
        { }

        SR_NODISCARD std::string ToString(uint32_t deep) const override;

        std::string GetAsName();

        std::string token;
        std::vector<SRSLExpr*> args;

        bool isCall = false;       
        bool isArray = false;      
        bool isList = false;       
        bool isString = false;     

    };


    class SRSLDecorator : public SRSLLexicalUnit {
    public:
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

        SR_NODISCARD std::string ToString(uint32_t deep) const override;

        std::string name;
        std::vector<SRSLExpr*> args;
    };


    class SRSLDecorators : public SRSLLexicalUnit {
    public:
        SRSLDecorators() = default;

        SRSLDecorators(SRSLDecorators&& other) noexcept
            : decorators(SR_UTILS_NS::Exchange(other.decorators, { }))
        { }

        SRSLDecorators& operator=(SRSLDecorators&& other) noexcept {
            decorators = SR_UTILS_NS::Exchange(other.decorators, { });
            return *this;
        }

        SR_NODISCARD std::string ToString(uint32_t deep) const override;
        SR_NODISCARD SRSLDecorator* Find(const std::string& name);

        std::vector<SRSLDecorator> decorators;
    };


    class SRSLVariable : public SRSLLexicalUnit {
    public:
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

        SR_NODISCARD std::string ToString(uint32_t deep) const override;

        SR_NODISCARD std::string GetType() const;
        SR_NODISCARD std::string GetName() const;

        SRSLDecorators* pDecorators = nullptr;
        SRSLExpr* pType = nullptr;
        SRSLExpr* pName = nullptr;
        SRSLExpr* pExpr = nullptr;
    };


    class SRSLReturn : public SRSLLexicalUnit {
    public:
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

        SRSLExpr* pExpr = nullptr;
    };


    class SRSLFunction : public SRSLLexicalUnit {
    public:
        ~SRSLFunction() override;

        SR_NODISCARD std::string ToString(uint32_t deep) const override;
        SR_NODISCARD std::string GetName() const { return pName->token; }

        SRSLDecorators* pDecorators = nullptr;
        SRSLExpr* pType = nullptr;
        SRSLExpr* pName = nullptr;

        std::vector<SRSLVariable*> args;

        SRSLLexicalTree* pLexicalTree = nullptr;
    };


    class SRSLIfStatement : public SRSLLexicalUnit {
    public:
        SRSLIfStatement() = default;
        explicit SRSLIfStatement(bool isElse);

        ~SRSLIfStatement() override;

        SRSLExpr* pExpr = nullptr;
        SRSLLexicalTree* pLexicalTree = nullptr;
        bool isElse = false;
    };


    class SRSLForStatement : public SRSLLexicalUnit {
    public:
        SRSLForStatement() = default;
        ~SRSLForStatement() override;

        SRSLVariable* pVar = nullptr;
        SRSLExpr* pCondition = nullptr;
        SRSLExpr* pExpr = nullptr;
        SRSLLexicalTree* pLexicalTree = nullptr;
    };

    class SRSLStructureStatement : public SRSLLexicalUnit {
    public:
        SRSLStructureStatement() = default;
        ~SRSLStructureStatement() override;

        SRSLExpr* pName = nullptr;
        SRSLLexicalTree* pLexicalTree = nullptr;

        bool HasDynamicArray() const;
    };


    class SRSLLexicalTree : public SRSLLexicalUnit {
    public:
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

        SR_NODISCARD std::string ToString(uint32_t deep) const override;

        SR_NODISCARD SRSLFunction* FindFunction(const std::string& name) const;
        SR_NODISCARD SRSLExpr* AsExpression() const;

        std::vector<SRSLLexicalUnit*> lexicalTree;
    };


    class SRSLAnalyzedTree : public SR_UTILS_NS::NonCopyable {
    public:
        using Ptr = std::shared_ptr<SRSLAnalyzedTree>;

        SRSLAnalyzedTree() = default;

        ~SRSLAnalyzedTree() override {
            SR_SAFE_DELETE_PTR(pLexicalTree);
        }

        SRSLLexicalTree* pLexicalTree = nullptr;
    };
}

#endif //SR_ENGINE_SRSL_LEXICALTREE_H
```


