//
// Created by Monika on 14.11.2022.
//

#include <Utils/Platform/Platform.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Debug.h>

#include <android/log.h>
#include <android/native_activity.h>
#include <android/configuration.h>

struct android_app;

struct android_poll_source {
    int32_t id;
    struct android_app* app;
    void (*process)(struct android_app* app, struct android_poll_source* source);
};

struct android_app {
    void* userData;
    void (*onAppCmd)(struct android_app* app, int32_t cmd);
    int32_t (*onInputEvent)(struct android_app* app, AInputEvent* event);
    ANativeActivity* activity;
    AConfiguration* config;
    void* savedState;
    size_t savedStateSize;
    ALooper* looper;
    AInputQueue* inputQueue;
    ANativeWindow* window;
    ARect contentRect;
    int activityState;
    int destroyRequested;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int msgread;
    int msgwrite;
    pthread_t thread;
    struct android_poll_source cmdPollSource;
    struct android_poll_source inputPollSource;
    int running;
    int stateSaved;
    int destroyed;
    int redrawNeeded;
    AInputQueue* pendingInputQueue;
    ANativeWindow* pendingWindow;
    ARect pendingContentRect;
};

namespace SR_UTILS_NS::Platform {
    android_app* pAndroidInstance = nullptr;

    void Initialize(void* pData) {
        pAndroidInstance = reinterpret_cast<android_app*>(pData);
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
        SRHalt("Not implemented!");
    }

    void CopyFilesToClipboard(std::list<SR_UTILS_NS::Path> paths) {
        SRHalt("Not implemented!");
    }

    void PasteFilesFromClipboard(const SR_UTILS_NS::Path &topath) {
        SRHalt("Not implemented!");
    }

    std::string GetClipboardText() {
        SRHalt("Not implemented!");
        return std::string();
    }

    void ClearClipboard() {
        SRHalt("Not implemented!");
    }

    SR_MATH_NS::FVector2 GetMousePos() {
        SRHalt("Not implemented!");
        return SR_MATH_NS::FVector2();
    }

    void Sleep(uint64_t milliseconds) {
        SRHalt("Not implemented!");
    }

    uint64_t GetProcessUsedMemory() {
        SRHalt("Not implemented!");
    }

    void SetThreadPriority(void *nativeHandle, ThreadPriority priority) {
        SRHalt("Not implemented!");
    }

    void Terminate() {
        SRHalt("Not implemented!");
    }

    void OpenWithAssociatedApp(const Path &filepath) {
        SRHalt("Not implemented!");
    }

    bool Copy(const Path &from, const Path &to) {
        SRHalt("Not implemented!");
        return false;
    }

    std::list<Path> GetInDirectory(const Path &dir, Path::Type type) {
        return {};
    }

    bool CreateFolder(const Path &path) {
        SRHalt("Not implemented!");
        return false;
    }

    bool Delete(const Path &path) {
        SRHalt("Not implemented!");
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
        SRHalt("Not implemented!");
        return false;
    }

    void SelfOpen() {
        SRHalt("Not implemented!");
    }

    bool IsAbsolutePath(const Path &path) {
        SRHalt("Not implemented!");
        return false;
    }

    void OpenInNativeFileExplorer(const Path &path){
        SRHalt("Not implemented!");
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
}

