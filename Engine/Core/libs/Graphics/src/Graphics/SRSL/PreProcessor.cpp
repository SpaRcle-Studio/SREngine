//
// Created by Monika on 05.08.2023.
//

#include <Graphics/SRSL/PreProcessor.h>

namespace SR_SRSL_NS {
    SRSLPreProcessor::OutResult SRSLPreProcessor::Process(std::vector<Lexem>&& lexems, Includes& includes) {
        Clear();

        m_lexems = SR_UTILS_NS::Exchange(lexems, { });
        m_includes = std::move(includes);

        while (InBounds() && !IsHasErrors()) {
            ProcessMain();
        }

        includes = std::move(m_includes);

        return std::make_pair(SR_UTILS_NS::Exchange(m_lexems, { }), std::move(m_result));
    }

    void SRSLPreProcessor::Clear() {
        m_currentLexem = 0;
        m_lexems.clear();
        m_result = SRSLResult();
        m_state = PPState::Idle;
        m_includes.clear();
        m_include.clear();
    }

    const Lexem* SRSLPreProcessor::GetLexem(int64_t offset) const {
        if (m_currentLexem + offset < static_cast<int64_t>(m_lexems.size()) && m_currentLexem + offset >= 0) {
            return &m_lexems.at(m_currentLexem + offset);
        }

        return nullptr;
    }

    bool SRSLPreProcessor::InBounds() const noexcept {
        return m_currentLexem < m_lexems.size();
    }

    bool SRSLPreProcessor::IsHasErrors() const noexcept {
        return m_result.HasErrors();
    }

    const Lexem* SRSLPreProcessor::GetCurrentLexem() const {
        return GetLexem(0);
    }

    void SRSLPreProcessor::ProcessMain() {
        switch (m_lexems[m_currentLexem].kind) {
            case LexemKind::Macro:
                if (m_state != PPState::Idle) {
                    m_result.AddError(SRSLMessage(SRSLReturnCode::UnknownLexem, GetCurrentLexem()));
                    return;
                }
                m_state = PPState::MacroName;
                m_lexems.erase(m_lexems.begin() + m_currentLexem);
                break;
            case LexemKind::OpeningAngleBracket:
                if (m_state == PPState::IncludeOpen) {
                    m_state = PPState::IncludePath;
                    m_lexems.erase(m_lexems.begin() + m_currentLexem);
                    break;
                }
                ++m_currentLexem;
                break;
            case LexemKind::ClosingAngleBracket:
                if (m_state == PPState::IncludePath) {
                    m_state = PPState::Idle;
                    m_lexems.erase(m_lexems.begin() + m_currentLexem);

                    auto&& includePath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(m_include);
                    if (!includePath.Exists(SR_UTILS_NS::Path::Type::File)) {
                        m_result.AddError(SRSLMessage(SRSLReturnCode::IncludeNotExists, GetCurrentLexem()))
                            .SetDescription(m_include);
                        return;
                    }

                    m_includes.emplace_back(std::move(m_include));

                    auto&& lexems = SR_SRSL_NS::SRSLLexer::Instance().Parse(includePath, m_include.size());
                    if (lexems.empty()) {
                        SR_ERROR("SRSLPreProcessor::ProcessMain() : failed to parse lexems!\n\tPath: " + includePath.ToString());
                        m_result.AddError(SRSLMessage(SRSLReturnCode::IncludeError, GetCurrentLexem())).SetDescription(includePath);
                        return;
                    }

                    m_lexems.insert(m_lexems.begin() + m_currentLexem, lexems.begin(), lexems.end());

                    break;
                }
                ++m_currentLexem;
                break;
            case LexemKind::Identifier:
                if (m_state == PPState::MacroName) {
                    if (GetCurrentLexem()->value == "include") {
                        m_state = PPState::IncludeOpen;
                        m_lexems.erase(m_lexems.begin() + m_currentLexem);
                    }
                    else {
                        m_result.AddError(SRSLMessage(SRSLReturnCode::UnknownLexem, GetCurrentLexem()));
                    }
                    break;
                }
                SR_FALLTHROUGH;
            case LexemKind::Integer:
            case LexemKind::Plus:
            case LexemKind::Minus:
            case LexemKind::OpeningSquareBracket:
            case LexemKind::ClosingSquareBracket:
            case LexemKind::OpeningCurlyBracket:
            case LexemKind::ClosingCurlyBracket:
            case LexemKind::OpeningBracket:
            case LexemKind::ClosingBracket:
            case LexemKind::Exponentiation:
            case LexemKind::Assign:
            case LexemKind::Dot:
            case LexemKind::Comma:
            case LexemKind::Negation:
            case LexemKind::Semicolon:
            case LexemKind::Percent:
            case LexemKind::Divide:
                switch (m_state) {
                    case PPState::Idle:
                        ++m_currentLexem;
                        break;
                    case PPState::IncludePath:
                        m_include += GetCurrentLexem()->value;
                        m_lexems.erase(m_lexems.begin() + m_currentLexem);
                        break;
                    default:
                        m_result.AddError(SRSLMessage(SRSLReturnCode::UnknownLexem, GetCurrentLexem()));
                        return;
                }
                break;
            default:
                ++m_currentLexem;
                break;
        }
    }
}