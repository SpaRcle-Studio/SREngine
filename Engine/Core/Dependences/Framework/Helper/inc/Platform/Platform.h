//
// Created by Monika on 17.03.2022.
//

#ifndef SRENGINE_PLATFORM_H
#define SRENGINE_PLATFORM_H

#include <Math/Vector2.h>

namespace SR_UTILS_NS::Platform {
    extern void TextToClipboard(const std::string& text);
    extern std::string GetClipboardText();
    extern void ClearClipboard();
    extern Math::FVector2 GetMousePos();
    extern void Sleep(uint64_t milliseconds);
    extern uint64_t GetProcessUsedMemory();
}

#endif //SRENGINE_PLATFORM_H
