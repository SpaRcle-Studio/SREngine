//
// Created by Monika on 17.03.2022.
//

#include <Utils/Platform/Platform.h>
#include <Utils/Debug.h>

#include <Windows.h>
#include <Psapi.h>
#include <rpc.h>
#include <shellapi.h>

/// убираем проклятые min и max после инклуда Windows.h

#ifdef min
    #undef min
#endif

#ifdef max
    #undef max
#endif

namespace SR_UTILS_NS::Platform {
    std::string GetLastErrorAsString()
    {
        //Get the error message ID, if any.
        DWORD errorMessageID = ::GetLastError();
        if(errorMessageID == 0) {
            return std::string(); //No error message has been recorded
        }
        LPSTR messageBuffer = nullptr;
        //Ask Win32 to give us the string version of that message ID.
        //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                     NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
        //Copy the error message into a std::string.
        std::string message(messageBuffer, size);
        //Free the Win32's string's buffer.
        LocalFree(messageBuffer);
        return message;
    }
}

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
#ifdef SR_MINGW
#else
        PROCESS_MEMORY_COUNTERS pmc;
        BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
        if (result) {
            return static_cast<uint64_t>(pmc.PeakWorkingSetSize);
        }
#endif

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

    void OpenWithAssociatedApp(const Path &filepath) {
        system(filepath.ToString().c_str());
    }

    bool Copy(const Path &from, const Path &to) {
        if (from.IsFile()) {
            const bool result = CopyFileA(
                    reinterpret_cast<LPCSTR>(from.ToString().c_str()),
                    reinterpret_cast<LPCSTR>(to.ToString().c_str()),
                    false
            );

            if (!result) {
                SR_WARN("Platform::Copy() : " + GetLastErrorAsString());
            }

            return result;
        }

        if (!from.IsDir()) {
            return false;
        }

        CreateFolder(to);

        for (auto&& item : GetInDirectory(from)) {
            if (Copy(item, to.Concat(item.GetBaseNameAndExt()))) {
                continue;
            }

            return false;
        }

        return true;
    }

    std::list<Path> GetInDirectory(const Path &dir) {
        std::list<Path> items;
        const std::string search_path = dir.ToString() + "/*.*";
        WIN32_FIND_DATA fd;
        HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
        if(hFind != INVALID_HANDLE_VALUE) {
            do {
                const auto filename = std::string(fd.cFileName);
                if (filename != "." && filename != ".." && !filename.empty())
                    items.emplace_back(dir.ToString() + "/" + filename);
            }
            while(::FindNextFile(hFind, &fd));

            ::FindClose(hFind);
        }
        return items;
    }

    bool CreateFolder(const Path &path) {
#ifdef SR_MINGW
        return mkdir(path.CStr());
#else
        return _mkdir(path.CStr());
#endif
    }
}