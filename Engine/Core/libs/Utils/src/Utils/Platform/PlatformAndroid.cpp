//
// Created by Monika on 14.11.2022.
//

#include <Utils/Platform/Platform.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Debug.h>

#include <android/log.h>

namespace SR_UTILS_NS::Platform {
    void WriteConsoleLog(const std::string& msg) {
        ((void)__android_log_print(ANDROID_LOG_INFO, "SpaRcle Engine", msg.c_str()));
    }

    void WriteConsoleError(const std::string& msg) {
        ((void)__android_log_print(ANDROID_LOG_ERROR, "SpaRcle Engine", msg.c_str()));
    }

    void WriteConsoleWarn(const std::string& msg) {
        ((void)__android_log_print(ANDROID_LOG_WARN, "SpaRcle Engine", msg.c_str()));
    }

    void TextToClipboard(const std::string &text) {

    }

    void CopyFilesToClipboard(std::list<SR_UTILS_NS::Path> paths) {

    }

    void PasteFilesFromClipboard(const SR_UTILS_NS::Path &topath) {

    }

    std::string GetClipboardText() {
        return std::string();
    }

    void ClearClipboard() {

    }

    SR_MATH_NS::FVector2 GetMousePos() {
        return SR_MATH_NS::FVector2();
    }

    void Sleep(uint64_t milliseconds) {

    }

    uint64_t GetProcessUsedMemory() {

    }

    void SetThreadPriority(void *nativeHandle, ThreadPriority priority) {

    }

    void Terminate() {

    }

    void OpenWithAssociatedApp(const Path &filepath) {

    }

    bool Copy(const Path &from, const Path &to) {
        return false;
    }

    std::list<Path> GetInDirectory(const Path &dir, Path::Type type) {
        return {};
    }

    bool CreateFolder(const Path &path) {
        return false;
    }

    bool Delete(const Path &path) {
        return false;
    }

    Path GetApplicationPath() {
        /// У операционной системы Android "папка" с приложением это /
        return Path();
    }

    Path GetApplicationName() {
        return "SREngine";
    }

    bool FileIsHidden(const Path &path) {
        return false;
    }

    void SelfOpen() {

    }

    bool IsAbsolutePath(const Path &path) {
        return false;
    }

    void OpenInNativeFileExplorer(const Path &path){

    }

    bool IsExists(const Path &path) {
        return false;
    }
}

