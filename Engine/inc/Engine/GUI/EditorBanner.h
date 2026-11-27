//
// Created by Monika on 28.11.2026.
//

#ifndef SR_ENGINE_GUI_EDITOR_BANNER_H
#define SR_ENGINE_GUI_EDITOR_BANNER_H

#include <Engine/stdInclude.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

/// Общее оформление презентационных окон редактора (Welcome, About)
namespace SR_CORE_GUI_NS::EditorBanner {
    /// Градиентная шапка на всю ширину области контента. Курсор остается под шапкой.
    /// Возвращает true, если нажат крестик закрытия в правом верхнем углу.
    bool Draw(void* pLogoDescriptor, const char* title, const char* subtitle, const char* badge, float_t height);

    /// Размер окна в единицах размера шрифта, ограниченный размером экрана
    SR_NODISCARD SR_MATH_NS::IVector2 CalcWindowSize(float_t widthInFontSizes, float_t heightInFontSizes);

    /// Заголовок раздела: акцентный текст с линией до конца строки
    void SectionTitle(const char* title);

    /// Карточка с заголовком и переносимым текстом
    void Card(const char* id, const char* title, const char* text, const SR_MATH_NS::FVector2& size);

    bool AccentButton(const char* label, const SR_MATH_NS::FVector2& size);
    bool SecondaryButton(const char* label, const SR_MATH_NS::FVector2& size);

    /// Ссылка: подсвечивается при наведении, по клику открывает url
    void Link(const char* label, const char* url);

    /// Строка "название - значение", значение выравнивается по labelWidth
    void InfoRow(const char* label, const char* value, float_t labelWidth);

    /// Набор скругленных меток с автоматическим переносом по ширине окна
    void Tags(std::span<const char* const> tags);

    SR_NODISCARD SR_MATH_NS::FColor GetAccentColor();
    SR_NODISCARD SR_MATH_NS::FColor GetMutedTextColor();
}

#endif //SR_ENGINE_GUI_EDITOR_BANNER_H
