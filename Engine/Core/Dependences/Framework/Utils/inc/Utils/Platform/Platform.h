//
// Created by Monika on 17.03.2022.
//

#ifndef SRENGINE_PLATFORM_H
#define SRENGINE_PLATFORM_H

#include <Utils/Math/Vector2.h>
#include <Utils/Common/ThreadUtils.h>

namespace SR_UTILS_NS::Platform {
    SR_DLL_EXPORT extern void TextToClipboard(const std::string& text);
    SR_DLL_EXPORT extern std::string GetClipboardText();
    SR_DLL_EXPORT extern void ClearClipboard();
    SR_DLL_EXPORT extern Math::FVector2 GetMousePos();
    SR_DLL_EXPORT extern void Sleep(uint64_t milliseconds);
    SR_DLL_EXPORT extern uint64_t GetProcessUsedMemory();
    SR_DLL_EXPORT extern void SetThreadPriority(void* nativeHandle, ThreadPriority priority);
    SR_DLL_EXPORT extern void Terminate();
}

#endif //SRENGINE_PLATFORM_H
