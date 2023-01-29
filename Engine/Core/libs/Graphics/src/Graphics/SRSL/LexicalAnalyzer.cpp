//
// Created by Monika on 22.01.2023.
//

#include <Graphics/SRSL/LexicalAnalyzer.h>

namespace SR_SRSL_NS {
    std::pair<SRSLLexicalTree, SRSLResult> SRSLLexicalAnalyzer::Analyze(std::vector<Lexem>&& lexems) {
        SR_GLOBAL_LOCK

        Clear();

        m_lexems = SR_UTILS_NS::Exchange(lexems, { });

        ProcessMain();

        return std::make_pair(SR_UTILS_NS::Exchange(m_lexicalTree, { }), SR_UTILS_NS::Exchange(m_result, { }));
    }

    void SRSLLexicalAnalyzer::Clear() {
        m_lexicalTree = SRSLLexicalTree();
        m_lexicalTree.lexicalTree.clear();

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
                    if (TryProcessIdentifier()) {
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
                    ProcessExpression();
                    if (IsHasErrors()) {
                        return;
                    }
                    m_lexicalTree.lexicalTree.emplace_back(m_expr);
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
                ProcessExpression();
                if (IsHasErrors()) {
                    return;
                }
                m_lexicalTree.lexicalTree.emplace_back(m_expr);
                return;
            }
            case LexemKind::OpeningSquareBracket: {
                if (m_states.empty()) {
                    SR_SAFE_DELETE_PTR(m_decorators);
                    ProcessDecorators();
                    return;
                }
                break;
            }

            default:
                break;
        }

        m_result = SRSLResult(SRSLReturnCode::UnexceptedLexem, m_lexems[m_currentLexem].offset);
    }

    const Lexem* SRSLLexicalAnalyzer::GetCurrentLexem() const {
        return GetLexem(0);
    }

    void SRSLLexicalAnalyzer::ProcessExpression() {
        std::vector<Lexem> exprLexems;
        uint32_t deep = 0;
        bool allowIdentifier = true;

    retry:
        const LexemKind lexemKind = InBounds() ? m_lexems[m_currentLexem].kind : LexemKind::Unknown;
        switch (lexemKind)
        {
            case LexemKind::OpeningBracket:
            case LexemKind::OpeningSquareBracket:
                ++deep;
                SR_FALLTHROUGH;
            default: {
                switch (lexemKind) {
                    case LexemKind::Unknown:
                    case LexemKind::Semicolon:
                    case LexemKind::Macro:
                    case LexemKind::Comma:
                        break;

                    default: {
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
                if (m_states.empty()) {
                    m_states.emplace_back(LXAState::Decorators);
                    ++m_currentLexem;
                    goto retry;
                }
                else if (m_states.back() == LXAState::Decorators) {
                    m_states.emplace_back(LXAState::Decorator);
                    m_decorators->decorators.emplace_back(std::move(SRSLDecorator()));
                    ++m_currentLexem;
                    goto retry;
                }
                break;
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

    bool SRSLLexicalAnalyzer::TryProcessIdentifier() {
        auto&& pCurrent = GetCurrentLexem();

        if (pCurrent->value == "return") {
            ++m_currentLexem;
            ProcessExpression();
            if (IsHasErrors()) {
                return false;
            }
            m_lexicalTree.lexicalTree.emplace_back(new SRSLReturn(std::move(m_expr)));
            return true;
        }

        if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::OpeningSquareBracket) {
            ProcessExpression();
        }
        else {
            m_expr = new SRSLExpr(std::string(pCurrent->value));
            ++m_currentLexem;
        }

        if (pCurrent = GetCurrentLexem(); pCurrent && pCurrent->kind == LexemKind::Identifier) {
            if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::OpeningBracket) {

            }
            /// здесь мы предпологаем что все "+=", "-=" и тд уже развернуты в выражения типа "a = a + b"
            else if (pNext && pNext->kind == LexemKind::Assign) {
                //auto&& pVariable = SRSLVariable();
            }
            else {
                auto&& pVariable = new SRSLVariable();

                pVariable->pType = SR_UTILS_NS::Exchange(m_expr, nullptr);
                pVariable->name = pCurrent->value;
                pVariable->pDecorators = SR_UTILS_NS::Exchange(m_decorators, nullptr);

                m_lexicalTree.lexicalTree.emplace_back(std::move(pVariable));
                m_currentLexem += 1;

                return true;
            }
        }
        else {
            --m_currentLexem;
        }

        return false;
    }
}
