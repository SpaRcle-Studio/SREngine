//
// Created by innerviewer on 05.11.2023.
//

#include <Utils/Platform/Platform.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Debug.h>

namespace SR_UTILS_NS::Platform {
    void InitSegmentationHandler() {
        SRHaltOnce("Not implemented!");
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
        SRHaltOnce("Not implemented!");
        return std::nullopt;
    }

    void WriteConsoleLog(const std::string& msg) {
        SRHaltOnce("Not implemented!");
    }

    void WriteConsoleError(const std::string& msg) {
        SRHaltOnce("Not implemented!");
    }

    void WriteConsoleWarn(const std::string& msg) {
        SRHaltOnce("Not implemented!");
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
        SRHaltOnce("Not implemented!");
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
        SRHaltOnce("Not implemented!");
        return false;
    }

    bool Delete(const Path &path) {
        SRHaltOnce("Not implemented!");
        return false;
    }

    Path GetApplicationPath() {
        return Path();
    }

    Path GetApplicationName() {
        return "SREngine";
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
        SRHaltOnce("Not implemented!");
        return false;
    }

    std::vector<SR_MATH_NS::UVector2> GetScreenResolutions() {
        SRHaltOnce("Not implemented!");
        return { };
    }
}

