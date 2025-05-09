

# File MessageBox.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Platform**](dir_dff07e13fcd57a959fed4d2a16791af6.md) **>** [**MessageBox.h**](Utils_2inc_2Utils_2Platform_2MessageBox_8h.md)

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


