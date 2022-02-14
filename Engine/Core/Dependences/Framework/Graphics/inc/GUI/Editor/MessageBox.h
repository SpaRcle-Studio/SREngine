//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_MESSAGEBOX_H
#define SRENGINE_MESSAGEBOX_H

#include <macros.h>
#include <GUI/Widget.h>
#include <Utils/NonCopyable.h>
#include <Utils/Singleton.h>
#include <mutex>
#include <string>

namespace Framework::Graphics::GUI {
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

    class MessageBoxWidget : public Widget, public Helper::Singleton<MessageBoxWidget> {
        friend class Helper::Singleton<MessageBoxWidget>;
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
        std::recursive_mutex m_mutex;
        std::string m_header;
        std::string m_message;
        MessageBoxType m_type;
        MessageBoxButton m_buttons;

    };
}

#endif //SRENGINE_MESSAGEBOX_H
