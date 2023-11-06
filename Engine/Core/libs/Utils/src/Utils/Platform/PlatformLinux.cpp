//
// Created by innerviewer on 05.11.2023.
//

#include <Utils/Platform/Platform.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Debug.h>

#include <libgen.h>         // dirname
#include <unistd.h>         // readlink
#include <linux/limits.h>   // PATH_MAX
#include <X11/Xlib.h>

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

    bool IsRunningUnderDebugger() {
        std::ifstream sf("/proc/self/status");
        std::string s;
        while (sf >> s)
        {
            if (s == "TracerPid:")
            {
                int pid;
                sf >> pid;
                return pid != 0;
            }
            std::getline(sf, s);
        }

        return false;
    }

    void SetInstance(void* pInstance) {
        SRHaltOnce("Not implemented!");
    }

    void SetMousePos(const SR_MATH_NS::IVector2& pos) {
        SRHaltOnce("Not implemented!");
    }

    void* GetInstance() {
        SRHaltOnce("Not implemented!");
        return nullptr;
    }

    std::optional<std::string> ReadFile(const Path& path) {
        std::ifstream ifs(path.c_str());

        if (!ifs.is_open()) {
            return { };
        }

        return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    }

    void WriteConsoleLog(const std::string& msg) {
        std::cout << msg;
    }

    void WriteConsoleError(const std::string& msg) {
        std::cout << msg;
    }

    void WriteConsoleWarn(const std::string& msg) {
        std::cout << msg;
    }

    void TextToClipboard(const std::string &text) {
        SRHaltOnce("Not implemented!");
    }

    void CopyFilesToClipboard(std::list<SR_UTILS_NS::Path> paths) {
        SRHaltOnce("Not implemented!");
    }

    void PasteFilesFromClipboard(const SR_UTILS_NS::Path &topath) {
        SRHaltOnce("Not implemented!");
    }

    std::string GetClipboardText() {
        SRHaltOnce("Not implemented!");
        return std::string();
    }

    void ClearClipboard() {
        SRHaltOnce("Not implemented!");
    }

    SR_MATH_NS::FVector2 GetMousePos() {
        SRHaltOnce("Not implemented!");
        return SR_MATH_NS::FVector2();
    }

    void Sleep(uint64_t milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    uint64_t GetProcessUsedMemory() {
        SRHaltOnce("Not implemented!");
        return 0;
    }

    void SetThreadPriority(void *nativeHandle, ThreadPriority priority) {
        SRHaltOnce("Not implemented!");
    }

    void Terminate() {
        SRHaltOnce("Not implemented!");
    }

    void OpenWithAssociatedApp(const Path &filepath) {
        SRHaltOnce("Not implemented!");
    }

    bool Copy(const Path &from, const Path &to) {
        SRHaltOnce("Not implemented!");
        return false;
    }

    std::list<Path> GetInDirectory(const Path &dir, Path::Type type) {
        return { };
    }

    bool CreateFolder(const std::string& path) {
        return mkdir(path.c_str(), S_IRWXU);
    }

    bool Delete(const Path &path) {
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

        const bool result = rmdir(path.CStr()) == 0;

        if (!result) {
            SR_WARN(SR_FORMAT("Platform::Delete() : failed to delete folder!\n\tPath: %s", path.CStr()));
        }

        return result;
    }

    Path GetApplicationPath() {
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        const char* path = nullptr;
        if (count != -1) {
            path = dirname(result);
        }

        return path;
    }

    Path GetApplicationName() {
        std::string sp;
        std::ifstream("/proc/self/comm") >> sp;

        return sp;
    }

    bool FileIsHidden(const Path &path) {
        SRHaltOnce("Not implemented!");
        return false;
    }

    void SelfOpen() {
        SRHaltOnce("Not implemented!");
    }

    bool IsAbsolutePath(const Path &path) {
        SRHaltOnce("Not implemented!");
        return false;
    }

    void OpenInNativeFileExplorer(const Path &path){
        SRHaltOnce("Not implemented!");
    }

    bool IsExists(const Path &path) {
        struct stat buffer;
        return (stat(path.c_str(), &buffer) == 0);
    }

    std::vector<SR_MATH_NS::UVector2> GetScreenResolutions() {
        std::vector<SR_MATH_NS::UVector2> resolutions;
        if (auto&& pDisplay = XOpenDisplay(nullptr)) {
            for (int32_t i = 0; i < ScreenCount(pDisplay); ++i) {
                if (auto&& pScreen = ScreenOfDisplay(pDisplay, i)) {
                    resolutions.emplace_back(SR_MATH_NS::UVector2(pScreen->width, pScreen->height));
                }
            }
        }

        return resolutions;
    }

    PlatformType GetType() {
        return PlatformType::Linux;
    }
}

