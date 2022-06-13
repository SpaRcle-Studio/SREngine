//
// Created by Monika on 17.03.2022.
//

#include <Platform/Platform.h>
#include <Debug.h>

#include <Windows.h>
#include <Psapi.h>

/// убираем проклятые min и max после инклуда Windows.h

#ifdef min
    #undef min
#endif

#ifdef max
    #undef max
#endif

namespace SR_UTILS_NS::Platform {
    void TextToClipboard(const std::string &text) {
        if (text.empty()) {
            SR_WARN("Platform::TextToClipboard() : text is empty!");
            return;
        }

        HGLOBAL glob = GlobalAlloc(GMEM_FIXED, text.size() + 1);
        memcpy(glob, text.c_str(), text.size() + 1);

        if (OpenClipboard(NULL)) {
            EmptyClipboard();
            SetClipboardData(CF_TEXT, glob);
            CloseClipboard();
        }
        else
            SR_ERROR("Platform::TextToClipboard() : failed to open clipboard!");
    }

    std::string GetClipboardText() {
        std::string text;

        if (OpenClipboard(NULL)) {
            HANDLE hData = GetClipboardData(CF_TEXT);

            const uint64_t size = GlobalSize(hData);
            if (size > 0) {
                char *pszText = static_cast<char *>(GlobalLock(hData));

                text.resize(size);
                memcpy((void *) text.c_str(), pszText, size);

                GlobalUnlock(hData);
            }

            CloseClipboard();

            return text;
        }

        SR_ERROR("Platform::GetClipboardText() : failed to open clipboard!");

        return text;
    }

    void ClearClipboard() {
        if (OpenClipboard(NULL)) {
            EmptyClipboard();
            CloseClipboard();
        }
        else
            SR_ERROR("Platform::ClearClipboard() : failed to open clipboard!");
    }

    Math::FVector2 GetMousePos() {
        POINT p;
        GetCursorPos(&p);
        return Math::FVector2(p.x, p.y);
    }

    void Sleep(uint64_t milliseconds) {
        ::Sleep(static_cast<DWORD>(milliseconds));
    }

    uint64_t GetProcessUsedMemory() {
        PROCESS_MEMORY_COUNTERS pmc;
        BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
        if (result)
            return static_cast<uint64_t>(pmc.PeakWorkingSetSize);
        else
            return -1;
    }

    void SetThreadPriority(void *nativeHandle, ThreadPriority priority) {
        int32_t winPriority = 0;

        switch (priority) {
            case ThreadPriority::SR_THREAD_PRIORITY_ABOVE_NORMAL:
                winPriority = THREAD_PRIORITY_ABOVE_NORMAL;
                break;
            case ThreadPriority::SR_THREAD_PRIORITY_BELOW_NORMAL:
                winPriority = THREAD_PRIORITY_BELOW_NORMAL;
                break;
            case ThreadPriority::SR_THREAD_PRIORITY_HIGHEST:
                winPriority = THREAD_PRIORITY_HIGHEST;
                break;
            case ThreadPriority::SR_THREAD_PRIORITY_IDLE:
                winPriority = THREAD_PRIORITY_IDLE;
                break;
            case ThreadPriority::SR_THREAD_PRIORITY_LOWEST:
                winPriority = THREAD_PRIORITY_LOWEST;
                break;
            case ThreadPriority::SR_THREAD_PRIORITY_NORMAL:
                winPriority = THREAD_PRIORITY_NORMAL;
                break;
            case ThreadPriority::SR_THREAD_PRIORITY_TIME_CRITICAL:
                winPriority = THREAD_PRIORITY_TIME_CRITICAL;
                break;
            default:
                SRAssert(false);
                return;
        }

        auto&& result = ::SetThreadPriority(static_cast<HANDLE>(nativeHandle), winPriority);

        if (result == FALSE) {
            SR_ERROR("Platform::SetThreadPriority() : failed to set thread priority!");
        }
    }

    void Terminate() {
#ifdef SR_MINGW

#else
        terminate();
#endif
    }
}