

# File MessageBox.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**Editor**](dir_ee39d7974ea8a860c3bbba1b251e09d1.md) **>** [**MessageBox.h**](MessageBox_8h.md)

[Go to the documentation of this file](MessageBox_8h.md)


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

    class SR_DLL_EXPORT MessageBoxWidget : public Widget, public SR_UTILS_NS::Singleton<MessageBoxWidget> {
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


