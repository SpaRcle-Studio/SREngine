//
// Created by Monika on 28.11.2026.
//

#include <Engine/GUI/EditorBanner.h>

#include <Utils/Platform/Process.h>

namespace SR_CORE_GUI_NS::EditorBanner {
    SR_MATH_NS::FColor GetAccentColor() {
        return SR_MATH_NS::FColor(0.45f, 0.62f, 1.0f, 1.0f);
    }

    SR_MATH_NS::FColor GetMutedTextColor() {
        return SR_MATH_NS::FColor(0.68f, 0.71f, 0.78f, 1.0f);
    }

    bool Draw(void* pLogoDescriptor, const char* title, const char* subtitle, const char* badge, float_t height) {
        auto&& pDrawList = SR_IMMEDIATE_GUI_NS::GetWindowDrawList();

        const float_t baseFontSize = SR_IMMEDIATE_GUI_NS::GetFontSize();
        const float_t width = SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x;

        const SR_MATH_NS::FVector2 min = SR_IMMEDIATE_GUI_NS::GetCursorScreenPos();
        const SR_MATH_NS::FVector2 max(min.x + width, min.y + height);

        SR_IMMEDIATE_GUI_NS::DrawListAddRectFilledMultiColor(pDrawList, min, max,
            SR_COL32(44, 58, 138, 255),
            SR_COL32(112, 48, 156, 255),
            SR_COL32(58, 22, 88, 255),
            SR_COL32(20, 28, 72, 255)
        );

        /// декоративные полупрозрачные круги в правой части шапки
        SR_IMMEDIATE_GUI_NS::DrawListAddCircleFilled(pDrawList, SR_MATH_NS::FVector2(max.x - height * 0.45f, min.y + height * 0.3f), height * 0.55f, SR_COL32(255, 255, 255, 12));
        SR_IMMEDIATE_GUI_NS::DrawListAddCircleFilled(pDrawList, SR_MATH_NS::FVector2(max.x - height * 1.25f, min.y + height * 0.62f), height * 0.3f, SR_COL32(255, 255, 255, 9));
        SR_IMMEDIATE_GUI_NS::DrawListAddCircleFilled(pDrawList, SR_MATH_NS::FVector2(max.x - height * 0.2f, min.y + height * 0.82f), height * 0.14f, SR_COL32(140, 200, 255, 22));

        /// акцентная полоса снизу
        SR_IMMEDIATE_GUI_NS::DrawListAddRectFilledMultiColor(pDrawList,
            SR_MATH_NS::FVector2(min.x, max.y - 3.0f), max,
            SR_COL32(90, 200, 255, 255),
            SR_COL32(190, 110, 255, 255),
            SR_COL32(190, 110, 255, 255),
            SR_COL32(90, 200, 255, 255)
        );

        const float_t padding = height * 0.18f;
        float_t textX = min.x + padding;

        if (pLogoDescriptor) {
            /// соотношение сторон Engine/Textures/logo.png
            const float_t logoHeight = height * 0.6f;
            const float_t logoWidth = logoHeight * (600.0f / 526.0f);
            const SR_MATH_NS::FVector2 logoMin(min.x + padding, min.y + (height - logoHeight) * 0.5f);
            SR_IMMEDIATE_GUI_NS::AddImage(pDrawList, pLogoDescriptor, logoMin, SR_MATH_NS::FVector2(logoMin.x + logoWidth, logoMin.y + logoHeight));
            textX = logoMin.x + logoWidth + padding;
        }

        const float_t titleSize = baseFontSize * 2.4f;
        const float_t subtitleSize = baseFontSize * 1.2f;
        const float_t textBlockHeight = titleSize + subtitleSize + baseFontSize * 0.5f;
        const float_t textY = min.y + (height - textBlockHeight) * 0.5f;

        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 1.0f));
        SR_IMMEDIATE_GUI_NS::PushFont(nullptr, titleSize);
        SR_IMMEDIATE_GUI_NS::SetCursorScreenPos(SR_MATH_NS::FVector2(textX, textY));
        SR_IMMEDIATE_GUI_NS::Text("%s", title);
        SR_IMMEDIATE_GUI_NS::PopFont();
        SR_IMMEDIATE_GUI_NS::PopStyleColor();

        if (subtitle) {
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(0.82f, 0.86f, 1.0f, 1.0f));
            SR_IMMEDIATE_GUI_NS::PushFont(nullptr, subtitleSize);
            SR_IMMEDIATE_GUI_NS::SetCursorScreenPos(SR_MATH_NS::FVector2(textX, textY + titleSize + baseFontSize * 0.5f));
            SR_IMMEDIATE_GUI_NS::Text("%s", subtitle);
            SR_IMMEDIATE_GUI_NS::PopFont();
            SR_IMMEDIATE_GUI_NS::PopStyleColor();
        }

        /// крестик закрытия в правом верхнем углу
        const float_t closeSize = baseFontSize * 2.2f;
        const float_t cornerOffset = baseFontSize * 0.6f;
        const SR_MATH_NS::FVector2 closeMin(max.x - cornerOffset - closeSize, min.y + cornerOffset);
        const SR_MATH_NS::FVector2 closeMax(closeMin.x + closeSize, closeMin.y + closeSize);

        SR_IMMEDIATE_GUI_NS::SetCursorScreenPos(closeMin);
        const bool closePressed = SR_IMMEDIATE_GUI_NS::InvisibleButton("##EditorBannerClose", SR_MATH_NS::FVector2(closeSize, closeSize));
        const bool closeHovered = SR_IMMEDIATE_GUI_NS::IsItemHovered();

        SR_IMMEDIATE_GUI_NS::DrawListAddRectFilled(pDrawList, closeMin, closeMax, closeHovered ? SR_COL32(232, 72, 92, 230) : SR_COL32(255, 255, 255, 34), closeSize * 0.5f);

        const float_t crossInset = closeSize * 0.32f;
        const float_t crossThickness = SR_MAX(1.5f, baseFontSize * 0.14f);
        SR_IMMEDIATE_GUI_NS::DrawListAddLine(pDrawList,
            SR_MATH_NS::FVector2(closeMin.x + crossInset, closeMin.y + crossInset),
            SR_MATH_NS::FVector2(closeMax.x - crossInset, closeMax.y - crossInset),
            SR_COL32(255, 255, 255, 240), crossThickness
        );
        SR_IMMEDIATE_GUI_NS::DrawListAddLine(pDrawList,
            SR_MATH_NS::FVector2(closeMax.x - crossInset, closeMin.y + crossInset),
            SR_MATH_NS::FVector2(closeMin.x + crossInset, closeMax.y - crossInset),
            SR_COL32(255, 255, 255, 240), crossThickness
        );

        if (badge) {
            const SR_MATH_NS::FVector2 badgeTextSize = SR_IMMEDIATE_GUI_NS::CalcTextSize(badge);
            const SR_MATH_NS::FVector2 badgePadding(baseFontSize * 0.7f, (closeSize - badgeTextSize.y) * 0.5f);
            const SR_MATH_NS::FVector2 badgeMax(closeMin.x - baseFontSize * 0.5f, closeMax.y);
            const SR_MATH_NS::FVector2 badgeMin(badgeMax.x - badgeTextSize.x - badgePadding.x * 2.0f, closeMin.y);

            SR_IMMEDIATE_GUI_NS::DrawListAddRectFilled(pDrawList, badgeMin, badgeMax, SR_COL32(255, 255, 255, 34), (badgeMax.y - badgeMin.y) * 0.5f);
            SR_IMMEDIATE_GUI_NS::AddText(pDrawList, SR_MATH_NS::FVector2(badgeMin.x + badgePadding.x, badgeMin.y + badgePadding.y), SR_COL32(255, 255, 255, 230), badge);
        }

        SR_IMMEDIATE_GUI_NS::SetCursorScreenPos(min);
        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(width, height));
        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, baseFontSize * 0.5f));

        return closePressed;
    }

    SR_MATH_NS::IVector2 CalcWindowSize(float_t widthInFontSizes, float_t heightInFontSizes) {
        const float_t baseFontSize = SR_IMMEDIATE_GUI_NS::GetFontSize();
        const SR_MATH_NS::FVector2 displaySize = SR_IMMEDIATE_GUI_NS::GetDisplaySize();

        const float_t width = SR_MIN(baseFontSize * widthInFontSizes, displaySize.x * 0.9f);
        const float_t height = SR_MIN(baseFontSize * heightInFontSizes, displaySize.y * 0.9f);

        return SR_MATH_NS::IVector2(static_cast<int32_t>(width), static_cast<int32_t>(height));
    }

    void SectionTitle(const char* title) {
        const float_t baseFontSize = SR_IMMEDIATE_GUI_NS::GetFontSize();

        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, baseFontSize * 0.4f));

        SR_IMMEDIATE_GUI_NS::PushFont(nullptr, baseFontSize * 1.15f);
        SR_IMMEDIATE_GUI_NS::TextColored(GetAccentColor(), "%s", title);
        SR_IMMEDIATE_GUI_NS::PopFont();

        const SR_MATH_NS::FVector2 textMax = SR_IMMEDIATE_GUI_NS::GetItemRectMax();
        const SR_MATH_NS::FVector2 textMin = SR_IMMEDIATE_GUI_NS::GetItemRectMin();
        const float_t lineY = (textMin.y + textMax.y) * 0.5f;
        const float_t lineEndX = SR_IMMEDIATE_GUI_NS::GetWindowPos().x + SR_IMMEDIATE_GUI_NS::GetWindowSize().x - SR_IMMEDIATE_GUI_NS::GetStyleVarVec2(SR_IMMEDIATE_GUI_NS::StyleVar::WindowPadding).x;

        if (lineEndX > textMax.x + baseFontSize) {
            SR_IMMEDIATE_GUI_NS::DrawListAddLine(SR_IMMEDIATE_GUI_NS::GetWindowDrawList(),
                SR_MATH_NS::FVector2(textMax.x + baseFontSize * 0.75f, lineY),
                SR_MATH_NS::FVector2(lineEndX, lineY),
                SR_COL32(255, 255, 255, 28)
            );
        }

        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, baseFontSize * 0.2f));
    }

    void Card(const char* id, const char* title, const char* text, const SR_MATH_NS::FVector2& size) {
        const float_t baseFontSize = SR_IMMEDIATE_GUI_NS::GetFontSize();

        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ChildBg, SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 0.035f));
        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Border, SR_MATH_NS::FColor(0.45f, 0.62f, 1.0f, 0.22f));
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ChildRounding, 8.0f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ChildBorderSize, 1.0f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::WindowPadding, SR_MATH_NS::FVector2(baseFontSize, baseFontSize * 0.8f));

        if (SR_IMMEDIATE_GUI_NS::BeginChild(id, size, SR_IMMEDIATE_GUI_NS::ChildWindowFlags::Borders, static_cast<SR_IMMEDIATE_GUI_NS::WindowFlags>(SR_IMMEDIATE_GUI_NS::WindowFlags::NoScrollbar | SR_IMMEDIATE_GUI_NS::WindowFlags::NoScrollWithMouse))) {
            SR_IMMEDIATE_GUI_NS::PushFont(nullptr, baseFontSize * 1.1f);
            SR_IMMEDIATE_GUI_NS::TextColored(GetAccentColor(), "%s", title);
            SR_IMMEDIATE_GUI_NS::PopFont();

            SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, baseFontSize * 0.15f));

            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, GetMutedTextColor());
            SR_IMMEDIATE_GUI_NS::TextWrapped("%s", text);
            SR_IMMEDIATE_GUI_NS::PopStyleColor();
        }
        SR_IMMEDIATE_GUI_NS::EndChild();

        SR_IMMEDIATE_GUI_NS::PopStyleVar(3);
        SR_IMMEDIATE_GUI_NS::PopStyleColor(2);
    }

    bool AccentButton(const char* label, const SR_MATH_NS::FVector2& size) {
        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Button, SR_MATH_NS::FColor(0.30f, 0.40f, 0.92f, 1.0f));
        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonHovered, SR_MATH_NS::FColor(0.40f, 0.51f, 1.0f, 1.0f));
        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonActive, SR_MATH_NS::FColor(0.24f, 0.32f, 0.80f, 1.0f));
        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 1.0f));
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameRounding, 6.0f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameBorderSize, 0.0f);

        const bool pressed = SR_IMMEDIATE_GUI_NS::Button(label, size);

        SR_IMMEDIATE_GUI_NS::PopStyleVar(2);
        SR_IMMEDIATE_GUI_NS::PopStyleColor(4);

        return pressed;
    }

    bool SecondaryButton(const char* label, const SR_MATH_NS::FVector2& size) {
        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Button, SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 0.06f));
        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonHovered, SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 0.12f));
        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonActive, SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 0.18f));
        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Border, SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 0.14f));
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameRounding, 6.0f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameBorderSize, 1.0f);

        const bool pressed = SR_IMMEDIATE_GUI_NS::Button(label, size);

        SR_IMMEDIATE_GUI_NS::PopStyleVar(2);
        SR_IMMEDIATE_GUI_NS::PopStyleColor(4);

        return pressed;
    }

    void Link(const char* label, const char* url) {
        SR_IMMEDIATE_GUI_NS::TextColored(GetAccentColor(), "%s", label);

        if (!SR_IMMEDIATE_GUI_NS::IsItemHovered()) {
            return;
        }

        const SR_MATH_NS::FVector2 min = SR_IMMEDIATE_GUI_NS::GetItemRectMin();
        const SR_MATH_NS::FVector2 max = SR_IMMEDIATE_GUI_NS::GetItemRectMax();
        SR_IMMEDIATE_GUI_NS::DrawListAddLine(SR_IMMEDIATE_GUI_NS::GetWindowDrawList(),
            SR_MATH_NS::FVector2(min.x, max.y),
            max,
            SR_COL32(115, 158, 255, 255)
        );

        if (SR_IMMEDIATE_GUI_NS::IsItemClicked()) {
            if (!SR_PLATFORM_NS::OpenAssociated(url)) {
                SR_WARN("EditorBanner::Link() : failed to open url \"{}\"", url);
            }
        }
    }

    void InfoRow(const char* label, const char* value, float_t labelWidth) {
        const float_t startX = SR_IMMEDIATE_GUI_NS::GetCursorPos().x;

        SR_IMMEDIATE_GUI_NS::TextColored(GetMutedTextColor(), "%s", label);
        SR_IMMEDIATE_GUI_NS::SameLine(startX + labelWidth);
        SR_IMMEDIATE_GUI_NS::Text("%s", value);
    }

    void Tags(std::span<const char* const> tags) {
        auto&& pDrawList = SR_IMMEDIATE_GUI_NS::GetWindowDrawList();

        const float_t baseFontSize = SR_IMMEDIATE_GUI_NS::GetFontSize();
        const SR_MATH_NS::FVector2 padding(baseFontSize * 0.6f, baseFontSize * 0.25f);
        const float_t gap = baseFontSize * 0.4f;

        const SR_MATH_NS::FVector2 origin = SR_IMMEDIATE_GUI_NS::GetCursorScreenPos();
        const float_t maxX = origin.x + SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x;

        SR_MATH_NS::FVector2 position = origin;
        float_t rowHeight = 0.0f;

        for (auto&& tag : tags) {
            const SR_MATH_NS::FVector2 textSize = SR_IMMEDIATE_GUI_NS::CalcTextSize(tag);
            const SR_MATH_NS::FVector2 tagSize(textSize.x + padding.x * 2.0f, textSize.y + padding.y * 2.0f);

            if (position.x > origin.x && position.x + tagSize.x > maxX) {
                position.x = origin.x;
                position.y += rowHeight + gap;
            }

            const SR_MATH_NS::FVector2 tagMax(position.x + tagSize.x, position.y + tagSize.y);

            SR_IMMEDIATE_GUI_NS::DrawListAddRectFilled(pDrawList, position, tagMax, SR_COL32(115, 158, 255, 30), tagSize.y * 0.5f);
            SR_IMMEDIATE_GUI_NS::DrawListAddRect(pDrawList, position, tagMax, SR_COL32(115, 158, 255, 70), tagSize.y * 0.5f);
            SR_IMMEDIATE_GUI_NS::AddText(pDrawList, SR_MATH_NS::FVector2(position.x + padding.x, position.y + padding.y), SR_COL32(214, 224, 255, 255), tag);

            rowHeight = SR_MAX(rowHeight, tagSize.y);
            position.x += tagSize.x + gap;
        }

        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(maxX - origin.x, position.y + rowHeight - origin.y));
    }
}
