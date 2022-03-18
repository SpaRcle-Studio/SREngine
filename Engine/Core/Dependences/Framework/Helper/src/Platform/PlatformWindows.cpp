//
// Created by Monika on 17.03.2022.
//

#include <Platform/Platform.h>
#include <Debug.h>

#include <Windows.h>

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
}