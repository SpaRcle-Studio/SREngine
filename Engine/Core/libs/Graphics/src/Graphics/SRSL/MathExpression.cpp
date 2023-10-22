//
// Created by Monika on 23.01.2023.
//

#include <Graphics/SRSL/MathExpression.h>

namespace SR_SRSL_NS {
    std::pair<SRSLExpr*, SRSLResult> SRSLMathExpression::Analyze(std::vector<Lexem>&& lexems) {
        Clear();

        m_lexems = SR_UTILS_NS::Exchange(lexems, { });

        if (m_lexems.empty()) {
            return std::make_pair(nullptr, SRSLReturnCode::EmptyExpression);
        }

        auto&& pExpr = ParseBinaryExpression(0);
        return std::make_pair(pExpr, std::move(m_result));
    }

    SRSLExpr* SRSLMathExpression::ParseBinaryExpression(int32_t minPriority) {
        SRSLExpr* pLeftExpr = ParseSimpleExpression();

        if (!InBounds()) {
            return pLeftExpr;
        }

        while (true) {
            uint32_t currentLexem = m_currentLexem;
            std::string operation = ParseToken();

            if (IsHasErrors()) {
                SR_SAFE_DELETE_PTR(pLeftExpr);
                return nullptr;
            }

            if (minPriority != 0 && operation == ".") {
                m_currentLexem = currentLexem;
                return pLeftExpr;
            }

            if (operation == "]" || operation == ",") {
                return pLeftExpr;
            }

            const int32_t priority = GetPriority(operation, IsPrefix());

            if (priority <= minPriority) {
                m_currentLexem = currentLexem;
                return pLeftExpr;
            }

            if (IsIncrementOrDecrement(operation)) {
                /// постинкремент
                pLeftExpr = new SRSLExpr(pLeftExpr, new SRSLExpr(std::move(operation)));

                if (!InBounds()) {
                    return pLeftExpr;
                }

                currentLexem = m_currentLexem;
                if (ParseToken() == ")") {
                    m_currentLexem = currentLexem;
                    return pLeftExpr;
                }
                m_currentLexem = currentLexem;

                auto&& pRightExpr = ParseBinaryExpression(priority);

                /// лексемы закончились
                if (!pRightExpr) {
                    return pLeftExpr;
                }

                if (pRightExpr->args.size() != 1) {
                    m_result = SRSLResult(SRSLReturnCode::InvalidIncrementOrDecrement);
                    SR_SAFE_DELETE_PTR(pRightExpr);
                    return pLeftExpr;
                }
                else {
                    pLeftExpr = new SRSLExpr(std::move(pRightExpr->token), pLeftExpr, SR_UTILS_NS::Exchange(pRightExpr->args[0], nullptr));
                    SR_SAFE_DELETE_PTR(pRightExpr);
                }
            }
            else {
                if (InBounds()) {
                    auto &&pRightExpr = ParseBinaryExpression(priority);
                    pLeftExpr = new SRSLExpr(std::move(operation), pLeftExpr, pRightExpr);
                }
                else {
                    return pLeftExpr;
                }
            }

            if (!InBounds() || GetCurrentLexem()->kind == LexemKind::OpeningSquareBracket) {
                return pLeftExpr;
            }
        }
    }

