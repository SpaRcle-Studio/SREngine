

# File MessageBox.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Platform**](dir_c017a2c280f4c252cdb104ea7a64a7b4.md) **>** [**MessageBox.h**](Utils_2inc_2Utils_2Platform_2MessageBox_8h.md)

[Go to the documentation of this file](Utils_2inc_2Utils_2Platform_2MessageBox_8h.md)


```C++
//
// Created by Monika on 02.05.2025.
//

#ifndef SR_ENGINE_UTILS_PLATFORM_MESSAGE_BOX_H
#define SR_ENGINE_UTILS_PLATFORM_MESSAGE_BOX_H

#include <Utils/stdInclude.h>

namespace SR_PLATFORM_NS {
    enum class MessageBoxType : uint8_t {
        Ok, OkCancel, YesNo, YesNoCancel
    };

    enum class MessageBoxDefaultButtonType : uint8_t {
        YesOk, No, Cancel
    };

    enum class MessageBoxIconType : uint8_t {
        Info,
        Warning,
        Error,
        Question
    };

    enum class MessageBoxResultType : uint8_t {
        YesOk = 0,
        No = 1,
        Cancel = 2,
    };

    SR_COMMON_DLL_API extern MessageBoxResultType ShowMessageBox(
        const std::string_view& title,
        const std::string_view& message,
        MessageBoxType type,
        MessageBoxIconType iconType,
        MessageBoxDefaultButtonType defaultButtonType
    );
}

#endif //SR_ENGINE_UTILS_PLATFORM_MESSAGE_BOX_H
```


