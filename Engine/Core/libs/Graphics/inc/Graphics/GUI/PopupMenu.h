//
// Created by Monika on 14.08.2023.
//

#ifndef SR_ENGINE_POPUPMENU_H
#define SR_ENGINE_POPUPMENU_H

#include <Graphics/GUI/ImGUI.h>

namespace SR_GRAPH_GUI_NS {
    class MenuItemSubWidget;
    class NodeWidget;

    struct DrawPopupContext {
        SR_MATH_NS::FVector2 popupPos;
        NodeWidget* pWidget = nullptr;
    };

    class PopupItemSubWidget : public SR_UTILS_NS::NonCopyable {
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<PopupItemSubWidget>;

    public:
        explicit PopupItemSubWidget(std::string name)
            : m_name(std::move(name))
        { }

    public:
        void Draw(const DrawPopupContext& context);
        void SetName(std::string name) { m_name = std::move(name); }

        MenuItemSubWidget& AddMenu(std::string name);
        MenuItemSubWidget& AddMenu(const std::vector<std::string>& category);

    protected:
        std::string m_name;
        std::vector<SR_HTYPES_NS::SharedPtr<MenuItemSubWidget>> m_menuItems;

    };

    class MenuItemSubWidget : public SR_UTILS_NS::NonCopyable {
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<PopupItemSubWidget>;
        using Action = SR_HTYPES_NS::Function<void(const DrawPopupContext& context)>;

    public:
        MenuItemSubWidget() = default;
        explicit MenuItemSubWidget(std::string name)
            : m_name(std::move(name))
        { }

    public:
        void Draw(const DrawPopupContext& context);

        SR_NODISCARD const std::string& GetName() const noexcept { return m_name; }

        MenuItemSubWidget& AddMenu(const std::string& name);
        MenuItemSubWidget& SetAction(Action action);

    protected:
        std::vector<SR_HTYPES_NS::SharedPtr<MenuItemSubWidget>> m_menuItems;
        std::string m_name;
        Action m_action;

    };
}

#endif //SR_ENGINE_POPUPMENU_H
