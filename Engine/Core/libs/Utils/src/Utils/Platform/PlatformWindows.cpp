//
// Created by Monika on 17.03.2022.
//

#include <Utils/Platform/Platform.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Debug.h>

#include <Windows.h>
#include <Psapi.h>
#include <rpc.h>
#include <tchar.h>
#include <shellapi.h>
#include <commdlg.h>
#include <shlobj.h>
#include <ImageHlp.h>
#include <csignal>

#ifdef SR_MINGW
    #include <ShObjIdl.h>
#endif

/// убираем проклятые min и max после инклуда Windows.h

#ifdef min
    #undef min
#endif

#ifdef max
    #undef max
#endif

namespace SR_UTILS_NS::Platform {
    void WriteConsoleLog(const std::string& msg) {
        std::cout << msg;
    }

    void WriteConsoleError(const std::string& msg) {
        std::cerr << msg;
    }

    void WriteConsoleWarn(const std::string& msg) {
        std::cout << msg;
    }

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
        std::string message(messageBuffer, size - 3);
        //Free the Win32's string's buffer.
        LocalFree(messageBuffer);
        return message;
    }

    std::string ErrorCodeToString(const DWORD a_error_code)
    {
        // Get the last windows error message.
        char msg_buf[1025] = { 0 };
        // Get the error message for our os code.
        if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                          0,
                          a_error_code,
                          0,
                          msg_buf,
                          sizeof(msg_buf) - 1,
                          0))
        {
            // Remove trailing newline character.
            char* nl_ptr = 0;
            if (0 != (nl_ptr = strchr(msg_buf, '\n')))
            {
                *nl_ptr = '\0';
            }
            if (0 != (nl_ptr = strchr(msg_buf, '\r')))
            {
                *nl_ptr = '\0';
            }
            return std::string(msg_buf);
        }
        return std::string("Failed to get error message");
    }
}

namespace SR_UTILS_NS::Platform {
    void SegmentationHandler(int sig) {
        WriteConsoleError("Application crashed!\n" + SR_UTILS_NS::GetStacktrace());
        Breakpoint();
        exit(1);
    }

    void StdHandler() {
        SegmentationHandler(1);
    }

    void InitSegmentationHandler() {
        signal(SIGSEGV, SegmentationHandler);
        std::set_terminate(StdHandler);
    }

    void SetInstance(void*) {

    }

    void* GetInstance() {
        return nullptr;
    }


    std::optional<std::string> ReadFile(const Path& path) {
        std::ifstream ifs(path.c_str());

        if (!ifs.is_open()) {
            return std::optional<std::string>();
        }

        return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    }

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

    class COleInitialize {
    public:
        COleInitialize() : m_hr(OleInitialize(NULL)) { }
        ~COleInitialize() { if (SUCCEEDED(m_hr)) OleUninitialize(); }
        operator HRESULT() const { return m_hr; }
        HRESULT m_hr;
    };

    ///функция для копирования файла/файлов в буфер обмена
    void CopyFilesToClipboard(std::list<SR_UTILS_NS::Path> paths) {

        // calculate *bytes* needed for memory allocation
        int clpSize = sizeof(DROPFILES);
        for (auto &&path:paths)
            clpSize += sizeof(TCHAR) * (_tcslen(path.ToString().c_str()) + 1); // + 1 => '\0'
        clpSize += sizeof(TCHAR); // two \0 needed at the end

        // allocate the zero initialized memory
        HDROP hdrop   = (HDROP)GlobalAlloc(GHND, clpSize);
        DROPFILES* df = (DROPFILES*)GlobalLock(hdrop);
        df->pFiles    = sizeof(DROPFILES); // string offset
#ifdef _UNICODE
        df->fWide     = TRUE; // unicode file names
#endif // _UNICODE

        // copy paths to the allocated memory
        TCHAR* dstStart = (TCHAR*)&df[1];
        for (auto &&path:paths)
        {
            _tcscpy(dstStart, path.ToString().c_str());
            dstStart = &dstStart[_tcslen(path.c_str()) + 1]; // + 1 => get beyond '\0'
        }
        GlobalUnlock(hdrop);

        // prepare the clipboard
        OpenClipboard(NULL);
        EmptyClipboard();
        SetClipboardData(CF_HDROP, hdrop);
        CloseClipboard();
    }

    ///функция для получения файла/файлов из буфер обмена
    void PasteFilesFromClipboard(const SR_UTILS_NS::Path &topath) {

        if(!topath.IsDir()) {
            return;
        }

        if (IsClipboardFormatAvailable(CF_HDROP)) { ///CF_HDROP - формат списка файлов
            std::list<SR_UTILS_NS::Path> paths;

            OpenClipboard(NULL);
            HDROP hDrop = static_cast<HDROP>(GetClipboardData(CF_HDROP));
            CloseClipboard();

            const uint64_t size = 32768;
            std::string buffer;
            buffer.resize(size);
            for (int i = 0; i < DragQueryFileA(hDrop,0xFFFFFFFF,NULL,NULL); i++) {
                DragQueryFileA(hDrop,i,&buffer[0],size);
                auto path = SR_UTILS_NS::Path(buffer);
                Copy(path,topath.Concat(path.GetBaseNameAndExt()));
            }
        } else {
            return;
        }
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
        SR_PLATFORM_NS::WriteConsoleError("Function \"Terminate\" has been called... >_<\n" + SR_UTILS_NS::GetStacktrace());
        SR_UTILS_NS::Breakpoint();
#ifdef SR_ANDROID

#endif
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
                SR_WARN(SR_FORMAT("Platform::Copy() : %s\n\tFrom: %s\n\tTo: %s", GetLastErrorAsString().c_str(), from.CStr(), to.CStr()));
            }

