//
// Created by Monika on 14.11.2022.
//

#include <Utils/Platform/Platform.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Debug.h>

#include <Utils/Platform/AndroidNativeAppGlue.h>

#include <android/log.h>
#include <android/native_activity.h>
#include <android/configuration.h>

namespace SR_UTILS_NS::Platform {
    static android_app* pAndroidInstance = nullptr;

    void InitSegmentationHandler() {

    }

    void SetInstance(void* pInstance) {
        pAndroidInstance = reinterpret_cast<android_app*>(pInstance);
    }

    void SetMousePos(const SR_MATH_NS::IVector2& pos) {

    }

    void* GetInstance() {
        return (void*)pAndroidInstance;
    }

    std::optional<std::string> ReadFile(const Path& path) {
        std::optional<std::string> content;

        AAssetDir* assetDir = AAssetManager_openDir(pAndroidInstance->activity->assetManager, "");
        if (AAsset* asset = AAssetManager_open(pAndroidInstance->activity->assetManager, path.c_str(), AASSET_MODE_STREAMING)) {
            const uint64_t len = AAsset_getLength64(asset);
            content = std::string();
            content->resize(len);
            AAsset_read(asset, content->data(), len);
            AAsset_close(asset);
        }

        AAssetDir_close(assetDir);

        return content;
    }

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
        return {};
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
        /// У операционной системы Android нет папки с приложением,
        /// работа идет с упакованными ресурсами в assets
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
        AAssetDir* assetDir = AAssetManager_openDir(pAndroidInstance->activity->assetManager, "");
        if (AAsset* asset = AAssetManager_open(pAndroidInstance->activity->assetManager, path.c_str(), AASSET_MODE_STREAMING)) {
            AAsset_close(asset);
            AAssetDir_close(assetDir);
            return true;
        }

        AAssetDir_close(assetDir);
        return false;
    }

    std::vector<SR_MATH_NS::UVector2> GetScreenResolutions() {
        if (!pAndroidInstance) {
            SR_ERROR("PlatformAndroid::GetScreenResolutions() : pAndroidInstance is nullptr!");
            return { SR_MATH_NS::UVector2(400, 400) };
        }

        if (!pAndroidInstance->window) {
            SR_ERROR("PlatformAndroid::GetScreenResolutions() : ANativeWindow is nullptr!");
            return { SR_MATH_NS::UVector2(400, 400) };
        }

        auto&& resolutions = std::vector<SR_MATH_NS::UVector2>();

        resolutions.emplace_back(SR_MATH_NS::UVector2(
                static_cast<uint32_t>(ANativeWindow_getWidth(pAndroidInstance->window)),
                static_cast<uint32_t>(ANativeWindow_getHeight(pAndroidInstance->window))
        ));

        return resolutions;
    }
}

