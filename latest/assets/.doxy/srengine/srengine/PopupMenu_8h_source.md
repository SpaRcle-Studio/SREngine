

# File PopupMenu.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**PopupMenu.h**](PopupMenu_8h.md)

[Go to the documentation of this file](PopupMenu_8h.md)


```C++
//
// Created by Monika on 14.08.2023.
//

#ifndef SR_ENGINE_POPUPMENU_H
#define SR_ENGINE_POPUPMENU_H

#include <Graphics/macros.h>

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
```