            return result;
        }

        if (!from.IsDir()) {
            SR_WARN(SR_FORMAT("Platform::Copy() : \"%s\" is not directory!", from.c_str()));
            return false;
        }

        CreateFolder(to.ToStringRef());

        for (auto&& item : GetInDirectory(from, Path::Type::Undefined)) {
            if (Copy(item, to.Concat(item.GetBaseNameAndExt()))) {
                continue;
            }

            return false;
        }

        return true;
    }

    std::list<Path> GetInDirectory(const Path &dir, Path::Type type) {
        std::list<Path> items;
        const std::string search_path = dir.ToString() + "/*.*";
        WIN32_FIND_DATA fd;
        HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
        if(hFind != INVALID_HANDLE_VALUE) {
            do {
                if ((fd.dwFileAttributes & static_cast<uint64_t>(FILE_ATTRIBUTE_DIRECTORY)) && type == Path::Type::File) {
                    continue;
                }

                if (!(fd.dwFileAttributes & static_cast<uint64_t>(FILE_ATTRIBUTE_DIRECTORY)) && type == Path::Type::Folder) {
                    continue;
                }

                const auto filename = std::string(fd.cFileName);
                if (filename != "." && filename != ".." && !filename.empty())
                    items.emplace_back(dir.ToString() + "/" + filename);
            }
            while(::FindNextFile(hFind, &fd));

            ::FindClose(hFind);
        }
        return items;
    }

    bool CreateFolder(const std::string& path) {
#ifdef SR_MINGW
        return mkdir(path.c_str());
#else
        return _mkdir(path.c_str());
#endif
    }

    bool Delete(const Path &path) { ///TODO: Обезопасить от безвозвратного удаления файлов
        if (path.IsFile()) {
            const bool result = std::remove(path.CStr()) == 0;

            if (!result) {
                SR_WARN(SR_FORMAT("Platform::Delete() : failed to delete file!\n\tPath: %s", path.CStr()));
            }

            return result;
        }

        if (!path.IsDir()) {
            return false;
        }

        for (auto&& item : GetInDirectory(path, Path::Type::Undefined)) {
            if (Delete(item)) {
                continue;
            }

            return false;
        }

        const bool result = _rmdir(path.CStr()) == 0;

        if (!result) {
            SR_WARN(SR_FORMAT("Platform::Delete() : failed to delete folder!\n\tPath: %s", path.CStr()));
        }

        return result;
    }

    Path GetApplicationPath() {
        const std::size_t buf_len = 260;
        auto s = new TCHAR[buf_len];
        auto path_len = GetModuleFileName(GetModuleHandle(nullptr), s, buf_len);
        return s;
    }

    Path GetApplicationName() {
        const std::size_t buf_len = 260;
        auto s = new TCHAR[buf_len];
        auto path_len = GetModuleFileName(GetModuleHandle(nullptr), s, buf_len);
        return Path(s).GetBaseNameAndExt();
    }

    bool FileIsHidden(const Path &path) {
        const DWORD attributes = GetFileAttributes(path.CStr());
        if (attributes & FILE_ATTRIBUTE_HIDDEN)
            return true;

        return false;
    }

    void SelfOpen() {
        auto&& exe = SR_PLATFORM_NS::GetApplicationPath();
        ShellExecute(NULL, "open", exe.CStr(), NULL, NULL, SW_SHOWDEFAULT);
    }

    bool IsAbsolutePath(const Path &path) {
        auto&& view = path.View();
        return view.size() >= 2 && view[1] == ':';
    }

    void OpenInNativeFileExplorer(const Path &path){
        ShellExecuteA(NULL, "open", path.ToString().c_str(), NULL, NULL, SW_SHOWDEFAULT);
    }

    bool IsExists(const Path &path) {
        const DWORD ftyp = GetFileAttributesA(path.CStr());

        if (ftyp == INVALID_FILE_ATTRIBUTES) {
            return false;  /// something is wrong with your path!
        }

        /// it is file or directory

        return true;
    }

    std::vector<SR_MATH_NS::UVector2> GetScreenResolutions() {
        auto&& resolutions = std::vector<SR_MATH_NS::UVector2>();

        resolutions.reserve(64);

        DEVMODE dm = { 0 };
        dm.dmSize = sizeof(dm);

        for (uint32_t iModeNum = 0; EnumDisplaySettings(NULL, iModeNum, &dm) != 0; ++iModeNum) {
            auto&& resolution = SR_MATH_NS::UVector2(dm.dmPelsWidth, dm.dmPelsHeight);

            if (std::find(resolutions.begin(), resolutions.end(), resolution) != resolutions.end()) {
                continue;
            }

            resolutions.emplace_back(resolution);
        }

        if (resolutions.empty()) {
            resolutions.emplace_back(SR_MATH_NS::UVector2(400, 400));
        }

        return resolutions;
    }

    void SetMousePos(const SR_MATH_NS::IVector2& pos) {
        ::SetCursorPos(static_cast<int32_t>(pos.x), static_cast<int32_t>(pos.y));
    }

    PlatformType GetType() {
        return PlatformType::Windows;
    }
}