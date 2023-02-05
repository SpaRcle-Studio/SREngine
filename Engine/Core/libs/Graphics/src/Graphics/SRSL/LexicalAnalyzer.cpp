//
// Created by Monika on 22.01.2023.
//

#include <Graphics/SRSL/LexicalAnalyzer.h>

namespace SR_SRSL_NS {
    std::pair<SRSLAnalyzedTree::Ptr, SRSLResult> SRSLLexicalAnalyzer::Analyze(std::vector<Lexem>&& lexems) {
        SR_GLOBAL_LOCK

        Clear();

        m_lexems = SR_UTILS_NS::Exchange(lexems, { });

        ProcessMain();

        if (m_lexicalTree.size() != 1) {
            return std::make_pair(nullptr, SR_SRSL_NS::SRSLResult(SRSLReturnCode::InvalidLexicalTree));
        }

        auto&& pAnalyzedTree = std::make_shared<SRSLAnalyzedTree>();

        pAnalyzedTree->pLexicalTree = SR_UTILS_NS::Exchange(*m_lexicalTree.begin(), { });

        return std::make_pair(std::move(pAnalyzedTree), SR_UTILS_NS::Exchange(m_result, { }));
    }

    void SRSLLexicalAnalyzer::Clear() {
        for (auto&& pLexicalTree : m_lexicalTree) {
            delete pLexicalTree;
        }
        m_lexicalTree.clear();

        SR_SAFE_DELETE_PTR(m_decorators);
        SR_SAFE_DELETE_PTR(m_expr);

        m_lexems.clear();
        m_currentLexem = 0;

        m_states.clear();
        m_result = SRSLResult(SRSLReturnCode::Success);
    }

    const Lexem *SRSLLexicalAnalyzer::GetLexem(int64_t offset) const {
        if (m_currentLexem + offset < static_cast<int64_t>(m_lexems.size())) {
            return &m_lexems.at(m_currentLexem + offset);
        }

        return nullptr;
    }

    bool SRSLLexicalAnalyzer::InBounds() const noexcept {
        return m_currentLexem < m_lexems.size();
    }

    void SRSLLexicalAnalyzer::ProcessMain() {
        m_lexicalTree.emplace_back(new SRSLLexicalTree());

        while (InBounds() && m_result.code == SRSLReturnCode::Success) {
            switch (m_lexems[m_currentLexem].kind) {
                case LexemKind::OpeningSquareBracket:
                case LexemKind::ClosingSquareBracket:
                case LexemKind::OpeningAngleBracket:
                case LexemKind::ClosingAngleBracket:
                case LexemKind::OpeningCurlyBracket:
                case LexemKind::ClosingCurlyBracket:
                case LexemKind::OpeningBracket:
                case LexemKind::ClosingBracket: {
                    ProcessBracket();
                    if (IsHasErrors()) {
                        return;
                    }
                    break;
                }

                case LexemKind::Identifier: {
                    if (GetCurrentLexem()->value == "else") {
                        if (auto&& pNext = GetLexem(1); pNext->value == "if") {
                            ++m_currentLexem;
                        }
                        ++m_currentLexem;
                        m_lexicalTree.back()->lexicalTree.emplace_back(new SRSLIfStatement(true));
                        m_states.emplace_back(LXAState::IfStatement);
                        break;
                    }

                    if (GetCurrentLexem()->value == "if") {
                        ++m_currentLexem;
                        m_lexicalTree.back()->lexicalTree.emplace_back(new SRSLIfStatement());
                        m_states.emplace_back(LXAState::IfStatement);
                        break;
                    }

                    if (auto&& pUnit = TryProcessIdentifier()) {
                        if (dynamic_cast<SRSLFunction*>(pUnit)) {
                            m_states.emplace_back(LXAState::Function);
                            m_lexicalTree.back()->lexicalTree.emplace_back(pUnit);
                        }
                        else if (!m_states.empty() && m_states.back() == LXAState::FunctionArgs) {
                            auto&& pFunction = dynamic_cast<SRSLFunction*>(m_lexicalTree.back()->lexicalTree.back());
                            auto&& pVar = dynamic_cast<SRSLVariable*>(pUnit);
                            SRAssert(pFunction && pVar);
                            pFunction->args.emplace_back(pVar);
                        }
                        else {
                            m_lexicalTree.back()->lexicalTree.emplace_back(pUnit);
                        }
                        break;
                    }
                    if (IsHasErrors()) {
                        return;
                    }

                    SR_FALLTHROUGH;
                }
                case LexemKind::Plus:
                case LexemKind::Minus:
                case LexemKind::Tilda:
                case LexemKind::Integer:
                case LexemKind::Negation: {
                    ProcessExpression(false, true);
                    if (IsHasErrors()) {
                        return;
                    }
                    m_lexicalTree.back()->lexicalTree.emplace_back(SR_UTILS_NS::Exchange(m_expr, nullptr));
                    break;
                }

                case LexemKind::Assign:
                case LexemKind::Semicolon:
                case LexemKind::Dot:
                case LexemKind::Comma:
                case LexemKind::And:
                case LexemKind::Or:
                case LexemKind::Macro:
                    ++m_currentLexem;
                    break;
                default:
                    m_result = SRSLResult(SRSLReturnCode::UnknownLexem, GetLexem(0)->offset);
                    break;
            }
        }
    }

