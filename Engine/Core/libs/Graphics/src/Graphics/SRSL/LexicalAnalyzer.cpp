//
// Created by Monika on 22.01.2023.
//

#include <Graphics/SRSL/LexicalAnalyzer.h>

namespace SR_SRSL_NS {
    std::pair<SRSLLexicalTree, SRSLLexicalAnalyzer::LXAResult> SRSLLexicalAnalyzer::Analyze(std::vector<Lexem>&& lexems) {
        SR_GLOBAL_LOCK

        Clear();

        m_lexems = SR_UTILS_NS::Exchange(lexems, { });

        ProcessMain();

        return std::make_pair(SR_UTILS_NS::Exchange(m_lexicalTree, { }), m_result);
    }

    void SRSLLexicalAnalyzer::Clear() {
        m_lexicalTree = SRSLLexicalTree();

        SR_SAFE_DELETE_PTR(m_decorators);
        SR_SAFE_DELETE_PTR(m_expr);

        m_lexems.clear();
        m_currentLexem = 0;

        m_states.clear();
        m_result = LXAResult(LXAReturnCode::Success);
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
        while (InBounds() && m_result.code == LXAReturnCode::Success) {
            switch (m_lexems[m_currentLexem].kind) {
                case LexemKind::OpeningSquareBracket:
                case LexemKind::ClosingSquareBracket:
                case LexemKind::OpeningAngleBracket:
                case LexemKind::ClosingAngleBracket:
                case LexemKind::OpeningCurlyBracket:
                case LexemKind::ClosingCurlyBracket:
                case LexemKind::OpeningBracket:
                case LexemKind::ClosingBracket:
                    ProcessBracket();
                    break;

                case LexemKind::Plus:
                case LexemKind::Minus:
                case LexemKind::Multiply:
                case LexemKind::Divide:
                case LexemKind::Assign:
                case LexemKind::Semicolon:
                case LexemKind::Dot:
                case LexemKind::Comma:
                case LexemKind::Negation:
                case LexemKind::And:
                case LexemKind::Or:
                case LexemKind::Integer:
                case LexemKind::Macro:
                case LexemKind::Identifier:
                    ++m_currentLexem;
                    break;
                default:
                    m_result = LXAResult(LXAReturnCode::UnknownLexem, GetLexem(0)->offset);
                    break;
            }
        }
    }

    void SRSLLexicalAnalyzer::ProcessBracket() {
        switch (m_lexems[m_currentLexem].kind)
        {
            case LexemKind::OpeningSquareBracket: {
                if (m_states.empty()) {
                    ProcessDecorators();
                    m_lexicalTree.lexicalTree.emplace_back(SR_UTILS_NS::Exchange(m_decorators, nullptr));
                    return;
                }
                break;
            }

            default:
                break;
        }

        m_result = LXAResult(LXAReturnCode::UnexceptedLexem, m_lexems[m_currentLexem].offset);
    }

    const Lexem* SRSLLexicalAnalyzer::GetCurrentLexem() const {
        return GetLexem(0);
    }

    void SRSLLexicalAnalyzer::ProcessExpression() {
        SR_SAFE_DELETE_PTR(m_expr);
        m_expr = new SRSLExpr();

        std::string value;

    retry:
        switch (m_lexems[m_currentLexem].kind)
        {
            case LexemKind::Integer: {
                if (!m_states.empty() && m_states.back() == LXAState::NumericDot) {
                    m_states.back() = LXAState::Float;
                }

                const bool isNumberState = !m_states.empty() && (m_states.back() == LXAState::Integer || m_states.back() == LXAState::Float);
                if (!isNumberState) {
                    m_states.emplace_back(LXAState::Integer);
                }

                value += m_lexems[m_currentLexem].value;
                ++m_currentLexem;
                goto retry;
            }
            case LexemKind::Dot: {
                if (!m_states.empty() && m_states.back() == LXAState::Integer) {
                    value += m_lexems[m_currentLexem].value;
                    ++m_currentLexem;
                    goto retry;
                }
                break;
            }
            default:
                break;
        }

        const bool isNumberState = !m_states.empty() && (m_states.back() == LXAState::Integer || m_states.back() == LXAState::Float);
        if (isNumberState) {
            m_states.pop_back();
            m_expr->type = SRSLExprType::Value;
            m_expr->token = value;
            return;
        }

        m_result = LXAResult(LXAReturnCode::UnexceptedLexem, m_lexems[m_currentLexem].offset);
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
                if (!m_states.empty() && m_states.back() == LXAState::Decorator) {
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
                if (!m_states.empty() && (m_states.back() == LXAState::Decorators || m_states.back() == LXAState::DecoratorArgs)) {
                    ++m_currentLexem;
                    goto retry;
                }
                break;
            }
            case LexemKind::OpeningBracket: {
                if (!m_states.empty() && m_states.back() == LXAState::Decorator) {
                    m_states.back() = LXAState::DecoratorArgs;
                    ++m_currentLexem;
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
            case LexemKind::Minus:
            case LexemKind::Negation:
            case LexemKind::Integer:
                if (!m_states.empty() && m_states.back() == LXAState::DecoratorArgs) {
                    ProcessExpression();
                    m_decorators->decorators.back().args.emplace_back(SR_UTILS_NS::Exchange(m_expr, nullptr));

                    if (IsHasErrors()) {
                        return;
                    }

                    goto retry;
                }
                break;
            default:
                break;
        }

        m_result = LXAResult(LXAReturnCode::UnexceptedLexem, m_lexems[m_currentLexem].offset);
    }

    bool SRSLLexicalAnalyzer::IsHasErrors() const noexcept {
        return m_result.code != LXAReturnCode::Success;
    }
}
