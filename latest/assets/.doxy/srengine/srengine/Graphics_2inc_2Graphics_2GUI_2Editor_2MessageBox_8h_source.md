

# File MessageBox.h

[**File List**](files.md) **>** [**Editor**](dir_cef4e51036814995af3e2bf6cd9d4d03.md) **>** [**MessageBox.h**](Graphics_2inc_2Graphics_2GUI_2Editor_2MessageBox_8h.md)

[Go to the documentation of this file](Graphics_2inc_2Graphics_2GUI_2Editor_2MessageBox_8h.md)


```C++
//
// Created by Monika on 10.02.2022.
//

#ifndef SR_ENGINE_MESSAGEBOX_H
#define SR_ENGINE_MESSAGEBOX_H

#include <Utils/Common/Singleton.h>

#include <Graphics/GUI/Widget.h>

namespace SR_GRAPH_NS::GUI {
    enum class MessageBoxType : uint8_t {
        Info, Warn, Error
    };

    enum MessageBoxButtonBits {
        MESSAGE_BOX_CLOSE    = 0,
        MESSAGE_BOX_OK       = 1 << 0,
        MESSAGE_BOX_CONTINUE = 1 << 1,
        MESSAGE_BOX_CANCEL   = 1 << 2
    };
    typedef uint32_t MessageBoxButton;

    class SR_RENDERER_DLL_API MessageBoxWidget : public Widget, public SR_UTILS_NS::Singleton<MessageBoxWidget> {
        SR_REGISTER_SINGLETON(MessageBoxWidget)
    private:
        MessageBoxWidget();
        ~MessageBoxWidget() override;

    public:
        void Show(const std::string& header, const std::string& message = std::string(),
                MessageBoxType type = MessageBoxType::Info,
                MessageBoxButton buttons = MESSAGE_BOX_CLOSE | MESSAGE_BOX_OK);

    private:
        void Draw() override;

    private:
        std::string m_header;
        std::string m_message;
        MessageBoxType m_type;
        MessageBoxButton m_buttons;

    };
}

#endif //SR_ENGINE_MESSAGEBOX_H
```