    void SRSLLexicalAnalyzer::ProcessBracket() {
        switch (m_lexems[m_currentLexem].kind)
        {
            case LexemKind::OpeningBracket: {
                if (!m_states.empty() && m_states.back() == LXAState::Function) {
                    ++m_currentLexem;
                    m_states.back() = LXAState::FunctionArgs;
                    return;
                }

                ProcessExpression();

                if (IsHasErrors()) {
                    return;
                }

                if (!m_states.empty() && m_states.back() == LXAState::IfStatement) {
                    auto&& pIfStatement = dynamic_cast<SRSLIfStatement*>(m_lexicalTree.back()->lexicalTree.back());
                    if (!pIfStatement) {
                        m_result = SRSLResult(SRSLReturnCode::InvalidIfStatement);
                        return;
                    }
                    pIfStatement->pExpr = SR_UTILS_NS::Exchange(m_expr, nullptr);
                }
                else {
                    m_lexicalTree.back()->lexicalTree.emplace_back(SR_UTILS_NS::Exchange(m_expr, nullptr));
                }

                return;
            }
            case LexemKind::ClosingBracket: {
                if (!m_states.empty() && m_states.back() == LXAState::FunctionArgs) {
                    m_states.back() = LXAState::Function;
                    ++m_currentLexem;
                    return;
                }

                break;
            }
            case LexemKind::OpeningSquareBracket: {
                ProcessDecorators();
                return;
            }
            case LexemKind::OpeningCurlyBracket: {
                m_lexicalTree.emplace_back(new SRSLLexicalTree());

                if (!m_states.empty() && m_states.back() == LXAState::Function) {
                    m_states.back() = LXAState::FunctionBody;
                    ++m_currentLexem;
                    return;
                }
                else if (!m_states.empty() && m_states.back() == LXAState::IfStatement) {
                    m_states.back() = LXAState::IfStatementBody;
                    ++m_currentLexem;
                    return;
                }

                return;
            }
            case LexemKind::ClosingCurlyBracket: {
                if (m_lexicalTree.size() <= 1) {
                    m_result = SRSLResult(SRSLReturnCode::InvalidScope, m_lexems[m_currentLexem].offset);
                    return;
                }

                SRSLLexicalTree* pLexicalTree = m_lexicalTree.back();
                m_lexicalTree.pop_back();

                if (!m_states.empty() && m_states.back() == LXAState::FunctionBody) {
                    m_states.pop_back();

                    auto&& pFunction = dynamic_cast<SRSLFunction*>(m_lexicalTree.back()->lexicalTree.back());
                    pFunction->pLexicalTree = std::move(pLexicalTree);
                }
                else if (!m_states.empty() && m_states.back() == LXAState::IfStatementBody) {
                    m_states.pop_back();
                    auto&& pIfStatement = dynamic_cast<SRSLIfStatement*>(m_lexicalTree.back()->lexicalTree.back());
                    pIfStatement->pLexicalTree = std::move(pLexicalTree);
                }
                else {
                    m_lexicalTree.back()->lexicalTree.emplace_back(pLexicalTree);
                }

                ++m_currentLexem;

                return;
            }
            default:
                break;
        }

        m_result = SRSLResult(SRSLReturnCode::UnexceptedLexem, m_lexems[m_currentLexem].offset);
    }

    const Lexem* SRSLLexicalAnalyzer::GetCurrentLexem() const {
        return GetLexem(0);
    }

