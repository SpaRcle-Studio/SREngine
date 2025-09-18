

# File Platform.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Platform**](dir_c017a2c280f4c252cdb104ea7a64a7b4.md) **>** [**Platform.h**](Platform_8h.md)

[Go to the documentation of this file](Platform_8h.md)


```C++
//
// Created by Monika on 17.03.2022.
//

#ifndef SR_ENGINE_UTILS_PLATFORM_H
#define SR_ENGINE_UTILS_PLATFORM_H

#include <Utils/Math/Vector2.h>
#include <Utils/Common/ThreadUtils.h>
#include <Utils/FileSystem/Path.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(PlatformType, uint8_t,
        Unknown, Windows, Linux, Android, MacOS, Emscripten, IOS
    );
}

namespace SR_UTILS_NS::Platform {
    static bool IsCompiledUnderMSVC() {
    #ifdef SR_MSVC
        return true;
    #else
        return false;
    #endif
    }

    struct FileMetadata {
        uint64_t lastWriteTime = SR_UINT64_MAX;
    };

    struct MouseState {
        SR_MATH_NS::FVector2 position;
        bool buttonStates[5] { false, false, false, false, false };
    };

    extern std::mutex g_platformLogMutex;

    SR_NORETURN SR_COMMON_DLL_API extern void Terminate(bool isError = true);

    SR_COMMON_DLL_API extern void InitializePlatform();
    SR_COMMON_DLL_API extern void InitSegmentationHandler();
    SR_COMMON_DLL_API extern void SetInstance(void* pInstance);
    SR_COMMON_DLL_API extern void* GetInstance();
    SR_COMMON_DLL_API extern PlatformType GetType();
    SR_COMMON_DLL_API extern bool IsMobilePlatform();

    SR_COMMON_DLL_API extern std::string ExecuteCommand(const std::string& command, const std::vector<std::string>& env = {});
    SR_COMMON_DLL_API extern void SetEnvironmentVar(const std::string_view& name, const std::string_view& value);
    SR_COMMON_DLL_API extern std::optional<std::string> ReadFile(const Path& path);
    SR_COMMON_DLL_API extern void TextToClipboard(const std::string& text);
    SR_COMMON_DLL_API extern void CopyFilesToClipboard(std::list<SR_UTILS_NS::Path> paths);
    SR_COMMON_DLL_API extern void SetCurrentProcessDirectory(const SR_UTILS_NS::Path& directory);
    SR_COMMON_DLL_API extern void PasteFilesFromClipboard(const SR_UTILS_NS::Path& topath);
    SR_COMMON_DLL_API extern void ClearClipboard();
    SR_COMMON_DLL_API extern void Sleep(uint64_t milliseconds);
    SR_COMMON_DLL_API extern void WriteConsoleLog(const std::string& msg);
    SR_COMMON_DLL_API extern void WriteConsoleError(const std::string& msg);
    SR_COMMON_DLL_API extern void WriteConsoleWarn(const std::string& msg);
    SR_COMMON_DLL_API extern void SelfOpen();
    SR_COMMON_DLL_API extern void OpenFile(const SR_UTILS_NS::Path& path, const std::string& args);
    SR_COMMON_DLL_API extern void Unzip(const SR_UTILS_NS::Path& source, const SR_UTILS_NS::Path& destination, bool replace = true);
    SR_COMMON_DLL_API extern void OpenWithAssociatedApp(const Path& filepath);
    SR_COMMON_DLL_API extern bool CreateFolder(const std::string& path);
    SR_COMMON_DLL_API extern bool Copy(const Path& from, const Path& to);
    SR_COMMON_DLL_API extern bool Delete(const Path& path);
    SR_COMMON_DLL_API extern bool WaitAndDelete(const Path& path);
    SR_COMMON_DLL_API extern bool DownloadFile(const std::string& url, const SR_UTILS_NS::Path& outputPath);
    SR_COMMON_DLL_API extern void* LoadLibraryModule(const Path& path);
    SR_COMMON_DLL_API extern bool UnloadLibraryModule(void* pLibrary);
    SR_COMMON_DLL_API extern void* GetLibraryFunctionAddress(void* pLibrary, const char* pFunctionName);

    SR_COMMON_DLL_API extern Path::Type GetPathType(std::string_view path);
    SR_COMMON_DLL_API extern uint64_t GetProcessUsedMemory();
    SR_COMMON_DLL_API extern uint16_t GetCurrentProcessId();
    SR_COMMON_DLL_API extern SR_MATH_NS::FVector2 GetMousePos();
    SR_COMMON_DLL_API extern MouseState GetMouseState();
    SR_COMMON_DLL_API extern bool GetSystemKeyboardState(uint8_t* pKeyCodes);
    SR_COMMON_DLL_API extern std::string GetClipboardText();
    SR_COMMON_DLL_API extern Path GetApplicationResourcesPath();
    SR_COMMON_DLL_API extern Path GetApplicationPath();
    SR_COMMON_DLL_API extern Path GetApplicationDirectory();
    SR_COMMON_DLL_API extern Path GetApplicationName();
    SR_COMMON_DLL_API extern std::list<Path> GetInDirectory(const Path& dir, Path::Type type);
    SR_COMMON_DLL_API extern std::list<Path> GetAllInDirectory(const Path& dir);
    SR_COMMON_DLL_API extern FileMetadata GetFileMetadata(const Path& file);
    SR_COMMON_DLL_API extern SR_MATH_NS::UVector2 GetScreenResolution();
    SR_COMMON_DLL_API extern double_t GetScreenDPI();
    SR_COMMON_DLL_API extern std::vector<SR_MATH_NS::UVector2> GetScreenResolutions();
    SR_COMMON_DLL_API extern bool FileIsHidden(const Path& path);
    SR_COMMON_DLL_API extern bool IsExists(const Path& path);
    SR_COMMON_DLL_API extern bool IsAbsolutePath(const Path& path);
    SR_COMMON_DLL_API extern bool IsRunningUnderDebugger();
    SR_COMMON_DLL_API extern bool IsFileDeletable(const SR_UTILS_NS::Path& path);
    SR_COMMON_DLL_API extern std::optional<Path> GetApplicationCachePath();
    SR_COMMON_DLL_API extern std::optional<Path> GetApplicationLogPath();

    SR_COMMON_DLL_API extern void SetMousePos(const SR_MATH_NS::IVector2& pos);
    SR_COMMON_DLL_API extern void SetCursorVisible(bool isVisible);
    SR_COMMON_DLL_API extern void ConfineCursor(); // TODO: add ability to confine cursor to a specific window
    SR_COMMON_DLL_API extern void ReleaseCursorConfinement(); // TODO: add ability to confine cursor to a specific window
    SR_COMMON_DLL_API extern void SetThreadPriority(void* nativeHandle, ThreadPriority priority);
    SR_COMMON_DLL_API extern void CopyPermissions(const SR_UTILS_NS::Path& source, const SR_UTILS_NS::Path& destination);
}
#endif //SR_ENGINE_UTILS_PLATFORM_H
```