    SRSLExpr* SRSLMathExpression::ParseSimpleExpression() {
        std::string token = ParseToken();

        if (IsHasErrors()) {
            return nullptr;
        }

        if (token.empty()) {
            m_result = SRSLResult(SRSLReturnCode::EmptyToken);
            return nullptr;
        }

        if (SR_MATH_NS::IsNumber(token) || IsIdentifier(token)) {
            auto&& pBasicExpr = new SRSLExpr(std::move(token));

            /// parse function call
            if (auto&& pLexem = GetCurrentLexem(); pLexem && pLexem->kind == LexemKind::OpeningBracket) {
                ++m_currentLexem;

                pBasicExpr->isCall = true;

            retryFnArg:
                pLexem = GetCurrentLexem();
                if (!pLexem || IsHasErrors()) {
                    SR_SAFE_DELETE_PTR(pBasicExpr);
                    m_result = SRSLResult(SRSLReturnCode::InvalidCall);
                    return nullptr;
                }

                if (pLexem->kind == LexemKind::Comma) {
                    ++m_currentLexem;
                    goto retryFnArg;
                }

                if (pLexem->kind == LexemKind::ClosingBracket) {
                    ++m_currentLexem;
                    return pBasicExpr;
                }

                auto&& pArgExpr = ParseBinaryExpression(0);
                if (pArgExpr) {
                    pBasicExpr->args.emplace_back(pArgExpr);
                }

                goto retryFnArg;
            }

        retrySubExpr:
            if (auto&& pLexem = GetCurrentLexem(); pLexem && pLexem->kind == LexemKind::OpeningSquareBracket) {
                ++m_currentLexem;
                auto&& pExpr = ParseBinaryExpression(30 /** = */);
                pBasicExpr = new SRSLExpr("[", pBasicExpr, pExpr);
                goto retrySubExpr;
            }
            else if (pLexem && pLexem->kind == LexemKind::Dot) {
                ++m_currentLexem;
                std::string field = GetCurrentLexem()->value;
                auto&& pExpr = new SRSLExpr(std::move(field));
                pBasicExpr = new SRSLExpr(".", pBasicExpr, pExpr);
                ++m_currentLexem;
                goto retrySubExpr;
            }

            return pBasicExpr;
        }

        if (token.size() == 1 && (token == "(")) {
            auto&& pExpr = ParseBinaryExpression(0);

            if (!InBounds()) {
                SR_SAFE_DELETE_PTR(pExpr);
                m_result = SRSLResult(SRSLReturnCode::InvalidComplexExpression);
                return nullptr;
            }

            std::string parsedToken = ParseToken();
            if (parsedToken != ")") {
                SR_SAFE_DELETE_PTR(pExpr);
                m_result = SRSLResult(SRSLReturnCode::InvalidComplexExpression);
                return nullptr;
            }

            return pExpr;
        }

        /// parse list { ... }
        if (token.size() == 1 && token == "{") {
            auto&& pListExpr = new SRSLExpr(std::move(token));

        labelNextArrayElem:
            token = ParseToken();

            if (token.empty()) {
                m_result = SRSLResult(SRSLReturnCode::InvalidListEnd);
                SR_SAFE_DELETE_PTR(pListExpr);
                return nullptr;
            }

            if (token == ",") {
                goto labelNextArrayElem;
            }

            if (token == "}") {
                return pListExpr;
            }

            --m_currentLexem;

            if (auto&& pListElemExpr = ParseBinaryExpression(0)) {
                pListExpr->args.emplace_back(pListElemExpr);
            }

            goto labelNextArrayElem;
        }

        if (!InBounds()) {
            return new SRSLExpr(std::move(token));
        }

        auto&& pArgExpr = ParseSimpleExpression();

        if (IsHasErrors()) {
            SR_SAFE_DELETE_PTR(pArgExpr);
            return nullptr;
        }

        if (IsIncrementOrDecrement(token)) {
            return new SRSLExpr(new SRSLExpr(std::move(token)), pArgExpr);
        }

        return new SRSLExpr(std::move(token), pArgExpr);
    }

    int32_t SRSLMathExpression::GetPriority(const std::string& operation, bool prefix) const {
        if (operation == "") {

        }

        //else if (operation == ".") return 25;

        else if (operation == "=") return 30;

        else if (operation == "~" && prefix) return 35;
        else if (operation == "!" && prefix) return 40;
        else if (operation == "+" && prefix) return 45;
        else if (operation == "-" && prefix) return 45;

        else if (operation == "[") return 50;
        else if (operation == "]") return 50;

        else if (operation == "?") return 60;
        else if (operation == ":") return 60;

        else if (operation == "||") return 71;
        else if (operation == "^^") return 72;
        else if (operation == "&&") return 73;

        else if (operation == "|") return 75;
        else if (operation == "^") return 76;
        else if (operation == "&") return 77;

        else if (operation == "!=") return 80;
        else if (operation == "==") return 80;

        else if (operation == ">=") return 85;
        else if (operation == "<=") return 85;
        else if (operation == ">") return 85;
        else if (operation == "<") return 85;

        else if (operation == ">>") return 90;
        else if (operation == "<<") return 90;

        else if (operation == "+") return 100;
        else if (operation == "-") return 100;

        else if (operation == "*") return 300;
        else if (operation == "/") return 300;
        else if (operation == "%") return 300;

        else if (operation == "++") return 500;
        else if (operation == "--") return 500;

        else if (operation == ".") return 600;

        return 0;
    }

    void SRSLMathExpression::Clear() {
        m_result = SRSLResult();

        m_lexems.clear();
        m_currentLexem = 0;
    }

    const Lexem* SRSLMathExpression::GetLexem(int64_t offset) const {
        if (m_currentLexem + offset < static_cast<int64_t>(m_lexems.size())) {
            return &m_lexems.at(m_currentLexem + offset);
        }

        return nullptr;
    }

    bool SRSLMathExpression::InBounds() const noexcept {
        return m_currentLexem < m_lexems.size();
    }

    bool SRSLMathExpression::IsHasErrors() const noexcept {
        return m_result.HasErrors();
    }

    const Lexem* SRSLMathExpression::GetCurrentLexem() const {
        return GetLexem(0);
    }