    void SRSLLexicalAnalyzer::ProcessExpression(bool isFunctionName, bool isSimpleExpr) {
        SRAssert(!m_expr);
        SR_SAFE_DELETE_PTR(m_expr);

        std::vector<Lexem> exprLexems;
        uint32_t deep = 0;
        bool allowIdentifier = true;

    retry:
        const LexemKind lexemKind = InBounds() ? m_lexems[m_currentLexem].kind : LexemKind::Unknown;
        switch (lexemKind)
        {
            case LexemKind::OpeningCurlyBracket:
                break;
            case LexemKind::OpeningBracket:
                if (isFunctionName && deep == 0) {
                    break;
                }
                SR_FALLTHROUGH;
            case LexemKind::OpeningSquareBracket:
                ++deep;
                SR_FALLTHROUGH;
            default: {
                switch (lexemKind) {
                    case LexemKind::Unknown:
                    case LexemKind::Semicolon:
                    case LexemKind::Macro:
                        break;

                    case LexemKind::Assign:
                        if (isSimpleExpr) {
                            goto gotoDefault;
                        }
                        SR_FALLTHROUGH;
                    case LexemKind::Comma:
                        if (deep == 0) {
                            break;
                        }
                        SR_FALLTHROUGH;
                    default: {
                    gotoDefault:
                        if (lexemKind == LexemKind::Identifier) {
                            if (!allowIdentifier) {
                                break;
                            }
                        }
                        else {
                            allowIdentifier = true;
                        }

                        exprLexems.emplace_back(m_lexems[m_currentLexem]);
                        ++m_currentLexem;

                        goto retry;
                    }
                }

                break;
            }
            case LexemKind::ClosingBracket:
            case LexemKind::ClosingSquareBracket:
                allowIdentifier = false;
                if (deep == 0) {
                    break;
                }
                exprLexems.emplace_back(m_lexems[m_currentLexem]);
                ++m_currentLexem;
                --deep;
                goto retry;
        }

        if (deep != 0) {
            m_result = SRSLResult(SRSLReturnCode::IncompleteExpression, InBounds() ? m_lexems[m_currentLexem].offset : SR_UINT64_MAX);
            return;
        }

        auto&& [pExpr, result] = SR_SRSL_NS::SRSLMathExpression::Instance().Analyze(std::move(exprLexems));
        m_expr = pExpr;
        m_result = std::move(result);
    }

    void SRSLLexicalAnalyzer::ProcessDecorators() {
        SR_SAFE_DELETE_PTR(m_decorators);
        m_decorators = new SRSLDecorators();

    retry:
        switch (m_lexems[m_currentLexem].kind)
        {
            case LexemKind::OpeningSquareBracket: {
                if (!m_states.empty() && m_states.back() == LXAState::Decorators) {
                    m_states.emplace_back(LXAState::Decorator);
                    m_decorators->decorators.emplace_back(std::move(SRSLDecorator()));
                    ++m_currentLexem;
                    goto retry;
                }
                else {
                    m_states.emplace_back(LXAState::Decorators);
                    ++m_currentLexem;
                    goto retry;
                }
            }
            case LexemKind::Identifier: {
                if (!m_states.empty() && m_states.back() == LXAState::DecoratorArgs) {
                    ProcessExpression();

                    if (IsHasErrors()) {
                        return;
                    }

                    m_decorators->decorators.back().args.emplace_back(SR_UTILS_NS::Exchange(m_expr, nullptr));

                    goto retry;
                }
                else if (!m_states.empty() && m_states.back() == LXAState::Decorator) {
                    m_decorators->decorators.back().name = GetCurrentLexem()->value;
                    ++m_currentLexem;
                    goto retry;
                }
                break;
            }
            case LexemKind::ClosingSquareBracket: {
                if (!m_states.empty() && m_states.back() == LXAState::Decorator) {
                    m_states.pop_back();
                    ++m_currentLexem;
                    goto retry;
                }
                else if (!m_states.empty() && m_states.back() == LXAState::Decorators) {
                    m_states.pop_back();
                    ++m_currentLexem;
                    return;
                }
                break;
            }
            case LexemKind::Comma: {
                if (!m_states.empty() && m_states.back() == LXAState::Decorators) {
                    ++m_currentLexem;
                    goto retry;
                }
                else if (!m_states.empty() && m_states.back() == LXAState::DecoratorArgs) {
                    ++m_currentLexem;

                    ProcessExpression();

                    if (IsHasErrors()) {
                        return;
                    }

                    m_decorators->decorators.back().args.emplace_back(SR_UTILS_NS::Exchange(m_expr, nullptr));

                    goto retry;
                }
                break;
            }
            case LexemKind::OpeningBracket: {
                if (!m_states.empty() && m_states.back() == LXAState::DecoratorArgs) {
                    ++m_currentLexem;

                    ProcessExpression();

                    if (IsHasErrors()) {
                        return;
                    }

                    m_decorators->decorators.back().args.emplace_back(SR_UTILS_NS::Exchange(m_expr, nullptr));

                    goto retry;
                }
                else if (!m_states.empty() && m_states.back() == LXAState::Decorator) {
                    m_states.back() = LXAState::DecoratorArgs;
                    goto retry;
                }
                break;
            }
            case LexemKind::ClosingBracket: {
                if (!m_states.empty() && m_states.back() == LXAState::DecoratorArgs) {
                    m_states.back() = LXAState::Decorator;
                    ++m_currentLexem;
                    goto retry;
                }
                break;
            }
            case LexemKind::Plus:
            case LexemKind::Minus:
            case LexemKind::Negation:
            case LexemKind::Integer:
                if (!m_states.empty() && m_states.back() == LXAState::DecoratorArgs) {
                    ProcessExpression();

                    if (IsHasErrors()) {
                        return;
                    }

                    m_decorators->decorators.back().args.emplace_back(SR_UTILS_NS::Exchange(m_expr, nullptr));

                    goto retry;
                }
                break;
            default:
                break;
        }

        m_result = SRSLResult(SRSLReturnCode::UnexceptedLexem, m_lexems[m_currentLexem].offset);
    }

