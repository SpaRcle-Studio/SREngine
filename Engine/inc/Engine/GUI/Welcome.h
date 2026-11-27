//
// Created by Monika on 28.11.2026.
//

#ifndef SR_ENGINE_GUI_WELCOME_H
#define SR_ENGINE_GUI_WELCOME_H

#include <Engine/stdInclude.h>

#include <Graphics/GUI/Widget.h>
#include <Graphics/Types/Texture.h>

#include <Utils/Resources/ResourceRef.h>

namespace SR_CORE_GUI_NS {
    /// Приветственное окно, показывается один раз при первом запуске редактора
    class Welcome : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        Welcome();

    public:
        /// Ключ в пользовательском хранилище: окно уже было показано
        static constexpr const char* ShownStoreKey = "WelcomeWindowShown";

    protected:
        void Draw() override;

    private:
        void OpenAssetsStore();

    private:
        SR_UTILS_NS::ResourceRef<SR_GTYPES_NS::Texture> m_logo;
        /// высота содержимого, измеренная в прошлом кадре
        float_t m_contentHeight = 0.0f;

    };
}

#endif //SR_ENGINE_GUI_WELCOME_H
