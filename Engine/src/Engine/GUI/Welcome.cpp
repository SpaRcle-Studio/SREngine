//
// Created by Monika on 28.11.2026.
//

#include <Engine/GUI/Welcome.h>
#include <Engine/GUI/EditorBanner.h>
#include <Engine/GUI/AssetsStore.h>
#include <Engine/GUI/EditorGUI.h>

#include <Utils/Platform/Process.h>

#include <Codegen/Welcome.generated.hpp>

namespace SR_CORE_GUI_NS {
    Welcome::Welcome()
        : Super("Welcome", SR_MATH_NS::IVector2(860, 640))
    {
        SetCenter(true);
        SetFlags(static_cast<SR_GRAPH_GUI_NS::WindowFlags>(SR_GRAPH_GUI_NS::WindowFlags::NoTitleBar
            | SR_GRAPH_GUI_NS::WindowFlags::NoCollapse
            | SR_GRAPH_GUI_NS::WindowFlags::NoMove
            | SR_GRAPH_GUI_NS::WindowFlags::NoDocking
            | SR_GRAPH_GUI_NS::WindowFlags::NoSavedSettings
        ));
        m_logo = "Engine/Textures/logo.png";
    }

    void Welcome::OpenAssetsStore() {
        if (auto&& pEditor = dynamic_cast<EditorGUI*>(GetManager())) {
            if (auto&& pStore = pEditor->OpenWidget<AssetsStore>()) {
                pStore->Focus();
            }
        }
        Close();
    }

    void Welcome::Draw() {
        const float_t baseFontSize = SR_IMMEDIATE_GUI_NS::GetFontSize();
        const float_t spacing = baseFontSize * 0.75f;

        /// ширина зависит от шрифта редактора, высота - от фактического содержимого прошлого кадра
        SR_MATH_NS::IVector2 windowSize = EditorBanner::CalcWindowSize(68.0f, 60.0f);
        if (m_contentHeight > 0.0f) {
            windowSize.y = static_cast<int32_t>(SR_MIN(m_contentHeight, SR_IMMEDIATE_GUI_NS::GetDisplaySize().y * 0.9f));
        }
        SetSize(windowSize);

        void* pLogoDescriptor = nullptr;
        if (m_logo) {
            pLogoDescriptor = m_logo.GetResource()->GetDescriptor();
        }

        if (EditorBanner::Draw(pLogoDescriptor, "SpaRcle Engine", "Добро пожаловать! Рады видеть вас в нашем движке.", "v" SR_ENGINE_VERSION, baseFontSize * 11.0f)) {
            Close();
            return;
        }

        /// Вступление
        SR_IMMEDIATE_GUI_NS::PushFont(nullptr, baseFontSize * 1.1f);
        SR_IMMEDIATE_GUI_NS::TextWrapped("%s",
            "SpaRcle Engine - кроссплатформенный игровой движок на C++ с открытым исходным кодом. "
            "Он задуман как лёгкая и гибкая основа для игр: от небольших прототипов до проектов "
            "с современной графикой. Редактор, сцены, физика, звук и скрипты: всё в одном "
            "исполняемом файле, без установки."
        );
        SR_IMMEDIATE_GUI_NS::PopFont();

        /// Возможности
        EditorBanner::SectionTitle("Возможности");

        const float_t availableWidth = SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x;
        const SR_MATH_NS::FVector2 cardSize((availableWidth - spacing) * 0.5f, baseFontSize * 8.0f);

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2(spacing, spacing));

        EditorBanner::Card("##RenderCard", "Графика",
            "Vulkan и WebGPU, настраиваемый граф рендера и собственный язык шейдеров SRSL с горячей перезагрузкой.",
            cardSize
        );
        SR_IMMEDIATE_GUI_NS::SameLine();
        EditorBanner::Card("##ScriptsCard", "Скрипты",
            "C++ скрипты с горячей перезагрузкой и сохранением состояния, а также AngelScript для быстрой логики.",
            cardSize
        );

        EditorBanner::Card("##PhysicsCard", "Физика и звук",
            "PhysX и Box2D для 3D и 2D физики, пространственный звук на OpenAL.",
            cardSize
        );
        SR_IMMEDIATE_GUI_NS::SameLine();
        EditorBanner::Card("##PlatformsCard", "Платформы",
            "Windows, Linux, Android и браузер через Emscripten. Сборка игры прямо из редактора.",
            cardSize
        );

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        /// С чего начать
        EditorBanner::SectionTitle("С чего начать?");

        SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, EditorBanner::GetMutedTextColor());
        SR_IMMEDIATE_GUI_NS::TextWrapped("%s",
            "Загляните в магазин ассетов и скачайте примеры: готовые сцены, модели и материалы "
            "помогут быстро разобраться в возможностях движка. Новый проект можно создать через File > Project."
        );
        SR_IMMEDIATE_GUI_NS::PopStyleColor();

        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, spacing));

        const float_t buttonHeight = baseFontSize * 2.6f;
        const float_t secondaryWidth = baseFontSize * 11.0f;
        const float_t accentWidth = SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x - (secondaryWidth + spacing) * 2.0f;

        SR_IMMEDIATE_GUI_NS::PushFont(nullptr, baseFontSize * 1.1f);

        if (EditorBanner::AccentButton("Открыть магазин ассетов и скачать примеры", SR_MATH_NS::FVector2(accentWidth, buttonHeight))) {
            OpenAssetsStore();
        }

        SR_IMMEDIATE_GUI_NS::SameLine(0.0f, spacing);

        if (EditorBanner::SecondaryButton("Документация", SR_MATH_NS::FVector2(secondaryWidth, buttonHeight))) {
            if (!SR_PLATFORM_NS::OpenAssociated("https://docs.sparcles.dev/")) {
                SR_WARN("Welcome::Draw() : failed to open documentation!");
            }
        }

        SR_IMMEDIATE_GUI_NS::SameLine(0.0f, spacing);

        if (EditorBanner::SecondaryButton("Начать работу", SR_MATH_NS::FVector2(secondaryWidth, buttonHeight))) {
            Close();
        }

        SR_IMMEDIATE_GUI_NS::PopFont();

        /// Подвал
        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, spacing));
        SR_IMMEDIATE_GUI_NS::Separator();
        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0.0f, spacing * 0.3f));

        SR_IMMEDIATE_GUI_NS::TextColored(EditorBanner::GetMutedTextColor(), "%s", "Это окно всегда можно открыть снова: Help > Welcome.");
        SR_IMMEDIATE_GUI_NS::SameLine(0.0f, spacing * 2.0f);
        EditorBanner::Link("GitHub", "https://github.com/SpaRcle-Studio/SREngine");
        SR_IMMEDIATE_GUI_NS::SameLine(0.0f, spacing);
        EditorBanner::Link("Discord", "https://discord.gg/NHuhNwFtYQ");

        m_contentHeight = SR_IMMEDIATE_GUI_NS::GetCursorPos().y + SR_IMMEDIATE_GUI_NS::GetStyleVarVec2(SR_IMMEDIATE_GUI_NS::StyleVar::WindowPadding).y;
    }
}