    bool SRSLLexicalAnalyzer::IsHasErrors() const noexcept {
        return m_result.code != SRSLReturnCode::Success;
    }

    SRSLLexicalUnit* SRSLLexicalAnalyzer::TryProcessIdentifier() {
        auto&& pCurrent = GetCurrentLexem();

        const uint64_t currentLexem = m_currentLexem;

        if (pCurrent->value == "return") {
            ++m_currentLexem;
            ProcessExpression();
            if (IsHasErrors()) {
                return nullptr;
            }
            return new SRSLReturn(SR_UTILS_NS::Exchange(m_expr, nullptr));
        }

        if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::OpeningSquareBracket) {
            ProcessExpression(true);
        }
        else {
            m_expr = new SRSLExpr(std::string(pCurrent->value));
            ++m_currentLexem;
        }

        if (pCurrent = GetCurrentLexem(); pCurrent && pCurrent->kind == LexemKind::Identifier) {
            auto&& pTypeExpr = SR_UTILS_NS::Exchange(m_expr, nullptr);
            ProcessExpression(true);
            auto&& pNameExpr = SR_UTILS_NS::Exchange(m_expr, nullptr);

            if (IsHasErrors()) {
                SR_SAFE_DELETE_PTR(pTypeExpr);
                SR_SAFE_DELETE_PTR(pNameExpr);
                return nullptr;
            }

            /// переменная имеющая значение: "type[...] name[...] = value;"
            if (pCurrent = GetCurrentLexem(); pCurrent && pCurrent->kind == LexemKind::Assign) {
                auto&& pVariable = new SRSLVariable();

                pVariable->pDecorators = SR_UTILS_NS::Exchange(m_decorators, nullptr);
                pVariable->pType = SR_UTILS_NS::Exchange(pTypeExpr, nullptr);
                pVariable->pName = SR_UTILS_NS::Exchange(pNameExpr, nullptr);

                ++m_currentLexem;

                ProcessExpression();

                pVariable->pExpr = SR_UTILS_NS::Exchange(m_expr, nullptr);

                return std::move(pVariable);
            }
            /// переменная имеющая значение: "type[...] name[...] = value;"
            else if (pCurrent && pCurrent->kind == LexemKind::OpeningBracket) {
                auto&& pFunction = new SRSLFunction();

                pFunction->pDecorators = SR_UTILS_NS::Exchange(m_decorators, nullptr);
                pFunction->pType = SR_UTILS_NS::Exchange(pTypeExpr, nullptr);
                pFunction->pName = SR_UTILS_NS::Exchange(pNameExpr, nullptr);

                return std::move(pFunction);
            }
            /// обычная переменная типа "type[...] name[...];"
            else if (pTypeExpr && pNameExpr) {
                auto&& pVariable = new SRSLVariable();

                pVariable->pType = SR_UTILS_NS::Exchange(pTypeExpr, nullptr);
                pVariable->pName = SR_UTILS_NS::Exchange(pNameExpr, nullptr);
                pVariable->pDecorators = SR_UTILS_NS::Exchange(m_decorators, nullptr);

                return std::move(pVariable);
            }

            SR_SAFE_DELETE_PTR(m_expr);
            SR_SAFE_DELETE_PTR(pTypeExpr);
            SR_SAFE_DELETE_PTR(pNameExpr);

            m_result = SRSLResult(SRSLReturnCode::UnexceptedLexem, InBounds() ? m_lexems[m_currentLexem].offset : SR_UINT64_MAX);

            return nullptr;
        }

        SR_SAFE_DELETE_PTR(m_expr);
        m_currentLexem = currentLexem;

        return nullptr;
    }
}