    std::string SRSLMathExpression::ParseToken()
    {
        /// пытаемся обработать как число
        {
            bool hasDot = false;
            bool hasInt = false;

            std::string token;

        retry:
            switch (InBounds() ? GetCurrentLexem()->kind : LexemKind::Unknown) {
                case LexemKind::Integer:
                    token += m_lexems[m_currentLexem++].value;
                    hasInt = true;
                    goto retry;
                case LexemKind::Dot:
                    if (hasDot) {
                        m_result = SRSLResult(SRSLReturnCode::UnexceptedDot, GetCurrentLexem());
                        return std::string();
                    }
                    token += m_lexems[m_currentLexem++].value;
                    hasDot = true;
                    goto retry;
                default: {
                    if (hasDot && !hasInt) {
                        return token;
                    }
                    else if (hasInt) {
                        return token;
                    }

                    break;
                }
            }
        }

        switch (GetCurrentLexem()->kind) {
            case LexemKind::OpeningBracket:
            case LexemKind::ClosingBracket:
            case LexemKind::OpeningSquareBracket:
            case LexemKind::ClosingSquareBracket:
            case LexemKind::ClosingCurlyBracket:
            case LexemKind::OpeningCurlyBracket:
            case LexemKind::Identifier:
            case LexemKind::Tilda:
            case LexemKind::Comma:
            case LexemKind::Dot:
            case LexemKind::Question:
            case LexemKind::Colon:
                return m_lexems[m_currentLexem++].value;

            case LexemKind::Negation: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// !=
                }
                return m_lexems[m_currentLexem++].value; /// !
            }

            case LexemKind::Multiply: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// *=
                }
                return m_lexems[m_currentLexem++].value; /// *
            }

            case LexemKind::Exponentiation: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Exponentiation) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// ^^
                }
                else if (pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// ^=
                }
                return m_lexems[m_currentLexem++].value; /// ^
            }

            case LexemKind::Divide: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// /=
                }
                return m_lexems[m_currentLexem++].value; /// /
            }

            case LexemKind::Percent: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// %=
                }
                return m_lexems[m_currentLexem++].value; /// %
            }

            case LexemKind::OpeningAngleBracket: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// <=
                }
                else if (pNext && pNext->kind == LexemKind::OpeningAngleBracket) {
                    if (auto&& pNextNext = GetLexem(2); pNextNext && pNextNext->kind == LexemKind::Assign) {
                        auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value + m_lexems[m_currentLexem + 2].value;
                        m_currentLexem += 3;
                        return std::move(token); /// <<=
                    }
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// <<
                }
                return m_lexems[m_currentLexem++].value; /// <
            }

            case LexemKind::ClosingAngleBracket: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// >=
                }
                else if (pNext && pNext->kind == LexemKind::ClosingAngleBracket) {
                    if (auto&& pNextNext = GetLexem(2); pNextNext && pNextNext->kind == LexemKind::Assign) {
                        auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value + m_lexems[m_currentLexem + 2].value;
                        m_currentLexem += 3;
                        return std::move(token); /// >>=
                    }
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// >>
                }
                return m_lexems[m_currentLexem++].value; /// >
            }

            case LexemKind::Plus: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// +=
                }
                else if (pNext && pNext->kind == LexemKind::Plus) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// ++
                }
                return m_lexems[m_currentLexem++].value; /// +
            }

            case LexemKind::Minus: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// -=
                }
                else if (pNext && pNext->kind == LexemKind::Minus) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// --
                }
                return m_lexems[m_currentLexem++].value; /// +
            }

            case LexemKind::Assign: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// ==
                }
                return m_lexems[m_currentLexem++].value; /// =
            }

            case LexemKind::And: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::And) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// &&
                }
                else if (pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// &=
                }
                return m_lexems[m_currentLexem++].value; /// &
            }

            case LexemKind::Or: {
                if (auto&& pNext = GetLexem(1); pNext && pNext->kind == LexemKind::Or) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// ||
                }
                else if (pNext && pNext->kind == LexemKind::Assign) {
                    auto&& token = m_lexems[m_currentLexem].value + m_lexems[m_currentLexem + 1].value;
                    m_currentLexem += 2;
                    return std::move(token); /// |=
                }
                return m_lexems[m_currentLexem++].value; /// |
            }

            default:
                break;
        }

        m_result = SRSLResult(SRSLReturnCode::InvalidMathToken, GetCurrentLexem());
        return std::string();
    }

    bool SRSLMathExpression::IsIncrementOrDecrement(const std::string &operation) const {
        return operation == "++" || operation == "--";
    }

    bool SRSLMathExpression::IsPrefix() const noexcept {
        auto&& pLexem = GetLexem(-1);

        if (!pLexem) {
            return true;
        }

        if (IsOperator(pLexem->value)) {
            return false;
        }

        return pLexem->kind != LexemKind::Identifier;
    }
}